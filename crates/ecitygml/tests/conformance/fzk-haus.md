# FZK Haus

Cases for the files in [`tests/fixtures/fzk-haus`](../../../../tests/fixtures/fzk-haus), grouped per file. Floating point values
are compared within ±1e-6 (absolute); lists are in document order; "the building" is the file's only building
(`iter_features` + `Building::try_from`).

# `FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml`

## `lod1_city_model`

- `city_objects_len` (bindings) / `city_object_members_len` (Rust): `1`.
- `bounded_by` → envelope: lower corner `(457842.0, 5439083.0, 111.8)`, upper corner `(457854.0, 5439093.0, 118.317669)`.

## `lod1_building_attributes`

| Getter | Expected |
|---|---|
| `feature_id` | `UUID_d281adfc-4901-0f52-540b-4cc1a9325f82` |
| `names` | `["AC14-FZK-Haus"]` |
| `class` | `1000` |
| `functions` / `usages` | `["1000"]` / `["1000"]` |
| `roof_type` | `1030` |
| `storeys_above_ground` / `storeys_below_ground` | `2` / `0` |
| `date_of_construction` / `date_of_demolition` | 2020-01-01 / none |
| `heights` | exactly one: high reference `topOfConstruction`, low reference `lowestGroundPoint`, status `Measured`, length `6.52` `m` |
| `occupancies` / `building_parts` | empty / empty |

## `lod1_solid`

- `lod1_solid` → `volume_3d`: `782.1228`.
- `lod1_solid` → `triangulate`: `12` triangles, none skipped.
- `boundaries`: empty.

## `lod1_envelope_measures`

The city model's envelope (`bounded_by` → `envelope`):

- `size_x` / `size_y` / `size_z`: `12.0` / `10.0` / `6.517669`; `center`: `(457848.0, 5439088.0, 115.0588345)`;
  `volume`: `782.12028`.
- `contains`: its lower and upper corner and `(457848.0, 5439088.0, 115.0)`; not `(457848.0, 5439088.0, 118.4)` and
  not `(457841.9, 5439088.0, 115.0)`.
- The city model's `creation_date`: none.

## `lod1_building_details`

