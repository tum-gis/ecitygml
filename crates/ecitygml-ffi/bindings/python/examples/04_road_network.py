"""Walks the road network of a CityGML file and measures it: centre-line lengths, traffic-area
areas and the volumes of the traffic spaces.

CityGML's transportation model is a hierarchy: a road consists of sections and intersections, which
(like the road itself) hold traffic spaces and auxiliary traffic spaces (e.g. lanes and sidewalks).
Each space is bounded by traffic areas or auxiliary traffic areas, its ground surfaces. The spaces
are reached through properties (`object()`), the areas through the space's `boundaries()`, converted
with `try_from`. Geometry calculations (`length_3d`, `area_3d`, `volume_3d`) can fail, e.g. for
degenerate geometry, and then raise.

Usage: python examples/04_road_network.py path/to/model.gml

Output for ASAM-UC_RoadShape.gml (shortened):

    Road UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f
      Section UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29
        TrafficSpace UUID_ae81947d-a661-3678-a5ee-eed58b686946
          Centre line (LoD2): 40.000 m
          Volume (LoD2 solid): 720.000 m^3
          TrafficArea UUID_8625bf6f-57cb-3ddf-8fd1-6674b756a2e2: 160.798 m^2
        ...

    Total volume of traffic spaces (LoD2): 1260.000 m^3
"""

import sys
from collections.abc import Callable
from dataclasses import dataclass
from typing import Any

from ecitygml import AbstractFeatureKindRef, AuxiliaryTrafficArea, GmlReader, Road, TrafficArea, TrafficSpace


@dataclass
class Totals:
    """Counts and sums over all spaces of one kind (traffic or auxiliary traffic spaces)."""

    spaces: int = 0
    length: float = 0.0
    volume: float = 0.0
    areas: int = 0
    area: float = 0.0


def measured(geometry: Any, measure: Callable[[Any], float], unit: str) -> tuple[str, float]:
    """The measurement as text (e.g. "40.000 m") and value; "-" without geometry, and a note if the
    calculation fails (counted as 0)."""
    if geometry is None:
        return "-", 0.0
    try:
        value = measure(geometry)
    except Exception as error:  # the bindings raise Exception(Error); str() is its message
        return f"not computable ({error})", 0.0
    return f"{value:.3f} {unit}", value


def print_space(space: Any, totals: Totals, indent: str) -> None:
    is_traffic_space = isinstance(space, TrafficSpace)
    print(f"{indent}{'TrafficSpace' if is_traffic_space else 'AuxiliaryTrafficSpace'} {space.feature_id().as_str()}")
    curve = space.lod2_multi_curve()
    length_text, length = measured(curve and curve.object(), lambda c: c.length_3d(), "m")
    solid = space.lod2_solid()
    volume_text, volume = measured(solid and solid.object(), lambda s: s.volume_3d(), "m^3")
    print(f"{indent}  Centre line (LoD2): {length_text}")
    print(f"{indent}  Volume (LoD2 solid): {volume_text}")
    totals.spaces += 1
    totals.length += length
    totals.volume += volume

    # The areas are the space's boundaries of the matching type.
    area_cls = TrafficArea if is_traffic_space else AuxiliaryTrafficArea
    for boundary_property in space.boundaries():
        boundary = boundary_property.object()
        area = None if boundary is None else area_cls.try_from(AbstractFeatureKindRef.from_space_boundary(boundary))
        if area is None:
            continue
        surface = area.lod2_multi_surface()
        area_text, value = measured(surface and surface.object(), lambda s: s.area_3d(), "m^2")
        print(f"{indent}  {'TrafficArea' if is_traffic_space else 'AuxiliaryTrafficArea'} {area.feature_id().as_str()}: {area_text}")
        totals.areas += 1
        totals.area += value


def print_spaces_of(transportation_space: Any, traffic: Totals, auxiliary: Totals, indent: str) -> None:
    """The traffic and auxiliary traffic spaces of a road, section or intersection."""
    for space_property in transportation_space.traffic_spaces():
        if (space := space_property.object()) is not None:
            print_space(space, traffic, indent)
    for space_property in transportation_space.auxiliary_traffic_spaces():
        if (space := space_property.object()) is not None:
            print_space(space, auxiliary, indent)


def main() -> int:
    if len(sys.argv) != 2:
        print("usage: 04_road_network path/to/model.gml", file=sys.stderr)
        return 2
    try:
        city_model = GmlReader.from_path(sys.argv[1]).finish()
    except Exception as error:  # the bindings raise Exception(Error); str() is its message
        print(f"error: {error}", file=sys.stderr)
        return 1

    traffic, auxiliary = Totals(), Totals()
    roads = [r for f in city_model.iter_features() if (r := Road.try_from(f)) is not None]
    for road in roads:
        print(f"Road {road.feature_id().as_str()}")
        print_spaces_of(road, traffic, auxiliary, "  ")  # a road can hold spaces directly, too
        for section_property in road.sections():
            if (section := section_property.object()) is not None:
                print(f"  Section {section.feature_id().as_str()}")
                print_spaces_of(section, traffic, auxiliary, "    ")
        for intersection_property in road.intersections():
            if (intersection := intersection_property.object()) is not None:
                print(f"  Intersection {intersection.feature_id().as_str()}")
                print_spaces_of(intersection, traffic, auxiliary, "    ")

    print()
    print(f"Roads: {len(roads)}")
    for label, totals in [("Traffic spaces", traffic), ("Auxiliary traffic spaces", auxiliary)]:
        print(
            f"{label}: {totals.spaces}, centre lines {totals.length:.3f} m, "
            f"{totals.areas} areas {totals.area:.3f} m^2, volume {totals.volume:.3f} m^3"
        )
    print(f"Total volume of traffic spaces (LoD2): {traffic.volume:.3f} m^3")
    return 0


if __name__ == "__main__":
    sys.exit(main())
