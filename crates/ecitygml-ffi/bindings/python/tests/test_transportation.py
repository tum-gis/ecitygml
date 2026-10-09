"""Transportation types: Road, Section, Intersection, TrafficSpace, TrafficArea,
AuxiliaryTrafficSpace, AuxiliaryTrafficArea and MultiCurve.

Ported from the former PyO3 bindings' `test_transportation.py`. Not ported (not in the Diplomat
bindings): `repr` of features and enums. Concrete classes have no `feature_type()` (only feature
refs and kinds do), so feature-type tests check the features that `try_from` accepts.
"""

from typing import Any

import pytest

from conftest import (
    ASAM_ROAD,
    boundaries_of,
    curve_points,
    features_of,
    objects,
    polygons,
    read_injected,
    unwrap,
)
from ecitygml import (
    AuxiliaryTrafficArea,
    AuxiliaryTrafficSpace,
    DirectPosition,
    Envelope,
    FeatureType,
    Intersection,
    MultiCurve,
    MultiSurface,
    Road,
    Section,
    TrafficArea,
    TrafficDirectionValue,
    TrafficSpace,
)


def accepts_only(model: Any, cls: Any, feature_type: FeatureType) -> bool:
    """Whether `cls.try_from` accepts features of `feature_type` only (and at least one).

    Diplomat's Python enums compare with `==` but don't hash, so no sets here.
    """
    types = [f.feature_type() for f in model.iter_features() if cls.try_from(f) is not None]
    return len(types) > 0 and all(t == feature_type for t in types)


class TestRoad:
    def test_type(self, asam_junction_road: Road) -> None:
        assert isinstance(asam_junction_road, Road)

    def test_id(self, asam_junction_road: Road) -> None:
        assert asam_junction_road.id().as_str() == "UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f"

    def test_feature_type(self, asam_junction_model: Any) -> None:
        assert accepts_only(asam_junction_model, Road, FeatureType.Road)

    def test_section_count(self, asam_junction_road: Road) -> None:
        assert len(objects(asam_junction_road.sections())) == 3

    def test_intersection_count(self, asam_junction_road: Road) -> None:
        assert len(objects(asam_junction_road.intersections())) == 1

    def test_section_type(self, asam_junction_road: Road) -> None:
        assert isinstance(objects(asam_junction_road.sections())[0], Section)

    def test_intersection_type(self, asam_junction_road: Road) -> None:
        assert isinstance(objects(asam_junction_road.intersections())[0], Intersection)


class TestSection:
    def test_id(self, asam_section: Section) -> None:
        assert asam_section.id().as_str() == "UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29"

    def test_feature_type(self, asam_junction_model: Any) -> None:
        assert accepts_only(asam_junction_model, Section, FeatureType.Section)

    def test_traffic_space_count(self, asam_section: Section) -> None:
        assert len(objects(asam_section.traffic_spaces())) == 2

    def test_traffic_space_type(self, asam_section: Section) -> None:
        assert isinstance(objects(asam_section.traffic_spaces())[0], TrafficSpace)

    def test_auxiliary_traffic_space_absent(self, asam_section: Section) -> None:
        assert list(asam_section.auxiliary_traffic_spaces()) == []

    def test_lod0_multi_curve_absent(self, asam_section: Section) -> None:
        assert asam_section.lod0_multi_curve() is None

    def test_lod1_solid_absent(self, asam_section: Section) -> None:
        assert asam_section.lod1_solid() is None


class TestIntersection:
    def test_id_non_empty(self, asam_junction_road: Road) -> None:
        assert objects(asam_junction_road.intersections())[0].id().as_str() != ""

    def test_feature_type(self, asam_junction_model: Any) -> None:
        assert accepts_only(asam_junction_model, Intersection, FeatureType.Intersection)

    def test_traffic_space_count(self, asam_junction_road: Road) -> None:
        intersection = objects(asam_junction_road.intersections())[0]
        assert len(objects(intersection.traffic_spaces())) == 3

    def test_traffic_space_type(self, asam_junction_road: Road) -> None:
        intersection = objects(asam_junction_road.intersections())[0]
        assert isinstance(objects(intersection.traffic_spaces())[0], TrafficSpace)


class TestTrafficSpace:
    def test_id_non_empty(self, asam_section: Section) -> None:
        assert objects(asam_section.traffic_spaces())[0].id().as_str() != ""

    def test_feature_type(self, asam_junction_model: Any) -> None:
        assert accepts_only(asam_junction_model, TrafficSpace, FeatureType.TrafficSpace)

    def test_lod2_multi_curve_present(self, asam_section: Section) -> None:
        space = objects(asam_section.traffic_spaces())[0]
        assert isinstance(unwrap(space.lod2_multi_curve()), MultiCurve)

    def test_lod2_multi_surface_absent(self, asam_section: Section) -> None:
        assert objects(asam_section.traffic_spaces())[0].lod2_multi_surface() is None

    def test_traffic_area_count(self, asam_section: Section) -> None:
        space = objects(asam_section.traffic_spaces())[0]
        assert len(boundaries_of(space, TrafficArea)) == 1

    def test_traffic_area_type(self, asam_section: Section) -> None:
        space = objects(asam_section.traffic_spaces())[0]
        assert isinstance(boundaries_of(space, TrafficArea)[0], TrafficArea)


def first_traffic_area(section: Section) -> TrafficArea:
    return boundaries_of(objects(section.traffic_spaces())[0], TrafficArea)[0]


