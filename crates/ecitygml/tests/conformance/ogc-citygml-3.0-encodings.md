# OGC CityGML 3.0 Encodings

Cases for the files in [`tests/fixtures/ogc-citygml-3.0-encodings`](../../../../tests/fixtures/ogc-citygml-3.0-encodings),
grouped per file. Floating point values are compared within ±1e-6 (absolute); lists are in document order. Thematic
surfaces without a `gml:id` get a generated `feature_id`, which no case asserts. An `href` is compared as written
(`HRef::to_string`); geometry referenced by `xlink:href` is not resolved, so its `area_3d` fails, and only the failure
is asserted, as in [`lod2_solid_unresolved`](fzk-haus.md#lod2_solid_unresolved).

Two files of the folder have no cases yet, as the reader rejects them (see the folder's README):
`Building_CityGML3.0_LOD2_with_several_attributes.gml` and `LocalCRS_CityGML3.gml`.

# `Building_and_garage_LOD2-EPSG25832.gml`

"The building" is the file's only building (`iter_features` + `Building::try_from`), "the part" its building part.

## `garage_city_model`

- `city_objects_len` (bindings) / `city_object_members_len` (Rust): `2`.
- `bounded_by` → envelope: lower corner `(458868.0, 5438343.0, 112.0)`, upper corner `(458892.0, 5438362.0, 117.0)`.
- `iter_features` (feature types): `CityModel`, `Building`, `GroundSurface`, `WallSurface` ×4, `RoofSurface` ×2,
  `BuildingPart`, `WallSurface` ×4, `GroundSurface`, `RoofSurface`, `ReliefFeature`, `TinRelief` (`18`).
- `iter_city_objects`: `17`.

## `garage_building`

| Getter | Expected |
|---|---|
| `feature_id` | `GML_7b1a5a6f-ddad-4c3d-a507-3eb9ee0a8e68` |
| `names` | `["Example Building LOD2"]` |
| `class` | none |
| `functions` / `usages` | `["1000"]` / empty |
| `roof_type` | `1030` |
| `storeys_above_ground` / `storeys_below_ground` | `1` / none |
| `date_of_construction` | 1985-01-01 |
| `heights` | exactly one: high reference `highestRoofEdge`, low reference `lowestGroundPoint`, status `Measured`, length `6.0` `#m` |

The building's `boundaries`, all inline (feature type, first name, `lod2_multi_surface` → `area_3d`): (`GroundSurface`,
`Ground Slab`, `50.0`), (`WallSurface`, `Wall South`, `30.0`), (`WallSurface`, `Wall North`, `30.0`), (`WallSurface`,
`Wall East`, `20.0`), (`WallSurface`, `Wall West`, `20.0`), (`RoofSurface`, `Roof North`, `32.01562118716424`),
(`RoofSurface`, `Roof South`, `32.01562118716424`).

## `garage_building_part`

- The building's `building_parts`: exactly one, inline (`href` none), `feature_id` `GMLID_BUI379228_1244_301`.
- The part: `names` `["Example BuildingPart LOD2"]`, `class` none, `functions` `["1630"]`, `usages` empty, `roof_type`
  `1010`, `date_of_construction` 1985-01-01, exactly one height (`highestRoofEdge`, `lowestGroundPoint`, `Measured`,
  `2.5` `#m`).
- The part's `boundaries`, all inline (feature type, first name): (`WallSurface`, `Garage Wall East`), (`WallSurface`,
  `Garage Wall South`), (`WallSurface`, `Garage Wall West`), (`WallSurface`, `Garage Wall North`), (`GroundSurface`,
  `Garage Ground Slab`), (`RoofSurface`, `Garage Roof`).
- Their `lod2_multi_surface` → `area_3d`: `9.600000023841858`, `6.25`, —, `5.75`, `10.0`, `10.012492197250394`. The west
  wall's only surface member is a `gml:OrientableSurface`, which the reader doesn't read yet; it is left out.

## `garage_relief`

- The relief feature (`iter_features` + `ReliefFeature::try_from`): `feature_id`
  `GML_6bb30328-7599-4500-90ef-766fde6aa67b`, `names` `["Example TIN LOD2"]`, `lod` `Two`; `relief_components`: exactly
  one, inline, of feature type `TinRelief`.
- The TIN relief (`TinRelief::try_from`): `feature_id` `GML_4eb161b0-aa7e-4087-937c-5c4c427c7fc9`, `names` `["Ground"]`,
  `lod` `Two`; `tin`: inline, a triangulated surface with `12` triangles and `area_3d` `399.8446647372588`.

