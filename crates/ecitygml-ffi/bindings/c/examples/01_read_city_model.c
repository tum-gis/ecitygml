// Reads a CityGML file and prints an overview of the city model.
//
// This is the starting point for every program using ecitygml: `GmlReader` reads a file (plain,
// `.gml.gz` or `.gml.zst`) into a `CityModel`, which owns all features. In C:
// - Fallible functions return a `..._result` struct with `is_ok` and either `ok` or `err`.
// - Every object returned as a non-const pointer is owned by the caller and must be freed with
//   its `..._destroy` function; `const` pointers borrow from another object (null when absent).
// - Strings are `DiplomatStringView`s (pointer and length, not null-terminated); text computed on
//   demand (e.g. error messages) is written into a `DiplomatWrite` buffer.
//
// Built by bindings/c/CMakeLists.txt (`mise run build-bindings-c`), which also runs it as a test.
//
// Usage: 01_read_city_model path/to/model.gml
//
// Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml:
//
//     City object members: 1
//     City objects (at all depths): 8
//     Envelope:
//       lower corner: 457842.000, 5439083.000, 111.800
//       upper corner: 457854.000, 5439093.000, 118.318
//       size: 12.000 x 10.000 x 6.518

#include <stdio.h>
#include <string.h>

#include "AbstractCityObjectKindRef.h"
#include "AbstractCityObjectKindRefIterator.h"
#include "BoundingShape.h"
#include "CityModel.h"
#include "DirectPosition.h"
#include "Envelope.h"
#include "Error.h"
#include "GmlReader.h"

// Prints the error's message and frees the error.
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
        fprintf(stderr, "usage: 01_read_city_model path/to/model.gml\n");
        return 2;
    }

    // `from_path` opens the file and picks the format from its extension; `finish` parses it.
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

    // `cityObjectMember`s are the top-level city objects (e.g. buildings); their boundary surfaces,
    // doors and windows are city objects too, which `iter_city_objects` visits as well. Each item
    // the iterator returns is owned and destroyed right away.
    size_t city_objects = 0;
    AbstractCityObjectKindRefIterator *iterator = ecitygml_CityModel_iter_city_objects(city_model);
    AbstractCityObjectKindRef *city_object;
    while ((city_object = ecitygml_AbstractCityObjectKindRefIterator_next(iterator)) != NULL) {
        ecitygml_AbstractCityObjectKindRef_destroy(city_object);
        ++city_objects;
    }
    ecitygml_AbstractCityObjectKindRefIterator_destroy(iterator);
    printf("City object members: %zu\n", ecitygml_CityModel_city_objects_len(city_model));
    printf("City objects (at all depths): %zu\n", city_objects);

    // `bounded_by` is the `gml:boundedBy` property, a bounding shape holding an envelope; both are
    // optional, as in the file. They are borrowed from the city model (const, not destroyed).
    const BoundingShape *bounding_shape = ecitygml_CityModel_bounded_by(city_model);
    const Envelope *envelope = bounding_shape ? ecitygml_BoundingShape_envelope(bounding_shape) : NULL;
    if (envelope == NULL) {
        printf("Envelope: none\n");
    } else {
        const DirectPosition *lower = ecitygml_Envelope_lower_corner(envelope);
        const DirectPosition *upper = ecitygml_Envelope_upper_corner(envelope);
        printf("Envelope:\n");
        printf("  lower corner: %.3f, %.3f, %.3f\n", ecitygml_DirectPosition_x(lower), ecitygml_DirectPosition_y(lower),
               ecitygml_DirectPosition_z(lower));
        printf("  upper corner: %.3f, %.3f, %.3f\n", ecitygml_DirectPosition_x(upper), ecitygml_DirectPosition_y(upper),
               ecitygml_DirectPosition_z(upper));
        printf("  size: %.3f x %.3f x %.3f\n", ecitygml_Envelope_size_x(envelope), ecitygml_Envelope_size_y(envelope),
               ecitygml_Envelope_size_z(envelope));
    }

    ecitygml_CityModel_destroy(city_model);
    return 0;
}
