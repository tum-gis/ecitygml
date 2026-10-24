// The cases of crates/ecitygml/tests/api/writer.md.
#include "api.h"

#include "Formatting.h"
#include "AbstractSurfaceKind.h"
#include "AbstractSurfaceProperty.h"
#include "AbstractSurfacePropertyIterator.h"
#include "DirectPosition.h"
#include "DirectPositionIterator.h"
#include "GmlWriter.h"
#include "LinearRing.h"
#include "MultiSurface.h"
#include "MultiSurfaceProperty.h"
#include "Polygon.h"
#include "WallSurface.h"

static CityModel *model;

void setUp(void) { model = read(FIXTURE("fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml")); }
void tearDown(void) { ecitygml_CityModel_destroy(model); }

/// Asserts that the file at `path` reads back.
static void assert_reads_back(const char *path) {
    CityModel *written = read(path);
    assert_same_feature_types(model, written);
    ecitygml_CityModel_destroy(written);
}

/// Writes the model with `writer`, then destroys the writer.
static void write_and_destroy(GmlWriter *writer) {
    ecitygml_GmlWriter_finish_result result = ecitygml_GmlWriter_finish(writer, model);
    TEST_ASSERT_TRUE(result.is_ok);
    ecitygml_GmlWriter_destroy(writer);
}

/// The model written as `Gml` text with `formatting` (none: the default), which is destroyed. Free the text.
static char *text(Formatting *formatting) {
    GmlWriter *writer = ecitygml_GmlWriter_new(CitygmlFormat_Gml);
    if (formatting != NULL) {
        ecitygml_GmlWriter_with_formatting(writer, formatting);
        ecitygml_Formatting_destroy(formatting);
    }
    TEST_ASSERT_TRUE(ecitygml_GmlWriter_finish(writer, model).is_ok);
    DiplomatU8View data = ecitygml_GmlWriter_data(writer);
    char *text = malloc(data.len + 1);
    memcpy(text, data.data, data.len);
    text[data.len] = '\0';
    ecitygml_GmlWriter_destroy(writer);
    return text;
}

static size_t line_count(const char *text) {
    size_t lines = 1;
    for (; *text != '\0'; ++text) {
        lines += *text == '\n' && text[1] != '\0';
    }
    return lines;
}

/// Whether a line of `text` starts with `prefix`.
static bool any_line_starts_with(const char *text, const char *prefix) {
    for (const char *line = text; line != NULL; line = strchr(line, '\n') != NULL ? strchr(line, '\n') + 1 : NULL) {
        if (strncmp(line, prefix, strlen(prefix)) == 0) {
            return true;
        }
    }
    return false;
}

static void writer_in_memory(void) {
    const CitygmlFormat formats[] = {CitygmlFormat_Gml, CitygmlFormat_GmlGz, CitygmlFormat_GmlZst};
    for (size_t i = 0; i < 3; ++i) {
        GmlWriter *writer = ecitygml_GmlWriter_new(formats[i]);
        TEST_ASSERT_EQUAL_size_t(0, ecitygml_GmlWriter_data(writer).len);
        TEST_ASSERT_TRUE(ecitygml_GmlWriter_finish(writer, model).is_ok);
        CityModel *written = read_data(ecitygml_GmlWriter_data(writer), formats[i]);
        assert_same_feature_types(model, written);
        ecitygml_CityModel_destroy(written);
        ecitygml_GmlWriter_destroy(writer);
    }
    char *plain = text(NULL);
    TEST_ASSERT_NOT_NULL(strstr(plain, "<bldg:Building"));
    free(plain);
}

static void writer_files(void) {
    char dir[64], path[128];
    make_temp_dir(dir);
    const char *const names[] = {"out.gml", "out.gml.gz", "out.gml.zst", NULL};
    for (size_t i = 0; names[i] != NULL; ++i) {
        ecitygml_GmlWriter_from_path_result writer = ecitygml_GmlWriter_from_path(view(temp_path(path, dir, names[i])));
        TEST_ASSERT_TRUE(writer.is_ok);
        write_and_destroy(writer.ok);
        assert_reads_back(path);
    }
    remove_temp_dir(dir, names);
}

/// Fills the file at `path` with 100 000 × `x`.
static void write_junk(const char *path) {
    FILE *file = fopen(path, "wb");
    TEST_ASSERT_NOT_NULL_MESSAGE(file, path);
    for (size_t i = 0; i < 100000; ++i) {
        fputc('x', file);
    }
    fclose(file);
}