## `garage_round_trip`

Writing the city model as CityGML (in memory or to a file, whichever the language offers) and reading it back gives
the same `iter_features` feature types in the same order, and the same `feature_id`s of the building, the part, the
relief feature and the TIN relief.

# `BuildingUnits_Storeys_xlink.gml`

"The building" is the file's only building; "the units" and "the storeys" are its building units and storeys
(`iter_features` + `BuildingUnit::try_from` / `Storey::try_from`).

## `units_city_model`

- `city_objects_len` / `city_object_members_len`: `1`.
- `bounded_by` → envelope: lower corner `(457841.0, 5439082.0, 111.0)`, upper corner `(457854.0, 5439093.0, 121.0)`.
- `iter_features` (feature types): `CityModel`, `Building`, `WallSurface` ×3, `RoofSurface`, `WallSurface`,
  `RoofSurface`, `GroundSurface`, then three building rooms — `BuildingRoom`, `InteriorWallSurface` ×8, `FloorSurface`,
  `CeilingSurface`; `BuildingRoom`, `InteriorWallSurface` ×8, `FloorSurface`, `CeilingSurface`; `BuildingRoom`,
  `InteriorWallSurface` ×4, `FloorSurface`, `CeilingSurface` — then `BuildingUnit` ×2, `Storey` ×2 (`42`).
- `iter_city_objects`: `41`.

## `units_building`

- `feature_id`: `building_unit_example_1`; `names`, `functions`, `usages`: empty; `class`, `roof_type`: none.
- `boundaries`, all inline (feature type, first name, `lod2_multi_surface` → `area_3d`): (`WallSurface`,
  `Outer Wall 1 (West)`, `89.375`), (`WallSurface`, `Outer Wall 2 (South)`, `81.25`), (`WallSurface`,
  `Outer Wall 3 (East)`, `89.375`), (`RoofSurface`, `Roof 1 (North)`, `86.53792521201326`), (`WallSurface`,
  `Outer Wall 4 (North)`, `81.25`), (`RoofSurface`, `Roof 2 (South)`, `86.53792521201326`), (`GroundSurface`,
  `Base Surface`, `143.0`).

## `units_subdivisions`

- The building's `building_subdivisions`: four, inline, of feature type `BuildingUnit`, `BuildingUnit`, `Storey`,
  `Storey`.
- The units: `feature_id` `BuildingUnit_apartment1`, `BuildingUnit_apartment2`; each `functions` `["apartment"]`,
  `class` none, `usages` empty, `boundaries` empty, `lod2_multi_surface` none.
- The storeys: `feature_id` `storey1`, `storey2`; each `names` empty, `class` none, `functions` and `usages` empty,
  `boundaries` empty.

## `units_storey_geometry`

Each storey's `lod2_multi_surface` is inline and has `6` surface members: the first inline, the next three only
references (`object` none), the last two inline. The references (`href`):

- `storey1`: `#Wall_1_PolyID82397_997_453711_16336011`, `#Wall_1_PolyID82397_997_453711_16336012`,
  `#Wall_1_PolyID82397_997_453711_163360136`.
- `storey2`: `#Wall_1_PolyID82397_997_453711_163360112`, `#Wall_1_PolyID82397_997_453711_163360122`,
  `#Wall_1_PolyID82397_997_453711_1633601362`.

Their `area_3d` fails (the referenced polygons aren't resolved). `bounded_by` → envelope: `storey1` from
`(457841.1, 5439082.1, 111.1)` to `(457853.9, 5439092.9, 113.9)`, `storey2` from `(457841.1, 5439082.1, 114.1)` to
`(457853.9, 5439092.9, 116.9)`.

## `units_round_trip`

Writing and reading back (as in `garage_round_trip`) gives the same `iter_features` feature types in the same order,
the building's `feature_id` `building_unit_example_1`, and the same `href`s of the storeys' surface members.

# `Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml`

"The bridge" and "the road" are the file's only bridge and road (`iter_features` + `Bridge::try_from` /
`Road::try_from`).

## `road_bridge_city_model`

- `city_objects_len` / `city_object_members_len`: `2`; `bounded_by`: none.
- `iter_features` (feature types): `CityModel`, `Bridge`, `GroundSurface`, `RoofSurface` ×2, `WallSurface` ×4, `Road`,
  then three times `Section`, `TrafficSpace`, `TrafficArea`, `TrafficSpace`, `TrafficArea` (`25`).
- `iter_city_objects`: `24`.

## `road_bridge_bridge`

