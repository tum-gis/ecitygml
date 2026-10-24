"""The cases of crates/ecitygml/tests/conformance/asam-opendrive.md."""

from typing import Any

import pytest

from conformance.helpers import close, read
from ecitygml import (
    AbstractFeatureKindRef,
    AuxiliaryTrafficArea,
    CityModel,
    FeatureType,
    GranularityValue,
    LineString,
    MultiCurve,
    Reference,
    Road,
    Section,
    SpaceType,
    TrafficArea,
    TrafficDirectionValue,
    TrafficSpace,
)

ROAD_SHAPE = "ASAM-UC_RoadShape.gml"
JUNCTION = "ASAM-Ex_Bidirectional_Junction.gml"

SPACES = [
    "UUID_ae81947d-a661-3678-a5ee-eed58b68694f",
    "UUID_6e4de408-1e54-3869-b7ce-1be3f2261421",
    "UUID_9582b02f-5cc7-38f8-b79c-a3a18b31856c",
    "UUID_c772e261-27f1-30b6-8a94-1ccf23e71a74",
    "UUID_656f23c9-92b6-3c98-a1bf-40b5f2625b13",
    "UUID_86f8df09-c972-332b-a279-636373ce4e0c",
    "UUID_144a6807-5844-32b2-bb34-8b2671b1afaa",
]


@pytest.fixture(scope="module")
def road_shape() -> CityModel:
    return read("asam-opendrive", ROAD_SHAPE)


@pytest.fixture(scope="module")
def junction() -> CityModel:
    return read("asam-opendrive", JUNCTION)


def road(city_model: CityModel) -> Road:
    return next(r for f in city_model.iter_features() if (r := Road.try_from(f)) is not None)


def objects(properties: Any) -> list[Any]:
    """The objects of inline properties; fails on a reference-only property."""
    result = []
    for prop in properties:
        assert prop.href() is None
        result.append(prop.object())
    return result


def ids(features: list[Any]) -> list[str]:
    return [f.feature_id().as_str() for f in features]


def first_name(feature: Any) -> str:
    return next(iter(feature.names())).value()


def corner(position: Any) -> tuple[float, float, float]:
    return (position.x(), position.y(), position.z())


def only_boundary(space: Any) -> AbstractFeatureKindRef:
    """The single boundary of a space, inline, as a feature."""
    [boundary] = objects(space.boundaries())
    return AbstractFeatureKindRef.from_space_boundary(boundary)


def line_string(multi_curve: MultiCurve) -> tuple[int, float]:
    """The single curve member of an inline multi curve, as a line string: (point count, length)."""
    [member] = objects(multi_curve.curve_member())
    curve = LineString.try_from(member)
    return len(list(curve.points())), curve.length_3d()


def local_ids(references: Any) -> list[str]:
    return [Reference.from_traffic_space_reference(r).href().local_id() for r in references]


