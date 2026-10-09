#include "test_helpers.hpp"

#include <ecitygml/AbstractReliefComponentKind.hpp>
#include <ecitygml/AbstractReliefComponentProperty.hpp>
#include <ecitygml/AbstractReliefComponentPropertyIterator.hpp>
#include <ecitygml/CityFurniture.hpp>
#include <ecitygml/CityFurnitureFunctionValue.hpp>
#include <ecitygml/CityFurnitureFunctionValueIterator.hpp>
#include <ecitygml/FeatureType.hpp>
#include <ecitygml/Id.hpp>
#include <ecitygml/LevelOfDetail.hpp>
#include <ecitygml/Measure.hpp>
#include <ecitygml/PlantCover.hpp>
#include <ecitygml/ReliefFeature.hpp>
#include <ecitygml/SolitaryVegetationObject.hpp>
#include <ecitygml/SolitaryVegetationObjectClassValue.hpp>
#include <ecitygml/SpeciesValue.hpp>
#include <ecitygml/TinProperty.hpp>
#include <ecitygml/TinRelief.hpp>
#include <ecitygml/Triangle.hpp>
#include <ecitygml/TriangleIterator.hpp>
#include <ecitygml/TriangulatedSurface.hpp>

TEST_CASE("SolitaryVegetationObject and PlantCover", "[vegetation]") {
    auto city_model = read_member(R"(<cityObjectMember>
    <veg:SolitaryVegetationObject gml:id="tree_1">
      <veg:class>1000</veg:class>
      <veg:species>Quercus robur</veg:species>
      <veg:height uom="m">12.5</veg:height>
    </veg:SolitaryVegetationObject>
  </cityObjectMember>
  <cityObjectMember>
    <veg:PlantCover gml:id="cover_1"><veg:averageHeight uom="m">2.5</veg:averageHeight></veg:PlantCover>
  </cityObjectMember>
</CityModel>
)");
    const auto* tree = first<ecitygml::SolitaryVegetationObject>(*city_model);
    REQUIRE(tree != nullptr);
    REQUIRE(tree->class_()->value() == "1000");
    REQUIRE(tree->species()->value() == "Quercus robur");
    REQUIRE(tree->height()->value() == 12.5);
    REQUIRE(tree->lod1_implicit_representation() == nullptr);
    REQUIRE(first<ecitygml::PlantCover>(*city_model)->average_height()->value() == 2.5);
}

TEST_CASE("CityFurniture", "[city_furniture]") {
    auto city_model = read_member(R"(<cityObjectMember>
    <frn:CityFurniture gml:id="sign_1"><frn:function>1080</frn:function></frn:CityFurniture>
  </cityObjectMember>
</CityModel>
)");
    const auto* furniture = first<ecitygml::CityFurniture>(*city_model);
    REQUIRE(furniture->feature_id().as_str() == "sign_1");
    REQUIRE(furniture->functions()->next()->value() == "1080");
    REQUIRE(furniture->class_() == nullptr);
}

TEST_CASE("ReliefFeature and TinRelief", "[relief]") {
    auto city_model = read_member(R"(<cityObjectMember>
    <dem:ReliefFeature gml:id="relief_1">
      <dem:lod>2</dem:lod>
      <dem:reliefComponent>
        <dem:TINRelief gml:id="tin_1">
          <dem:lod>1</dem:lod>
          <dem:tin><gml:TriangulatedSurface><gml:patches><gml:Triangle><gml:exterior><gml:LinearRing>
            <gml:posList>0 0 0 1 0 0 0 1 0 0 0 0</gml:posList>
          </gml:LinearRing></gml:exterior></gml:Triangle></gml:patches></gml:TriangulatedSurface></dem:tin>
        </dem:TINRelief>
      </dem:reliefComponent>
    </dem:ReliefFeature>
  </cityObjectMember>
</CityModel>
)");
    const auto* relief = first<ecitygml::ReliefFeature>(*city_model);
    REQUIRE(relief->lod() == ecitygml::LevelOfDetail::Two);
    auto components = relief->relief_components();
    const auto* component = components->next()->object();
    REQUIRE(component->feature_type() == ecitygml::FeatureType::TinRelief);
    REQUIRE(component->lod() == ecitygml::LevelOfDetail::One);
    REQUIRE(components->next() == nullptr);

    const auto* tin = first<ecitygml::TinRelief>(*city_model);
    REQUIRE(tin->feature_id().as_str() == "tin_1");
    auto triangles = tin->tin()->object()->triangles();
    REQUIRE(triangles->next() != nullptr);
    REQUIRE(triangles->next() == nullptr);
}