static void writer_overwrites_file(void) {
    char dir[64], path[128];
    make_temp_dir(dir);
    write_junk(temp_path(path, dir, "out.gml"));
    ecitygml_GmlWriter_from_path_result writer = ecitygml_GmlWriter_from_path(view(path));
    TEST_ASSERT_TRUE(writer.is_ok);
    write_and_destroy(writer.ok);
    assert_reads_back(path);
    remove_temp_dir(dir, (const char *const[]){"out.gml", NULL});
}

static void writer_base_path_with_format(void) {
    char dir[64], path[128];
    make_temp_dir(dir);
    write_junk(temp_path(path, dir, "out.gml.gz"));
    ecitygml_GmlWriter_from_base_path_with_format_result writer =
        ecitygml_GmlWriter_from_base_path_with_format(view(temp_path(path, dir, "out")), CitygmlFormat_GmlGz);
    TEST_ASSERT_TRUE(writer.is_ok);
    write_and_destroy(writer.ok);
    assert_reads_back(temp_path(path, dir, "out.gml.gz"));
    remove_temp_dir(dir, (const char *const[]){"out.gml.gz", NULL});
}

static void writer_formatting(void) {
    char *default_text = text(NULL);
    TEST_ASSERT_GREATER_THAN_size_t(1, line_count(default_text));
    TEST_ASSERT_FALSE(any_line_starts_with(default_text, " "));
    TEST_ASSERT_FALSE(any_line_starts_with(default_text, "\t"));

    char *new_line = text(ecitygml_Formatting_new_line());
    TEST_ASSERT_EQUAL_STRING(default_text, new_line);
    char *indent_zero = text(ecitygml_Formatting_indent(' ', 0));
    TEST_ASSERT_EQUAL_STRING(default_text, indent_zero);

    char *compact = text(ecitygml_Formatting_compact());
    TEST_ASSERT_LESS_THAN_size_t(line_count(default_text), line_count(compact));

    char *spaces = text(ecitygml_Formatting_indent(' ', 2));
    TEST_ASSERT_TRUE(any_line_starts_with(spaces, "  <"));
    TEST_ASSERT_FALSE(any_line_starts_with(spaces, "\t"));

    char *tabs = text(ecitygml_Formatting_indent('\t', 1));
    TEST_ASSERT_TRUE(any_line_starts_with(tabs, "\t<"));
    CityModel *written = read_data((DiplomatU8View){(const uint8_t *)tabs, strlen(tabs)}, CitygmlFormat_Gml);
    assert_same_feature_types(model, written);
    ecitygml_CityModel_destroy(written);

    free(default_text);
    free(new_line);
    free(indent_zero);
    free(compact);
    free(spaces);
    free(tabs);
}

static void writer_finish_once(void) {
    GmlWriter *writer = ecitygml_GmlWriter_new(CitygmlFormat_Gml);
    TEST_ASSERT_TRUE(ecitygml_GmlWriter_finish(writer, model).is_ok);
    ecitygml_GmlWriter_finish_result again = ecitygml_GmlWriter_finish(writer, model);
    TEST_ASSERT_FALSE(again.is_ok);
    assert_error(again.err, ErrorKind_InvalidArgument, "already finished");
    ecitygml_GmlWriter_destroy(writer);
}

static void writer_unsupported_extension(void) {
    char dir[64], path[128];
    make_temp_dir(dir);
    ecitygml_GmlWriter_from_path_result writer = ecitygml_GmlWriter_from_path(view(temp_path(path, dir, "out.txt")));
    TEST_ASSERT_FALSE(writer.is_ok);
    assert_error(writer.err, ErrorKind_InvalidArgument, "txt");
    remove_temp_dir(dir, (const char *const[]){NULL});
}

static void writer_missing_directory(void) {
    char dir[64], path[128];
    make_temp_dir(dir);
    ecitygml_GmlWriter_from_path_result writer =
        ecitygml_GmlWriter_from_path(view(temp_path(path, dir, "missing/out.gml")));
    TEST_ASSERT_FALSE(writer.is_ok);
    assert_error(writer.err, ErrorKind_Io, "");
    remove_temp_dir(dir, (const char *const[]){NULL});
}

#define FZK_LOD2 FIXTURE("fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml")
/// The most wall coordinates of FZK LoD2.
#define MAX_COORDINATES 64

