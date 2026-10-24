// The cases of crates/ecitygml/tests/api/types.md.
#include "api.h"

#include <math.h>

#include "AbstractCityObjectKindRef.h"
#include "AbstractCityObjectKindRefIterator.h"
#include "AuxiliaryTrafficArea.h"
#include "AuxiliaryTrafficSpace.h"
#include "Building.h"
#include "BuildingClassValue.h"
#include "BuildingFunctionValue.h"
#include "BuildingFunctionValueIterator.h"
#include "BuildingUsageValue.h"
#include "BuildingUsageValueIterator.h"
#include "Code.h"
#include "CodeIterator.h"
#include "Date.h"
#include "DateTime.h"
#include "DirectPosition.h"
#include "DoorSurface.h"
#include "GroundSurface.h"
#include "Id.h"
#include "ImplicitGeometry.h"
#include "ImplicitGeometryProperty.h"
#include "LevelOfDetail.h"
#include "Road.h"
#include "RoofSurface.h"
#include "Section.h"
#include "SolitaryVegetationObject.h"
#include "TrafficArea.h"
#include "TrafficSpace.h"
#include "TransformationMatrix4x4.h"
#include "WallSurface.h"
#include "WindowSurface.h"

#define FZK_LOD1 FIXTURE("fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml")
#define FZK_LOD2 FIXTURE("fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml")
#define FZK_LOD3 FIXTURE("fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml")
#define TUM FIXTURE("tum-main-entrance/TUM-Main-Entrance.gml")
#define ASAM_ROAD_SHAPE FIXTURE("asam-opendrive/ASAM-UC_RoadShape.gml")
#define ASAM_JUNCTION FIXTURE("asam-opendrive/ASAM-Ex_Bidirectional_Junction.gml")
#define RAILWAY FIXTURE("railway-scene/Railway_Scene_LoD3__v3-thinned.gml")
#define SIG3D "http://www.sig3d.org/codelists/citygml/2.0/building/2.0/_AbstractBuilding_"

void setUp(void) {}
void tearDown(void) {}

/// Asserts what a `DateTime::to_rfc3339` writes.
static void assert_rfc3339(const char *expected, const DateTime *date_time) {
    DiplomatWrite *write = diplomat_buffer_write_create(32);
    ecitygml_DateTime_to_rfc3339(date_time, write);
    ASSERT_STR(expected, ((DiplomatStringView){diplomat_buffer_write_get_bytes(write), diplomat_buffer_write_len(write)}));
    diplomat_buffer_write_destroy(write);
}

/// Asserts what a `FeatureType::to_string` writes.
static void assert_name(const char *expected, FeatureType feature_type) {
    DiplomatWrite *write = diplomat_buffer_write_create(32);
    ecitygml_FeatureType_to_string(feature_type, write);
    ASSERT_STR(expected, ((DiplomatStringView){diplomat_buffer_write_get_bytes(write), diplomat_buffer_write_len(write)}));
    diplomat_buffer_write_destroy(write);
}

/// Asserts a code's code space; `expected` NULL for none.
static void assert_code_space(const char *expected, const Code *code) {
    ecitygml_Code_code_space_result code_space = ecitygml_Code_code_space(code);
    if (expected == NULL) {
        TEST_ASSERT_FALSE(code_space.is_ok);
    } else {
        TEST_ASSERT_TRUE(code_space.is_ok);
        ASSERT_STR(expected, code_space.ok);
    }
}

/// Declares `first_<T>`: the first feature `T::try_from` accepts (borrowed from the model), and `accepts_<T>`.
#define DEFINE_FIRST_OF(T)                                                                       \
    static const T *first_##T(const CityModel *city_model) {                                     \
        const T *found = NULL;                                                                   \
        AbstractFeatureKindRefIterator *iterator = ecitygml_CityModel_iter_features(city_model); \
        AbstractFeatureKindRef *feature;                                                         \
        while (found == NULL && (feature = ecitygml_AbstractFeatureKindRefIterator_next(iterator)) != NULL) { \
            found = ecitygml_##T##_try_from(feature);                                            \
            ecitygml_AbstractFeatureKindRef_destroy(feature);                                    \
        }                                                                                        \
        ecitygml_AbstractFeatureKindRefIterator_destroy(iterator);                               \
        TEST_ASSERT_NOT_NULL(found);                                                             \
        return found;                                                                            \
    }

