// The cases of crates/ecitygml/tests/conformance/ogc-citygml-3.0-encodings.md.
#include "conformance/conformance.hpp"

#include <ecitygml/AbstractBuildingSubdivisionKind.hpp>
#include <ecitygml/AbstractBuildingSubdivisionProperty.hpp>
#include <ecitygml/AbstractBuildingSubdivisionPropertyIterator.hpp>
#include <ecitygml/AbstractCityObjectKindRef.hpp>
#include <ecitygml/AbstractCityObjectKindRefIterator.hpp>
#include <ecitygml/AbstractReliefComponentKind.hpp>
#include <ecitygml/AbstractReliefComponentProperty.hpp>
#include <ecitygml/AbstractReliefComponentPropertyIterator.hpp>
#include <ecitygml/AbstractSpaceBoundaryKind.hpp>
#include <ecitygml/AbstractSpaceBoundaryProperty.hpp>
#include <ecitygml/AbstractSpaceBoundaryPropertyIterator.hpp>
#include <ecitygml/AbstractSurfaceProperty.hpp>
#include <ecitygml/AbstractSurfacePropertyIterator.hpp>
#include <ecitygml/AuxiliaryTrafficSpacePropertyIterator.hpp>
#include <ecitygml/BoundingShape.hpp>
#include <ecitygml/Bridge.hpp>
#include <ecitygml/BuildingFunctionValue.hpp>
#include <ecitygml/BuildingFunctionValueIterator.hpp>
#include <ecitygml/BuildingPart.hpp>
#include <ecitygml/BuildingPartProperty.hpp>
#include <ecitygml/BuildingPartPropertyIterator.hpp>
#include <ecitygml/BuildingSubdivisionClassValue.hpp>
#include <ecitygml/BuildingSubdivisionFunctionValue.hpp>
#include <ecitygml/BuildingSubdivisionFunctionValueIterator.hpp>
#include <ecitygml/BuildingSubdivisionUsageValueIterator.hpp>
#include <ecitygml/BuildingUnit.hpp>
#include <ecitygml/BuildingUsageValueIterator.hpp>
#include <ecitygml/CitygmlFormat.hpp>
#include <ecitygml/CityObjectRelation.hpp>
#include <ecitygml/CityObjectRelationProperty.hpp>
#include <ecitygml/CityObjectRelationPropertyIterator.hpp>
#include <ecitygml/Date.hpp>
#include <ecitygml/DateTime.hpp>
#include <ecitygml/DirectPosition.hpp>
#include <ecitygml/Envelope.hpp>
#include <ecitygml/FeatureType.hpp>
#include <ecitygml/GenericAttributeKindIterator.hpp>
#include <ecitygml/GmlReader.hpp>
#include <ecitygml/GmlWriter.hpp>
#include <ecitygml/GroundSurface.hpp>
#include <ecitygml/HRef.hpp>
#include <ecitygml/Height.hpp>
#include <ecitygml/HeightIterator.hpp>
#include <ecitygml/HeightStatusValue.hpp>
#include <ecitygml/Id.hpp>
#include <ecitygml/Length.hpp>
#include <ecitygml/LevelOfDetail.hpp>
#include <ecitygml/MultiSurface.hpp>
#include <ecitygml/MultiSurfaceProperty.hpp>
#include <ecitygml/Reference.hpp>
#include <ecitygml/RelationTypeValue.hpp>
#include <ecitygml/ReliefFeature.hpp>
#include <ecitygml/Road.hpp>
#include <ecitygml/RoofSurface.hpp>
#include <ecitygml/RoofTypeValue.hpp>
#include <ecitygml/Section.hpp>
#include <ecitygml/SectionProperty.hpp>
#include <ecitygml/SectionPropertyIterator.hpp>
#include <ecitygml/Storey.hpp>
#include <ecitygml/TinProperty.hpp>
#include <ecitygml/TinRelief.hpp>
#include <ecitygml/TrafficArea.hpp>
#include <ecitygml/TrafficSpace.hpp>
#include <ecitygml/TrafficSpaceProperty.hpp>
#include <ecitygml/TrafficSpacePropertyIterator.hpp>
#include <ecitygml/TriangleIterator.hpp>
#include <ecitygml/TriangulatedSurface.hpp>
#include <ecitygml/WallSurface.hpp>

#include <array>
#include <map>
#include <optional>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using conformance::close;
using conformance::features;
using conformance::first_name;
using ecitygml::FeatureType;

