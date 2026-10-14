from pathlib import Path

import pytest

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
    GeometryType,
    GmlReader,
    GranularityValue,
    GroundSurface,
    HeightStatusValue,
    LineString,
    Polygon,
    Road,
    RoofSurface,
    SpaceType,
    TrafficArea,
    TrafficDirectionValue,
    TrafficSpace,
    WallSurface,
    WindowSurface,
)

FIXTURES = Path(__file__).parents[5] / "tests" / "fixtures"


def read(path: str) -> CityModel:
    return GmlReader.from_path(path).finish()


def test_reads_city_objects() -> None:
    city_model = read(str(FIXTURES / "FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml"))
    assert city_model.city_objects_len() == 1


def test_missing_file_raises_with_message() -> None:
    with pytest.raises(Exception, match="No such file") as info:
        read(str(FIXTURES / "does-not-exist.gml"))
    assert info.value.args[0].kind() == ErrorKind.Io


def test_unsupported_extension_raises() -> None:
    with pytest.raises(Exception) as info:
        read(str(FIXTURES.parent.parent / "README.md"))
    assert info.value.args[0].kind() == ErrorKind.InvalidArgument


def test_bounded_by() -> None:
    city_model = read(str(FIXTURES / "FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml"))
    bounding_shape = city_model.bounded_by()
    assert bounding_shape is not None
    envelope = bounding_shape.envelope()
    assert envelope is not None
    assert (envelope.size_x(), envelope.size_y()) == (12.0, 10.0)
    assert envelope.size_z() == pytest.approx(6.517669)


def test_envelope_corners() -> None:
    city_model = read(str(FIXTURES / "FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml"))
    envelope = city_model.bounded_by().envelope()
    lower = envelope.lower_corner()
    assert (lower.x(), lower.y(), lower.z()) == (457842.0, 5439083.0, 111.8)


def test_direct_position() -> None:
    position = DirectPosition(1.0, 2.0, 3.0)
    assert (position.x(), position.y(), position.z()) == (1.0, 2.0, 3.0)
    with pytest.raises(Exception, match="non-finite"):
        DirectPosition(float("nan"), 0.0, 0.0)


def test_lifespan(tmp_path: Path) -> None:
    # The fixtures only have lifespan dates on buildings; add one to the city model itself.
    original = (FIXTURES / "FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml").read_text()
    path = tmp_path / "lifespan.gml"
    path.write_text(original.replace(
        "</gml:boundedBy>",
        "</gml:boundedBy>\n  <creationDate>2017-01-23T00:00:00+01:00</creationDate>",
        1,
    ))
    city_model = read(str(path))
    creation_date = city_model.creation_date()
    assert creation_date is not None
    assert creation_date.to_rfc3339() == "2017-01-23T00:00:00+01:00"
    assert creation_date.timestamp() == 1485126000
    assert city_model.valid_to() is None


def test_feature_id(tmp_path: Path) -> None:
    original = (FIXTURES / "FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml").read_text()
    path = tmp_path / "id.gml"
    path.write_text(original.replace("<CityModel ", '<CityModel gml:id="CM_1" ', 1))
    assert read(str(path)).feature_id().as_str() == "CM_1"


def test_gml_id_and_names(tmp_path: Path) -> None:
    city_model = read(str(FIXTURES / "FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml"))
    assert [(n.value(), n.code_space()) for n in city_model.names()] == [("AC14-FZK-Haus", None)]

    original = (FIXTURES / "FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml").read_text()
    path = tmp_path / "gml_id.gml"
    path.write_text(original.replace("<CityModel ", '<CityModel gml:id="CM_gml" ', 1))
    assert read(str(path)).id().as_str() == "CM_gml"


def test_gml_reader_finishes_once() -> None:
    reader = GmlReader.from_path(str(FIXTURES / "FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml"))
    reader.with_rebuild_object_bounds(False)
    assert reader.finish().city_objects_len() == 1
    with pytest.raises(Exception, match="already finished"):
        reader.finish()


def test_traffic_spaces() -> None:
    city_model = read(str(FIXTURES / "ASAM-UC_RoadShape.gml"))
    spaces = [s for f in city_model.iter_features() if (s := TrafficSpace.try_from(f)) is not None]
    assert len(spaces) == 2
    # Diplomat's Python enums compare with == but don't hash consistently, so no sets here.
    directions = [s.traffic_direction() for s in spaces]
    assert TrafficDirectionValue.Forwards in directions
    assert TrafficDirectionValue.Backwards in directions

    space = spaces[0]
    assert space.granularity() == GranularityValue.Lane
    assert [f.value() for f in space.functions()] == ["1"]
    assert [u.code().value() for u in space.usages()] == ["2"]
    assert list(space.occupancies()) == []
    assert space.class_() is None
    assert space.space_type() == SpaceType.Open
    assert space.feature_id().as_str()


