#ifndef ECITYGML_C_TEST_HELPERS_H
#define ECITYGML_C_TEST_HELPERS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "unity.h"

#include "CitygmlFormat.h"
#include "CityModel.h"
#include "Error.h"
#include "GmlReader.h"

#define FIXTURE(name) ECITYGML_FIXTURES "/" name

static inline DiplomatStringView view(const char *text) { return (DiplomatStringView){text, strlen(text)}; }

/// Whether the error's message contains `text`.
static inline bool message_contains(const Error *error, const char *text) {
    DiplomatWrite *write = diplomat_buffer_write_create(64);
    ecitygml_Error_message(error, write);
    size_t len = diplomat_buffer_write_len(write);
    char *message = malloc(len + 1);
    memcpy(message, diplomat_buffer_write_get_bytes(write), len);
    message[len] = '\0';
    diplomat_buffer_write_destroy(write);
    bool contains = strstr(message, text) != NULL;
    free(message);
    return contains;
}

/// `GmlReader::from_path(path)?.finish()`, as in Rust; fails the test on errors. Destroy the model.
static inline CityModel *read(const char *path) {
    ecitygml_GmlReader_from_path_result reader = ecitygml_GmlReader_from_path(view(path));
    TEST_ASSERT_TRUE_MESSAGE(reader.is_ok, path);
    ecitygml_GmlReader_finish_result city_model = ecitygml_GmlReader_finish(reader.ok);
    ecitygml_GmlReader_destroy(reader.ok);
    TEST_ASSERT_TRUE_MESSAGE(city_model.is_ok, path);
    return city_model.ok;
}

/// Asserts that a borrowed string equals `expected` (length and content); evaluates each argument once.
#define ASSERT_STR(expected, actual)                                        \
    do {                                                                    \
        const char *expected_ = (expected);                                 \
        DiplomatStringView actual_ = (actual);                              \
        TEST_ASSERT_EQUAL_size_t(strlen(expected_), actual_.len);           \
        TEST_ASSERT_EQUAL_STRING_LEN(expected_, actual_.data, actual_.len); \
    } while (0)

/// Reads the fixture with the first `from` replaced by `to` (to inject content no fixture has); fails the test
/// on errors. Destroy the model.
static inline CityModel *read_modified(const char *path, const char *from, const char *to) {
    FILE *file = fopen(path, "rb");
    TEST_ASSERT_NOT_NULL_MESSAGE(file, path);
    fseek(file, 0, SEEK_END);
    size_t size = (size_t)ftell(file);
    fseek(file, 0, SEEK_SET);
    char *text = malloc(size + 1);
    TEST_ASSERT_EQUAL_size_t(size, fread(text, 1, size, file));
    text[size] = '\0';
    fclose(file);

    const char *anchor = strstr(text, from);
    TEST_ASSERT_NOT_NULL_MESSAGE(anchor, from);
    size_t prefix = (size_t)(anchor - text), from_len = strlen(from), to_len = strlen(to);
    size_t modified_len = size - from_len + to_len;
    uint8_t *modified = malloc(modified_len);
    memcpy(modified, text, prefix);
    memcpy(modified + prefix, to, to_len);
    memcpy(modified + prefix + to_len, anchor + from_len, size - prefix - from_len);
    free(text);

    GmlReader *reader = ecitygml_GmlReader_new((DiplomatU8View){modified, modified_len}, CitygmlFormat_Gml);
    ecitygml_GmlReader_finish_result city_model = ecitygml_GmlReader_finish(reader);
    ecitygml_GmlReader_destroy(reader);
    free(modified);
    TEST_ASSERT_TRUE_MESSAGE(city_model.is_ok, path);
    return city_model.ok;
}

#endif
