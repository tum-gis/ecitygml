"""Converts a CityGML file: reads it and writes it again, e.g. compressed or indented.

Shows writing with `GmlWriter`: `from_path` creates the output file and picks the format from its
extension (`.gml`, `.gml.gz` or `.gml.zst`), `with_formatting` sets the layout (here indented by
two spaces; `Formatting.compact()` writes no line breaks at all), and `finish` writes the city
model. Reading the written file back verifies the result.

Usage: python examples/07_convert.py input.gml output.gml.gz

Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml, converted to a .gml.gz file:

    Read: 1 city object members, 8 city objects
    Wrote: gzip-compressed CityGML, indented by 2 spaces
    Read back: 1 city object members, 8 city objects
"""

import sys

from ecitygml import CityModel, Formatting, GmlReader, GmlWriter

INDENT_SIZE = 2


def summary(city_model: CityModel) -> str:
    city_objects = sum(1 for _ in city_model.iter_city_objects())
    return f"{city_model.city_objects_len()} city object members, {city_objects} city objects"


def format_name(path: str) -> str:
    """What `GmlWriter.from_path` writes for this path (it fails for other extensions)."""
    if path.endswith(".gml.gz"):
        return "gzip-compressed CityGML"
    if path.endswith(".gml.zst"):
        return "zstd-compressed CityGML"
    return "CityGML"


def main() -> int:
    if len(sys.argv) != 3:
        print("usage: 07_convert input.gml output.gml[.gz|.zst]", file=sys.stderr)
        return 2
    input_path, output_path = sys.argv[1], sys.argv[2]
    try:
        city_model = GmlReader.from_path(input_path).finish()
        print(f"Read: {summary(city_model)}")

        writer = GmlWriter.from_path(output_path)
        writer.with_formatting(Formatting.indent(ord(" "), INDENT_SIZE))
        writer.finish(city_model)
        print(f"Wrote: {format_name(output_path)}, indented by {INDENT_SIZE} spaces")

        written = GmlReader.from_path(output_path).finish()
        print(f"Read back: {summary(written)}")
    except Exception as error:  # the bindings raise Exception(Error); str() is its message
        print(f"error: {error}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
