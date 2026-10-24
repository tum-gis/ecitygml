# Synthetic

Cases for the hand-written files in [`tests/fixtures/synthetic`](../../../../tests/fixtures/synthetic), grouped per
file: the content no real fixture has. Floating point values are compared within ±1e-6 (absolute); lists are in
document order; "the bridge" (tunnel, …) is the file's only one (`iter_features` + `T::try_from`), other features are
named by their `feature_id`. A round trip writes the city model as CityGML (in memory or to a file, whichever the
language offers) and reads it back.

# `bridge.gml`

## `bridge_city_model`

- `city_objects_len` (bindings) / `city_object_members_len` (Rust): `1`.
- `iter_features` (feature types): `CityModel`, `Bridge`, `BridgePart`; `iter_city_objects`: `Bridge`, `BridgePart`.

## `bridge_attributes`

- The bridge: `feature_id` `bridge_1`, `names` `["Synthetic bridge"]`, `class` `1000`, `functions` `["1010", "1020"]`,
  `usages` `["1000"]`, `date_of_construction` 1990-05-01, `heights` empty.
- Its `bridge_parts`: exactly one, inline, `feature_id` `bridge_part_1`, `class` none, `functions` empty; it is the
  feature `BridgePart::try_from` accepts.

## `bridge_is_movable`

Suites: all except Kotlin (`is_movable` isn't bound there).

`is_movable`: the bridge `true`, its part `false`.

## `bridge_code_spaces`

Suites: all except .NET (`Code::code_space` isn't bound there).

The bridge's `class` code space `https://example.org/bridge_class`; its functions have no code space.

## `bridge_round_trip`

After a round trip: the same `iter_features` feature types; the bridge's `class` `1000`, `functions` `["1010",
"1020"]`, `date_of_construction` 1990-05-01; its part's `feature_id` `bridge_part_1`.

# `tunnel.gml`

## `tunnel_city_model`

- `city_objects_len` / `city_object_members_len`: `1`.
- `iter_features` (feature types): `CityModel`, `Tunnel`, `TunnelPart`; `iter_city_objects`: `Tunnel`, `TunnelPart`.

## `tunnel_attributes`

- The tunnel: `feature_id` `tunnel_1`, `names` `["Synthetic tunnel"]`, `class` `1000`, `functions` `["1010", "1020"]`,
  `usages` `["1000"]`, `date_of_construction` 1990-05-01, `heights` empty.
- Its `tunnel_parts`: exactly one, inline, `feature_id` `tunnel_part_1`, `class` none, `functions` `["1030"]`; it is
  the feature `TunnelPart::try_from` accepts.

## `tunnel_code_spaces`

Suites: all except .NET (`Code::code_space` isn't bound there).

The tunnel's `class` code space `https://example.org/tunnel_class`; its functions have no code space.

## `tunnel_round_trip`

After a round trip: the same `iter_features` feature types; the tunnel's `class` `1000`, `functions` `["1010",
"1020"]`; its part's `functions` `["1030"]`.

# `vegetation.gml`

## `vegetation_city_model`

- `city_objects_len` / `city_object_members_len`: `3`.
- `iter_features` (feature types): `CityModel`, `SolitaryVegetationObject`, `SolitaryVegetationObject`, `PlantCover`.

## `vegetation_tree`

The tree `tree_1`: `class` `1000`, `functions` `["1010"]`, `usages` `["1020"]`, `species` `Quercus robur`; `height`
`12.5` `m`, `trunk_diameter` `0.4`, `crown_diameter` `5.5`, `root_ball_diameter` `1.2`, `max_root_ball_depth` `0.8`;
`lod2_implicit_representation`, `lod3_implicit_representation`, `lod1_solid`, `lod1_terrain_intersection_curve`:
none.

## `vegetation_implicit_geometry`

The `lod1_implicit_representation` of `tree_1`, inline (`href` none):

- `object_id` `tree_prototype`, `mime_type` `model/gltf+json`, `reference_point` `(457850.0, 5439090.0, 112.0)`.
- `transformation_matrix`, rows: `(2, 0, 0, 10)`, `(0, 2, 0, 20)`, `(0, 0, 3, 30)`, `(0, 0, 0, 1)`.
- `relative_geometry`: of `geometry_type` `MultiSurface` (`MultiSurface::try_from` accepts it, `Point::try_from`
  doesn't) with `1` surface member; `triangulate` gives `1` triangle, none skipped.

## `vegetation_point_relative_geometry`

The tree `tree_2`: `lod1_implicit_representation` none; its `lod2_implicit_representation`: `object_id`
`point_prototype`, `mime_type` none, `relative_geometry` of `geometry_type` `Point` at `(0.0, 0.0, 0.0)`
(`MultiSurface::try_from` doesn't accept it).

## `vegetation_library_object`

Suites: all except .NET (`ImplicitGeometry::library_object` isn't bound there).

`library_object`: `tree_1`'s implicit geometry none, `tree_2`'s `https://example.org/trees/oak.gltf`.

## `vegetation_plant_cover`

The plant cover `cover_1`: `class` `2000`, `functions` and `usages` empty, `average_height` `2.5`, `min_height` `1.0`,
`max_height` `4.0`, `lod1_implicit_representation` none; `SolitaryVegetationObject::try_from` doesn't accept it.

