# Invalid

The one exception to real data in `tests/fixtures`: small hand-written files the reader must reject, for the
[API suite](../../../crates/ecitygml/tests/api/README.md). They are not CityGML, so no conformance case list belongs to
this folder.

| File | Contents | Made with |
|---|---|---|
| `unclosed-tag.gml` | the text `<no-citygml` (no line break): an unclosed tag | `printf '<no-citygml' > unclosed-tag.gml` |
