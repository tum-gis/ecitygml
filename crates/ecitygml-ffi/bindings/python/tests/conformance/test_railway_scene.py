"""The cases of crates/ecitygml/tests/conformance/railway-scene.md."""

from collections import Counter
from pathlib import Path
from typing import Any

import pytest

from conformance.helpers import close, first_name, read
from ecitygml import (
    Bridge,
    Building,
    CityFurniture,
    CityModel,
    FeatureType,
    GmlReader,
    GmlWriter,
    LevelOfDetail,
    MultiSurface,
    RelativeToTerrain,
    ReliefFeature,
    SolitaryVegetationObject,
    TinRelief,
    Tunnel,
)

TEMPLATE_A = "#Mult_SO043561_5693_194007"
TEMPLATE_B = "#Mult_SO045475_3243_790864"
INLINE_TEMPLATES = {"Forest tree 3", "Tree1", "Forest tree 1"}
TEMPLATE_A_TREES = {"Forest tree 4", "Forest tree 9", "Forest tree 5"}

WALL, ROOF, GROUND, CLOSURE = (
    FeatureType.WallSurface,
    FeatureType.RoofSurface,
    FeatureType.GroundSurface,
    FeatureType.ClosureSurface,
)


@pytest.fixture(scope="module")
def model() -> CityModel:
    return read("railway-scene", "Railway_Scene_LoD3__v3-thinned.gml")


def feature_types(city_model: CityModel) -> list[str]:
    # Two returned FeatureType values never compare equal (only one against the class constant), hence `str`.
    return [str(f.feature_type()) for f in city_model.iter_features()]


def all_of(city_model: CityModel, cls: Any) -> list[Any]:
    """All features of a class, in document order."""
    return [x for f in city_model.iter_features() if (x := cls.try_from(f)) is not None]


def implicit_geometry(tree: Any) -> Any:
    """A tree's inline LoD3 implicit geometry."""
    prop = tree.lod3_implicit_representation()
    assert prop.href() is None
    return prop.object()


def template_href(tree: Any) -> str | None:
    href = implicit_geometry(tree).relative_geometry().href()
    return href.to_string() if href is not None else None


def test_railway_city_model(model: CityModel) -> None:
    assert model.city_objects_len() == 52
    assert model.bounded_by() is None
    types = feature_types(model)
    assert len(types) == 232
    assert types[0] == str(FeatureType.CityModel)
    expected = {
        FeatureType.CityModel: 1,
        FeatureType.SolitaryVegetationObject: 15,
        FeatureType.Tunnel: 4,
        FeatureType.TunnelInstallation: 8,
        FeatureType.Railway: 10,
        FeatureType.Bridge: 4,
        FeatureType.BridgeConstructiveElement: 3,
        FeatureType.BridgeInstallation: 2,
        FeatureType.Building: 3,
        FeatureType.BuildingInstallation: 56,
        FeatureType.CityFurniture: 11,
        FeatureType.CityObjectGroup: 1,
        FeatureType.GenericOccupiedSpace: 2,
        FeatureType.WaterBody: 1,
        FeatureType.WaterSurface: 1,
        FeatureType.WaterGroundSurface: 1,
        FeatureType.ReliefFeature: 1,
        FeatureType.TinRelief: 1,
        WALL: 33,
        ROOF: 12,
        GROUND: 7,
        CLOSURE: 8,
        FeatureType.DoorSurface: 9,
        FeatureType.WindowSurface: 34,
        FeatureType.OuterCeilingSurface: 3,
        FeatureType.OuterFloorSurface: 1,
    }
    assert Counter(types) == Counter({str(t): n for t, n in expected.items()})
    assert len(list(model.iter_city_objects())) == 231


