// The cases of crates/ecitygml/tests/conformance/asam-opendrive.md.
#include "conformance/conformance.h"

#include "AbstractCityObjectKindRef.h"
#include "AbstractCityObjectKindRefIterator.h"
#include "AbstractCurveProperty.h"
#include "AbstractCurvePropertyIterator.h"
#include "AbstractSpaceBoundaryKind.h"
#include "AbstractSpaceBoundaryProperty.h"
#include "AbstractSpaceBoundaryPropertyIterator.h"
#include "AbstractSurfacePropertyIterator.h"
#include "AuxiliaryTrafficArea.h"
#include "AuxiliaryTrafficAreaFunctionValueIterator.h"
#include "AuxiliaryTrafficAreaUsageValueIterator.h"
#include "AuxiliaryTrafficSpace.h"
#include "AuxiliaryTrafficSpaceFunctionValueIterator.h"
#include "AuxiliaryTrafficSpaceProperty.h"
#include "AuxiliaryTrafficSpacePropertyIterator.h"
#include "AuxiliaryTrafficSpaceUsageValueIterator.h"
#include "BoundingShape.h"
#include "DirectPosition.h"
#include "DirectPositionIterator.h"
#include "DoubleAttribute.h"
#include "Envelope.h"
#include "FeatureType.h"
#include "GenericAttributeKind.h"
#include "GenericAttributeKindIterator.h"
#include "GranularityValue.h"
#include "HRef.h"
#include "HolePropertyIterator.h"
#include "Id.h"
#include "IntAttribute.h"
#include "Intersection.h"
#include "IntersectionProperty.h"
#include "IntersectionPropertyIterator.h"
#include "LineString.h"
#include "Marking.h"
#include "MarkingProperty.h"
#include "MarkingPropertyIterator.h"
#include "MultiCurve.h"
#include "MultiCurveProperty.h"
#include "MultiSurface.h"
#include "MultiSurfaceProperty.h"
#include "OccupancyIterator.h"
#include "Reference.h"
#include "Road.h"
#include "RoadFunctionValueIterator.h"
#include "RoadUsageValueIterator.h"
#include "Section.h"
#include "SectionProperty.h"
#include "SectionPropertyIterator.h"
#include "Solid.h"
#include "SolidProperty.h"
#include "SpaceType.h"
#include "StringAttribute.h"
#include "TrafficArea.h"
#include "TrafficAreaFunctionValue.h"
#include "TrafficAreaFunctionValueIterator.h"
#include "TrafficAreaUsageValue.h"
#include "TrafficAreaUsageValueIterator.h"
#include "TrafficDirectionValue.h"
#include "TrafficSpace.h"
#include "TrafficSpaceFunctionValue.h"
#include "TrafficSpaceFunctionValueIterator.h"
#include "TrafficSpaceProperty.h"
#include "TrafficSpacePropertyIterator.h"
#include "TrafficSpaceReference.h"
#include "TrafficSpaceReferenceIterator.h"
#include "TrafficSpaceUsageValue.h"
#include "TrafficSpaceUsageValueIterator.h"

#define ROAD_SHAPE FIXTURE("asam-opendrive/ASAM-UC_RoadShape.gml")
#define JUNCTION FIXTURE("asam-opendrive/ASAM-Ex_Bidirectional_Junction.gml")

/// The most features a fixture of this file has.
#define MAX_FEATURES 32

static const char *SPACES[] = {
    "UUID_ae81947d-a661-3678-a5ee-eed58b68694f", "UUID_6e4de408-1e54-3869-b7ce-1be3f2261421",
    "UUID_9582b02f-5cc7-38f8-b79c-a3a18b31856c", "UUID_c772e261-27f1-30b6-8a94-1ccf23e71a74",
    "UUID_656f23c9-92b6-3c98-a1bf-40b5f2625b13", "UUID_86f8df09-c972-332b-a279-636373ce4e0c",
    "UUID_144a6807-5844-32b2-bb34-8b2671b1afaa",
};

void setUp(void) {}
void tearDown(void) {}

/// Takes the iterator, counts its (borrowed) items and destroys it: `count_<Iterator>(iterator)`.
#define DEFINE_COUNT(Iterator)                                   \
    static size_t count_##Iterator(Iterator *iterator) {         \
        size_t count = 0;                                        \
        while (ecitygml_##Iterator##_next(iterator) != NULL) {   \
            count++;                                             \
        }                                                        \
        ecitygml_##Iterator##_destroy(iterator);                 \
        return count;                                            \
    }

DEFINE_COUNT(AbstractSurfacePropertyIterator)
DEFINE_COUNT(AuxiliaryTrafficAreaFunctionValueIterator)
DEFINE_COUNT(AuxiliaryTrafficAreaUsageValueIterator)
DEFINE_COUNT(AuxiliaryTrafficSpaceFunctionValueIterator)
DEFINE_COUNT(AuxiliaryTrafficSpacePropertyIterator)
DEFINE_COUNT(AuxiliaryTrafficSpaceUsageValueIterator)
DEFINE_COUNT(DirectPositionIterator)
DEFINE_COUNT(HolePropertyIterator)
DEFINE_COUNT(IntersectionPropertyIterator)
DEFINE_COUNT(MarkingPropertyIterator)
DEFINE_COUNT(OccupancyIterator)
DEFINE_COUNT(RoadFunctionValueIterator)
DEFINE_COUNT(RoadUsageValueIterator)
DEFINE_COUNT(TrafficSpacePropertyIterator)
DEFINE_COUNT(TrafficSpaceReferenceIterator)

