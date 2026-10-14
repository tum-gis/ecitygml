// Exports the building geometry of a CityGML file to a Wavefront OBJ file.
//
// Shows how to get triangles out of CityGML geometry for your own file format or renderer:
// `triangulate` turns a multi surface or solid into a `Triangulation`, whose `surface` is a
// triangulated surface; each `Triangle` has its corners `a`, `b` and `c`. Every wall, roof and ground
// surface, door and window becomes a named OBJ group, using its highest level of detail; buildings
// without such surfaces fall back to their highest LoD solid.
//
// Built by bindings/c/CMakeLists.txt (`mise run build:bindings:c`), which also runs it as a test.
//
// Usage: 06_export_obj input.gml output.obj
//
// Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml:
//
//     Wrote 48 vertices, 16 triangles, 7 groups

#include <stdbool.h>
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
#include "Building.h"
#include "CityModel.h"
#include "DirectPosition.h"
#include "Error.h"
#include "FeatureType.h"
#include "GmlReader.h"
#include "GroundSurface.h"
#include "Id.h"
#include "MultiSurface.h"
#include "MultiSurfaceProperty.h"
#include "RoofSurface.h"
#include "Solid.h"
#include "SolidProperty.h"
#include "Triangle.h"
#include "TriangleIterator.h"
#include "TriangulatedSurface.h"
#include "Triangulation.h"
#include "WallSurface.h"

// Writes OBJ groups as they come: `g` starts a group, `v` adds a vertex, `f` a triangle of the last
// three vertices (OBJ indices are 1-based and count all vertices written so far).
typedef struct {
    FILE *file;
    size_t vertices;
    size_t triangles;
    size_t groups;
} ObjWriter;

static int print_error(Error *error) {
    DiplomatWrite *message = diplomat_buffer_write_create(64);
    ecitygml_Error_message(error, message);
    fprintf(stderr, "error: %.*s\n", (int)diplomat_buffer_write_len(message), diplomat_buffer_write_get_bytes(message));
    diplomat_buffer_write_destroy(message);
    ecitygml_Error_destroy(error);
    return 1;
}

// Writes the triangles of a triangulation as a group named `<prefix>_<type>_<id>` and frees it.
static void write_group(ObjWriter *obj, DiplomatStringView prefix, const char *type, DiplomatStringView id,
                        Triangulation *triangulation) {
    fprintf(obj->file, "g %.*s_%s", (int)prefix.len, prefix.data, type);
    if (id.len > 0) {
        fprintf(obj->file, "_%.*s", (int)id.len, id.data);
    }
    fprintf(obj->file, "\n");
    ++obj->groups;
    TriangleIterator *triangles = ecitygml_TriangulatedSurface_triangles(ecitygml_Triangulation_surface(triangulation));
    const Triangle *triangle;
    while ((triangle = ecitygml_TriangleIterator_next(triangles)) != NULL) {
        const DirectPosition *corners[] = {ecitygml_Triangle_a(triangle), ecitygml_Triangle_b(triangle),
                                           ecitygml_Triangle_c(triangle)};
        for (size_t index = 0; index < 3; ++index) {
            fprintf(obj->file, "v %.6f %.6f %.6f\n", ecitygml_DirectPosition_x(corners[index]),
                    ecitygml_DirectPosition_y(corners[index]), ecitygml_DirectPosition_z(corners[index]));
        }
        fprintf(obj->file, "f %zu %zu %zu\n", obj->vertices + 1, obj->vertices + 2, obj->vertices + 3);
        obj->vertices += 3;
        ++obj->triangles;
    }
    ecitygml_TriangleIterator_destroy(triangles);
    ecitygml_Triangulation_destroy(triangulation);
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

// Triangulates and writes a surface's multi surface (if any); returns the error if it fails, else NULL.
static Error *write_surface(ObjWriter *obj, DiplomatStringView prefix, const char *type, const Id *id,
                            const MultiSurface *multi_surface) {
    if (multi_surface == NULL) {
        return NULL;
    }
    ecitygml_MultiSurface_triangulate_result triangulation = ecitygml_MultiSurface_triangulate(multi_surface);
    if (!triangulation.is_ok) {
        return triangulation.err;
    }
    write_group(obj, prefix, type, ecitygml_Id_as_str(id), triangulation.ok);
    return NULL;
}

// Writes the doors and windows of a wall, roof or ground surface (`feature_type` names their type);
// destroys the iterator.
static Error *write_filling_surfaces(ObjWriter *obj, DiplomatStringView prefix, AbstractFillingSurfacePropertyIterator *iterator) {
    Error *error = NULL;
    const AbstractFillingSurfaceProperty *property;
    while (error == NULL && (property = ecitygml_AbstractFillingSurfacePropertyIterator_next(iterator)) != NULL) {
        const AbstractFillingSurfaceKind *filling = ecitygml_AbstractFillingSurfaceProperty_object(property);
        if (filling == NULL) {
            continue;
        }
        DiplomatWrite *type = diplomat_buffer_write_create(32);
        ecitygml_FeatureType_to_string(ecitygml_AbstractFillingSurfaceKind_feature_type(filling), type);
        char type_name[64];
        snprintf(type_name, sizeof type_name, "%.*s", (int)diplomat_buffer_write_len(type), diplomat_buffer_write_get_bytes(type));
        diplomat_buffer_write_destroy(type);
        error = write_surface(obj, prefix, type_name, ecitygml_AbstractFillingSurfaceKind_feature_id(filling),
                              highest_lod(ecitygml_AbstractFillingSurfaceKind_lod3_multi_surface(filling),
                                          ecitygml_AbstractFillingSurfaceKind_lod2_multi_surface(filling),
                                          ecitygml_AbstractFillingSurfaceKind_lod1_multi_surface(filling),
                                          ecitygml_AbstractFillingSurfaceKind_lod0_multi_surface(filling)));
    }
    ecitygml_AbstractFillingSurfacePropertyIterator_destroy(iterator);
    return error;
}

// Writes the boundary surfaces of a building (sets `*has_surfaces` if it has any); returns the first error.
static Error *write_boundaries(ObjWriter *obj, const Building *building, DiplomatStringView prefix, bool *has_surfaces) {
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
            *has_surfaces = true;
            error = write_surface(obj, prefix, "WallSurface", ecitygml_WallSurface_feature_id(wall),
                                  highest_lod(ecitygml_WallSurface_lod3_multi_surface(wall),
                                              ecitygml_WallSurface_lod2_multi_surface(wall),
                                              ecitygml_WallSurface_lod1_multi_surface(wall),
                                              ecitygml_WallSurface_lod0_multi_surface(wall)));
            if (error == NULL) {
                error = write_filling_surfaces(obj, prefix, ecitygml_WallSurface_filling_surfaces(wall));
            }
        } else if (roof) {
            *has_surfaces = true;
            error = write_surface(obj, prefix, "RoofSurface", ecitygml_RoofSurface_feature_id(roof),
                                  highest_lod(ecitygml_RoofSurface_lod3_multi_surface(roof),
                                              ecitygml_RoofSurface_lod2_multi_surface(roof),
                                              ecitygml_RoofSurface_lod1_multi_surface(roof),
                                              ecitygml_RoofSurface_lod0_multi_surface(roof)));
            if (error == NULL) {
                error = write_filling_surfaces(obj, prefix, ecitygml_RoofSurface_filling_surfaces(roof));
            }
        } else if (ground) {
            *has_surfaces = true;
            error = write_surface(obj, prefix, "GroundSurface", ecitygml_GroundSurface_feature_id(ground),
                                  highest_lod(ecitygml_GroundSurface_lod3_multi_surface(ground),
                                              ecitygml_GroundSurface_lod2_multi_surface(ground),
                                              ecitygml_GroundSurface_lod1_multi_surface(ground),
                                              ecitygml_GroundSurface_lod0_multi_surface(ground)));
            if (error == NULL) {
                error = write_filling_surfaces(obj, prefix, ecitygml_GroundSurface_filling_surfaces(ground));
            }
        }
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(boundaries);
    return error;
}

