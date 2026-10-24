// The cases of crates/ecitygml/tests/api/geometry.md.
#include "api.hpp"

#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <ecitygml/AbstractCurveKind.hpp>
#include <ecitygml/AbstractCurveProperty.hpp>
#include <ecitygml/AbstractCurvePropertyIterator.hpp>
#include <ecitygml/AbstractFeatureKindRef.hpp>
#include <ecitygml/AbstractFeatureKindRefIterator.hpp>
#include <ecitygml/AbstractRingKind.hpp>
#include <ecitygml/AbstractRingKindIterator.hpp>
#include <ecitygml/AbstractSurfaceKind.hpp>
#include <ecitygml/AbstractSurfacePatchKind.hpp>
#include <ecitygml/AbstractSurfacePatchKindIterator.hpp>
#include <ecitygml/AbstractSurfaceProperty.hpp>
#include <ecitygml/AbstractSurfacePropertyIterator.hpp>
#include <ecitygml/Building.hpp>
#include <ecitygml/CompositeSurface.hpp>
#include <ecitygml/DirectPosition.hpp>
#include <ecitygml/DirectPositionIterator.hpp>
#include <ecitygml/Envelope.hpp>
#include <ecitygml/GeometryType.hpp>
#include <ecitygml/GroundSurface.hpp>
#include <ecitygml/Id.hpp>
#include <ecitygml/ImplicitGeometry.hpp>
#include <ecitygml/ImplicitGeometryProperty.hpp>
#include <ecitygml/LinearRing.hpp>
#include <ecitygml/MultiCurve.hpp>
#include <ecitygml/MultiCurveProperty.hpp>
#include <ecitygml/MultiSurface.hpp>
#include <ecitygml/MultiSurfaceProperty.hpp>
#include <ecitygml/Point.hpp>
#include <ecitygml/PointProperty.hpp>
#include <ecitygml/Polygon.hpp>
#include <ecitygml/PolygonPatch.hpp>
#include <ecitygml/Shell.hpp>
#include <ecitygml/Solid.hpp>
#include <ecitygml/SolidProperty.hpp>
#include <ecitygml/SolitaryVegetationObject.hpp>
#include <ecitygml/Storey.hpp>
#include <ecitygml/Surface.hpp>
#include <ecitygml/TinProperty.hpp>
#include <ecitygml/TinRelief.hpp>
#include <ecitygml/TrafficSpace.hpp>
#include <ecitygml/Triangle.hpp>
#include <ecitygml/TriangleIterator.hpp>
#include <ecitygml/TriangulatedSurface.hpp>
#include <ecitygml/Triangulation.hpp>

#include <array>
#include <string>
#include <utility>
#include <vector>

using Catch::Matchers::WithinAbs;
using ecitygml::ErrorKind;
using ecitygml::GeometryType;

namespace {
const std::string FZK_LOD1 = "fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml";
const std::string FZK_LOD2 = "fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml";
const std::string TUM = "tum-main-entrance/TUM-Main-Entrance.gml";
const std::string ASAM_ROAD_SHAPE = "asam-opendrive/ASAM-UC_RoadShape.gml";
const std::string RAILWAY = "railway-scene/Railway_Scene_LoD3__v3-thinned.gml";
const std::string OGC_GARAGE = "ogc-citygml-3.0-encodings/Building_and_garage_LOD2-EPSG25832.gml";
const std::string OGC_UNITS = "ogc-citygml-3.0-encodings/BuildingUnits_Storeys_xlink.gml";
const std::string OGC_ROAD_OVER_BRIDGE =
    "ogc-citygml-3.0-encodings/Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml";

using Point = std::array<double, 3>;

/// The features that `T::try_from` accepts; the model must outlive them.
template <typename T>
std::vector<const T*> all_of(const ecitygml::CityModel& city_model) {
    std::vector<const T*> result;
    auto features = city_model.iter_features();
    while (auto feature = features->next()) {
        if (const auto* typed = T::try_from(*feature)) {
            result.push_back(typed);
        }
    }
    return result;
}

template <typename T>
const T& with_id(const std::vector<const T*>& features, const std::string& id) {
    for (const auto* feature : features) {
        if (feature->feature_id().as_str() == id) {
            return *feature;
        }
    }
    FAIL("no feature " << id);
    throw;
}

/// The number of items of an iterator.
template <typename Iterator>
size_t count(std::unique_ptr<Iterator> iterator) {
    size_t n = 0;
    while (iterator->next()) {
        ++n;
    }
    return n;
}

template <typename T>
T ok(diplomat::result<T, std::unique_ptr<ecitygml::Error>> result) {
    REQUIRE(result.is_ok());
    return std::move(std::move(result).ok().value());
}

void require_position(const ecitygml::DirectPosition& actual, const Point& expected) {
    REQUIRE_THAT(actual.x(), WithinAbs(expected[0], 1e-6));
    REQUIRE_THAT(actual.y(), WithinAbs(expected[1], 1e-6));
    REQUIRE_THAT(actual.z(), WithinAbs(expected[2], 1e-6));
}

void require_envelope(const std::unique_ptr<ecitygml::Envelope>& envelope, const Point& lower, const Point& upper) {
    REQUIRE(envelope != nullptr);
    require_position(envelope->lower_corner(), lower);
    require_position(envelope->upper_corner(), upper);
}
}  // namespace

