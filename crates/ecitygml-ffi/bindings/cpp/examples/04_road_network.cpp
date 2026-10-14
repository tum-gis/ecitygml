// Walks the road network of a CityGML file and measures it: centre-line lengths, traffic-area
// areas and the volumes of the traffic spaces.
//
// CityGML's transportation model is a hierarchy: a road consists of sections and intersections, which
// (like the road itself) hold traffic spaces and auxiliary traffic spaces (e.g. lanes and sidewalks).
// Each space is bounded by traffic areas or auxiliary traffic areas, its ground surfaces. The spaces
// are reached through properties (`object()`), the areas through the space's `boundaries()`, converted
// with `try_from`. Geometry calculations (`length_3d`, `area_3d`, `volume_3d`) can fail, e.g. for
// degenerate geometry, and return a `diplomat::result`.
//
// Built by bindings/cpp/CMakeLists.txt (`mise run build:bindings:cpp`), which also runs it as a test.
//
// Usage: 04_road_network path/to/model.gml
//
// Output for ASAM-UC_RoadShape.gml (shortened):
//
//     Road UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f
//       Section UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29
//         TrafficSpace UUID_ae81947d-a661-3678-a5ee-eed58b686946
//           Centre line (LoD2): 40.000 m
//           Volume (LoD2 solid): 720.000 m^3
//           TrafficArea UUID_8625bf6f-57cb-3ddf-8fd1-6674b756a2e2: 160.798 m^2
//         ...
//
//     Total volume of traffic spaces (LoD2): 1260.000 m^3

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <ecitygml/AbstractFeatureKindRef.hpp>
#include <ecitygml/AbstractFeatureKindRefIterator.hpp>
#include <ecitygml/AbstractSpaceBoundaryKind.hpp>
#include <ecitygml/AbstractSpaceBoundaryProperty.hpp>
#include <ecitygml/AbstractSpaceBoundaryPropertyIterator.hpp>
#include <ecitygml/AuxiliaryTrafficArea.hpp>
#include <ecitygml/AuxiliaryTrafficSpace.hpp>
#include <ecitygml/AuxiliaryTrafficSpaceProperty.hpp>
#include <ecitygml/AuxiliaryTrafficSpacePropertyIterator.hpp>
#include <ecitygml/CityModel.hpp>
#include <ecitygml/Error.hpp>
#include <ecitygml/GmlReader.hpp>
#include <ecitygml/Id.hpp>
#include <ecitygml/Intersection.hpp>
#include <ecitygml/IntersectionProperty.hpp>
#include <ecitygml/IntersectionPropertyIterator.hpp>
#include <ecitygml/MultiCurve.hpp>
#include <ecitygml/MultiCurveProperty.hpp>
#include <ecitygml/MultiSurface.hpp>
#include <ecitygml/MultiSurfaceProperty.hpp>
#include <ecitygml/Road.hpp>
#include <ecitygml/Section.hpp>
#include <ecitygml/SectionProperty.hpp>
#include <ecitygml/SectionPropertyIterator.hpp>
#include <ecitygml/Solid.hpp>
#include <ecitygml/SolidProperty.hpp>
#include <ecitygml/TrafficArea.hpp>
#include <ecitygml/TrafficSpace.hpp>
#include <ecitygml/TrafficSpaceProperty.hpp>
#include <ecitygml/TrafficSpacePropertyIterator.hpp>