namespace {
const std::string DATASET = "ogc-citygml-3.0-encodings";
constexpr FeatureType WALL = FeatureType::WallSurface;
constexpr FeatureType ROOF = FeatureType::RoofSurface;
constexpr FeatureType GROUND = FeatureType::GroundSurface;

using Point = std::array<double, 3>;
using Date = std::array<int64_t, 3>;

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

std::vector<FeatureType> feature_types(const ecitygml::CityModel& city_model) {
    std::vector<FeatureType> result;
    for (const auto& feature : features(city_model)) {
        result.push_back(feature->feature_type());
    }
    return result;
}

/// `n` times the feature type, appended.
void append(std::vector<FeatureType>& types, FeatureType type, size_t n) { types.insert(types.end(), n, type); }

/// All features a class accepts, in document order; the model must outlive them.
template <typename T>
std::vector<const T*> all_of(const ecitygml::CityModel& city_model) {
    std::vector<const T*> result;
    auto iterator = city_model.iter_features();
    while (auto feature = iterator->next()) {
        if (const auto* x = T::try_from(*feature)) {
            result.push_back(x);
        }
    }
    return result;
}

template <typename Iterator>
std::vector<std::string> names(const std::unique_ptr<Iterator>& iterator) {
    std::vector<std::string> result;
    while (const auto* name = iterator->next()) {
        result.emplace_back(name->value());
    }
    return result;
}

void require_point_close(const ecitygml::DirectPosition& position, const Point& expected) {
    REQUIRE_THAT(position.x(), close(expected[0]));
    REQUIRE_THAT(position.y(), close(expected[1]));
    REQUIRE_THAT(position.z(), close(expected[2]));
}

void require_envelope(const ecitygml::Envelope* envelope, const Point& lower, const Point& upper) {
    REQUIRE(envelope != nullptr);
    require_point_close(envelope->lower_corner(), lower);
    require_point_close(envelope->upper_corner(), upper);
}

std::unique_ptr<ecitygml::CityModel> round_trip(const ecitygml::CityModel& city_model) {
    auto writer = ecitygml::GmlWriter::create(ecitygml::CitygmlFormat::Gml);
    REQUIRE(writer->finish(city_model).is_ok());
    return ok(ecitygml::GmlReader::create(writer->data(), ecitygml::CitygmlFormat::Gml)->finish());
}

struct Surface {
    FeatureType type;
    std::string id;
    std::optional<std::string> name;
    const ecitygml::MultiSurfaceProperty* multi_surface;
};

/// A space's boundaries; all inline wall, roof or ground surfaces. The model must outlive them.
std::vector<Surface> surfaces(const std::unique_ptr<ecitygml::AbstractSpaceBoundaryPropertyIterator>& boundaries) {
    std::vector<Surface> result;
    while (const auto* property = boundaries->next()) {
        REQUIRE(property->href() == nullptr);
        const auto* object = property->object();
        REQUIRE(object != nullptr);
        const std::string id(object->feature_id().as_str());
        const auto feature = ecitygml::AbstractFeatureKindRef::from_space_boundary(*object);
        const auto first = [](const auto& names_iterator) -> std::optional<std::string> {
            const auto all = names(names_iterator);
            return all.empty() ? std::nullopt : std::optional<std::string>(all.front());
        };
        if (const auto* wall = ecitygml::WallSurface::try_from(*feature)) {
            result.push_back({feature->feature_type(), id, first(wall->names()), wall->lod2_multi_surface()});
        } else if (const auto* roof = ecitygml::RoofSurface::try_from(*feature)) {
            result.push_back({feature->feature_type(), id, first(roof->names()), roof->lod2_multi_surface()});
        } else if (const auto* ground = ecitygml::GroundSurface::try_from(*feature)) {
            result.push_back({feature->feature_type(), id, first(ground->names()), ground->lod2_multi_surface()});
        } else {
            FAIL("unexpected boundary");
        }
    }
    return result;
}

double lod2_area(const ecitygml::MultiSurfaceProperty* property) {
    REQUIRE(property != nullptr);
    REQUIRE(property->object() != nullptr);
    return ok(property->object()->area_3d());
}

void require_height(const std::unique_ptr<ecitygml::HeightIterator>& heights, double length) {
    const auto* height = heights->next();
    REQUIRE(height != nullptr);
    REQUIRE(heights->next() == nullptr);
    REQUIRE(height->high_reference().value() == "highestRoofEdge");
    REQUIRE(height->low_reference().value() == "lowestGroundPoint");
    REQUIRE(height->status() == ecitygml::HeightStatusValue::Measured);
    REQUIRE_THAT(height->length().value(), close(length));
    REQUIRE(height->length().uom() == "#m");
}

/// The hrefs of a storey's LoD2 surface members (none for inline members).
std::vector<std::optional<std::string>> member_hrefs(const ecitygml::Storey& storey) {
    const auto* property = storey.lod2_multi_surface();
    REQUIRE(property != nullptr);
    REQUIRE(property->href() == nullptr);
    std::vector<std::optional<std::string>> result;
    auto members = property->object()->surface_member();
    while (const auto* member = members->next()) {
        REQUIRE((member->object() == nullptr) == (member->href() != nullptr));
        result.push_back(member->href() == nullptr ? std::nullopt : std::optional<std::string>(member->href()->to_string()));
    }
    return result;
}

using Relation = std::tuple<std::string, std::string, std::optional<std::string>>;

std::vector<Relation> relation_list(const std::string& id,
                                    const std::unique_ptr<ecitygml::CityObjectRelationPropertyIterator>& related_to) {
    std::vector<Relation> result;
    while (const auto* property = related_to->next()) {
        REQUIRE(property->href() == nullptr);
        const auto* relation = property->object();
        REQUIRE(relation != nullptr);
        REQUIRE(relation->generic_attributes()->next() == nullptr);
        const auto* href = relation->relation_to().href();
        result.emplace_back(id, std::string(relation->relation_type().value()),
                            href == nullptr ? std::nullopt : std::optional<std::string>(href->to_string()));
    }
    return result;
}

/// The relations of the roof surfaces and traffic areas, in document order.
std::vector<Relation> relations(const ecitygml::CityModel& city_model) {
    std::vector<Relation> result;
    for (const auto& feature : features(city_model)) {
        std::vector<Relation> found;
        if (const auto* roof = ecitygml::RoofSurface::try_from(*feature)) {
            found = relation_list(std::string(roof->feature_id().as_str()), roof->related_to());
        } else if (const auto* area = ecitygml::TrafficArea::try_from(*feature)) {
            found = relation_list(std::string(area->feature_id().as_str()), area->related_to());
        }
        result.insert(result.end(), found.begin(), found.end());
    }
    return result;
}

/// (year, month, day) of a date time at 00:00 UTC.
std::optional<Date> date(const ecitygml::DateTime* date_time) {
    if (date_time == nullptr) {
        return std::nullopt;
    }
    REQUIRE((date_time->hour() == 0 && date_time->minute() == 0 && date_time->offset_seconds() == 0));
    return Date{date_time->year(), date_time->month(), date_time->day()};
}

template <typename T>
std::vector<std::string> ids(const std::vector<const T*>& items) {
    std::vector<std::string> result;
    for (const auto* item : items) {
        result.emplace_back(item->feature_id().as_str());
    }
    return result;
}
}  // namespace

