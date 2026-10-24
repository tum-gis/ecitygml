# Railway Scene

Cases for the file in [`tests/fixtures/railway-scene`](../../../../tests/fixtures/railway-scene), whose geometry is
thinned (see its README): areas and surface member counts are those of the thinned file. Floating point values are
compared within ±1e-6 (absolute); lists are in document order. "The tunnels", "the trees", … are `iter_features` +
`Tunnel::try_from`, `SolitaryVegetationObject::try_from`, … in document order. Implicit geometries have no `gml:id`;
the `object_id`s the reader generates for them are not part of any case, nor is `library_object` (.NET doesn't bind
it; none is set). Railways, the water body, the city object group, the generic city objects and the tunnel, bridge and
building installations are not bound yet and only counted.

# `Railway_Scene_LoD3__v3-thinned.gml`

## `railway_city_model`

- `city_objects_len` (bindings) / `city_object_members_len` (Rust): `52`; `bounded_by`: none.
- `iter_features`: `232`, the city model first; per feature type: `CityModel` `1`, `SolitaryVegetationObject` `15`,
  `Tunnel` `4`, `TunnelInstallation` `8`, `Railway` `10`, `Bridge` `4`, `BridgeConstructiveElement` `3`,
  `BridgeInstallation` `2`, `Building` `3`, `BuildingInstallation` `56`, `CityFurniture` `11`, `CityObjectGroup` `1`,
  `GenericOccupiedSpace` `2`, `WaterBody` `1`, `WaterSurface` `1`, `WaterGroundSurface` `1`, `ReliefFeature` `1`,
  `TinRelief` `1`, `WallSurface` `33`, `RoofSurface` `12`, `GroundSurface` `7`, `ClosureSurface` `8`, `DoorSurface`
  `9`, `WindowSurface` `34`, `OuterCeilingSurface` `3`, `OuterFloorSurface` `1`.
- `iter_city_objects`: `231`.

## `railway_tunnels`

The tunnels (`feature_id`, first name, `boundaries` feature types, all inline):

| `feature_id` | Name | Boundaries |
|---|---|---|
| `GMLID_BUI142242_863_347` | `Tunnel KIT/KHH-3` | `GroundSurface`, `WallSurface`, `RoofSurface`, `WallSurface`, `ClosureSurface`, `ClosureSurface` |
| `GMLID_BUI336993_213_9312` | `Tunnel KIT/KHH-2` | `WallSurface`, `RoofSurface`, `WallSurface`, `ClosureSurface`, `ClosureSurface`, `GroundSurface` |
| `GMLID_BUI289877_1911_4122` | `Tunnel KIT/KHH-4` | `WallSurface`, `GroundSurface`, `ClosureSurface`, `WallSurface`, `RoofSurface`, `ClosureSurface` |
| `GMLID_BUI180021_673_14143` | `Tunnel KIT/KHH-1` | `GroundSurface`, `WallSurface`, `RoofSurface`, `ClosureSurface`, `ClosureSurface`, `WallSurface` |

Each: `class` none, `functions`, `usages` and `tunnel_parts` empty, `creation_date` 2015-03-06 00:00 at UTC offset
+01:00, `relative_to_terrain` `EntirelyAboveTerrain`.

## `railway_trees`

The trees (`feature_id`, first name, `class`, `species`, `functions`):

| `feature_id` | Name | `class` | `species` | `functions` |
|---|---|---|---|---|
| `GMLID_SO0158953_776_12462` | `Forest tree 3` | `1070` | `1800` | empty |
| `GMLID_SO092422_3593_9527` | `Tree1` | none | `9999` | `["LOD3"]` |
| `GMLID_SO0200811_525_4986` | `Forest tree 1` | `1060` | `1640` | empty |
| `GMLID_SO0321978_1466_7441` | `Forest tree 4` | `1070` | `1800` | empty |
| `GMLID_SO0260143_1214_1315` | `Forest tree 11` | `1060` | `1640` | empty |
| `GMLID_SO0400934_2926_3381` | `Forest tree 12` | `1060` | `1640` | empty |
| `GMLID_SO0124800_3522_13577` | `Forest tree 13` | `1060` | `1640` | empty |
| `GMLID_SO0443764_1492_9667` | `Forest tree 14` | `1060` | `1640` | empty |
| `GMLID_SO015374_872_14131` | `Forest tree 2` | `1060` | `1640` | empty |
| `GMLID_SO081792_2341_11961` | `Forest tree 10` | `1060` | `1640` | empty |
| `GMLID_SO0283142_1335_8999` | `Forest tree 7` | `1060` | `1640` | empty |
| `GMLID_SO0107241_3793_12555` | `Forest tree 9` | `1070` | `1800` | empty |
| `GMLID_SO0286258_965_2893` | `Forest tree 5` | `1070` | `1800` | empty |
| `GMLID_SO0410128_214_10515` | `Forest tree 6` | `1060` | `1640` | empty |
| `GMLID_SO086970_1053_8814` | `Forest tree 8` | `1060` | `1640` | empty |

