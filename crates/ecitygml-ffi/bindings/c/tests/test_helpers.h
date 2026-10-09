#ifndef ECITYGML_C_TEST_HELPERS_H
#define ECITYGML_C_TEST_HELPERS_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "unity.h"

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

#endif