def test_traffic_space_multi_curves() -> None:
    city_model = read(str(FIXTURES / "ASAM-UC_RoadShape.gml"))
    spaces = [s for f in city_model.iter_features() if (s := TrafficSpace.try_from(f)) is not None]
    assert len(spaces) == 2
    for space in spaces:
        assert space.lod0_multi_curve() is None
        assert space.lod3_multi_curve() is None
        multi_curve = space.lod2_multi_curve().object()
        assert multi_curve.length_3d() == pytest.approx(40.0)
        assert multi_curve.compute_envelope() is not None

        members = list(multi_curve.curve_member())
        assert len(members) == 1
        curve = members[0].object()
        assert curve.geometry_type() == GeometryType.LineString
        line_string = LineString.try_from(curve)
        assert line_string.length_3d() == pytest.approx(40.0)
        assert len(list(line_string.points())) == 2


# A 10 m x 4 m rectangle with a 1 m x 1 m hole (39 m^2), inserted after the first lod2Solid.
LOD2_MULTI_SURFACE = '</lod2Solid><lod2MultiSurface><gml:MultiSurface><gml:surfaceMember><gml:Polygon gml:id="PolyID_space"><gml:exterior><gml:LinearRing><gml:posList srsDimension="3">0 0 0 10 0 0 10 4 0 0 4 0 0 0 0</gml:posList></gml:LinearRing></gml:exterior><gml:interior><gml:LinearRing><gml:posList srsDimension="3">1 1 0 1 2 0 2 2 0 2 1 0 1 1 0</gml:posList></gml:LinearRing></gml:interior></gml:Polygon></gml:surfaceMember></gml:MultiSurface></lod2MultiSurface>'


def test_traffic_space_multi_surface(tmp_path: Path) -> None:
    original = (FIXTURES / "ASAM-UC_RoadShape.gml").read_text()
    path = tmp_path / "multi_surface.gml"
    path.write_text(original.replace("</lod2Solid>", LOD2_MULTI_SURFACE, 1))
    city_model = read(str(path))
    spaces = [s for f in city_model.iter_features() if (s := TrafficSpace.try_from(f)) is not None]
    assert len(spaces) == 2
    assert spaces[1].lod2_multi_surface() is None

    space = spaces[0]
    assert space.lod0_multi_surface() is None
    assert space.lod3_multi_surface() is None
    multi_surface = space.lod2_multi_surface().object()
    assert multi_surface.area_3d() == pytest.approx(39.0)
    assert multi_surface.compute_envelope() is not None
    assert len(list(multi_surface.points())) == 8  # 4 per ring, without the closing position

    members = list(multi_surface.surface_member())
    assert len(members) == 1
    surface = members[0].object()
    assert surface.geometry_type() == GeometryType.Polygon
    assert surface.id().as_str() == "PolyID_space"
    polygon = Polygon.try_from(surface)
    assert polygon.area_3d() == pytest.approx(39.0)
    assert len(list(polygon.points())) == 8


def test_traffic_space_lod0_point(tmp_path: Path) -> None:
    original = (FIXTURES / "ASAM-UC_RoadShape.gml").read_text()
    path = tmp_path / "point.gml"
    path.write_text(original.replace("</lod2Solid>", '</lod2Solid><lod0Point><gml:Point gml:id="PointID_space"><gml:pos srsDimension="3">1.5 -2.5 3.25</gml:pos></gml:Point></lod0Point>', 1))
    city_model = read(str(path))  # keep the model alive while its features are borrowed
    spaces = [s for f in city_model.iter_features() if (s := TrafficSpace.try_from(f)) is not None]
    assert len(spaces) == 2
    assert spaces[1].lod0_point() is None

    point = spaces[0].lod0_point().object()
    assert point.id().as_str() == "PointID_space"
    pos = point.pos()
    assert (pos.x(), pos.y(), pos.z()) == (1.5, -2.5, 3.25)
    assert point.compute_envelope().lower_corner().x() == 1.5


