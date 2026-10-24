// Helpers of the API suite (crates/ecitygml/tests/api/README.md).
#ifndef ECITYGML_C_API_H
#define ECITYGML_C_API_H

// `mkdtemp` is in unistd.h (macOS), which also declares a `read` of its own: renamed here, as test_helpers.h's `read`
// reads a city model.
#define read posix_read
#include <unistd.h>
#undef read

#include "test_helpers.h"

#include "AbstractFeatureKindRef.h"
#include "AbstractFeatureKindRefIterator.h"
#include "ErrorKind.h"
#include "FeatureType.h"

/// The most features a fixture of the API cases has.
#define MAX_FEATURES 64

/// Asserts the error's kind and that its message contains `part`, then destroys it.
static inline void assert_error(Error *error, ErrorKind kind, const char *part) {
    TEST_ASSERT_EQUAL_INT(kind, ecitygml_Error_kind(error));
    TEST_ASSERT_TRUE_MESSAGE(message_contains(error, part), part);
    ecitygml_Error_destroy(error);
}

/// The content of the file at `path`, into `*len`. Free it.
static inline uint8_t *read_bytes(const char *path, size_t *len) {
    FILE *file = fopen(path, "rb");
    TEST_ASSERT_NOT_NULL_MESSAGE(file, path);
    fseek(file, 0, SEEK_END);
    *len = (size_t)ftell(file);
    fseek(file, 0, SEEK_SET);
    uint8_t *data = malloc(*len);
    TEST_ASSERT_EQUAL_size_t(*len, fread(data, 1, *len, file));
    fclose(file);
    return data;
}

/// `GmlReader::new(data, format).finish()`; fails the test on errors. Destroy the model.
static inline CityModel *read_data(DiplomatU8View data, CitygmlFormat format) {
    GmlReader *reader = ecitygml_GmlReader_new(data, format);
    ecitygml_GmlReader_finish_result city_model = ecitygml_GmlReader_finish(reader);
    ecitygml_GmlReader_destroy(reader);
    TEST_ASSERT_TRUE(city_model.is_ok);
    return city_model.ok;
}

/// The feature types of `iter_features`, into `out`; returns their number.
static inline size_t feature_types(const CityModel *city_model, FeatureType *out) {
    size_t len = 0;
    AbstractFeatureKindRefIterator *features = ecitygml_CityModel_iter_features(city_model);
    AbstractFeatureKindRef *feature;
    while ((feature = ecitygml_AbstractFeatureKindRefIterator_next(features)) != NULL) {
        TEST_ASSERT_LESS_THAN_size_t(MAX_FEATURES, len);
        out[len++] = ecitygml_AbstractFeatureKindRef_feature_type(feature);
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractFeatureKindRefIterator_destroy(features);
    return len;
}

/// Asserts that both models have the same `iter_features` feature types in the same order.
static inline void assert_same_feature_types(const CityModel *expected, const CityModel *actual) {
    FeatureType expected_types[MAX_FEATURES], actual_types[MAX_FEATURES];
    size_t expected_len = feature_types(expected, expected_types);
    TEST_ASSERT_EQUAL_size_t(expected_len, feature_types(actual, actual_types));
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_types, actual_types, expected_len);
}

/// A fresh temporary directory, into `dir` (at least 64 bytes); remove it with `remove_temp_dir`.
static inline void make_temp_dir(char *dir) {
    const char *tmp = getenv("TMPDIR");
    snprintf(dir, 64, "%s/ecitygml-c-XXXXXX", tmp != NULL && strlen(tmp) < 40 ? tmp : "/tmp");
    TEST_ASSERT_NOT_NULL(mkdtemp(dir));
}

/// `<dir>/<name>`, into `path` (at least 128 bytes).
static inline const char *temp_path(char *path, const char *dir, const char *name) {
    snprintf(path, 128, "%s/%s", dir, name);
    return path;
}

/// Removes the files `names` (a NULL-terminated list) of the temporary directory, then the directory.
static inline void remove_temp_dir(const char *dir, const char *const *names) {
    char path[128];
    for (; *names != NULL; ++names) {
        remove(temp_path(path, dir, *names));
    }
    TEST_ASSERT_EQUAL_INT(0, remove(dir));  // POSIX: removes an empty directory
}

#endif
