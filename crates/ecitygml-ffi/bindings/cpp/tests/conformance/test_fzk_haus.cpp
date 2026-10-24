// The cases of crates/ecitygml/tests/conformance/fzk-haus.md.
#include "conformance/conformance.hpp"

#include <ecitygml/AbstractCityObjectKindRef.hpp>
#include <ecitygml/AbstractCityObjectKindRefIterator.hpp>
#include <ecitygml/AbstractFillingSurfaceKind.hpp>
#include <ecitygml/AbstractFillingSurfaceProperty.hpp>
#include <ecitygml/AbstractFillingSurfacePropertyIterator.hpp>
#include <ecitygml/AbstractRingKind.hpp>
#include <ecitygml/AbstractRingKindIterator.hpp>
#include <ecitygml/AbstractSurfaceKind.hpp>
#include <ecitygml/AbstractSurfaceProperty.hpp>
#include <ecitygml/AbstractSurfacePropertyIterator.hpp>
#include <ecitygml/BoundingShape.hpp>
#include <ecitygml/BuildingClassValue.hpp>
#include <ecitygml/BuildingFunctionValue.hpp>
#include <ecitygml/BuildingFunctionValueIterator.hpp>
#include <ecitygml/BuildingPartPropertyIterator.hpp>
#include <ecitygml/BuildingUsageValue.hpp>
#include <ecitygml/BuildingUsageValueIterator.hpp>
#include <ecitygml/CityObjectRelationPropertyIterator.hpp>
#include <ecitygml/CitygmlFormat.hpp>
#include <ecitygml/CompositeSurface.hpp>
#include <ecitygml/Date.hpp>
#include <ecitygml/DateTime.hpp>
#include <ecitygml/DirectPosition.hpp>
#include <ecitygml/DoorSurface.hpp>
#include <ecitygml/ElevationReferenceValue.hpp>
#include <ecitygml/Envelope.hpp>
#include <ecitygml/ExternalReferenceIterator.hpp>
#include <ecitygml/FeatureType.hpp>
#include <ecitygml/GenericAttributeKind.hpp>
#include <ecitygml/GenericAttributeKindIterator.hpp>
#include <ecitygml/GmlReader.hpp>
#include <ecitygml/GmlWriter.hpp>
#include <ecitygml/GroundSurface.hpp>
#include <ecitygml/HRef.hpp>
#include <ecitygml/Height.hpp>
#include <ecitygml/HeightIterator.hpp>
#include <ecitygml/HeightStatusValue.hpp>
#include <ecitygml/Id.hpp>
#include <ecitygml/ImplicitGeometryProperty.hpp>
#include <ecitygml/Length.hpp>
#include <ecitygml/LinearRing.hpp>
#include <ecitygml/Measure.hpp>
#include <ecitygml/MeasureAttribute.hpp>
#include <ecitygml/MultiCurveProperty.hpp>
#include <ecitygml/MultiSurface.hpp>
#include <ecitygml/MultiSurfaceProperty.hpp>
#include <ecitygml/OccupancyIterator.hpp>
#include <ecitygml/Polygon.hpp>
#include <ecitygml/RelativeToTerrain.hpp>
#include <ecitygml/RelativeToWater.hpp>
#include <ecitygml/RoofSurface.hpp>
#include <ecitygml/RoofTypeValue.hpp>
#include <ecitygml/Scale3.hpp>
#include <ecitygml/Shell.hpp>
#include <ecitygml/ShellIterator.hpp>
#include <ecitygml/Solid.hpp>
#include <ecitygml/SolidProperty.hpp>
#include <ecitygml/StringAttribute.hpp>
#include <ecitygml/Triangle.hpp>
#include <ecitygml/TriangleIterator.hpp>
#include <ecitygml/TriangulatedSurface.hpp>
#include <ecitygml/Triangulation.hpp>
#include <ecitygml/TriangulationSkippedIterator.hpp>
#include <ecitygml/Vector3.hpp>
#include <ecitygml/WallSurface.hpp>
#include <ecitygml/WindowSurface.hpp>

#include <algorithm>
#include <array>
#include <string>
#include <utility>
#include <vector>

using conformance::boundaries;
using conformance::building;
using conformance::close;
using conformance::features;
using conformance::first_name;
using ecitygml::FeatureType;