// Writes a building's boundary surfaces, or else its highest LoD solid; returns the first error.
static Error *export_building(ObjWriter *obj, const Building *building) {
    DiplomatStringView prefix = ecitygml_Id_as_str(ecitygml_Building_feature_id(building));
    bool has_surfaces = false;
    Error *error = write_boundaries(obj, building, prefix, &has_surfaces);
    if (error || has_surfaces) {
        return error;
    }
    const SolidProperty *solids[] = {ecitygml_Building_lod3_solid(building), ecitygml_Building_lod2_solid(building),
                                     ecitygml_Building_lod1_solid(building)};
    const char *names[] = {"LoD3Solid", "LoD2Solid", "LoD1Solid"};
    for (size_t index = 0; index < 3; ++index) {
        const Solid *solid = solids[index] ? ecitygml_SolidProperty_object(solids[index]) : NULL;
        if (solid) {
            ecitygml_Solid_triangulate_result triangulation = ecitygml_Solid_triangulate(solid);
            if (!triangulation.is_ok) {
                return triangulation.err;
            }
            write_group(obj, prefix, names[index], (DiplomatStringView){"", 0}, triangulation.ok);
            return NULL;
        }
    }
    return NULL;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "usage: 06_export_obj input.gml output.obj\n");
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

    ObjWriter obj = {fopen(argv[2], "w"), 0, 0, 0};
    if (obj.file == NULL) {
        fprintf(stderr, "error: cannot create %s\n", argv[2]);
        ecitygml_CityModel_destroy(city_model);
        return 1;
    }
    Error *error = NULL;
    AbstractFeatureKindRefIterator *features = ecitygml_CityModel_iter_features(city_model);
    AbstractFeatureKindRef *feature;
    while (error == NULL && (feature = ecitygml_AbstractFeatureKindRefIterator_next(features)) != NULL) {
        const Building *building = ecitygml_Building_try_from(feature);
        if (building) {
            error = export_building(&obj, building);
        }
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractFeatureKindRefIterator_destroy(features);
    fclose(obj.file);
    ecitygml_CityModel_destroy(city_model);
    if (error) {
        return print_error(error);
    }
    printf("Wrote %zu vertices, %zu triangles, %zu groups\n", obj.vertices, obj.triangles, obj.groups);
    return 0;
}
