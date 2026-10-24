# FZK Haus CityGML 3.0

Cases for the files in [`tests/fixtures/fzk-haus-citygml-3.0`](../../../../tests/fixtures/fzk-haus-citygml-3.0), grouped
per file. Floating point values are compared within ±1e-6 (absolute); lists are in document order; "the building" is
the file's only building (`iter_features` + `Building::try_from`), "the storeys" its two storeys (`iter_features` +
`Storey::try_from`). The storeys and their boundary surfaces have no `gml:id`; the `feature_id`s the reader generates
for them are not part of any case. Feature type counts are over `iter_features`, which includes the city model.

# `01-FZK-Haus-LoD2-Tex-Storey-Construction-CG30-V01.gml`

## `construction_city_model`

- `city_objects_len` (bindings) / `city_object_members_len` (Rust): `1`.
- `bounded_by` → envelope: lower corner `(458899.5, 5438784.5, 113.5)`, upper corner `(458912.5, 5438795.5, 120.017691)`.
- `iter_features` (feature types): `CityModel`, `Building`, `Storey`, `BuildingConstructiveElement` ×5, `Storey`,
  `BuildingConstructiveElement` ×6, `Appearance`, `ParameterizedTexture` ×5, `X3DMaterial` ×5 (`26`).
- `iter_city_objects`: `14`.

## `construction_building`

| Getter | Expected |
|---|---|
| `feature_id` | `_FZK-Haus-Storey-Construction_BD.DX9Xm6VLbbyLGAxG2v86` |
| `names` | `["KIT FZK-Haus"]` |
| `class` | none |
| `functions` / `usages` | `["31001_1000"]` / empty |
| `roof_type` | `3100` |
| `storeys_above_ground` / `storeys_below_ground` | none / none |
| `heights` | exactly one: high reference `highestRoofEdge`, low reference `lowestGroundPoint`, status `Measured`, length `6.52` `urn:adv:uom:m` |
| `occupancies` | exactly one: `number_of_occupants` `2` |
| `boundaries`, `generic_attributes` | empty |
| `lod2_solid`, `lod2_multi_surface` | none |

## `construction_storeys`

- `building_subdivisions`: exactly two, inline (`href` none), both of feature type `Storey`.
- The storeys: first name `Ground Floor`, `Second Floor`; `class` `Entrance Floor`, `non Entrance Floor`; each
  `functions` and `usages` empty, `boundaries` empty, `lod2_solid` none.

## `construction_storey_details`

