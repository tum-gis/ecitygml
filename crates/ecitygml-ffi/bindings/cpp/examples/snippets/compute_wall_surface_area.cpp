#include <ecitygml/AbstractFeatureKindRef.hpp>
#include <ecitygml/AbstractFeatureKindRefIterator.hpp>
#include <ecitygml/CityModel.hpp>
#include <ecitygml/Error.hpp>
#include <ecitygml/GmlReader.hpp>
#include <ecitygml/MultiSurface.hpp>
#include <ecitygml/MultiSurfaceProperty.hpp>
#include <ecitygml/WallSurface.hpp>

#include <cstdio>

int main(int argc, char** argv) {
    const char* path = argc > 1 ? argv[1] : "model.gml";

    // Parse the CityGML document into the in-memory city model
    auto reader = ecitygml::GmlReader::from_path(path);
    if (!reader.is_ok()) return 1;
    auto city_model = std::move(reader).ok().value()->finish();
    if (!city_model.is_ok()) return 1;
    auto model = std::move(city_model).ok().value();

    // Sum up the areas of the LOD2 multi-surfaces of all wall surfaces;
    // other feature types, walls without an LOD2 multi-surface, and areas
    // that cannot be computed are skipped
    double total_area = 0.0;
    auto features = model->iter_features();
    while (auto feature = features->next()) {
        const auto* wall = ecitygml::WallSurface::try_from(*feature);
        if (!wall) continue;
        const auto* surface_property = wall->lod2_multi_surface();
        if (!surface_property) continue;
        const auto* surface = surface_property->object();
        if (!surface) continue;
        auto area = surface->area_3d();
        if (area.is_ok()) total_area += std::move(area).ok().value();
    }

    std::printf("Total area of wall surfaces (LoD2): %.3f m^2\n", total_area);
}