def test_railway_tunnels(model: CityModel) -> None:
    expected = [
        ("GMLID_BUI142242_863_347", "Tunnel KIT/KHH-3", [GROUND, WALL, ROOF, WALL, CLOSURE, CLOSURE]),
        ("GMLID_BUI336993_213_9312", "Tunnel KIT/KHH-2", [WALL, ROOF, WALL, CLOSURE, CLOSURE, GROUND]),
        ("GMLID_BUI289877_1911_4122", "Tunnel KIT/KHH-4", [WALL, GROUND, CLOSURE, WALL, ROOF, CLOSURE]),
        ("GMLID_BUI180021_673_14143", "Tunnel KIT/KHH-1", [GROUND, WALL, ROOF, CLOSURE, CLOSURE, WALL]),
    ]
    tunnels = all_of(model, Tunnel)
    assert len(tunnels) == len(expected)
    for tunnel, (feature_id, name, boundaries) in zip(tunnels, expected):
        assert tunnel.feature_id().as_str() == feature_id
        assert first_name(tunnel) == name
        props = list(tunnel.boundaries())
        assert all(p.href() is None for p in props)
        assert [str(p.object().feature_type()) for p in props] == [str(t) for t in boundaries]
        assert tunnel.class_() is None
        assert list(tunnel.functions()) == []
        assert list(tunnel.usages()) == []
        assert list(tunnel.tunnel_parts()) == []
        created = tunnel.creation_date()
        assert (created.year(), created.month(), created.day()) == (2015, 3, 6)
        assert (created.hour(), created.minute()) == (0, 0)
        assert created.offset_seconds() == 3600
        assert tunnel.relative_to_terrain() == RelativeToTerrain.EntirelyAboveTerrain


def test_railway_trees(model: CityModel) -> None:
    expected = [
        ("GMLID_SO0158953_776_12462", "Forest tree 3", "1070", "1800", []),
        ("GMLID_SO092422_3593_9527", "Tree1", None, "9999", ["LOD3"]),
        ("GMLID_SO0200811_525_4986", "Forest tree 1", "1060", "1640", []),
        ("GMLID_SO0321978_1466_7441", "Forest tree 4", "1070", "1800", []),
        ("GMLID_SO0260143_1214_1315", "Forest tree 11", "1060", "1640", []),
        ("GMLID_SO0400934_2926_3381", "Forest tree 12", "1060", "1640", []),
        ("GMLID_SO0124800_3522_13577", "Forest tree 13", "1060", "1640", []),
        ("GMLID_SO0443764_1492_9667", "Forest tree 14", "1060", "1640", []),
        ("GMLID_SO015374_872_14131", "Forest tree 2", "1060", "1640", []),
        ("GMLID_SO081792_2341_11961", "Forest tree 10", "1060", "1640", []),
        ("GMLID_SO0283142_1335_8999", "Forest tree 7", "1060", "1640", []),
        ("GMLID_SO0107241_3793_12555", "Forest tree 9", "1070", "1800", []),
        ("GMLID_SO0286258_965_2893", "Forest tree 5", "1070", "1800", []),
        ("GMLID_SO0410128_214_10515", "Forest tree 6", "1060", "1640", []),
        ("GMLID_SO086970_1053_8814", "Forest tree 8", "1060", "1640", []),
    ]
    trees = all_of(model, SolitaryVegetationObject)
    assert len(trees) == len(expected)
    for tree, (feature_id, name, class_, species, functions) in zip(trees, expected):
        assert tree.feature_id().as_str() == feature_id
        assert first_name(tree) == name
        assert (tree.class_().value() if tree.class_() is not None else None) == class_
        assert tree.species().value() == species
        assert [f.value() for f in tree.functions()] == functions
        assert list(tree.usages()) == []
        assert tree.lod1_implicit_representation() is None
        assert tree.lod2_implicit_representation() is None


def test_railway_tree_templates(model: CityModel) -> None:
    for tree in all_of(model, SolitaryVegetationObject):
        geometry = implicit_geometry(tree)
        assert geometry.mime_type() is None
        matrix = geometry.transformation_matrix()
        assert [matrix.get(i, i) for i in range(4)] == close([30.0, 30.0, 30.0, 1.0])
        name = first_name(tree)
        prop = geometry.relative_geometry()
        if name in INLINE_TEMPLATES:
            assert prop.href() is None
            multi_surface = MultiSurface.try_from(prop.object())
            assert multi_surface is not None, name
            assert len(list(multi_surface.surface_member())) == 1
        else:
            assert prop.object() is None
            assert template_href(tree) == (TEMPLATE_A if name in TEMPLATE_A_TREES else TEMPLATE_B), name


