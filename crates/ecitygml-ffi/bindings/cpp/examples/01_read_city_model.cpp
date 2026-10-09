// Reads a CityGML file and prints an overview of the city model.
//
// This is the starting point for every program using ecitygml: `GmlReader` reads a file (plain,
// `.gml.gz` or `.gml.zst`) into a `CityModel`, which owns all features. Fallible calls return a
// `diplomat::result` holding either the value or an `ecitygml::Error`; owned objects come as
// `std::unique_ptr`, borrowed ones as references or pointers (null when absent).
//
// Built by bindings/cpp/CMakeLists.txt (`mise run build-bindings-cpp`), which also runs it as a test.
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

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <memory>

#include <ecitygml/AbstractCityObjectKindRef.hpp>
#include <ecitygml/AbstractCityObjectKindRefIterator.hpp>
#include <ecitygml/BoundingShape.hpp>
#include <ecitygml/CityModel.hpp>
#include <ecitygml/DirectPosition.hpp>
#include <ecitygml/Envelope.hpp>
#include <ecitygml/Error.hpp>
#include <ecitygml/GmlReader.hpp>

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "usage: 01_read_city_model path/to/model.gml\n";
        return 2;
    }

    // `from_path` opens the file and picks the format from its extension; `finish` parses it.
    auto reader = ecitygml::GmlReader::from_path(argv[1]);
    if (reader.is_err()) {
        std::cerr << "error: " << std::move(reader).err().value()->message() << "\n";
        return 1;
    }
    auto result = std::move(reader).ok().value()->finish();
    if (result.is_err()) {
        std::cerr << "error: " << std::move(result).err().value()->message() << "\n";
        return 1;
    }
    std::unique_ptr<ecitygml::CityModel> city_model = std::move(result).ok().value();

    // `cityObjectMember`s are the top-level city objects (e.g. buildings); their boundary surfaces,
    // doors and windows are city objects too, which `iter_city_objects()` visits as well.
    std::size_t city_objects = 0;
    auto iterator = city_model->iter_city_objects();
    while (iterator->next() != nullptr) {
        ++city_objects;
    }
    std::cout << "City object members: " << city_model->city_objects_len() << "\n";
    std::cout << "City objects (at all depths): " << city_objects << "\n";

    // `bounded_by()` is the `gml:boundedBy` property, a bounding shape holding an envelope; both
    // are optional, as in the file, so both pointers may be null.
    const ecitygml::BoundingShape *bounding_shape = city_model->bounded_by();
    const ecitygml::Envelope *envelope = bounding_shape ? bounding_shape->envelope() : nullptr;
    if (envelope == nullptr) {
        std::cout << "Envelope: none\n";
        return 0;
    }
    const auto &lower = envelope->lower_corner();
    const auto &upper = envelope->upper_corner();
    std::cout << std::fixed << std::setprecision(3) << "Envelope:\n"
              << "  lower corner: " << lower.x() << ", " << lower.y() << ", " << lower.z() << "\n"
              << "  upper corner: " << upper.x() << ", " << upper.y() << ", " << upper.z() << "\n"
              << "  size: " << envelope->size_x() << " x " << envelope->size_y() << " x " << envelope->size_z() << "\n";
    return 0;
}
