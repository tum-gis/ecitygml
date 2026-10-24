# Synthetic

Hand-written CityGML 3.0, not real data: small files with the content no real fixture in `tests/fixtures` has (bridge
and tunnel parts, vegetation, city furniture, generic attribute sets, city object relations, implicit geometries,
geometry members that triangulate unusually, …). Prefer real data: when a real fixture with such content turns up,
its case list replaces the case here.

Every file is valid against the official CityGML 3.0 schemas: `mise run check:fixtures` validates them with xmllint
against [`../scripts/citygml-3.0.xsd`](../scripts/citygml-3.0.xsd), which imports the modules from
schemas.opengis.net. The values are made up; codes such as `1000` or `https://example.org/…` code spaces mean nothing.
The case list is [`synthetic.md`](../../../crates/ecitygml/tests/conformance/synthetic.md).

| File | Contents |
|---|---|
| `bridge.gml` | a bridge with construction date, class (with code space), functions, usage, `isMovable`, and a bridge part |
| `tunnel.gml` | a tunnel with construction date, class (with code space), functions, usage, and a tunnel part |
| `vegetation.gml` | a solitary vegetation object with all its attributes and an implicit geometry (multi surface), one with a point implicit geometry from a library object, and a plant cover |
| `city-furniture.gml` | a city furniture with class (with code space), function, usage and an LoD2 multi surface |
| `building.gml` | a building with relative-to-water, a city object relation, a generic attribute set, a roof with a window, an href-only boundary, a terrain intersection curve, a demolition date and an occupancy; a second, empty building as the relation's target |
| `transportation.gml` | a section with traffic direction and occupancy; its traffic space with an LoD0 point and a multi curve of a line string, a linear ring and an unresolved reference |
| `geometry.gml` | a multi surface of a square, a degenerate (collinear) polygon and a triangulated surface |

Written by hand for this repository; no terms of use apply beyond the repository's.
