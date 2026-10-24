// The cases of crates/ecitygml/tests/conformance/tum-main-entrance.md.
#include "conformance/conformance.h"

#include "AbstractBuildingSubdivisionPropertyIterator.h"
#include "AbstractCityObjectKindRef.h"
#include "AbstractCityObjectKindRefIterator.h"
#include "AbstractSurfaceProperty.h"
#include "AbstractSurfacePropertyIterator.h"
#include "BoundingShape.h"
#include "BuildingFunctionValue.h"
#include "BuildingFunctionValueIterator.h"
#include "BuildingUsageValueIterator.h"
#include "CitygmlFormat.h"
#include "DateTime.h"
#include "DirectPosition.h"
#include "ElevationReferenceValue.h"
#include "Envelope.h"
#include "Error.h"
#include "ExternalReference.h"
#include "ExternalReferenceIterator.h"
#include "FeatureType.h"
#include "GenericAttributeKind.h"
#include "GenericAttributeKindIterator.h"
#include "GmlReader.h"
#include "GmlWriter.h"
#include "GroundSurface.h"
#include "Height.h"
#include "HeightIterator.h"
#include "HeightStatusValue.h"
#include "Id.h"
#include "Length.h"
#include "MultiSurface.h"
#include "MultiSurfaceProperty.h"
#include "OccupancyIterator.h"
#include "RoofSurface.h"
#include "RoofTypeValue.h"
#include "Shell.h"
#include "Solid.h"
#include "SolidProperty.h"
#include "StringAttribute.h"
#include "TriangleIterator.h"
#include "TriangulatedSurface.h"
#include "Triangulation.h"
#include "WallSurface.h"

#define ENTRANCE FIXTURE("tum-main-entrance/TUM-Main-Entrance.gml")

/// The most features the fixture has.
#define MAX_FEATURES 32

void setUp(void) {}
void tearDown(void) {}

/// The types of the building's boundaries, in document order.
static const FeatureType BOUNDARY_TYPES[] = {
    FeatureType_WallSurface,   FeatureType_WallSurface, FeatureType_WallSurface, FeatureType_WallSurface,
    FeatureType_WallSurface,   FeatureType_WallSurface, FeatureType_WallSurface, FeatureType_WallSurface,
    FeatureType_WallSurface,   FeatureType_WallSurface, FeatureType_GroundSurface, FeatureType_WallSurface,
    FeatureType_WallSurface,   FeatureType_WallSurface, FeatureType_RoofSurface, FeatureType_RoofSurface,
    FeatureType_WallSurface,
};
#define BOUNDARY_COUNT (sizeof(BOUNDARY_TYPES) / sizeof(BOUNDARY_TYPES[0]))

static void assert_point_close(double x, double y, double z, const DirectPosition *position) {
    TEST_ASSERT_NOT_NULL(position);
    ASSERT_CLOSE(x, ecitygml_DirectPosition_x(position));
    ASSERT_CLOSE(y, ecitygml_DirectPosition_y(position));
    ASSERT_CLOSE(z, ecitygml_DirectPosition_z(position));
}

