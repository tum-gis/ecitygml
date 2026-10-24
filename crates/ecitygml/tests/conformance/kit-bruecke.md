# KIT Brücke

Cases for the file in [`tests/fixtures/kit-bruecke`](../../../../tests/fixtures/kit-bruecke). Floating point values are
compared within ±1e-6 (absolute); lists are in document order; "the bridge" is the file's only bridge (`iter_features`
+ `Bridge::try_from`).

# `Modellbahnbruecke-LoD2-V03__v3.gml`

## `bridge_city_model`

- `city_objects_len` (bindings) / `city_object_members_len` (Rust): `1`.
- `bounded_by` → envelope: lower corner `(457644.585, 5439126.455, 109.0)`, upper corner `(457708.084, 5439157.169, 124.3)`.
- `iter_features` (feature types): `CityModel`, `Bridge`, `Appearance`, `ParameterizedTexture` ×3,
  `BridgeInstallation` ×2, `BridgeConstructiveElement` ×11 (`19`).
- `iter_city_objects`: `14`.

## `bridge_attributes`

| Getter | Expected |
|---|---|
| `feature_id` | `_Modellbahnbruecke-LoD2-V03_BD.rx3tFkxPQkL5qDXML1W7` |
| `names` | empty |
| `class` | none (`is_movable` is left out: Kotlin doesn't bind it) |
| `functions` / `usages` | empty / empty |
| `bridge_parts`, `boundaries` | empty |
| `date_of_construction`, `creation_date` | none |
| `heights`, `occupancies`, `generic_attributes`, `external_references` | empty |

## `bridge_geometry`

- `bounded_by` → envelope: lower corner `(457645.136, 5439126.692, 115.3)`, upper corner `(457707.533, 5439156.931, 116.2)`.
- `lod2_multi_surface`: inline (`href` none), `18` surface members, `area_3d` `795.4201811265907`; `triangulate`
  gives `60` triangles and skips none.
- `lod1_solid`, `lod2_solid`, `lod3_multi_surface`: none.

## `bridge_parts`

Suites: Rust (constructive elements, installations and appearances aren't bound in the FFI yet).

The bridge's `bridge_constructive_elements`: `11`, `bridge_installations`: `2`, `appearances`: `1`; the same after a
round trip (as in `bridge_round_trip`).

## `bridge_round_trip`

Writing the city model as CityGML (in memory or to a file, whichever the language offers) and reading it back gives
the same `iter_features` feature types in the same order and the bridge's `feature_id`
`_Modellbahnbruecke-LoD2-V03_BD.rx3tFkxPQkL5qDXML1W7`.
