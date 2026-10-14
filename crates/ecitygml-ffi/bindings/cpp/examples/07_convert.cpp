// Converts a CityGML file: reads it and writes it again, e.g. compressed or indented.
//
// Shows writing with `GmlWriter`: `from_path` creates the output file and picks the format from its
// extension (`.gml`, `.gml.gz` or `.gml.zst`), `with_formatting` sets the layout (here indented by two
// spaces; `Formatting::compact()` writes no line breaks at all), and `finish` writes the city model.
// Reading the written file back verifies the result.
//
// Built by bindings/cpp/CMakeLists.txt (`mise run build:bindings:cpp`), which also runs it as a test.
//
// Usage: 07_convert input.gml output.gml.gz
//
// Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml, converted to a .gml.gz file:
//
//     Read: 1 city object members, 8 city objects
//     Wrote: gzip-compressed CityGML, indented by 2 spaces
//     Read back: 1 city object members, 8 city objects

#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include <ecitygml/AbstractCityObjectKindRef.hpp>
#include <ecitygml/AbstractCityObjectKindRefIterator.hpp>
#include <ecitygml/CityModel.hpp>
#include <ecitygml/Error.hpp>
#include <ecitygml/Formatting.hpp>
#include <ecitygml/GmlReader.hpp>
#include <ecitygml/GmlWriter.hpp>

namespace {
constexpr std::size_t INDENT_SIZE = 2;

std::unique_ptr<ecitygml::CityModel> read(const std::string &path) {
    auto reader = ecitygml::GmlReader::from_path(path);
    if (reader.is_err()) {
        std::cerr << "error: " << std::move(reader).err().value()->message() << "\n";
        return nullptr;
    }
    auto result = std::move(reader).ok().value()->finish();
    if (result.is_err()) {
        std::cerr << "error: " << std::move(result).err().value()->message() << "\n";
        return nullptr;
    }
    return std::move(result).ok().value();
}

std::string summary(const ecitygml::CityModel &city_model) {
    std::size_t city_objects = 0;
    auto iterator = city_model.iter_city_objects();
    while (iterator->next() != nullptr) {
        ++city_objects;
    }
    return std::to_string(city_model.city_objects_len()) + " city object members, " + std::to_string(city_objects) +
           " city objects";
}

bool ends_with(const std::string &text, const std::string &suffix) {
    return text.size() >= suffix.size() && text.compare(text.size() - suffix.size(), suffix.size(), suffix) == 0;
}

/// What `GmlWriter::from_path` writes for this path (it fails for other extensions).
std::string format_name(const std::string &path) {
    if (ends_with(path, ".gml.gz")) {
        return "gzip-compressed CityGML";
    }
    if (ends_with(path, ".gml.zst")) {
        return "zstd-compressed CityGML";
    }
    return "CityGML";
}
}  // namespace

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "usage: 07_convert input.gml output.gml[.gz|.zst]\n";
        return 2;
    }
    const std::string output_path = argv[2];
    auto city_model = read(argv[1]);
    if (!city_model) {
        return 1;
    }
    std::cout << "Read: " << summary(*city_model) << "\n";

    auto writer = ecitygml::GmlWriter::from_path(output_path);
    if (writer.is_err()) {
        std::cerr << "error: " << std::move(writer).err().value()->message() << "\n";
        return 1;
    }
    auto gml_writer = std::move(writer).ok().value();
    gml_writer->with_formatting(*ecitygml::Formatting::indent(' ', INDENT_SIZE));
    auto finished = gml_writer->finish(*city_model);
    if (finished.is_err()) {
        std::cerr << "error: " << std::move(finished).err().value()->message() << "\n";
        return 1;
    }
    std::cout << "Wrote: " << format_name(output_path) << ", indented by " << INDENT_SIZE << " spaces\n";

    auto written = read(output_path);
    if (!written) {
        return 1;
    }
    std::cout << "Read back: " << summary(*written) << "\n";
    return 0;
}
