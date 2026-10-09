// Prints a report of every building in a CityGML file: its attributes and its boundary surfaces
// with their doors and windows.
//
// Shows how the bindings mirror the Rust data model:
// - Optional values are null pointers or `std::optional`s when absent; lists are iterators whose
//   `next()` returns null at the end.
// - Code-list values (class, function, ...) are wrappers with `value()` (and `code()`).
// - Properties referencing other objects (e.g. a building's boundaries) have `object()` and `href()`;
//   `object()` is null if the property only references an object elsewhere via `xlink:href`.
// - Abstract types are converted with `try_from`, e.g. a generic attribute to a `MeasureAttribute`,
//   or a boundary (via `AbstractFeatureKindRef::from_space_boundary`) to a `WallSurface`.
//
// Built by bindings/cpp/CMakeLists.txt (`mise run build-bindings-cpp`), which also runs it as a test.
//
// Usage: 03_building_report path/to/model.gml
//
// Output for FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml (shortened):
//
//     Building UUID_d281adfc-4901-0f52-540b-4cc1a9325f82
//       Name: AC14-FZK-Haus
//       Class: 1000
//       ...
//       Boundaries:
//         WallSurface GML_5856d7ad-5e34-498a-817b-9544bfbb1475
//           WindowSurface GML_356b85c1-25a0-49f9-b39e-013fbbafcce4
//         ...

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <ecitygml/AbstractFeatureKindRef.hpp>
#include <ecitygml/AbstractFeatureKindRefIterator.hpp>
#include <ecitygml/AbstractFillingSurfaceKind.hpp>
#include <ecitygml/AbstractFillingSurfaceProperty.hpp>
#include <ecitygml/AbstractFillingSurfacePropertyIterator.hpp>
#include <ecitygml/AbstractSpaceBoundaryKind.hpp>
#include <ecitygml/AbstractSpaceBoundaryProperty.hpp>
#include <ecitygml/AbstractSpaceBoundaryPropertyIterator.hpp>
#include <ecitygml/Building.hpp>
#include <ecitygml/BuildingClassValue.hpp>
#include <ecitygml/BuildingFunctionValue.hpp>
#include <ecitygml/BuildingFunctionValueIterator.hpp>
#include <ecitygml/BuildingUsageValue.hpp>
#include <ecitygml/BuildingUsageValueIterator.hpp>
#include <ecitygml/CityModel.hpp>
#include <ecitygml/Code.hpp>
#include <ecitygml/CodeIterator.hpp>
#include <ecitygml/Date.hpp>
#include <ecitygml/DoubleAttribute.hpp>
#include <ecitygml/ElevationReferenceValue.hpp>
#include <ecitygml/Error.hpp>
#include <ecitygml/FeatureType.hpp>
#include <ecitygml/GenericAttributeKind.hpp>
#include <ecitygml/GenericAttributeKindIterator.hpp>
#include <ecitygml/GmlReader.hpp>
#include <ecitygml/GroundSurface.hpp>
#include <ecitygml/HRef.hpp>
#include <ecitygml/Height.hpp>
#include <ecitygml/HeightIterator.hpp>
#include <ecitygml/Id.hpp>
#include <ecitygml/IntAttribute.hpp>
#include <ecitygml/Length.hpp>
#include <ecitygml/Measure.hpp>
#include <ecitygml/MeasureAttribute.hpp>
#include <ecitygml/RoofSurface.hpp>
#include <ecitygml/RoofTypeValue.hpp>
#include <ecitygml/StringAttribute.hpp>
#include <ecitygml/WallSurface.hpp>

