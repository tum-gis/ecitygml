#include "test_helpers.h"

#include "ErrorKind.h"

void setUp(void) {}
void tearDown(void) {}

static void test_reads_city_objects(void) {
    CityModel *city_model = read(FIXTURE("FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml"));
    TEST_ASSERT_EQUAL_size_t(1, ecitygml_CityModel_city_objects_len(city_model));
    ecitygml_CityModel_destroy(city_model);
}

static void test_missing_file(void) {
    ecitygml_GmlReader_from_path_result reader = ecitygml_GmlReader_from_path(view(FIXTURE("does-not-exist.gml")));
    TEST_ASSERT_FALSE(reader.is_ok);
    TEST_ASSERT_EQUAL_INT(ErrorKind_Io, ecitygml_Error_kind(reader.err));
    TEST_ASSERT_TRUE(message_contains(reader.err, "No such file"));
    ecitygml_Error_destroy(reader.err);
}

static void test_unsupported_extension(void) {
    ecitygml_GmlReader_from_path_result reader = ecitygml_GmlReader_from_path(view(FIXTURE("../../README.md")));
    TEST_ASSERT_FALSE(reader.is_ok);
    TEST_ASSERT_EQUAL_INT(ErrorKind_InvalidArgument, ecitygml_Error_kind(reader.err));
    ecitygml_Error_destroy(reader.err);
}

static void test_finish_only_once(void) {
    ecitygml_GmlReader_from_path_result reader =
        ecitygml_GmlReader_from_path(view(FIXTURE("FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml")));
    TEST_ASSERT_TRUE(reader.is_ok);
    ecitygml_GmlReader_with_rebuild_object_bounds(reader.ok, false);

    ecitygml_GmlReader_finish_result first = ecitygml_GmlReader_finish(reader.ok);
    TEST_ASSERT_TRUE(first.is_ok);
    ecitygml_CityModel_destroy(first.ok);

    ecitygml_GmlReader_finish_result second = ecitygml_GmlReader_finish(reader.ok);
    TEST_ASSERT_FALSE(second.is_ok);
    TEST_ASSERT_EQUAL_INT(ErrorKind_InvalidArgument, ecitygml_Error_kind(second.err));
    TEST_ASSERT_TRUE(message_contains(second.err, "already finished"));
    ecitygml_Error_destroy(second.err);
    ecitygml_GmlReader_destroy(reader.ok);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_reads_city_objects);
    RUN_TEST(test_missing_file);
    RUN_TEST(test_unsupported_extension);
    RUN_TEST(test_finish_only_once);
    return UNITY_END();
}