/// A city model written as `Gml` text. Free the text.
static char *text_of(const CityModel *city_model) {
    GmlWriter *writer = ecitygml_GmlWriter_new(CitygmlFormat_Gml);
    TEST_ASSERT_TRUE(ecitygml_GmlWriter_finish(writer, city_model).is_ok);
    DiplomatU8View data = ecitygml_GmlWriter_data(writer);
    char *written = malloc(data.len + 1);
    memcpy(written, data.data, data.len);
    written[data.len] = '\0';
    ecitygml_GmlWriter_destroy(writer);
    return written;
}

static size_t occurrences(const char *text, const char *part) {
    size_t n = 0;
    for (const char *at = strstr(text, part); at != NULL; at = strstr(at + strlen(part), part)) n++;
    return n;
}

static void writer_keeps_references(void) {
    CityModel *city_model = read(FZK_LOD2);
    char *written = text_of(city_model);
    TEST_ASSERT_EQUAL_size_t(1, occurrences(written, "xlink:href=\"#PolyID7350_878_759628_120742\""));
    TEST_ASSERT_EQUAL_size_t(1, occurrences(written, "gml:id=\"PolyID7350_878_759628_120742\""));
    free(written);
    ecitygml_CityModel_destroy(city_model);
}

/// The exterior ring positions (x, y, z) of every polygon of the wall surfaces' LoD2 multi surfaces, in document
/// order, into `out`; returns their number.
static size_t wall_coordinates(const CityModel *city_model, double out[][3]) {
    size_t len = 0;
    AbstractFeatureKindRefIterator *features = ecitygml_CityModel_iter_features(city_model);
    AbstractFeatureKindRef *feature;
    while ((feature = ecitygml_AbstractFeatureKindRefIterator_next(features)) != NULL) {
        const WallSurface *wall = ecitygml_WallSurface_try_from(feature);
        const MultiSurfaceProperty *property = wall != NULL ? ecitygml_WallSurface_lod2_multi_surface(wall) : NULL;
        if (property != NULL) {
            AbstractSurfacePropertyIterator *members =
                ecitygml_MultiSurface_surface_member(ecitygml_MultiSurfaceProperty_object(property));
            const AbstractSurfaceProperty *member;
            while ((member = ecitygml_AbstractSurfacePropertyIterator_next(members)) != NULL) {
                const Polygon *polygon = ecitygml_Polygon_try_from(ecitygml_AbstractSurfaceProperty_object(member));
                if (polygon == NULL) continue;
                DirectPositionIterator *points =
                    ecitygml_LinearRing_points(ecitygml_LinearRing_try_from(ecitygml_Polygon_exterior(polygon)));
                const DirectPosition *p;
                while ((p = ecitygml_DirectPositionIterator_next(points)) != NULL) {
                    TEST_ASSERT_LESS_THAN_size_t(MAX_COORDINATES, len);
                    out[len][0] = ecitygml_DirectPosition_x(p);
                    out[len][1] = ecitygml_DirectPosition_y(p);
                    out[len++][2] = ecitygml_DirectPosition_z(p);
                }
                ecitygml_DirectPositionIterator_destroy(points);
            }
            ecitygml_AbstractSurfacePropertyIterator_destroy(members);
        }
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractFeatureKindRefIterator_destroy(features);
    return len;
}

static void writer_preserves_coordinates(void) {
    CityModel *city_model = read(FZK_LOD2);
    char *written_text = text_of(city_model);
    CityModel *written = read_data((DiplomatU8View){(const uint8_t *)written_text, strlen(written_text)}, CitygmlFormat_Gml);
    double expected[MAX_COORDINATES][3];
    double actual[MAX_COORDINATES][3];
    size_t len = wall_coordinates(city_model, expected);
    TEST_ASSERT_GREATER_THAN_size_t(0, len);
    TEST_ASSERT_EQUAL_size_t(len, wall_coordinates(written, actual));
    TEST_ASSERT_EQUAL_DOUBLE_ARRAY(&expected[0][0], &actual[0][0], len * 3);
    ecitygml_CityModel_destroy(written);
    free(written_text);
    ecitygml_CityModel_destroy(city_model);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(writer_in_memory);
    RUN_TEST(writer_files);
    RUN_TEST(writer_overwrites_file);
    RUN_TEST(writer_base_path_with_format);
    RUN_TEST(writer_formatting);
    RUN_TEST(writer_finish_once);
    RUN_TEST(writer_unsupported_extension);
    RUN_TEST(writer_missing_directory);
    RUN_TEST(writer_keeps_references);
    RUN_TEST(writer_preserves_coordinates);
    return UNITY_END();
}