namespace {
const std::string LOD1 = "FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml";
const std::string LOD2 = "FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml";
const std::string LOD3 = "FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml";

/// The first names of the surfaces of one type among the features.
template <typename T>
std::vector<std::string> names_of(const std::vector<std::unique_ptr<ecitygml::AbstractFeatureKindRef>>& features) {
    std::vector<std::string> names;
    for (const auto& feature : features) {
        if (const auto* surface = T::try_from(*feature)) {
            names.push_back(first_name(*surface));
        }
    }
    return names;
}

using Point = std::array<double, 3>;

Point point(const ecitygml::DirectPosition& position) { return {position.x(), position.y(), position.z()}; }

void require_point_close(const Point& actual, const Point& expected) {
    for (size_t i = 0; i < actual.size(); ++i) {
        REQUIRE_THAT(actual[i], close(expected[i]));
    }
}

/// The number of items of a Diplomat iterator.
template <typename Iterator>
int count(const std::unique_ptr<Iterator>& iterator) {
    int n = 0;
    while (iterator->next() != nullptr) {
        ++n;
    }
    return n;
}

/// The value of a successful result.
template <typename Result>
auto ok(Result result) {
    REQUIRE(result.is_ok());
    return std::move(result).ok().value();
}

const ecitygml::Polygon& polygon_of(const ecitygml::AbstractSurfaceProperty& property) {
    REQUIRE(property.object() != nullptr);
    const auto* polygon = ecitygml::Polygon::try_from(*property.object());
    REQUIRE(polygon != nullptr);
    return *polygon;
}

/// The wall surfaces of the city model; the model must outlive them.
std::vector<const ecitygml::WallSurface*> walls(const std::vector<std::unique_ptr<ecitygml::AbstractFeatureKindRef>>& all) {
    std::vector<const ecitygml::WallSurface*> result;
    for (const auto& feature : all) {
        if (const auto* wall = ecitygml::WallSurface::try_from(*feature)) {
            result.push_back(wall);
        }
    }
    return result;
}

std::vector<bool> walls_bounded(const ecitygml::CityModel& city_model) {
    const auto all = features(city_model);
    std::vector<bool> result;
    for (const auto* wall : walls(all)) {
        result.push_back(wall->bounded_by() != nullptr);
    }
    return result;
}

/// The lower corners of the city model's envelope and of the first wall surface's.
std::vector<Point> lower_corners(const ecitygml::CityModel& city_model) {
    const auto all = features(city_model);
    return {
        point(city_model.bounded_by()->envelope()->lower_corner()),
        point(walls(all).front()->bounded_by()->envelope()->lower_corner()),
    };
}

/// The sum of the LoD2 areas of the surfaces of one type among the features.
template <typename T>
double lod2_area(const std::vector<std::unique_ptr<ecitygml::AbstractFeatureKindRef>>& features) {
    double area = 0.0;
    for (const auto& feature : features) {
        if (const auto* surface = T::try_from(*feature)) {
            auto result = surface->lod2_multi_surface()->object()->area_3d();
            REQUIRE(result.is_ok());
            area += std::move(result).ok().value();
        }
    }
    return area;
}
}  // namespace

TEST_CASE("Lod1 city model", "[fzk-haus][lod1]") {
    auto city_model = conformance::read("fzk-haus", LOD1);
    REQUIRE(city_model->city_objects_len() == 1);
    const auto* envelope = city_model->bounded_by()->envelope();
    const auto& lower = envelope->lower_corner();
    const auto& upper = envelope->upper_corner();
    REQUIRE_THAT(lower.x(), close(457842.0));
    REQUIRE_THAT(lower.y(), close(5439083.0));
    REQUIRE_THAT(lower.z(), close(111.8));
    REQUIRE_THAT(upper.x(), close(457854.0));
    REQUIRE_THAT(upper.y(), close(5439093.0));
    REQUIRE_THAT(upper.z(), close(118.317669));
}