Each: `usages` empty; `lod1_implicit_representation` and `lod2_implicit_representation` none.

## `railway_tree_templates`

Each tree's `lod3_implicit_representation` is inline (`href` none). Its implicit geometry: `mime_type` none;
`transformation_matrix` `get(0, 0)`, `get(1, 1)`, `get(2, 2)` `30.0` and `get(3, 3)` `1.0`; `relative_geometry`:

- inline, a `MultiSurface` (`MultiSurface::try_from`) with `1` surface member, for `Forest tree 3`, `Tree1` and
  `Forest tree 1`;
- only a reference, `href` `#Mult_SO043561_5693_194007`, for `Forest tree 4`, `Forest tree 9` and `Forest tree 5`;
- only a reference, `href` `#Mult_SO045475_3243_790864`, for the nine other trees.

## `railway_tree_placement`

The implicit geometries' `reference_point` → point → `pos`, and the translation `get(0, 3)`, `get(1, 3)`,
`get(2, 3)` of their `transformation_matrix`:

- `Forest tree 3`: reference point `(-600.0, 400.0, -150.0)`, translation
  `(39.4421005419207, 220.3838834926932, 268.5013679006178)`.
- `Tree1`: reference point `(-568.8000793496976, 457.60044759869743, 105.00139681350242)`, translation `(0.0, 0.0, 0.0)`.
- Every other tree: reference point `(-600.0, 400.0, -150.0)`.

## `railway_furniture`

The city furniture (`feature_id`, `functions`):

| `feature_id` | `functions` |
|---|---|
| `GMLID_7431654_78949_792` | `["1090"]` |
| `GMLID_0528986_170479_94` | `["OTHERS"]` |
| `GMLID_4323540_367099_910` | `["1090"]` |
| `GMLID_1381455_184173_656` | `["OTHERS"]` |
| `GMLID_1429491_351612_1485` | `["1090"]` |
| `GMLID_5361967_192822_672` | `["1090"]` |
| `GMLID_2108434_31807_876` | `["1090"]` |
| `GMLID_0373494_301709_129` | `["1540"]` |
| `GMLID_6162422_289094_1279` | `["1090"]` |
| `GMLID_3313190_307178_612` | `["1090"]` |
| `GMLID_855011_330784_753` | `["1540"]` |

Each: `class` none, `usages` empty, `lod3_implicit_representation` none, `lod3_multi_surface` inline with `1` surface
member.

## `railway_relief`

- The relief feature: `feature_id` `GMLID_TIN436865_187531_1154`, `names` empty, `lod` `Three`; `relief_components`:
  exactly one, inline, of feature type `TinRelief`.
- The TIN relief: `feature_id` `UUID_5aa70b07-6bbf-427b-8222-d72ed77dbfa9`, `lod` `Three`; `tin`: inline, a
  triangulated surface with `1` triangle and `area_3d` `3.2750424144626247`.

## `railway_buildings_and_bridges`

- The buildings (`feature_id`, first name, number of `boundaries`): `GMLID_BUI184698_512_898` `Station KIT/KHH-1`
  `13`, `GMLID_BUI46739_1739_10911` `Chapel KIT/KHH-1` `19`, `GMLID_BUI130363_1235_6047` `Boatshouse KIT/KHH-1` `8`.
- The bridges (`feature_id`, first name): `GMLID_BUI205585_1385_1373` `Bridge KIT 4`, `GMLID_BUI51891_765_738`
  `Bridge KIT 3`, `GMLID_BUI100628_817_8083` `Bridge KIT 2`, `GMLID_BUI30683_572_6686` `Bridge KIT 1`.

## `railway_round_trip`

Writing the city model as CityGML (in memory or to a file, whichever the language offers) and reading it back gives
the same `iter_features` feature types in the same order, the same `feature_id`s of the tunnels, trees, city
furniture, buildings and bridges, and the same `href`s of the trees' relative geometries.
