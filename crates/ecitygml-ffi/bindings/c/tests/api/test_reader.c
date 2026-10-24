// The cases of crates/ecitygml/tests/api/reader.md.
#include "api.h"

#include "WallSurface.h"

#define FZK_LOD1 FIXTURE("fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml")
#define FZK_LOD2 FIXTURE("fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml")

void setUp(void) {}
void tearDown(void) {}

static void reader_from_bytes(void) {
    size_t len;
    uint8_t *data = read_bytes(FZK_LOD1, &len);
    CityModel *city_model = read_data((DiplomatU8View){data, len}, CitygmlFormat_Gml);
    TEST_ASSERT_EQUAL_size_t(1, ecitygml_CityModel_city_objects_len(city_model));
    ecitygml_CityModel_destroy(city_model);
    free(data);
}

static void reader_compressed(void) {
    const char *paths[] = {FIXTURE("fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml.gz"),
                           FIXTURE("fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml.zst")};
    const CitygmlFormat formats[] = {CitygmlFormat_GmlGz, CitygmlFormat_GmlZst};
    for (size_t i = 0; i < 2; ++i) {
        CityModel *city_model = read(paths[i]);
        TEST_ASSERT_EQUAL_size_t(1, ecitygml_CityModel_city_objects_len(city_model));
        ecitygml_CityModel_destroy(city_model);

        size_t len;
        uint8_t *data = read_bytes(paths[i], &len);
        city_model = read_data((DiplomatU8View){data, len}, formats[i]);
        TEST_ASSERT_EQUAL_size_t(1, ecitygml_CityModel_city_objects_len(city_model));
        ecitygml_CityModel_destroy(city_model);
        free(data);
    }
}

static void reader_default_rebuilds_object_bounds(void) {
    CityModel *city_model = read(FZK_LOD2);
    size_t walls = 0;
    AbstractFeatureKindRefIterator *features = ecitygml_CityModel_iter_features(city_model);
    AbstractFeatureKindRef *feature;
    while ((feature = ecitygml_AbstractFeatureKindRefIterator_next(features)) != NULL) {
        const WallSurface *wall = ecitygml_WallSurface_try_from(feature);
        if (wall != NULL) {
            TEST_ASSERT_NOT_NULL(ecitygml_WallSurface_bounded_by(wall));
            ++walls;
        }
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractFeatureKindRefIterator_destroy(features);
    TEST_ASSERT_EQUAL_size_t(4, walls);
    ecitygml_CityModel_destroy(city_model);
}

static void reader_finish_once(void) {
    ecitygml_GmlReader_from_path_result reader = ecitygml_GmlReader_from_path(view(FZK_LOD1));
    TEST_ASSERT_TRUE(reader.is_ok);
    ecitygml_GmlReader_with_rebuild_object_bounds(reader.ok, false);

    ecitygml_GmlReader_finish_result first = ecitygml_GmlReader_finish(reader.ok);
    TEST_ASSERT_TRUE(first.is_ok);
    TEST_ASSERT_EQUAL_size_t(1, ecitygml_CityModel_city_objects_len(first.ok));
    ecitygml_CityModel_destroy(first.ok);

    ecitygml_GmlReader_finish_result second = ecitygml_GmlReader_finish(reader.ok);
    TEST_ASSERT_FALSE(second.is_ok);
    assert_error(second.err, ErrorKind_InvalidArgument, "already finished");
    ecitygml_GmlReader_destroy(reader.ok);
}

static void reader_missing_file(void) {
    ecitygml_GmlReader_from_path_result reader = ecitygml_GmlReader_from_path(view(FIXTURE("does-not-exist.gml")));
    TEST_ASSERT_FALSE(reader.is_ok);
    assert_error(reader.err, ErrorKind_Io, "No such file");
}

static void reader_unsupported_extension(void) {
    ecitygml_GmlReader_from_path_result reader = ecitygml_GmlReader_from_path(view(FIXTURE("README.md")));
    TEST_ASSERT_FALSE(reader.is_ok);
    assert_error(reader.err, ErrorKind_InvalidArgument, "md");
}

static void reader_non_utf8_path(void) {
    ecitygml_GmlReader_from_path_result reader = ecitygml_GmlReader_from_path(view("\xff.gml"));
    TEST_ASSERT_FALSE(reader.is_ok);
    assert_error(reader.err, ErrorKind_InvalidArgument, "`path`");
}

static void reader_invalid_content(void) {
    ecitygml_GmlReader_from_path_result reader = ecitygml_GmlReader_from_path(view(FIXTURE("invalid/unclosed-tag.gml")));
    TEST_ASSERT_TRUE(reader.is_ok);
    ecitygml_GmlReader_finish_result city_model = ecitygml_GmlReader_finish(reader.ok);
    TEST_ASSERT_FALSE(city_model.is_ok);
    assert_error(city_model.err, ErrorKind_Parse, "tag not closed");
    ecitygml_GmlReader_destroy(reader.ok);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(reader_from_bytes);
    RUN_TEST(reader_compressed);
    RUN_TEST(reader_default_rebuilds_object_bounds);
    RUN_TEST(reader_finish_once);
    RUN_TEST(reader_missing_file);
    RUN_TEST(reader_unsupported_extension);
    RUN_TEST(reader_non_utf8_path);
    RUN_TEST(reader_invalid_content);
    return UNITY_END();
}