def test_traffic_areas() -> None:
    city_model = read(str(FIXTURES / "ASAM-UC_RoadShape.gml"))
    areas = [a for f in city_model.iter_features() if (a := TrafficArea.try_from(f)) is not None]
    assert len(areas) == 2

    area = areas[0]
    assert area.class_() is None
    assert [f.value() for f in area.functions()] == ["1"]
    assert [u.code().value() for u in area.usages()] == ["2"]
    assert area.surface_material() is None
    assert area.lod0_multi_curve() is None
    assert area.feature_id().as_str().startswith("UUID_8625bf6f")
    assert [n.value() for n in area.names()] == ["Lane"]

    total_area = sum(a.lod2_multi_surface().object().area_3d() for a in areas)
    assert total_area == pytest.approx(282.1405004348745)


def test_auxiliary_traffic_spaces_and_areas() -> None:
    city_model = read(str(FIXTURES / "ASAM-UC_RoadShape.gml"))
    features = list(city_model.iter_features())

    spaces = [s for f in features if (s := AuxiliaryTrafficSpace.try_from(f)) is not None]
    assert len(spaces) == 2
    for space in spaces:
        assert space.class_() is None
        assert list(space.functions()) == []
        assert space.granularity() == GranularityValue.Lane
        assert space.lod2_solid().object().volume_3d() == pytest.approx(100.0)
        assert space.lod2_multi_curve().object().length_3d() == pytest.approx(40.0)

    areas = [a for f in features if (a := AuxiliaryTrafficArea.try_from(f)) is not None]
    assert len(areas) == 2
    for area in areas:
        assert area.class_() is None
        assert list(area.functions()) == []
        assert area.surface_material() is None
        assert [n.value() for n in area.names()] == ["Lane"]
        assert area.lod2_multi_surface().object().area_3d() == pytest.approx(40.0)


def test_road_with_section() -> None:
    city_model = read(str(FIXTURES / "ASAM-UC_RoadShape.gml"))
    road = next(r for f in city_model.iter_features() if (r := Road.try_from(f)) is not None)
    assert road.class_() is None
    assert list(road.intersections()) == []
    assert list(road.traffic_spaces()) == []

    sections = list(road.sections())
    assert len(sections) == 1
    section = sections[0].object()
    assert len(list(section.traffic_spaces())) == 2
    volume = sum(p.object().lod2_solid().object().volume_3d() for p in section.auxiliary_traffic_spaces())
    assert volume == pytest.approx(200.0)


def test_road_with_sections_intersection_and_markings() -> None:
    city_model = read(str(FIXTURES / "ASAM-Ex_Bidirectional_Junction.gml"))
    road = next(r for f in city_model.iter_features() if (r := Road.try_from(f)) is not None)
    sections = [p.object() for p in road.sections()]
    assert [len(list(s.traffic_spaces())) for s in sections] == [2, 1, 1]
    markings = [p.object() for p in sections[0].markings()]
    assert len(markings) == 4
    assert all(m.class_() is None for m in markings)

    intersections = [p.object() for p in road.intersections()]
    assert len(intersections) == 1
    assert len(list(intersections[0].traffic_spaces())) == 3


def test_building() -> None:
    city_model = read(str(FIXTURES / "FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml"))
    building = next(b for f in city_model.iter_features() if (b := Building.try_from(f)) is not None)
    assert building.class_().value() == "1000"
    assert [f.value() for f in building.functions()] == ["1000"]
    assert building.roof_type().value() == "1030"
    assert (building.storeys_above_ground(), building.storeys_below_ground()) == (2, 0)

    date = building.date_of_construction()
    assert (date.year(), date.month(), date.day()) == (2020, 1, 1)
    assert building.date_of_demolition() is None
    heights = list(building.heights())
    assert len(heights) == 1
    assert heights[0].high_reference().value() == "topOfConstruction"
    assert heights[0].status() == HeightStatusValue.Measured
    assert (heights[0].length().value(), heights[0].length().uom()) == (6.52, "m")

    assert building.lod1_solid().object().volume_3d() == pytest.approx(782.1228)
    assert list(building.building_parts()) == []


def test_building_part(tmp_path: Path) -> None:
    original = (FIXTURES / "FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml").read_text()
    part = '<bldg:buildingPart><bldg:BuildingPart gml:id="BP_1"><bldg:storeysAboveGround>1</bldg:storeysAboveGround></bldg:BuildingPart></bldg:buildingPart>'
    path = tmp_path / "building_part.gml"
    path.write_text(original.replace("</bldg:Building>", part + "</bldg:Building>", 1))
    city_model = read(str(path))
    building = next(b for f in city_model.iter_features() if (b := Building.try_from(f)) is not None)
    parts = [p.object() for p in building.building_parts()]
    assert [p.feature_id().as_str() for p in parts] == ["BP_1"]
    assert parts[0].storeys_above_ground() == 1