Suites: Rust (constructive elements, sort keys and elevations of storeys aren't bound in the FFI yet).

- The storeys' `building_constructive_elements`: `5`, `6`; `sort_key`: `1.0`, `2.0`; `elevations`: exactly one each,
  reference `lowestGroundPoint`, value `[0.0]` and `[2.7]`.
- The building's own `elevations` (`con:elevation`): empty.
- The same after a round trip (as in `construction_round_trip`).

## `construction_round_trip`

Writing the city model as CityGML (in memory or to a file, whichever the language offers) and reading it back gives
the same `iter_features` feature types in the same order and the building's `feature_id`
`_FZK-Haus-Storey-Construction_BD.DX9Xm6VLbbyLGAxG2v86`.

# `04-FZK-Haus-LoD2-Tex-Storey-CG30-V01-InteriorSurface.gml`

## `interior_city_model`

- `city_objects_len` / `city_object_members_len`: `1`.
- `bounded_by` → envelope: lower corner `(458900.0, 5438785.0, 113.5)`, upper corner `(458912.0, 5438795.0, 120.017691)`.
- `iter_features`: `77`; per feature type: `CityModel` `1`, `Building` `1`, `Storey` `2`, `GroundSurface` `1`,
  `WallSurface` `8`, `RoofSurface` `2`, `BuildingRoom` `7`, `InteriorWallSurface` `27`, `CeilingSurface` `8`,
  `FloorSurface` `7`, `ClosureSurface` `6`, `Appearance` `1`, `ParameterizedTexture` `5`, `X3DMaterial` `1`.
- `iter_city_objects`: `69`.

## `interior_building`

| Getter | Expected |
|---|---|
| `feature_id` | `KIT-Test-Building-01` |
| `names` | `["KIT Test Building FZK-Haus for CityGML 3.0"]` |
| `class`, `roof_type` | none |
| `functions` / `usages` | empty / empty |
| `heights` | exactly one: `highestRoofEdge`, `lowestGroundPoint`, `Measured`, `6.52` `urn:adv:uom:m` |
| `occupancies` | exactly one: `number_of_occupants` `2` |
| `generic_attributes` | exactly one: `@cityeditor:layer` (string `LoD2-Ausgeblendet`) |
| `boundaries` | empty |

## `interior_solid_unresolved`

- The building's `lod2_solid` is inline (`href` none), and its `volume_3d` fails: the exterior shell's `11` polygons
  are only referenced by `xlink:href`. Only the failure is asserted, as in
  [`lod2_solid_unresolved`](fzk-haus.md#lod2_solid_unresolved).

## `interior_storey_boundaries`

The storeys' `boundaries` (feature type, first name, `lod2_multi_surface` → `area_3d`), all inline:

- Ground floor: (`GroundSurface`, `Ground`, `120.0`), (`WallSurface`, `Ground Floor / Wall East`, `29.0`),
  (`WallSurface`, `Ground Floor / Wall South`, `34.80000000447035`), (`WallSurface`, `Ground Floor / Wall West`,
  `29.0`), (`WallSurface`, `Ground Floor / Wall North`, `34.80000000447035`).
- Second floor: (`RoofSurface`, `Second Floor / Roof South`, `69.28203022609509`), (`RoofSurface`,
  `Second Floor / Roof North`, `69.28203022609509`), (`WallSurface`, `Second Floor / Wall South`,
  `8.771279998123646`), (`WallSurface`, `Second Floor / Wall West`, `21.743155002593994`), (`WallSurface`,
  `Second Floor / Wall East`, `21.743155002593994`), (`WallSurface`, `Second Floor / Wall North`, `8.771279998123646`).
- The storeys' first names: `Ground Floor`, `Second Floor`; `class` none.

## `interior_storey_rooms`

Suites: Rust (building rooms aren't bound in the FFI yet).

The storeys' `building_rooms`: `6`, `1`; the same after a round trip (as in `interior_round_trip`).

## `interior_round_trip`

Writing and reading back (as in `construction_round_trip`) gives the same `iter_features` feature types in the same
order and the building's `feature_id` `KIT-Test-Building-01`.

# `04-FZK-Haus-LoD2-Tex-Storey-Construction-CG30-V01-Window-Interior.gml`

## `window_city_model`

- `city_objects_len` / `city_object_members_len`: `1`.
- `bounded_by` → envelope: lower corner `(458899.5, 5438784.5, 113.5)`, upper corner `(458912.5, 5438795.5, 120.017691)`.
- `iter_features`: `54`; per feature type: `CityModel` `1`, `Building` `1`, `Storey` `2`,
  `BuildingConstructiveElement` `18`, `Door` `5`, `Window` `11`, `Appearance` `2`, `ParameterizedTexture` `5`,
  `X3DMaterial` `9`.
- `iter_city_objects`: `37`.

## `window_building`

- `feature_id`: `_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz`; `names` `["KIT FZK-Haus"]`;
  `functions` `["31001_1000"]`; `roof_type` `3100`; `boundaries` empty.
- The storeys: first name `Ground Floor`, `Second Floor`; `class` `Entrance Floor`, `non Entrance Floor`.

## `window_round_trip`

Writing and reading back gives the same `iter_features` feature types in the same order and the building's
`feature_id` `_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz`.

# `06-FZK-Haus-LoD2-Tex-Storey-CG30-V01-PointCloud-thinned.gml`

## `point_cloud_city_model`

- `city_objects_len` / `city_object_members_len`: `1`.
- `bounded_by` → envelope: lower corner `(458900.0, 5438785.0, 113.5)`, upper corner `(458912.0, 5438795.0, 120.017691)`.
- `iter_features` (feature types): `CityModel`, `Building`, `Storey`, `GroundSurface`, `WallSurface` ×4, `Storey`,
  `RoofSurface` ×2, `WallSurface` ×4 (`15`).

## `point_cloud_storey_boundaries`

- The building: `feature_id` `KIT-Test-Building-01`, `boundaries` empty.
- The storeys' `boundaries` (feature type, first name), all inline and without a `lod2_multi_surface` (the surfaces
  carry point clouds instead):
  - Ground floor: (`GroundSurface`, ` Ground Floor / GroundSurface`, with the leading space of the file),
    (`WallSurface`, `Ground Floor / Wall East`), (`WallSurface`, `Ground Floor / Wall South`), (`WallSurface`,
    `Ground Floor / Wall West`), (`WallSurface`, `Ground Floor / Wall North`).
  - Second floor: (`RoofSurface`, `Second Floor / Roof North`), (`RoofSurface`, `Second Floor / Roof South`),
    (`WallSurface`, `Second Floor / Wall South`), (`WallSurface`, `Second Floor / Wall West`), (`WallSurface`,
    `Second Floor / Wall East`), (`WallSurface`, `Second Floor / Wall North`).

## `point_cloud_surfaces`

Suites: Rust (point clouds and qualified areas aren't bound in the FFI yet).

The storeys' boundaries, in the order of `point_cloud_storey_boundaries`: each has exactly one qualified area (`areas`)
in `m2` of type `gross` and a point cloud (`point_cloud` → `points` → point members); (area, points): (`120.0`, `40`),
(`29.0`, `20`), (`34.8`, `20`), (`29.0`, `20`), (`34.8`, `20`), (`69.28`, `30`), (`69.28`, `30`), (`8.77`, `10`),
(`21.74`, `21`), (`21.74`, `20`), (`8.77`, `10`). The same after a round trip.

## `point_cloud_round_trip`

Writing and reading back gives the same `iter_features` feature types in the same order and the building's
`feature_id` `KIT-Test-Building-01`.