namespace {
/// Counts and sums over all spaces of one kind (traffic or auxiliary traffic spaces).
struct Totals {
    std::size_t spaces = 0;
    double length = 0.0;
    double volume = 0.0;
    std::size_t areas = 0;
    double area = 0.0;
};

std::string fixed3(double value) {
    std::ostringstream text;
    text << std::fixed << std::setprecision(3) << value;
    return text.str();
}

/// The object of an optional property, or null if the property or its object is absent.
template <typename Property>
auto object_of(const Property *property) -> decltype(property->object()) {
    return property ? property->object() : nullptr;
}

/// A measurement as text (e.g. "40.000 m"), added to `sum`; "-" without geometry, and a note if the
/// calculation fails.
template <typename Geometry, typename Measure>
std::string measured(const Geometry *geometry, Measure measure, const std::string &unit, double &sum) {
    if (geometry == nullptr) {
        return "-";
    }
    auto result = measure(*geometry);
    if (result.is_err()) {
        return "not computable (" + std::move(result).err().value()->message() + ")";
    }
    const double value = std::move(result).ok().value();
    sum += value;
    return fixed3(value) + " " + unit;
}

/// Prints a traffic space (`Area` = `TrafficArea`) or an auxiliary traffic space
/// (`Area` = `AuxiliaryTrafficArea`), which have the same getters.
template <typename Area, typename Space>
void print_space(const Space &space, const char *space_name, const char *area_name, Totals &totals,
                 const std::string &indent) {
    std::cout << indent << space_name << " " << space.feature_id().as_str() << "\n";
    const auto length = measured(object_of(space.lod2_multi_curve()), [](const auto &c) { return c.length_3d(); }, "m",
                                 totals.length);
    const auto volume = measured(object_of(space.lod2_solid()), [](const auto &s) { return s.volume_3d(); }, "m^3",
                                 totals.volume);
    std::cout << indent << "  Centre line (LoD2): " << length << "\n";
    std::cout << indent << "  Volume (LoD2 solid): " << volume << "\n";
    ++totals.spaces;

    // The areas are the space's boundaries of the matching type.
    auto boundaries = space.boundaries();
    while (const auto *property = boundaries->next()) {
        const auto *boundary = property->object();
        if (boundary == nullptr) {
            continue;
        }
        auto feature = ecitygml::AbstractFeatureKindRef::from_space_boundary(*boundary);
        if (const Area *area = Area::try_from(*feature)) {
            const auto text = measured(object_of(area->lod2_multi_surface()), [](const auto &m) { return m.area_3d(); },
                                       "m^2", totals.area);
            std::cout << indent << "  " << area_name << " " << area->feature_id().as_str() << ": " << text << "\n";
            ++totals.areas;
        }
    }
}

/// The traffic and auxiliary traffic spaces of a road, section or intersection.
template <typename TransportationSpace>
void print_spaces_of(const TransportationSpace &transportation_space, Totals &traffic, Totals &auxiliary,
                     const std::string &indent) {
    auto spaces = transportation_space.traffic_spaces();
    while (const auto *property = spaces->next()) {
        if (const auto *space = property->object()) {
            print_space<ecitygml::TrafficArea>(*space, "TrafficSpace", "TrafficArea", traffic, indent);
        }
    }
    auto auxiliary_spaces = transportation_space.auxiliary_traffic_spaces();
    while (const auto *property = auxiliary_spaces->next()) {
        if (const auto *space = property->object()) {
            print_space<ecitygml::AuxiliaryTrafficArea>(*space, "AuxiliaryTrafficSpace", "AuxiliaryTrafficArea",
                                                        auxiliary, indent);
        }
    }
}
}  // namespace

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "usage: 04_road_network path/to/model.gml\n";
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

    Totals traffic;
    Totals auxiliary;
    std::size_t roads = 0;
    auto features = city_model->iter_features();
    while (auto feature = features->next()) {
        const ecitygml::Road *road = ecitygml::Road::try_from(*feature);
        if (road == nullptr) {
            continue;
        }
        ++roads;
        std::cout << "Road " << road->feature_id().as_str() << "\n";
        print_spaces_of(*road, traffic, auxiliary, "  ");  // a road can hold spaces directly, too
        auto sections = road->sections();
        while (const auto *property = sections->next()) {
            if (const auto *section = property->object()) {
                std::cout << "  Section " << section->feature_id().as_str() << "\n";
                print_spaces_of(*section, traffic, auxiliary, "    ");
            }
        }
        auto intersections = road->intersections();
        while (const auto *property = intersections->next()) {
            if (const auto *intersection = property->object()) {
                std::cout << "  Intersection " << intersection->feature_id().as_str() << "\n";
                print_spaces_of(*intersection, traffic, auxiliary, "    ");
            }
        }
    }

    std::cout << "\nRoads: " << roads << "\n";
    for (const auto &[label, totals] : {std::pair<const char *, Totals>{"Traffic spaces", traffic},
                                        std::pair<const char *, Totals>{"Auxiliary traffic spaces", auxiliary}}) {
        std::cout << label << ": " << totals.spaces << ", centre lines " << fixed3(totals.length) << " m, "
                  << totals.areas << " areas " << fixed3(totals.area) << " m^2, volume " << fixed3(totals.volume)
                  << " m^3\n";
    }
    std::cout << "Total volume of traffic spaces (LoD2): " << fixed3(traffic.volume) << " m^3\n";
    return 0;
}
