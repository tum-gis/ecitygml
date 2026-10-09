// Measures the geometry of every building in a CityGML file: areas and triangle counts of its wall,
// roof and ground surfaces, its doors and windows, and the volumes of its solids.
//
// Geometry calculations work on the geometry stored inline: `area_3d` of a multi surface,
// `volume_3d` of a solid, `triangulate` (a `Triangulation`, whose `surface` holds the triangles).
// They return a `..._result` struct whose `err` is set when they can't compute a result. A common
// case: a solid whose surfaces only reference the boundary polygons by `xlink:href` (the reader
// doesn't resolve such references, as in Rust), shown here as "not computable" with the error message.
//
// Built by bindings/c/CMakeLists.txt (`mise run build-bindings-c`), which also runs it as a test.
//
// Usage: 05_measure_geometry path/to/model.gml
//
// Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml (shortened):
//
//     Building UUID_d281adfc-4901-0f52-540b-4cc1a9325f82
//       WallSurface: 4, area 188.629 m^2, 10 triangles
//       RoofSurface: 2, area 138.564 m^2, 4 triangles
//       GroundSurface: 1, area 120.000 m^2, 2 triangles
//       Doors and windows: 0, area 0.000 m^2
//       LoD2 solid: 7 surfaces, 7 of them xlink:href references
//         Volume: not computable (surface member references '#PolyID7350_878_759628_120742' via ...)

#include <stdio.h>
#include <string.h>

#include "AbstractFeatureKindRef.h"
#include "AbstractFeatureKindRefIterator.h"
#include "AbstractFillingSurfaceKind.h"
#include "AbstractFillingSurfaceProperty.h"
#include "AbstractFillingSurfacePropertyIterator.h"
#include "AbstractSpaceBoundaryKind.h"
#include "AbstractSpaceBoundaryProperty.h"
#include "AbstractSpaceBoundaryPropertyIterator.h"
#include "AbstractSurfaceProperty.h"
#include "AbstractSurfacePropertyIterator.h"
#include "Building.h"
#include "CityModel.h"
#include "Error.h"
#include "GmlReader.h"
#include "GroundSurface.h"
#include "Id.h"
#include "MultiSurface.h"
#include "MultiSurfaceProperty.h"
#include "RoofSurface.h"
#include "Shell.h"
#include "Solid.h"
#include "SolidProperty.h"
#include "Triangle.h"
#include "TriangleIterator.h"
#include "TriangulatedSurface.h"
#include "Triangulation.h"
#include "WallSurface.h"

typedef struct {
    size_t count;
    double area;
    size_t triangles;
} Measurement;

static int print_error(Error *error) {
    DiplomatWrite *message = diplomat_buffer_write_create(64);
    ecitygml_Error_message(error, message);
    fprintf(stderr, "error: %.*s\n", (int)diplomat_buffer_write_len(message), diplomat_buffer_write_get_bytes(message));
    diplomat_buffer_write_destroy(message);
    ecitygml_Error_destroy(error);
    return 1;
}

// Prints "not computable (<message>)" and frees the error.
static void print_not_computable(Error *error) {
    DiplomatWrite *message = diplomat_buffer_write_create(64);
    ecitygml_Error_message(error, message);
    printf("not computable (%.*s)\n", (int)diplomat_buffer_write_len(message), diplomat_buffer_write_get_bytes(message));
    diplomat_buffer_write_destroy(message);
    ecitygml_Error_destroy(error);
}

// The multi surface of the highest level of detail among a thematic surface's properties, or NULL.
static const MultiSurface *highest_lod(const MultiSurfaceProperty *lod3, const MultiSurfaceProperty *lod2,
                                       const MultiSurfaceProperty *lod1, const MultiSurfaceProperty *lod0) {
    const MultiSurfaceProperty *properties[] = {lod3, lod2, lod1, lod0};
    for (size_t index = 0; index < 4; ++index) {
        const MultiSurface *multi_surface = properties[index] ? ecitygml_MultiSurfaceProperty_object(properties[index]) : NULL;
        if (multi_surface) {
            return multi_surface;
        }
    }
    return NULL;
}