// Building_and_garage_LOD2-EPSG25832.gml

TEST_CASE("Garage city model", "[ogc-citygml-3.0-encodings][garage]") {
    auto city_model = conformance::read(DATASET, "Building_and_garage_LOD2-EPSG25832.gml");
    REQUIRE(city_model->city_objects_len() == 2);
    require_envelope(city_model->bounded_by()->envelope(), {458868.0, 5438343.0, 112.0}, {458892.0, 5438362.0, 117.0});
    std::vector<FeatureType> expected{FeatureType::CityModel, FeatureType::Building, GROUND};
    append(expected, WALL, 4);
    expected.insert(expected.end(), {ROOF, ROOF, FeatureType::BuildingPart});
    append(expected, WALL, 4);
    expected.insert(expected.end(), {GROUND, ROOF, FeatureType::ReliefFeature, FeatureType::TinRelief});
    REQUIRE(feature_types(*city_model) == expected);
    REQUIRE(count(city_model->iter_city_objects()) == 17);
}

TEST_CASE("Garage building", "[ogc-citygml-3.0-encodings][garage]") {
    auto city_model = conformance::read(DATASET, "Building_and_garage_LOD2-EPSG25832.gml");
    const auto buildings = all_of<ecitygml::Building>(*city_model);
    REQUIRE(buildings.size() == 1);
    const auto* b = buildings.front();
    REQUIRE(b->feature_id().as_str() == "GML_7b1a5a6f-ddad-4c3d-a507-3eb9ee0a8e68");
    REQUIRE(names(b->names()) == std::vector<std::string>{"Example Building LOD2"});
    REQUIRE(b->class_() == nullptr);
    REQUIRE(names(b->functions()) == std::vector<std::string>{"1000"});
    REQUIRE(b->usages()->next() == nullptr);
    REQUIRE(b->roof_type()->value() == "1030");
    REQUIRE(b->storeys_above_ground() == 1);
    REQUIRE_FALSE(b->storeys_below_ground().has_value());
    const auto* built = b->date_of_construction();
    REQUIRE(built != nullptr);
    REQUIRE((built->year() == 1985 && built->month() == 1 && built->day() == 1));
    require_height(b->heights(), 6.0);
    const std::vector<std::tuple<FeatureType, std::string, double>> expected{
        {GROUND, "Ground Slab", 50.0},          {WALL, "Wall South", 30.0},
        {WALL, "Wall North", 30.0},             {WALL, "Wall East", 20.0},
        {WALL, "Wall West", 20.0},              {ROOF, "Roof North", 32.01562118716424},
        {ROOF, "Roof South", 32.01562118716424},
    };
    const auto actual = surfaces(b->boundaries());
    REQUIRE(actual.size() == expected.size());
    for (size_t i = 0; i < actual.size(); ++i) {
        const auto& [type, name, area] = expected[i];
        REQUIRE(actual[i].type == type);
        REQUIRE(actual[i].name == name);
        REQUIRE_THAT(lod2_area(actual[i].multi_surface), close(area));
    }
}

