// The cases of crates/ecitygml/tests/api/iteration.md.
#include "api.h"

#define FZK_LOD3 FIXTURE("fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml")
#define ASAM_ROAD_SHAPE FIXTURE("asam-opendrive/ASAM-UC_RoadShape.gml")

void setUp(void) {}
void tearDown(void) {}

static void iterator_exhausted(void) {
    CityModel *city_model = read(FZK_LOD3);
    AbstractFeatureKindRefIterator *iterator = ecitygml_CityModel_iter_features(city_model);
    size_t count = 0;
    AbstractFeatureKindRef *feature;
    while ((feature = ecitygml_AbstractFeatureKindRefIterator_next(iterator)) != NULL) {
        ecitygml_AbstractFeatureKindRef_destroy(feature);
        count++;
    }
    TEST_ASSERT_EQUAL_size_t(22, count);
    TEST_ASSERT_NULL(ecitygml_AbstractFeatureKindRefIterator_next(iterator));
    ecitygml_AbstractFeatureKindRefIterator_destroy(iterator);
    ecitygml_CityModel_destroy(city_model);
}

static void iterator_stopped_early(void) {
    CityModel *city_model = read(ASAM_ROAD_SHAPE);
    AbstractFeatureKindRefIterator *iterator = ecitygml_CityModel_iter_features(city_model);
    AbstractFeatureKindRef *first = ecitygml_AbstractFeatureKindRefIterator_next(iterator);
    TEST_ASSERT_NOT_NULL(first);
    TEST_ASSERT_EQUAL_INT(FeatureType_CityModel, ecitygml_AbstractFeatureKindRef_feature_type(first));
    ecitygml_AbstractFeatureKindRef_destroy(first);
    ecitygml_AbstractFeatureKindRefIterator_destroy(iterator);
    FeatureType types[MAX_FEATURES];
    TEST_ASSERT_EQUAL_size_t(11, feature_types(city_model, types));
    TEST_ASSERT_EQUAL_size_t(1, ecitygml_CityModel_city_objects_len(city_model));
    ecitygml_CityModel_destroy(city_model);
}

static void iterators_independent(void) {
    CityModel *city_model = read(FZK_LOD3);
    AbstractFeatureKindRefIterator *first = ecitygml_CityModel_iter_features(city_model);
    AbstractFeatureKindRefIterator *second = ecitygml_CityModel_iter_features(city_model);
    FeatureType a[MAX_FEATURES];
    FeatureType b[MAX_FEATURES];
    size_t len = 0;
    for (;;) {
        AbstractFeatureKindRef *x = ecitygml_AbstractFeatureKindRefIterator_next(first);
        AbstractFeatureKindRef *y = ecitygml_AbstractFeatureKindRefIterator_next(second);
        TEST_ASSERT_EQUAL_INT(x == NULL, y == NULL);
        if (x == NULL || y == NULL) {
            break;
        }
        TEST_ASSERT_LESS_THAN_size_t(MAX_FEATURES, len);
        a[len] = ecitygml_AbstractFeatureKindRef_feature_type(x);
        b[len++] = ecitygml_AbstractFeatureKindRef_feature_type(y);
        ecitygml_AbstractFeatureKindRef_destroy(x);
        ecitygml_AbstractFeatureKindRef_destroy(y);
    }
    ecitygml_AbstractFeatureKindRefIterator_destroy(first);
    ecitygml_AbstractFeatureKindRefIterator_destroy(second);
    TEST_ASSERT_EQUAL_size_t(22, len);
    TEST_ASSERT_EQUAL_INT_ARRAY(a, b, len);
    FeatureType expected[MAX_FEATURES];
    TEST_ASSERT_EQUAL_size_t(len, feature_types(city_model, expected));
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, a, len);
    ecitygml_CityModel_destroy(city_model);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(iterator_exhausted);
    RUN_TEST(iterator_stopped_early);
    RUN_TEST(iterators_independent);
    return UNITY_END();
}