TEST_CASE("Lod1 building attributes", "[fzk-haus][lod1]") {
    auto city_model = conformance::read("fzk-haus", LOD1);
    const auto* b = building(*city_model);
    REQUIRE(b->feature_id().as_str() == "UUID_d281adfc-4901-0f52-540b-4cc1a9325f82");
    auto names = b->names();
    REQUIRE(names->next()->value() == "AC14-FZK-Haus");
    REQUIRE(names->next() == nullptr);
    REQUIRE(b->class_()->value() == "1000");
    auto functions = b->functions();
    REQUIRE(functions->next()->value() == "1000");
    REQUIRE(functions->next() == nullptr);
    auto usages = b->usages();
    REQUIRE(usages->next()->value() == "1000");
    REQUIRE(usages->next() == nullptr);
    REQUIRE(b->roof_type()->value() == "1030");
    REQUIRE(b->storeys_above_ground() == 2);
    REQUIRE(b->storeys_below_ground() == 0);

    const auto* date = b->date_of_construction();
    REQUIRE(date != nullptr);
    REQUIRE((date->year() == 2020 && date->month() == 1 && date->day() == 1));
    REQUIRE(b->date_of_demolition() == nullptr);
    auto heights = b->heights();
    const auto* height = heights->next();
    REQUIRE(height != nullptr);
    REQUIRE(heights->next() == nullptr);
    REQUIRE(height->high_reference().value() == "topOfConstruction");
    REQUIRE(height->low_reference().value() == "lowestGroundPoint");
    REQUIRE(height->status() == ecitygml::HeightStatusValue::Measured);
    REQUIRE_THAT(height->length().value(), close(6.52));
    REQUIRE(height->length().uom() == "m");
    REQUIRE(b->occupancies()->next() == nullptr);
    REQUIRE(b->building_parts()->next() == nullptr);
}

TEST_CASE("Lod1 solid", "[fzk-haus][lod1]") {
    auto city_model = conformance::read("fzk-haus", LOD1);
    const auto* b = building(*city_model);
    const auto* solid = b->lod1_solid()->object();
    auto volume = solid->volume_3d();
    REQUIRE(volume.is_ok());
    REQUIRE_THAT(std::move(volume).ok().value(), close(782.1228));
    auto triangulation = solid->triangulate();
    REQUIRE(triangulation.is_ok());
    auto result = std::move(triangulation).ok().value();
    auto triangles = result->surface().triangles();
    int count = 0;
    while (triangles->next() != nullptr) {
        ++count;
    }
    REQUIRE(count == 12);
    REQUIRE_FALSE(result->has_skipped());
    REQUIRE(b->boundaries()->next() == nullptr);
}

TEST_CASE("Lod1 envelope measures", "[fzk-haus][lod1]") {
    auto city_model = conformance::read("fzk-haus", LOD1);
    const auto* envelope = city_model->bounded_by()->envelope();
    require_point_close({envelope->size_x(), envelope->size_y(), envelope->size_z()}, {12.0, 10.0, 6.517669});
    require_point_close(point(*envelope->center()), {457848.0, 5439088.0, 115.0588345});
    REQUIRE_THAT(envelope->volume(), close(782.12028));
    REQUIRE(envelope->contains(envelope->lower_corner()));
    REQUIRE(envelope->contains(envelope->upper_corner()));
    const auto at = [](double x, double y, double z) { return ok(ecitygml::DirectPosition::create(x, y, z)); };
    REQUIRE(envelope->contains(*at(457848.0, 5439088.0, 115.0)));
    REQUIRE_FALSE(envelope->contains(*at(457848.0, 5439088.0, 118.4)));
    REQUIRE_FALSE(envelope->contains(*at(457841.9, 5439088.0, 115.0)));
    REQUIRE(city_model->creation_date() == nullptr);
}

TEST_CASE("Lod1 building details", "[fzk-haus][lod1]") {
    auto city_model = conformance::read("fzk-haus", LOD1);
    int buildings = 0;
    for (const auto& feature : features(*city_model)) {
        buildings += feature->feature_type() == FeatureType::Building;
    }
    REQUIRE(buildings == 1);
    const auto* b = building(*city_model);
    REQUIRE(b->id() != nullptr);
    REQUIRE(b->id()->as_str() == "UUID_d281adfc-4901-0f52-540b-4cc1a9325f82");
    const auto* envelope = b->bounded_by()->envelope();
    require_point_close(point(envelope->lower_corner()), {457842.0, 5439083.0, 111.8});
    require_point_close(point(envelope->upper_corner()), {457854.0, 5439093.0, 118.31769});
    REQUIRE(b->lod2_solid() == nullptr);
    REQUIRE(b->lod0_multi_surface() == nullptr);
}