namespace {
/// The `value()`s of an iterator's code-list values (or codes), comma-separated; "-" if none.
template <typename Iterator>
std::string joined(Iterator &iterator) {
    std::string text;
    while (const auto *value = iterator.next()) {
        text += (text.empty() ? "" : ", ") + std::string(value->value());
    }
    return text.empty() ? "-" : text;
}

/// The `value()` of an optional code-list value; "-" if absent.
template <typename Value>
std::string value_or_dash(const Value *value) {
    return value ? std::string(value->value()) : "-";
}

std::string optional_number(std::optional<int64_t> value) {
    return value ? std::to_string(*value) : "-";
}

std::string fixed3(double value) {
    std::ostringstream text;
    text << std::fixed << std::setprecision(3) << value;
    return text.str();
}

/// The value of a generic attribute: string, integer, double or measure (value and unit).
std::string generic_attribute_value(const ecitygml::GenericAttributeKind &attribute) {
    if (const auto *string = attribute.as_string()) {
        return std::string(string->value());
    }
    if (const auto *integer = attribute.as_int()) {
        return std::to_string(integer->value());
    }
    if (const auto *real = attribute.as_double()) {
        return fixed3(real->value());
    }
    if (const auto *measure = ecitygml::MeasureAttribute::try_from(attribute)) {
        return fixed3(measure->value().value()) + " " + std::string(measure->value().uom());
    }
    return "(not shown)";  // e.g. a generic attribute set, which holds further attributes
}

/// Prints the doors and windows of a wall, roof or ground surface.
template <typename Surface>
void print_filling_surfaces(const Surface &surface) {
    auto fillings = surface.filling_surfaces();
    while (const auto *property = fillings->next()) {
        if (const auto *filling = property->object()) {
            std::cout << "      " << filling->feature_type().to_string() << " " << filling->feature_id().as_str() << "\n";
        }
    }
}

void print_building(const ecitygml::Building &building) {
    std::cout << "Building " << building.feature_id().as_str() << "\n";
    auto names = building.names();
    std::cout << "  Name: " << joined(*names) << "\n";
    std::cout << "  Class: " << value_or_dash(building.class_()) << "\n";
    auto functions = building.functions();
    std::cout << "  Functions: " << joined(*functions) << "\n";
    auto usages = building.usages();
    std::cout << "  Usages: " << joined(*usages) << "\n";
    std::cout << "  Roof type: " << value_or_dash(building.roof_type()) << "\n";
    std::cout << "  Storeys above ground: " << optional_number(building.storeys_above_ground()) << "\n";
    std::cout << "  Storeys below ground: " << optional_number(building.storeys_below_ground()) << "\n";
    std::cout << "  Date of construction: ";
    if (const ecitygml::Date *date = building.date_of_construction()) {
        std::cout << std::setfill('0') << std::setw(4) << date->year() << "-" << std::setw(2) << date->month() << "-"
                  << std::setw(2) << date->day() << std::setfill(' ') << "\n";
    } else {
        std::cout << "-\n";
    }

    std::cout << "  Heights:\n";
    auto heights = building.heights();
    while (const auto *height = heights->next()) {
        std::cout << "    " << fixed3(height->length().value()) << " " << height->length().uom() << " ("
                  << height->high_reference().value() << " to " << height->low_reference().value() << ")\n";
    }

    std::cout << "  Generic attributes:\n";
    auto attributes = building.generic_attributes();
    while (const auto *attribute = attributes->next()) {
        std::cout << "    " << attribute->name() << ": " << generic_attribute_value(*attribute) << "\n";
    }

    // Each boundary property holds an `AbstractSpaceBoundaryKind` (or only an href). Wall, roof
    // and ground surfaces can have filling surfaces: doors and windows.
    std::cout << "  Boundaries:\n";
    auto boundaries = building.boundaries();
    while (const auto *property = boundaries->next()) {
        const ecitygml::AbstractSpaceBoundaryKind *boundary = property->object();
        if (boundary == nullptr) {
            std::cout << "    (reference to " << property->href()->to_string() << ")\n";
            continue;
        }
        std::cout << "    " << boundary->feature_type().to_string() << " " << boundary->feature_id().as_str() << "\n";
        auto feature = ecitygml::AbstractFeatureKindRef::from_space_boundary(*boundary);
        if (const auto *wall = ecitygml::WallSurface::try_from(*feature)) {
            print_filling_surfaces(*wall);
        } else if (const auto *roof = ecitygml::RoofSurface::try_from(*feature)) {
            print_filling_surfaces(*roof);
        } else if (const auto *ground = ecitygml::GroundSurface::try_from(*feature)) {
            print_filling_surfaces(*ground);
        }
    }
}
}  // namespace

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "usage: 03_building_report path/to/model.gml\n";
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

    // The buildings borrow from the city model, which outlives them.
    std::vector<const ecitygml::Building *> buildings;
    auto features = city_model->iter_features();
    while (auto feature = features->next()) {
        if (const auto *building = ecitygml::Building::try_from(*feature)) {
            buildings.push_back(building);
        }
    }
    if (buildings.empty()) {
        std::cout << "No buildings.\n";
    }
    for (std::size_t index = 0; index < buildings.size(); ++index) {
        if (index > 0) {
            std::cout << "\n";
        }
        print_building(*buildings[index]);
    }
    return 0;
}
