// Measures the geometry of every building in a CityGML file: areas and triangle counts of its wall,
// roof and ground surfaces, its doors and windows, and the volumes of its solids.
//
// Geometry calculations work on the geometry stored inline: `area_3d()` of a multi surface,
// `volume_3d()` of a solid, `triangulate()` (a `Triangulation`, whose `surface()` holds the
// triangles). They return a `diplomat::result` holding an `ecitygml::Error` when they can't compute a
// result. A common case: a solid whose surfaces only reference the boundary polygons by `xlink:href`
// (the reader doesn't resolve such references, as in Rust), shown here as "not computable" with the
// error message.
//
// Built by bindings/cpp/CMakeLists.txt (`mise run build-bindings-cpp`), which also runs it as a test.
//
// Usage: 05_measure_geometry path/to/model.gml
//
// Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml (shortened):
//
//     Building UUID_d281adfc-4901-0f52-540b-4cc1a9325f82
//       WallSurface: 4, area 188.629 m^2, 10 triangles
//       RoofSurface: 2, area 138.564 m^2, 4 triangles
//       GroundSurface: 1, area 120.000 m^2, 2 triangles
//       Doors and windows: 0, area 0.000 m^2
//       LoD2 solid: 7 surfaces, 7 of them xlink:href references
//         Volume: not computable (surface member references '#PolyID7350_878_759628_120742' via ...)

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include <ecitygml/AbstractFeatureKindRef.hpp>
#include <ecitygml/AbstractFeatureKindRefIterator.hpp>
#include <ecitygml/AbstractFillingSurfaceKind.hpp>
#include <ecitygml/AbstractFillingSurfaceProperty.hpp>
#include <ecitygml/AbstractFillingSurfacePropertyIterator.hpp>
#include <ecitygml/AbstractSpaceBoundaryKind.hpp>
#include <ecitygml/AbstractSpaceBoundaryProperty.hpp>
#include <ecitygml/AbstractSpaceBoundaryPropertyIterator.hpp>
#include <ecitygml/AbstractSurfaceProperty.hpp>
#include <ecitygml/AbstractSurfacePropertyIterator.hpp>
#include <ecitygml/Building.hpp>
#include <ecitygml/CityModel.hpp>
#include <ecitygml/Error.hpp>
#include <ecitygml/GmlReader.hpp>
#include <ecitygml/GroundSurface.hpp>
#include <ecitygml/Id.hpp>
#include <ecitygml/MultiSurface.hpp>
#include <ecitygml/MultiSurfaceProperty.hpp>
#include <ecitygml/RoofSurface.hpp>
#include <ecitygml/Shell.hpp>
#include <ecitygml/Solid.hpp>
#include <ecitygml/SolidProperty.hpp>
#include <ecitygml/Triangle.hpp>
#include <ecitygml/TriangleIterator.hpp>
#include <ecitygml/TriangulatedSurface.hpp>
#include <ecitygml/Triangulation.hpp>
#include <ecitygml/WallSurface.hpp>

namespace {
std::string fixed3(double value) {
    std::ostringstream text;
    text << std::fixed << std::setprecision(3) << value;
    return text.str();
}

/// The value of a result, or a `std::runtime_error` with the error's message (caught per building).
template <typename T>
T value_or_throw(diplomat::result<T, std::unique_ptr<ecitygml::Error>> result) {
    if (result.is_err()) {
        throw std::runtime_error(std::move(result).err().value()->message());
    }
    return std::move(result).ok().value();
}

/// The multi surface of the highest level of detail a thematic surface has, or null.
template <typename Surface>
const ecitygml::MultiSurface *highest_lod_multi_surface(const Surface &surface) {
    for (const auto *property : {surface.lod3_multi_surface(), surface.lod2_multi_surface(),
                                 surface.lod1_multi_surface(), surface.lod0_multi_surface()}) {
        if (property != nullptr && property->object() != nullptr) {
            return property->object();
        }
    }
    return nullptr;
}

struct Measurement {
    std::size_t count = 0;
    double area = 0.0;
    std::size_t triangles = 0;