TEST_CASE("Lod1 solid structure", "[fzk-haus][lod1]") {
    auto city_model = conformance::read("fzk-haus", LOD1);
    const auto* solid = building(*city_model)->lod1_solid()->object();
    REQUIRE(count(solid->interior()) == 0);
    REQUIRE(count(solid->points()) == 24);
    const auto* shell = solid->exterior();
    REQUIRE(shell != nullptr);
    REQUIRE_THAT(ok(shell->volume_3d()), close(782.1228));
    std::vector<const ecitygml::LinearRing*> rings;
    auto members = shell->members();
    while (const auto* member = members->next()) {
        REQUIRE(member->href() == nullptr);
        const auto& polygon = polygon_of(*member);
        REQUIRE(count(polygon.interior()) == 0);
        REQUIRE(polygon.exterior() != nullptr);
        const auto* ring = ecitygml::LinearRing::try_from(*polygon.exterior());
        REQUIRE(ring != nullptr);
        rings.push_back(ring);
    }
    REQUIRE(rings.size() == 6);
    for (const auto* ring : rings) {
        REQUIRE(count(ring->points()) == 4);
        REQUIRE(ring->area_3d() > 0.0);
    }
    require_point_close(point(*rings[0]->points()->next()), {457842.0, 5439083.0, 111.8});
    REQUIRE_THAT(rings[0]->length_3d(), close(44.0));
    REQUIRE_THAT(rings[0]->area_3d(), close(120.0));
}

TEST_CASE("Lod1 solid triangulation", "[fzk-haus][lod1]") {
    auto city_model = conformance::read("fzk-haus", LOD1);
    const auto* solid = building(*city_model)->lod1_solid()->object();
    auto triangulation = ok(solid->triangulate());
    REQUIRE(count(triangulation->skipped()) == 0);
    const auto& surface = triangulation->surface();
    REQUIRE_THAT(ok(surface.area_3d()), close(526.77836));
    REQUIRE(count(surface.points()) == 36);
    auto triangles = surface.triangles();
    const auto* triangle = triangles->next();
    REQUIRE(triangle != nullptr);
    REQUIRE_THAT(triangle->a().z(), close(111.8));
    REQUIRE_THAT(triangle->area(), close(60.0));
    const auto* shell = solid->exterior();
    REQUIRE(count(ok(shell->triangulate())->surface().triangles()) == 12);
    const auto& first = polygon_of(*shell->members()->next());
    REQUIRE(count(ok(first.triangulate())->surface().triangles()) == 2);
}

TEST_CASE("Lod1 apply scale", "[fzk-haus][lod1]") {
    auto city_model = conformance::read("fzk-haus", LOD1);
    city_model->apply_scale(ecitygml::Scale3{2.0, 3.0, 0.5});
    const auto* envelope = city_model->bounded_by()->envelope();
    require_point_close({envelope->size_x(), envelope->size_y(), envelope->size_z()}, {24.0, 30.0, 3.2588345});
}

TEST_CASE("Lod2 boundary surfaces", "[fzk-haus][lod2]") {
    auto city_model = conformance::read("fzk-haus", LOD2);
    const auto features = boundaries(*building(*city_model));
    std::vector<FeatureType> types;
    for (const auto& feature : features) {
        types.push_back(feature->feature_type());
    }
    REQUIRE(types == std::vector<FeatureType>{FeatureType::WallSurface, FeatureType::WallSurface,
                                              FeatureType::WallSurface, FeatureType::RoofSurface,
                                              FeatureType::WallSurface, FeatureType::RoofSurface,
                                              FeatureType::GroundSurface});
    REQUIRE(names_of<ecitygml::WallSurface>(features) ==
            std::vector<std::string>{"Outer Wall 1 (West)", "Outer Wall 2 (South)", "Outer Wall 3 (East)",
                                     "Outer Wall 4 (North)"});
    REQUIRE(names_of<ecitygml::RoofSurface>(features) == std::vector<std::string>{"Roof 1 (North)", "Roof 2 (South)"});
    REQUIRE(names_of<ecitygml::GroundSurface>(features) == std::vector<std::string>{"Base Surface"});
}

TEST_CASE("Lod2 surface areas", "[fzk-haus][lod2]") {
    auto city_model = conformance::read("fzk-haus", LOD2);
    const auto features = boundaries(*building(*city_model));
    REQUIRE_THAT(lod2_area<ecitygml::WallSurface>(features), close(188.62887820601463));
    REQUIRE_THAT(lod2_area<ecitygml::RoofSurface>(features), close(138.56406460961398));
    REQUIRE_THAT(lod2_area<ecitygml::GroundSurface>(features), close(120.0));
}