#define DEFINE_ACCEPTS(T) \
    static bool accepts_##T(const AbstractFeatureKindRef *feature) { return ecitygml_##T##_try_from(feature) != NULL; }

DEFINE_FIRST_OF(Building)
DEFINE_FIRST_OF(WallSurface)

DEFINE_ACCEPTS(Building)
DEFINE_ACCEPTS(WallSurface)
DEFINE_ACCEPTS(RoofSurface)
DEFINE_ACCEPTS(GroundSurface)
DEFINE_ACCEPTS(DoorSurface)
DEFINE_ACCEPTS(WindowSurface)
DEFINE_ACCEPTS(Road)
DEFINE_ACCEPTS(Section)
DEFINE_ACCEPTS(TrafficSpace)
DEFINE_ACCEPTS(TrafficArea)
DEFINE_ACCEPTS(AuxiliaryTrafficSpace)
DEFINE_ACCEPTS(AuxiliaryTrafficArea)

typedef struct {
    bool (*accepts)(const AbstractFeatureKindRef *);
    FeatureType feature_type;
} Accepts;

/// `T::try_from` accepts exactly the features of its feature type.
static void assert_try_from_matches(const char *path, const Accepts *types, size_t len) {
    CityModel *city_model = read(path);
    AbstractFeatureKindRefIterator *iterator = ecitygml_CityModel_iter_features(city_model);
    AbstractFeatureKindRef *feature;
    while ((feature = ecitygml_AbstractFeatureKindRefIterator_next(iterator)) != NULL) {
        FeatureType feature_type = ecitygml_AbstractFeatureKindRef_feature_type(feature);
        for (size_t i = 0; i < len; i++) {
            TEST_ASSERT_EQUAL_INT(feature_type == types[i].feature_type, types[i].accepts(feature));
        }
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractFeatureKindRefIterator_destroy(iterator);
    ecitygml_CityModel_destroy(city_model);
}

static void direct_position_new(void) {
    ecitygml_DirectPosition_new_result position = ecitygml_DirectPosition_new(1.0, 2.0, 3.0);
    TEST_ASSERT_TRUE(position.is_ok);
    TEST_ASSERT_EQUAL_DOUBLE(1.0, ecitygml_DirectPosition_x(position.ok));
    TEST_ASSERT_EQUAL_DOUBLE(2.0, ecitygml_DirectPosition_y(position.ok));
    TEST_ASSERT_EQUAL_DOUBLE(3.0, ecitygml_DirectPosition_z(position.ok));
    ecitygml_DirectPosition_destroy(position.ok);

    ecitygml_DirectPosition_new_result invalid = ecitygml_DirectPosition_new(NAN, 0.0, 0.0);
    TEST_ASSERT_FALSE(invalid.is_ok);
    assert_error(invalid.err, ErrorKind_InvalidArgument, "non-finite");
}

static void level_of_detail_index(void) {
    const LevelOfDetail levels[] = {LevelOfDetail_Zero, LevelOfDetail_One, LevelOfDetail_Two, LevelOfDetail_Three};
    for (uint8_t index = 0; index < 4; index++) {
        TEST_ASSERT_EQUAL_size_t(index, ecitygml_LevelOfDetail_as_index(levels[index]));
        ecitygml_LevelOfDetail_try_from_result lod = ecitygml_LevelOfDetail_try_from(index);
        TEST_ASSERT_TRUE(lod.is_ok);
        TEST_ASSERT_EQUAL_INT(levels[index], lod.ok);
    }
    ecitygml_LevelOfDetail_try_from_result invalid = ecitygml_LevelOfDetail_try_from(4);
    TEST_ASSERT_FALSE(invalid.is_ok);
    assert_error(invalid.err, ErrorKind_InvalidArgument, "4");
}

static void feature_type_name(void) {
    assert_name("Building", FeatureType_Building);
    assert_name("TinRelief", FeatureType_TinRelief);
}

static void date_from_parts(void) {
    ecitygml_Date_from_parts_result date = ecitygml_Date_from_parts(2020, 1, 2, 3600);
    TEST_ASSERT_TRUE(date.is_ok);
    TEST_ASSERT_EQUAL_INT32(2020, ecitygml_Date_year(date.ok));
    TEST_ASSERT_EQUAL_UINT32(1, ecitygml_Date_month(date.ok));
    TEST_ASSERT_EQUAL_UINT32(2, ecitygml_Date_day(date.ok));
    TEST_ASSERT_EQUAL_INT32(3600, ecitygml_Date_offset_seconds(date.ok));
    DateTime *start = ecitygml_Date_start_of_day(date.ok);
    TEST_ASSERT_EQUAL_UINT32(0, ecitygml_DateTime_hour(start));
    TEST_ASSERT_EQUAL_UINT32(0, ecitygml_DateTime_minute(start));
    TEST_ASSERT_EQUAL_UINT32(0, ecitygml_DateTime_second(start));
    assert_rfc3339("2020-01-02T00:00:00+01:00", start);
    ecitygml_DateTime_destroy(start);
    ecitygml_Date_destroy(date.ok);

    ecitygml_Date_from_parts_result invalid = ecitygml_Date_from_parts(2021, 2, 30, 0);
    TEST_ASSERT_FALSE(invalid.is_ok);
    assert_error(invalid.err, ErrorKind_InvalidArgument, "do not form a valid date");
}

static void date_time_from_parts(void) {
    ecitygml_DateTime_from_parts_result result = ecitygml_DateTime_from_parts(2017, 1, 23, 13, 14, 15, 500000000, -7200);
    TEST_ASSERT_TRUE(result.is_ok);
    const DateTime *date_time = result.ok;
    TEST_ASSERT_EQUAL_INT32(2017, ecitygml_DateTime_year(date_time));
    TEST_ASSERT_EQUAL_UINT32(1, ecitygml_DateTime_month(date_time));
    TEST_ASSERT_EQUAL_UINT32(23, ecitygml_DateTime_day(date_time));
    TEST_ASSERT_EQUAL_UINT32(13, ecitygml_DateTime_hour(date_time));
    TEST_ASSERT_EQUAL_UINT32(14, ecitygml_DateTime_minute(date_time));
    TEST_ASSERT_EQUAL_UINT32(15, ecitygml_DateTime_second(date_time));
    TEST_ASSERT_EQUAL_UINT32(500000000, ecitygml_DateTime_nanosecond(date_time));
    TEST_ASSERT_EQUAL_INT32(-7200, ecitygml_DateTime_offset_seconds(date_time));
    TEST_ASSERT_EQUAL_INT64(1485184455, ecitygml_DateTime_timestamp(date_time));
    TEST_ASSERT_EQUAL_UINT32(500000000, ecitygml_DateTime_timestamp_subsec_nanos(date_time));
    assert_rfc3339("2017-01-23T13:14:15.500-02:00", date_time);
    ecitygml_DateTime_destroy(result.ok);

    ecitygml_DateTime_from_parts_result invalid = ecitygml_DateTime_from_parts(2020, 1, 1, 0, 0, 0, 0, 30);
    TEST_ASSERT_FALSE(invalid.is_ok);
    assert_error(invalid.err, ErrorKind_InvalidArgument, "timezone offset of 30 s is invalid");
}

static void date_time_read(void) {
    CityModel *city_model = read(FZK_LOD2);
    const DateTime *created = ecitygml_Building_creation_date(first_Building(city_model));
    TEST_ASSERT_NOT_NULL(created);
    assert_rfc3339("2017-01-23T00:00:00+01:00", created);
    ecitygml_CityModel_destroy(city_model);
}

static void try_from_matches_feature_type(void) {
    const Accepts lod3[] = {
        {accepts_Building, FeatureType_Building},           {accepts_WallSurface, FeatureType_WallSurface},
        {accepts_RoofSurface, FeatureType_RoofSurface},     {accepts_GroundSurface, FeatureType_GroundSurface},
        {accepts_DoorSurface, FeatureType_DoorSurface},     {accepts_WindowSurface, FeatureType_WindowSurface},
    };
    assert_try_from_matches(FZK_LOD3, lod3, sizeof(lod3) / sizeof(lod3[0]));
    const Accepts road_shape[] = {
        {accepts_Road, FeatureType_Road},
        {accepts_Section, FeatureType_Section},
        {accepts_TrafficSpace, FeatureType_TrafficSpace},
        {accepts_TrafficArea, FeatureType_TrafficArea},
        {accepts_AuxiliaryTrafficSpace, FeatureType_AuxiliaryTrafficSpace},
        {accepts_AuxiliaryTrafficArea, FeatureType_AuxiliaryTrafficArea},
    };
    assert_try_from_matches(ASAM_ROAD_SHAPE, road_shape, sizeof(road_shape) / sizeof(road_shape[0]));
}

static void feature_from_city_object(void) {
    CityModel *city_model = read(ASAM_JUNCTION);
    AbstractCityObjectKindRefIterator *city_objects = ecitygml_CityModel_iter_city_objects(city_model);
    AbstractCityObjectKindRef *city_object = ecitygml_AbstractCityObjectKindRefIterator_next(city_objects);
    TEST_ASSERT_NOT_NULL(city_object);
    TEST_ASSERT_EQUAL_INT(FeatureType_Road, ecitygml_AbstractCityObjectKindRef_feature_type(city_object));
    AbstractFeatureKindRef *feature = ecitygml_AbstractFeatureKindRef_from_city_object(city_object);
    TEST_ASSERT_EQUAL_INT(FeatureType_Road, ecitygml_AbstractFeatureKindRef_feature_type(feature));
    const Road *road = ecitygml_Road_try_from(feature);
    TEST_ASSERT_NOT_NULL(road);
    ASSERT_STR("UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f", ecitygml_Id_as_str(ecitygml_Road_feature_id(road)));
    TEST_ASSERT_NULL(ecitygml_Building_try_from(feature));
    ecitygml_AbstractFeatureKindRef_destroy(feature);
    ecitygml_AbstractCityObjectKindRef_destroy(city_object);
    ecitygml_AbstractCityObjectKindRefIterator_destroy(city_objects);
    ecitygml_CityModel_destroy(city_model);
}

static void matrix_index_out_of_range(void) {
    CityModel *city_model = read(RAILWAY);
    const SolitaryVegetationObject *tree = NULL;
    AbstractFeatureKindRefIterator *iterator = ecitygml_CityModel_iter_features(city_model);
    AbstractFeatureKindRef *feature;
    while ((feature = ecitygml_AbstractFeatureKindRefIterator_next(iterator)) != NULL) {
        const SolitaryVegetationObject *candidate = ecitygml_SolitaryVegetationObject_try_from(feature);
        if (candidate != NULL) {
            DiplomatStringView id = ecitygml_Id_as_str(ecitygml_SolitaryVegetationObject_feature_id(candidate));
            if (id.len == strlen("GMLID_SO092422_3593_9527") && memcmp(id.data, "GMLID_SO092422_3593_9527", id.len) == 0) {
                tree = candidate;
            }
        }
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractFeatureKindRefIterator_destroy(iterator);
    TEST_ASSERT_NOT_NULL(tree);
    const TransformationMatrix4x4 *matrix = ecitygml_ImplicitGeometry_transformation_matrix(
        ecitygml_ImplicitGeometryProperty_object(ecitygml_SolitaryVegetationObject_lod3_implicit_representation(tree)));
    ecitygml_TransformationMatrix4x4_get_result value = ecitygml_TransformationMatrix4x4_get(matrix, 3, 3);
    TEST_ASSERT_TRUE(value.is_ok);
    TEST_ASSERT_EQUAL_DOUBLE(1.0, value.ok);
    const size_t indices[][2] = {{4, 0}, {0, 4}};
    for (size_t i = 0; i < 2; i++) {
        ecitygml_TransformationMatrix4x4_get_result invalid =
            ecitygml_TransformationMatrix4x4_get(matrix, indices[i][0], indices[i][1]);
        TEST_ASSERT_FALSE(invalid.is_ok);
        assert_error(invalid.err, ErrorKind_InvalidArgument, "out of range");
    }
    ecitygml_CityModel_destroy(city_model);
}

static void gml_id(void) {
    CityModel *lod1 = read(FZK_LOD1);
    DiplomatStringView generated = ecitygml_Id_as_str(ecitygml_CityModel_feature_id(lod1));
    const char *prefix = "ecitygml-gen-feature-";
    TEST_ASSERT_TRUE(generated.len > strlen(prefix) && memcmp(generated.data, prefix, strlen(prefix)) == 0);
    const Id *id = ecitygml_CityModel_id(lod1);
    TEST_ASSERT_NOT_NULL(id);
    DiplomatStringView same = ecitygml_Id_as_str(id);
    TEST_ASSERT_EQUAL_size_t(generated.len, same.len);
    TEST_ASSERT_EQUAL_MEMORY(generated.data, same.data, generated.len);
    ecitygml_CityModel_destroy(lod1);

    CityModel *lod2 = read(FZK_LOD2);
    const WallSurface *wall = first_WallSurface(lod2);
    TEST_ASSERT_NOT_NULL(ecitygml_WallSurface_id(wall));
    ASSERT_STR("GML_5856d7ad-5e34-498a-817b-9544bfbb1475", ecitygml_Id_as_str(ecitygml_WallSurface_id(wall)));
    ASSERT_STR("GML_5856d7ad-5e34-498a-817b-9544bfbb1475", ecitygml_Id_as_str(ecitygml_WallSurface_feature_id(wall)));
    ecitygml_CityModel_destroy(lod2);

    CityModel *tum = read(TUM);
    const Id *building_id = ecitygml_Building_id(first_Building(tum));
    TEST_ASSERT_NOT_NULL(building_id);
    ASSERT_STR("DEBY_LOD2_4959457", ecitygml_Id_as_str(building_id));
    ecitygml_CityModel_destroy(tum);
}

static void code_space(void) {
    CityModel *lod2 = read(FZK_LOD2);
    const Building *building = first_Building(lod2);
    const Code *class_code = ecitygml_BuildingClassValue_code(ecitygml_Building_class(building));
    ASSERT_STR("1000", ecitygml_Code_value(class_code));
    assert_code_space(SIG3D "class.xml", class_code);
    BuildingFunctionValueIterator *functions = ecitygml_Building_functions(building);
    assert_code_space(SIG3D "function.xml",
                      ecitygml_BuildingFunctionValue_code(ecitygml_BuildingFunctionValueIterator_next(functions)));
    TEST_ASSERT_NULL(ecitygml_BuildingFunctionValueIterator_next(functions));
    ecitygml_BuildingFunctionValueIterator_destroy(functions);
    BuildingUsageValueIterator *usages = ecitygml_Building_usages(building);
    assert_code_space(SIG3D "usage.xml", ecitygml_BuildingUsageValue_code(ecitygml_BuildingUsageValueIterator_next(usages)));
    TEST_ASSERT_NULL(ecitygml_BuildingUsageValueIterator_next(usages));
    ecitygml_BuildingUsageValueIterator_destroy(usages);
    ecitygml_CityModel_destroy(lod2);

    CityModel *tum = read(TUM);
    BuildingFunctionValueIterator *tum_functions = ecitygml_Building_functions(first_Building(tum));
    const BuildingFunctionValue *function = ecitygml_BuildingFunctionValueIterator_next(tum_functions);
    ASSERT_STR("31001_3020", ecitygml_BuildingFunctionValue_value(function));
    assert_code_space(NULL, ecitygml_BuildingFunctionValue_code(function));
    TEST_ASSERT_NULL(ecitygml_BuildingFunctionValueIterator_next(tum_functions));
    ecitygml_BuildingFunctionValueIterator_destroy(tum_functions);
    ecitygml_CityModel_destroy(tum);

    CityModel *lod1 = read(FZK_LOD1);
    CodeIterator *names = ecitygml_CityModel_names(lod1);
    const Code *name = ecitygml_CodeIterator_next(names);
    ASSERT_STR("AC14-FZK-Haus", ecitygml_Code_value(name));
    assert_code_space(NULL, name);
    TEST_ASSERT_NULL(ecitygml_CodeIterator_next(names));
    ecitygml_CodeIterator_destroy(names);
    ecitygml_CityModel_destroy(lod1);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(direct_position_new);
    RUN_TEST(level_of_detail_index);
    RUN_TEST(feature_type_name);
    RUN_TEST(date_from_parts);
    RUN_TEST(date_time_from_parts);
    RUN_TEST(date_time_read);
    RUN_TEST(try_from_matches_feature_type);
    RUN_TEST(feature_from_city_object);
    RUN_TEST(matrix_index_out_of_range);
    RUN_TEST(gml_id);
    RUN_TEST(code_space);
    return UNITY_END();
}
