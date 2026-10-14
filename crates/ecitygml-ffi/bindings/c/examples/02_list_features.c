// Lists the feature types of a CityGML file with their counts, and the ids of its buildings.
//
// A city model is a tree of features: the city model, buildings, their wall surfaces, the doors in
// those walls, and so on. `ecitygml_CityModel_iter_features` visits all of them, depth first in
// document order, as `AbstractFeatureKindRef`s. Each tells its feature type; to use the getters of
// its concrete type, convert it with that type's `try_from`, which returns NULL for other types.
//
// Built by bindings/c/CMakeLists.txt (`mise run build:bindings:c`), which also runs it as a test.
//
// Usage: 02_list_features path/to/model.gml
//
// Output for FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml (shortened):
//
//     Feature type              Count
//     CityModel                     1
//     Building                      1
//     WallSurface                   4
//     ...
//     Total                        22
//
//     Buildings:
//       UUID_d281adfc-4901-0f52-540b-4cc1a9325f82

#include <stdio.h>
#include <string.h>

#include "AbstractFeatureKindRef.h"
#include "AbstractFeatureKindRefIterator.h"
#include "Building.h"
#include "CityModel.h"
#include "Error.h"
#include "FeatureType.h"
#include "GmlReader.h"
#include "Id.h"

// More than the number of feature types.
#define MAX_FEATURE_TYPES 128

static int print_error(Error *error) {
    DiplomatWrite *message = diplomat_buffer_write_create(64);
    ecitygml_Error_message(error, message);
    fprintf(stderr, "error: %.*s\n", (int)diplomat_buffer_write_len(message), diplomat_buffer_write_get_bytes(message));
    diplomat_buffer_write_destroy(message);
    ecitygml_Error_destroy(error);
    return 1;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: 02_list_features path/to/model.gml\n");
        return 2;
    }
    ecitygml_GmlReader_from_path_result reader = ecitygml_GmlReader_from_path((DiplomatStringView){argv[1], strlen(argv[1])});
    if (!reader.is_ok) {
        return print_error(reader.err);
    }
    ecitygml_GmlReader_finish_result result = ecitygml_GmlReader_finish(reader.ok);
    ecitygml_GmlReader_destroy(reader.ok);
    if (!result.is_ok) {
        return print_error(result.err);
    }
    CityModel *city_model = result.ok;

    // Count the features per type, in the order the types first appear.
    FeatureType types[MAX_FEATURE_TYPES];
    size_t counts[MAX_FEATURE_TYPES];
    size_t type_count = 0;
    size_t total = 0;
    AbstractFeatureKindRefIterator *features = ecitygml_CityModel_iter_features(city_model);
    AbstractFeatureKindRef *feature;
    while ((feature = ecitygml_AbstractFeatureKindRefIterator_next(features)) != NULL) {
        FeatureType type = ecitygml_AbstractFeatureKindRef_feature_type(feature);
        size_t index = 0;
        while (index < type_count && types[index] != type) {
            ++index;
        }
        if (index == type_count) {
            types[type_count] = type;
            counts[type_count++] = 0;
        }
        ++counts[index];
        ++total;
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractFeatureKindRefIterator_destroy(features);

    // `ecitygml_FeatureType_to_string` writes the type's name (as Rust's `Display`).
    printf("%-24s %6s\n", "Feature type", "Count");
    for (size_t index = 0; index < type_count; ++index) {
        DiplomatWrite *name = diplomat_buffer_write_create(32);
        ecitygml_FeatureType_to_string(types[index], name);
        printf("%-24.*s %6zu\n", (int)diplomat_buffer_write_len(name), diplomat_buffer_write_get_bytes(name), counts[index]);
        diplomat_buffer_write_destroy(name);
    }
    printf("%-24s %6zu\n", "Total", total);

    // `ecitygml_Building_try_from` turns a feature into a `Building` (or NULL). The building borrows
    // from the city model, not from the feature, so it stays valid after the feature is destroyed.
    printf("\nBuildings:\n");
    features = ecitygml_CityModel_iter_features(city_model);
    while ((feature = ecitygml_AbstractFeatureKindRefIterator_next(features)) != NULL) {
        const Building *building = ecitygml_Building_try_from(feature);
        if (building) {
            DiplomatStringView id = ecitygml_Id_as_str(ecitygml_Building_feature_id(building));
            printf("  %.*s\n", (int)id.len, id.data);
        }
        ecitygml_AbstractFeatureKindRef_destroy(feature);
    }
    ecitygml_AbstractFeatureKindRefIterator_destroy(features);

    ecitygml_CityModel_destroy(city_model);
    return 0;
}
