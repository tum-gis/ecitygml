# TUM Main Entrance

Cases for the file in [`tests/fixtures/tum-main-entrance`](../../../../tests/fixtures/tum-main-entrance). Floating
point values are compared within ±1e-6 (absolute); lists are in document order; "the building" is the file's only
building (`iter_features` + `Building::try_from`).

# `TUM-Main-Entrance.gml`

## `entrance_city_model`

- `city_objects_len` (bindings) / `city_object_members_len` (Rust): `1`.
- `bounded_by` → envelope: lower corner `(689975.68, 5335962.63, 503.0)`, upper corner `(692025.893, 5338012.713, 581.62)`.
- `iter_features` (feature types): `CityModel`, `Building`, `WallSurface` ×10, `GroundSurface`, `WallSurface` ×3,
  `RoofSurface` ×2, `WallSurface` (`19`).
- `iter_city_objects`: `18`.

## `entrance_building_attributes`

| Getter | Expected |
|---|---|
| `feature_id` | `DEBY_LOD2_4959457` |
| `names` | empty |
| `class` | none |
| `functions` / `usages` | `["31001_3020"]` / empty |
| `roof_type` | `1000` |
| `storeys_above_ground` / `storeys_below_ground` | `4` / none |
| `heights` | exactly one: high reference `topOfConstruction`, low reference `lowestGroundPoint`, status `Measured`, length `19.408` `urn:adv:uom:m` |
| `creation_date` | 2025-01-02 00:00, UTC offset +01:00 |
| `bounded_by` | none |
| `occupancies`, `building_subdivisions` | empty |

## `entrance_external_reference`

`external_references`: exactly one, `target_resource` `DEBYvAAAAABTMIyA` (its `information_system` and `relation_type`
are in `entrance_external_reference_details`).

## `entrance_external_reference_details`

Suites: all except .NET (`ExternalReference::information_system` and `relation_type` aren't bound there).

The building's only external reference: `information_system`
`http://repository.gdi-de.org/schemas/adv/citygml/fdv/art.htm#_9100`, `relation_type` none.

## `entrance_generic_attributes`

`generic_attributes`, all string attributes (name, value): `DatenquelleBodenhoehe` `1100`, `DatenquelleDachhoehe`
`1000`, `DatenquelleLage` `1000`, `Gemeindeschluessel` `09162000`, `HoeheDach` `534.450`, `HoeheGrund` `515.042`,
`Methode` `2000`, `NiedrigsteTraufeDesGebaeudes` `527.312`, `Grundrissaktualitaet` `2025-02-17`,
`Geometrietyp2DReferenz` `3000`.

## `entrance_boundaries`

- `boundaries` (feature types): `WallSurface` ×10, `GroundSurface`, `WallSurface` ×3, `RoofSurface` ×2,
  `WallSurface`; all inline, each with an inline `lod2_multi_surface`.
- The first wall surface: `feature_id` `DEBY_LOD2_4959457_ca1db42f-9d12-4f41-972c-c7da1614f0a8_2`, `names` empty.
- Sum of `lod2_multi_surface` → `area_3d` per type: wall surfaces `3783.3908922901974`, roof surfaces
  `1229.562255859375` (`250.233154296875`, `979.3291015625`), ground surface `1229.562255859375`.

## `entrance_wall_triangulation`

The first wall surface's `lod2_multi_surface`: `1` surface member, `area_3d` `546.6949745937537`; `triangulate` gives
`4` triangles, skips none, and the triangulated surface's `area_3d` is `546.6949742237184`.

## `entrance_solid_unresolved`

The building's `lod2_solid` is inline (`href` none), and its `volume_3d` fails: the exterior shell's `17` polygons
are only referenced by `xlink:href`. Only the failure is asserted, as in
[`lod2_solid_unresolved`](fzk-haus.md#lod2_solid_unresolved).

## `entrance_round_trip`

Writing the city model as CityGML (in memory or to a file, whichever the language offers) and reading it back gives
the same `iter_features` feature types in the same order, the building's `feature_id` `DEBY_LOD2_4959457` and the
same `feature_id`s of its boundaries.
