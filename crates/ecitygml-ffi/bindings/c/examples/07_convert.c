// Converts a CityGML file: reads it and writes it again, e.g. compressed or indented.
//
// Shows writing with `GmlWriter`: `from_path` creates the output file and picks the format from its
// extension (`.gml`, `.gml.gz` or `.gml.zst`), `with_formatting` sets the layout (here indented by two
// spaces; `ecitygml_Formatting_compact` writes no line breaks at all), and `finish` writes the city
// model. Reading the written file back verifies the result.
//
// Built by bindings/c/CMakeLists.txt (`mise run build:bindings:c`), which also runs it as a test.
//
// Usage: 07_convert input.gml output.gml.gz
//
// Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml, converted to a .gml.gz file:
//
//     Read: 1 city object members, 8 city objects
//     Wrote: gzip-compressed CityGML, indented by 2 spaces
//     Read back: 1 city object members, 8 city objects

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "AbstractCityObjectKindRef.h"
#include "AbstractCityObjectKindRefIterator.h"
#include "CityModel.h"
#include "Error.h"
#include "Formatting.h"
#include "GmlReader.h"
#include "GmlWriter.h"

#define INDENT_SIZE 2

static int print_error(Error *error) {
    DiplomatWrite *message = diplomat_buffer_write_create(64);
    ecitygml_Error_message(error, message);
    fprintf(stderr, "error: %.*s\n", (int)diplomat_buffer_write_len(message), diplomat_buffer_write_get_bytes(message));
    diplomat_buffer_write_destroy(message);
    ecitygml_Error_destroy(error);
    return 1;
}

// Reads a city model, or prints the error and returns NULL. The caller destroys the city model.
static CityModel *read(const char *path) {
    ecitygml_GmlReader_from_path_result reader = ecitygml_GmlReader_from_path((DiplomatStringView){path, strlen(path)});
    if (!reader.is_ok) {
        print_error(reader.err);
        return NULL;
    }
    ecitygml_GmlReader_finish_result result = ecitygml_GmlReader_finish(reader.ok);
    ecitygml_GmlReader_destroy(reader.ok);
    if (!result.is_ok) {
        print_error(result.err);
        return NULL;
    }
    return result.ok;
}

static void print_summary(const char *label, const CityModel *city_model) {
    size_t city_objects = 0;
    AbstractCityObjectKindRefIterator *iterator = ecitygml_CityModel_iter_city_objects(city_model);
    AbstractCityObjectKindRef *city_object;
    while ((city_object = ecitygml_AbstractCityObjectKindRefIterator_next(iterator)) != NULL) {
        ecitygml_AbstractCityObjectKindRef_destroy(city_object);
        ++city_objects;
    }
    ecitygml_AbstractCityObjectKindRefIterator_destroy(iterator);
    printf("%s: %zu city object members, %zu city objects\n", label, ecitygml_CityModel_city_objects_len(city_model),
           city_objects);
}

static bool ends_with(const char *text, const char *suffix) {
    size_t text_length = strlen(text);
    size_t suffix_length = strlen(suffix);
    return text_length >= suffix_length && strcmp(text + text_length - suffix_length, suffix) == 0;
}

// What `ecitygml_GmlWriter_from_path` writes for this path (it fails for other extensions).
static const char *format_name(const char *path) {
    if (ends_with(path, ".gml.gz")) {
        return "gzip-compressed CityGML";
    }
    if (ends_with(path, ".gml.zst")) {
        return "zstd-compressed CityGML";
    }
    return "CityGML";
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "usage: 07_convert input.gml output.gml[.gz|.zst]\n");
        return 2;
    }
    const char *output_path = argv[2];
    CityModel *city_model = read(argv[1]);
    if (city_model == NULL) {
        return 1;
    }
    print_summary("Read", city_model);

    ecitygml_GmlWriter_from_path_result writer = ecitygml_GmlWriter_from_path((DiplomatStringView){output_path, strlen(output_path)});
    if (!writer.is_ok) {
        ecitygml_CityModel_destroy(city_model);
        return print_error(writer.err);
    }
    Formatting *formatting = ecitygml_Formatting_indent(' ', INDENT_SIZE);
    ecitygml_GmlWriter_with_formatting(writer.ok, formatting);
    ecitygml_Formatting_destroy(formatting);
    ecitygml_GmlWriter_finish_result finished = ecitygml_GmlWriter_finish(writer.ok, city_model);
    ecitygml_GmlWriter_destroy(writer.ok);  // also closes the file
    ecitygml_CityModel_destroy(city_model);
    if (!finished.is_ok) {
        return print_error(finished.err);
    }
    printf("Wrote: %s, indented by %d spaces\n", format_name(output_path), INDENT_SIZE);

    CityModel *written = read(output_path);
    if (written == NULL) {
        return 1;
    }
    print_summary("Read back", written);
    ecitygml_CityModel_destroy(written);
    return 0;
}