// Adds a surface with its highest LoD multi surface (may be NULL); returns the error if the area or
// triangulation can't be computed, else NULL.
static Error *add_surface(Measurement *measurement, const MultiSurface *multi_surface) {
    ++measurement->count;
    if (multi_surface == NULL) {
        return NULL;
    }
    ecitygml_MultiSurface_area_3d_result area = ecitygml_MultiSurface_area_3d(multi_surface);
    if (!area.is_ok) {
        return area.err;
    }
    measurement->area += area.ok;
    ecitygml_MultiSurface_triangulate_result triangulation = ecitygml_MultiSurface_triangulate(multi_surface);
    if (!triangulation.is_ok) {
        return triangulation.err;
    }
    TriangleIterator *triangles = ecitygml_TriangulatedSurface_triangles(ecitygml_Triangulation_surface(triangulation.ok));
    while (ecitygml_TriangleIterator_next(triangles) != NULL) {
        ++measurement->triangles;
    }
    ecitygml_TriangleIterator_destroy(triangles);
    ecitygml_Triangulation_destroy(triangulation.ok);
    return NULL;
}

// Adds the doors and windows of a wall, roof or ground surface; destroys the iterator.
static Error *add_filling_surfaces(Measurement *fillings, AbstractFillingSurfacePropertyIterator *iterator) {
    Error *error = NULL;
    const AbstractFillingSurfaceProperty *property;
    while (error == NULL && (property = ecitygml_AbstractFillingSurfacePropertyIterator_next(iterator)) != NULL) {
        const AbstractFillingSurfaceKind *filling = ecitygml_AbstractFillingSurfaceProperty_object(property);
        if (filling) {
            error = add_surface(fillings,
                                highest_lod(ecitygml_AbstractFillingSurfaceKind_lod3_multi_surface(filling),
                                            ecitygml_AbstractFillingSurfaceKind_lod2_multi_surface(filling),
                                            ecitygml_AbstractFillingSurfaceKind_lod1_multi_surface(filling),
                                            ecitygml_AbstractFillingSurfaceKind_lod0_multi_surface(filling)));
        }
    }
    ecitygml_AbstractFillingSurfacePropertyIterator_destroy(iterator);
    return error;
}