TEST_CASE("Lod2 generic attributes", "[fzk-haus][lod2]") {
    auto city_model = conformance::read("fzk-haus", LOD2);
    const auto* b = building(*city_model);
    auto attributes = b->generic_attributes();
    const auto* area = attributes->next();
    const auto* method = attributes->next();
    const auto* landmarked = attributes->next();
    REQUIRE((area != nullptr && method != nullptr && landmarked != nullptr));
    REQUIRE(attributes->next() == nullptr);
    const auto* measure = ecitygml::MeasureAttribute::try_from(*area);
    REQUIRE(measure != nullptr);
    REQUIRE(area->name() == "GrossPlannedArea");
    REQUIRE_THAT(measure->value().value(), close(120.0));
    REQUIRE(measure->value().uom() == "m2");
    REQUIRE(method->name() == "ConstructionMethod");
    REQUIRE(method->as_string()->value() == "New Building");
    REQUIRE(landmarked->name() == "IsLandmarked");
    REQUIRE(landmarked->as_string()->value() == "NO");
    REQUIRE(b->external_references()->next() == nullptr);
}

TEST_CASE("Lod2 solid unresolved", "[fzk-haus][lod2]") {
    auto city_model = conformance::read("fzk-haus", LOD2);
    const auto* solid = building(*city_model)->lod2_solid()->object();
    REQUIRE(solid->volume_3d().is_err());
}

TEST_CASE("Lod2 building details", "[fzk-haus][lod2]") {
    auto city_model = conformance::read("fzk-haus", LOD2);
    const auto* b = building(*city_model);
    REQUIRE(b->relative_to_terrain() == ecitygml::RelativeToTerrain::EntirelyAboveTerrain);
    REQUIRE_FALSE(b->relative_to_water().has_value());
    const auto* created = b->creation_date();
    REQUIRE(created != nullptr);
    REQUIRE((created->year() == 2017 && created->month() == 1 && created->day() == 23 && created->hour() == 0));
    REQUIRE(created->offset_seconds() == 3600);
    REQUIRE(created->timestamp() == 1485126000);
    REQUIRE(b->termination_date() == nullptr);
    REQUIRE(b->valid_from() == nullptr);
    REQUIRE(b->valid_to() == nullptr);

    REQUIRE(b->class_()->value() == "1000");
    auto functions = b->functions();
    REQUIRE(functions->next()->value() == "1000");
    REQUIRE(functions->next() == nullptr);
    auto usages = b->usages();
    REQUIRE(usages->next()->value() == "1000");
    REQUIRE(usages->next() == nullptr);
    REQUIRE(b->roof_type()->value() == "1030");
    REQUIRE(b->storeys_above_ground() == 2);
    REQUIRE(b->storeys_below_ground() == 0);
    const auto* date = b->date_of_construction();
    REQUIRE(date != nullptr);
    REQUIRE((date->year() == 2020 && date->month() == 1 && date->day() == 1));
    REQUIRE(b->date_of_demolition() == nullptr);
    auto heights = b->heights();
    const auto* height = heights->next();
    REQUIRE(height != nullptr);
    REQUIRE(heights->next() == nullptr);
    REQUIRE(height->high_reference().value() == "topOfConstruction");
    REQUIRE(height->low_reference().value() == "lowestGroundPoint");
    REQUIRE(height->status() == ecitygml::HeightStatusValue::Measured);
    REQUIRE_THAT(height->length().value(), close(6.52));
    REQUIRE(height->length().uom() == "m");

    REQUIRE(count(b->occupancies()) == 0);
    REQUIRE(count(b->related_to()) == 0);
    REQUIRE(b->lod1_solid() == nullptr);
    REQUIRE(b->bounded_by() == nullptr);
    REQUIRE(b->lod1_terrain_intersection_curve() == nullptr);
    REQUIRE(b->lod2_terrain_intersection_curve() == nullptr);
    REQUIRE(b->lod3_terrain_intersection_curve() == nullptr);
    REQUIRE(b->lod1_implicit_representation() == nullptr);
    REQUIRE(b->lod2_implicit_representation() == nullptr);
    REQUIRE(b->lod3_implicit_representation() == nullptr);
}

TEST_CASE("Lod2 boundary ids", "[fzk-haus][lod2]") {
    auto city_model = conformance::read("fzk-haus", LOD2);
    std::vector<std::string> ids;
    auto properties = building(*city_model)->boundaries();
    while (const auto* property = properties->next()) {
        REQUIRE(property->href() == nullptr);
        ids.emplace_back(property->object()->feature_id().as_str());
    }
    REQUIRE(ids == std::vector<std::string>{
                       "GML_5856d7ad-5e34-498a-817b-9544bfbb1475",
                       "GML_d38cf762-c29d-4491-88c9-bdc89e141978",
                       "GML_8e5db638-e46a-4739-a98a-2fc2d39c9069",
                       "GML_875d470b-32b4-4985-a4c8-0f02caa342a2",
                       "GML_0f30f604-e70d-4dfe-ba35-853bc69609cc",
                       "GML_eeb6796a-e261-4d3b-a6f2-475940cca80a",
                       "GML_257a8dde-8194-4ca3-b581-abd591dcd6a3",
                   });
}