TEST_CASE("Garage building part", "[ogc-citygml-3.0-encodings][garage]") {
    auto city_model = conformance::read(DATASET, "Building_and_garage_LOD2-EPSG25832.gml");
    auto parts = all_of<ecitygml::Building>(*city_model).front()->building_parts();
    const auto* property = parts->next();
    REQUIRE(property != nullptr);
    REQUIRE(parts->next() == nullptr);
    REQUIRE(property->href() == nullptr);
    const auto* part = property->object();
    REQUIRE(part != nullptr);
    REQUIRE(part->feature_id().as_str() == "GMLID_BUI379228_1244_301");
    REQUIRE(names(part->names()) == std::vector<std::string>{"Example BuildingPart LOD2"});
    REQUIRE(part->class_() == nullptr);
    REQUIRE(names(part->functions()) == std::vector<std::string>{"1630"});
    REQUIRE(part->usages()->next() == nullptr);
    REQUIRE(part->roof_type()->value() == "1010");
    const auto* built = part->date_of_construction();
    REQUIRE(built != nullptr);
    REQUIRE((built->year() == 1985 && built->month() == 1 && built->day() == 1));
    require_height(part->heights(), 2.5);
    // The west wall's area is left out: its member is a gml:OrientableSurface, not read yet.
    const std::vector<std::tuple<FeatureType, std::string, std::optional<double>>> expected{
        {WALL, "Garage Wall East", 9.600000023841858}, {WALL, "Garage Wall South", 6.25},
        {WALL, "Garage Wall West", std::nullopt},      {WALL, "Garage Wall North", 5.75},
        {GROUND, "Garage Ground Slab", 10.0},          {ROOF, "Garage Roof", 10.012492197250394},
    };
    const auto actual = surfaces(part->boundaries());
    REQUIRE(actual.size() == expected.size());
    for (size_t i = 0; i < actual.size(); ++i) {
        const auto& [type, name, area] = expected[i];
        REQUIRE(actual[i].type == type);
        REQUIRE(actual[i].name == name);
        if (area.has_value()) {
            REQUIRE_THAT(lod2_area(actual[i].multi_surface), close(*area));
        }
    }
}

TEST_CASE("Garage relief", "[ogc-citygml-3.0-encodings][garage]") {
    auto city_model = conformance::read(DATASET, "Building_and_garage_LOD2-EPSG25832.gml");
    const auto reliefs = all_of<ecitygml::ReliefFeature>(*city_model);
    REQUIRE(reliefs.size() == 1);
    const auto* relief = reliefs.front();
    REQUIRE(relief->feature_id().as_str() == "GML_6bb30328-7599-4500-90ef-766fde6aa67b");
    REQUIRE(names(relief->names()) == std::vector<std::string>{"Example TIN LOD2"});
    REQUIRE(relief->lod() == ecitygml::LevelOfDetail::Two);
    auto components = relief->relief_components();
    const auto* component = components->next();
    REQUIRE(component != nullptr);
    REQUIRE(components->next() == nullptr);
    REQUIRE(component->href() == nullptr);
    REQUIRE(component->object()->feature_type() == FeatureType::TinRelief);

    const auto tin_reliefs = all_of<ecitygml::TinRelief>(*city_model);
    REQUIRE(tin_reliefs.size() == 1);
    const auto* tin_relief = tin_reliefs.front();
    REQUIRE(tin_relief->feature_id().as_str() == "GML_4eb161b0-aa7e-4087-937c-5c4c427c7fc9");
    REQUIRE(names(tin_relief->names()) == std::vector<std::string>{"Ground"});
    REQUIRE(tin_relief->lod() == ecitygml::LevelOfDetail::Two);
    const auto* tin = tin_relief->tin();
    REQUIRE(tin != nullptr);
    REQUIRE(tin->href() == nullptr);
    const auto* surface = tin->object();
    REQUIRE(surface != nullptr);
    REQUIRE(count(surface->triangles()) == 12);
    REQUIRE_THAT(ok(surface->area_3d()), close(399.8446647372588));
}