TEST_CASE("Compute envelope", "[api][geometry]") {
    auto lod1 = read(fixture(FZK_LOD1));
    const auto* solid = all_of<ecitygml::Building>(*lod1)[0]->lod1_solid()->object();
    const Point lower{457842.0, 5439083.0, 111.8};
    const Point upper{457854.0, 5439093.0, 118.31769};
    require_envelope(solid->compute_envelope(), lower, upper);
    const auto* shell = solid->exterior();
    REQUIRE(shell != nullptr);
    require_envelope(shell->compute_envelope(), lower, upper);
    auto triangulation = ok(solid->triangulate());
    require_envelope(triangulation->surface().compute_envelope(), lower, upper);
    const auto* first = ecitygml::Polygon::try_from(*shell->members()->next()->object());
    REQUIRE(first != nullptr);
    const Point ground{457854.0, 5439093.0, 111.8};
    require_envelope(first->compute_envelope(), lower, ground);
    require_envelope(first->exterior()->compute_envelope(), lower, ground);

    auto road_shape = read(fixture(ASAM_ROAD_SHAPE));
    const auto* space = all_of<ecitygml::TrafficSpace>(*road_shape)[0];
    const auto* multi_curve = space->lod2_multi_curve()->object();
    const Point curve_lower{-48.38872036507727, 2.3148451158285663, 0.25};
    const Point curve_upper{-16.661414812688488, 26.674198193965925, 0.25};
    require_envelope(multi_curve->compute_envelope(), curve_lower, curve_upper);
    auto members = multi_curve->curve_member();
    const auto* member = members->next();
    REQUIRE(member != nullptr);
    REQUIRE(members->next() == nullptr);
    require_envelope(member->object()->compute_envelope(), curve_lower, curve_upper);
    const auto* space_solid = space->lod2_solid()->object();
    require_envelope(space_solid->compute_envelope(), {-49.60668801898414, 0.7284798382091271, 0.05},
                     {-15.44344715878162, 28.260563471585364, 4.95});
    REQUIRE(count(space_solid->points()) == 24);

    auto railway = read(fixture(RAILWAY));
    const auto& tree = with_id(all_of<ecitygml::SolitaryVegetationObject>(*railway), "GMLID_SO092422_3593_9527");
    const auto* point = tree.lod3_implicit_representation()->object()->reference_point().object();
    REQUIRE(point != nullptr);
    const Point reference{-568.8000793496976, 457.60044759869743, 105.00139681350242};
    require_envelope(point->compute_envelope(), reference, reference);

    auto garage = read(fixture(OGC_GARAGE));
    const auto* tin = all_of<ecitygml::TinRelief>(*garage)[0]->tin()->object();
    require_envelope(tin->compute_envelope(), {458868.0, 5438343.0, 112.0}, {458892.0, 5438362.0, 114.0});
}

