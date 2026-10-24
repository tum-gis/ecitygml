// The cases of crates/ecitygml/tests/conformance/ogc-citygml-3.0-encodings.md.
#include "conformance/conformance.h"

#include "AbstractBuildingSubdivisionKind.h"
#include "AbstractBuildingSubdivisionProperty.h"
#include "AbstractBuildingSubdivisionPropertyIterator.h"
#include "AbstractCityObjectKindRef.h"
#include "AbstractCityObjectKindRefIterator.h"
#include "AbstractReliefComponentKind.h"
#include "AbstractReliefComponentProperty.h"
#include "AbstractReliefComponentPropertyIterator.h"
#include "AbstractSpaceBoundaryKind.h"
#include "AbstractSurfaceProperty.h"
#include "AbstractSurfacePropertyIterator.h"
#include "AuxiliaryTrafficSpacePropertyIterator.h"
#include "BoundingShape.h"
#include "Bridge.h"
#include "BuildingFunctionValue.h"
#include "BuildingFunctionValueIterator.h"
#include "BuildingPart.h"
#include "BuildingPartProperty.h"
#include "BuildingPartPropertyIterator.h"
#include "BuildingSubdivisionClassValue.h"
#include "BuildingSubdivisionFunctionValue.h"
#include "BuildingSubdivisionFunctionValueIterator.h"
#include "BuildingSubdivisionUsageValueIterator.h"
#include "BuildingUnit.h"
#include "BuildingUsageValueIterator.h"
#include "CityObjectRelation.h"
#include "CityObjectRelationProperty.h"
#include "CityObjectRelationPropertyIterator.h"
#include "CitygmlFormat.h"
#include "Date.h"
#include "DateTime.h"
#include "DirectPosition.h"
#include "ElevationReferenceValue.h"
#include "Envelope.h"
#include "Error.h"
#include "FeatureType.h"
#include "GenericAttributeKindIterator.h"
#include "GmlReader.h"
#include "GmlWriter.h"
#include "GroundSurface.h"
#include "HRef.h"
#include "Height.h"
#include "HeightIterator.h"
#include "HeightStatusValue.h"
#include "Id.h"
#include "Length.h"
#include "LevelOfDetail.h"
#include "MultiSurface.h"
#include "MultiSurfaceProperty.h"
#include "Reference.h"
#include "RelationTypeValue.h"
#include "ReliefFeature.h"
#include "Road.h"
#include "RoofSurface.h"
#include "RoofTypeValue.h"
#include "Section.h"
#include "SectionProperty.h"
#include "SectionPropertyIterator.h"
#include "Storey.h"
#include "TinProperty.h"
#include "TinRelief.h"
#include "TrafficArea.h"
#include "TrafficSpace.h"
#include "TrafficSpaceProperty.h"
#include "TrafficSpacePropertyIterator.h"
#include "TriangleIterator.h"
#include "TriangulatedSurface.h"
#include "WallSurface.h"

#include <stdio.h>

#define GARAGE FIXTURE("ogc-citygml-3.0-encodings/Building_and_garage_LOD2-EPSG25832.gml")
#define UNITS FIXTURE("ogc-citygml-3.0-encodings/BuildingUnits_Storeys_xlink.gml")
#define ROAD_BRIDGE FIXTURE("ogc-citygml-3.0-encodings/Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml")
#define VERSIONING FIXTURE("ogc-citygml-3.0-encodings/historicalSuccession_CityGML_3.0_LOD2_Versioning.gml")

/// The most features a fixture of this dataset has.
#define MAX_FEATURES 64
/// The longest id or href of the dataset, plus the terminating zero.
#define MAX_STRING 96

#define WALL FeatureType_WallSurface
#define ROOF FeatureType_RoofSurface
#define GROUND FeatureType_GroundSurface

void setUp(void) {}
void tearDown(void) {}

static void assert_point_close(double x, double y, double z, const DirectPosition *position) {
    TEST_ASSERT_NOT_NULL(position);
    ASSERT_CLOSE(x, ecitygml_DirectPosition_x(position));
    ASSERT_CLOSE(y, ecitygml_DirectPosition_y(position));
    ASSERT_CLOSE(z, ecitygml_DirectPosition_z(position));
}

static void assert_envelope(const Envelope *envelope, const double lower[3], const double upper[3]) {
    TEST_ASSERT_NOT_NULL(envelope);
    assert_point_close(lower[0], lower[1], lower[2], ecitygml_Envelope_lower_corner(envelope));
    assert_point_close(upper[0], upper[1], upper[2], ecitygml_Envelope_upper_corner(envelope));
}

/// A borrowed string view, copied into `out`.
static void copy_view(DiplomatStringView view, char out[MAX_STRING]) {
    TEST_ASSERT_LESS_THAN_size_t(MAX_STRING, view.len);
    memcpy(out, view.data, view.len);
    out[view.len] = '\0';
}

/// An href as written, into `out`.
static void href_string(const HRef *href, char out[MAX_STRING]) {
    DiplomatWrite *write = diplomat_buffer_write_create(64);
    ecitygml_HRef_to_string(href, write);
    size_t len = diplomat_buffer_write_len(write);
    TEST_ASSERT_LESS_THAN_size_t(MAX_STRING, len);
    memcpy(out, diplomat_buffer_write_get_bytes(write), len);
    out[len] = '\0';
    diplomat_buffer_write_destroy(write);
}

/// The feature types of `iter_features`, into `out`; returns their number.
static size_t feature_types(const CityModel *city_model, FeatureType *out) {
    size_t len = 0;
    AbstractFeatureKindRefIterator *iterator = ecitygml_CityModel_iter_features(city_model);
    AbstractFeatureKindRef *feature;
    while ((feature = ecitygml_AbstractFeatureKindRefIterator_next(iterator)) != NULL) {
        TEST_ASSERT_LESS_THAN_size_t(MAX_FEATURES, len);
        out[len++] = ecitygml_AbstractFeatureKindRef_feature_type(feature);
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractFeatureKindRefIterator_destroy(iterator);
    return len;
}

/// Asserts the feature types of `iter_features`.
static void assert_feature_types(const CityModel *city_model, const FeatureType *expected, size_t expected_len) {
    FeatureType types[MAX_FEATURES];
    TEST_ASSERT_EQUAL_size_t(expected_len, feature_types(city_model, types));
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, types, expected_len);
}

/// Asserts that the city model and its round trip have the same `iter_features` feature types.
static void assert_same_feature_types(const CityModel *a, const CityModel *b) {
    FeatureType first[MAX_FEATURES];
    FeatureType second[MAX_FEATURES];
    size_t len = feature_types(a, first);
    TEST_ASSERT_EQUAL_size_t(len, feature_types(b, second));
    TEST_ASSERT_EQUAL_INT_ARRAY(first, second, len);
}

static size_t count_city_objects(const CityModel *city_model) {
    size_t count = 0;
    AbstractCityObjectKindRefIterator *iterator = ecitygml_CityModel_iter_city_objects(city_model);
    AbstractCityObjectKindRef *object;
    while ((object = ecitygml_AbstractCityObjectKindRefIterator_next(iterator)) != NULL) {
        count++;
        ecitygml_AbstractCityObjectKindRef_destroy(object);
    }
    ecitygml_AbstractCityObjectKindRefIterator_destroy(iterator);
    return count;
}

