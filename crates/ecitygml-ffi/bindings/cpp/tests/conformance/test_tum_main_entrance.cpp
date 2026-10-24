// The cases of crates/ecitygml/tests/conformance/tum-main-entrance.md.
#include "conformance/conformance.hpp"

#include <ecitygml/AbstractBuildingSubdivisionPropertyIterator.hpp>
#include <ecitygml/AbstractCityObjectKindRef.hpp>
#include <ecitygml/AbstractCityObjectKindRefIterator.hpp>
#include <ecitygml/AbstractSurfaceProperty.hpp>
#include <ecitygml/AbstractSurfacePropertyIterator.hpp>
#include <ecitygml/BoundingShape.hpp>
#include <ecitygml/BuildingFunctionValue.hpp>
#include <ecitygml/BuildingFunctionValueIterator.hpp>
#include <ecitygml/BuildingUsageValueIterator.hpp>
#include <ecitygml/CitygmlFormat.hpp>
#include <ecitygml/DateTime.hpp>
#include <ecitygml/DirectPosition.hpp>
#include <ecitygml/Envelope.hpp>
#include <ecitygml/ExternalReference.hpp>
#include <ecitygml/ExternalReferenceIterator.hpp>
#include <ecitygml/FeatureType.hpp>
#include <ecitygml/GenericAttributeKind.hpp>
#include <ecitygml/GenericAttributeKindIterator.hpp>
#include <ecitygml/GmlReader.hpp>
#include <ecitygml/GmlWriter.hpp>
#include <ecitygml/GroundSurface.hpp>
#include <ecitygml/Height.hpp>
#include <ecitygml/HeightIterator.hpp>
#include <ecitygml/HeightStatusValue.hpp>
#include <ecitygml/Id.hpp>
#include <ecitygml/Length.hpp>
#include <ecitygml/MultiSurface.hpp>
#include <ecitygml/MultiSurfaceProperty.hpp>
#include <ecitygml/OccupancyIterator.hpp>
#include <ecitygml/RoofSurface.hpp>
#include <ecitygml/RoofTypeValue.hpp>
#include <ecitygml/Shell.hpp>
#include <ecitygml/Solid.hpp>
#include <ecitygml/SolidProperty.hpp>
#include <ecitygml/StringAttribute.hpp>
#include <ecitygml/TriangleIterator.hpp>
#include <ecitygml/TriangulatedSurface.hpp>
#include <ecitygml/Triangulation.hpp>
#include <ecitygml/WallSurface.hpp>

#include <array>
#include <string>
#include <utility>
#include <vector>

using conformance::boundaries;
using conformance::building;
using conformance::close;
using conformance::features;
using ecitygml::FeatureType;

namespace {
const std::string DATASET = "tum-main-entrance";
const std::string ENTRANCE = "TUM-Main-Entrance.gml";

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

void require_point_close(const ecitygml::DirectPosition& position, const std::array<double, 3>& expected) {
    REQUIRE_THAT(position.x(), close(expected[0]));
    REQUIRE_THAT(position.y(), close(expected[1]));
    REQUIRE_THAT(position.z(), close(expected[2]));
}

std::vector<FeatureType> feature_types(const ecitygml::CityModel& city_model) {
    std::vector<FeatureType> result;
    for (const auto& feature : features(city_model)) {
        result.push_back(feature->feature_type());
    }
    return result;
}

/// The types of the building's boundaries, in document order.
std::vector<FeatureType> boundary_types() {
    std::vector<FeatureType> types(10, FeatureType::WallSurface);
    types.push_back(FeatureType::GroundSurface);
    types.insert(types.end(), 3, FeatureType::WallSurface);
    types.insert(types.end(), {FeatureType::RoofSurface, FeatureType::RoofSurface, FeatureType::WallSurface});
    return types;
}

/// The area of an inline LoD2 multi surface.
double lod2_area(const ecitygml::MultiSurfaceProperty* property) {
    REQUIRE(property != nullptr);
    REQUIRE(property->href() == nullptr);
    REQUIRE(property->object() != nullptr);
    return ok(property->object()->area_3d());
}
}  // namespace

