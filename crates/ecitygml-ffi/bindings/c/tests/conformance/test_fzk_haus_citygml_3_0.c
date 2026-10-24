// The cases of crates/ecitygml/tests/conformance/fzk-haus-citygml-3.0.md.
#include "conformance/conformance.h"

#include "AbstractBuildingSubdivisionKind.h"
#include "AbstractBuildingSubdivisionProperty.h"
#include "AbstractBuildingSubdivisionPropertyIterator.h"
#include "AbstractCityObjectKindRef.h"
#include "AbstractCityObjectKindRefIterator.h"
#include "AbstractSurfaceProperty.h"
#include "AbstractSurfacePropertyIterator.h"
#include "BoundingShape.h"
#include "BuildingFunctionValue.h"
#include "BuildingFunctionValueIterator.h"
#include "BuildingSubdivisionClassValue.h"
#include "BuildingSubdivisionFunctionValueIterator.h"
#include "BuildingSubdivisionUsageValueIterator.h"
#include "BuildingUsageValueIterator.h"
#include "CitygmlFormat.h"
#include "DirectPosition.h"
#include "ElevationReferenceValue.h"
#include "Envelope.h"
#include "Error.h"
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
#include "Occupancy.h"
#include "OccupancyIterator.h"
#include "RoofSurface.h"
#include "RoofTypeValue.h"
#include "Shell.h"
#include "Solid.h"
#include "SolidProperty.h"
#include "Storey.h"
#include "StringAttribute.h"
#include "WallSurface.h"

#define CONSTRUCTION FIXTURE("fzk-haus-citygml-3.0/01-FZK-Haus-LoD2-Tex-Storey-Construction-CG30-V01.gml")
#define INTERIOR FIXTURE("fzk-haus-citygml-3.0/04-FZK-Haus-LoD2-Tex-Storey-CG30-V01-InteriorSurface.gml")
#define WINDOW FIXTURE("fzk-haus-citygml-3.0/04-FZK-Haus-LoD2-Tex-Storey-Construction-CG30-V01-Window-Interior.gml")
#define POINT_CLOUD FIXTURE("fzk-haus-citygml-3.0/06-FZK-Haus-LoD2-Tex-Storey-CG30-V01-PointCloud-thinned.gml")

#define CONSTRUCTION_ID "_FZK-Haus-Storey-Construction_BD.DX9Xm6VLbbyLGAxG2v86"
#define TEST_BUILDING_ID "KIT-Test-Building-01"
#define WINDOW_ID "_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz"

/// The most features a fixture of this dataset has.
#define MAX_FEATURES 96

/// The storeys of each fixture.
#define STOREYS 2

void setUp(void) {}
void tearDown(void) {}