/// Declares `all_<T>`: the features `T::try_from` accepts, into `out` (borrowed from the model); returns their number.
#define DEFINE_ALL_OF(T)                                                                       \
    static size_t all_##T(const CityModel *city_model, const T **out, size_t max) {            \
        size_t len = 0;                                                                        \
        AbstractFeatureKindRefIterator *iterator = ecitygml_CityModel_iter_features(city_model); \
        AbstractFeatureKindRef *feature;                                                       \
        while ((feature = ecitygml_AbstractFeatureKindRefIterator_next(iterator)) != NULL) {   \
            const T *x = ecitygml_##T##_try_from(feature);                                     \
            if (x != NULL) {                                                                   \
                TEST_ASSERT_LESS_THAN_size_t(max, len);                                        \
                out[len++] = x;                                                                \
            }                                                                                  \
            ecitygml_AbstractFeatureKindRef_destroy(feature);                                  \
        }                                                                                      \
        ecitygml_AbstractFeatureKindRefIterator_destroy(iterator);                             \
        return len;                                                                            \
    }

DEFINE_ALL_OF(Building)
DEFINE_ALL_OF(BuildingPart)
DEFINE_ALL_OF(BuildingUnit)
DEFINE_ALL_OF(Storey)
DEFINE_ALL_OF(ReliefFeature)
DEFINE_ALL_OF(TinRelief)
DEFINE_ALL_OF(Bridge)
DEFINE_ALL_OF(Road)
DEFINE_ALL_OF(WallSurface)
DEFINE_ALL_OF(GroundSurface)

/// The model's only building.
static const Building *only_building(const CityModel *city_model) {
    const Building *buildings[2];
    TEST_ASSERT_EQUAL_size_t(1, all_Building(city_model, buildings, 2));
    return buildings[0];
}

/// Asserts an iterator of codes is empty and destroys it.
static void assert_no_names(CodeIterator *names) {
    TEST_ASSERT_NULL(ecitygml_CodeIterator_next(names));
    ecitygml_CodeIterator_destroy(names);
}

/// Asserts exactly one name and destroys the iterator.
static void assert_only_name(const char *expected, CodeIterator *names) {
    ASSERT_STR(expected, ecitygml_Code_value(ecitygml_CodeIterator_next(names)));
    TEST_ASSERT_NULL(ecitygml_CodeIterator_next(names));
    ecitygml_CodeIterator_destroy(names);
}

/// Asserts the one height and destroys the iterator.
static void assert_height(HeightIterator *heights, double length) {
    const Height *height = ecitygml_HeightIterator_next(heights);
    TEST_ASSERT_NOT_NULL(height);
    TEST_ASSERT_NULL(ecitygml_HeightIterator_next(heights));
    ASSERT_STR("highestRoofEdge", ecitygml_ElevationReferenceValue_value(ecitygml_Height_high_reference(height)));
    ASSERT_STR("lowestGroundPoint", ecitygml_ElevationReferenceValue_value(ecitygml_Height_low_reference(height)));
    TEST_ASSERT_EQUAL_INT(HeightStatusValue_Measured, ecitygml_Height_status(height));
    ASSERT_CLOSE(length, ecitygml_Length_value(ecitygml_Height_length(height)));
    ASSERT_STR("#m", ecitygml_Length_uom(ecitygml_Height_length(height)));
    ecitygml_HeightIterator_destroy(heights);
}

/// An expected boundary surface: type, `feature_id` (NULL: not checked), first name (NULL: not checked) and LoD2
/// area (unchecked if `has_area` is false).
typedef struct {
    FeatureType type;
    const char *id;
    const char *name;
    double area;
    bool has_area;
} ExpectedSurface;

/// Asserts a space's boundaries, all inline wall, roof or ground surfaces; destroys the iterator.
static void assert_surfaces(AbstractSpaceBoundaryPropertyIterator *properties, const ExpectedSurface *expected,
                            size_t expected_len) {
    const AbstractSpaceBoundaryProperty *property;
    size_t len = 0;
    while ((property = ecitygml_AbstractSpaceBoundaryPropertyIterator_next(properties)) != NULL) {
        TEST_ASSERT_LESS_THAN_size_t(expected_len, len);
        TEST_ASSERT_NULL(ecitygml_AbstractSpaceBoundaryProperty_href(property));
        const AbstractSpaceBoundaryKind *object = ecitygml_AbstractSpaceBoundaryProperty_object(property);
        TEST_ASSERT_NOT_NULL(object);
        if (expected[len].id != NULL) {
            ASSERT_STR(expected[len].id, ecitygml_Id_as_str(ecitygml_AbstractSpaceBoundaryKind_feature_id(object)));
        }
        AbstractFeatureKindRef *feature = ecitygml_AbstractFeatureKindRef_from_space_boundary(object);
        TEST_ASSERT_EQUAL_INT(expected[len].type, ecitygml_AbstractFeatureKindRef_feature_type(feature));
        const WallSurface *wall = ecitygml_WallSurface_try_from(feature);
        const RoofSurface *roof = ecitygml_RoofSurface_try_from(feature);
        const GroundSurface *ground = ecitygml_GroundSurface_try_from(feature);
        TEST_ASSERT_TRUE(wall != NULL || roof != NULL || ground != NULL);
        if (expected[len].name != NULL) {
            CodeIterator *names = wall != NULL   ? ecitygml_WallSurface_names(wall)
                                  : roof != NULL ? ecitygml_RoofSurface_names(roof)
                                                 : ecitygml_GroundSurface_names(ground);
            ASSERT_STR(expected[len].name, first_name(names));
        }
        if (expected[len].has_area) {
            const MultiSurfaceProperty *multi_surface = wall != NULL   ? ecitygml_WallSurface_lod2_multi_surface(wall)
                                                        : roof != NULL ? ecitygml_RoofSurface_lod2_multi_surface(roof)
                                                                       : ecitygml_GroundSurface_lod2_multi_surface(ground);
            TEST_ASSERT_NOT_NULL(multi_surface);
            ecitygml_MultiSurface_area_3d_result area =
                ecitygml_MultiSurface_area_3d(ecitygml_MultiSurfaceProperty_object(multi_surface));
            TEST_ASSERT_TRUE(area.is_ok);
            ASSERT_CLOSE(expected[len].area, area.ok);
        }
        ecitygml_AbstractFeatureKindRef_destroy(feature);
        len++;
    }
    ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(properties);
    TEST_ASSERT_EQUAL_size_t(expected_len, len);
}

static CityModel *round_trip(const CityModel *city_model) {
    GmlWriter *writer = ecitygml_GmlWriter_new(CitygmlFormat_Gml);
    TEST_ASSERT_TRUE(ecitygml_GmlWriter_finish(writer, city_model).is_ok);
    GmlReader *reader = ecitygml_GmlReader_new(ecitygml_GmlWriter_data(writer), CitygmlFormat_Gml);
    ecitygml_GmlReader_finish_result written = ecitygml_GmlReader_finish(reader);
    ecitygml_GmlReader_destroy(reader);
    ecitygml_GmlWriter_destroy(writer);
    TEST_ASSERT_TRUE(written.is_ok);
    return written.ok;
}

#define LEN(array) (sizeof(array) / sizeof((array)[0]))

// Building_and_garage_LOD2-EPSG25832.gml

static void test_garage_city_model(void) {
    CityModel *city_model = read(GARAGE);
    TEST_ASSERT_EQUAL_size_t(2, ecitygml_CityModel_city_objects_len(city_model));
    assert_envelope(ecitygml_BoundingShape_envelope(ecitygml_CityModel_bounded_by(city_model)),
                    (const double[]){458868.0, 5438343.0, 112.0}, (const double[]){458892.0, 5438362.0, 117.0});
    static const FeatureType expected[] = {
        FeatureType_CityModel, FeatureType_Building, GROUND, WALL, WALL, WALL, WALL, ROOF, ROOF,
        FeatureType_BuildingPart, WALL, WALL, WALL, WALL, GROUND, ROOF, FeatureType_ReliefFeature,
        FeatureType_TinRelief,
    };
    assert_feature_types(city_model, expected, LEN(expected));
    TEST_ASSERT_EQUAL_size_t(17, count_city_objects(city_model));
    ecitygml_CityModel_destroy(city_model);
}