    /// Adds a surface: the area and triangle count of its highest LoD multi surface.
    template <typename Surface>
    void add(const Surface &surface) {
        ++count;
        if (const auto *multi_surface = highest_lod_multi_surface(surface)) {
            area += value_or_throw(multi_surface->area_3d());
            auto triangulation = value_or_throw(multi_surface->triangulate());
            auto iterator = triangulation->surface().triangles();
            while (iterator->next() != nullptr) {
                ++triangles;
            }
        }
    }
};

/// Adds the doors and windows of a wall, roof or ground surface.
template <typename Surface>
void add_filling_surfaces(const Surface &surface, Measurement &fillings) {
    auto iterator = surface.filling_surfaces();
    while (const auto *property = iterator->next()) {
        if (const auto *filling = property->object()) {
            fillings.add(*filling);
        }
    }
}

void print_boundaries(const ecitygml::Building &building) {
    Measurement walls, roofs, grounds, fillings;
    auto boundaries = building.boundaries();
    while (const auto *property = boundaries->next()) {
        const auto *boundary = property->object();
        if (boundary == nullptr) {
            continue;
        }
        auto feature = ecitygml::AbstractFeatureKindRef::from_space_boundary(*boundary);
        if (const auto *wall = ecitygml::WallSurface::try_from(*feature)) {
            walls.add(*wall);
            add_filling_surfaces(*wall, fillings);
        } else if (const auto *roof = ecitygml::RoofSurface::try_from(*feature)) {
            roofs.add(*roof);
            add_filling_surfaces(*roof, fillings);
        } else if (const auto *ground = ecitygml::GroundSurface::try_from(*feature)) {
            grounds.add(*ground);
            add_filling_surfaces(*ground, fillings);
        }
    }
    for (const auto &[label, measurement] : {std::pair<const char *, Measurement>{"WallSurface", walls},
                                             std::pair<const char *, Measurement>{"RoofSurface", roofs},
                                             std::pair<const char *, Measurement>{"GroundSurface", grounds}}) {
        std::cout << "  " << label << ": " << measurement.count << ", area " << fixed3(measurement.area) << " m^2, "
                  << measurement.triangles << " triangles\n";
    }
    std::cout << "  Doors and windows: " << fillings.count << ", area " << fixed3(fillings.area) << " m^2\n";
}

void print_solids(const ecitygml::Building &building) {
    int lod = 1;
    for (const auto *property : {building.lod1_solid(), building.lod2_solid(), building.lod3_solid()}) {
        const ecitygml::Solid *solid = property ? property->object() : nullptr;
        if (solid != nullptr) {
            std::size_t members = 0;
            std::size_t references = 0;
            if (const auto *shell = solid->exterior()) {
                auto iterator = shell->members();
                while (const auto *member = iterator->next()) {
                    ++members;
                    references += member->object() == nullptr ? 1 : 0;
                }
            }
            std::cout << "  LoD" << lod << " solid: " << members << " surfaces, " << references
                      << " of them xlink:href references\n";
            auto volume = solid->volume_3d();
            if (volume.is_ok()) {
                std::cout << "    Volume: " << fixed3(std::move(volume).ok().value()) << " m^3\n";
            } else {
                std::cout << "    Volume: not computable (" << std::move(volume).err().value()->message() << ")\n";
            }
        }
        ++lod;
    }
}
}  // namespace

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "usage: 05_measure_geometry path/to/model.gml\n";
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

    std::size_t buildings = 0;
    auto features = city_model->iter_features();
    while (auto feature = features->next()) {
        const ecitygml::Building *building = ecitygml::Building::try_from(*feature);
        if (building == nullptr) {
            continue;
        }
        if (buildings++ > 0) {
            std::cout << "\n";
        }
        std::cout << "Building " << building->feature_id().as_str() << "\n";
        try {
            print_boundaries(*building);
        } catch (const std::runtime_error &error) {  // e.g. a surface that can't be triangulated
            std::cout << "  Boundaries: not computable (" << error.what() << ")\n";
        }
        print_solids(*building);
    }
    if (buildings == 0) {
        std::cout << "No buildings.\n";
    }
    return 0;
}