- `feature_id`: `id_bridge1`; `names` empty; `related_to` empty.
- `boundaries`, all inline (`feature_id`, `lod2_multi_surface` → `area_3d`): `id_groundsurface1` `77500.15996032`,
  `id_roofsurface1` `38750.07998016`, `id_roofsurface2` `38750.07998016`, `id_wallsurface4` `10075.02000744`,
  `id_wallsurface1` `20150.04001488`, `id_wallsurface2` `10075.02000744`, `id_wallsurface3` `20150.04001488`.

## `road_bridge_road`

- `feature_id`: `id_road1`; `related_to`, `traffic_spaces`, `auxiliary_traffic_spaces`: empty.
- `sections`: three, inline, `feature_id` `id_section1`, `id_section2`, `id_section3`.
- Their `traffic_spaces`, inline: `id_trafficspace1`, `id_trafficspace2`; `id_trafficspace5`, `id_trafficspace6`;
  `id_trafficspace3`, `id_trafficspace4`. Each has exactly one boundary, an inline `TrafficArea` with the same number
  (`id_trafficarea1` …).

## `road_bridge_relations`

The `related_to` of the roof surfaces and the traffic areas (`iter_features` + `RoofSurface::try_from` /
`TrafficArea::try_from`, in document order): those below have exactly one, inline, `relation_type` `equal`,
`generic_attributes` empty, with the `href` of `relation_to` as written in the file — without `#`, and the last two
with a capital `S` that matches no `gml:id`; the other traffic areas (`id_trafficarea1` … `id_trafficarea4`) have none.

| City object | `relation_to` → `href` |
|---|---|
| `id_roofsurface1` | `id_trafficarea5` |
| `id_roofsurface2` | `id_trafficarea6` |
| `id_trafficarea5` | `id_roofSurface1` |
| `id_trafficarea6` | `id_roofSurface2` |

The wall and ground surfaces (`WallSurface::try_from`, `GroundSurface::try_from`) have no `related_to`.

## `road_bridge_round_trip`

Writing and reading back gives the same `iter_features` feature types in the same order, the bridge's and the road's
`feature_id`s, and the same relations of the roof surfaces and traffic areas (city object, `relation_type`, `href`).

# `historicalSuccession_CityGML_3.0_LOD2_Versioning.gml`

The file's versions and version transitions are not modeled; the reader reads the four buildings. "The buildings" are
`iter_features` + `Building::try_from`, "the parts" `BuildingPart::try_from`.

## `versioning_city_model`

- `city_objects_len` / `city_object_members_len`: `4`; `bounded_by`: none.
- `iter_features`: `60`, the city model first; per feature type: `CityModel` `1`, `Building` `4`, `BuildingPart` `5`,
  `RoofSurface` `14`, `WallSurface` `31`, `GroundSurface` `5`.
- `iter_city_objects`: `59`.

## `versioning_buildings`

The buildings (`feature_id`, first name, `creation_date`, `termination_date`, `building_parts` → `feature_id`s, all
inline); all dates at 00:00, UTC offset `0`:

| `feature_id` | Name | Created | Terminated | Parts |
|---|---|---|---|---|
| `BU_69381AL47_2000-01-01` | `Building A` | 2000-01-01 | 2015-01-01 | `BU_69381AL47_1` |
| `BU_69381AL49_2000-01-01` | `Building B` | 2000-01-01 | 2015-01-01 | `BU_69381AL49_1_2000-01-01` |
| `BU_69381AL49_2015-01-01` | `Building B` | 2015-01-01 | none | `BU_69381AL49_1_2015-01-01`, `BU_69381AL49_2_2015-01-01` |
| `BU_69381AL50_2015-01-01` | `Building C` | 2015-01-01 | none | `BU_69381AL50_1` |

Each building: `heights` and `boundaries` empty.

## `versioning_building_parts`

The parts (`feature_id`, height length in `#m`, number of `boundaries`); each has exactly one height
(`highestRoofEdge`, `lowestGroundPoint`, `Measured`), no `creation_date` and no names:

| `feature_id` | Height | Boundaries |
|---|---|---|
| `BU_69381AL47_1` | `13.015` | `8` |
| `BU_69381AL49_1_2000-01-01` | `10.63` | `9` |
| `BU_69381AL49_1_2015-01-01` | `10.63` | `9` |
| `BU_69381AL49_2_2015-01-01` | `8.743` | `7` |
| `BU_69381AL50_1` | `18.215` | `17` |

## `versioning_round_trip`

Writing and reading back gives the same `iter_features` feature types in the same order, the same `feature_id`s of
the buildings and the parts, and the same creation and termination dates of the buildings.