class TestTrafficArea:
    def test_id(self, asam_section: Section) -> None:
        area = first_traffic_area(asam_section)
        assert area.id().as_str() == "UUID_8625bf6f-57cb-3ddf-8fd1-6674b756a2e2"

    def test_feature_type(self, asam_junction_model: Any) -> None:
        assert accepts_only(asam_junction_model, TrafficArea, FeatureType.TrafficArea)

    def test_lod2_multi_surface_present(self, asam_section: Section) -> None:
        assert isinstance(unwrap(first_traffic_area(asam_section).lod2_multi_surface()), MultiSurface)

    def test_lod2_multi_surface_polygon_count(self, asam_section: Section) -> None:
        assert len(polygons(unwrap(first_traffic_area(asam_section).lod2_multi_surface()))) == 8


def first_lane_curve(section: Section) -> MultiCurve:
    return unwrap(objects(section.traffic_spaces())[0].lod2_multi_curve())


class TestMultiCurve:
    def test_curves_returns_list(self, asam_section: Section) -> None:
        assert isinstance(curve_points(first_lane_curve(asam_section)), list)

    def test_curve_count(self, asam_section: Section) -> None:
        assert len(curve_points(first_lane_curve(asam_section))) == 1

    def test_curve_points_are_direct_positions(self, asam_section: Section) -> None:
        for point in curve_points(first_lane_curve(asam_section))[0]:
            assert isinstance(point, DirectPosition)

    def test_curve_point_count(self, asam_section: Section) -> None:
        assert len(curve_points(first_lane_curve(asam_section))[0]) == 9

    def test_compute_envelope_returns_envelope(self, asam_section: Section) -> None:
        assert isinstance(first_lane_curve(asam_section).compute_envelope(), Envelope)


class TestAuxiliaryTrafficSpace:
    def test_count(self, asam_road_section: Section) -> None:
        assert len(objects(asam_road_section.auxiliary_traffic_spaces())) == 2

    def test_type(self, asam_road_section: Section) -> None:
        space = objects(asam_road_section.auxiliary_traffic_spaces())[0]
        assert isinstance(space, AuxiliaryTrafficSpace)

    def test_feature_type(self, asam_road_model: Any) -> None:
        assert accepts_only(asam_road_model, AuxiliaryTrafficSpace, FeatureType.AuxiliaryTrafficSpace)

    def test_id_non_empty(self, asam_road_section: Section) -> None:
        assert objects(asam_road_section.auxiliary_traffic_spaces())[0].id().as_str() != ""

    def test_auxiliary_traffic_area_returns_list(self, asam_road_section: Section) -> None:
        space = objects(asam_road_section.auxiliary_traffic_spaces())[0]
        assert isinstance(boundaries_of(space, AuxiliaryTrafficArea), list)


class TestAuxiliaryTrafficArea:
    def test_type(self, asam_road_section: Section) -> None:
        for space in objects(asam_road_section.auxiliary_traffic_spaces()):
            for area in boundaries_of(space, AuxiliaryTrafficArea):
                assert isinstance(area, AuxiliaryTrafficArea)

    def test_feature_type(self, asam_road_model: Any) -> None:
        assert accepts_only(asam_road_model, AuxiliaryTrafficArea, FeatureType.AuxiliaryTrafficArea)

    def test_id_non_empty(self, asam_road_section: Section) -> None:
        for space in objects(asam_road_section.auxiliary_traffic_spaces()):
            for area in boundaries_of(space, AuxiliaryTrafficArea):
                assert area.id().as_str() != ""


# The fixtures carry no transportation-space-level traffic direction or occupancy; they are
# injected into the first section of a copy of the ASAM road shape file, before its traffic
# spaces as in the CityGML 3.0 schema (AbstractTransportationSpaceType).
SECTION_START = '<tran:Section gml:id="UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29">'
SECTION_PROPERTIES = """
          <tran:trafficDirection>both</tran:trafficDirection>
          <tran:occupancy>
            <Occupancy>
              <numberOfOccupants>120</numberOfOccupants>
              <interval>peakHour</interval>
            </Occupancy>
          </tran:occupancy>"""


@pytest.fixture(scope="module")
def extended_road_model(tmp_path_factory: pytest.TempPathFactory) -> Any:
    tmp_path = tmp_path_factory.mktemp("transportation")
    return read_injected(tmp_path, ASAM_ROAD, SECTION_START, SECTION_START + SECTION_PROPERTIES)


@pytest.fixture(scope="module")
def extended_section(extended_road_model: Any) -> Section:
    return objects(features_of(extended_road_model, Road)[0].sections())[0]


class TestAbstractTransportationSpace:
    def test_traffic_direction(self, extended_section: Section) -> None:
        assert extended_section.traffic_direction() == TrafficDirectionValue.Both

    def test_traffic_direction_absent(self, asam_road_shape_road: Road) -> None:
        assert asam_road_shape_road.traffic_direction() is None
        assert objects(asam_road_shape_road.sections())[0].traffic_direction() is None

    def test_occupancies(self, extended_section: Section) -> None:
        occupancies = [(o.number_of_occupants(), o.interval().value()) for o in extended_section.occupancies()]
        assert occupancies == [(120, "peakHour")]

    def test_injection_keeps_traffic_spaces(self, extended_section: Section) -> None:
        assert len(objects(extended_section.traffic_spaces())) == 2
        assert len(objects(extended_section.auxiliary_traffic_spaces())) == 2

    def test_road_has_traffic_space_getters(self, asam_road_shape_road: Road) -> None:
        # Roads may hold traffic spaces directly; the ASAM fixtures hold them in sections.
        assert list(asam_road_shape_road.traffic_spaces()) == []
        assert list(asam_road_shape_road.auxiliary_traffic_spaces()) == []
