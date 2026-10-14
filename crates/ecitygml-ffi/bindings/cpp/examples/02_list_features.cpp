// Lists the feature types of a CityGML file with their counts, and the ids of its buildings.
//
// A city model is a tree of features: the city model, buildings, their wall surfaces, the doors in
// those walls, and so on. `iter_features()` visits all of them, depth first in document order, as
// `AbstractFeatureKindRef`s. Each tells its `feature_type()`; to use the getters of its concrete
// type, convert it with that type's `try_from`, which returns null for other types.
//
// Built by bindings/cpp/CMakeLists.txt (`mise run build:bindings:cpp`), which also runs it as a test.
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

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <ecitygml/AbstractFeatureKindRef.hpp>
#include <ecitygml/AbstractFeatureKindRefIterator.hpp>
#include <ecitygml/Building.hpp>
#include <ecitygml/CityModel.hpp>
#include <ecitygml/Error.hpp>
#include <ecitygml/FeatureType.hpp>
#include <ecitygml/GmlReader.hpp>
#include <ecitygml/Id.hpp>

namespace {
void print_row(const std::string &name, const std::string &count) {
    std::cout << std::left << std::setw(24) << name << " " << std::right << std::setw(6) << count << "\n";
}
}  // namespace

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "usage: 02_list_features path/to/model.gml\n";
        return 2;
    }
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
    auto city_model = std::move(result).ok().value();

    // Count the features per type, in the order the types first appear. `FeatureType::to_string`
    // is the type's name, as Rust's `Display`.
    std::vector<std::pair<std::string, std::size_t>> counts;
    std::size_t total = 0;
    auto features = city_model->iter_features();
    while (auto feature = features->next()) {  // each feature is a std::unique_ptr, freed per loop
        const std::string name = feature->feature_type().to_string();
        auto entry = counts.begin();
        while (entry != counts.end() && entry->first != name) {
            ++entry;
        }
        if (entry == counts.end()) {
            counts.emplace_back(name, 0);
            entry = counts.end() - 1;
        }
        ++entry->second;
        ++total;
    }

    print_row("Feature type", "Count");
    for (const auto &[name, count] : counts) {
        print_row(name, std::to_string(count));
    }
    print_row("Total", std::to_string(total));

    // `Building::try_from` turns a feature into a `Building` (or null). The building borrows from
    // the city model, which must outlive it.
    std::cout << "\nBuildings:\n";
    features = city_model->iter_features();
    while (auto feature = features->next()) {
        if (const ecitygml::Building *building = ecitygml::Building::try_from(*feature)) {
            std::cout << "  " << building->feature_id().as_str() << "\n";
        }
    }
    return 0;
}