TEST_CASE("Garage round trip", "[ogc-citygml-3.0-encodings][garage]") {
    auto city_model = conformance::read(DATASET, "Building_and_garage_LOD2-EPSG25832.gml");
    auto written = round_trip(*city_model);
    REQUIRE(feature_types(*written) == feature_types(*city_model));
    std::vector<std::string> found = ids(all_of<ecitygml::Building>(*written));
    for (const auto& id : ids(all_of<ecitygml::BuildingPart>(*written))) found.push_back(id);
    for (const auto& id : ids(all_of<ecitygml::ReliefFeature>(*written))) found.push_back(id);
    for (const auto& id : ids(all_of<ecitygml::TinRelief>(*written))) found.push_back(id);
    REQUIRE(found == std::vector<std::string>{
                         "GML_7b1a5a6f-ddad-4c3d-a507-3eb9ee0a8e68",
                         "GMLID_BUI379228_1244_301",
                         "GML_6bb30328-7599-4500-90ef-766fde6aa67b",
                         "GML_4eb161b0-aa7e-4087-937c-5c4c427c7fc9",
                     });
}

// BuildingUnits_Storeys_xlink.gml

TEST_CASE("Units city model", "[ogc-citygml-3.0-encodings][units]") {
    auto city_model = conformance::read(DATASET, "BuildingUnits_Storeys_xlink.gml");
    REQUIRE(city_model->city_objects_len() == 1);
    require_envelope(city_model->bounded_by()->envelope(), {457841.0, 5439082.0, 111.0}, {457854.0, 5439093.0, 121.0});
    std::vector<FeatureType> expected{FeatureType::CityModel, FeatureType::Building};
    append(expected, WALL, 3);
    expected.insert(expected.end(), {ROOF, WALL, ROOF, GROUND});
    for (size_t walls : {8, 8, 4}) {
        expected.push_back(FeatureType::BuildingRoom);
        append(expected, FeatureType::InteriorWallSurface, walls);
        expected.insert(expected.end(), {FeatureType::FloorSurface, FeatureType::CeilingSurface});
    }
    expected.insert(expected.end(),
                    {FeatureType::BuildingUnit, FeatureType::BuildingUnit, FeatureType::Storey, FeatureType::Storey});
    REQUIRE(feature_types(*city_model) == expected);
    REQUIRE(count(city_model->iter_city_objects()) == 41);
}

TEST_CASE("Units building", "[ogc-citygml-3.0-encodings][units]") {
    auto city_model = conformance::read(DATASET, "BuildingUnits_Storeys_xlink.gml");
    const auto buildings = all_of<ecitygml::Building>(*city_model);
    REQUIRE(buildings.size() == 1);
    const auto* b = buildings.front();
    REQUIRE(b->feature_id().as_str() == "building_unit_example_1");
    REQUIRE(b->names()->next() == nullptr);
    REQUIRE(b->functions()->next() == nullptr);
    REQUIRE(b->usages()->next() == nullptr);
    REQUIRE(b->class_() == nullptr);
    REQUIRE(b->roof_type() == nullptr);
    const std::vector<std::tuple<FeatureType, std::string, double>> expected{
        {WALL, "Outer Wall 1 (West)", 89.375},        {WALL, "Outer Wall 2 (South)", 81.25},
        {WALL, "Outer Wall 3 (East)", 89.375},        {ROOF, "Roof 1 (North)", 86.53792521201326},
        {WALL, "Outer Wall 4 (North)", 81.25},        {ROOF, "Roof 2 (South)", 86.53792521201326},
        {GROUND, "Base Surface", 143.0},
    };
    const auto actual = surfaces(b->boundaries());
    REQUIRE(actual.size() == expected.size());
    for (size_t i = 0; i < actual.size(); ++i) {
        const auto& [type, name, area] = expected[i];
        REQUIRE(actual[i].type == type);
        REQUIRE(actual[i].name == name);
        REQUIRE_THAT(lod2_area(actual[i].multi_surface), close(area));
    }
}

TEST_CASE("Units subdivisions", "[ogc-citygml-3.0-encodings][units]") {
    auto city_model = conformance::read(DATASET, "BuildingUnits_Storeys_xlink.gml");
    auto subdivisions = all_of<ecitygml::Building>(*city_model).front()->building_subdivisions();
    std::vector<FeatureType> types;
    while (const auto* property = subdivisions->next()) {
        REQUIRE(property->href() == nullptr);
        REQUIRE(property->object() != nullptr);
        types.push_back(property->object()->feature_type());
    }
    REQUIRE(types == std::vector<FeatureType>{FeatureType::BuildingUnit, FeatureType::BuildingUnit,
                                              FeatureType::Storey, FeatureType::Storey});
    const auto units = all_of<ecitygml::BuildingUnit>(*city_model);
    REQUIRE(ids(units) == std::vector<std::string>{"BuildingUnit_apartment1", "BuildingUnit_apartment2"});
    for (const auto* unit : units) {
        REQUIRE(names(unit->functions()) == std::vector<std::string>{"apartment"});
        REQUIRE(unit->class_() == nullptr);
        REQUIRE(unit->usages()->next() == nullptr);
        REQUIRE(unit->boundaries()->next() == nullptr);
        REQUIRE(unit->lod2_multi_surface() == nullptr);
    }
    const auto storeys = all_of<ecitygml::Storey>(*city_model);
    REQUIRE(ids(storeys) == std::vector<std::string>{"storey1", "storey2"});
    for (const auto* storey : storeys) {
        REQUIRE(storey->names()->next() == nullptr);
        REQUIRE(storey->class_() == nullptr);
        REQUIRE(storey->functions()->next() == nullptr);
        REQUIRE(storey->usages()->next() == nullptr);
        REQUIRE(storey->boundaries()->next() == nullptr);
    }
}