TEST_CASE("Lod2 wall surface", "[fzk-haus][lod2]") {
    auto city_model = conformance::read("fzk-haus", LOD2);
    const auto features = boundaries(*building(*city_model));
    const auto wall_surfaces = walls(features);
    const auto* wall = wall_surfaces.front();
    REQUIRE(wall->id() != nullptr);
    REQUIRE(wall->id()->as_str() == "GML_5856d7ad-5e34-498a-817b-9544bfbb1475");
    REQUIRE(wall->lod0_multi_curve() == nullptr);
    REQUIRE(wall->lod0_multi_surface() == nullptr);
    REQUIRE(wall->lod1_multi_surface() == nullptr);
    REQUIRE_FALSE(wall->relative_to_terrain().has_value());
    REQUIRE(wall->creation_date() == nullptr);
    REQUIRE(count(wall->generic_attributes()) == 0);
    REQUIRE(wall->bounded_by() != nullptr);
    const auto* multi_surface = wall->lod2_multi_surface()->object();
    REQUIRE(count(multi_surface->surface_member()) == 1);
    REQUIRE(count(ok(multi_surface->triangulate())->surface().triangles()) == 3);
    for (const auto* w : wall_surfaces) {
        REQUIRE(count(w->filling_surfaces()) == 0);
    }
    const ecitygml::GroundSurface* ground = nullptr;
    for (const auto& feature : features) {
        ground = ground != nullptr ? ground : ecitygml::GroundSurface::try_from(*feature);
    }
    REQUIRE(ground != nullptr);
    const auto& ground_polygon = polygon_of(*ground->lod2_multi_surface()->object()->surface_member()->next());
    REQUIRE(count(ground_polygon.exterior()->points()) == 4);
}

TEST_CASE("Lod2 generic attribute kinds", "[fzk-haus][lod2]") {
    auto city_model = conformance::read("fzk-haus", LOD2);
    auto attributes = building(*city_model)->generic_attributes();
    const auto* area = attributes->next();
    const auto* method = attributes->next();
    const auto* landmarked = attributes->next();
    REQUIRE((area != nullptr && method != nullptr && landmarked != nullptr));
    REQUIRE(area->as_string() == nullptr);
    REQUIRE(ecitygml::MeasureAttribute::try_from(*method) == nullptr);
    REQUIRE(ecitygml::MeasureAttribute::try_from(*landmarked) == nullptr);
}

TEST_CASE("Lod2 city objects", "[fzk-haus][lod2]") {
    auto city_model = conformance::read("fzk-haus", LOD2);
    std::vector<FeatureType> objects;
    auto iterator = city_model->iter_city_objects();
    while (auto object = iterator->next()) {
        objects.push_back(object->feature_type());
    }
    REQUIRE(objects == std::vector<FeatureType>{FeatureType::Building, FeatureType::WallSurface,
                                                FeatureType::WallSurface, FeatureType::WallSurface,
                                                FeatureType::RoofSurface, FeatureType::WallSurface,
                                                FeatureType::RoofSurface, FeatureType::GroundSurface});
    const auto all = features(*city_model);
    REQUIRE(all.front()->feature_type() == FeatureType::CityModel);
    int city_models = 0;
    for (const auto& feature : all) {
        city_models += feature->feature_type() == FeatureType::CityModel;
    }
    REQUIRE(city_models == 1);
}

TEST_CASE("Lod2 object bounds", "[fzk-haus][lod2]") {
    auto reader = ok(ecitygml::GmlReader::from_path(fixture("fzk-haus/" + LOD2)));
    reader->with_rebuild_object_bounds(false);
    auto city_model = ok(reader->finish());
    REQUIRE(walls_bounded(*city_model) == std::vector<bool>(4, false));
    city_model->recompute_child_bounding_shapes();
    REQUIRE(walls_bounded(*city_model) == std::vector<bool>(4, true));
}

TEST_CASE("Lod2 apply translation", "[fzk-haus][lod2]") {
    auto city_model = conformance::read("fzk-haus", LOD2);
    for (const auto& corner : lower_corners(*city_model)) {
        require_point_close(corner, {457842.0, 5439083.0, 111.8});
    }
    city_model->apply_translation(ecitygml::Vector3{-100.0, 200.0, 10.0});
    for (const auto& corner : lower_corners(*city_model)) {
        require_point_close(corner, {457742.0, 5439283.0, 121.8});
    }
}

