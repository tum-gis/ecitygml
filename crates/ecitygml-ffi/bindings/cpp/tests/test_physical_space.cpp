#include "test_helpers.hpp"

#include <ecitygml/AbstractFeatureKindRef.hpp>
#include <ecitygml/AbstractFeatureKindRefIterator.hpp>
#include <ecitygml/AbstractGeometryKind.hpp>
#include <ecitygml/AbstractGeometryProperty.hpp>
#include <ecitygml/Building.hpp>
#include <ecitygml/DirectPosition.hpp>
#include <ecitygml/ErrorKind.hpp>
#include <ecitygml/GeometryType.hpp>
#include <ecitygml/Id.hpp>
#include <ecitygml/ImplicitGeometry.hpp>
#include <ecitygml/ImplicitGeometryProperty.hpp>
#include <ecitygml/MimeTypeValue.hpp>
#include <ecitygml/MultiCurve.hpp>
#include <ecitygml/MultiCurveProperty.hpp>
#include <ecitygml/MultiSurface.hpp>
#include <ecitygml/Point.hpp>
#include <ecitygml/PointProperty.hpp>
#include <ecitygml/TransformationMatrix4x4.hpp>

#include <string>
#include <utility>

namespace {
const ecitygml::Building* first_building(const ecitygml::CityModel& city_model) {
    auto features = city_model.iter_features();
    while (auto feature = features->next()) {
        if (const auto* building = ecitygml::Building::try_from(*feature)) {
            return building;
        }
    }
    return nullptr;
}
}  // namespace

TEST_CASE("Terrain intersection curve and implicit representation", "[physical_space]") {
    // No fixture has these; they are injected into the FZK LoD2 building after its solid.
    auto city_model = read_modified("FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml", "</lod2Solid>", R"(</lod2Solid>
      <lod2TerrainIntersectionCurve><gml:MultiCurve><gml:curveMember><gml:LineString>
        <gml:posList>457842 5439083 111.8 457854 5439083 111.8</gml:posList>
      </gml:LineString></gml:curveMember></gml:MultiCurve></lod2TerrainIntersectionCurve>
      <lod1ImplicitRepresentation>
        <ImplicitGeometry gml:id="tree_prototype">
          <transformationMatrix>2 0 0 10 0 2 0 20 0 0 3 30 0 0 0 1</transformationMatrix>
          <mimeType>model/gltf+json</mimeType>
          <referencePoint><gml:Point><gml:pos>457850 5439090 112</gml:pos></gml:Point></referencePoint>
          <relativeGeometry><gml:Point><gml:pos>0 0 0</gml:pos></gml:Point></relativeGeometry>
        </ImplicitGeometry>
      </lod1ImplicitRepresentation>)");
    const auto* building = first_building(*city_model);
    REQUIRE(building != nullptr);
    REQUIRE(building->lod1_terrain_intersection_curve() == nullptr);
    REQUIRE(building->lod2_terrain_intersection_curve()->object()->length_3d().ok().value() == 12.0);
    REQUIRE(building->lod2_implicit_representation() == nullptr);

    const auto* implicit = building->lod1_implicit_representation()->object();
    REQUIRE(implicit->object_id().as_str() == "tree_prototype");
    REQUIRE(implicit->mime_type()->value() == "model/gltf+json");
    REQUIRE(!implicit->library_object().has_value());
    REQUIRE(implicit->reference_point().object()->pos().z() == 112.0);

    const auto& matrix = implicit->transformation_matrix();
    REQUIRE(matrix.get(0, 3).ok().value() == 10.0);
    REQUIRE(matrix.get(2, 2).ok().value() == 3.0);
    auto out_of_range = matrix.get(4, 0);
    REQUIRE(out_of_range.is_err());
    REQUIRE(std::move(out_of_range).err().value()->kind() == ecitygml::ErrorKind::InvalidArgument);

    const auto* geometry = implicit->relative_geometry()->object();
    REQUIRE(geometry->geometry_type() == ecitygml::GeometryType::Point);
    REQUIRE(ecitygml::Point::try_from(*geometry)->pos().x() == 0.0);
    REQUIRE(ecitygml::MultiSurface::try_from(*geometry) == nullptr);
}
