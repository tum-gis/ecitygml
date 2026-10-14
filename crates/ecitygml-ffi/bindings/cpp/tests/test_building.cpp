#include "test_helpers.hpp"

#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <ecitygml/AbstractFeatureKindRef.hpp>
#include <ecitygml/AbstractFeatureKindRefIterator.hpp>
#include <ecitygml/Building.hpp>
#include <ecitygml/BuildingClassValue.hpp>
#include <ecitygml/BuildingFunctionValue.hpp>
#include <ecitygml/BuildingFunctionValueIterator.hpp>
#include <ecitygml/BuildingPart.hpp>
#include <ecitygml/BuildingPartProperty.hpp>
#include <ecitygml/BuildingPartPropertyIterator.hpp>
#include <ecitygml/AbstractBuildingSubdivisionKind.hpp>
#include <ecitygml/AbstractBuildingSubdivisionProperty.hpp>
#include <ecitygml/AbstractBuildingSubdivisionPropertyIterator.hpp>
#include <ecitygml/BuildingSubdivisionClassValue.hpp>
#include <ecitygml/BuildingSubdivisionFunctionValue.hpp>
#include <ecitygml/BuildingSubdivisionFunctionValueIterator.hpp>
#include <ecitygml/BuildingSubdivisionUsageValue.hpp>
#include <ecitygml/BuildingSubdivisionUsageValueIterator.hpp>
#include <ecitygml/BuildingUnit.hpp>
#include <ecitygml/FeatureType.hpp>
#include <ecitygml/Storey.hpp>
#include <ecitygml/Date.hpp>
#include <ecitygml/ExternalReference.hpp>
#include <ecitygml/ExternalReferenceIterator.hpp>
#include <ecitygml/GenericAttributeKind.hpp>
#include <ecitygml/GenericAttributeKindIterator.hpp>
#include <ecitygml/Measure.hpp>
#include <ecitygml/MeasureAttribute.hpp>
#include <ecitygml/StringAttribute.hpp>
#include <ecitygml/ElevationReferenceValue.hpp>
#include <ecitygml/Height.hpp>
#include <ecitygml/HeightIterator.hpp>
#include <ecitygml/HeightStatusValue.hpp>
#include <ecitygml/Id.hpp>
#include <ecitygml/Length.hpp>
#include <ecitygml/RoofTypeValue.hpp>
#include <ecitygml/Solid.hpp>
#include <ecitygml/SolidProperty.hpp>

#include <utility>

using Catch::Matchers::WithinRel;