class TestRoadShape:
    @staticmethod
    def section(city_model: CityModel) -> Section:
        [section] = objects(road(city_model).sections())
        return section

    def traffic_spaces(self, city_model: CityModel) -> list[TrafficSpace]:
        return objects(self.section(city_model).traffic_spaces())

    def test_road_shape_city_model(self, road_shape: CityModel) -> None:
        assert road_shape.city_objects_len() == 1
        types = [
            FeatureType.CityModel,
            FeatureType.Road,
            FeatureType.Section,
            FeatureType.TrafficSpace,
            FeatureType.TrafficArea,
            FeatureType.TrafficSpace,
            FeatureType.TrafficArea,
            FeatureType.AuxiliaryTrafficSpace,
            FeatureType.AuxiliaryTrafficArea,
            FeatureType.AuxiliaryTrafficSpace,
            FeatureType.AuxiliaryTrafficArea,
        ]
        assert [f.feature_type() for f in road_shape.iter_features()] == types
        assert [o.feature_type() for o in road_shape.iter_city_objects()] == types[1:]
        envelope = road_shape.bounded_by().envelope()
        assert corner(envelope.lower_corner()) == close((-50.21567184593757, -2.4442507170297514, 0.0))
        assert corner(envelope.upper_corner()) == close((-13.007511850967884, 29.053746110395082, 4.95))

    def test_road_shape_road(self, road_shape: CityModel) -> None:
        r = road(road_shape)
        assert r.feature_id().as_str() == "UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f"
        assert r.class_() is None
        assert r.traffic_direction() is None
        for empty in (
            r.functions(),
            r.usages(),
            r.intersections(),
            r.occupancies(),
            r.traffic_spaces(),
            r.auxiliary_traffic_spaces(),
            r.markings(),
            r.holes(),
        ):
            assert list(empty) == []
        assert self.section(road_shape).feature_id().as_str() == "UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29"

    def test_road_shape_section(self, road_shape: CityModel) -> None:
        section = self.section(road_shape)
        assert section.class_() is None
        assert section.traffic_direction() is None
        assert section.lod0_multi_curve() is None
        assert section.lod1_solid() is None
        assert list(section.markings()) == []
        assert list(section.holes()) == []
        assert ids(objects(section.traffic_spaces())) == [
            "UUID_ae81947d-a661-3678-a5ee-eed58b68694f",
            "UUID_6e4de408-1e54-3869-b7ce-1be3f2261421",
        ]
        assert ids(objects(section.auxiliary_traffic_spaces())) == [
            "UUID_12298df9-4982-33a8-ab4a-9953410bbff7",
            "UUID_f8211bb5-0ce8-36e1-9b84-73d30114f578",
        ]

    def test_road_shape_traffic_spaces(self, road_shape: CityModel) -> None:
        spaces = self.traffic_spaces(road_shape)
        assert [s.traffic_direction() for s in spaces] == [
            TrafficDirectionValue.Backwards,
            TrafficDirectionValue.Forwards,
        ]
        for space in spaces:
            assert space.granularity() == GranularityValue.Lane
            assert space.class_() is None
            assert [f.value() for f in space.functions()] == ["1"]
            assert [u.value() for u in space.usages()] == ["2"]
            assert list(space.occupancies()) == []
            assert space.space_type() == SpaceType.Open
            assert space.relative_to_terrain() is None
            assert space.creation_date() is None
            assert list(space.predecessors()) == []
            assert list(space.successors()) == []
            assert TrafficArea.try_from(only_boundary(space)) is not None

    def test_road_shape_generic_attributes(self, road_shape: CityModel) -> None:
        space = self.traffic_spaces(road_shape)[0]

        def describe(attribute: Any) -> tuple[str, str]:
            if (int_attribute := attribute.as_int()) is not None:
                return attribute.name(), f"int {int_attribute.value()}"
            if (double := attribute.as_double()) is not None:
                return attribute.name(), f"double {double.value()!r}"
            return attribute.name(), f"string {attribute.as_string().value()}"

        assert [describe(a) for a in space.generic_attributes()] == [
            ("identifier_laneId", "int 1"),
            ("identifier_laneSectionId", "int 0"),
            ("identifier_roadId", "string 1"),
            ("opendrive_road_length", "double 40.0"),
            ("opendrive_road_rule", "string RIGHT_HAND_TRAFFIC"),
            ("opendrive_laneSection_curvePositionStart", "double 0.0"),
            ("opendrive_lane_type", "string DRIVING"),
            ("opendrive_lane_level", "string false"),
        ]

    def test_road_shape_traffic_space_geometry(self, road_shape: CityModel) -> None:
        spaces = self.traffic_spaces(road_shape)
        assert [s.lod2_solid().object().volume_3d() for s in spaces] == close([720.0, 540.0])
        for space in spaces:
            prop = space.lod2_multi_curve()
            assert prop.href() is None
            multi_curve = prop.object()
            assert multi_curve.length_3d() == close(40.0)
            points, length = line_string(multi_curve)
            assert points == 2
            assert length == close(40.0)
            assert space.lod0_multi_curve() is None
            assert space.lod3_multi_curve() is None
            assert space.lod1_solid() is None
            assert space.lod3_solid() is None
            assert space.lod2_multi_surface() is None

    def test_road_shape_traffic_areas(self, road_shape: CityModel) -> None:
        areas = [TrafficArea.try_from(only_boundary(s)) for s in self.traffic_spaces(road_shape)]
        assert ids(areas) == [
            "UUID_8625bf6f-57cb-3ddf-8fd1-6674b756a2e2",
            "UUID_dc110e80-dadc-3c87-b864-2854cc0cb39a",
        ]
        for area in areas:
            assert first_name(area) == "Lane"
            assert area.class_() is None
            assert [f.value() for f in area.functions()] == ["1"]
            assert [u.value() for u in area.usages()] == ["2"]
            assert area.surface_material() is None
            assert area.lod0_multi_curve() is None
            assert area.lod0_multi_surface() is None
            assert area.lod1_multi_surface() is None
            assert area.lod3_multi_surface() is None
            assert area.relative_to_terrain() is None
            assert len(list(area.lod2_multi_surface().object().surface_member())) == 1
        assert [a.lod2_multi_surface().object().area_3d() for a in areas] == close(
            [160.79800993793438, 121.34249049694012]
        )

    def test_road_shape_auxiliary_traffic(self, road_shape: CityModel) -> None:
        spaces = objects(self.section(road_shape).auxiliary_traffic_spaces())
        for space in spaces:
            assert space.granularity() == GranularityValue.Lane
            assert space.class_() is None
            assert list(space.functions()) == []
            assert list(space.usages()) == []
            assert space.space_type() == SpaceType.Open
            assert space.lod2_solid().object().volume_3d() == close(100.0)
            assert space.lod2_multi_curve().object().length_3d() == close(40.0)
        areas = [AuxiliaryTrafficArea.try_from(only_boundary(s)) for s in spaces]
        assert ids(areas) == [
            "UUID_4890681a-e9fa-365e-a676-f89afb453f9b",
            "UUID_d3c71d48-5222-355e-8037-9677aee30d7e",
        ]
        for area in areas:
            assert first_name(area) == "Lane"
            assert area.class_() is None
            assert list(area.functions()) == []
            assert list(area.usages()) == []
            assert area.surface_material() is None
            assert area.lod2_multi_surface().object().area_3d() == close(40.0)