TEST_CASE("Entrance city model", "[tum-main-entrance]") {
    auto city_model = conformance::read(DATASET, ENTRANCE);
    REQUIRE(city_model->city_objects_len() == 1);
    const auto* envelope = city_model->bounded_by()->envelope();
    require_point_close(envelope->lower_corner(), {689975.68, 5335962.63, 503.0});
    require_point_close(envelope->upper_corner(), {692025.893, 5338012.713, 581.62});
    std::vector<FeatureType> expected{FeatureType::CityModel, FeatureType::Building};
    const auto boundaries = boundary_types();
    expected.insert(expected.end(), boundaries.begin(), boundaries.end());
    REQUIRE(feature_types(*city_model) == expected);
    REQUIRE(count(city_model->iter_city_objects()) == 18);
}

TEST_CASE("Entrance building attributes", "[tum-main-entrance]") {
    auto city_model = conformance::read(DATASET, ENTRANCE);
    const auto* b = building(*city_model);
    REQUIRE(b->feature_id().as_str() == "DEBY_LOD2_4959457");
    REQUIRE(b->names()->next() == nullptr);
    REQUIRE(b->class_() == nullptr);
    auto functions = b->functions();
    const auto* function = functions->next();
    REQUIRE(function != nullptr);
    REQUIRE(functions->next() == nullptr);
    REQUIRE(function->value() == "31001_3020");
    REQUIRE(b->usages()->next() == nullptr);
    REQUIRE(b->roof_type()->value() == "1000");
    REQUIRE(b->storeys_above_ground() == 4);
    REQUIRE_FALSE(b->storeys_below_ground().has_value());

    auto heights = b->heights();
    const auto* height = heights->next();
    REQUIRE(height != nullptr);
    REQUIRE(heights->next() == nullptr);
    REQUIRE(height->high_reference().value() == "topOfConstruction");
    REQUIRE(height->low_reference().value() == "lowestGroundPoint");
    REQUIRE(height->status() == ecitygml::HeightStatusValue::Measured);
    REQUIRE_THAT(height->length().value(), close(19.408));
    REQUIRE(height->length().uom() == "urn:adv:uom:m");

    const auto* created = b->creation_date();
    REQUIRE(created != nullptr);
    REQUIRE((created->year() == 2025 && created->month() == 1 && created->day() == 2));
    REQUIRE((created->hour() == 0 && created->minute() == 0));
    REQUIRE(created->offset_seconds() == 3600);
    REQUIRE(b->bounded_by() == nullptr);
    REQUIRE(b->occupancies()->next() == nullptr);
    REQUIRE(b->building_subdivisions()->next() == nullptr);
}

TEST_CASE("Entrance external reference", "[tum-main-entrance]") {
    auto city_model = conformance::read(DATASET, ENTRANCE);
    auto references = building(*city_model)->external_references();
    const auto* reference = references->next();
    REQUIRE(reference != nullptr);
    REQUIRE(references->next() == nullptr);
    REQUIRE(reference->target_resource() == "DEBYvAAAAABTMIyA");
}

TEST_CASE("Entrance external reference details", "[tum-main-entrance]") {
    auto city_model = conformance::read(DATASET, ENTRANCE);
    auto references = building(*city_model)->external_references();
    const auto* reference = references->next();
    REQUIRE(reference != nullptr);
    REQUIRE(references->next() == nullptr);
    REQUIRE(reference->information_system() == "http://repository.gdi-de.org/schemas/adv/citygml/fdv/art.htm#_9100");
    REQUIRE_FALSE(reference->relation_type().has_value());
}

TEST_CASE("Entrance generic attributes", "[tum-main-entrance]") {
    auto city_model = conformance::read(DATASET, ENTRANCE);
    std::vector<std::pair<std::string, std::string>> attributes;
    auto iterator = building(*city_model)->generic_attributes();
    while (const auto* attribute = iterator->next()) {
        const auto* string = attribute->as_string();
        REQUIRE(string != nullptr);
        attributes.emplace_back(attribute->name(), string->value());
    }
    REQUIRE(attributes == std::vector<std::pair<std::string, std::string>>{
                              {"DatenquelleBodenhoehe", "1100"},
                              {"DatenquelleDachhoehe", "1000"},
                              {"DatenquelleLage", "1000"},
                              {"Gemeindeschluessel", "09162000"},
                              {"HoeheDach", "534.450"},
                              {"HoeheGrund", "515.042"},
                              {"Methode", "2000"},
                              {"NiedrigsteTraufeDesGebaeudes", "527.312"},
                              {"Grundrissaktualitaet", "2025-02-17"},
                              {"Geometrietyp2DReferenz", "3000"},
                          });
}

