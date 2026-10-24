"""The cases of crates/ecitygml/tests/api/types.md. `level_of_detail_index` is scoped out (nanobind enums have no
methods)."""

from typing import Any

import pytest

from api.helpers import assert_error, fixture
from conftest import read_model
from ecitygml import (
    AbstractFeatureKindRef,
    AuxiliaryTrafficArea,
    AuxiliaryTrafficSpace,
    Building,
    CityModel,
    Date,
    DateTime,
    DirectPosition,
    DoorSurface,
    ErrorKind,
    FeatureType,
    GroundSurface,
    Road,
    RoofSurface,
    Section,
    SolitaryVegetationObject,
    TrafficArea,
    TrafficSpace,
    WallSurface,
    WindowSurface,
)

FZK_LOD1 = fixture("fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml")
FZK_LOD2 = fixture("fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml")
FZK_LOD3 = fixture("fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml")
TUM = fixture("tum-main-entrance/TUM-Main-Entrance.gml")
ASAM_ROAD_SHAPE = fixture("asam-opendrive/ASAM-UC_RoadShape.gml")
ASAM_JUNCTION = fixture("asam-opendrive/ASAM-Ex_Bidirectional_Junction.gml")
RAILWAY = fixture("railway-scene/Railway_Scene_LoD3__v3-thinned.gml")
SIG3D = "http://www.sig3d.org/codelists/citygml/2.0/building/2.0/_AbstractBuilding_"


def first(city_model: CityModel, cls: Any) -> Any:
    """The first feature that `cls.try_from` accepts."""
    return next(x for f in city_model.iter_features() if (x := cls.try_from(f)) is not None)


def test_direct_position_new() -> None:
    position = DirectPosition(1.0, 2.0, 3.0)
    assert (position.x(), position.y(), position.z()) == (1.0, 2.0, 3.0)
    with pytest.raises(Exception) as raised:
        DirectPosition(float("nan"), 0.0, 0.0)
    assert_error(raised, ErrorKind.InvalidArgument, "non-finite")


def test_feature_type_name() -> None:
    assert FeatureType.Building.name == "Building"
    assert FeatureType.TinRelief.name == "TinRelief"


def test_date_from_parts() -> None:
    date = Date.from_parts(2020, 1, 2, 3600)
    assert (date.year(), date.month(), date.day(), date.offset_seconds()) == (2020, 1, 2, 3600)
    start = date.start_of_day()
    assert (start.hour(), start.minute(), start.second()) == (0, 0, 0)
    assert start.to_rfc3339() == "2020-01-02T00:00:00+01:00"

    with pytest.raises(Exception) as raised:
        Date.from_parts(2021, 2, 30, 0)
    assert_error(raised, ErrorKind.InvalidArgument, "do not form a valid date")


def test_date_time_from_parts() -> None:
    date_time = DateTime.from_parts(2017, 1, 23, 13, 14, 15, 500_000_000, -7200)
    assert (date_time.year(), date_time.month(), date_time.day()) == (2017, 1, 23)
    assert (date_time.hour(), date_time.minute(), date_time.second()) == (13, 14, 15)
    assert date_time.nanosecond() == 500_000_000
    assert date_time.offset_seconds() == -7200
    assert date_time.timestamp() == 1485184455
    assert date_time.timestamp_subsec_nanos() == 500_000_000
    assert date_time.to_rfc3339() == "2017-01-23T13:14:15.500-02:00"

    with pytest.raises(Exception) as raised:
        DateTime.from_parts(2020, 1, 1, 0, 0, 0, 0, 30)
    assert_error(raised, ErrorKind.InvalidArgument, "timezone offset of 30 s is invalid")


def test_date_time_read() -> None:
    city_model = read_model(FZK_LOD2)
    assert first(city_model, Building).creation_date().to_rfc3339() == "2017-01-23T00:00:00+01:00"


def assert_try_from_matches(city_model: CityModel, classes: list[tuple[Any, FeatureType]]) -> None:
    """`cls.try_from` accepts exactly the features of its feature type."""
    for feature in city_model.iter_features():
        for cls, feature_type in classes:
            accepted = cls.try_from(feature) is not None
            assert accepted == (feature.feature_type() == feature_type), (cls, str(feature.feature_type()))


def test_try_from_matches_feature_type() -> None:
    assert_try_from_matches(
        read_model(FZK_LOD3),
        [
            (Building, FeatureType.Building),
            (WallSurface, FeatureType.WallSurface),
            (RoofSurface, FeatureType.RoofSurface),
            (GroundSurface, FeatureType.GroundSurface),
            (DoorSurface, FeatureType.DoorSurface),
            (WindowSurface, FeatureType.WindowSurface),
        ],
    )
    assert_try_from_matches(
        read_model(ASAM_ROAD_SHAPE),
        [
            (Road, FeatureType.Road),
            (Section, FeatureType.Section),
            (TrafficSpace, FeatureType.TrafficSpace),
            (TrafficArea, FeatureType.TrafficArea),
            (AuxiliaryTrafficSpace, FeatureType.AuxiliaryTrafficSpace),
            (AuxiliaryTrafficArea, FeatureType.AuxiliaryTrafficArea),
        ],
    )


def test_feature_from_city_object() -> None:
    city_model = read_model(ASAM_JUNCTION)
    city_object = next(iter(city_model.iter_city_objects()))
    assert city_object.feature_type() == FeatureType.Road
    feature = AbstractFeatureKindRef.from_city_object(city_object)
    assert feature.feature_type() == FeatureType.Road
    assert Road.try_from(feature).feature_id().as_str() == "UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f"
    assert Building.try_from(feature) is None


def test_matrix_index_out_of_range() -> None:
    city_model = read_model(RAILWAY)
    tree = next(
        t
        for f in city_model.iter_features()
        if (t := SolitaryVegetationObject.try_from(f)) is not None
        and t.feature_id().as_str() == "GMLID_SO092422_3593_9527"
    )
    matrix = tree.lod3_implicit_representation().object().transformation_matrix()
    assert matrix.get(3, 3) == 1.0
    for row, column in [(4, 0), (0, 4)]:
        with pytest.raises(Exception) as raised:
            matrix.get(row, column)
        assert_error(raised, ErrorKind.InvalidArgument, "out of range")


def test_gml_id() -> None:
    city_model = read_model(FZK_LOD1)
    generated = city_model.feature_id().as_str()
    assert generated.startswith("ecitygml-gen-feature-")
    assert city_model.id().as_str() == generated

    city_model = read_model(FZK_LOD2)
    wall = first(city_model, WallSurface)
    assert wall.id().as_str() == "GML_5856d7ad-5e34-498a-817b-9544bfbb1475"
    assert wall.feature_id().as_str() == "GML_5856d7ad-5e34-498a-817b-9544bfbb1475"

    city_model = read_model(TUM)
    assert first(city_model, Building).id().as_str() == "DEBY_LOD2_4959457"


def test_code_space() -> None:
    city_model = read_model(FZK_LOD2)
    building = first(city_model, Building)
    code = building.class_().code()
    assert (code.value(), code.code_space()) == ("1000", SIG3D + "class.xml")
    assert [f.code().code_space() for f in building.functions()] == [SIG3D + "function.xml"]
    assert [u.code().code_space() for u in building.usages()] == [SIG3D + "usage.xml"]

    city_model = read_model(TUM)
    assert [(f.value(), f.code().code_space()) for f in first(city_model, Building).functions()] == [
        ("31001_3020", None)
    ]

    city_model = read_model(FZK_LOD1)
    assert [(n.value(), n.code_space()) for n in city_model.names()] == [("AC14-FZK-Haus", None)]
