#include "test_helpers.h"

#include "AbstractFeatureKindRef.h"
#include "AbstractFeatureKindRefIterator.h"
#include "GranularityValue.h"
#include "Solid.h"
#include "SolidProperty.h"
#include "TrafficDirectionValue.h"
#include "TrafficSpace.h"
#include "TrafficSpaceFunctionValue.h"
#include "TrafficSpaceFunctionValueIterator.h"

void setUp(void) {}
void tearDown(void) {}

static void test_traffic_spaces(void) {
    CityModel *city_model = read(FIXTURE("ASAM-UC_RoadShape.gml"));
    size_t spaces = 0;
    size_t forwards = 0;
    double total_volume = 0.0;

    AbstractFeatureKindRefIterator *features = ecitygml_CityModel_iter_features(city_model);
    AbstractFeatureKindRef *feature;
    while ((feature = ecitygml_AbstractFeatureKindRefIterator_next(features)) != NULL) {
        const TrafficSpace *space = ecitygml_TrafficSpace_try_from(feature);
        if (space != NULL) {
            spaces++;
            TEST_ASSERT_EQUAL_INT(GranularityValue_Lane, ecitygml_TrafficSpace_granularity(space));
            ecitygml_TrafficSpace_traffic_direction_result direction = ecitygml_TrafficSpace_traffic_direction(space);
            TEST_ASSERT_TRUE(direction.is_ok);
            forwards += direction.ok == TrafficDirectionValue_Forwards;

            TrafficSpaceFunctionValueIterator *functions = ecitygml_TrafficSpace_functions(space);
            const TrafficSpaceFunctionValue *function = ecitygml_TrafficSpaceFunctionValueIterator_next(functions);
            TEST_ASSERT_NOT_NULL(function);
            DiplomatStringView value = ecitygml_TrafficSpaceFunctionValue_value(function);
            TEST_ASSERT_EQUAL_STRING_LEN("1", value.data, value.len);
            TEST_ASSERT_NULL(ecitygml_TrafficSpaceFunctionValueIterator_next(functions));
            ecitygml_TrafficSpaceFunctionValueIterator_destroy(functions);

            const SolidProperty *lod2_solid = ecitygml_TrafficSpace_lod2_solid(space);
            TEST_ASSERT_NOT_NULL(lod2_solid);
            ecitygml_Solid_volume_3d_result volume = ecitygml_Solid_volume_3d(ecitygml_SolidProperty_object(lod2_solid));
            TEST_ASSERT_TRUE(volume.is_ok);
            total_volume += volume.ok;
        }
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractFeatureKindRefIterator_destroy(features);
    ecitygml_CityModel_destroy(city_model);

    TEST_ASSERT_EQUAL_size_t(2, spaces);
    TEST_ASSERT_EQUAL_size_t(1, forwards);
    TEST_ASSERT_DOUBLE_WITHIN(1e-6, 1260.0, total_volume);
}

static void test_iterator_destroyed_early(void) {
    // Destroying an iterator before it is exhausted must free everything it holds.
    CityModel *city_model = read(FIXTURE("ASAM-UC_RoadShape.gml"));
    AbstractFeatureKindRefIterator *features = ecitygml_CityModel_iter_features(city_model);
    AbstractFeatureKindRef *feature = ecitygml_AbstractFeatureKindRefIterator_next(features);
    TEST_ASSERT_NOT_NULL(feature);
    ecitygml_AbstractFeatureKindRef_destroy(feature);
    ecitygml_AbstractFeatureKindRefIterator_destroy(features);
    ecitygml_CityModel_destroy(city_model);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_traffic_spaces);
    RUN_TEST(test_iterator_destroyed_early);
    return UNITY_END();
}