def test_railway_tree_placement(model: CityModel) -> None:
    for tree in all_of(model, SolitaryVegetationObject):
        geometry = implicit_geometry(tree)
        pos = geometry.reference_point().object().pos()
        matrix = geometry.transformation_matrix()
        translation = (matrix.get(0, 3), matrix.get(1, 3), matrix.get(2, 3))
        name = first_name(tree)
        if name == "Tree1":
            assert (pos.x(), pos.y(), pos.z()) == close((-568.8000793496976, 457.60044759869743, 105.00139681350242))
            assert translation == close((0.0, 0.0, 0.0))
        else:
            assert (pos.x(), pos.y(), pos.z()) == close((-600.0, 400.0, -150.0))
            if name == "Forest tree 3":
                assert translation == close((39.4421005419207, 220.3838834926932, 268.5013679006178))


def test_railway_furniture(model: CityModel) -> None:
    expected = [
        ("GMLID_7431654_78949_792", "1090"),
        ("GMLID_0528986_170479_94", "OTHERS"),
        ("GMLID_4323540_367099_910", "1090"),
        ("GMLID_1381455_184173_656", "OTHERS"),
        ("GMLID_1429491_351612_1485", "1090"),
        ("GMLID_5361967_192822_672", "1090"),
        ("GMLID_2108434_31807_876", "1090"),
        ("GMLID_0373494_301709_129", "1540"),
        ("GMLID_6162422_289094_1279", "1090"),
        ("GMLID_3313190_307178_612", "1090"),
        ("GMLID_855011_330784_753", "1540"),
    ]
    furniture = all_of(model, CityFurniture)
    assert [(f.feature_id().as_str(), [x.value() for x in f.functions()]) for f in furniture] == [
        (i, [function]) for i, function in expected
    ]
    for item in furniture:
        assert item.class_() is None
        assert list(item.usages()) == []
        assert item.lod3_implicit_representation() is None
        prop = item.lod3_multi_surface()
        assert prop.href() is None
        assert len(list(prop.object().surface_member())) == 1


def test_railway_relief(model: CityModel) -> None:
    [relief] = all_of(model, ReliefFeature)
    assert relief.feature_id().as_str() == "GMLID_TIN436865_187531_1154"
    assert list(relief.names()) == []
    assert relief.lod() == LevelOfDetail.Three
    [component] = list(relief.relief_components())
    assert component.href() is None
    assert component.object().feature_type() == FeatureType.TinRelief

    [tin_relief] = all_of(model, TinRelief)
    assert tin_relief.feature_id().as_str() == "UUID_5aa70b07-6bbf-427b-8222-d72ed77dbfa9"
    assert tin_relief.lod() == LevelOfDetail.Three
    tin = tin_relief.tin()
    assert tin.href() is None
    surface = tin.object()
    assert len(list(surface.triangles())) == 1
    assert surface.area_3d() == close(3.2750424144626247)


def test_railway_buildings_and_bridges(model: CityModel) -> None:
    assert [(b.feature_id().as_str(), first_name(b), len(list(b.boundaries()))) for b in all_of(model, Building)] == [
        ("GMLID_BUI184698_512_898", "Station KIT/KHH-1", 13),
        ("GMLID_BUI46739_1739_10911", "Chapel KIT/KHH-1", 19),
        ("GMLID_BUI130363_1235_6047", "Boatshouse KIT/KHH-1", 8),
    ]
    assert [(b.feature_id().as_str(), first_name(b)) for b in all_of(model, Bridge)] == [
        ("GMLID_BUI205585_1385_1373", "Bridge KIT 4"),
        ("GMLID_BUI51891_765_738", "Bridge KIT 3"),
        ("GMLID_BUI100628_817_8083", "Bridge KIT 2"),
        ("GMLID_BUI30683_572_6686", "Bridge KIT 1"),
    ]


def test_railway_round_trip(model: CityModel, tmp_path: Path) -> None:
    path = tmp_path / "round-trip.gml"
    GmlWriter.from_path(str(path)).finish(model)
    written = GmlReader.from_path(str(path)).finish()
    assert feature_types(written) == feature_types(model)

    def ids(city_model: CityModel) -> list[str]:
        return [
            x.feature_id().as_str()
            for cls in (Tunnel, SolitaryVegetationObject, CityFurniture, Building, Bridge)
            for x in all_of(city_model, cls)
        ]

    def hrefs(city_model: CityModel) -> list[str | None]:
        return [template_href(t) for t in all_of(city_model, SolitaryVegetationObject)]

    assert ids(written) == ids(model)
    assert hrefs(written) == hrefs(model)