TEST_CASE("Units storey geometry", "[ogc-citygml-3.0-encodings][units]") {
    auto city_model = conformance::read(DATASET, "BuildingUnits_Storeys_xlink.gml");
    const std::vector<std::tuple<std::vector<std::string>, Point, Point>> expected{
        {{"#Wall_1_PolyID82397_997_453711_16336011", "#Wall_1_PolyID82397_997_453711_16336012",
          "#Wall_1_PolyID82397_997_453711_163360136"},
         {457841.1, 5439082.1, 111.1},
         {457853.9, 5439092.9, 113.9}},
        {{"#Wall_1_PolyID82397_997_453711_163360112", "#Wall_1_PolyID82397_997_453711_163360122",
          "#Wall_1_PolyID82397_997_453711_1633601362"},
         {457841.1, 5439082.1, 114.1},
         {457853.9, 5439092.9, 116.9}},
    };
    const auto storeys = all_of<ecitygml::Storey>(*city_model);
    REQUIRE(storeys.size() == expected.size());
    for (size_t i = 0; i < storeys.size(); ++i) {
        const auto& [hrefs, lower, upper] = expected[i];
        const std::vector<std::optional<std::string>> want{std::nullopt, hrefs[0], hrefs[1], hrefs[2],
                                                          std::nullopt, std::nullopt};
        REQUIRE(member_hrefs(*storeys[i]) == want);
        REQUIRE(storeys[i]->lod2_multi_surface()->object()->area_3d().is_err());
        require_envelope(storeys[i]->bounded_by()->envelope(), lower, upper);
    }
}

TEST_CASE("Units round trip", "[ogc-citygml-3.0-encodings][units]") {
    auto city_model = conformance::read(DATASET, "BuildingUnits_Storeys_xlink.gml");
    auto written = round_trip(*city_model);
    REQUIRE(feature_types(*written) == feature_types(*city_model));
    REQUIRE(ids(all_of<ecitygml::Building>(*written)) == std::vector<std::string>{"building_unit_example_1"});
    const auto hrefs = [](const ecitygml::CityModel& model) {
        std::vector<std::vector<std::optional<std::string>>> result;
        for (const auto* storey : all_of<ecitygml::Storey>(model)) {
            result.push_back(member_hrefs(*storey));
        }
        return result;
    };
    REQUIRE(hrefs(*written) == hrefs(*city_model));
}

// Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml

TEST_CASE("Road bridge city model", "[ogc-citygml-3.0-encodings][road-bridge]") {
    auto city_model = conformance::read(DATASET, "Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml");
    REQUIRE(city_model->city_objects_len() == 2);
    REQUIRE(city_model->bounded_by() == nullptr);
    std::vector<FeatureType> expected{FeatureType::CityModel, FeatureType::Bridge, GROUND, ROOF, ROOF};
    append(expected, WALL, 4);
    expected.push_back(FeatureType::Road);
    for (int i = 0; i < 3; ++i) {
        expected.insert(expected.end(), {FeatureType::Section, FeatureType::TrafficSpace, FeatureType::TrafficArea,
                                         FeatureType::TrafficSpace, FeatureType::TrafficArea});
    }
    REQUIRE(feature_types(*city_model) == expected);
    REQUIRE(count(city_model->iter_city_objects()) == 24);
}

TEST_CASE("Road bridge bridge", "[ogc-citygml-3.0-encodings][road-bridge]") {
    auto city_model = conformance::read(DATASET, "Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml");
    const auto bridges = all_of<ecitygml::Bridge>(*city_model);
    REQUIRE(bridges.size() == 1);
    const auto* bridge = bridges.front();
    REQUIRE(bridge->feature_id().as_str() == "id_bridge1");
    REQUIRE(bridge->names()->next() == nullptr);
    REQUIRE(bridge->related_to()->next() == nullptr);
    const std::vector<std::pair<std::string, double>> expected{
        {"id_groundsurface1", 77500.15996032}, {"id_roofsurface1", 38750.07998016},
        {"id_roofsurface2", 38750.07998016},   {"id_wallsurface4", 10075.02000744},
        {"id_wallsurface1", 20150.04001488},   {"id_wallsurface2", 10075.02000744},
        {"id_wallsurface3", 20150.04001488},
    };
    const auto actual = surfaces(bridge->boundaries());
    REQUIRE(actual.size() == expected.size());
    for (size_t i = 0; i < actual.size(); ++i) {
        REQUIRE(actual[i].id == expected[i].first);
        REQUIRE_THAT(lod2_area(actual[i].multi_surface), close(expected[i].second));
    }
}