/// Takes the iterator of properties, writes their objects into `out` (failing on a reference-only property),
/// destroys it and returns their number: `objects_<Property>(iterator, out)`.
#define DEFINE_OBJECTS(Property, Object)                                                  \
    static size_t objects_##Property(Property##Iterator *iterator, const Object **out) { \
        size_t len = 0;                                                                   \
        const Property *property;                                                         \
        while ((property = ecitygml_##Property##Iterator_next(iterator)) != NULL) {       \
            TEST_ASSERT_LESS_THAN_size_t(MAX_FEATURES, len);                              \
            TEST_ASSERT_NULL(ecitygml_##Property##_href(property));                       \
            out[len] = ecitygml_##Property##_object(property);                            \
            TEST_ASSERT_NOT_NULL(out[len]);                                               \
            len++;                                                                        \
        }                                                                                 \
        ecitygml_##Property##Iterator_destroy(iterator);                                  \
        return len;                                                                       \
    }

DEFINE_OBJECTS(AbstractCurveProperty, AbstractCurveKind)
DEFINE_OBJECTS(AbstractSpaceBoundaryProperty, AbstractSpaceBoundaryKind)
DEFINE_OBJECTS(AuxiliaryTrafficSpaceProperty, AuxiliaryTrafficSpace)
DEFINE_OBJECTS(IntersectionProperty, Intersection)
DEFINE_OBJECTS(MarkingProperty, Marking)
DEFINE_OBJECTS(SectionProperty, Section)
DEFINE_OBJECTS(TrafficSpaceProperty, TrafficSpace)

/// Takes the iterator of code list values and asserts it has exactly one, `expected`.
#define ASSERT_SINGLE_VALUE(Value, iterator_expression, expected)                       \
    do {                                                                                \
        Value##Iterator *iterator_ = (iterator_expression);                             \
        const Value *value_ = ecitygml_##Value##Iterator_next(iterator_);               \
        TEST_ASSERT_NOT_NULL(value_);                                                   \
        ASSERT_STR((expected), ecitygml_##Value##_value(value_));                       \
        TEST_ASSERT_NULL(ecitygml_##Value##Iterator_next(iterator_));                   \
        ecitygml_##Value##Iterator_destroy(iterator_);                                  \
    } while (0)

static void assert_point_close(double x, double y, double z, const DirectPosition *position) {
    ASSERT_CLOSE(x, ecitygml_DirectPosition_x(position));
    ASSERT_CLOSE(y, ecitygml_DirectPosition_y(position));
    ASSERT_CLOSE(z, ecitygml_DirectPosition_z(position));
}

static void assert_envelope(const CityModel *city_model, const double lower[3], const double upper[3]) {
    const Envelope *envelope = ecitygml_BoundingShape_envelope(ecitygml_CityModel_bounded_by(city_model));
    TEST_ASSERT_NOT_NULL(envelope);
    assert_point_close(lower[0], lower[1], lower[2], ecitygml_Envelope_lower_corner(envelope));
    assert_point_close(upper[0], upper[1], upper[2], ecitygml_Envelope_upper_corner(envelope));
}

/// All features of the city model, into `out`; returns their number. Destroy them with `destroy_features`.
static size_t all_features(const CityModel *city_model, AbstractFeatureKindRef **out) {
    size_t len = 0;
    AbstractFeatureKindRefIterator *iterator = ecitygml_CityModel_iter_features(city_model);
    AbstractFeatureKindRef *feature;
    while ((feature = ecitygml_AbstractFeatureKindRefIterator_next(iterator)) != NULL) {
        TEST_ASSERT_LESS_THAN_size_t(MAX_FEATURES, len);
        out[len++] = feature;
    }
    ecitygml_AbstractFeatureKindRefIterator_destroy(iterator);
    return len;
}

/// The city model's road; it borrows from the model.
static const Road *road(const CityModel *city_model) {
    const Road *road = NULL;
    AbstractFeatureKindRef *features[MAX_FEATURES];
    size_t len = all_features(city_model, features);
    for (size_t i = 0; road == NULL && i < len; i++) {
        road = ecitygml_Road_try_from(features[i]);
    }
    destroy_features(features, len);
    TEST_ASSERT_NOT_NULL(road);
    return road;
}

/// The traffic spaces of the city model (`iter_features` + `try_from`), into `out`; returns their number.
static size_t all_traffic_spaces(const CityModel *city_model, const TrafficSpace **out) {
    AbstractFeatureKindRef *features[MAX_FEATURES];
    size_t len = all_features(city_model, features);
    size_t spaces = 0;
    for (size_t i = 0; i < len; i++) {
        const TrafficSpace *space = ecitygml_TrafficSpace_try_from(features[i]);
        if (space != NULL) out[spaces++] = space;
    }
    destroy_features(features, len);
    return spaces;
}

/// The single boundary of a space, inline, as a feature; takes the iterator. Destroy the feature.
static AbstractFeatureKindRef *only_boundary(AbstractSpaceBoundaryPropertyIterator *boundaries) {
    const AbstractSpaceBoundaryKind *all[MAX_FEATURES];
    TEST_ASSERT_EQUAL_size_t(1, objects_AbstractSpaceBoundaryProperty(boundaries, all));
    return ecitygml_AbstractFeatureKindRef_from_space_boundary(all[0]);
}

/// The single curve member of an inline multi curve, as a line string: its point count, and its length into
/// `length`.
static size_t line_string(const MultiCurve *multi_curve, double *length) {
    TEST_ASSERT_NOT_NULL(multi_curve);
    const AbstractCurveKind *members[MAX_FEATURES];
    TEST_ASSERT_EQUAL_size_t(1, objects_AbstractCurveProperty(ecitygml_MultiCurve_curve_member(multi_curve), members));
    const LineString *curve = ecitygml_LineString_try_from(members[0]);
    TEST_ASSERT_NOT_NULL(curve);
    *length = ecitygml_LineString_length_3d(curve);
    return count_DirectPositionIterator(ecitygml_LineString_points(curve));
}

/// Asserts the local ids of the references; takes the iterator.
static void assert_local_ids(TrafficSpaceReferenceIterator *references, const char *const *expected, size_t len) {
    size_t i = 0;
    const TrafficSpaceReference *reference;
    while ((reference = ecitygml_TrafficSpaceReferenceIterator_next(references)) != NULL) {
        TEST_ASSERT_LESS_THAN_size_t(len, i);
        Reference *owned = ecitygml_Reference_from_traffic_space_reference(reference);
        const HRef *href = ecitygml_Reference_href(owned);
        TEST_ASSERT_NOT_NULL(href);
        ecitygml_HRef_local_id_result local_id = ecitygml_HRef_local_id(href);
        TEST_ASSERT_TRUE(local_id.is_ok);
        ASSERT_STR(expected[i], local_id.ok);
        ecitygml_Reference_destroy(owned);
        i++;
    }
    ecitygml_TrafficSpaceReferenceIterator_destroy(references);
    TEST_ASSERT_EQUAL_size_t(len, i);
}

static double lod2_area_of(const MultiSurfaceProperty *property) {
    TEST_ASSERT_NOT_NULL(property);
    ecitygml_MultiSurface_area_3d_result area = ecitygml_MultiSurface_area_3d(ecitygml_MultiSurfaceProperty_object(property));
    TEST_ASSERT_TRUE(area.is_ok);
    return area.ok;
}

static double volume_of(const SolidProperty *property) {
    TEST_ASSERT_NOT_NULL(property);
    ecitygml_Solid_volume_3d_result volume = ecitygml_Solid_volume_3d(ecitygml_SolidProperty_object(property));
    TEST_ASSERT_TRUE(volume.is_ok);
    return volume.ok;
}

static double length_of(const MultiCurveProperty *property) {
    TEST_ASSERT_NOT_NULL(property);
    ecitygml_MultiCurve_length_3d_result length = ecitygml_MultiCurve_length_3d(ecitygml_MultiCurveProperty_object(property));
    TEST_ASSERT_TRUE(length.is_ok);
    return length.ok;
}

// ASAM-UC_RoadShape.gml

/// The road's single section; it borrows from the model.
static const Section *road_shape_section(const CityModel *city_model) {
    const Section *sections[MAX_FEATURES];
    TEST_ASSERT_EQUAL_size_t(1, objects_SectionProperty(ecitygml_Road_sections(road(city_model)), sections));
    return sections[0];
}

static size_t road_shape_spaces(const CityModel *city_model, const TrafficSpace **out) {
    return objects_TrafficSpaceProperty(ecitygml_Section_traffic_spaces(road_shape_section(city_model)), out);
}

static void test_road_shape_city_model(void) {
    CityModel *city_model = read(ROAD_SHAPE);
    TEST_ASSERT_EQUAL_size_t(1, ecitygml_CityModel_city_objects_len(city_model));
    const FeatureType types[] = {
        FeatureType_CityModel,   FeatureType_Road,          FeatureType_Section,
        FeatureType_TrafficSpace, FeatureType_TrafficArea,  FeatureType_TrafficSpace,
        FeatureType_TrafficArea, FeatureType_AuxiliaryTrafficSpace, FeatureType_AuxiliaryTrafficArea,
        FeatureType_AuxiliaryTrafficSpace, FeatureType_AuxiliaryTrafficArea,
    };
    AbstractFeatureKindRef *features[MAX_FEATURES];
    size_t len = all_features(city_model, features);
    TEST_ASSERT_EQUAL_size_t(11, len);
    for (size_t i = 0; i < len; i++) {
        TEST_ASSERT_EQUAL_INT(types[i], ecitygml_AbstractFeatureKindRef_feature_type(features[i]));
    }
    destroy_features(features, len);
    size_t objects = 0;
    AbstractCityObjectKindRefIterator *iterator = ecitygml_CityModel_iter_city_objects(city_model);
    AbstractCityObjectKindRef *object;
    while ((object = ecitygml_AbstractCityObjectKindRefIterator_next(iterator)) != NULL) {
        TEST_ASSERT_LESS_THAN_size_t(10, objects);
        TEST_ASSERT_EQUAL_INT(types[++objects], ecitygml_AbstractCityObjectKindRef_feature_type(object));
        ecitygml_AbstractCityObjectKindRef_destroy(object);
    }
    ecitygml_AbstractCityObjectKindRefIterator_destroy(iterator);
    TEST_ASSERT_EQUAL_size_t(10, objects);
    const double lower[] = {-50.21567184593757, -2.4442507170297514, 0.0};
    const double upper[] = {-13.007511850967884, 29.053746110395082, 4.95};
    assert_envelope(city_model, lower, upper);
    ecitygml_CityModel_destroy(city_model);
}

static void test_road_shape_road(void) {
    CityModel *city_model = read(ROAD_SHAPE);
    const Road *r = road(city_model);
    ASSERT_STR("UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f", ecitygml_Id_as_str(ecitygml_Road_feature_id(r)));
    TEST_ASSERT_NULL(ecitygml_Road_class(r));
    TEST_ASSERT_FALSE(ecitygml_Road_traffic_direction(r).is_ok);
    TEST_ASSERT_EQUAL_size_t(0, count_RoadFunctionValueIterator(ecitygml_Road_functions(r)));
    TEST_ASSERT_EQUAL_size_t(0, count_RoadUsageValueIterator(ecitygml_Road_usages(r)));
    TEST_ASSERT_EQUAL_size_t(0, count_IntersectionPropertyIterator(ecitygml_Road_intersections(r)));
    TEST_ASSERT_EQUAL_size_t(0, count_OccupancyIterator(ecitygml_Road_occupancies(r)));
    TEST_ASSERT_EQUAL_size_t(0, count_TrafficSpacePropertyIterator(ecitygml_Road_traffic_spaces(r)));
    TEST_ASSERT_EQUAL_size_t(0, count_AuxiliaryTrafficSpacePropertyIterator(ecitygml_Road_auxiliary_traffic_spaces(r)));
    TEST_ASSERT_EQUAL_size_t(0, count_MarkingPropertyIterator(ecitygml_Road_markings(r)));
    TEST_ASSERT_EQUAL_size_t(0, count_HolePropertyIterator(ecitygml_Road_holes(r)));
    ASSERT_STR("UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29",
               ecitygml_Id_as_str(ecitygml_Section_feature_id(road_shape_section(city_model))));
    ecitygml_CityModel_destroy(city_model);
}

static void test_road_shape_section(void) {
    CityModel *city_model = read(ROAD_SHAPE);
    const Section *section = road_shape_section(city_model);
    TEST_ASSERT_NULL(ecitygml_Section_class(section));
    TEST_ASSERT_FALSE(ecitygml_Section_traffic_direction(section).is_ok);
    TEST_ASSERT_NULL(ecitygml_Section_lod0_multi_curve(section));
    TEST_ASSERT_NULL(ecitygml_Section_lod1_solid(section));
    TEST_ASSERT_EQUAL_size_t(0, count_MarkingPropertyIterator(ecitygml_Section_markings(section)));
    TEST_ASSERT_EQUAL_size_t(0, count_HolePropertyIterator(ecitygml_Section_holes(section)));
    const TrafficSpace *spaces[MAX_FEATURES];
    TEST_ASSERT_EQUAL_size_t(2, objects_TrafficSpaceProperty(ecitygml_Section_traffic_spaces(section), spaces));
    ASSERT_STR("UUID_ae81947d-a661-3678-a5ee-eed58b68694f", ecitygml_Id_as_str(ecitygml_TrafficSpace_feature_id(spaces[0])));
    ASSERT_STR("UUID_6e4de408-1e54-3869-b7ce-1be3f2261421", ecitygml_Id_as_str(ecitygml_TrafficSpace_feature_id(spaces[1])));
    const AuxiliaryTrafficSpace *auxiliary[MAX_FEATURES];
    TEST_ASSERT_EQUAL_size_t(
        2, objects_AuxiliaryTrafficSpaceProperty(ecitygml_Section_auxiliary_traffic_spaces(section), auxiliary));
    ASSERT_STR("UUID_12298df9-4982-33a8-ab4a-9953410bbff7",
               ecitygml_Id_as_str(ecitygml_AuxiliaryTrafficSpace_feature_id(auxiliary[0])));
    ASSERT_STR("UUID_f8211bb5-0ce8-36e1-9b84-73d30114f578",
               ecitygml_Id_as_str(ecitygml_AuxiliaryTrafficSpace_feature_id(auxiliary[1])));
    ecitygml_CityModel_destroy(city_model);
}

static void test_road_shape_traffic_spaces(void) {
    CityModel *city_model = read(ROAD_SHAPE);
    const TrafficSpace *spaces[MAX_FEATURES];
    TEST_ASSERT_EQUAL_size_t(2, road_shape_spaces(city_model, spaces));
    const TrafficDirectionValue directions[] = {TrafficDirectionValue_Backwards, TrafficDirectionValue_Forwards};
    for (size_t i = 0; i < 2; i++) {
        const TrafficSpace *space = spaces[i];
        ecitygml_TrafficSpace_traffic_direction_result direction = ecitygml_TrafficSpace_traffic_direction(space);
        TEST_ASSERT_TRUE(direction.is_ok);
        TEST_ASSERT_EQUAL_INT(directions[i], direction.ok);
        TEST_ASSERT_EQUAL_INT(GranularityValue_Lane, ecitygml_TrafficSpace_granularity(space));
        TEST_ASSERT_NULL(ecitygml_TrafficSpace_class(space));
        ASSERT_SINGLE_VALUE(TrafficSpaceFunctionValue, ecitygml_TrafficSpace_functions(space), "1");
        ASSERT_SINGLE_VALUE(TrafficSpaceUsageValue, ecitygml_TrafficSpace_usages(space), "2");
        TEST_ASSERT_EQUAL_size_t(0, count_OccupancyIterator(ecitygml_TrafficSpace_occupancies(space)));
        ecitygml_TrafficSpace_space_type_result space_type = ecitygml_TrafficSpace_space_type(space);
        TEST_ASSERT_TRUE(space_type.is_ok);
        TEST_ASSERT_EQUAL_INT(SpaceType_Open, space_type.ok);
        TEST_ASSERT_FALSE(ecitygml_TrafficSpace_relative_to_terrain(space).is_ok);
        TEST_ASSERT_NULL(ecitygml_TrafficSpace_creation_date(space));
        TEST_ASSERT_EQUAL_size_t(0, count_TrafficSpaceReferenceIterator(ecitygml_TrafficSpace_predecessors(space)));
        TEST_ASSERT_EQUAL_size_t(0, count_TrafficSpaceReferenceIterator(ecitygml_TrafficSpace_successors(space)));
        AbstractFeatureKindRef *boundary = only_boundary(ecitygml_TrafficSpace_boundaries(space));
        TEST_ASSERT_NOT_NULL(ecitygml_TrafficArea_try_from(boundary));
        ecitygml_AbstractFeatureKindRef_destroy(boundary);
    }
    ecitygml_CityModel_destroy(city_model);
}

static void test_road_shape_generic_attributes(void) {
    CityModel *city_model = read(ROAD_SHAPE);
    const TrafficSpace *spaces[MAX_FEATURES];
    road_shape_spaces(city_model, spaces);
    const char *names[] = {
        "identifier_laneId",   "identifier_laneSectionId", "identifier_roadId",
        "opendrive_road_length", "opendrive_road_rule",    "opendrive_laneSection_curvePositionStart",
        "opendrive_lane_type", "opendrive_lane_level",
    };
    // 'i' int, 'd' double, 's' string, with the value in the matching field.
    const char kinds[] = {'i', 'i', 's', 'd', 's', 'd', 's', 's'};
    const int64_t ints[] = {1, 0, 0, 0, 0, 0, 0, 0};
    const double doubles[] = {0, 0, 0, 40.0, 0, 0.0, 0, 0};
    const char *strings[] = {NULL, NULL, "1", NULL, "RIGHT_HAND_TRAFFIC", NULL, "DRIVING", "false"};
    size_t i = 0;
    GenericAttributeKindIterator *attributes = ecitygml_TrafficSpace_generic_attributes(spaces[0]);
    const GenericAttributeKind *attribute;
    while ((attribute = ecitygml_GenericAttributeKindIterator_next(attributes)) != NULL) {
        TEST_ASSERT_LESS_THAN_size_t(8, i);
        ASSERT_STR(names[i], ecitygml_GenericAttributeKind_name(attribute));
        const IntAttribute *integer = ecitygml_GenericAttributeKind_as_int(attribute);
        const DoubleAttribute *number = ecitygml_GenericAttributeKind_as_double(attribute);
        const StringAttribute *text = ecitygml_GenericAttributeKind_as_string(attribute);
        TEST_ASSERT_EQUAL(kinds[i] == 'i', integer != NULL);
        TEST_ASSERT_EQUAL(kinds[i] == 'd', number != NULL);
        TEST_ASSERT_EQUAL(kinds[i] == 's', text != NULL);
        if (integer != NULL) TEST_ASSERT_EQUAL_INT64(ints[i], ecitygml_IntAttribute_value(integer));
        if (number != NULL) ASSERT_CLOSE(doubles[i], ecitygml_DoubleAttribute_value(number));
        if (text != NULL) ASSERT_STR(strings[i], ecitygml_StringAttribute_value(text));
        i++;
    }
    ecitygml_GenericAttributeKindIterator_destroy(attributes);
    TEST_ASSERT_EQUAL_size_t(8, i);
    ecitygml_CityModel_destroy(city_model);
}

static void test_road_shape_traffic_space_geometry(void) {
    CityModel *city_model = read(ROAD_SHAPE);
    const TrafficSpace *spaces[MAX_FEATURES];
    TEST_ASSERT_EQUAL_size_t(2, road_shape_spaces(city_model, spaces));
    const double volumes[] = {720.0, 540.0};
    for (size_t i = 0; i < 2; i++) {
        const TrafficSpace *space = spaces[i];
        ASSERT_CLOSE(volumes[i], volume_of(ecitygml_TrafficSpace_lod2_solid(space)));
        const MultiCurveProperty *property = ecitygml_TrafficSpace_lod2_multi_curve(space);
        TEST_ASSERT_NOT_NULL(property);
        TEST_ASSERT_NULL(ecitygml_MultiCurveProperty_href(property));
        ASSERT_CLOSE(40.0, length_of(property));
        double length;
        TEST_ASSERT_EQUAL_size_t(2, line_string(ecitygml_MultiCurveProperty_object(property), &length));
        ASSERT_CLOSE(40.0, length);
        TEST_ASSERT_NULL(ecitygml_TrafficSpace_lod0_multi_curve(space));
        TEST_ASSERT_NULL(ecitygml_TrafficSpace_lod3_multi_curve(space));
        TEST_ASSERT_NULL(ecitygml_TrafficSpace_lod1_solid(space));
        TEST_ASSERT_NULL(ecitygml_TrafficSpace_lod3_solid(space));
        TEST_ASSERT_NULL(ecitygml_TrafficSpace_lod2_multi_surface(space));
    }
    ecitygml_CityModel_destroy(city_model);
}

static void test_road_shape_traffic_areas(void) {
    CityModel *city_model = read(ROAD_SHAPE);
    const TrafficSpace *spaces[MAX_FEATURES];
    TEST_ASSERT_EQUAL_size_t(2, road_shape_spaces(city_model, spaces));
    const char *ids[] = {"UUID_8625bf6f-57cb-3ddf-8fd1-6674b756a2e2", "UUID_dc110e80-dadc-3c87-b864-2854cc0cb39a"};
    const double areas[] = {160.79800993793438, 121.34249049694012};
    for (size_t i = 0; i < 2; i++) {
        AbstractFeatureKindRef *boundary = only_boundary(ecitygml_TrafficSpace_boundaries(spaces[i]));
        const TrafficArea *area = ecitygml_TrafficArea_try_from(boundary);
        TEST_ASSERT_NOT_NULL(area);
        ASSERT_STR(ids[i], ecitygml_Id_as_str(ecitygml_TrafficArea_feature_id(area)));
        ASSERT_STR("Lane", first_name(ecitygml_TrafficArea_names(area)));
        TEST_ASSERT_NULL(ecitygml_TrafficArea_class(area));
        ASSERT_SINGLE_VALUE(TrafficAreaFunctionValue, ecitygml_TrafficArea_functions(area), "1");
        ASSERT_SINGLE_VALUE(TrafficAreaUsageValue, ecitygml_TrafficArea_usages(area), "2");
        TEST_ASSERT_NULL(ecitygml_TrafficArea_surface_material(area));
        TEST_ASSERT_NULL(ecitygml_TrafficArea_lod0_multi_curve(area));
        TEST_ASSERT_NULL(ecitygml_TrafficArea_lod0_multi_surface(area));
        TEST_ASSERT_NULL(ecitygml_TrafficArea_lod1_multi_surface(area));
        TEST_ASSERT_NULL(ecitygml_TrafficArea_lod3_multi_surface(area));
        TEST_ASSERT_FALSE(ecitygml_TrafficArea_relative_to_terrain(area).is_ok);
        const MultiSurfaceProperty *property = ecitygml_TrafficArea_lod2_multi_surface(area);
        TEST_ASSERT_EQUAL_size_t(1, count_AbstractSurfacePropertyIterator(ecitygml_MultiSurface_surface_member(
                                        ecitygml_MultiSurfaceProperty_object(property))));
        ASSERT_CLOSE(areas[i], lod2_area_of(property));
        ecitygml_AbstractFeatureKindRef_destroy(boundary);
    }
    ecitygml_CityModel_destroy(city_model);
}

static void test_road_shape_auxiliary_traffic(void) {
    CityModel *city_model = read(ROAD_SHAPE);
    const AuxiliaryTrafficSpace *spaces[MAX_FEATURES];
    TEST_ASSERT_EQUAL_size_t(2, objects_AuxiliaryTrafficSpaceProperty(
                                    ecitygml_Section_auxiliary_traffic_spaces(road_shape_section(city_model)), spaces));
    const char *ids[] = {"UUID_4890681a-e9fa-365e-a676-f89afb453f9b", "UUID_d3c71d48-5222-355e-8037-9677aee30d7e"};
    for (size_t i = 0; i < 2; i++) {
        const AuxiliaryTrafficSpace *space = spaces[i];
        TEST_ASSERT_EQUAL_INT(GranularityValue_Lane, ecitygml_AuxiliaryTrafficSpace_granularity(space));
        TEST_ASSERT_NULL(ecitygml_AuxiliaryTrafficSpace_class(space));
        TEST_ASSERT_EQUAL_size_t(
            0, count_AuxiliaryTrafficSpaceFunctionValueIterator(ecitygml_AuxiliaryTrafficSpace_functions(space)));
        TEST_ASSERT_EQUAL_size_t(
            0, count_AuxiliaryTrafficSpaceUsageValueIterator(ecitygml_AuxiliaryTrafficSpace_usages(space)));
        ecitygml_AuxiliaryTrafficSpace_space_type_result space_type = ecitygml_AuxiliaryTrafficSpace_space_type(space);
        TEST_ASSERT_TRUE(space_type.is_ok);
        TEST_ASSERT_EQUAL_INT(SpaceType_Open, space_type.ok);
        ASSERT_CLOSE(100.0, volume_of(ecitygml_AuxiliaryTrafficSpace_lod2_solid(space)));
        ASSERT_CLOSE(40.0, length_of(ecitygml_AuxiliaryTrafficSpace_lod2_multi_curve(space)));

        AbstractFeatureKindRef *boundary = only_boundary(ecitygml_AuxiliaryTrafficSpace_boundaries(space));
        const AuxiliaryTrafficArea *area = ecitygml_AuxiliaryTrafficArea_try_from(boundary);
        TEST_ASSERT_NOT_NULL(area);
        ASSERT_STR(ids[i], ecitygml_Id_as_str(ecitygml_AuxiliaryTrafficArea_feature_id(area)));
        ASSERT_STR("Lane", first_name(ecitygml_AuxiliaryTrafficArea_names(area)));
        TEST_ASSERT_NULL(ecitygml_AuxiliaryTrafficArea_class(area));
        TEST_ASSERT_EQUAL_size_t(
            0, count_AuxiliaryTrafficAreaFunctionValueIterator(ecitygml_AuxiliaryTrafficArea_functions(area)));
        TEST_ASSERT_EQUAL_size_t(0,
                                 count_AuxiliaryTrafficAreaUsageValueIterator(ecitygml_AuxiliaryTrafficArea_usages(area)));
        TEST_ASSERT_NULL(ecitygml_AuxiliaryTrafficArea_surface_material(area));
        ASSERT_CLOSE(40.0, lod2_area_of(ecitygml_AuxiliaryTrafficArea_lod2_multi_surface(area)));
        ecitygml_AbstractFeatureKindRef_destroy(boundary);
    }
    ecitygml_CityModel_destroy(city_model);
}

// ASAM-Ex_Bidirectional_Junction.gml

static void test_junction_city_model(void) {
    CityModel *city_model = read(JUNCTION);
    TEST_ASSERT_EQUAL_size_t(1, ecitygml_CityModel_city_objects_len(city_model));
    const FeatureType types[] = {
        FeatureType_CityModel,    FeatureType_Road,         FeatureType_Section,      FeatureType_TrafficSpace,
        FeatureType_TrafficArea,  FeatureType_TrafficSpace, FeatureType_TrafficArea,  FeatureType_Marking,
        FeatureType_Marking,      FeatureType_Marking,      FeatureType_Marking,      FeatureType_Section,
        FeatureType_TrafficSpace, FeatureType_TrafficArea,  FeatureType_Section,      FeatureType_TrafficSpace,
        FeatureType_TrafficArea,  FeatureType_Intersection, FeatureType_TrafficSpace, FeatureType_TrafficArea,
        FeatureType_TrafficSpace, FeatureType_TrafficArea,  FeatureType_TrafficSpace, FeatureType_TrafficArea,
    };
    AbstractFeatureKindRef *features[MAX_FEATURES];
    size_t len = all_features(city_model, features);
    TEST_ASSERT_EQUAL_size_t(24, len);
    for (size_t i = 0; i < len; i++) {
        TEST_ASSERT_EQUAL_INT(types[i], ecitygml_AbstractFeatureKindRef_feature_type(features[i]));
    }
    destroy_features(features, len);
    size_t objects = 0;
    AbstractCityObjectKindRefIterator *iterator = ecitygml_CityModel_iter_city_objects(city_model);
    AbstractCityObjectKindRef *object;
    while ((object = ecitygml_AbstractCityObjectKindRefIterator_next(iterator)) != NULL) {
        objects++;
        ecitygml_AbstractCityObjectKindRef_destroy(object);
    }
    ecitygml_AbstractCityObjectKindRefIterator_destroy(iterator);
    TEST_ASSERT_EQUAL_size_t(23, objects);
    const double lower[] = {-52.66282419815818, -37.4146115571896, 0.0};
    const double upper[] = {34.10760429351533, 6.338805461729647, 0.0};
    assert_envelope(city_model, lower, upper);
    ecitygml_CityModel_destroy(city_model);
}

static void test_junction_road(void) {
    CityModel *city_model = read(JUNCTION);
    const Road *r = road(city_model);
    ASSERT_STR("UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f", ecitygml_Id_as_str(ecitygml_Road_feature_id(r)));
    const Section *sections[MAX_FEATURES];
    TEST_ASSERT_EQUAL_size_t(3, objects_SectionProperty(ecitygml_Road_sections(r), sections));
    const char *ids[] = {"UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29", "UUID_ef20f165-2564-373a-a5f8-98fd15f1ae69",
                         "UUID_4799566b-daf4-3135-aa9d-ec1b34a9167d"};
    const size_t spaces[] = {2, 1, 1};
    const size_t markings[] = {4, 0, 0};
    for (size_t i = 0; i < 3; i++) {
        ASSERT_STR(ids[i], ecitygml_Id_as_str(ecitygml_Section_feature_id(sections[i])));
        TEST_ASSERT_EQUAL_size_t(spaces[i], count_TrafficSpacePropertyIterator(ecitygml_Section_traffic_spaces(sections[i])));
        TEST_ASSERT_EQUAL_size_t(markings[i], count_MarkingPropertyIterator(ecitygml_Section_markings(sections[i])));
        TEST_ASSERT_EQUAL_size_t(
            0, count_AuxiliaryTrafficSpacePropertyIterator(ecitygml_Section_auxiliary_traffic_spaces(sections[i])));
    }
    const Intersection *intersections[MAX_FEATURES];
    TEST_ASSERT_EQUAL_size_t(1, objects_IntersectionProperty(ecitygml_Road_intersections(r), intersections));
    ASSERT_STR("UUID_47b7678d-e8b1-36ca-90b6-5b86cc859571",
               ecitygml_Id_as_str(ecitygml_Intersection_feature_id(intersections[0])));
    TEST_ASSERT_NULL(ecitygml_Intersection_class(intersections[0]));
    const TrafficSpace *intersection_spaces[MAX_FEATURES];
    TEST_ASSERT_EQUAL_size_t(3, objects_TrafficSpaceProperty(ecitygml_Intersection_traffic_spaces(intersections[0]),
                                                             intersection_spaces));
    for (size_t i = 0; i < 3; i++) {
        ASSERT_STR(SPACES[4 + i], ecitygml_Id_as_str(ecitygml_TrafficSpace_feature_id(intersection_spaces[i])));
    }
    ecitygml_CityModel_destroy(city_model);
}

static void test_junction_traffic_spaces(void) {
    CityModel *city_model = read(JUNCTION);
    const TrafficSpace *spaces[MAX_FEATURES];
    TEST_ASSERT_EQUAL_size_t(7, all_traffic_spaces(city_model, spaces));
    const size_t points[] = {9, 9, 5, 6, 7, 8, 7};
    const double lengths[] = {36.74683751297985,  36.74683751297985,  20.0, 21.746217945006258,
                              26.761532846607814, 30.210435770102656, 30.0};
    for (size_t i = 0; i < 7; i++) {
        ASSERT_STR(SPACES[i], ecitygml_Id_as_str(ecitygml_TrafficSpace_feature_id(spaces[i])));
        ecitygml_TrafficSpace_traffic_direction_result direction = ecitygml_TrafficSpace_traffic_direction(spaces[i]);
        TEST_ASSERT_TRUE(direction.is_ok);
        TEST_ASSERT_EQUAL_INT(i == 0 ? TrafficDirectionValue_Backwards : TrafficDirectionValue_Forwards, direction.ok);
        TEST_ASSERT_NULL(ecitygml_TrafficSpace_lod2_solid(spaces[i]));
        double length;
        const MultiCurveProperty *property = ecitygml_TrafficSpace_lod2_multi_curve(spaces[i]);
        TEST_ASSERT_NOT_NULL(property);
        TEST_ASSERT_EQUAL_size_t(points[i], line_string(ecitygml_MultiCurveProperty_object(property), &length));
        ASSERT_CLOSE(lengths[i], length);
    }
    ecitygml_CityModel_destroy(city_model);
}

static void test_junction_traffic_areas(void) {
    CityModel *city_model = read(JUNCTION);
    const size_t members[] = {8, 8, 4, 5, 6, 7, 6};
    const double areas[] = {112.81279116484816, 112.81279116484816, 61.4, 66.76088909116919,
                            81.22157625123039,  92.69041581703632,  92.1};
    AbstractFeatureKindRef *features[MAX_FEATURES];
    size_t len = all_features(city_model, features);
    size_t n = 0;
    for (size_t i = 0; i < len; i++) {
        const TrafficArea *area = ecitygml_TrafficArea_try_from(features[i]);
        if (area == NULL) continue;
        TEST_ASSERT_LESS_THAN_size_t(7, n);
        const MultiSurfaceProperty *property = ecitygml_TrafficArea_lod2_multi_surface(area);
        TEST_ASSERT_NOT_NULL(property);
        TEST_ASSERT_EQUAL_size_t(members[n], count_AbstractSurfacePropertyIterator(ecitygml_MultiSurface_surface_member(
                                                 ecitygml_MultiSurfaceProperty_object(property))));
        ASSERT_CLOSE(areas[n], lod2_area_of(property));
        n++;
    }
    destroy_features(features, len);
    TEST_ASSERT_EQUAL_size_t(7, n);
    ecitygml_CityModel_destroy(city_model);
}

static void test_junction_traffic_space_links(void) {
    CityModel *city_model = read(JUNCTION);
    const TrafficSpace *spaces[MAX_FEATURES];
    TEST_ASSERT_EQUAL_size_t(7, all_traffic_spaces(city_model, spaces));
    const char *const unknown[] = {"UUID_d7d4aa5a-88c9-328d-9151-a6c043e57d7f"};
    const char *const *predecessors[] = {NULL,          NULL, (const char *const[]){SPACES[4], SPACES[5]},
                                         NULL,          (const char *const[]){SPACES[3]}, unknown,
                                         (const char *const[]){SPACES[1]}};
    const size_t predecessor_counts[] = {0, 0, 2, 0, 1, 1, 1};
    const char *const *successors[] = {NULL,
                                       (const char *const[]){SPACES[6]},
                                       NULL,
                                       (const char *const[]){SPACES[4]},
                                       (const char *const[]){SPACES[2]},
                                       (const char *const[]){SPACES[0]},
                                       (const char *const[]){SPACES[2]}};
    const size_t successor_counts[] = {0, 1, 0, 1, 1, 1, 1};
    for (size_t i = 0; i < 7; i++) {
        assert_local_ids(ecitygml_TrafficSpace_predecessors(spaces[i]), predecessors[i], predecessor_counts[i]);
        assert_local_ids(ecitygml_TrafficSpace_successors(spaces[i]), successors[i], successor_counts[i]);
    }
    ecitygml_CityModel_destroy(city_model);
}

static void test_junction_markings(void) {
    CityModel *city_model = read(JUNCTION);
    const Section *sections[MAX_FEATURES];
    objects_SectionProperty(ecitygml_Road_sections(road(city_model)), sections);
    const Marking *markings[MAX_FEATURES];
    TEST_ASSERT_EQUAL_size_t(4, objects_MarkingProperty(ecitygml_Section_markings(sections[0]), markings));
    const double areas[] = {0.48, 0.48, 0.48, 0.08962050155758661};
    for (size_t i = 0; i < 4; i++) {
        const Marking *marking = markings[i];
        ASSERT_STR("RoadMarking", first_name(ecitygml_Marking_names(marking)));
        TEST_ASSERT_NULL(ecitygml_Marking_class(marking));
        TEST_ASSERT_NULL(ecitygml_Marking_lod0_multi_surface(marking));
        TEST_ASSERT_NULL(ecitygml_Marking_lod3_multi_surface(marking));
        const MultiSurfaceProperty *property = ecitygml_Marking_lod2_multi_surface(marking);
        TEST_ASSERT_NOT_NULL(property);
        TEST_ASSERT_EQUAL_size_t(1, count_AbstractSurfacePropertyIterator(ecitygml_MultiSurface_surface_member(
                                        ecitygml_MultiSurfaceProperty_object(property))));
        ASSERT_CLOSE(areas[i], lod2_area_of(property));
    }
    ecitygml_CityModel_destroy(city_model);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_road_shape_city_model);
    RUN_TEST(test_road_shape_road);
    RUN_TEST(test_road_shape_section);
    RUN_TEST(test_road_shape_traffic_spaces);
    RUN_TEST(test_road_shape_generic_attributes);
    RUN_TEST(test_road_shape_traffic_space_geometry);
    RUN_TEST(test_road_shape_traffic_areas);
    RUN_TEST(test_road_shape_auxiliary_traffic);
    RUN_TEST(test_junction_city_model);
    RUN_TEST(test_junction_road);
    RUN_TEST(test_junction_traffic_spaces);
    RUN_TEST(test_junction_traffic_areas);
    RUN_TEST(test_junction_traffic_space_links);
    RUN_TEST(test_junction_markings);
    return UNITY_END();
}