TEST_CASE("Entrance boundaries", "[tum-main-entrance]") {
    auto city_model = conformance::read(DATASET, ENTRANCE);
    const auto* b = building(*city_model);
    auto properties = b->boundaries();
    while (const auto* property = properties->next()) {
        REQUIRE(property->href() == nullptr);
    }
    const auto features = boundaries(*b);
    std::vector<FeatureType> types;
    for (const auto& feature : features) {
        types.push_back(feature->feature_type());
    }
    REQUIRE(types == boundary_types());

    std::vector<const ecitygml::WallSurface*> walls;
    std::vector<double> roofs;
    std::vector<double> grounds;
    for (const auto& feature : features) {
        if (const auto* wall = ecitygml::WallSurface::try_from(*feature)) {
            walls.push_back(wall);
        } else if (const auto* roof = ecitygml::RoofSurface::try_from(*feature)) {
            roofs.push_back(lod2_area(roof->lod2_multi_surface()));
        } else if (const auto* ground = ecitygml::GroundSurface::try_from(*feature)) {
            grounds.push_back(lod2_area(ground->lod2_multi_surface()));
        }
    }
    REQUIRE(walls.front()->feature_id().as_str() == "DEBY_LOD2_4959457_ca1db42f-9d12-4f41-972c-c7da1614f0a8_2");
    REQUIRE(walls.front()->names()->next() == nullptr);
    double wall_area = 0.0;
    for (const auto* wall : walls) {
        wall_area += lod2_area(wall->lod2_multi_surface());
    }
    REQUIRE_THAT(wall_area, close(3783.3908922901974));
    REQUIRE(roofs.size() == 2);
    REQUIRE_THAT(roofs[0], close(250.233154296875));
    REQUIRE_THAT(roofs[1], close(979.3291015625));
    REQUIRE_THAT(roofs[0] + roofs[1], close(1229.562255859375));
    REQUIRE(grounds.size() == 1);
    REQUIRE_THAT(grounds[0], close(1229.562255859375));
}

TEST_CASE("Entrance wall triangulation", "[tum-main-entrance]") {
    auto city_model = conformance::read(DATASET, ENTRANCE);
    const auto* wall = first<ecitygml::WallSurface>(*city_model);
    REQUIRE(wall != nullptr);
    const auto* multi_surface = wall->lod2_multi_surface()->object();
    REQUIRE(count(multi_surface->surface_member()) == 1);
    REQUIRE_THAT(ok(multi_surface->area_3d()), close(546.6949745937537));
    auto triangulation = ok(multi_surface->triangulate());
    REQUIRE(count(triangulation->surface().triangles()) == 4);
    REQUIRE_FALSE(triangulation->has_skipped());
    REQUIRE_THAT(ok(triangulation->surface().area_3d()), close(546.6949742237184));
}

TEST_CASE("Entrance solid unresolved", "[tum-main-entrance]") {
    auto city_model = conformance::read(DATASET, ENTRANCE);
    const auto* property = building(*city_model)->lod2_solid();
    REQUIRE(property != nullptr);
    REQUIRE(property->href() == nullptr);
    const auto* solid = property->object();
    REQUIRE(solid != nullptr);
    auto members = solid->exterior()->members();
    int n = 0;
    while (const auto* member = members->next()) {
        REQUIRE(member->object() == nullptr);
        ++n;
    }
    REQUIRE(n == 17);
    REQUIRE(solid->volume_3d().is_err());
}

TEST_CASE("Entrance round trip", "[tum-main-entrance]") {
    auto city_model = conformance::read(DATASET, ENTRANCE);
    auto writer = ecitygml::GmlWriter::create(ecitygml::CitygmlFormat::Gml);
    REQUIRE(writer->finish(*city_model).is_ok());
    auto written = ok(ecitygml::GmlReader::create(writer->data(), ecitygml::CitygmlFormat::Gml)->finish());
    REQUIRE(feature_types(*written) == feature_types(*city_model));
    REQUIRE(building(*written)->feature_id().as_str() == "DEBY_LOD2_4959457");
    const auto boundary_ids = [](const ecitygml::CityModel& model) {
        std::vector<std::string> ids;
        auto properties = building(model)->boundaries();
        while (const auto* property = properties->next()) {
            ids.emplace_back(property->object()->feature_id().as_str());
        }
        return ids;
    };
    REQUIRE(boundary_ids(*written) == boundary_ids(*city_model));
}