namespace {
/// The first building of a model; the model must outlive the returned pointer.
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

TEST_CASE("Building own and inherited getters", "[building]") {
    auto city_model = read(fixture("FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml"));
    const auto* building = first_building(*city_model);
    REQUIRE(building != nullptr);

    REQUIRE(building->class_()->value() == "1000");
    REQUIRE(building->functions()->next()->value() == "1000");
    REQUIRE(building->roof_type()->value() == "1030");
    REQUIRE(building->storeys_above_ground() == 2);
    REQUIRE(building->storeys_below_ground() == 0);

    const auto* date = building->date_of_construction();
    REQUIRE(date != nullptr);
    REQUIRE(date->year() == 2020);
    REQUIRE(building->date_of_demolition() == nullptr);
    auto heights = building->heights();
    const auto* height = heights->next();
    REQUIRE(height != nullptr);
    REQUIRE(heights->next() == nullptr);
    REQUIRE(height->high_reference().value() == "topOfConstruction");
    REQUIRE(height->status() == ecitygml::HeightStatusValue::Measured);
    REQUIRE(height->length().value() == 6.52);
    REQUIRE(height->length().uom() == "m");

    auto volume = building->lod1_solid()->object()->volume_3d();
    REQUIRE(volume.is_ok());
    REQUIRE_THAT(std::move(volume).ok().value(), WithinRel(782.1228, 1e-9));
    REQUIRE(building->building_parts()->next() == nullptr);
}

TEST_CASE("Building part", "[building]") {
    auto city_model = read_modified(
        "FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml", "</bldg:Building>",
        "<bldg:buildingPart><bldg:BuildingPart gml:id=\"BP_1\"><bldg:storeysAboveGround>1</bldg:storeysAboveGround>"
        "</bldg:BuildingPart></bldg:buildingPart></bldg:Building>");
    const auto* building = first_building(*city_model);
    REQUIRE(building != nullptr);
    auto parts = building->building_parts();
    const auto* part = parts->next();
    REQUIRE(part != nullptr);
    REQUIRE(parts->next() == nullptr);
    REQUIRE(part->object()->feature_id().as_str() == "BP_1");
    REQUIRE(part->object()->storeys_above_ground() == 1);
}

TEST_CASE("Generic attributes and external references", "[building]") {
    auto fzk = read(fixture("FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml"));
    const auto* building = first_building(*fzk);
    REQUIRE(building != nullptr);
    auto attributes = building->generic_attributes();
    const auto* area = attributes->next();
    REQUIRE(area->name() == "GrossPlannedArea");
    const auto* measure = ecitygml::MeasureAttribute::try_from(*area);
    REQUIRE(measure != nullptr);
    REQUIRE(measure->value().value() == 120.0);
    REQUIRE(measure->value().uom() == "m2");
    const auto* method = attributes->next()->as_string();
    REQUIRE(method != nullptr);
    REQUIRE(method->value() == "New Building");
    REQUIRE(building->external_references()->next() == nullptr);

    auto tum = read(fixture("TUM-Main-Entrance.gml"));
    auto references = first_building(*tum)->external_references();
    REQUIRE(references->next()->target_resource() == "DEBYvAAAAABTMIyA");
    REQUIRE(references->next() == nullptr);
}

TEST_CASE("Building subdivisions: storeys and building units", "[building]") {
    // No fixture has subdivisions; they are injected after the storey counts (AbstractBuildingType).
    auto city_model = read_modified("FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml",
        "<bldg:storeysBelowGround>0</bldg:storeysBelowGround>",
        "<bldg:storeysBelowGround>0</bldg:storeysBelowGround>"
        "<bldg:buildingSubdivision><bldg:Storey gml:id=\"storey_ground\">"
        "<bldg:class codeSpace=\"https://example.org/storey_class\">ground</bldg:class>"
        "<bldg:function>living</bldg:function></bldg:Storey></bldg:buildingSubdivision>"
        "<bldg:buildingSubdivision><bldg:BuildingUnit gml:id=\"unit_1\">"
        "<bldg:usage>residential</bldg:usage></bldg:BuildingUnit></bldg:buildingSubdivision>");
    const auto* building = first_building(*city_model);
    REQUIRE(building != nullptr);
    auto subdivisions = building->building_subdivisions();
    const auto* storey = subdivisions->next()->object();
    const auto* unit = subdivisions->next()->object();
    REQUIRE(subdivisions->next() == nullptr);

    REQUIRE(storey->feature_type() == ecitygml::FeatureType::Storey);
    REQUIRE(unit->feature_type() == ecitygml::FeatureType::BuildingUnit);
    REQUIRE(storey->feature_id().as_str() == "storey_ground");
    REQUIRE(storey->class_()->value() == "ground");
    REQUIRE(storey->functions()->next()->value() == "living");
    REQUIRE(unit->class_() == nullptr);
    REQUIRE(unit->usages()->next()->value() == "residential");

    const ecitygml::Storey* typed_storey = nullptr;
    const ecitygml::BuildingUnit* typed_unit = nullptr;
    auto features = city_model->iter_features();
    while (auto feature = features->next()) {
        typed_storey = typed_storey ? typed_storey : ecitygml::Storey::try_from(*feature);
        typed_unit = typed_unit ? typed_unit : ecitygml::BuildingUnit::try_from(*feature);
    }
    REQUIRE(typed_storey->feature_id().as_str() == "storey_ground");
    REQUIRE(typed_unit->usages()->next()->value() == "residential");
}