static void assert_point_close(double x, double y, double z, const DirectPosition *position) {
    TEST_ASSERT_NOT_NULL(position);
    ASSERT_CLOSE(x, ecitygml_DirectPosition_x(position));
    ASSERT_CLOSE(y, ecitygml_DirectPosition_y(position));
    ASSERT_CLOSE(z, ecitygml_DirectPosition_z(position));
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

/// The number of features of a type among the feature types.
static size_t count_type(const FeatureType *types, size_t len, FeatureType type) {
    size_t count = 0;
    for (size_t i = 0; i < len; i++) {
        if (types[i] == type) count++;
    }
    return count;
}

/// A feature type and its expected number of features.
typedef struct {
    FeatureType type;
    size_t count;
} TypeCount;

/// Asserts the number of features per feature type, and that there are no others.
static void assert_type_counts(const CityModel *city_model, const TypeCount *expected, size_t expected_len) {
    FeatureType types[MAX_FEATURES];
    size_t len = feature_types(city_model, types);
    size_t total = 0;
    for (size_t i = 0; i < expected_len; i++) {
        TEST_ASSERT_EQUAL_size_t_MESSAGE(expected[i].count, count_type(types, len, expected[i].type), "feature type");
        total += expected[i].count;
    }
    TEST_ASSERT_EQUAL_size_t(total, len);
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

/// The storeys, into `out`; they borrow from the model. Asserts there are exactly `STOREYS`.
static void storeys(const CityModel *city_model, const Storey **out) {
    size_t len = 0;
    AbstractFeatureKindRefIterator *iterator = ecitygml_CityModel_iter_features(city_model);
    AbstractFeatureKindRef *feature;
    while ((feature = ecitygml_AbstractFeatureKindRefIterator_next(iterator)) != NULL) {
        const Storey *storey = ecitygml_Storey_try_from(feature);
        if (storey != NULL) {
            TEST_ASSERT_LESS_THAN_size_t(STOREYS, len);
            out[len++] = storey;
        }
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractFeatureKindRefIterator_destroy(iterator);
    TEST_ASSERT_EQUAL_size_t(STOREYS, len);
}

static void assert_city_model(const CityModel *city_model, const double lower[3], const double upper[3]) {
    TEST_ASSERT_EQUAL_size_t(1, ecitygml_CityModel_city_objects_len(city_model));
    const Envelope *envelope = ecitygml_BoundingShape_envelope(ecitygml_CityModel_bounded_by(city_model));
    TEST_ASSERT_NOT_NULL(envelope);
    assert_point_close(lower[0], lower[1], lower[2], ecitygml_Envelope_lower_corner(envelope));
    assert_point_close(upper[0], upper[1], upper[2], ecitygml_Envelope_upper_corner(envelope));
}

/// The one height and occupancy of the storey examples' buildings.
static void assert_height_and_occupancy(const Building *b) {
    HeightIterator *heights = ecitygml_Building_heights(b);
    const Height *height = ecitygml_HeightIterator_next(heights);
    TEST_ASSERT_NOT_NULL(height);
    TEST_ASSERT_NULL(ecitygml_HeightIterator_next(heights));
    ASSERT_STR("highestRoofEdge", ecitygml_ElevationReferenceValue_value(ecitygml_Height_high_reference(height)));
    ASSERT_STR("lowestGroundPoint", ecitygml_ElevationReferenceValue_value(ecitygml_Height_low_reference(height)));
    TEST_ASSERT_EQUAL_INT(HeightStatusValue_Measured, ecitygml_Height_status(height));
    ASSERT_CLOSE(6.52, ecitygml_Length_value(ecitygml_Height_length(height)));
    ASSERT_STR("urn:adv:uom:m", ecitygml_Length_uom(ecitygml_Height_length(height)));
    ecitygml_HeightIterator_destroy(heights);
    OccupancyIterator *occupancies = ecitygml_Building_occupancies(b);
    const Occupancy *occupancy = ecitygml_OccupancyIterator_next(occupancies);
    TEST_ASSERT_NOT_NULL(occupancy);
    TEST_ASSERT_NULL(ecitygml_OccupancyIterator_next(occupancies));
    TEST_ASSERT_EQUAL_INT64(2, ecitygml_Occupancy_number_of_occupants(occupancy));
    ecitygml_OccupancyIterator_destroy(occupancies);
}

/// The storeys' first names (`Ground Floor`, `Second Floor`) and classes (NULL for none).
static void assert_storeys(const CityModel *city_model, const char *const classes[STOREYS]) {
    static const char *const names[STOREYS] = {"Ground Floor", "Second Floor"};
    const Storey *found[STOREYS];
    storeys(city_model, found);
    for (size_t i = 0; i < STOREYS; i++) {
        ASSERT_STR(names[i], first_name(ecitygml_Storey_names(found[i])));
        const BuildingSubdivisionClassValue *class_value = ecitygml_Storey_class(found[i]);
        if (classes[i] == NULL) {
            TEST_ASSERT_NULL(class_value);
        } else {
            TEST_ASSERT_NOT_NULL(class_value);
            ASSERT_STR(classes[i], ecitygml_BuildingSubdivisionClassValue_value(class_value));
        }
    }
}

/// An expected boundary surface: its type, first name and LoD2 area (unused where it has none).
typedef struct {
    FeatureType type;
    const char *name;
    double area;
} ExpectedSurface;

/// Asserts a storey's boundaries: all inline wall, roof or ground surfaces with the expected types and first names,
/// and with an LoD2 multi surface of the expected area if `with_area`, else without one.
static void assert_boundaries(const Storey *storey, const ExpectedSurface *expected, size_t expected_len,
                              bool with_area) {
    AbstractSpaceBoundaryPropertyIterator *properties = ecitygml_Storey_boundaries(storey);
    const AbstractSpaceBoundaryProperty *property;
    size_t len = 0;
    while ((property = ecitygml_AbstractSpaceBoundaryPropertyIterator_next(properties)) != NULL) {
        TEST_ASSERT_LESS_THAN_size_t(expected_len, len);
        TEST_ASSERT_NULL(ecitygml_AbstractSpaceBoundaryProperty_href(property));
        AbstractFeatureKindRef *feature =
            ecitygml_AbstractFeatureKindRef_from_space_boundary(ecitygml_AbstractSpaceBoundaryProperty_object(property));
        TEST_ASSERT_EQUAL_INT(expected[len].type, ecitygml_AbstractFeatureKindRef_feature_type(feature));
        const WallSurface *wall = ecitygml_WallSurface_try_from(feature);
        const RoofSurface *roof = ecitygml_RoofSurface_try_from(feature);
        const GroundSurface *ground = ecitygml_GroundSurface_try_from(feature);
        TEST_ASSERT_TRUE(wall != NULL || roof != NULL || ground != NULL);
        CodeIterator *names = wall != NULL   ? ecitygml_WallSurface_names(wall)
                              : roof != NULL ? ecitygml_RoofSurface_names(roof)
                                             : ecitygml_GroundSurface_names(ground);
        ASSERT_STR(expected[len].name, first_name(names));
        const MultiSurfaceProperty *multi_surface = wall != NULL   ? ecitygml_WallSurface_lod2_multi_surface(wall)
                                                    : roof != NULL ? ecitygml_RoofSurface_lod2_multi_surface(roof)
                                                                   : ecitygml_GroundSurface_lod2_multi_surface(ground);
        if (with_area) {
            TEST_ASSERT_NOT_NULL(multi_surface);
            ecitygml_MultiSurface_area_3d_result area =
                ecitygml_MultiSurface_area_3d(ecitygml_MultiSurfaceProperty_object(multi_surface));
            TEST_ASSERT_TRUE(area.is_ok);
            ASSERT_CLOSE(expected[len].area, area.ok);
        } else {
            TEST_ASSERT_NULL(multi_surface);
        }
        ecitygml_AbstractFeatureKindRef_destroy(feature);
        len++;
    }
    ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(properties);
    TEST_ASSERT_EQUAL_size_t(expected_len, len);
}

/// Asserts that the building has no boundaries.
static void assert_no_boundaries(const Building *b) {
    AbstractSpaceBoundaryPropertyIterator *boundaries = ecitygml_Building_boundaries(b);
    TEST_ASSERT_NULL(ecitygml_AbstractSpaceBoundaryPropertyIterator_next(boundaries));
    ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(boundaries);
}

/// Writes the city model and reads it back: the same feature types in the same order and the building's id.
static void assert_round_trip(const char *path, const char *building_id) {
    CityModel *city_model = read(path);
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
    ASSERT_STR(building_id, ecitygml_Id_as_str(ecitygml_Building_feature_id(first_building(written.ok))));
    ecitygml_CityModel_destroy(written.ok);
    ecitygml_CityModel_destroy(city_model);
}

// 01-FZK-Haus-LoD2-Tex-Storey-Construction-CG30-V01.gml

static void test_construction_city_model(void) {
    CityModel *city_model = read(CONSTRUCTION);
    assert_city_model(city_model, (const double[]){458899.5, 5438784.5, 113.5},
                      (const double[]){458912.5, 5438795.5, 120.017691});
    FeatureType expected[26] = {FeatureType_CityModel, FeatureType_Building, FeatureType_Storey};
    for (size_t i = 3; i < 8; i++) expected[i] = FeatureType_BuildingConstructiveElement;
    expected[8] = FeatureType_Storey;
    for (size_t i = 9; i < 15; i++) expected[i] = FeatureType_BuildingConstructiveElement;
    expected[15] = FeatureType_Appearance;
    for (size_t i = 16; i < 21; i++) expected[i] = FeatureType_ParameterizedTexture;
    for (size_t i = 21; i < 26; i++) expected[i] = FeatureType_X3DMaterial;
    FeatureType types[MAX_FEATURES];
    TEST_ASSERT_EQUAL_size_t(26, feature_types(city_model, types));
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, types, 26);
    TEST_ASSERT_EQUAL_size_t(14, count_city_objects(city_model));
    ecitygml_CityModel_destroy(city_model);
}

static void test_construction_building(void) {
    CityModel *city_model = read(CONSTRUCTION);
    const Building *b = first_building(city_model);
    ASSERT_STR(CONSTRUCTION_ID, ecitygml_Id_as_str(ecitygml_Building_feature_id(b)));
    CodeIterator *names = ecitygml_Building_names(b);
    ASSERT_STR("KIT FZK-Haus", ecitygml_Code_value(ecitygml_CodeIterator_next(names)));
    TEST_ASSERT_NULL(ecitygml_CodeIterator_next(names));
    ecitygml_CodeIterator_destroy(names);
    TEST_ASSERT_NULL(ecitygml_Building_class(b));
    BuildingFunctionValueIterator *functions = ecitygml_Building_functions(b);
    ASSERT_STR("31001_1000", ecitygml_BuildingFunctionValue_value(ecitygml_BuildingFunctionValueIterator_next(functions)));
    TEST_ASSERT_NULL(ecitygml_BuildingFunctionValueIterator_next(functions));
    ecitygml_BuildingFunctionValueIterator_destroy(functions);
    BuildingUsageValueIterator *usages = ecitygml_Building_usages(b);
    TEST_ASSERT_NULL(ecitygml_BuildingUsageValueIterator_next(usages));
    ecitygml_BuildingUsageValueIterator_destroy(usages);
    ASSERT_STR("3100", ecitygml_RoofTypeValue_value(ecitygml_Building_roof_type(b)));
    TEST_ASSERT_FALSE(ecitygml_Building_storeys_above_ground(b).is_ok);
    TEST_ASSERT_FALSE(ecitygml_Building_storeys_below_ground(b).is_ok);
    assert_height_and_occupancy(b);
    assert_no_boundaries(b);
    GenericAttributeKindIterator *attributes = ecitygml_Building_generic_attributes(b);
    TEST_ASSERT_NULL(ecitygml_GenericAttributeKindIterator_next(attributes));
    ecitygml_GenericAttributeKindIterator_destroy(attributes);
    TEST_ASSERT_NULL(ecitygml_Building_lod2_solid(b));
    TEST_ASSERT_NULL(ecitygml_Building_lod2_multi_surface(b));
    ecitygml_CityModel_destroy(city_model);
}

static void test_construction_storeys(void) {
    CityModel *city_model = read(CONSTRUCTION);
    AbstractBuildingSubdivisionPropertyIterator *subdivisions =
        ecitygml_Building_building_subdivisions(first_building(city_model));
    const AbstractBuildingSubdivisionProperty *subdivision;
    size_t count = 0;
    while ((subdivision = ecitygml_AbstractBuildingSubdivisionPropertyIterator_next(subdivisions)) != NULL) {
        TEST_ASSERT_NULL(ecitygml_AbstractBuildingSubdivisionProperty_href(subdivision));
        const AbstractBuildingSubdivisionKind *object = ecitygml_AbstractBuildingSubdivisionProperty_object(subdivision);
        TEST_ASSERT_NOT_NULL(object);
        TEST_ASSERT_EQUAL_INT(FeatureType_Storey, ecitygml_AbstractBuildingSubdivisionKind_feature_type(object));
        count++;
    }
    ecitygml_AbstractBuildingSubdivisionPropertyIterator_destroy(subdivisions);
    TEST_ASSERT_EQUAL_size_t(2, count);
    assert_storeys(city_model, (const char *const[]){"Entrance Floor", "non Entrance Floor"});
    const Storey *found[STOREYS];
    storeys(city_model, found);
    for (size_t i = 0; i < STOREYS; i++) {
        BuildingSubdivisionFunctionValueIterator *functions = ecitygml_Storey_functions(found[i]);
        TEST_ASSERT_NULL(ecitygml_BuildingSubdivisionFunctionValueIterator_next(functions));
        ecitygml_BuildingSubdivisionFunctionValueIterator_destroy(functions);
        BuildingSubdivisionUsageValueIterator *usages = ecitygml_Storey_usages(found[i]);
        TEST_ASSERT_NULL(ecitygml_BuildingSubdivisionUsageValueIterator_next(usages));
        ecitygml_BuildingSubdivisionUsageValueIterator_destroy(usages);
        AbstractSpaceBoundaryPropertyIterator *boundaries = ecitygml_Storey_boundaries(found[i]);
        TEST_ASSERT_NULL(ecitygml_AbstractSpaceBoundaryPropertyIterator_next(boundaries));
        ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(boundaries);
        TEST_ASSERT_NULL(ecitygml_Storey_lod2_solid(found[i]));
    }
    ecitygml_CityModel_destroy(city_model);
}

static void test_construction_round_trip(void) { assert_round_trip(CONSTRUCTION, CONSTRUCTION_ID); }

// 04-FZK-Haus-LoD2-Tex-Storey-CG30-V01-InteriorSurface.gml

static void test_interior_city_model(void) {
    CityModel *city_model = read(INTERIOR);
    assert_city_model(city_model, (const double[]){458900.0, 5438785.0, 113.5},
                      (const double[]){458912.0, 5438795.0, 120.017691});
    static const TypeCount expected[] = {
        {FeatureType_CityModel, 1},       {FeatureType_Building, 1},
        {FeatureType_Storey, 2},          {FeatureType_GroundSurface, 1},
        {FeatureType_WallSurface, 8},     {FeatureType_RoofSurface, 2},
        {FeatureType_BuildingRoom, 7},    {FeatureType_InteriorWallSurface, 27},
        {FeatureType_CeilingSurface, 8},  {FeatureType_FloorSurface, 7},
        {FeatureType_ClosureSurface, 6},  {FeatureType_Appearance, 1},
        {FeatureType_ParameterizedTexture, 5}, {FeatureType_X3DMaterial, 1},
    };
    FeatureType types[MAX_FEATURES];
    TEST_ASSERT_EQUAL_size_t(77, feature_types(city_model, types));
    assert_type_counts(city_model, expected, sizeof(expected) / sizeof(expected[0]));
    TEST_ASSERT_EQUAL_size_t(69, count_city_objects(city_model));
    ecitygml_CityModel_destroy(city_model);
}

static void test_interior_building(void) {
    CityModel *city_model = read(INTERIOR);
    const Building *b = first_building(city_model);
    ASSERT_STR(TEST_BUILDING_ID, ecitygml_Id_as_str(ecitygml_Building_feature_id(b)));
    CodeIterator *names = ecitygml_Building_names(b);
    ASSERT_STR("KIT Test Building FZK-Haus for CityGML 3.0", ecitygml_Code_value(ecitygml_CodeIterator_next(names)));
    TEST_ASSERT_NULL(ecitygml_CodeIterator_next(names));
    ecitygml_CodeIterator_destroy(names);
    TEST_ASSERT_NULL(ecitygml_Building_class(b));
    TEST_ASSERT_NULL(ecitygml_Building_roof_type(b));
    BuildingFunctionValueIterator *functions = ecitygml_Building_functions(b);
    TEST_ASSERT_NULL(ecitygml_BuildingFunctionValueIterator_next(functions));
    ecitygml_BuildingFunctionValueIterator_destroy(functions);
    BuildingUsageValueIterator *usages = ecitygml_Building_usages(b);
    TEST_ASSERT_NULL(ecitygml_BuildingUsageValueIterator_next(usages));
    ecitygml_BuildingUsageValueIterator_destroy(usages);
    assert_height_and_occupancy(b);
    GenericAttributeKindIterator *attributes = ecitygml_Building_generic_attributes(b);
    const GenericAttributeKind *attribute = ecitygml_GenericAttributeKindIterator_next(attributes);
    TEST_ASSERT_NOT_NULL(attribute);
    TEST_ASSERT_NULL(ecitygml_GenericAttributeKindIterator_next(attributes));
    ASSERT_STR("@cityeditor:layer", ecitygml_GenericAttributeKind_name(attribute));
    const StringAttribute *string = ecitygml_GenericAttributeKind_as_string(attribute);
    TEST_ASSERT_NOT_NULL(string);
    ASSERT_STR("LoD2-Ausgeblendet", ecitygml_StringAttribute_value(string));
    ecitygml_GenericAttributeKindIterator_destroy(attributes);
    assert_no_boundaries(b);
    ecitygml_CityModel_destroy(city_model);
}

static void test_interior_solid_unresolved(void) {
    CityModel *city_model = read(INTERIOR);
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
    TEST_ASSERT_EQUAL_size_t(11, count);
    ecitygml_Solid_volume_3d_result volume = ecitygml_Solid_volume_3d(solid);
    TEST_ASSERT_FALSE(volume.is_ok);
    ecitygml_Error_destroy(volume.err);
    ecitygml_CityModel_destroy(city_model);
}

static void test_interior_storey_boundaries(void) {
    static const ExpectedSurface ground_floor[] = {
        {FeatureType_GroundSurface, "Ground", 120.0},
        {FeatureType_WallSurface, "Ground Floor / Wall East", 29.0},
        {FeatureType_WallSurface, "Ground Floor / Wall South", 34.80000000447035},
        {FeatureType_WallSurface, "Ground Floor / Wall West", 29.0},
        {FeatureType_WallSurface, "Ground Floor / Wall North", 34.80000000447035},
    };
    static const ExpectedSurface second_floor[] = {
        {FeatureType_RoofSurface, "Second Floor / Roof South", 69.28203022609509},
        {FeatureType_RoofSurface, "Second Floor / Roof North", 69.28203022609509},
        {FeatureType_WallSurface, "Second Floor / Wall South", 8.771279998123646},
        {FeatureType_WallSurface, "Second Floor / Wall West", 21.743155002593994},
        {FeatureType_WallSurface, "Second Floor / Wall East", 21.743155002593994},
        {FeatureType_WallSurface, "Second Floor / Wall North", 8.771279998123646},
    };
    CityModel *city_model = read(INTERIOR);
    const Storey *found[STOREYS];
    storeys(city_model, found);
    assert_boundaries(found[0], ground_floor, sizeof(ground_floor) / sizeof(ground_floor[0]), true);
    assert_boundaries(found[1], second_floor, sizeof(second_floor) / sizeof(second_floor[0]), true);
    assert_storeys(city_model, (const char *const[]){NULL, NULL});
    ecitygml_CityModel_destroy(city_model);
}

static void test_interior_round_trip(void) { assert_round_trip(INTERIOR, TEST_BUILDING_ID); }

// 04-FZK-Haus-LoD2-Tex-Storey-Construction-CG30-V01-Window-Interior.gml

static void test_window_city_model(void) {
    CityModel *city_model = read(WINDOW);
    assert_city_model(city_model, (const double[]){458899.5, 5438784.5, 113.5},
                      (const double[]){458912.5, 5438795.5, 120.017691});
    static const TypeCount expected[] = {
        {FeatureType_CityModel, 1},  {FeatureType_Building, 1},
        {FeatureType_Storey, 2},     {FeatureType_BuildingConstructiveElement, 18},
        {FeatureType_Door, 5},       {FeatureType_Window, 11},
        {FeatureType_Appearance, 2}, {FeatureType_ParameterizedTexture, 5},
        {FeatureType_X3DMaterial, 9},
    };
    FeatureType types[MAX_FEATURES];
    TEST_ASSERT_EQUAL_size_t(54, feature_types(city_model, types));
    assert_type_counts(city_model, expected, sizeof(expected) / sizeof(expected[0]));
    TEST_ASSERT_EQUAL_size_t(37, count_city_objects(city_model));
    ecitygml_CityModel_destroy(city_model);
}

static void test_window_building(void) {
    CityModel *city_model = read(WINDOW);
    const Building *b = first_building(city_model);
    ASSERT_STR(WINDOW_ID, ecitygml_Id_as_str(ecitygml_Building_feature_id(b)));
    CodeIterator *names = ecitygml_Building_names(b);
    ASSERT_STR("KIT FZK-Haus", ecitygml_Code_value(ecitygml_CodeIterator_next(names)));
    TEST_ASSERT_NULL(ecitygml_CodeIterator_next(names));
    ecitygml_CodeIterator_destroy(names);
    BuildingFunctionValueIterator *functions = ecitygml_Building_functions(b);
    ASSERT_STR("31001_1000", ecitygml_BuildingFunctionValue_value(ecitygml_BuildingFunctionValueIterator_next(functions)));
    TEST_ASSERT_NULL(ecitygml_BuildingFunctionValueIterator_next(functions));
    ecitygml_BuildingFunctionValueIterator_destroy(functions);
    ASSERT_STR("3100", ecitygml_RoofTypeValue_value(ecitygml_Building_roof_type(b)));
    assert_no_boundaries(b);
    assert_storeys(city_model, (const char *const[]){"Entrance Floor", "non Entrance Floor"});
    ecitygml_CityModel_destroy(city_model);
}

static void test_window_round_trip(void) { assert_round_trip(WINDOW, WINDOW_ID); }

// 06-FZK-Haus-LoD2-Tex-Storey-CG30-V01-PointCloud-thinned.gml

static void test_point_cloud_city_model(void) {
    CityModel *city_model = read(POINT_CLOUD);
    assert_city_model(city_model, (const double[]){458900.0, 5438785.0, 113.5},
                      (const double[]){458912.0, 5438795.0, 120.017691});
    static const FeatureType expected[] = {
        FeatureType_CityModel,   FeatureType_Building,    FeatureType_Storey,      FeatureType_GroundSurface,
        FeatureType_WallSurface, FeatureType_WallSurface, FeatureType_WallSurface, FeatureType_WallSurface,
        FeatureType_Storey,      FeatureType_RoofSurface, FeatureType_RoofSurface, FeatureType_WallSurface,
        FeatureType_WallSurface, FeatureType_WallSurface, FeatureType_WallSurface,
    };
    FeatureType types[MAX_FEATURES];
    TEST_ASSERT_EQUAL_size_t(15, feature_types(city_model, types));
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, types, 15);
    ecitygml_CityModel_destroy(city_model);
}

static void test_point_cloud_storey_boundaries(void) {
    static const ExpectedSurface ground_floor[] = {
        {FeatureType_GroundSurface, " Ground Floor / GroundSurface", 0.0},
        {FeatureType_WallSurface, "Ground Floor / Wall East", 0.0},
        {FeatureType_WallSurface, "Ground Floor / Wall South", 0.0},
        {FeatureType_WallSurface, "Ground Floor / Wall West", 0.0},
        {FeatureType_WallSurface, "Ground Floor / Wall North", 0.0},
    };
    static const ExpectedSurface second_floor[] = {
        {FeatureType_RoofSurface, "Second Floor / Roof North", 0.0},
        {FeatureType_RoofSurface, "Second Floor / Roof South", 0.0},
        {FeatureType_WallSurface, "Second Floor / Wall South", 0.0},
        {FeatureType_WallSurface, "Second Floor / Wall West", 0.0},
        {FeatureType_WallSurface, "Second Floor / Wall East", 0.0},
        {FeatureType_WallSurface, "Second Floor / Wall North", 0.0},
    };
    CityModel *city_model = read(POINT_CLOUD);
    const Building *b = first_building(city_model);
    ASSERT_STR(TEST_BUILDING_ID, ecitygml_Id_as_str(ecitygml_Building_feature_id(b)));
    assert_no_boundaries(b);
    const Storey *found[STOREYS];
    storeys(city_model, found);
    assert_boundaries(found[0], ground_floor, sizeof(ground_floor) / sizeof(ground_floor[0]), false);
    assert_boundaries(found[1], second_floor, sizeof(second_floor) / sizeof(second_floor[0]), false);
    ecitygml_CityModel_destroy(city_model);
}

static void test_point_cloud_round_trip(void) { assert_round_trip(POINT_CLOUD, TEST_BUILDING_ID); }

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_construction_city_model);
    RUN_TEST(test_construction_building);
    RUN_TEST(test_construction_storeys);
    RUN_TEST(test_construction_round_trip);
    RUN_TEST(test_interior_city_model);
    RUN_TEST(test_interior_building);
    RUN_TEST(test_interior_solid_unresolved);
    RUN_TEST(test_interior_storey_boundaries);
    RUN_TEST(test_interior_round_trip);
    RUN_TEST(test_window_city_model);
    RUN_TEST(test_window_building);
    RUN_TEST(test_window_round_trip);
    RUN_TEST(test_point_cloud_city_model);
    RUN_TEST(test_point_cloud_storey_boundaries);
    RUN_TEST(test_point_cloud_round_trip);
    return UNITY_END();
}
