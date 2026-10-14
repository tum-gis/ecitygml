// Exports the building geometry of a CityGML file to a Wavefront OBJ file.
//
// Shows how to get triangles out of CityGML geometry for your own file format or renderer:
// `triangulate()` turns a multi surface or solid into a `Triangulation`, whose `surface()` is a
// triangulated surface; each `Triangle` has its corners `a()`, `b()` and `c()`. Every wall, roof and
// ground surface, door and window becomes a named OBJ group, using its highest level of detail;
// buildings without such surfaces fall back to their highest LoD solid.
//
// Built by bindings/cpp/CMakeLists.txt (`mise run build:bindings:cpp`), which also runs it as a test.
//
// Usage: 06_export_obj input.gml output.obj
//
// Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml:
//
//     Wrote 48 vertices, 16 triangles, 7 groups

#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
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
#include <ecitygml/Building.hpp>
#include <ecitygml/CityModel.hpp>
#include <ecitygml/DirectPosition.hpp>
#include <ecitygml/Error.hpp>
#include <ecitygml/FeatureType.hpp>
#include <ecitygml/GmlReader.hpp>
#include <ecitygml/GroundSurface.hpp>
#include <ecitygml/Id.hpp>
#include <ecitygml/MultiSurface.hpp>
#include <ecitygml/MultiSurfaceProperty.hpp>
#include <ecitygml/RoofSurface.hpp>
#include <ecitygml/Solid.hpp>
#include <ecitygml/SolidProperty.hpp>
#include <ecitygml/Triangle.hpp>
#include <ecitygml/TriangleIterator.hpp>
#include <ecitygml/TriangulatedSurface.hpp>
#include <ecitygml/Triangulation.hpp>
#include <ecitygml/WallSurface.hpp>

namespace {
/// Writes OBJ groups as they come: `g` starts a group, `v` adds a vertex, `f` a triangle of the last
/// three vertices (OBJ indices are 1-based and count all vertices written so far).
class ObjWriter {
  public:
    explicit ObjWriter(std::ofstream &file) : file_(file) {}

    /// Writes the triangles of anything with `triangulate()`, e.g. a multi surface or solid; throws a
    /// `std::runtime_error` if the triangulation fails.
    template <typename Geometry>
    void write_group(const std::string &name, const Geometry &geometry) {
        auto triangulation = geometry.triangulate();
        if (triangulation.is_err()) {
            throw std::runtime_error(std::move(triangulation).err().value()->message());
        }
        file_ << "g " << name << "\n";
        ++groups;
        // Keep the triangulation alive while iterating: its triangles are borrowed from it.
        const std::unique_ptr<ecitygml::Triangulation> owned = std::move(triangulation).ok().value();
        auto triangles_iterator = owned->surface().triangles();
        char line[128];
        while (const auto *triangle = triangles_iterator->next()) {
            for (const auto *corner : {&triangle->a(), &triangle->b(), &triangle->c()}) {
                // %.6f like the other languages, independent of the stream's locale.
                std::snprintf(line, sizeof line, "v %.6f %.6f %.6f\n", corner->x(), corner->y(), corner->z());
                file_ << line;
            }
            file_ << "f " << vertices + 1 << " " << vertices + 2 << " " << vertices + 3 << "\n";
            vertices += 3;
            ++triangles;
        }
    }

    std::size_t vertices = 0;
    std::size_t triangles = 0;
    std::size_t groups = 0;

  private:
    std::ofstream &file_;
};

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

template <typename Surface>
void write_surface(ObjWriter &obj, const std::string &prefix, const Surface &surface, const std::string &type_name) {
    if (const auto *multi_surface = highest_lod_multi_surface(surface)) {
        obj.write_group(prefix + "_" + type_name + "_" + std::string(surface.feature_id().as_str()), *multi_surface);
    }
}

/// Writes a wall, roof or ground surface and its doors and windows (`feature_type()` names their type).
template <typename Surface>
void write_surface_with_fillings(ObjWriter &obj, const std::string &prefix, const Surface &surface,
                                 const std::string &type_name) {
    write_surface(obj, prefix, surface, type_name);
    auto fillings = surface.filling_surfaces();
    while (const auto *property = fillings->next()) {
        if (const auto *filling = property->object()) {
            write_surface(obj, prefix, *filling, filling->feature_type().to_string());
        }
    }
}

void export_building(ObjWriter &obj, const ecitygml::Building &building) {
    const std::string prefix(building.feature_id().as_str());
    bool has_surfaces = false;
    auto boundaries = building.boundaries();
    while (const auto *property = boundaries->next()) {
        const auto *boundary = property->object();
        if (boundary == nullptr) {
            continue;
        }
        auto feature = ecitygml::AbstractFeatureKindRef::from_space_boundary(*boundary);
        if (const auto *wall = ecitygml::WallSurface::try_from(*feature)) {
            write_surface_with_fillings(obj, prefix, *wall, "WallSurface");
        } else if (const auto *roof = ecitygml::RoofSurface::try_from(*feature)) {
            write_surface_with_fillings(obj, prefix, *roof, "RoofSurface");
        } else if (const auto *ground = ecitygml::GroundSurface::try_from(*feature)) {
            write_surface_with_fillings(obj, prefix, *ground, "GroundSurface");
        } else {
            continue;
        }
        has_surfaces = true;
    }
    if (has_surfaces) {
        return;
    }
    int lod = 3;
    for (const auto *property : {building.lod3_solid(), building.lod2_solid(), building.lod1_solid()}) {
        if (property != nullptr && property->object() != nullptr) {
            obj.write_group(prefix + "_LoD" + std::to_string(lod) + "Solid", *property->object());
            return;
        }
        --lod;
    }
}
}  // namespace

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "usage: 06_export_obj input.gml output.obj\n";
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

    std::ofstream file(argv[2]);
    if (!file) {
        std::cerr << "error: cannot create " << argv[2] << "\n";
        return 1;
    }
    ObjWriter obj(file);
    try {
        auto features = city_model->iter_features();
        while (auto feature = features->next()) {
            if (const auto *building = ecitygml::Building::try_from(*feature)) {
                export_building(obj, *building);
            }
        }
    } catch (const std::runtime_error &error) {
        std::cerr << "error: " << error.what() << "\n";
        return 1;
    }
    std::cout << "Wrote " << obj.vertices << " vertices, " << obj.triangles << " triangles, " << obj.groups
              << " groups\n";
    return 0;
}