TEST_CASE("Polygon interior rings", "[api][geometry]") {
    auto city_model = read(fixture(TUM));
    const auto grounds = all_of<ecitygml::GroundSurface>(*city_model);
    REQUIRE(grounds.size() == 1);
    const auto* multi_surface = grounds[0]->lod2_multi_surface()->object();
    REQUIRE(count(multi_surface->surface_member()) == 1);
    const auto* polygon = ecitygml::Polygon::try_from(*multi_surface->surface_member()->next()->object());
    REQUIRE(polygon != nullptr);
    REQUIRE(polygon->id()->as_str() == "DEBY_LOD2_4959457_2470b16f-99f0-43c3-9a27-bd4fc3822c91_2_poly");
    const auto* exterior = ecitygml::LinearRing::try_from(*polygon->exterior());
    REQUIRE(exterior != nullptr);
    REQUIRE(count(exterior->points()) == 11);
    REQUIRE_THAT(exterior->area_3d(), WithinAbs(1371.825439453125, 1e-6));
    REQUIRE_THAT(exterior->length_3d(), WithinAbs(150.78554397170106, 1e-6));
    REQUIRE(count(polygon->interior()) == 1);
    const auto* interior = ecitygml::LinearRing::try_from(*polygon->interior()->next());
    REQUIRE(interior != nullptr);
    REQUIRE(count(interior->points()) == 4);
    REQUIRE_THAT(interior->area_3d(), WithinAbs(142.26318359375, 1e-6));
    REQUIRE_THAT(interior->length_3d(), WithinAbs(47.7096809282068, 1e-6));
    REQUIRE_THAT(ok(polygon->area_3d()), WithinAbs(1229.562255859375, 1e-6));
    REQUIRE(count(polygon->points()) == 15);
    require_envelope(polygon->compute_envelope(), {691009.16, 5335994.57, 515.042}, {691054.07, 5336047.41, 515.042});
    auto triangulation = ok(multi_surface->triangulate());
    REQUIRE_FALSE(triangulation->has_skipped());
    REQUIRE(count(triangulation->surface().triangles()) == 15);
    REQUIRE_THAT(ok(triangulation->surface().area_3d()), WithinAbs(1229.5620994984272, 1e-6));
}

TEST_CASE("Composite surface and patches", "[api][geometry]") {
    auto city_model = read(fixture(OGC_ROAD_OVER_BRIDGE));
    const auto& ground = with_id(all_of<ecitygml::GroundSurface>(*city_model), "id_groundsurface1");
    const auto* multi_surface = ground.lod2_multi_surface()->object();
    REQUIRE(multi_surface->id()->as_str() == "id_groundsurface1-0");
    REQUIRE_THAT(ok(multi_surface->area_3d()), WithinAbs(77500.15996032, 1e-6));
    REQUIRE(count(multi_surface->surface_member()) == 1);
    const auto* kind = multi_surface->surface_member()->next()->object();
    REQUIRE(kind->geometry_type() == GeometryType::CompositeSurface);
    REQUIRE(ecitygml::Polygon::try_from(*kind) == nullptr);
    const auto* composite = ecitygml::CompositeSurface::try_from(*kind);
    REQUIRE(composite != nullptr);
    REQUIRE(composite->id()->as_str() == "id_groundsurface1-1");
    REQUIRE_THAT(ok(composite->area_3d()), WithinAbs(77500.15996032, 1e-6));
    REQUIRE(count(composite->points()) == 6);
    require_envelope(composite->compute_envelope(), {0.0, 0.0, 0.0}, {393.7008, 196.8504, 0.0});
    auto triangulation = ok(composite->triangulate());
    REQUIRE_FALSE(triangulation->has_skipped());
    REQUIRE(count(triangulation->surface().triangles()) == 2);

    const std::vector<std::string> ids = {"fme-gen-1a9ac79e-2880-47c7-b7c3-c9df5bc17447",
                                          "fme-gen-545ee504-7440-4cb6-8713-fc8ba21ac163"};
    REQUIRE(count(composite->surface_member()) == ids.size());
    auto members = composite->surface_member();
    for (const auto& id : ids) {
        const auto* surface_kind = members->next()->object();
        REQUIRE(surface_kind->geometry_type() == GeometryType::Surface);
        const auto* surface = ecitygml::Surface::try_from(*surface_kind);
        REQUIRE(surface != nullptr);
        REQUIRE(surface->id()->as_str() == id);
        REQUIRE_THAT(ok(surface->area_3d()), WithinAbs(38750.07998016, 1e-6));
        auto surface_triangulation = ok(surface->triangulate());
        REQUIRE(count(surface_triangulation->surface().triangles()) == 1);
        REQUIRE(count(surface->patches()) == 1);
        const auto* patch = surface->patches()->next();
        REQUIRE(ecitygml::Triangle::try_from(*patch) == nullptr);
        const auto* polygon_patch = ecitygml::PolygonPatch::try_from(*patch);
        REQUIRE(polygon_patch != nullptr);
        REQUIRE(count(polygon_patch->interior()) == 0);
        const auto* exterior = ecitygml::LinearRing::try_from(*polygon_patch->exterior());
        REQUIRE(exterior != nullptr);
        REQUIRE(count(exterior->points()) == 3);
        REQUIRE_THAT(ok(patch->area_3d()), WithinAbs(38750.07998016, 1e-6));
        auto patch_triangulation = ok(patch->triangulate());
        REQUIRE(count(patch_triangulation->surface().triangles()) == 1);
    }
}