// Measures the wall, roof and ground surfaces and their doors and windows; returns the first error.
static Error *measure_boundaries(const Building *building, Measurement measurements[4]) {
    Measurement *walls = &measurements[0], *roofs = &measurements[1], *grounds = &measurements[2];
    Measurement *fillings = &measurements[3];
    Error *error = NULL;
    AbstractSpaceBoundaryPropertyIterator *boundaries = ecitygml_Building_boundaries(building);
    const AbstractSpaceBoundaryProperty *property;
    while (error == NULL && (property = ecitygml_AbstractSpaceBoundaryPropertyIterator_next(boundaries)) != NULL) {
        const AbstractSpaceBoundaryKind *boundary = ecitygml_AbstractSpaceBoundaryProperty_object(property);
        if (boundary == NULL) {
            continue;
        }
        AbstractFeatureKindRef *feature = ecitygml_AbstractFeatureKindRef_from_space_boundary(boundary);
        const WallSurface *wall = ecitygml_WallSurface_try_from(feature);
        const RoofSurface *roof = ecitygml_RoofSurface_try_from(feature);
        const GroundSurface *ground = ecitygml_GroundSurface_try_from(feature);
        if (wall) {
            error = add_surface(walls, highest_lod(ecitygml_WallSurface_lod3_multi_surface(wall),
                                                   ecitygml_WallSurface_lod2_multi_surface(wall),
                                                   ecitygml_WallSurface_lod1_multi_surface(wall),
                                                   ecitygml_WallSurface_lod0_multi_surface(wall)));
            if (error == NULL) {
                error = add_filling_surfaces(fillings, ecitygml_WallSurface_filling_surfaces(wall));
            }
        } else if (roof) {
            error = add_surface(roofs, highest_lod(ecitygml_RoofSurface_lod3_multi_surface(roof),
                                                   ecitygml_RoofSurface_lod2_multi_surface(roof),
                                                   ecitygml_RoofSurface_lod1_multi_surface(roof),
                                                   ecitygml_RoofSurface_lod0_multi_surface(roof)));
            if (error == NULL) {
                error = add_filling_surfaces(fillings, ecitygml_RoofSurface_filling_surfaces(roof));
            }
        } else if (ground) {
            error = add_surface(grounds, highest_lod(ecitygml_GroundSurface_lod3_multi_surface(ground),
                                                     ecitygml_GroundSurface_lod2_multi_surface(ground),
                                                     ecitygml_GroundSurface_lod1_multi_surface(ground),
                                                     ecitygml_GroundSurface_lod0_multi_surface(ground)));
            if (error == NULL) {
                error = add_filling_surfaces(fillings, ecitygml_GroundSurface_filling_surfaces(ground));
            }
        }
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(boundaries);
    return error;
}

static void print_boundaries(const Building *building) {
    Measurement measurements[4] = {{0}};
    Error *error = measure_boundaries(building, measurements);
    if (error) {  // e.g. a surface that can't be triangulated
        printf("  Boundaries: ");
        print_not_computable(error);
        return;
    }
    const char *labels[] = {"WallSurface", "RoofSurface", "GroundSurface"};
    for (size_t index = 0; index < 3; ++index) {
        printf("  %s: %zu, area %.3f m^2, %zu triangles\n", labels[index], measurements[index].count,
               measurements[index].area, measurements[index].triangles);
    }
    printf("  Doors and windows: %zu, area %.3f m^2\n", measurements[3].count, measurements[3].area);
}

static void print_solids(const Building *building) {
    const SolidProperty *properties[] = {ecitygml_Building_lod1_solid(building), ecitygml_Building_lod2_solid(building),
                                         ecitygml_Building_lod3_solid(building)};
    for (size_t index = 0; index < 3; ++index) {
        const Solid *solid = properties[index] ? ecitygml_SolidProperty_object(properties[index]) : NULL;
        if (solid == NULL) {
            continue;
        }
        size_t members = 0;
        size_t references = 0;
        const Shell *shell = ecitygml_Solid_exterior(solid);
        if (shell) {
            AbstractSurfacePropertyIterator *iterator = ecitygml_Shell_members(shell);
            const AbstractSurfaceProperty *member;
            while ((member = ecitygml_AbstractSurfacePropertyIterator_next(iterator)) != NULL) {
                ++members;
                if (ecitygml_AbstractSurfaceProperty_object(member) == NULL) {
                    ++references;
                }
            }
            ecitygml_AbstractSurfacePropertyIterator_destroy(iterator);
        }
        printf("  LoD%zu solid: %zu surfaces, %zu of them xlink:href references\n", index + 1, members, references);
        printf("    Volume: ");
        ecitygml_Solid_volume_3d_result volume = ecitygml_Solid_volume_3d(solid);
        if (volume.is_ok) {
            printf("%.3f m^3\n", volume.ok);
        } else {
            print_not_computable(volume.err);
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: 05_measure_geometry path/to/model.gml\n");
        return 2;
    }
    ecitygml_GmlReader_from_path_result reader = ecitygml_GmlReader_from_path((DiplomatStringView){argv[1], strlen(argv[1])});
    if (!reader.is_ok) {
        return print_error(reader.err);
    }
    ecitygml_GmlReader_finish_result result = ecitygml_GmlReader_finish(reader.ok);
    ecitygml_GmlReader_destroy(reader.ok);
    if (!result.is_ok) {
        return print_error(result.err);
    }
    CityModel *city_model = result.ok;

    size_t buildings = 0;
    AbstractFeatureKindRefIterator *features = ecitygml_CityModel_iter_features(city_model);
    AbstractFeatureKindRef *feature;
    while ((feature = ecitygml_AbstractFeatureKindRefIterator_next(features)) != NULL) {
        const Building *building = ecitygml_Building_try_from(feature);
        if (building) {
            if (buildings++ > 0) {
                printf("\n");
            }
            DiplomatStringView id = ecitygml_Id_as_str(ecitygml_Building_feature_id(building));
            printf("Building %.*s\n", (int)id.len, id.data);
            print_boundaries(building);
            print_solids(building);
        }
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractFeatureKindRefIterator_destroy(features);
    if (buildings == 0) {
        printf("No buildings.\n");
    }

    ecitygml_CityModel_destroy(city_model);
    return 0;
}
