// Walks the road network of a CityGML file and measures it: centre-line lengths, traffic-area
// areas and the volumes of the traffic spaces.
//
// CityGML's transportation model is a hierarchy: a road consists of sections and intersections, which
// (like the road itself) hold traffic spaces and auxiliary traffic spaces (e.g. lanes and sidewalks).
// Each space is bounded by traffic areas or auxiliary traffic areas, its ground surfaces. The spaces
// are reached through properties (`..._object`), the areas through the space's `..._boundaries`,
// converted with `try_from`. Geometry calculations (`length_3d`, `area_3d`, `volume_3d`) can fail,
// e.g. for degenerate geometry, and return a `..._result` struct.
//
// Built by bindings/c/CMakeLists.txt (`mise run build:bindings:c`), which also runs it as a test.
//
// Usage: 04_road_network path/to/model.gml
//
// Output for ASAM-UC_RoadShape.gml (shortened):
//
//     Road UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f
//       Section UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29
//         TrafficSpace UUID_ae81947d-a661-3678-a5ee-eed58b686946
//           Centre line (LoD2): 40.000 m
//           Volume (LoD2 solid): 720.000 m^3
//           TrafficArea UUID_8625bf6f-57cb-3ddf-8fd1-6674b756a2e2: 160.798 m^2
//         ...
//
//     Total volume of traffic spaces (LoD2): 1260.000 m^3

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "AbstractFeatureKindRef.h"
#include "AbstractFeatureKindRefIterator.h"
#include "AbstractSpaceBoundaryKind.h"
#include "AbstractSpaceBoundaryProperty.h"
#include "AbstractSpaceBoundaryPropertyIterator.h"
#include "AuxiliaryTrafficArea.h"
#include "AuxiliaryTrafficSpace.h"
#include "AuxiliaryTrafficSpaceProperty.h"
#include "AuxiliaryTrafficSpacePropertyIterator.h"
#include "CityModel.h"
#include "Error.h"
#include "GmlReader.h"
#include "Id.h"
#include "Intersection.h"
#include "IntersectionProperty.h"
#include "IntersectionPropertyIterator.h"
#include "MultiCurve.h"
#include "MultiCurveProperty.h"
#include "MultiSurface.h"
#include "MultiSurfaceProperty.h"
#include "Road.h"
#include "Section.h"
#include "SectionProperty.h"
#include "SectionPropertyIterator.h"
#include "Solid.h"
#include "SolidProperty.h"
#include "TrafficArea.h"
#include "TrafficSpace.h"
#include "TrafficSpaceProperty.h"
#include "TrafficSpacePropertyIterator.h"

// Counts and sums over all spaces of one kind (traffic or auxiliary traffic spaces).
typedef struct {
    size_t spaces;
    double length;
    double volume;
    size_t areas;
    double area;
} Totals;

// The outcome of a geometry calculation; the `..._result` structs of the bindings differ in type
// only, so each calculation below converts its result into this.
typedef struct {
    bool has_geometry;
    bool is_ok;
    double value;
    Error *error;
} Measurement;

static int print_error(Error *error) {
    DiplomatWrite *message = diplomat_buffer_write_create(64);
    ecitygml_Error_message(error, message);
    fprintf(stderr, "error: %.*s\n", (int)diplomat_buffer_write_len(message), diplomat_buffer_write_get_bytes(message));
    diplomat_buffer_write_destroy(message);
    ecitygml_Error_destroy(error);
    return 1;
}

static void print_id(const Id *id) {
    DiplomatStringView text = ecitygml_Id_as_str(id);
    printf("%.*s", (int)text.len, text.data);
}

static Measurement length_of(const MultiCurveProperty *property) {
    const MultiCurve *curve = property ? ecitygml_MultiCurveProperty_object(property) : NULL;
    if (curve == NULL) {
        return (Measurement){0};
    }
    ecitygml_MultiCurve_length_3d_result result = ecitygml_MultiCurve_length_3d(curve);
    return (Measurement){true, result.is_ok, result.is_ok ? result.ok : 0.0, result.is_ok ? NULL : result.err};
}

static Measurement volume_of(const SolidProperty *property) {
    const Solid *solid = property ? ecitygml_SolidProperty_object(property) : NULL;
    if (solid == NULL) {
        return (Measurement){0};
    }
    ecitygml_Solid_volume_3d_result result = ecitygml_Solid_volume_3d(solid);
    return (Measurement){true, result.is_ok, result.is_ok ? result.ok : 0.0, result.is_ok ? NULL : result.err};
}