static void test_garage_building(void) {
    CityModel *city_model = read(GARAGE);
    const Building *b = only_building(city_model);
    ASSERT_STR("GML_7b1a5a6f-ddad-4c3d-a507-3eb9ee0a8e68", ecitygml_Id_as_str(ecitygml_Building_feature_id(b)));
    assert_only_name("Example Building LOD2", ecitygml_Building_names(b));
    TEST_ASSERT_NULL(ecitygml_Building_class(b));
    BuildingFunctionValueIterator *functions = ecitygml_Building_functions(b);
    ASSERT_STR("1000", ecitygml_BuildingFunctionValue_value(ecitygml_BuildingFunctionValueIterator_next(functions)));
    TEST_ASSERT_NULL(ecitygml_BuildingFunctionValueIterator_next(functions));
    ecitygml_BuildingFunctionValueIterator_destroy(functions);
    BuildingUsageValueIterator *usages = ecitygml_Building_usages(b);
    TEST_ASSERT_NULL(ecitygml_BuildingUsageValueIterator_next(usages));
    ecitygml_BuildingUsageValueIterator_destroy(usages);
    ASSERT_STR("1030", ecitygml_RoofTypeValue_value(ecitygml_Building_roof_type(b)));
    ecitygml_Building_storeys_above_ground_result above = ecitygml_Building_storeys_above_ground(b);
    TEST_ASSERT_TRUE(above.is_ok);
    TEST_ASSERT_EQUAL_INT64(1, above.ok);
    TEST_ASSERT_FALSE(ecitygml_Building_storeys_below_ground(b).is_ok);
    const Date *built = ecitygml_Building_date_of_construction(b);
    TEST_ASSERT_NOT_NULL(built);
    TEST_ASSERT_EQUAL_INT32(1985, ecitygml_Date_year(built));
    TEST_ASSERT_EQUAL_UINT32(1, ecitygml_Date_month(built));
    TEST_ASSERT_EQUAL_UINT32(1, ecitygml_Date_day(built));
    assert_height(ecitygml_Building_heights(b), 6.0);
    static const ExpectedSurface expected[] = {
        {GROUND, NULL, "Ground Slab", 50.0, true},       {WALL, NULL, "Wall South", 30.0, true},
        {WALL, NULL, "Wall North", 30.0, true},          {WALL, NULL, "Wall East", 20.0, true},
        {WALL, NULL, "Wall West", 20.0, true},           {ROOF, NULL, "Roof North", 32.01562118716424, true},
        {ROOF, NULL, "Roof South", 32.01562118716424, true},
    };
    assert_surfaces(ecitygml_Building_boundaries(b), expected, LEN(expected));
    ecitygml_CityModel_destroy(city_model);
}

static void test_garage_building_part(void) {
    CityModel *city_model = read(GARAGE);
    BuildingPartPropertyIterator *parts = ecitygml_Building_building_parts(only_building(city_model));
    const BuildingPartProperty *property = ecitygml_BuildingPartPropertyIterator_next(parts);
    TEST_ASSERT_NOT_NULL(property);
    TEST_ASSERT_NULL(ecitygml_BuildingPartPropertyIterator_next(parts));
    ecitygml_BuildingPartPropertyIterator_destroy(parts);
    TEST_ASSERT_NULL(ecitygml_BuildingPartProperty_href(property));
    const BuildingPart *part = ecitygml_BuildingPartProperty_object(property);
    TEST_ASSERT_NOT_NULL(part);
    ASSERT_STR("GMLID_BUI379228_1244_301", ecitygml_Id_as_str(ecitygml_BuildingPart_feature_id(part)));
    assert_only_name("Example BuildingPart LOD2", ecitygml_BuildingPart_names(part));
    TEST_ASSERT_NULL(ecitygml_BuildingPart_class(part));
    BuildingFunctionValueIterator *functions = ecitygml_BuildingPart_functions(part);
    ASSERT_STR("1630", ecitygml_BuildingFunctionValue_value(ecitygml_BuildingFunctionValueIterator_next(functions)));
    TEST_ASSERT_NULL(ecitygml_BuildingFunctionValueIterator_next(functions));
    ecitygml_BuildingFunctionValueIterator_destroy(functions);
    BuildingUsageValueIterator *usages = ecitygml_BuildingPart_usages(part);
    TEST_ASSERT_NULL(ecitygml_BuildingUsageValueIterator_next(usages));
    ecitygml_BuildingUsageValueIterator_destroy(usages);
    ASSERT_STR("1010", ecitygml_RoofTypeValue_value(ecitygml_BuildingPart_roof_type(part)));
    const Date *built = ecitygml_BuildingPart_date_of_construction(part);
    TEST_ASSERT_NOT_NULL(built);
    TEST_ASSERT_EQUAL_INT32(1985, ecitygml_Date_year(built));
    TEST_ASSERT_EQUAL_UINT32(1, ecitygml_Date_month(built));
    TEST_ASSERT_EQUAL_UINT32(1, ecitygml_Date_day(built));
    assert_height(ecitygml_BuildingPart_heights(part), 2.5);
    // The west wall's area is left out: its member is a gml:OrientableSurface, not read yet.
    static const ExpectedSurface expected[] = {
        {WALL, NULL, "Garage Wall East", 9.600000023841858, true},
        {WALL, NULL, "Garage Wall South", 6.25, true},
        {WALL, NULL, "Garage Wall West", 0.0, false},
        {WALL, NULL, "Garage Wall North", 5.75, true},
        {GROUND, NULL, "Garage Ground Slab", 10.0, true},
        {ROOF, NULL, "Garage Roof", 10.012492197250394, true},
    };
    assert_surfaces(ecitygml_BuildingPart_boundaries(part), expected, LEN(expected));
    ecitygml_CityModel_destroy(city_model);
}

static void test_garage_relief(void) {
    CityModel *city_model = read(GARAGE);
    const ReliefFeature *reliefs[2];
    TEST_ASSERT_EQUAL_size_t(1, all_ReliefFeature(city_model, reliefs, 2));
    const ReliefFeature *relief = reliefs[0];
    ASSERT_STR("GML_6bb30328-7599-4500-90ef-766fde6aa67b", ecitygml_Id_as_str(ecitygml_ReliefFeature_feature_id(relief)));
    assert_only_name("Example TIN LOD2", ecitygml_ReliefFeature_names(relief));
    TEST_ASSERT_EQUAL_INT(LevelOfDetail_Two, ecitygml_ReliefFeature_lod(relief));
    AbstractReliefComponentPropertyIterator *components = ecitygml_ReliefFeature_relief_components(relief);
    const AbstractReliefComponentProperty *component = ecitygml_AbstractReliefComponentPropertyIterator_next(components);
    TEST_ASSERT_NOT_NULL(component);
    TEST_ASSERT_NULL(ecitygml_AbstractReliefComponentPropertyIterator_next(components));
    TEST_ASSERT_NULL(ecitygml_AbstractReliefComponentProperty_href(component));
    TEST_ASSERT_EQUAL_INT(FeatureType_TinRelief, ecitygml_AbstractReliefComponentKind_feature_type(
                                                     ecitygml_AbstractReliefComponentProperty_object(component)));
    ecitygml_AbstractReliefComponentPropertyIterator_destroy(components);

    const TinRelief *tin_reliefs[2];
    TEST_ASSERT_EQUAL_size_t(1, all_TinRelief(city_model, tin_reliefs, 2));
    const TinRelief *tin_relief = tin_reliefs[0];
    ASSERT_STR("GML_4eb161b0-aa7e-4087-937c-5c4c427c7fc9", ecitygml_Id_as_str(ecitygml_TinRelief_feature_id(tin_relief)));
    assert_only_name("Ground", ecitygml_TinRelief_names(tin_relief));
    TEST_ASSERT_EQUAL_INT(LevelOfDetail_Two, ecitygml_TinRelief_lod(tin_relief));
    const TinProperty *tin = ecitygml_TinRelief_tin(tin_relief);
    TEST_ASSERT_NOT_NULL(tin);
    TEST_ASSERT_NULL(ecitygml_TinProperty_href(tin));
    const TriangulatedSurface *surface = ecitygml_TinProperty_object(tin);
    TEST_ASSERT_NOT_NULL(surface);
    TriangleIterator *triangles = ecitygml_TriangulatedSurface_triangles(surface);
    size_t count = 0;
    while (ecitygml_TriangleIterator_next(triangles) != NULL) count++;
    ecitygml_TriangleIterator_destroy(triangles);
    TEST_ASSERT_EQUAL_size_t(12, count);
    ecitygml_TriangulatedSurface_area_3d_result area = ecitygml_TriangulatedSurface_area_3d(surface);
    TEST_ASSERT_TRUE(area.is_ok);
    ASSERT_CLOSE(399.8446647372588, area.ok);
    ecitygml_CityModel_destroy(city_model);
}

