"""The AbstractCityObject getters.

Ported from the former PyO3 bindings' `test_city_object.py`. Not ported (not in the Diplomat
bindings): the `GenericAttribute` alias, `repr`. Generic attributes are `GenericAttributeKind`s:
their values come from `as_string()`, `as_int()`, `as_double()` (as in Rust),
`MeasureAttribute.try_from()` or `GenericAttributeSet.try_from()`, instead of `isinstance`.
"""

from typing import Any

import pytest

from conftest import FZK_LOD2, features_of, objects, read_injected
from ecitygml import (
    Building,
    CityObjectRelation,
    ExternalReference,
    GenericAttributeSet,
    MeasureAttribute,
    RelativeToTerrain,
    RelativeToWater,
    TrafficSpace,
    WallSurface,
)

# Properties absent from the fixtures, injected into a copy of the FZK LoD2 building. They
# include relatedTo and generic attributes, which the former tests also read.
EXTRA_CITY_OBJECT_PROPERTIES = """<relativeToTerrain>entirelyAboveTerrain</relativeToTerrain>
      <relativeToWater>entirelyAboveWaterSurface</relativeToWater>
      <relatedTo>
        <CityObjectRelation>
          <relationType>shared</relationType>
          <relatedTo xlink:href="#UUID_other"/>
          <genericAttribute>
            <gen:IntAttribute><gen:name>weight</gen:name><gen:value>3</gen:value></gen:IntAttribute>
          </genericAttribute>
        </CityObjectRelation>
      </relatedTo>
      <genericAttribute>
        <gen:GenericAttributeSet>
          <gen:name>energy</gen:name>
          <gen:genericAttribute>
            <gen:DoubleAttribute><gen:name>demand</gen:name><gen:value>12.5</gen:value></gen:DoubleAttribute>
          </gen:genericAttribute>
          <gen:genericAttribute>
            <gen:StringAttribute><gen:name>label</gen:name><gen:value>A+</gen:value></gen:StringAttribute>
          </gen:genericAttribute>
        </gen:GenericAttributeSet>
      </genericAttribute>"""


@pytest.fixture(scope="module")
def extended_model(tmp_path_factory: pytest.TempPathFactory) -> Any:
    anchor = "<relativeToTerrain>entirelyAboveTerrain</relativeToTerrain>"
    tmp_path = tmp_path_factory.mktemp("city_object")
    return read_injected(tmp_path, FZK_LOD2, anchor, EXTRA_CITY_OBJECT_PROPERTIES)


@pytest.fixture(scope="module")
def extended_building(extended_model: Any) -> Building:
    return features_of(extended_model, Building)[0]


class TestRelativeToTerrainAndWater:
    def test_relative_to_terrain(self, fzk_lod2_building: Building) -> None:
        assert fzk_lod2_building.relative_to_terrain() == RelativeToTerrain.EntirelyAboveTerrain

    def test_relative_to_water_absent(self, fzk_lod2_building: Building) -> None:
        assert fzk_lod2_building.relative_to_water() is None

    def test_relative_to_water(self, extended_building: Building) -> None:
        assert extended_building.relative_to_water() == RelativeToWater.EntirelyAboveWaterSurface


def kind(attribute: Any) -> str:
    """The attribute's kind, as the former tests' class names."""
    if attribute.as_string() is not None:
        return "StringAttribute"
    if attribute.as_int() is not None:
        return "IntAttribute"
    if attribute.as_double() is not None:
        return "DoubleAttribute"
    if MeasureAttribute.try_from(attribute) is not None:
        return "MeasureAttribute"
    assert GenericAttributeSet.try_from(attribute) is not None
    return "GenericAttributeSet"


def value(attribute: Any) -> Any:
    typed = attribute.as_string() or attribute.as_int() or attribute.as_double()
    return typed.value()


class TestExternalReferences:
    def test_values(self, tum_building: Building) -> None:
        references = list(tum_building.external_references())
        assert len(references) == 1
        reference = references[0]
        assert isinstance(reference, ExternalReference)
        assert reference.target_resource() == "DEBYvAAAAABTMIyA"
        assert reference.information_system() == (
            "http://repository.gdi-de.org/schemas/adv/citygml/fdv/art.htm#_9100"
        )
        assert reference.relation_type() is None

    def test_empty(self, fzk_lod2_building: Building) -> None:
        assert list(fzk_lod2_building.external_references()) == []


class TestGenericAttributes:
    def test_kinds_and_values(self, fzk_lod2_building: Building) -> None:
        attributes = list(fzk_lod2_building.generic_attributes())
        assert [(kind(a), a.name()) for a in attributes] == [
            ("MeasureAttribute", "GrossPlannedArea"),
            ("StringAttribute", "ConstructionMethod"),
            ("StringAttribute", "IsLandmarked"),
        ]
        assert attributes[1].as_string().value() == "New Building"

    def test_measure_attribute(self, fzk_lod2_building: Building) -> None:
        measure = MeasureAttribute.try_from(next(iter(fzk_lod2_building.generic_attributes())))
        assert isinstance(measure, MeasureAttribute)
        assert measure.value().value() == 120.0
        assert measure.value().uom() == "m2"

    def test_int_and_double_attributes(self, asam_road_model: Any) -> None:
        attributes = list(features_of(asam_road_model, TrafficSpace)[0].generic_attributes())
        by_name = {a.name(): a for a in attributes}
        assert by_name["identifier_laneId"].as_int().value() == 1
        assert by_name["opendrive_road_length"].as_double().value() == 40.0

    def test_value_types(self, asam_road_model: Any) -> None:
        for attribute in features_of(asam_road_model, TrafficSpace)[0].generic_attributes():
            if attribute.as_int() is not None:
                assert type(attribute.as_int().value()) is int
            elif attribute.as_double() is not None:
                assert type(attribute.as_double().value()) is float

    def test_generic_attribute_set(self, extended_building: Building) -> None:
        attribute_set = GenericAttributeSet.try_from(next(iter(extended_building.generic_attributes())))
        assert isinstance(attribute_set, GenericAttributeSet)
        assert attribute_set.name() == "energy"
        nested = list(attribute_set.generic_attributes())
        assert [(kind(a), a.name(), value(a)) for a in nested] == [
            ("DoubleAttribute", "demand", 12.5),
            ("StringAttribute", "label", "A+"),
        ]

    def test_thematic_surface_without_attributes(self, fzk_lod2_model: Any) -> None:
        assert list(features_of(fzk_lod2_model, WallSurface)[0].generic_attributes()) == []


class TestRelatedTo:
    def test_empty(self, fzk_lod2_building: Building) -> None:
        assert list(fzk_lod2_building.related_to()) == []

    def test_relation(self, extended_building: Building) -> None:
        relations = objects(extended_building.related_to())
        assert len(relations) == 1
        relation = relations[0]
        assert isinstance(relation, CityObjectRelation)
        assert relation.relation_type().value() == "shared"
        assert relation.relation_type().code().code_space() is None
        assert relation.relation_to().href().to_string() == "#UUID_other"

    def test_relation_generic_attributes(self, extended_building: Building) -> None:
        attributes = list(objects(extended_building.related_to())[0].generic_attributes())
        assert len(attributes) == 1
        assert (attributes[0].name(), attributes[0].as_int().value()) == ("weight", 3)