## `vegetation_code_spaces`

Suites: all except .NET (`Code::code_space` isn't bound there).

`tree_1`'s `class` code space `https://example.org/tree_class`; `cover_1`'s `class` has none.

## `vegetation_round_trip`

After a round trip: the same `iter_features` feature types; `tree_1`'s `species` `Quercus robur`, `height` `12.5`, its
implicit geometry's `object_id` `tree_prototype` and `mime_type` `model/gltf+json`; `cover_1`'s `average_height`
`2.5`. The written CityGML doesn't contain `objectId` (the `gml:id` isn't written twice).

# `city-furniture.gml`

## `furniture_attributes`

The city furniture: `feature_id` `sign_1`, `names` `["Vorschriftzeichen"]`, `class` `1000`, `functions` `["1080"]`,
`usages` `["1090"]`; `lod2_multi_surface` inline with `1` surface member; `lod1_implicit_representation` and
`lod2_terrain_intersection_curve` none.

## `furniture_code_spaces`

Suites: all except .NET (`Code::code_space` isn't bound there).

The `class` code space `https://example.org/furniture_class`.

# `building.gml`

"The building" is `building_1`.

## `building_city_model`

- `city_objects_len` / `city_object_members_len`: `2`.
- `iter_features` (feature types): `CityModel`, `Building`, `RoofSurface`, `WindowSurface`, `Building`;
  `iter_city_objects`: `4`.

## `building_relation`

The building's `related_to`: exactly one, inline: `relation_type` `shared`, `relation_to` → `href` `#building_2`;
`generic_attributes`: exactly one, `weight`, an int attribute with value `3`.

## `building_attribute_set`

The building's `generic_attributes`: exactly one, a generic attribute set (`GenericAttributeSet::try_from`) named
`energy`, whose `generic_attributes` are `demand` (double `12.5`) and `label` (string `A+`).

## `building_construction`

The building: `relative_to_water` `EntirelyAboveWaterSurface`, `date_of_construction` 2020-01-01,
`date_of_demolition` 2050-12-31; `occupancies`: exactly one, `number_of_occupants` `4`, `interval` `daytime`,
`occupant_type` `residents`.

## `building_boundaries`

The building's `boundaries`: two.

- The first inline, a `RoofSurface` with `feature_id` `roof_1`; its `filling_surfaces`: exactly one, inline, a
  `WindowSurface` with `feature_id` `roof_window_1`.
- The second only a reference: `object` none, `href` `#missing_boundary`.

## `building_terrain_intersection_curve`

The building's `lod2_terrain_intersection_curve`: inline, one curve member, a line string with `2` points;
`length_3d` `12.0`. `lod1_terrain_intersection_curve` and `lod3_terrain_intersection_curve`: none.

## `building_round_trip`

After a round trip: the same `iter_features` feature types; the relation's `href` `#building_2`, the attribute set's
name `energy`, `date_of_demolition` 2050-12-31, the occupancy (`4`, `daytime`, `residents`), the roof window's
`feature_id` `roof_window_1`, the second boundary's `href` `#missing_boundary`, the terrain intersection curve's
`length_3d` `12.0`. The written CityGML doesn't contain `TerrainIntersectionCurveProperty` (the curve is written as a
`gml:MultiCurve`).

# `transportation.gml`

## `transportation_section`

The section `section_1`: `traffic_direction` `Both`; `occupancies`: exactly one, `number_of_occupants` `120`,
`interval` `peakHour`; `traffic_spaces`: exactly one, inline, `feature_id` `space_1`, `granularity` `Lane`.

## `transportation_point`

The traffic space's `lod0_point`: inline, `id` `point_1`, `pos` `(1.5, -2.5, 3.25)`; `compute_envelope`: lower and
upper corner both at `pos`.

## `transportation_curves`

The traffic space's `lod0_multi_curve`: three curve members.

- The first a line string (`geometry_type` `LineString`) with `2` points, `length_3d` `5.0`; `AbstractRingKind::try_from`
  doesn't accept it.
- The second a linear ring (`geometry_type` `LinearRing`; `AbstractRingKind::try_from` accepts it) with `3` points
  (the repeated closing position is dropped), `length_3d` `3.414213562373095` (`2 + √2`).
- The third only a reference: `object` none, `href` `#missing_curve`.
- The multi curve's `length_3d` fails with `UnresolvedReference`, message containing `#missing_curve`.

# `geometry.gml`

## `geometry_skipped_members`

The building `geometry_1`: its `lod2_multi_surface` has three surface members:

- Polygons `square` and `collinear` (`geometry_type` `Polygon`); the collinear one has `area_3d` `0.0`.
- `tin`, a triangulated surface (`geometry_type` `TriangulatedSurface`; `Polygon::try_from` doesn't accept it,
  `TriangulatedSurface::try_from` does) with `2` triangles, `2` `surface` patches and `area_3d` `1.0`.
- The multi surface's `triangulate`: `4` triangles (`2` of the square, `2` of the TIN); `has_skipped`, exactly one
  skipped member error: `InvalidArgument`, message containing `earcut produced no triangles`.
