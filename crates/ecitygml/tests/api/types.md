# Types

Cases of the value types and conversions: positions, levels of detail, feature types, dates, `try_from` and the
feature references, ids and codes. "FZK LoD1" is `<fixtures>/fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml`, "FZK
LoD2" and "FZK LoD3" its siblings, "TUM" `<fixtures>/tum-main-entrance/TUM-Main-Entrance.gml`, "ASAM road shape" and
"ASAM junction" `<fixtures>/asam-opendrive/ASAM-UC_RoadShape.gml` and `…/ASAM-Ex_Bidirectional_Junction.gml`.

## `direct_position_new`

`DirectPosition::new(1.0, 2.0, 3.0)` (C++, Kotlin, .NET: `create`; Python, TypeScript, Dart: the constructor): `x`, `y`, `z` are `1.0`,
`2.0`, `3.0`. `DirectPosition::new(NaN, 0.0, 0.0)` fails with `InvalidArgument`, message containing `non-finite`.

## `level_of_detail_index`

Suites: all except Python, .NET (their enums have no methods).

`as_index` of `Zero`, `One`, `Two`, `Three` is `0`, `1`, `2`, `3`; `LevelOfDetail::try_from` of `0` … `3` gives them
back; `try_from(4)` fails with `InvalidArgument`, message containing `4`.

## `feature_type_name`

The name of `FeatureType::Building` is `Building`, of `FeatureType::TinRelief` `TinRelief`: `to_string` (Rust:
`Display`; Kotlin, Python: the enum's `name`; .NET: `ToString()`).

## `date_from_parts`

- `Date::from_parts(2020, 1, 2, 3600)`: `year` `2020`, `month` `1`, `day` `2`, `offset_seconds` `3600`; its
  `start_of_day`: `hour`, `minute`, `second` `0`, `to_rfc3339` `2020-01-02T00:00:00+01:00`.
- `Date::from_parts(2021, 2, 30, 0)` fails with `InvalidArgument`, message containing `do not form a valid date`.

## `date_time_from_parts`

- `DateTime::from_parts(2017, 1, 23, 13, 14, 15, 500000000, -7200)`: `year` `2017`, `month` `1`, `day` `23`, `hour`
  `13`, `minute` `14`, `second` `15`, `nanosecond` `500000000`, `offset_seconds` `-7200`; `timestamp` `1485184455`,
  `timestamp_subsec_nanos` `500000000`; `to_rfc3339` `2017-01-23T13:14:15.500-02:00`.
- `DateTime::from_parts(2020, 1, 1, 0, 0, 0, 0, 30)` fails with `InvalidArgument`, message containing
  `timezone offset of 30 s is invalid`.

## `date_time_read`

The `creation_date` of the FZK LoD2 building: `to_rfc3339` `2017-01-23T00:00:00+01:00`.

## `try_from_matches_feature_type`

For every feature of FZK LoD3 (`iter_features`), `T::try_from` accepts it exactly when its `feature_type` is `T`, for
`T` = `Building`, `WallSurface`, `RoofSurface`, `GroundSurface`, `DoorSurface`, `WindowSurface`; likewise for every
feature of ASAM road shape and `T` = `Road`, `Section`, `TrafficSpace`, `TrafficArea`, `AuxiliaryTrafficSpace`,
`AuxiliaryTrafficArea`.

## `feature_from_city_object`

The first of ASAM junction's `iter_city_objects` has feature type `Road`. As a feature
(`AbstractFeatureKindRef::from_city_object`; Rust: the `AbstractCityObjectKind` variant of `AbstractFeatureKindRef`):
feature type `Road`; `Road::try_from` accepts it, `feature_id` `UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f`;
`Building::try_from` doesn't.

## `matrix_index_out_of_range`

Suites: all except Rust (its matrix is an `nalgebra` matrix, indexed without a fallible `get`).

The `transformation_matrix` of the lod3 implicit representation of the tree `GMLID_SO092422_3593_9527` in
`<fixtures>/railway-scene/Railway_Scene_LoD3__v3-thinned.gml`: `get(3, 3)` is `1.0`; `get(4, 0)` and `get(0, 4)` fail
with `InvalidArgument`, message containing `out of range`.

## `gml_id`

`id` (`gml:id`, an `Option`) next to `feature_id`:

- FZK LoD1's city model has no `gml:id`: the reader generates one, so `id` and `feature_id` are the same id, starting
  with `ecitygml-gen-feature-`.
- FZK LoD2's first wall surface: `id` and `feature_id` `GML_5856d7ad-5e34-498a-817b-9544bfbb1475`.
- The TUM building: `id` `DEBY_LOD2_4959457`.

## `code_space`

Suites: all except .NET (`Code::code_space` isn't bound there).

- The FZK LoD2 building: `class` → `code`: value `1000`, `code_space`
  `http://www.sig3d.org/codelists/citygml/2.0/building/2.0/_AbstractBuilding_class.xml`; its function and usage
  (`1000` each) have the code spaces `…_AbstractBuilding_function.xml` and `…_AbstractBuilding_usage.xml` (same prefix).
- The TUM building's function `31001_3020`: `code_space` none.
- FZK LoD1's city model name `AC14-FZK-Haus`: `code_space` none.