static void test_garage_round_trip(void) {
    CityModel *city_model = read(GARAGE);
    CityModel *written = round_trip(city_model);
    assert_same_feature_types(city_model, written);
    const Building *buildings[2];
    const BuildingPart *parts[2];
    const ReliefFeature *reliefs[2];
    const TinRelief *tin_reliefs[2];
    TEST_ASSERT_EQUAL_size_t(1, all_Building(written, buildings, 2));
    TEST_ASSERT_EQUAL_size_t(1, all_BuildingPart(written, parts, 2));
    TEST_ASSERT_EQUAL_size_t(1, all_ReliefFeature(written, reliefs, 2));
    TEST_ASSERT_EQUAL_size_t(1, all_TinRelief(written, tin_reliefs, 2));
    ASSERT_STR("GML_7b1a5a6f-ddad-4c3d-a507-3eb9ee0a8e68", ecitygml_Id_as_str(ecitygml_Building_feature_id(buildings[0])));
    ASSERT_STR("GMLID_BUI379228_1244_301", ecitygml_Id_as_str(ecitygml_BuildingPart_feature_id(parts[0])));
    ASSERT_STR("GML_6bb30328-7599-4500-90ef-766fde6aa67b", ecitygml_Id_as_str(ecitygml_ReliefFeature_feature_id(reliefs[0])));
    ASSERT_STR("GML_4eb161b0-aa7e-4087-937c-5c4c427c7fc9", ecitygml_Id_as_str(ecitygml_TinRelief_feature_id(tin_reliefs[0])));
    ecitygml_CityModel_destroy(written);
    ecitygml_CityModel_destroy(city_model);
}

// BuildingUnits_Storeys_xlink.gml

/// The number of surface members of a storey's LoD2 multi surface.
#define STOREY_MEMBERS 6

/// The hrefs of a storey's LoD2 surface members, into `out` ("" for inline members).
static void member_hrefs(const Storey *storey, char out[STOREY_MEMBERS][MAX_STRING]) {
    const MultiSurfaceProperty *property = ecitygml_Storey_lod2_multi_surface(storey);
    TEST_ASSERT_NOT_NULL(property);
    TEST_ASSERT_NULL(ecitygml_MultiSurfaceProperty_href(property));
    AbstractSurfacePropertyIterator *members =
        ecitygml_MultiSurface_surface_member(ecitygml_MultiSurfaceProperty_object(property));
    const AbstractSurfaceProperty *member;
    size_t len = 0;
    while ((member = ecitygml_AbstractSurfacePropertyIterator_next(members)) != NULL) {
        TEST_ASSERT_LESS_THAN_size_t(STOREY_MEMBERS, len);
        const HRef *href = ecitygml_AbstractSurfaceProperty_href(member);
        TEST_ASSERT_EQUAL(ecitygml_AbstractSurfaceProperty_object(member) == NULL, href != NULL);
        if (href != NULL) {
            href_string(href, out[len]);
        } else {
            out[len][0] = '\0';
        }
        len++;
    }
    ecitygml_AbstractSurfacePropertyIterator_destroy(members);
    TEST_ASSERT_EQUAL_size_t(STOREY_MEMBERS, len);
}

static void test_units_city_model(void) {
    CityModel *city_model = read(UNITS);
    TEST_ASSERT_EQUAL_size_t(1, ecitygml_CityModel_city_objects_len(city_model));
    assert_envelope(ecitygml_BoundingShape_envelope(ecitygml_CityModel_bounded_by(city_model)),
                    (const double[]){457841.0, 5439082.0, 111.0}, (const double[]){457854.0, 5439093.0, 121.0});
    FeatureType expected[42];
    size_t len = 0;
    const FeatureType head[] = {FeatureType_CityModel, FeatureType_Building, WALL, WALL, WALL, ROOF, WALL, ROOF, GROUND};
    for (size_t i = 0; i < LEN(head); i++) expected[len++] = head[i];
    const size_t walls[] = {8, 8, 4};
    for (size_t r = 0; r < LEN(walls); r++) {
        expected[len++] = FeatureType_BuildingRoom;
        for (size_t i = 0; i < walls[r]; i++) expected[len++] = FeatureType_InteriorWallSurface;
        expected[len++] = FeatureType_FloorSurface;
        expected[len++] = FeatureType_CeilingSurface;
    }
    expected[len++] = FeatureType_BuildingUnit;
    expected[len++] = FeatureType_BuildingUnit;
    expected[len++] = FeatureType_Storey;
    expected[len++] = FeatureType_Storey;
    TEST_ASSERT_EQUAL_size_t(42, len);
    assert_feature_types(city_model, expected, len);
    TEST_ASSERT_EQUAL_size_t(41, count_city_objects(city_model));
    ecitygml_CityModel_destroy(city_model);
}

static void test_units_building(void) {
    CityModel *city_model = read(UNITS);
    const Building *b = only_building(city_model);
    ASSERT_STR("building_unit_example_1", ecitygml_Id_as_str(ecitygml_Building_feature_id(b)));
    assert_no_names(ecitygml_Building_names(b));
    BuildingFunctionValueIterator *functions = ecitygml_Building_functions(b);
    TEST_ASSERT_NULL(ecitygml_BuildingFunctionValueIterator_next(functions));
    ecitygml_BuildingFunctionValueIterator_destroy(functions);
    BuildingUsageValueIterator *usages = ecitygml_Building_usages(b);
    TEST_ASSERT_NULL(ecitygml_BuildingUsageValueIterator_next(usages));
    ecitygml_BuildingUsageValueIterator_destroy(usages);
    TEST_ASSERT_NULL(ecitygml_Building_class(b));
    TEST_ASSERT_NULL(ecitygml_Building_roof_type(b));
    static const ExpectedSurface expected[] = {
        {WALL, NULL, "Outer Wall 1 (West)", 89.375, true},
        {WALL, NULL, "Outer Wall 2 (South)", 81.25, true},
        {WALL, NULL, "Outer Wall 3 (East)", 89.375, true},
        {ROOF, NULL, "Roof 1 (North)", 86.53792521201326, true},
        {WALL, NULL, "Outer Wall 4 (North)", 81.25, true},
        {ROOF, NULL, "Roof 2 (South)", 86.53792521201326, true},
        {GROUND, NULL, "Base Surface", 143.0, true},
    };
    assert_surfaces(ecitygml_Building_boundaries(b), expected, LEN(expected));
    ecitygml_CityModel_destroy(city_model);
}

