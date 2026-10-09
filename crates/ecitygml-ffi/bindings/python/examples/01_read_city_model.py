"""Reads a CityGML file and prints an overview of the city model.

This is the starting point for every program using ecitygml: `GmlReader` reads a file (plain,
`.gml.gz` or `.gml.zst`) into a `CityModel`, which owns all features. Errors, e.g. a missing file
or invalid XML, are raised as exceptions carrying the ecitygml `Error`.

Usage: python examples/01_read_city_model.py path/to/model.gml

Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml:

    City object members: 1
    City objects (at all depths): 8
    Envelope:
      lower corner: 457842.000, 5439083.000, 111.800
      upper corner: 457854.000, 5439093.000, 118.318
      size: 12.000 x 10.000 x 6.518
"""

import sys

from ecitygml import GmlReader


def main() -> int:
    if len(sys.argv) != 2:
        print("usage: 01_read_city_model path/to/model.gml", file=sys.stderr)
        return 2

    # `from_path` opens the file and picks the format from its extension; `finish` parses it.
    try:
        city_model = GmlReader.from_path(sys.argv[1]).finish()
    except Exception as error:  # the bindings raise Exception(Error); str() is its message
        print(f"error: {error}", file=sys.stderr)
        return 1

    # `cityObjectMember`s are the top-level city objects (e.g. buildings); their boundary surfaces,
    # doors and windows are city objects too, which `iter_city_objects()` visits as well.
    print(f"City object members: {city_model.city_objects_len()}")
    print(f"City objects (at all depths): {sum(1 for _ in city_model.iter_city_objects())}")

    # `bounded_by()` is the `gml:boundedBy` property, a bounding shape holding an envelope; both
    # are optional, as in the file.
    bounding_shape = city_model.bounded_by()
    envelope = None if bounding_shape is None else bounding_shape.envelope()
    if envelope is None:
        print("Envelope: none")
        return 0
    lower, upper = envelope.lower_corner(), envelope.upper_corner()
    print("Envelope:")
    print(f"  lower corner: {lower.x():.3f}, {lower.y():.3f}, {lower.z():.3f}")
    print(f"  upper corner: {upper.x():.3f}, {upper.y():.3f}, {upper.z():.3f}")
    print(f"  size: {envelope.size_x():.3f} x {envelope.size_y():.3f} x {envelope.size_z():.3f}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
