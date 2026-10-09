"""Prints a report of every building in a CityGML file: its attributes and its boundary surfaces
with their doors and windows.

Shows how the bindings mirror the Rust data model:
- Optional values are `None` when absent, lists are iterators (possibly empty).
- Code-list values (class, function, ...) are wrappers with `value()` (and `code()`).
- Properties referencing other objects (e.g. a building's boundaries) have `object()` and `href()`;
  `object()` is `None` if the property only references an object elsewhere via `xlink:href`.
- Abstract types are converted with `try_from`, e.g. a generic attribute to a `MeasureAttribute`,
  or a boundary (via `AbstractFeatureKindRef.from_space_boundary`) to a `WallSurface`.

Usage: python examples/03_building_report.py path/to/model.gml

Output for FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml (shortened):

    Building UUID_d281adfc-4901-0f52-540b-4cc1a9325f82
      Name: AC14-FZK-Haus
      Class: 1000
      ...
      Boundaries:
        WallSurface GML_5856d7ad-5e34-498a-817b-9544bfbb1475
          DoorSurface GML_...
          WindowSurface GML_...
        ...
"""

import sys
from collections.abc import Iterable
from typing import Any

from ecitygml import (
    AbstractFeatureKindRef,
    Building,
    GmlReader,
    GroundSurface,
    MeasureAttribute,
    RoofSurface,
    WallSurface,
)


def joined(values: Iterable[Any]) -> str:
    """The `value()`s of code-list values (or codes), comma-separated; "-" if there are none."""
    return ", ".join(v.value() for v in values) or "-"


def optional(value: Any) -> str:
    return "-" if value is None else str(value)


def type_name(feature_type: Any) -> str:
    """The name of a `FeatureType`; Diplomat's Python enums have no methods, so from its repr."""
    return repr(feature_type).removeprefix("FeatureType.")


def generic_attribute_value(attribute: Any) -> str:
    """The value of a generic attribute: string, integer, double or measure (value and unit)."""
    if (string := attribute.as_string()) is not None:
        return string.value()
    if (integer := attribute.as_int()) is not None:
        return str(integer.value())
    if (double := attribute.as_double()) is not None:
        return f"{double.value():.3f}"
    if (measure := MeasureAttribute.try_from(attribute)) is not None:
        return f"{measure.value().value():.3f} {measure.value().uom()}"
    return "(not shown)"  # e.g. a generic attribute set, which holds further attributes


def print_building(building: Building) -> None:
    print(f"Building {building.feature_id().as_str()}")
    print(f"  Name: {joined(building.names())}")
    print(f"  Class: {joined([building.class_()] if building.class_() else [])}")
    print(f"  Functions: {joined(building.functions())}")
    print(f"  Usages: {joined(building.usages())}")
    print(f"  Roof type: {joined([building.roof_type()] if building.roof_type() else [])}")
    print(f"  Storeys above ground: {optional(building.storeys_above_ground())}")
    print(f"  Storeys below ground: {optional(building.storeys_below_ground())}")
    date = building.date_of_construction()
    print(f"  Date of construction: {'-' if date is None else f'{date.year():04}-{date.month():02}-{date.day():02}'}")

    print("  Heights:")
    for height in building.heights():
        length = height.length()
        print(
            f"    {length.value():.3f} {length.uom()} "
            f"({height.high_reference().value()} to {height.low_reference().value()})"
        )

    print("  Generic attributes:")
    for attribute in building.generic_attributes():
        print(f"    {attribute.name()}: {generic_attribute_value(attribute)}")

    # Each boundary property holds an `AbstractSpaceBoundaryKind` (or only an href). Wall, roof
    # and ground surfaces can have filling surfaces: doors and windows.
    print("  Boundaries:")
    for boundary_property in building.boundaries():
        boundary = boundary_property.object()
        if boundary is None:
            print(f"    (reference to {boundary_property.href().to_string()})")
            continue
        print(f"    {type_name(boundary.feature_type())} {boundary.feature_id().as_str()}")
        feature = AbstractFeatureKindRef.from_space_boundary(boundary)
        surface = WallSurface.try_from(feature) or RoofSurface.try_from(feature) or GroundSurface.try_from(feature)
        if surface is None:
            continue
        for filling_property in surface.filling_surfaces():
            if (filling := filling_property.object()) is not None:
                print(f"      {type_name(filling.feature_type())} {filling.feature_id().as_str()}")


def main() -> int:
    if len(sys.argv) != 2:
        print("usage: 03_building_report path/to/model.gml", file=sys.stderr)
        return 2
    try:
        city_model = GmlReader.from_path(sys.argv[1]).finish()
    except Exception as error:  # the bindings raise Exception(Error); str() is its message
        print(f"error: {error}", file=sys.stderr)
        return 1

    # The buildings borrow from the city model, which stays referenced in `city_model`.
    buildings = [b for f in city_model.iter_features() if (b := Building.try_from(f)) is not None]
    if not buildings:
        print("No buildings.")
    for index, building in enumerate(buildings):
        if index > 0:
            print()
        print_building(building)
    return 0


if __name__ == "__main__":
    sys.exit(main())
