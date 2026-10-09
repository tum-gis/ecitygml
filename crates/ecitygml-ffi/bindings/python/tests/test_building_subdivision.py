"""Storey and BuildingUnit (AbstractBuildingSubdivision, AbstractLogicalSpace).

Ported from the former PyO3 bindings' `test_building_subdivision.py`. Not ported (not in the
Diplomat bindings): `repr`. `building_subdivisions()` yields
`AbstractBuildingSubdivisionKind`s, whose `feature_type()` tells storeys and building units apart;
the concrete classes come from `Storey.try_from` and `BuildingUnit.try_from` on the features.
"""

from pathlib import Path

import pytest

from conftest import FZK_LOD2, city_objects_of, features_of, objects, read_injected, read_model
from ecitygml import Building, BuildingUnit, CityModel, FeatureType, GmlWriter, Storey

# No fixture contains building subdivisions; they are injected into a copy of the FZK LoD2
# building after its storey counts, as in the CityGML 3.0 schema (AbstractBuildingType).
ANCHOR = "<bldg:storeysBelowGround>0</bldg:storeysBelowGround>"
SUBDIVISIONS = """
      <bldg:buildingSubdivision>
        <bldg:Storey gml:id="storey_ground">
          <bldg:class codeSpace="https://example.org/storey_class">ground</bldg:class>
          <bldg:function>living</bldg:function>
        </bldg:Storey>
      </bldg:buildingSubdivision>
      <bldg:buildingSubdivision>
        <bldg:BuildingUnit gml:id="unit_1">
          <bldg:usage>residential</bldg:usage>
        </bldg:BuildingUnit>
      </bldg:buildingSubdivision>"""


@pytest.fixture(scope="module")
def model(tmp_path_factory: pytest.TempPathFactory) -> CityModel:
    tmp_path = tmp_path_factory.mktemp("subdivision")
    return read_injected(tmp_path, FZK_LOD2, ANCHOR, ANCHOR + SUBDIVISIONS)


@pytest.fixture(scope="module")
def building(model: CityModel) -> Building:
    return features_of(model, Building)[0]


class TestBuildingSubdivisions:
    def test_kinds_in_document_order(self, building: Building) -> None:
        kinds = [s.feature_type() for s in objects(building.building_subdivisions())]
        assert kinds == [FeatureType.Storey, FeatureType.BuildingUnit]

    def test_absent(self) -> None:
        model = read_model(FZK_LOD2)
        assert list(features_of(model, Building)[0].building_subdivisions()) == []

    def test_storey_codes(self, building: Building) -> None:
        storey = objects(building.building_subdivisions())[0]
        assert storey.class_() is not None
        assert (storey.class_().value(), storey.class_().code().code_space()) == (
            "ground",
            "https://example.org/storey_class",
        )
        assert [f.value() for f in storey.functions()] == ["living"]
        assert list(storey.usages()) == []

    def test_building_unit_codes(self, building: Building) -> None:
        unit = objects(building.building_subdivisions())[1]
        assert unit.class_() is None
        assert [u.value() for u in unit.usages()] == ["residential"]

    def test_feature_types_and_ids(self, building: Building) -> None:
        storey, unit = objects(building.building_subdivisions())
        assert (storey.id().as_str(), storey.feature_type()) == ("storey_ground", FeatureType.Storey)
        assert (unit.id().as_str(), unit.feature_type()) == ("unit_1", FeatureType.BuildingUnit)

    def test_space_geometry_absent(self, building: Building) -> None:
        storey = objects(building.building_subdivisions())[0]
        assert storey.lod1_solid() is None
        assert storey.lod0_multi_surface() is None


class TestFeatures:
    def test_filter_by_class(self, model: CityModel) -> None:
        assert [s.id().as_str() for s in features_of(model, Storey)] == ["storey_ground"]
        assert [u.id().as_str() for u in features_of(model, BuildingUnit)] == ["unit_1"]

    def test_not_top_level_city_objects(self, model: CityModel) -> None:
        assert model.city_objects_len() == 1
        assert [s.id().as_str() for s in city_objects_of(model, Storey)] == ["storey_ground"]
        assert [u.id().as_str() for u in city_objects_of(model, BuildingUnit)] == ["unit_1"]


def test_write_round_trip(model: CityModel, tmp_path: Path) -> None:
    path = tmp_path / "written.gml"
    GmlWriter.from_path(str(path)).finish(model)
    written = read_model(path)
    storey, unit = objects(features_of(written, Building)[0].building_subdivisions())
    assert (storey.feature_type(), unit.feature_type()) == (FeatureType.Storey, FeatureType.BuildingUnit)
    assert storey.class_() is not None and storey.class_().value() == "ground"
    assert [u.value() for u in unit.usages()] == ["residential"]