TEST_CASE("Lod3 doors and windows", "[fzk-haus][lod3]") {
    auto city_model = conformance::read("fzk-haus", LOD3);
    const auto all = features(*city_model);
    std::vector<std::string> doors;
    double area = 0.0;
    int windows = 0;
    for (const auto& feature : all) {
        if (const auto* door = ecitygml::DoorSurface::try_from(*feature)) {
            doors.push_back(first_name(*door));
            auto result = door->lod3_multi_surface()->object()->area_3d();
            REQUIRE(result.is_ok());
            area += std::move(result).ok().value();
        }
        windows += ecitygml::WindowSurface::try_from(*feature) != nullptr;
    }
    REQUIRE(doors == std::vector<std::string>{"Door West", "Door South"});
    REQUIRE_THAT(area, close(6.803850099444389));
    REQUIRE(windows == 11);
}

TEST_CASE("Lod3 west wall fillings", "[fzk-haus][lod3]") {
    auto city_model = conformance::read("fzk-haus", LOD3);
    const auto features = boundaries(*building(*city_model));
    const auto* wall = ecitygml::WallSurface::try_from(*features.front());
    REQUIRE(wall != nullptr);
    REQUIRE(first_name(*wall) == "Outer Wall 1 (West)");
    std::vector<std::pair<FeatureType, std::string>> fillings;
    auto properties = wall->filling_surfaces();
    while (const auto* property = properties->next()) {
        const auto* filling = property->object();
        fillings.emplace_back(filling->feature_type(), first_name(*filling));
    }
    REQUIRE(fillings == std::vector<std::pair<FeatureType, std::string>>{
                            {FeatureType::WindowSurface, "Window Round"},
                            {FeatureType::WindowSurface, "Window North"},
                            {FeatureType::DoorSurface, "Door West"},
                            {FeatureType::WindowSurface, "Window South"},
                        });
}

TEST_CASE("Lod3 building details", "[fzk-haus][lod3]") {
    auto city_model = conformance::read("fzk-haus", LOD3);
    REQUIRE(city_model->city_objects_len() == 1);
    const auto* b = building(*city_model);
    REQUIRE(b->relative_to_terrain() == ecitygml::RelativeToTerrain::EntirelyAboveTerrain);
    const auto features = boundaries(*b);
    std::vector<FeatureType> types;
    for (const auto& feature : features) {
        types.push_back(feature->feature_type());
    }
    REQUIRE(types == std::vector<FeatureType>{FeatureType::WallSurface, FeatureType::WallSurface,
                                              FeatureType::WallSurface, FeatureType::RoofSurface,
                                              FeatureType::WallSurface, FeatureType::RoofSurface,
                                              FeatureType::GroundSurface});
    for (const auto* wall : walls(features)) {
        REQUIRE(wall->lod3_multi_surface() != nullptr);
    }
}

TEST_CASE("Lod3 fillings", "[fzk-haus][lod3]") {
    auto city_model = conformance::read("fzk-haus", LOD3);
    const auto features = boundaries(*building(*city_model));
    std::vector<int> per_wall;
    int doors = 0;
    int windows = 0;
    for (const auto* wall : walls(features)) {
        per_wall.push_back(count(wall->filling_surfaces()));
        auto properties = wall->filling_surfaces();
        while (const auto* property = properties->next()) {
            REQUIRE(property->href() == nullptr);
            const auto* filling = property->object();
            doors += filling->feature_type() == FeatureType::DoorSurface;
            windows += filling->feature_type() == FeatureType::WindowSurface;
            REQUIRE(ok(filling->lod3_multi_surface()->object()->area_3d()) > 0.0);
        }
    }
    REQUIRE(per_wall == std::vector<int>{4, 3, 3, 3});
    REQUIRE((doors == 2 && windows == 11));
    for (const auto& feature : features) {
        if (const auto* roof = ecitygml::RoofSurface::try_from(*feature)) {
            REQUIRE(count(roof->filling_surfaces()) == 0);
        }
    }

    const auto all = conformance::features(*city_model);
    double window_area = 0.0;
    std::vector<std::string> door_ids;
    for (const auto& feature : all) {
        if (const auto* window = ecitygml::WindowSurface::try_from(*feature)) {
            window_area += ok(window->lod3_multi_surface()->object()->area_3d());
        }
        if (const auto* door = ecitygml::DoorSurface::try_from(*feature)) {
            door_ids.emplace_back(door->feature_id().as_str());
            REQUIRE(door->lod2_multi_surface() == nullptr);
        }
    }
    REQUIRE_THAT(window_area, close(23.168802611529827));
    REQUIRE(door_ids ==
            std::vector<std::string>{"GML_c137f11d-9a8c-4126-9aeb-9a6c9b4e1cbd", "GML_2d6ddf04-ee56-42a1-a9b1-b47e4181a629"});
}