TEST_CASE("Road bridge road", "[ogc-citygml-3.0-encodings][road-bridge]") {
    auto city_model = conformance::read(DATASET, "Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml");
    const auto roads = all_of<ecitygml::Road>(*city_model);
    REQUIRE(roads.size() == 1);
    const auto* road = roads.front();
    REQUIRE(road->feature_id().as_str() == "id_road1");
    REQUIRE(road->related_to()->next() == nullptr);
    REQUIRE(road->traffic_spaces()->next() == nullptr);
    REQUIRE(road->auxiliary_traffic_spaces()->next() == nullptr);
    std::vector<const ecitygml::Section*> sections;
    auto section_properties = road->sections();
    while (const auto* property = section_properties->next()) {
        REQUIRE(property->href() == nullptr);
        REQUIRE(property->object() != nullptr);
        sections.push_back(property->object());
    }
    REQUIRE(ids(sections) == std::vector<std::string>{"id_section1", "id_section2", "id_section3"});
    std::vector<const ecitygml::TrafficSpace*> spaces;
    for (const auto* section : sections) {
        auto properties = section->traffic_spaces();
        while (const auto* property = properties->next()) {
            REQUIRE(property->href() == nullptr);
            REQUIRE(property->object() != nullptr);
            spaces.push_back(property->object());
        }
    }
    const std::array<int, 6> numbers{1, 2, 5, 6, 3, 4};
    REQUIRE(spaces.size() == numbers.size());
    for (size_t i = 0; i < spaces.size(); ++i) {
        REQUIRE(spaces[i]->feature_id().as_str() == "id_trafficspace" + std::to_string(numbers[i]));
        auto boundaries = spaces[i]->boundaries();
        const auto* boundary = boundaries->next();
        REQUIRE(boundary != nullptr);
        REQUIRE(boundaries->next() == nullptr);
        REQUIRE(boundary->href() == nullptr);
        const auto* area = boundary->object();
        REQUIRE(area != nullptr);
        REQUIRE(area->feature_type() == FeatureType::TrafficArea);
        REQUIRE(area->feature_id().as_str() == "id_trafficarea" + std::to_string(numbers[i]));
    }
}

TEST_CASE("Road bridge relations", "[ogc-citygml-3.0-encodings][road-bridge]") {
    auto city_model = conformance::read(DATASET, "Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml");
    REQUIRE(relations(*city_model) == std::vector<Relation>{
                                          {"id_roofsurface1", "equal", "id_trafficarea5"},
                                          {"id_roofsurface2", "equal", "id_trafficarea6"},
                                          {"id_trafficarea5", "equal", "id_roofSurface1"},
                                          {"id_trafficarea6", "equal", "id_roofSurface2"},
                                      });
    for (const auto* wall : all_of<ecitygml::WallSurface>(*city_model)) {
        REQUIRE(wall->related_to()->next() == nullptr);
    }
    for (const auto* ground : all_of<ecitygml::GroundSurface>(*city_model)) {
        REQUIRE(ground->related_to()->next() == nullptr);
    }
}

TEST_CASE("Road bridge round trip", "[ogc-citygml-3.0-encodings][road-bridge]") {
    auto city_model = conformance::read(DATASET, "Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml");
    auto written = round_trip(*city_model);
    REQUIRE(feature_types(*written) == feature_types(*city_model));
    REQUIRE(ids(all_of<ecitygml::Bridge>(*written)) == std::vector<std::string>{"id_bridge1"});
    REQUIRE(ids(all_of<ecitygml::Road>(*written)) == std::vector<std::string>{"id_road1"});
    REQUIRE(relations(*written) == relations(*city_model));
}

// historicalSuccession_CityGML_3.0_LOD2_Versioning.gml