class TestJunction:
    @staticmethod
    def traffic_spaces(city_model: CityModel) -> list[TrafficSpace]:
        return [s for f in city_model.iter_features() if (s := TrafficSpace.try_from(f)) is not None]

    def test_junction_city_model(self, junction: CityModel) -> None:
        assert junction.city_objects_len() == 1
        T = FeatureType
        assert [f.feature_type() for f in junction.iter_features()] == [
            T.CityModel,
            T.Road,
            T.Section,
            T.TrafficSpace,
            T.TrafficArea,
            T.TrafficSpace,
            T.TrafficArea,
            T.Marking,
            T.Marking,
            T.Marking,
            T.Marking,
            T.Section,
            T.TrafficSpace,
            T.TrafficArea,
            T.Section,
            T.TrafficSpace,
            T.TrafficArea,
            T.Intersection,
            T.TrafficSpace,
            T.TrafficArea,
            T.TrafficSpace,
            T.TrafficArea,
            T.TrafficSpace,
            T.TrafficArea,
        ]
        assert len(list(junction.iter_city_objects())) == 23
        envelope = junction.bounded_by().envelope()
        assert corner(envelope.lower_corner()) == close((-52.66282419815818, -37.4146115571896, 0.0))
        assert corner(envelope.upper_corner()) == close((34.10760429351533, 6.338805461729647, 0.0))

    def test_junction_road(self, junction: CityModel) -> None:
        r = road(junction)
        assert r.feature_id().as_str() == "UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f"
        sections = objects(r.sections())
        assert ids(sections) == [
            "UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29",
            "UUID_ef20f165-2564-373a-a5f8-98fd15f1ae69",
            "UUID_4799566b-daf4-3135-aa9d-ec1b34a9167d",
        ]
        assert [len(list(s.traffic_spaces())) for s in sections] == [2, 1, 1]
        assert [len(list(s.markings())) for s in sections] == [4, 0, 0]
        assert all(list(s.auxiliary_traffic_spaces()) == [] for s in sections)
        [intersection] = objects(r.intersections())
        assert intersection.feature_id().as_str() == "UUID_47b7678d-e8b1-36ca-90b6-5b86cc859571"
        assert intersection.class_() is None
        assert ids(objects(intersection.traffic_spaces())) == SPACES[4:]

    def test_junction_traffic_spaces(self, junction: CityModel) -> None:
        spaces = self.traffic_spaces(junction)
        assert ids(spaces) == SPACES
        assert [s.traffic_direction() for s in spaces] == [TrafficDirectionValue.Backwards] + [
            TrafficDirectionValue.Forwards
        ] * 6
        assert all(s.lod2_solid() is None for s in spaces)
        curves = [line_string(s.lod2_multi_curve().object()) for s in spaces]
        assert [points for points, _ in curves] == [9, 9, 5, 6, 7, 8, 7]
        assert [length for _, length in curves] == close(
            [
                36.74683751297985,
                36.74683751297985,
                20.0,
                21.746217945006258,
                26.761532846607814,
                30.210435770102656,
                30.0,
            ]
        )

    def test_junction_traffic_areas(self, junction: CityModel) -> None:
        surfaces = [
            a.lod2_multi_surface().object() for f in junction.iter_features() if (a := TrafficArea.try_from(f))
        ]
        assert [len(list(s.surface_member())) for s in surfaces] == [8, 8, 4, 5, 6, 7, 6]
        assert [s.area_3d() for s in surfaces] == close(
            [
                112.81279116484816,
                112.81279116484816,
                61.4,
                66.76088909116919,
                81.22157625123039,
                92.69041581703632,
                92.1,
            ]
        )

    def test_junction_traffic_space_links(self, junction: CityModel) -> None:
        s0, s1, s2, s3, s4, s5, s6 = SPACES
        links = [(local_ids(s.predecessors()), local_ids(s.successors())) for s in self.traffic_spaces(junction)]
        assert links == [
            ([], []),
            ([], [s6]),
            ([s4, s5], []),
            ([], [s4]),
            ([s3], [s2]),
            (["UUID_d7d4aa5a-88c9-328d-9151-a6c043e57d7f"], [s0]),
            ([s1], [s2]),
        ]

    def test_junction_markings(self, junction: CityModel) -> None:
        section = objects(road(junction).sections())[0]
        markings = objects(section.markings())
        for marking in markings:
            assert first_name(marking) == "RoadMarking"
            assert marking.class_() is None
            assert marking.lod0_multi_surface() is None
            assert marking.lod3_multi_surface() is None
            assert len(list(marking.lod2_multi_surface().object().surface_member())) == 1
        assert [m.lod2_multi_surface().object().area_3d() for m in markings] == close(
            [0.48, 0.48, 0.48, 0.08962050155758661]
        )