TEST_CASE("Lod3 city objects", "[fzk-haus][lod3]") {
    auto city_model = conformance::read("fzk-haus", LOD3);
    std::vector<FeatureType> objects;
    auto iterator = city_model->iter_city_objects();
    while (auto object = iterator->next()) {
        objects.push_back(object->feature_type());
    }
    REQUIRE(objects.size() == 21);
    std::vector<int> counts;
    for (auto type : {FeatureType::Building, FeatureType::WallSurface, FeatureType::RoofSurface,
                      FeatureType::GroundSurface, FeatureType::DoorSurface, FeatureType::WindowSurface}) {
        counts.push_back(static_cast<int>(std::count(objects.begin(), objects.end(), type)));
    }
    REQUIRE(counts == std::vector<int>{1, 4, 2, 1, 2, 11});
    const auto all = features(*city_model);
    REQUIRE(all.size() == 22);
    REQUIRE(all.front()->feature_type() == FeatureType::CityModel);
}

TEST_CASE("Lod3 composite surface", "[fzk-haus][lod3]") {
    auto city_model = conformance::read("fzk-haus", LOD3);
    const auto features = boundaries(*building(*city_model));
    const auto* wall = ecitygml::WallSurface::try_from(*features.front());
    REQUIRE(wall != nullptr);
    auto members = wall->lod3_multi_surface()->object()->surface_member();
    const auto* member = members->next();
    REQUIRE((member != nullptr && member->object() != nullptr));
    const auto* composite = ecitygml::CompositeSurface::try_from(*member->object());
    REQUIRE(composite != nullptr);
    REQUIRE(count(composite->surface_member()) == 85);
    const auto& first = polygon_of(*composite->surface_member()->next());
    require_point_close(point(*first.exterior()->points()->next()), {457842.0, 5439088.49240388, 115.913175911167});
}

TEST_CASE("Lod3 round trip", "[fzk-haus][lod3]") {
    auto city_model = conformance::read("fzk-haus", LOD3);
    auto writer = ecitygml::GmlWriter::create(ecitygml::CitygmlFormat::Gml);
    REQUIRE(writer->finish(*city_model).is_ok());
    auto written = ok(ecitygml::GmlReader::create(writer->data(), ecitygml::CitygmlFormat::Gml)->finish());
    const auto types = [](const ecitygml::CityModel& model) {
        std::vector<FeatureType> result;
        for (const auto& feature : features(model)) {
            result.push_back(feature->feature_type());
        }
        return result;
    };
    REQUIRE(types(*written) == types(*city_model));
    REQUIRE(building(*written)->feature_id().as_str() == "UUID_d281adfc-4901-0f52-540b-4cc1a9325f82");
    // The `feature_id`s of the building's boundaries, then of the wall surfaces' filling surfaces.
    const auto surface_ids = [](const ecitygml::CityModel& model) {
        std::vector<std::string> ids;
        auto properties = building(model)->boundaries();
        while (const auto* property = properties->next()) {
            ids.emplace_back(property->object()->feature_id().as_str());
        }
        auto walls = building(model)->boundaries();
        while (const auto* property = walls->next()) {
            const auto feature = ecitygml::AbstractFeatureKindRef::from_space_boundary(*property->object());
            if (const auto* wall = ecitygml::WallSurface::try_from(*feature)) {
                auto fillings = wall->filling_surfaces();
                while (const auto* filling = fillings->next()) {
                    ids.emplace_back(filling->object()->feature_id().as_str());
                }
            }
        }
        return ids;
    };
    REQUIRE(surface_ids(*written) == surface_ids(*city_model));
    auto heights = building(*written)->heights();
    const auto* height = heights->next();
    REQUIRE(height != nullptr);
    REQUIRE(heights->next() == nullptr);
    REQUIRE(height->high_reference().value() == "topOfConstruction");
    REQUIRE(height->low_reference().value() == "lowestGroundPoint");
    REQUIRE(height->status() == ecitygml::HeightStatusValue::Measured);
    REQUIRE_THAT(height->length().value(), close(6.52));
    REQUIRE(height->length().uom() == "m");
}