/// The area of an inline LoD2 multi surface.
static double lod2_area(const MultiSurfaceProperty *property) {
    TEST_ASSERT_NOT_NULL(property);
    TEST_ASSERT_NULL(ecitygml_MultiSurfaceProperty_href(property));
    const MultiSurface *multi_surface = ecitygml_MultiSurfaceProperty_object(property);
    TEST_ASSERT_NOT_NULL(multi_surface);
    ecitygml_MultiSurface_area_3d_result area = ecitygml_MultiSurface_area_3d(multi_surface);
    TEST_ASSERT_TRUE(area.is_ok);
    return area.ok;
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

/// The `feature_id`s of the building's boundaries, into `out`; returns their number.
static size_t boundary_ids(const CityModel *city_model, char out[][96]) {
    size_t len = 0;
    AbstractSpaceBoundaryPropertyIterator *properties = ecitygml_Building_boundaries(first_building(city_model));
    const AbstractSpaceBoundaryProperty *property;
    while ((property = ecitygml_AbstractSpaceBoundaryPropertyIterator_next(properties)) != NULL) {
        TEST_ASSERT_LESS_THAN_size_t(MAX_BOUNDARIES, len);
        AbstractFeatureKindRef *feature =
            ecitygml_AbstractFeatureKindRef_from_space_boundary(ecitygml_AbstractSpaceBoundaryProperty_object(property));
        const WallSurface *wall = ecitygml_WallSurface_try_from(feature);
        const RoofSurface *roof = ecitygml_RoofSurface_try_from(feature);
        const GroundSurface *ground = ecitygml_GroundSurface_try_from(feature);
        DiplomatStringView id = wall != NULL   ? ecitygml_Id_as_str(ecitygml_WallSurface_feature_id(wall))
                                : roof != NULL ? ecitygml_Id_as_str(ecitygml_RoofSurface_feature_id(roof))
                                               : ecitygml_Id_as_str(ecitygml_GroundSurface_feature_id(ground));
        TEST_ASSERT_LESS_THAN_size_t(96, id.len);
        memcpy(out[len], id.data, id.len);
        out[len][id.len] = '\0';
        len++;
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(properties);
    return len;
}

static void test_entrance_city_model(void) {
    CityModel *city_model = read(ENTRANCE);
    TEST_ASSERT_EQUAL_size_t(1, ecitygml_CityModel_city_objects_len(city_model));
    const Envelope *envelope = ecitygml_BoundingShape_envelope(ecitygml_CityModel_bounded_by(city_model));
    TEST_ASSERT_NOT_NULL(envelope);
    assert_point_close(689975.68, 5335962.63, 503.0, ecitygml_Envelope_lower_corner(envelope));
    assert_point_close(692025.893, 5338012.713, 581.62, ecitygml_Envelope_upper_corner(envelope));
    FeatureType types[MAX_FEATURES];
    TEST_ASSERT_EQUAL_size_t(2 + BOUNDARY_COUNT, feature_types(city_model, types));
    TEST_ASSERT_EQUAL_INT(FeatureType_CityModel, types[0]);
    TEST_ASSERT_EQUAL_INT(FeatureType_Building, types[1]);
    for (size_t i = 0; i < BOUNDARY_COUNT; i++) {
        TEST_ASSERT_EQUAL_INT(BOUNDARY_TYPES[i], types[2 + i]);
    }
    TEST_ASSERT_EQUAL_size_t(18, count_city_objects(city_model));
    ecitygml_CityModel_destroy(city_model);
}

static void test_entrance_building_attributes(void) {
    CityModel *city_model = read(ENTRANCE);
    const Building *b = first_building(city_model);
    ASSERT_STR("DEBY_LOD2_4959457", ecitygml_Id_as_str(ecitygml_Building_feature_id(b)));
    CodeIterator *names = ecitygml_Building_names(b);
    TEST_ASSERT_NULL(ecitygml_CodeIterator_next(names));
    ecitygml_CodeIterator_destroy(names);
    TEST_ASSERT_NULL(ecitygml_Building_class(b));
    BuildingFunctionValueIterator *functions = ecitygml_Building_functions(b);
    const BuildingFunctionValue *function = ecitygml_BuildingFunctionValueIterator_next(functions);
    TEST_ASSERT_NOT_NULL(function);
    TEST_ASSERT_NULL(ecitygml_BuildingFunctionValueIterator_next(functions));
    ASSERT_STR("31001_3020", ecitygml_BuildingFunctionValue_value(function));
    ecitygml_BuildingFunctionValueIterator_destroy(functions);
    BuildingUsageValueIterator *usages = ecitygml_Building_usages(b);
    TEST_ASSERT_NULL(ecitygml_BuildingUsageValueIterator_next(usages));
    ecitygml_BuildingUsageValueIterator_destroy(usages);
    ASSERT_STR("1000", ecitygml_RoofTypeValue_value(ecitygml_Building_roof_type(b)));
    ecitygml_Building_storeys_above_ground_result above = ecitygml_Building_storeys_above_ground(b);
    TEST_ASSERT_TRUE(above.is_ok);
    TEST_ASSERT_EQUAL_INT64(4, above.ok);
    TEST_ASSERT_FALSE(ecitygml_Building_storeys_below_ground(b).is_ok);

    HeightIterator *heights = ecitygml_Building_heights(b);
    const Height *height = ecitygml_HeightIterator_next(heights);
    TEST_ASSERT_NOT_NULL(height);
    TEST_ASSERT_NULL(ecitygml_HeightIterator_next(heights));
    ASSERT_STR("topOfConstruction", ecitygml_ElevationReferenceValue_value(ecitygml_Height_high_reference(height)));
    ASSERT_STR("lowestGroundPoint", ecitygml_ElevationReferenceValue_value(ecitygml_Height_low_reference(height)));
    TEST_ASSERT_EQUAL_INT(HeightStatusValue_Measured, ecitygml_Height_status(height));
    ASSERT_CLOSE(19.408, ecitygml_Length_value(ecitygml_Height_length(height)));
    ASSERT_STR("urn:adv:uom:m", ecitygml_Length_uom(ecitygml_Height_length(height)));
    ecitygml_HeightIterator_destroy(heights);

    const DateTime *created = ecitygml_Building_creation_date(b);
    TEST_ASSERT_NOT_NULL(created);
    TEST_ASSERT_EQUAL_INT32(2025, ecitygml_DateTime_year(created));
    TEST_ASSERT_EQUAL_UINT32(1, ecitygml_DateTime_month(created));
    TEST_ASSERT_EQUAL_UINT32(2, ecitygml_DateTime_day(created));
    TEST_ASSERT_EQUAL_UINT32(0, ecitygml_DateTime_hour(created));
    TEST_ASSERT_EQUAL_UINT32(0, ecitygml_DateTime_minute(created));
    TEST_ASSERT_EQUAL_INT32(3600, ecitygml_DateTime_offset_seconds(created));
    TEST_ASSERT_NULL(ecitygml_Building_bounded_by(b));
    OccupancyIterator *occupancies = ecitygml_Building_occupancies(b);
    TEST_ASSERT_NULL(ecitygml_OccupancyIterator_next(occupancies));
    ecitygml_OccupancyIterator_destroy(occupancies);
    AbstractBuildingSubdivisionPropertyIterator *subdivisions = ecitygml_Building_building_subdivisions(b);
    TEST_ASSERT_NULL(ecitygml_AbstractBuildingSubdivisionPropertyIterator_next(subdivisions));
    ecitygml_AbstractBuildingSubdivisionPropertyIterator_destroy(subdivisions);
    ecitygml_CityModel_destroy(city_model);
}

static void test_entrance_external_reference(void) {
    CityModel *city_model = read(ENTRANCE);
    ExternalReferenceIterator *references = ecitygml_Building_external_references(first_building(city_model));
    const ExternalReference *reference = ecitygml_ExternalReferenceIterator_next(references);
    TEST_ASSERT_NOT_NULL(reference);
    TEST_ASSERT_NULL(ecitygml_ExternalReferenceIterator_next(references));
    ASSERT_STR("DEBYvAAAAABTMIyA", ecitygml_ExternalReference_target_resource(reference));
    ecitygml_ExternalReferenceIterator_destroy(references);
    ecitygml_CityModel_destroy(city_model);
}

static void test_entrance_external_reference_details(void) {
    CityModel *city_model = read(ENTRANCE);
    ExternalReferenceIterator *references = ecitygml_Building_external_references(first_building(city_model));
    const ExternalReference *reference = ecitygml_ExternalReferenceIterator_next(references);
    TEST_ASSERT_NOT_NULL(reference);
    TEST_ASSERT_NULL(ecitygml_ExternalReferenceIterator_next(references));
    ecitygml_ExternalReference_information_system_result information_system =
        ecitygml_ExternalReference_information_system(reference);
    TEST_ASSERT_TRUE(information_system.is_ok);
    ASSERT_STR("http://repository.gdi-de.org/schemas/adv/citygml/fdv/art.htm#_9100", information_system.ok);
    TEST_ASSERT_FALSE(ecitygml_ExternalReference_relation_type(reference).is_ok);
    ecitygml_ExternalReferenceIterator_destroy(references);
    ecitygml_CityModel_destroy(city_model);
}

static void test_entrance_generic_attributes(void) {
    static const char *const expected[][2] = {
        {"DatenquelleBodenhoehe", "1100"},
        {"DatenquelleDachhoehe", "1000"},
        {"DatenquelleLage", "1000"},
        {"Gemeindeschluessel", "09162000"},
        {"HoeheDach", "534.450"},
        {"HoeheGrund", "515.042"},
        {"Methode", "2000"},
        {"NiedrigsteTraufeDesGebaeudes", "527.312"},
        {"Grundrissaktualitaet", "2025-02-17"},
        {"Geometrietyp2DReferenz", "3000"},
    };
    CityModel *city_model = read(ENTRANCE);
    GenericAttributeKindIterator *attributes = ecitygml_Building_generic_attributes(first_building(city_model));
    for (size_t i = 0; i < sizeof(expected) / sizeof(expected[0]); i++) {
        const GenericAttributeKind *attribute = ecitygml_GenericAttributeKindIterator_next(attributes);
        TEST_ASSERT_NOT_NULL(attribute);
        ASSERT_STR(expected[i][0], ecitygml_GenericAttributeKind_name(attribute));
        const StringAttribute *string = ecitygml_GenericAttributeKind_as_string(attribute);
        TEST_ASSERT_NOT_NULL(string);
        ASSERT_STR(expected[i][1], ecitygml_StringAttribute_value(string));
    }
    TEST_ASSERT_NULL(ecitygml_GenericAttributeKindIterator_next(attributes));
    ecitygml_GenericAttributeKindIterator_destroy(attributes);
    ecitygml_CityModel_destroy(city_model);
}

static void test_entrance_boundaries(void) {
    CityModel *city_model = read(ENTRANCE);
    const Building *b = first_building(city_model);
    AbstractSpaceBoundaryPropertyIterator *properties = ecitygml_Building_boundaries(b);
    const AbstractSpaceBoundaryProperty *property;
    while ((property = ecitygml_AbstractSpaceBoundaryPropertyIterator_next(properties)) != NULL) {
        TEST_ASSERT_NULL(ecitygml_AbstractSpaceBoundaryProperty_href(property));
    }
    ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(properties);

    AbstractFeatureKindRef *features[MAX_BOUNDARIES];
    size_t len = boundaries(b, features);
    TEST_ASSERT_EQUAL_size_t(BOUNDARY_COUNT, len);
    double wall_area = 0.0;
    double roofs[2];
    size_t roof_count = 0;
    double ground_area = 0.0;
    size_t ground_count = 0;
    const WallSurface *first_wall = NULL;
    for (size_t i = 0; i < len; i++) {
        TEST_ASSERT_EQUAL_INT(BOUNDARY_TYPES[i], ecitygml_AbstractFeatureKindRef_feature_type(features[i]));
        const WallSurface *wall = ecitygml_WallSurface_try_from(features[i]);
        const RoofSurface *roof = ecitygml_RoofSurface_try_from(features[i]);
        const GroundSurface *ground = ecitygml_GroundSurface_try_from(features[i]);
        if (wall != NULL) {
            if (first_wall == NULL) first_wall = wall;
            wall_area += lod2_area(ecitygml_WallSurface_lod2_multi_surface(wall));
        } else if (roof != NULL) {
            TEST_ASSERT_LESS_THAN_size_t(2, roof_count);
            roofs[roof_count++] = lod2_area(ecitygml_RoofSurface_lod2_multi_surface(roof));
        } else if (ground != NULL) {
            ground_area = lod2_area(ecitygml_GroundSurface_lod2_multi_surface(ground));
            ground_count++;
        }
    }
    TEST_ASSERT_NOT_NULL(first_wall);
    ASSERT_STR("DEBY_LOD2_4959457_ca1db42f-9d12-4f41-972c-c7da1614f0a8_2",
               ecitygml_Id_as_str(ecitygml_WallSurface_feature_id(first_wall)));
    CodeIterator *names = ecitygml_WallSurface_names(first_wall);
    TEST_ASSERT_NULL(ecitygml_CodeIterator_next(names));
    ecitygml_CodeIterator_destroy(names);
    ASSERT_CLOSE(3783.3908922901974, wall_area);
    TEST_ASSERT_EQUAL_size_t(2, roof_count);
    ASSERT_CLOSE(250.233154296875, roofs[0]);
    ASSERT_CLOSE(979.3291015625, roofs[1]);
    ASSERT_CLOSE(1229.562255859375, roofs[0] + roofs[1]);
    TEST_ASSERT_EQUAL_size_t(1, ground_count);
    ASSERT_CLOSE(1229.562255859375, ground_area);
    destroy_features(features, len);
    ecitygml_CityModel_destroy(city_model);
}

static void test_entrance_wall_triangulation(void) {
    CityModel *city_model = read(ENTRANCE);
    AbstractFeatureKindRef *features[MAX_BOUNDARIES];
    size_t len = boundaries(first_building(city_model), features);
    const WallSurface *wall = ecitygml_WallSurface_try_from(features[0]);
    TEST_ASSERT_NOT_NULL(wall);
    const MultiSurface *multi_surface =
        ecitygml_MultiSurfaceProperty_object(ecitygml_WallSurface_lod2_multi_surface(wall));
    TEST_ASSERT_NOT_NULL(multi_surface);
    AbstractSurfacePropertyIterator *members = ecitygml_MultiSurface_surface_member(multi_surface);
    TEST_ASSERT_NOT_NULL(ecitygml_AbstractSurfacePropertyIterator_next(members));
    TEST_ASSERT_NULL(ecitygml_AbstractSurfacePropertyIterator_next(members));
    ecitygml_AbstractSurfacePropertyIterator_destroy(members);
    ecitygml_MultiSurface_area_3d_result area = ecitygml_MultiSurface_area_3d(multi_surface);
    TEST_ASSERT_TRUE(area.is_ok);
    ASSERT_CLOSE(546.6949745937537, area.ok);
    ecitygml_MultiSurface_triangulate_result triangulation = ecitygml_MultiSurface_triangulate(multi_surface);
    TEST_ASSERT_TRUE(triangulation.is_ok);
    const TriangulatedSurface *surface = ecitygml_Triangulation_surface(triangulation.ok);
    TriangleIterator *triangles = ecitygml_TriangulatedSurface_triangles(surface);
    size_t count = 0;
    while (ecitygml_TriangleIterator_next(triangles) != NULL) count++;
    ecitygml_TriangleIterator_destroy(triangles);
    TEST_ASSERT_EQUAL_size_t(4, count);
    TEST_ASSERT_FALSE(ecitygml_Triangulation_has_skipped(triangulation.ok));
    ecitygml_TriangulatedSurface_area_3d_result triangulated_area = ecitygml_TriangulatedSurface_area_3d(surface);
    TEST_ASSERT_TRUE(triangulated_area.is_ok);
    ASSERT_CLOSE(546.6949742237184, triangulated_area.ok);
    ecitygml_Triangulation_destroy(triangulation.ok);
    destroy_features(features, len);
    ecitygml_CityModel_destroy(city_model);
}

static void test_entrance_solid_unresolved(void) {
    CityModel *city_model = read(ENTRANCE);
    const SolidProperty *property = ecitygml_Building_lod2_solid(first_building(city_model));
    TEST_ASSERT_NOT_NULL(property);
    TEST_ASSERT_NULL(ecitygml_SolidProperty_href(property));
    const Solid *solid = ecitygml_SolidProperty_object(property);
    TEST_ASSERT_NOT_NULL(solid);
    AbstractSurfacePropertyIterator *members = ecitygml_Shell_members(ecitygml_Solid_exterior(solid));
    const AbstractSurfaceProperty *member;
    size_t count = 0;
    while ((member = ecitygml_AbstractSurfacePropertyIterator_next(members)) != NULL) {
        TEST_ASSERT_NULL(ecitygml_AbstractSurfaceProperty_object(member));
        count++;
    }
    ecitygml_AbstractSurfacePropertyIterator_destroy(members);
    TEST_ASSERT_EQUAL_size_t(17, count);
    ecitygml_Solid_volume_3d_result volume = ecitygml_Solid_volume_3d(solid);
    TEST_ASSERT_FALSE(volume.is_ok);
    ecitygml_Error_destroy(volume.err);
    ecitygml_CityModel_destroy(city_model);
}

static void test_entrance_round_trip(void) {
    CityModel *city_model = read(ENTRANCE);
    GmlWriter *writer = ecitygml_GmlWriter_new(CitygmlFormat_Gml);
    TEST_ASSERT_TRUE(ecitygml_GmlWriter_finish(writer, city_model).is_ok);
    GmlReader *reader = ecitygml_GmlReader_new(ecitygml_GmlWriter_data(writer), CitygmlFormat_Gml);
    ecitygml_GmlReader_finish_result written = ecitygml_GmlReader_finish(reader);
    ecitygml_GmlReader_destroy(reader);
    ecitygml_GmlWriter_destroy(writer);
    TEST_ASSERT_TRUE(written.is_ok);
    FeatureType original[MAX_FEATURES];
    FeatureType read_back[MAX_FEATURES];
    size_t len = feature_types(city_model, original);
    TEST_ASSERT_EQUAL_size_t(len, feature_types(written.ok, read_back));
    TEST_ASSERT_EQUAL_INT_ARRAY(original, read_back, len);
    ASSERT_STR("DEBY_LOD2_4959457", ecitygml_Id_as_str(ecitygml_Building_feature_id(first_building(written.ok))));
    char original_ids[MAX_BOUNDARIES][96];
    char written_ids[MAX_BOUNDARIES][96];
    size_t ids = boundary_ids(city_model, original_ids);
    TEST_ASSERT_EQUAL_size_t(ids, boundary_ids(written.ok, written_ids));
    for (size_t i = 0; i < ids; i++) {
        TEST_ASSERT_EQUAL_STRING(original_ids[i], written_ids[i]);
    }
    ecitygml_CityModel_destroy(written.ok);
    ecitygml_CityModel_destroy(city_model);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_entrance_city_model);
    RUN_TEST(test_entrance_building_attributes);
    RUN_TEST(test_entrance_external_reference);
    RUN_TEST(test_entrance_external_reference_details);
    RUN_TEST(test_entrance_generic_attributes);
    RUN_TEST(test_entrance_boundaries);
    RUN_TEST(test_entrance_wall_triangulation);
    RUN_TEST(test_entrance_solid_unresolved);
    RUN_TEST(test_entrance_round_trip);
    return UNITY_END();
}
