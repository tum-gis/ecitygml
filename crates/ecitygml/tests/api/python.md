# Python

Cases of the Python bindings' dynamic typing: which class a getter returns, which getters a class has, the enums and
the Python types of values. The other languages check these at compile time, so every case is scoped to Python. "FZK
LoD1" is `<fixtures>/fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml`, "FZK LoD2" and "FZK LoD3" its siblings, "TUM"
`<fixtures>/tum-main-entrance/TUM-Main-Entrance.gml`, "ASAM road shape" and "ASAM junction"
`<fixtures>/asam-opendrive/ASAM-UC_RoadShape.gml` and `…/ASAM-Ex_Bidirectional_Junction.gml`, "synthetic `<file>`"
`<fixtures>/synthetic/<file>`. A property's object is `object()` of the property.

## `python_return_types`

Suites: Python (the other languages are statically typed).

Each value is an instance (`isinstance`) of the class:

| File | Value | Class |
|---|---|---|
| FZK LoD2 | `GmlReader::from_path(…).finish()` | `CityModel` |
| FZK LoD2 | the items of the building's `heights` | `Height` |
| FZK LoD1 | the object of the building's `lod1_solid` | `Solid` |
| FZK LoD1 | the solid's `points`; the `a`, `b`, `c` of its triangulation's first triangle | `DirectPosition` |
| FZK LoD1 | the exterior of the solid's first polygon | `AbstractRingKind`; `LinearRing::try_from` of it `LinearRing` |
| FZK LoD1 | the solid's `compute_envelope`; its first polygon's `compute_envelope` | `Envelope` |
| FZK LoD1 | `contains` of the building's `bounded_by` envelope, for the solid's first point | `bool` |
| FZK LoD1 | the solid's `triangulate().surface()` | `TriangulatedSurface` |
| FZK LoD1 | the items of that surface's `triangles` | `Triangle` |
| FZK LoD3 | the objects of the first wall's, door's and window's `lod3_multi_surface` | `MultiSurface` |
| FZK LoD3 | the objects of the walls' `filling_surfaces` | `AbstractFillingSurfaceKind` |
| TUM | the items of the first building's `external_references` | `ExternalReference` |
| ASAM junction | the objects of the road's `sections`, `intersections` | `Section`, `Intersection` |
| ASAM junction | the objects of the first section's `traffic_spaces` | `TrafficSpace` |
| ASAM junction | the object of the first section's first traffic space's `lod2_multi_curve` | `MultiCurve` |
| ASAM road shape | the objects of the first section's `auxiliary_traffic_spaces` | `AuxiliaryTrafficSpace` |
| synthetic `building.gml` | the items of `building_1`'s `occupancies` | `Occupancy` |
| synthetic `building.gml` | the objects of `building_1`'s `related_to` | `CityObjectRelation` |
| synthetic `building.gml` | the object of `building_1`'s `lod2_terrain_intersection_curve` | `MultiCurve` |
| synthetic `bridge.gml` | the objects of the bridge's `bridge_parts` | `BridgePart` |
| synthetic `tunnel.gml` | the objects of the tunnel's `tunnel_parts` | `TunnelPart` |
| synthetic `vegetation.gml` | the object of `tree_1`'s `lod1_implicit_representation` | `ImplicitGeometry` |

## `python_class_getters`

Suites: Python (the other languages are statically typed).

Each class has (`hasattr`) the getters of its abstract CityGML types, and lacks those of the others. The groups:

- Spaces: `Building`, `Bridge`, `BridgePart`, `Tunnel`, `TunnelPart`, `CityFurniture`, `SolitaryVegetationObject`,
  `PlantCover` (the occupied ones), `Road`, `Section`, `Intersection`, `TrafficSpace`, `AuxiliaryTrafficSpace` (the
  unoccupied ones).
- Logical spaces: `Storey`, `BuildingUnit`.
- Thematic surfaces: `WallSurface`, `RoofSurface`, `GroundSurface` (the construction surfaces), `DoorSurface`,
  `WindowSurface`, `AbstractFillingSurfaceKind` (the filling surfaces), `TrafficArea`, `AuxiliaryTrafficArea`.
