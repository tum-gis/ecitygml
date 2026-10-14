#include "test_helpers.h"

#include <math.h>

#include "BoundingShape.h"
#include "DirectPosition.h"
#include "Envelope.h"
#include "Scale3.h"
#include "Vector3.h"
#include "ErrorKind.h"

void setUp(void) {}
void tearDown(void) {}

static void test_city_model_envelope(void) {
    CityModel *city_model = read(FIXTURE("FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml"));
    const BoundingShape *bounding_shape = ecitygml_CityModel_bounded_by(city_model);
    TEST_ASSERT_NOT_NULL(bounding_shape);
    const Envelope *envelope = ecitygml_BoundingShape_envelope(bounding_shape);
    TEST_ASSERT_NOT_NULL(envelope);
    TEST_ASSERT_EQUAL_DOUBLE(12.0, ecitygml_Envelope_size_x(envelope));
    TEST_ASSERT_EQUAL_DOUBLE(10.0, ecitygml_Envelope_size_y(envelope));
    TEST_ASSERT_DOUBLE_WITHIN(1e-9, 6.517669, ecitygml_Envelope_size_z(envelope));

    const DirectPosition *lower = ecitygml_Envelope_lower_corner(envelope);
    TEST_ASSERT_EQUAL_DOUBLE(457842.0, ecitygml_DirectPosition_x(lower));
    TEST_ASSERT_EQUAL_DOUBLE(111.8, ecitygml_DirectPosition_z(lower));
    ecitygml_CityModel_destroy(city_model);
}

static void test_apply_translation_and_scale(void) {
    CityModel *city_model = read(FIXTURE("FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml"));
    const DirectPosition *lower = ecitygml_Envelope_lower_corner(ecitygml_BoundingShape_envelope(ecitygml_CityModel_bounded_by(city_model)));
    double x = ecitygml_DirectPosition_x(lower), y = ecitygml_DirectPosition_y(lower), z = ecitygml_DirectPosition_z(lower);

    ecitygml_CityModel_apply_translation(city_model, (Vector3){-100.0, 200.0, 10.0});
    lower = ecitygml_Envelope_lower_corner(ecitygml_BoundingShape_envelope(ecitygml_CityModel_bounded_by(city_model)));
    TEST_ASSERT_DOUBLE_WITHIN(1e-6, x - 100.0, ecitygml_DirectPosition_x(lower));
    TEST_ASSERT_DOUBLE_WITHIN(1e-6, y + 200.0, ecitygml_DirectPosition_y(lower));
    TEST_ASSERT_DOUBLE_WITHIN(1e-6, z + 10.0, ecitygml_DirectPosition_z(lower));

    ecitygml_CityModel_apply_scale(city_model, (Scale3){2.0, 3.0, 0.5});
    const Envelope *envelope = ecitygml_BoundingShape_envelope(ecitygml_CityModel_bounded_by(city_model));
    TEST_ASSERT_DOUBLE_WITHIN(1e-6, 24.0, ecitygml_Envelope_size_x(envelope));
    TEST_ASSERT_DOUBLE_WITHIN(1e-6, 30.0, ecitygml_Envelope_size_y(envelope));
    TEST_ASSERT_DOUBLE_WITHIN(1e-6, 6.517669 / 2.0, ecitygml_Envelope_size_z(envelope));
    ecitygml_CityModel_destroy(city_model);
}

static void test_direct_position_new(void) {
    ecitygml_DirectPosition_new_result position = ecitygml_DirectPosition_new(1.0, 2.0, 3.0);
    TEST_ASSERT_TRUE(position.is_ok);
    TEST_ASSERT_EQUAL_DOUBLE(2.0, ecitygml_DirectPosition_y(position.ok));
    ecitygml_DirectPosition_destroy(position.ok);

    ecitygml_DirectPosition_new_result invalid = ecitygml_DirectPosition_new(NAN, 0.0, 0.0);
    TEST_ASSERT_FALSE(invalid.is_ok);
    TEST_ASSERT_EQUAL_INT(ErrorKind_InvalidArgument, ecitygml_Error_kind(invalid.err));
    TEST_ASSERT_TRUE(message_contains(invalid.err, "non-finite"));
    ecitygml_Error_destroy(invalid.err);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_city_model_envelope);
    RUN_TEST(test_apply_translation_and_scale);
    RUN_TEST(test_direct_position_new);
    return UNITY_END();
}