static Measurement area_of(const MultiSurfaceProperty *property) {
    const MultiSurface *surface = property ? ecitygml_MultiSurfaceProperty_object(property) : NULL;
    if (surface == NULL) {
        return (Measurement){0};
    }
    ecitygml_MultiSurface_area_3d_result result = ecitygml_MultiSurface_area_3d(surface);
    return (Measurement){true, result.is_ok, result.is_ok ? result.ok : 0.0, result.is_ok ? NULL : result.err};
}

// Prints a measurement (e.g. "40.000 m") and adds it to `sum`; "-" without geometry, and a note if
// the calculation failed (freeing the error).
static void print_measurement(Measurement measurement, const char *unit, double *sum) {
    if (!measurement.has_geometry) {
        printf("-\n");
    } else if (measurement.is_ok) {
        printf("%.3f %s\n", measurement.value, unit);
        *sum += measurement.value;
    } else {
        DiplomatWrite *message = diplomat_buffer_write_create(64);
        ecitygml_Error_message(measurement.error, message);
        printf("not computable (%.*s)\n", (int)diplomat_buffer_write_len(message), diplomat_buffer_write_get_bytes(message));
        diplomat_buffer_write_destroy(message);
        ecitygml_Error_destroy(measurement.error);
    }
}

static void print_traffic_space(const TrafficSpace *space, Totals *totals, const char *indent) {
    printf("%sTrafficSpace ", indent);
    print_id(ecitygml_TrafficSpace_feature_id(space));
    printf("\n%s  Centre line (LoD2): ", indent);
    print_measurement(length_of(ecitygml_TrafficSpace_lod2_multi_curve(space)), "m", &totals->length);
    printf("%s  Volume (LoD2 solid): ", indent);
    print_measurement(volume_of(ecitygml_TrafficSpace_lod2_solid(space)), "m^3", &totals->volume);
    ++totals->spaces;

    // The areas are the space's boundaries of the matching type.
    AbstractSpaceBoundaryPropertyIterator *boundaries = ecitygml_TrafficSpace_boundaries(space);
    const AbstractSpaceBoundaryProperty *property;
    while ((property = ecitygml_AbstractSpaceBoundaryPropertyIterator_next(boundaries)) != NULL) {
        const AbstractSpaceBoundaryKind *boundary = ecitygml_AbstractSpaceBoundaryProperty_object(property);
        if (boundary == NULL) {
            continue;
        }
        AbstractFeatureKindRef *feature = ecitygml_AbstractFeatureKindRef_from_space_boundary(boundary);
        const TrafficArea *area = ecitygml_TrafficArea_try_from(feature);
        if (area) {
            printf("%s  TrafficArea ", indent);
            print_id(ecitygml_TrafficArea_feature_id(area));
            printf(": ");
            print_measurement(area_of(ecitygml_TrafficArea_lod2_multi_surface(area)), "m^2", &totals->area);
            ++totals->areas;
        }
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(boundaries);
}

// The same for auxiliary traffic spaces, which have the same getters but are a separate C type.
static void print_auxiliary_traffic_space(const AuxiliaryTrafficSpace *space, Totals *totals, const char *indent) {
    printf("%sAuxiliaryTrafficSpace ", indent);
    print_id(ecitygml_AuxiliaryTrafficSpace_feature_id(space));
    printf("\n%s  Centre line (LoD2): ", indent);
    print_measurement(length_of(ecitygml_AuxiliaryTrafficSpace_lod2_multi_curve(space)), "m", &totals->length);
    printf("%s  Volume (LoD2 solid): ", indent);
    print_measurement(volume_of(ecitygml_AuxiliaryTrafficSpace_lod2_solid(space)), "m^3", &totals->volume);
    ++totals->spaces;

    AbstractSpaceBoundaryPropertyIterator *boundaries = ecitygml_AuxiliaryTrafficSpace_boundaries(space);
    const AbstractSpaceBoundaryProperty *property;
    while ((property = ecitygml_AbstractSpaceBoundaryPropertyIterator_next(boundaries)) != NULL) {
        const AbstractSpaceBoundaryKind *boundary = ecitygml_AbstractSpaceBoundaryProperty_object(property);
        if (boundary == NULL) {
            continue;
        }
        AbstractFeatureKindRef *feature = ecitygml_AbstractFeatureKindRef_from_space_boundary(boundary);
        const AuxiliaryTrafficArea *area = ecitygml_AuxiliaryTrafficArea_try_from(feature);
        if (area) {
            printf("%s  AuxiliaryTrafficArea ", indent);
            print_id(ecitygml_AuxiliaryTrafficArea_feature_id(area));
            printf(": ");
            print_measurement(area_of(ecitygml_AuxiliaryTrafficArea_lod2_multi_surface(area)), "m^2", &totals->area);
            ++totals->areas;
        }
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(boundaries);
}

// The traffic and auxiliary traffic spaces of a road, section or intersection; destroys the iterators.
static void print_spaces(TrafficSpacePropertyIterator *spaces, AuxiliaryTrafficSpacePropertyIterator *auxiliary_spaces,
                         Totals *traffic, Totals *auxiliary, const char *indent) {
    const TrafficSpaceProperty *property;
    while ((property = ecitygml_TrafficSpacePropertyIterator_next(spaces)) != NULL) {
        const TrafficSpace *space = ecitygml_TrafficSpaceProperty_object(property);
        if (space) {
            print_traffic_space(space, traffic, indent);
        }
    }
    ecitygml_TrafficSpacePropertyIterator_destroy(spaces);
    const AuxiliaryTrafficSpaceProperty *auxiliary_property;
    while ((auxiliary_property = ecitygml_AuxiliaryTrafficSpacePropertyIterator_next(auxiliary_spaces)) != NULL) {
        const AuxiliaryTrafficSpace *space = ecitygml_AuxiliaryTrafficSpaceProperty_object(auxiliary_property);
        if (space) {
            print_auxiliary_traffic_space(space, auxiliary, indent);
        }
    }
    ecitygml_AuxiliaryTrafficSpacePropertyIterator_destroy(auxiliary_spaces);
}

static void print_road(const Road *road, Totals *traffic, Totals *auxiliary) {
    printf("Road ");
    print_id(ecitygml_Road_feature_id(road));
    printf("\n");
    // A road can hold spaces directly, too.
    print_spaces(ecitygml_Road_traffic_spaces(road), ecitygml_Road_auxiliary_traffic_spaces(road), traffic, auxiliary,
                 "  ");

    SectionPropertyIterator *sections = ecitygml_Road_sections(road);
    const SectionProperty *section_property;
    while ((section_property = ecitygml_SectionPropertyIterator_next(sections)) != NULL) {
        const Section *section = ecitygml_SectionProperty_object(section_property);
        if (section) {
            printf("  Section ");
            print_id(ecitygml_Section_feature_id(section));
            printf("\n");
            print_spaces(ecitygml_Section_traffic_spaces(section), ecitygml_Section_auxiliary_traffic_spaces(section),
                         traffic, auxiliary, "    ");
        }
    }
    ecitygml_SectionPropertyIterator_destroy(sections);

    IntersectionPropertyIterator *intersections = ecitygml_Road_intersections(road);
    const IntersectionProperty *intersection_property;
    while ((intersection_property = ecitygml_IntersectionPropertyIterator_next(intersections)) != NULL) {
        const Intersection *intersection = ecitygml_IntersectionProperty_object(intersection_property);
        if (intersection) {
            printf("  Intersection ");
            print_id(ecitygml_Intersection_feature_id(intersection));
            printf("\n");
            print_spaces(ecitygml_Intersection_traffic_spaces(intersection),
                         ecitygml_Intersection_auxiliary_traffic_spaces(intersection), traffic, auxiliary, "    ");
        }
    }
    ecitygml_IntersectionPropertyIterator_destroy(intersections);
}

static void print_totals(const char *label, const Totals *totals) {
    printf("%s: %zu, centre lines %.3f m, %zu areas %.3f m^2, volume %.3f m^3\n", label, totals->spaces, totals->length,
           totals->areas, totals->area, totals->volume);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: 04_road_network path/to/model.gml\n");
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

    Totals traffic = {0};
    Totals auxiliary = {0};
    size_t roads = 0;
    AbstractFeatureKindRefIterator *features = ecitygml_CityModel_iter_features(city_model);
    AbstractFeatureKindRef *feature;
    while ((feature = ecitygml_AbstractFeatureKindRefIterator_next(features)) != NULL) {
        const Road *road = ecitygml_Road_try_from(feature);
        if (road) {
            ++roads;
            print_road(road, &traffic, &auxiliary);
        }
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractFeatureKindRefIterator_destroy(features);

    printf("\nRoads: %zu\n", roads);
    print_totals("Traffic spaces", &traffic);
    print_totals("Auxiliary traffic spaces", &auxiliary);
    printf("Total volume of traffic spaces (LoD2): %.3f m^3\n", traffic.volume);

    ecitygml_CityModel_destroy(city_model);
    return 0;
}
