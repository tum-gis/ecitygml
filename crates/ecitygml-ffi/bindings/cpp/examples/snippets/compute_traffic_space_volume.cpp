#include <ecitygml/AbstractFeatureKindRef.hpp>
#include <ecitygml/AbstractFeatureKindRefIterator.hpp>
#include <ecitygml/CityModel.hpp>
#include <ecitygml/Error.hpp>
#include <ecitygml/GmlReader.hpp>
#include <ecitygml/Solid.hpp>
#include <ecitygml/SolidProperty.hpp>
#include <ecitygml/TrafficSpace.hpp>

#include <cstdio>
#include <vector>

int main(int argc, char** argv) {
    const char* path = argc > 1 ? argv[1] : "model.gml";

    // Parse the CityGML document into the in-memory city model
    auto reader = ecitygml::GmlReader::from_path(path);
    if (!reader.is_ok()) return 1;
    auto city_model = std::move(reader).ok().value()->finish();
    if (!city_model.is_ok()) return 1;
    auto model = std::move(city_model).ok().value();

    // Traverse all features and keep only those that are traffic
    // spaces, using a type-safe conversion that skips all other
    // feature types
    std::vector<const ecitygml::TrafficSpace*> traffic_spaces;
    auto features = model->iter_features();
    while (auto feature = features->next()) {
        const auto* space = ecitygml::TrafficSpace::try_from(*feature);
        if (space) traffic_spaces.push_back(space);
    }

    // Compute the volumes of the LOD2 solids and sum them up; spaces
    // without an LOD2 solid, or whose volume cannot be computed, are
    // skipped
    double total = 0.0;
    for (const auto* space : traffic_spaces) {
        const auto* solid_property = space->lod2_solid();
        if (!solid_property) continue;
        const auto* solid = solid_property->object();
        if (!solid) continue;
        auto volume = solid->volume_3d();
        if (volume.is_ok()) total += std::move(volume).ok().value();
    }

    std::printf(
        "Total volume of traffic spaces (LoD2): %.3f m^3\n", total);
}