- Features: all of the above (except `AbstractFillingSurfaceKind`), `ReliefFeature`, `TinRelief`.

| Classes | Have | Lack |
|---|---|---|
| features | `id`, `bounded_by`, `creation_date`, `termination_date`, `valid_from`, `valid_to`, `relative_to_terrain`, `relative_to_water`, `external_references`, `generic_attributes`, `related_to` | |
| spaces | `lod1_solid` … `lod3_solid`, `lod0_multi_surface`, `lod2_multi_surface`, `lod3_multi_surface`, `lod0_multi_curve`, `lod2_multi_curve`, `lod3_multi_curve`, `lod1_terrain_intersection_curve` … `lod3_terrain_intersection_curve` | |
| occupied spaces | `lod1_implicit_representation` … `lod3_implicit_representation` | |
| unoccupied spaces | | `lod1_implicit_representation` … `lod3_implicit_representation` |
| `Building`, `Bridge`, `BridgePart`, `Tunnel`, `TunnelPart` | `date_of_construction`, `date_of_demolition`, `heights`, `occupancies`, `class_`, `functions`, `usages` | |
| `CityFurniture`, `SolitaryVegetationObject`, `PlantCover` | | `date_of_construction`, `date_of_demolition`, `heights`, `occupancies` |
| `Building` | `roof_type`, `storeys_above_ground`, `storeys_below_ground`, `building_subdivisions` | |
| `Bridge`, `BridgePart` | `is_movable` | `roof_type`, `storeys_above_ground` |
| `Tunnel`, `TunnelPart` | | `is_movable` |
| `Road`, `Section`, `Intersection` | `traffic_direction`, `occupancies`, `traffic_spaces`, `auxiliary_traffic_spaces` | |
| `TrafficSpace`, `AuxiliaryTrafficSpace` | | `traffic_spaces`, `auxiliary_traffic_spaces` |
| logical spaces | the spaces' `lod…` geometry getters but not the terrain intersection curves, `class_`, `functions`, `usages` | `lod1_terrain_intersection_curve` … `lod3_terrain_intersection_curve` |
| thematic surfaces | `generic_attributes`, `lod0_multi_curve`, `lod0_multi_surface` … `lod3_multi_surface` (filling surfaces: `lod3_multi_surface`) | |
| construction surfaces | `filling_surfaces` | `door_surfaces`, `window_surfaces` |
| filling surfaces | | `filling_surfaces` |

## `python_enums`

Suites: Python (nanobind enums; the other languages' enums are covered by `feature_type_name` and
`level_of_detail_index`).

- `FeatureType.Building == FeatureType.Building`, `FeatureType.Road != FeatureType.Building`; `LevelOfDetail.One ==
  LevelOfDetail.One`, `LevelOfDetail.One != LevelOfDetail.Two`.
- `.value` of `LevelOfDetail.Zero` … `Three`: `0` … `3`.
- `repr` of `FeatureType.Building` contains `Building`, of `LevelOfDetail.One` `One`.
- `FeatureType` has the members `Building`, `Road`, `Section`, `Intersection`, `TrafficSpace`, `TrafficArea`,
  `AuxiliaryTrafficSpace`, `AuxiliaryTrafficArea`, `WallSurface`, `RoofSurface`, `GroundSurface`, `DoorSurface`,
  `WindowSurface`, `TinRelief`, `ReliefFeature`, `SolitaryVegetationObject`, `CityFurniture`.

## `python_value_types`

Suites: Python (the other languages are statically typed).

- The values of the int and double generic attributes of every traffic space of ASAM road shape (`as_int`,
  `as_double`) are exactly `int` and `float` (`type(…) is`).
- Absent values are `None`: FZK LoD2's first wall surface's `creation_date`, `termination_date`, `valid_from`,
  `valid_to`; ASAM junction's road's space geometries (`lod1_solid` … `lod3_multi_curve`); TUM's first external
  reference's `relation_type`.