def test_wall_roof_and_ground_surfaces() -> None:
    city_model = read(str(FIXTURES / "FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml"))
    features = list(city_model.iter_features())

    def area(surface) -> float:
        return surface.lod2_multi_surface().object().area_3d()

    walls = [s for f in features if (s := WallSurface.try_from(f)) is not None]
    assert [next(iter(w.names())).value() for w in walls] == [
        "Outer Wall 1 (West)",
        "Outer Wall 2 (South)",
        "Outer Wall 3 (East)",
        "Outer Wall 4 (North)",
    ]
    assert sum(area(w) for w in walls) == pytest.approx(188.62887820601463)

    roofs = [s for f in features if (s := RoofSurface.try_from(f)) is not None]
    assert len(roofs) == 2
    assert sum(area(r) for r in roofs) == pytest.approx(138.56406460961398)

    grounds = [s for f in features if (s := GroundSurface.try_from(f)) is not None]
    assert [next(iter(g.names())).value() for g in grounds] == ["Base Surface"]
    assert area(grounds[0]) == pytest.approx(120.0)


def test_door_and_window_surfaces() -> None:
    city_model = read(str(FIXTURES / "FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml"))
    features = list(city_model.iter_features())
    doors = [s for f in features if (s := DoorSurface.try_from(f)) is not None]
    assert [next(iter(d.names())).value() for d in doors] == ["Door West", "Door South"]
    assert sum(d.lod3_multi_surface().object().area_3d() for d in doors) == pytest.approx(6.803850099444389)
    assert len([s for f in features if (s := WindowSurface.try_from(f)) is not None]) == 11

    west = next(
        w
        for f in features
        if (w := WallSurface.try_from(f)) is not None and next(iter(w.names())).value() == "Outer Wall 1 (West)"
    )
    fillings = [p.object() for p in west.filling_surfaces()]
    assert [(f.feature_type() == FeatureType.DoorSurface, next(iter(f.names())).value()) for f in fillings] == [
        (False, "Window Round"),
        (False, "Window North"),
        (True, "Door West"),
        (False, "Window South"),
    ]


def test_space_boundaries() -> None:
    city_model = read(str(FIXTURES / "FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml"))
    building = next(b for f in city_model.iter_features() if (b := Building.try_from(f)) is not None)
    boundaries = [p.object() for p in building.boundaries()]
    assert len(boundaries) == 7
    assert len([b for b in boundaries if b.feature_type() == FeatureType.GroundSurface]) == 1
    walls = [
        w for b in boundaries if (w := WallSurface.try_from(AbstractFeatureKindRef.from_space_boundary(b))) is not None
    ]
    assert len(walls) == 4
    assert sum(w.lod2_multi_surface().object().area_3d() for w in walls) == pytest.approx(188.62887820601463)

    city_model = read(str(FIXTURES / "ASAM-UC_RoadShape.gml"))
    spaces = [s for f in city_model.iter_features() if (s := TrafficSpace.try_from(f)) is not None]
    areas = [
        TrafficArea.try_from(AbstractFeatureKindRef.from_space_boundary(p.object()))
        for s in spaces
        for p in s.boundaries()
    ]
    assert sum(a.lod2_multi_surface().object().area_3d() for a in areas) == pytest.approx(282.1405004348745)


def test_total_traffic_space_volume() -> None:
    # The traffic-space analysis of the original Python example, with the generated API.
    city_model = GmlReader.from_path(str(FIXTURES / "ASAM-UC_RoadShape.gml")).finish()
    total_volume = 0.0
    for feature in city_model.iter_features():
        space = TrafficSpace.try_from(feature)
        if space and space.lod2_solid() and space.lod2_solid().object():
            total_volume += space.lod2_solid().object().volume_3d()
    assert total_volume == pytest.approx(1260.0)


def test_date_and_date_time_from_parts() -> None:
    date_time = DateTime.from_parts(2017, 1, 23, 13, 14, 15, 0, -7200)
    assert (date_time.year(), date_time.hour(), date_time.offset_seconds()) == (2017, 13, -7200)
    assert date_time.to_rfc3339() == "2017-01-23T13:14:15-02:00"

    date = Date.from_parts(2020, 1, 2, 3600)
    assert date.start_of_day().to_rfc3339() == "2020-01-02T00:00:00+01:00"
    with pytest.raises(Exception):
        Date.from_parts(2021, 2, 30, 0)