TEST_CASE("Triangle patches", "[api][geometry]") {
    auto city_model = read(fixture(OGC_GARAGE));
    const auto* tin = all_of<ecitygml::TinRelief>(*city_model)[0]->tin()->object();
    REQUIRE(count(tin->surface().patches()) == 12);
    auto triangles = tin->triangles();
    const auto* triangle = triangles->next();
    REQUIRE(triangle != nullptr);
    require_position(triangle->a(), {458883.0, 5438362.0, 114.0});
    require_position(triangle->b(), {458868.0, 5438362.0, 112.0});
    require_position(triangle->c(), {458875.0, 5438355.0, 112.0});
    REQUIRE_THAT(triangle->area(), WithinAbs(53.42518132865812, 1e-6));
    REQUIRE(triangle->exterior().geometry_type() == GeometryType::LinearRing);
}

TEST_CASE("Unresolved surface reference", "[api][geometry]") {
    auto city_model = read(fixture(OGC_UNITS));
    const auto& storey = with_id(all_of<ecitygml::Storey>(*city_model), "storey1");
    const auto* multi_surface = storey.lod2_multi_surface()->object();
    REQUIRE(count(multi_surface->surface_member()) == 6);
    require_error(*error_of(multi_surface->area_3d()), ErrorKind::UnresolvedReference,
                  "#Wall_1_PolyID82397_997_453711_16336011");
    REQUIRE(count(multi_surface->points()) == 12);
    require_envelope(multi_surface->compute_envelope(), {457841.1, 5439082.1, 111.1}, {457853.9, 5439092.9, 113.9});
    auto triangulation = ok(multi_surface->triangulate());
    REQUIRE_FALSE(triangulation->has_skipped());
    REQUIRE(count(triangulation->surface().triangles()) == 6);
}

TEST_CASE("Solid unresolved reference", "[api][geometry]") {
    auto city_model = read(fixture(FZK_LOD2));
    const auto* solid = all_of<ecitygml::Building>(*city_model)[0]->lod2_solid()->object();
    require_error(*error_of(solid->volume_3d()), ErrorKind::UnresolvedReference, "#PolyID7350_878_759628_120742");
}

TEST_CASE("Triangulate without members", "[api][geometry]") {
    auto city_model = read(fixture(FZK_LOD2));
    const auto* solid = all_of<ecitygml::Building>(*city_model)[0]->lod2_solid()->object();
    REQUIRE(count(solid->points()) == 0);
    REQUIRE(solid->compute_envelope() == nullptr);
    require_error(*error_of(solid->triangulate()), ErrorKind::InvalidArgument, "requires at least 1 element");
}