static void test_units_subdivisions(void) {
    CityModel *city_model = read(UNITS);
    static const FeatureType expected_types[] = {FeatureType_BuildingUnit, FeatureType_BuildingUnit, FeatureType_Storey,
                                                 FeatureType_Storey};
    AbstractBuildingSubdivisionPropertyIterator *subdivisions =
        ecitygml_Building_building_subdivisions(only_building(city_model));
    const AbstractBuildingSubdivisionProperty *subdivision;
    size_t len = 0;
    while ((subdivision = ecitygml_AbstractBuildingSubdivisionPropertyIterator_next(subdivisions)) != NULL) {
        TEST_ASSERT_LESS_THAN_size_t(LEN(expected_types), len);
        TEST_ASSERT_NULL(ecitygml_AbstractBuildingSubdivisionProperty_href(subdivision));
        const AbstractBuildingSubdivisionKind *object = ecitygml_AbstractBuildingSubdivisionProperty_object(subdivision);
        TEST_ASSERT_NOT_NULL(object);
        TEST_ASSERT_EQUAL_INT(expected_types[len], ecitygml_AbstractBuildingSubdivisionKind_feature_type(object));
        len++;
    }
    ecitygml_AbstractBuildingSubdivisionPropertyIterator_destroy(subdivisions);
    TEST_ASSERT_EQUAL_size_t(LEN(expected_types), len);

    static const char *const unit_ids[] = {"BuildingUnit_apartment1", "BuildingUnit_apartment2"};
    const BuildingUnit *units[3];
    TEST_ASSERT_EQUAL_size_t(2, all_BuildingUnit(city_model, units, 3));
    for (size_t i = 0; i < 2; i++) {
        ASSERT_STR(unit_ids[i], ecitygml_Id_as_str(ecitygml_BuildingUnit_feature_id(units[i])));
        BuildingSubdivisionFunctionValueIterator *functions = ecitygml_BuildingUnit_functions(units[i]);
        ASSERT_STR("apartment", ecitygml_BuildingSubdivisionFunctionValue_value(
                                    ecitygml_BuildingSubdivisionFunctionValueIterator_next(functions)));
        TEST_ASSERT_NULL(ecitygml_BuildingSubdivisionFunctionValueIterator_next(functions));
        ecitygml_BuildingSubdivisionFunctionValueIterator_destroy(functions);
        TEST_ASSERT_NULL(ecitygml_BuildingUnit_class(units[i]));
        BuildingSubdivisionUsageValueIterator *usages = ecitygml_BuildingUnit_usages(units[i]);
        TEST_ASSERT_NULL(ecitygml_BuildingSubdivisionUsageValueIterator_next(usages));
        ecitygml_BuildingSubdivisionUsageValueIterator_destroy(usages);
        AbstractSpaceBoundaryPropertyIterator *boundaries = ecitygml_BuildingUnit_boundaries(units[i]);
        TEST_ASSERT_NULL(ecitygml_AbstractSpaceBoundaryPropertyIterator_next(boundaries));
        ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(boundaries);
        TEST_ASSERT_NULL(ecitygml_BuildingUnit_lod2_multi_surface(units[i]));
    }

    static const char *const storey_ids[] = {"storey1", "storey2"};
    const Storey *storeys[3];
    TEST_ASSERT_EQUAL_size_t(2, all_Storey(city_model, storeys, 3));
    for (size_t i = 0; i < 2; i++) {
        ASSERT_STR(storey_ids[i], ecitygml_Id_as_str(ecitygml_Storey_feature_id(storeys[i])));
        assert_no_names(ecitygml_Storey_names(storeys[i]));
        TEST_ASSERT_NULL(ecitygml_Storey_class(storeys[i]));
        BuildingSubdivisionFunctionValueIterator *functions = ecitygml_Storey_functions(storeys[i]);
        TEST_ASSERT_NULL(ecitygml_BuildingSubdivisionFunctionValueIterator_next(functions));
        ecitygml_BuildingSubdivisionFunctionValueIterator_destroy(functions);
        BuildingSubdivisionUsageValueIterator *usages = ecitygml_Storey_usages(storeys[i]);
        TEST_ASSERT_NULL(ecitygml_BuildingSubdivisionUsageValueIterator_next(usages));
        ecitygml_BuildingSubdivisionUsageValueIterator_destroy(usages);
        AbstractSpaceBoundaryPropertyIterator *boundaries = ecitygml_Storey_boundaries(storeys[i]);
        TEST_ASSERT_NULL(ecitygml_AbstractSpaceBoundaryPropertyIterator_next(boundaries));
        ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(boundaries);
    }
    ecitygml_CityModel_destroy(city_model);
}

static void test_units_storey_geometry(void) {
    static const char *const hrefs[2][STOREY_MEMBERS] = {
        {"", "#Wall_1_PolyID82397_997_453711_16336011", "#Wall_1_PolyID82397_997_453711_16336012",
         "#Wall_1_PolyID82397_997_453711_163360136", "", ""},
        {"", "#Wall_1_PolyID82397_997_453711_163360112", "#Wall_1_PolyID82397_997_453711_163360122",
         "#Wall_1_PolyID82397_997_453711_1633601362", "", ""},
    };
    static const double lower[2][3] = {{457841.1, 5439082.1, 111.1}, {457841.1, 5439082.1, 114.1}};
    static const double upper[2][3] = {{457853.9, 5439092.9, 113.9}, {457853.9, 5439092.9, 116.9}};
    CityModel *city_model = read(UNITS);
    const Storey *storeys[3];
    TEST_ASSERT_EQUAL_size_t(2, all_Storey(city_model, storeys, 3));
    for (size_t i = 0; i < 2; i++) {
        char actual[STOREY_MEMBERS][MAX_STRING];
        member_hrefs(storeys[i], actual);
        for (size_t j = 0; j < STOREY_MEMBERS; j++) {
            TEST_ASSERT_EQUAL_STRING(hrefs[i][j], actual[j]);
        }
        ecitygml_MultiSurface_area_3d_result area = ecitygml_MultiSurface_area_3d(
            ecitygml_MultiSurfaceProperty_object(ecitygml_Storey_lod2_multi_surface(storeys[i])));
        TEST_ASSERT_FALSE(area.is_ok);
        ecitygml_Error_destroy(area.err);
        assert_envelope(ecitygml_BoundingShape_envelope(ecitygml_Storey_bounded_by(storeys[i])), lower[i], upper[i]);
    }
    ecitygml_CityModel_destroy(city_model);
}

static void test_units_round_trip(void) {
    CityModel *city_model = read(UNITS);
    CityModel *written = round_trip(city_model);
    assert_same_feature_types(city_model, written);
    ASSERT_STR("building_unit_example_1", ecitygml_Id_as_str(ecitygml_Building_feature_id(only_building(written))));
    const Storey *original[3];
    const Storey *read_back[3];
    TEST_ASSERT_EQUAL_size_t(2, all_Storey(city_model, original, 3));
    TEST_ASSERT_EQUAL_size_t(2, all_Storey(written, read_back, 3));
    for (size_t i = 0; i < 2; i++) {
        char a[STOREY_MEMBERS][MAX_STRING];
        char b[STOREY_MEMBERS][MAX_STRING];
        member_hrefs(original[i], a);
        member_hrefs(read_back[i], b);
        for (size_t j = 0; j < STOREY_MEMBERS; j++) {
            TEST_ASSERT_EQUAL_STRING(a[j], b[j]);
        }
    }
    ecitygml_CityModel_destroy(written);
    ecitygml_CityModel_destroy(city_model);
}

// Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml

/// A relation: city object, relation type and the href of `relation_to` ("" for none).
typedef struct {
    char object[MAX_STRING];
    char type[MAX_STRING];
    char href[MAX_STRING];
} Relation;

#define MAX_RELATIONS 8

/// Appends the relations of a city object to `out`; destroys the iterator.
static void append_relations(DiplomatStringView id, CityObjectRelationPropertyIterator *related_to, Relation *out,
                             size_t *len) {
    const CityObjectRelationProperty *property;
    while ((property = ecitygml_CityObjectRelationPropertyIterator_next(related_to)) != NULL) {
        TEST_ASSERT_LESS_THAN_size_t(MAX_RELATIONS, *len);
        TEST_ASSERT_NULL(ecitygml_CityObjectRelationProperty_href(property));
        const CityObjectRelation *relation = ecitygml_CityObjectRelationProperty_object(property);
        TEST_ASSERT_NOT_NULL(relation);
        GenericAttributeKindIterator *attributes = ecitygml_CityObjectRelation_generic_attributes(relation);
        TEST_ASSERT_NULL(ecitygml_GenericAttributeKindIterator_next(attributes));
        ecitygml_GenericAttributeKindIterator_destroy(attributes);
        Relation *r = &out[(*len)++];
        copy_view(id, r->object);
        copy_view(ecitygml_RelationTypeValue_value(ecitygml_CityObjectRelation_relation_type(relation)), r->type);
        const HRef *href = ecitygml_Reference_href(ecitygml_CityObjectRelation_relation_to(relation));
        if (href != NULL) {
            href_string(href, r->href);
        } else {
            r->href[0] = '\0';
        }
    }
    ecitygml_CityObjectRelationPropertyIterator_destroy(related_to);
}