- The features of type `Building`: exactly one; its `id` (`gml:id`) is `UUID_d281adfc-4901-0f52-540b-4cc1a9325f82`.
- The building's own `bounded_by` → envelope: lower corner `(457842.0, 5439083.0, 111.8)`, upper corner
  `(457854.0, 5439093.0, 118.31769)` (stored in the file, not the city model's).
- `lod2_solid`, `lod0_multi_surface`: none.

## `lod1_solid_structure`

The building's `lod1_solid`:

- `interior` shells: none; `points`: `24`.
- `exterior` shell: `volume_3d` `782.1228`; `6` members, all inline polygons (`href` none) without interior rings, each
  exterior a linear ring with `4` points (the repeated closing position is dropped) and an `area_3d` above `0`.
- The first polygon's exterior ring: first point `(457842.0, 5439083.0, 111.8)`, `length_3d` `44.0`, `area_3d` `120.0`.

## `lod1_solid_triangulation`

The building's `lod1_solid` → `triangulate`:

- `skipped`: none; the triangulated surface: `area_3d` `526.77836`, `points` `36`.
- Its first triangle: `a` has z `111.8`, `area` `60.0`.
- The exterior shell triangulates to `12` triangles, its first polygon to `2`.

## `lod1_apply_scale`

`apply_scale(2.0, 3.0, 0.5)` on the city model: its envelope's `size_x` / `size_y` / `size_z` become `24.0` / `30.0` /
`3.2588345`.

# `FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml`

## `lod2_boundary_surfaces`

- `boundaries` (feature types): `WallSurface`, `WallSurface`, `WallSurface`, `RoofSurface`, `WallSurface`, `RoofSurface`,
  `GroundSurface`.
- First name of the wall surfaces: `Outer Wall 1 (West)`, `Outer Wall 2 (South)`, `Outer Wall 3 (East)`,
  `Outer Wall 4 (North)`; of the roof surfaces: `Roof 1 (North)`, `Roof 2 (South)`; of the ground surface:
  `Base Surface`.

## `lod2_surface_areas`

Sum of `lod2_multi_surface` → `area_3d` per type: wall surfaces `188.62887820601463`, roof surfaces
`138.56406460961398`, ground surface `120.0`.

## `lod2_generic_attributes`

- `generic_attributes`: `GrossPlannedArea` (measure `120.0` `m2`), `ConstructionMethod` (string `New Building`),
  `IsLandmarked` (string `NO`).
- `external_references`: empty.

## `lod2_solid_unresolved`

- `lod2_solid` → `volume_3d` fails (an error, no value): the solid's polygons are only referenced by `xlink:href`.
  Only the failure is asserted, as the error differs: Rust skips the unresolved members and fails with
  `egml::Error::TooFewElements`; the bridge API checks the members first and fails with
  `ErrorKind::UnresolvedReference`.

## `lod2_building_details`

The building:

- `relative_to_terrain`: `EntirelyAboveTerrain`; `relative_to_water`: none.
- `creation_date`: 2017-01-23 00:00 at offset `3600` s (timestamp `1485126000`); `termination_date`, `valid_from`,
  `valid_to`: none.
- `class` `1000`, `functions` `["1000"]`, `usages` `["1000"]`, `roof_type` `1030`, storeys `2` / `0`,
  `date_of_construction` 2020-01-01, `date_of_demolition` none, exactly one height (`topOfConstruction`,
  `lowestGroundPoint`, `Measured`, `6.52` `m`).
- `occupancies`, `related_to`: empty; `lod1_solid`, `bounded_by`: none.
- `lod1_terrain_intersection_curve` … `lod3_terrain_intersection_curve`, `lod1_implicit_representation` …
  `lod3_implicit_representation`: none.

## `lod2_boundary_ids`

All `boundaries` are inline (`href` none); their `feature_id`s: `GML_5856d7ad-5e34-498a-817b-9544bfbb1475`,
`GML_d38cf762-c29d-4491-88c9-bdc89e141978`, `GML_8e5db638-e46a-4739-a98a-2fc2d39c9069`,
`GML_875d470b-32b4-4985-a4c8-0f02caa342a2`, `GML_0f30f604-e70d-4dfe-ba35-853bc69609cc`,
`GML_eeb6796a-e261-4d3b-a6f2-475940cca80a`, `GML_257a8dde-8194-4ca3-b581-abd591dcd6a3`.

## `lod2_wall_surface`

The first wall surface (`Outer Wall 1 (West)`):

- `id` (`gml:id`): `GML_5856d7ad-5e34-498a-817b-9544bfbb1475`.
- `lod0_multi_curve`, `lod0_multi_surface`, `lod1_multi_surface`, `relative_to_terrain`, `creation_date`: none;
  `generic_attributes`: empty; `bounded_by`: present (the reader derives it).
- `lod2_multi_surface`: `1` surface member; triangulates to `3` triangles.
- No wall surface of the file has filling surfaces.
- The ground surface's polygon: `4` exterior points.

## `lod2_generic_attribute_kinds`

`GrossPlannedArea` is not a string attribute (`as_string` none); `ConstructionMethod` and `IsLandmarked` are not
measure attributes (`MeasureAttribute::try_from` none).

## `lod2_city_objects`

- `iter_city_objects` (feature types, at every depth, without the city model): `Building`, `WallSurface`,
  `WallSurface`, `WallSurface`, `RoofSurface`, `WallSurface`, `RoofSurface`, `GroundSurface`.
- `iter_features`: the city model first and only once.

## `lod2_object_bounds`

Read with `with_rebuild_object_bounds(false)`: none of the 4 wall surfaces has a `bounded_by`;
`recompute_child_bounding_shapes` gives all 4 one.

## `lod2_apply_translation`

`apply_translation(-100.0, 200.0, 10.0)` on the city model moves the lower corner of its envelope and of the first wall
surface's from `(457842.0, 5439083.0, 111.8)` to `(457742.0, 5439283.0, 121.8)`.

# `FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml`

## `lod3_doors_and_windows`

- Door surfaces (`iter_features` + `DoorSurface::try_from`), first name: `Door West`, `Door South`; sum of
  `lod3_multi_surface` → `area_3d`: `6.803850099444389`.
- Window surfaces (`WindowSurface::try_from`): `11`.

## `lod3_west_wall_fillings`

- The first boundary is a wall surface named `Outer Wall 1 (West)`.
- Its `filling_surfaces` (feature type, first name): (`WindowSurface`, `Window Round`), (`WindowSurface`,
  `Window North`), (`DoorSurface`, `Door West`), (`WindowSurface`, `Window South`).

## `lod3_building_details`

- `city_objects_len`: `1`; the building's `relative_to_terrain`: `EntirelyAboveTerrain`.
- `boundaries` (feature types): `WallSurface`, `WallSurface`, `WallSurface`, `RoofSurface`, `WallSurface`,
  `RoofSurface`, `GroundSurface`; each wall surface has a `lod3_multi_surface`.

## `lod3_fillings`

- The wall surfaces' `filling_surfaces`: `4`, `3`, `3`, `3` (`13`: `2` door and `11` window surfaces), all inline
  (`href` none), each with a `lod3_multi_surface` → `area_3d` above `0`; the roof surfaces have none.
- Window surfaces (`iter_features`): sum of `lod3_multi_surface` → `area_3d` `23.168802611529827`.
- Door surfaces: `feature_id`s `GML_c137f11d-9a8c-4126-9aeb-9a6c9b4e1cbd`, `GML_2d6ddf04-ee56-42a1-a9b1-b47e4181a629`;
  `lod2_multi_surface` none.

## `lod3_city_objects`

- `iter_city_objects`: `21` (`1` building, `4` wall, `2` roof, `1` ground, `2` door, `11` window surfaces).
- `iter_features`: `22`, the city model first.

## `lod3_composite_surface`

The first wall surface's `lod3_multi_surface`: its first surface member is a composite surface with `85` members; the
exterior of the composite's first polygon starts at `(457842.0, 5439088.49240388, 115.913175911167)`.

## `lod3_round_trip`

Writing the city model as CityGML (in memory or to a file, whichever the language offers) and reading it back gives
the same `iter_features` feature types in the same order, the building's `feature_id`
`UUID_d281adfc-4901-0f52-540b-4cc1a9325f82`, the same `feature_id`s of its boundaries and of the wall surfaces'
`filling_surfaces` (each in document order), and the building's only height (`topOfConstruction`,
`lowestGroundPoint`, `Measured`, `6.52` `m`).