TEST_CASE("Versioning city model", "[ogc-citygml-3.0-encodings][versioning]") {
    auto city_model = conformance::read(DATASET, "historicalSuccession_CityGML_3.0_LOD2_Versioning.gml");
    REQUIRE(city_model->city_objects_len() == 4);
    REQUIRE(city_model->bounded_by() == nullptr);
    const auto types = feature_types(*city_model);
    REQUIRE(types.size() == 60);
    REQUIRE(types.front() == FeatureType::CityModel);
    std::map<FeatureType, int> counts;
    for (const auto type : types) {
        ++counts[type];
    }
    REQUIRE(counts == std::map<FeatureType, int>{
                          {FeatureType::CityModel, 1},
                          {FeatureType::Building, 4},
                          {FeatureType::BuildingPart, 5},
                          {ROOF, 14},
                          {WALL, 31},
                          {GROUND, 5},
                      });
    REQUIRE(count(city_model->iter_city_objects()) == 59);
}

TEST_CASE("Versioning buildings", "[ogc-citygml-3.0-encodings][versioning]") {
    auto city_model = conformance::read(DATASET, "historicalSuccession_CityGML_3.0_LOD2_Versioning.gml");
    const std::vector<std::tuple<std::string, std::string, Date, std::optional<Date>, std::vector<std::string>>>
        expected{
            {"BU_69381AL47_2000-01-01", "Building A", {2000, 1, 1}, Date{2015, 1, 1}, {"BU_69381AL47_1"}},
            {"BU_69381AL49_2000-01-01", "Building B", {2000, 1, 1}, Date{2015, 1, 1}, {"BU_69381AL49_1_2000-01-01"}},
            {"BU_69381AL49_2015-01-01",
             "Building B",
             {2015, 1, 1},
             std::nullopt,
             {"BU_69381AL49_1_2015-01-01", "BU_69381AL49_2_2015-01-01"}},
            {"BU_69381AL50_2015-01-01", "Building C", {2015, 1, 1}, std::nullopt, {"BU_69381AL50_1"}},
        };
    const auto buildings = all_of<ecitygml::Building>(*city_model);
    REQUIRE(buildings.size() == expected.size());
    for (size_t i = 0; i < buildings.size(); ++i) {
        const auto& [id, name, created, terminated, parts] = expected[i];
        const auto* b = buildings[i];
        REQUIRE(b->feature_id().as_str() == id);
        REQUIRE(first_name(*b) == name);
        REQUIRE(date(b->creation_date()) == created);
        REQUIRE(date(b->termination_date()) == terminated);
        std::vector<std::string> part_ids;
        auto properties = b->building_parts();
        while (const auto* property = properties->next()) {
            REQUIRE(property->href() == nullptr);
            part_ids.emplace_back(property->object()->feature_id().as_str());
        }
        REQUIRE(part_ids == parts);
        REQUIRE(b->heights()->next() == nullptr);
        REQUIRE(b->boundaries()->next() == nullptr);
    }
}

TEST_CASE("Versioning building parts", "[ogc-citygml-3.0-encodings][versioning]") {
    auto city_model = conformance::read(DATASET, "historicalSuccession_CityGML_3.0_LOD2_Versioning.gml");
    const std::vector<std::tuple<std::string, double, int>> expected{
        {"BU_69381AL47_1", 13.015, 8},           {"BU_69381AL49_1_2000-01-01", 10.63, 9},
        {"BU_69381AL49_1_2015-01-01", 10.63, 9}, {"BU_69381AL49_2_2015-01-01", 8.743, 7},
        {"BU_69381AL50_1", 18.215, 17},
    };
    const auto parts = all_of<ecitygml::BuildingPart>(*city_model);
    REQUIRE(parts.size() == expected.size());
    for (size_t i = 0; i < parts.size(); ++i) {
        const auto& [id, height, boundaries] = expected[i];
        REQUIRE(parts[i]->feature_id().as_str() == id);
        require_height(parts[i]->heights(), height);
        REQUIRE(count(parts[i]->boundaries()) == boundaries);
        REQUIRE(parts[i]->creation_date() == nullptr);
        REQUIRE(parts[i]->names()->next() == nullptr);
    }
}

TEST_CASE("Versioning round trip", "[ogc-citygml-3.0-encodings][versioning]") {
    auto city_model = conformance::read(DATASET, "historicalSuccession_CityGML_3.0_LOD2_Versioning.gml");
    auto written = round_trip(*city_model);
    REQUIRE(feature_types(*written) == feature_types(*city_model));
    const auto all_ids = [](const ecitygml::CityModel& model) {
        std::vector<std::string> result = ids(all_of<ecitygml::Building>(model));
        for (const auto& id : ids(all_of<ecitygml::BuildingPart>(model))) result.push_back(id);
        return result;
    };
    const auto dates = [](const ecitygml::CityModel& model) {
        std::vector<std::pair<std::optional<Date>, std::optional<Date>>> result;
        for (const auto* b : all_of<ecitygml::Building>(model)) {
            result.emplace_back(date(b->creation_date()), date(b->termination_date()));
        }
        return result;
    };
    REQUIRE(all_ids(*written) == all_ids(*city_model));
    REQUIRE(dates(*written) == dates(*city_model));
}