/// The relations of the roof surfaces and traffic areas, in document order, into `out`; returns their number.
static size_t relations(const CityModel *city_model, Relation *out) {
    size_t len = 0;
    AbstractFeatureKindRefIterator *iterator = ecitygml_CityModel_iter_features(city_model);
    AbstractFeatureKindRef *feature;
    while ((feature = ecitygml_AbstractFeatureKindRefIterator_next(iterator)) != NULL) {
        const RoofSurface *roof = ecitygml_RoofSurface_try_from(feature);
        const TrafficArea *area = ecitygml_TrafficArea_try_from(feature);
        if (roof != NULL) {
            append_relations(ecitygml_Id_as_str(ecitygml_RoofSurface_feature_id(roof)),
                             ecitygml_RoofSurface_related_to(roof), out, &len);
        } else if (area != NULL) {
            append_relations(ecitygml_Id_as_str(ecitygml_TrafficArea_feature_id(area)),
                             ecitygml_TrafficArea_related_to(area), out, &len);
        }
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractFeatureKindRefIterator_destroy(iterator);
    return len;
}

static void test_road_bridge_city_model(void) {
    CityModel *city_model = read(ROAD_BRIDGE);
    TEST_ASSERT_EQUAL_size_t(2, ecitygml_CityModel_city_objects_len(city_model));
    TEST_ASSERT_NULL(ecitygml_CityModel_bounded_by(city_model));
    FeatureType expected[25];
    size_t len = 0;
    const FeatureType head[] = {FeatureType_CityModel, FeatureType_Bridge, GROUND, ROOF, ROOF, WALL, WALL, WALL, WALL,
                                FeatureType_Road};
    for (size_t i = 0; i < LEN(head); i++) expected[len++] = head[i];
    const FeatureType section[] = {FeatureType_Section, FeatureType_TrafficSpace, FeatureType_TrafficArea,
                                   FeatureType_TrafficSpace, FeatureType_TrafficArea};
    for (size_t s = 0; s < 3; s++) {
        for (size_t i = 0; i < LEN(section); i++) expected[len++] = section[i];
    }
    assert_feature_types(city_model, expected, len);
    TEST_ASSERT_EQUAL_size_t(24, count_city_objects(city_model));
    ecitygml_CityModel_destroy(city_model);
}

static void test_road_bridge_bridge(void) {
    CityModel *city_model = read(ROAD_BRIDGE);
    const Bridge *bridges[2];
    TEST_ASSERT_EQUAL_size_t(1, all_Bridge(city_model, bridges, 2));
    const Bridge *bridge = bridges[0];
    ASSERT_STR("id_bridge1", ecitygml_Id_as_str(ecitygml_Bridge_feature_id(bridge)));
    assert_no_names(ecitygml_Bridge_names(bridge));
    CityObjectRelationPropertyIterator *related_to = ecitygml_Bridge_related_to(bridge);
    TEST_ASSERT_NULL(ecitygml_CityObjectRelationPropertyIterator_next(related_to));
    ecitygml_CityObjectRelationPropertyIterator_destroy(related_to);
    static const ExpectedSurface expected[] = {
        {GROUND, "id_groundsurface1", NULL, 77500.15996032, true},
        {ROOF, "id_roofsurface1", NULL, 38750.07998016, true},
        {ROOF, "id_roofsurface2", NULL, 38750.07998016, true},
        {WALL, "id_wallsurface4", NULL, 10075.02000744, true},
        {WALL, "id_wallsurface1", NULL, 20150.04001488, true},
        {WALL, "id_wallsurface2", NULL, 10075.02000744, true},
        {WALL, "id_wallsurface3", NULL, 20150.04001488, true},
    };
    assert_surfaces(ecitygml_Bridge_boundaries(bridge), expected, LEN(expected));
    ecitygml_CityModel_destroy(city_model);
}

static void test_road_bridge_road(void) {
    CityModel *city_model = read(ROAD_BRIDGE);
    const Road *roads[2];
    TEST_ASSERT_EQUAL_size_t(1, all_Road(city_model, roads, 2));
    const Road *road = roads[0];
    ASSERT_STR("id_road1", ecitygml_Id_as_str(ecitygml_Road_feature_id(road)));
    CityObjectRelationPropertyIterator *related_to = ecitygml_Road_related_to(road);
    TEST_ASSERT_NULL(ecitygml_CityObjectRelationPropertyIterator_next(related_to));
    ecitygml_CityObjectRelationPropertyIterator_destroy(related_to);
    TrafficSpacePropertyIterator *own_spaces = ecitygml_Road_traffic_spaces(road);
    TEST_ASSERT_NULL(ecitygml_TrafficSpacePropertyIterator_next(own_spaces));
    ecitygml_TrafficSpacePropertyIterator_destroy(own_spaces);
    AuxiliaryTrafficSpacePropertyIterator *auxiliary = ecitygml_Road_auxiliary_traffic_spaces(road);
    TEST_ASSERT_NULL(ecitygml_AuxiliaryTrafficSpacePropertyIterator_next(auxiliary));
    ecitygml_AuxiliaryTrafficSpacePropertyIterator_destroy(auxiliary);

    static const char *const section_ids[] = {"id_section1", "id_section2", "id_section3"};
    static const int numbers[] = {1, 2, 5, 6, 3, 4};
    SectionPropertyIterator *sections = ecitygml_Road_sections(road);
    const SectionProperty *section_property;
    size_t sections_len = 0;
    size_t spaces_len = 0;
    while ((section_property = ecitygml_SectionPropertyIterator_next(sections)) != NULL) {
        TEST_ASSERT_LESS_THAN_size_t(LEN(section_ids), sections_len);
        TEST_ASSERT_NULL(ecitygml_SectionProperty_href(section_property));
        const Section *section = ecitygml_SectionProperty_object(section_property);
        TEST_ASSERT_NOT_NULL(section);
        ASSERT_STR(section_ids[sections_len++], ecitygml_Id_as_str(ecitygml_Section_feature_id(section)));
        TrafficSpacePropertyIterator *spaces = ecitygml_Section_traffic_spaces(section);
        const TrafficSpaceProperty *space_property;
        while ((space_property = ecitygml_TrafficSpacePropertyIterator_next(spaces)) != NULL) {
            TEST_ASSERT_LESS_THAN_size_t(LEN(numbers), spaces_len);
            TEST_ASSERT_NULL(ecitygml_TrafficSpaceProperty_href(space_property));
            const TrafficSpace *space = ecitygml_TrafficSpaceProperty_object(space_property);
            TEST_ASSERT_NOT_NULL(space);
            char id[MAX_STRING];
            snprintf(id, sizeof(id), "id_trafficspace%d", numbers[spaces_len]);
            ASSERT_STR(id, ecitygml_Id_as_str(ecitygml_TrafficSpace_feature_id(space)));
            AbstractSpaceBoundaryPropertyIterator *boundaries = ecitygml_TrafficSpace_boundaries(space);
            const AbstractSpaceBoundaryProperty *boundary = ecitygml_AbstractSpaceBoundaryPropertyIterator_next(boundaries);
            TEST_ASSERT_NOT_NULL(boundary);
            TEST_ASSERT_NULL(ecitygml_AbstractSpaceBoundaryPropertyIterator_next(boundaries));
            TEST_ASSERT_NULL(ecitygml_AbstractSpaceBoundaryProperty_href(boundary));
            const AbstractSpaceBoundaryKind *area = ecitygml_AbstractSpaceBoundaryProperty_object(boundary);
            TEST_ASSERT_NOT_NULL(area);
            TEST_ASSERT_EQUAL_INT(FeatureType_TrafficArea, ecitygml_AbstractSpaceBoundaryKind_feature_type(area));
            snprintf(id, sizeof(id), "id_trafficarea%d", numbers[spaces_len]);
            ASSERT_STR(id, ecitygml_Id_as_str(ecitygml_AbstractSpaceBoundaryKind_feature_id(area)));
            ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(boundaries);
            spaces_len++;
        }
        ecitygml_TrafficSpacePropertyIterator_destroy(spaces);
    }
    ecitygml_SectionPropertyIterator_destroy(sections);
    TEST_ASSERT_EQUAL_size_t(LEN(section_ids), sections_len);
    TEST_ASSERT_EQUAL_size_t(LEN(numbers), spaces_len);
    ecitygml_CityModel_destroy(city_model);
}

static void test_road_bridge_relations(void) {
    static const char *const expected[][2] = {
        {"id_roofsurface1", "id_trafficarea5"},
        {"id_roofsurface2", "id_trafficarea6"},
        {"id_trafficarea5", "id_roofSurface1"},
        {"id_trafficarea6", "id_roofSurface2"},
    };
    CityModel *city_model = read(ROAD_BRIDGE);
    Relation found[MAX_RELATIONS];
    TEST_ASSERT_EQUAL_size_t(LEN(expected), relations(city_model, found));
    for (size_t i = 0; i < LEN(expected); i++) {
        TEST_ASSERT_EQUAL_STRING(expected[i][0], found[i].object);
        TEST_ASSERT_EQUAL_STRING("equal", found[i].type);
        TEST_ASSERT_EQUAL_STRING(expected[i][1], found[i].href);
    }
    const WallSurface *walls[8];
    size_t walls_len = all_WallSurface(city_model, walls, 8);
    for (size_t i = 0; i < walls_len; i++) {
        CityObjectRelationPropertyIterator *related_to = ecitygml_WallSurface_related_to(walls[i]);
        TEST_ASSERT_NULL(ecitygml_CityObjectRelationPropertyIterator_next(related_to));
        ecitygml_CityObjectRelationPropertyIterator_destroy(related_to);
    }
    const GroundSurface *grounds[8];
    size_t grounds_len = all_GroundSurface(city_model, grounds, 8);
    for (size_t i = 0; i < grounds_len; i++) {
        CityObjectRelationPropertyIterator *related_to = ecitygml_GroundSurface_related_to(grounds[i]);
        TEST_ASSERT_NULL(ecitygml_CityObjectRelationPropertyIterator_next(related_to));
        ecitygml_CityObjectRelationPropertyIterator_destroy(related_to);
    }
    ecitygml_CityModel_destroy(city_model);
}

static void test_road_bridge_round_trip(void) {
    CityModel *city_model = read(ROAD_BRIDGE);
    CityModel *written = round_trip(city_model);
    assert_same_feature_types(city_model, written);
    const Bridge *bridges[2];
    TEST_ASSERT_EQUAL_size_t(1, all_Bridge(written, bridges, 2));
    ASSERT_STR("id_bridge1", ecitygml_Id_as_str(ecitygml_Bridge_feature_id(bridges[0])));
    const Road *roads[2];
    TEST_ASSERT_EQUAL_size_t(1, all_Road(written, roads, 2));
    ASSERT_STR("id_road1", ecitygml_Id_as_str(ecitygml_Road_feature_id(roads[0])));
    Relation original[MAX_RELATIONS];
    Relation read_back[MAX_RELATIONS];
    size_t len = relations(city_model, original);
    TEST_ASSERT_EQUAL_size_t(len, relations(written, read_back));
    for (size_t i = 0; i < len; i++) {
        TEST_ASSERT_EQUAL_STRING(original[i].object, read_back[i].object);
        TEST_ASSERT_EQUAL_STRING(original[i].type, read_back[i].type);
        TEST_ASSERT_EQUAL_STRING(original[i].href, read_back[i].href);
    }
    ecitygml_CityModel_destroy(written);
    ecitygml_CityModel_destroy(city_model);
}

// historicalSuccession_CityGML_3.0_LOD2_Versioning.gml

/// Asserts a date time at 00:00 UTC on the given day, or none if `year` is 0.
static void assert_date(int year, unsigned month, unsigned day, const DateTime *date_time) {
    if (year == 0) {
        TEST_ASSERT_NULL(date_time);
        return;
    }
    TEST_ASSERT_NOT_NULL(date_time);
    TEST_ASSERT_EQUAL_INT32(year, ecitygml_DateTime_year(date_time));
    TEST_ASSERT_EQUAL_UINT32(month, ecitygml_DateTime_month(date_time));
    TEST_ASSERT_EQUAL_UINT32(day, ecitygml_DateTime_day(date_time));
    TEST_ASSERT_EQUAL_UINT32(0, ecitygml_DateTime_hour(date_time));
    TEST_ASSERT_EQUAL_UINT32(0, ecitygml_DateTime_minute(date_time));
    TEST_ASSERT_EQUAL_INT32(0, ecitygml_DateTime_offset_seconds(date_time));
}

static void test_versioning_city_model(void) {
    CityModel *city_model = read(VERSIONING);
    TEST_ASSERT_EQUAL_size_t(4, ecitygml_CityModel_city_objects_len(city_model));
    TEST_ASSERT_NULL(ecitygml_CityModel_bounded_by(city_model));
    FeatureType types[MAX_FEATURES];
    size_t len = feature_types(city_model, types);
    TEST_ASSERT_EQUAL_size_t(60, len);
    TEST_ASSERT_EQUAL_INT(FeatureType_CityModel, types[0]);
    static const struct {
        FeatureType type;
        size_t count;
    } expected[] = {
        {FeatureType_CityModel, 1}, {FeatureType_Building, 4}, {FeatureType_BuildingPart, 5},
        {ROOF, 14},                 {WALL, 31},                {GROUND, 5},
    };
    size_t total = 0;
    for (size_t i = 0; i < LEN(expected); i++) {
        size_t count = 0;
        for (size_t j = 0; j < len; j++) {
            if (types[j] == expected[i].type) count++;
        }
        TEST_ASSERT_EQUAL_size_t(expected[i].count, count);
        total += expected[i].count;
    }
    TEST_ASSERT_EQUAL_size_t(len, total);
    TEST_ASSERT_EQUAL_size_t(59, count_city_objects(city_model));
    ecitygml_CityModel_destroy(city_model);
}

static void test_versioning_buildings(void) {
    static const struct {
        const char *id;
        const char *name;
        int created_year;
        int terminated_year;
        const char *parts[2];
    } expected[] = {
        {"BU_69381AL47_2000-01-01", "Building A", 2000, 2015, {"BU_69381AL47_1", NULL}},
        {"BU_69381AL49_2000-01-01", "Building B", 2000, 2015, {"BU_69381AL49_1_2000-01-01", NULL}},
        {"BU_69381AL49_2015-01-01", "Building B", 2015, 0, {"BU_69381AL49_1_2015-01-01", "BU_69381AL49_2_2015-01-01"}},
        {"BU_69381AL50_2015-01-01", "Building C", 2015, 0, {"BU_69381AL50_1", NULL}},
    };
    CityModel *city_model = read(VERSIONING);
    const Building *buildings[5];
    TEST_ASSERT_EQUAL_size_t(LEN(expected), all_Building(city_model, buildings, 5));
    for (size_t i = 0; i < LEN(expected); i++) {
        const Building *b = buildings[i];
        ASSERT_STR(expected[i].id, ecitygml_Id_as_str(ecitygml_Building_feature_id(b)));
        ASSERT_STR(expected[i].name, first_name(ecitygml_Building_names(b)));
        assert_date(expected[i].created_year, 1, 1, ecitygml_Building_creation_date(b));
        assert_date(expected[i].terminated_year, 1, 1, ecitygml_Building_termination_date(b));
        BuildingPartPropertyIterator *parts = ecitygml_Building_building_parts(b);
        const BuildingPartProperty *property;
        size_t parts_len = 0;
        while ((property = ecitygml_BuildingPartPropertyIterator_next(parts)) != NULL) {
            TEST_ASSERT_LESS_THAN_size_t(2, parts_len);
            TEST_ASSERT_NOT_NULL(expected[i].parts[parts_len]);
            TEST_ASSERT_NULL(ecitygml_BuildingPartProperty_href(property));
            ASSERT_STR(expected[i].parts[parts_len],
                       ecitygml_Id_as_str(ecitygml_BuildingPart_feature_id(ecitygml_BuildingPartProperty_object(property))));
            parts_len++;
        }
        ecitygml_BuildingPartPropertyIterator_destroy(parts);
        TEST_ASSERT_TRUE(parts_len == 2 || expected[i].parts[parts_len] == NULL);
        HeightIterator *heights = ecitygml_Building_heights(b);
        TEST_ASSERT_NULL(ecitygml_HeightIterator_next(heights));
        ecitygml_HeightIterator_destroy(heights);
        AbstractSpaceBoundaryPropertyIterator *boundaries = ecitygml_Building_boundaries(b);
        TEST_ASSERT_NULL(ecitygml_AbstractSpaceBoundaryPropertyIterator_next(boundaries));
        ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(boundaries);
    }
    ecitygml_CityModel_destroy(city_model);
}

static void test_versioning_building_parts(void) {
    static const struct {
        const char *id;
        double height;
        size_t boundaries;
    } expected[] = {
        {"BU_69381AL47_1", 13.015, 8},           {"BU_69381AL49_1_2000-01-01", 10.63, 9},
        {"BU_69381AL49_1_2015-01-01", 10.63, 9}, {"BU_69381AL49_2_2015-01-01", 8.743, 7},
        {"BU_69381AL50_1", 18.215, 17},
    };
    CityModel *city_model = read(VERSIONING);
    const BuildingPart *parts[6];
    TEST_ASSERT_EQUAL_size_t(LEN(expected), all_BuildingPart(city_model, parts, 6));
    for (size_t i = 0; i < LEN(expected); i++) {
        ASSERT_STR(expected[i].id, ecitygml_Id_as_str(ecitygml_BuildingPart_feature_id(parts[i])));
        assert_height(ecitygml_BuildingPart_heights(parts[i]), expected[i].height);
        AbstractSpaceBoundaryPropertyIterator *boundaries = ecitygml_BuildingPart_boundaries(parts[i]);
        size_t count = 0;
        while (ecitygml_AbstractSpaceBoundaryPropertyIterator_next(boundaries) != NULL) count++;
        ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(boundaries);
        TEST_ASSERT_EQUAL_size_t(expected[i].boundaries, count);
        TEST_ASSERT_NULL(ecitygml_BuildingPart_creation_date(parts[i]));
        assert_no_names(ecitygml_BuildingPart_names(parts[i]));
    }
    ecitygml_CityModel_destroy(city_model);
}

static void test_versioning_round_trip(void) {
    CityModel *city_model = read(VERSIONING);
    CityModel *written = round_trip(city_model);
    assert_same_feature_types(city_model, written);
    const Building *a[5];
    const Building *b[5];
    size_t len = all_Building(city_model, a, 5);
    TEST_ASSERT_EQUAL_size_t(len, all_Building(written, b, 5));
    for (size_t i = 0; i < len; i++) {
        char id[MAX_STRING];
        copy_view(ecitygml_Id_as_str(ecitygml_Building_feature_id(a[i])), id);
        ASSERT_STR(id, ecitygml_Id_as_str(ecitygml_Building_feature_id(b[i])));
        const DateTime *created = ecitygml_Building_creation_date(a[i]);
        const DateTime *terminated = ecitygml_Building_termination_date(a[i]);
        assert_date(created != NULL ? ecitygml_DateTime_year(created) : 0, 1, 1, ecitygml_Building_creation_date(b[i]));
        assert_date(terminated != NULL ? ecitygml_DateTime_year(terminated) : 0, 1, 1,
                    ecitygml_Building_termination_date(b[i]));
    }
    const BuildingPart *p[6];
    const BuildingPart *q[6];
    size_t parts = all_BuildingPart(city_model, p, 6);
    TEST_ASSERT_EQUAL_size_t(parts, all_BuildingPart(written, q, 6));
    for (size_t i = 0; i < parts; i++) {
        char id[MAX_STRING];
        copy_view(ecitygml_Id_as_str(ecitygml_BuildingPart_feature_id(p[i])), id);
        ASSERT_STR(id, ecitygml_Id_as_str(ecitygml_BuildingPart_feature_id(q[i])));
    }
    ecitygml_CityModel_destroy(written);
    ecitygml_CityModel_destroy(city_model);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_garage_city_model);
    RUN_TEST(test_garage_building);
    RUN_TEST(test_garage_building_part);
    RUN_TEST(test_garage_relief);
    RUN_TEST(test_garage_round_trip);
    RUN_TEST(test_units_city_model);
    RUN_TEST(test_units_building);
    RUN_TEST(test_units_subdivisions);
    RUN_TEST(test_units_storey_geometry);
    RUN_TEST(test_units_round_trip);
    RUN_TEST(test_road_bridge_city_model);
    RUN_TEST(test_road_bridge_bridge);
    RUN_TEST(test_road_bridge_road);
    RUN_TEST(test_road_bridge_relations);
    RUN_TEST(test_road_bridge_round_trip);
    RUN_TEST(test_versioning_city_model);
    RUN_TEST(test_versioning_buildings);
    RUN_TEST(test_versioning_building_parts);
    RUN_TEST(test_versioning_round_trip);
    return UNITY_END();
}
