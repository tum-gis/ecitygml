# Geometry

Cases of the geometry types and their computations: envelopes, polygons with holes, composite surfaces and patches,
triangles, unresolved references and triangulation. Floating point values are compared within ±1e-6 (absolute). "FZK
LoD1" is `<fixtures>/fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml`, "FZK LoD2" its LoD2 sibling, "TUM"
`<fixtures>/tum-main-entrance/TUM-Main-Entrance.gml`, "ASAM road shape" `<fixtures>/asam-opendrive/ASAM-UC_RoadShape.gml`,
"railway" `<fixtures>/railway-scene/Railway_Scene_LoD3__v3-thinned.gml`, "OGC garage", "OGC units" and "OGC road over
bridge" the files `Building_and_garage_LOD2-EPSG25832.gml`, `BuildingUnits_Storeys_xlink.gml` and
`Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml` in `<fixtures>/ogc-citygml-3.0-encodings`.

Members only referenced by `xlink:href` are kept unresolved: they fail measurements (`area_3d`), are left out of
`points`, `compute_envelope` and `triangulate`, and a geometry without any other member has no envelope and fails to
triangulate. Geometry only hand-written input has (rings as curve members, unresolved curve references, triangulated
surfaces as surface members, members that fail to triangulate) is not part of this list.

## `compute_envelope`

`compute_envelope` (lower corner .. upper corner):

- FZK LoD1, the building's `lod1_solid`: `(457842.0, 5439083.0, 111.8)` .. `(457854.0, 5439093.0, 118.31769)`; the same
  for its `exterior` shell and for its `triangulate` → `surface`. The shell's first polygon and that polygon's
  `exterior` ring: `(457842.0, 5439083.0, 111.8)` .. `(457854.0, 5439093.0, 111.8)`.
- ASAM road shape, the first traffic space: `lod2_multi_curve` and its only curve member `(-48.38872036507727,
  2.3148451158285663, 0.25)` .. `(-16.661414812688488, 26.674198193965925, 0.25)`; `lod2_solid` `(-49.60668801898414,
  0.7284798382091271, 0.05)` .. `(-15.44344715878162, 28.260563471585364, 4.95)`, with `24` `points`.
- Railway, the `reference_point` of the lod3 implicit representation of the tree `GMLID_SO092422_3593_9527`: lower and
  upper corner both `(-568.8000793496976, 457.60044759869743, 105.00139681350242)`.
- OGC garage, the `tin` of the TIN relief: `(458868.0, 5438343.0, 112.0)` .. `(458892.0, 5438362.0, 114.0)`.

## `polygon_interior_rings`

TUM, the building's only ground surface (`GroundSurface::try_from`): its `lod2_multi_surface` has one polygon, `id`
`DEBY_LOD2_4959457_2470b16f-99f0-43c3-9a27-bd4fc3822c91_2_poly`.

- `exterior`: a `LinearRing` with `11` points, `area_3d` `1371.825439453125`, `length_3d` `150.78554397170106`.
- `interior`: exactly one ring, with `4` points, `area_3d` `142.26318359375`, `length_3d` `47.7096809282068`.
- The polygon: `area_3d` `1229.562255859375` (the exterior without the hole), `points` `15`, `compute_envelope`
  `(691009.16, 5335994.57, 515.042)` .. `(691054.07, 5336047.41, 515.042)`.
- The multi surface's `triangulate`: `15` triangles, none skipped, `area_3d` `1229.5620994984272`.

## `composite_surface_and_patches`

OGC road over bridge, the ground surface `id_groundsurface1`: its `lod2_multi_surface` (`id` `id_groundsurface1-0`,
`area_3d` `77500.15996032`) has one surface member, a composite surface:

- `geometry_type` `CompositeSurface`, `id` `id_groundsurface1-1`; `Polygon::try_from` doesn't accept it,
  `CompositeSurface::try_from` does.
- `area_3d` `77500.15996032`, `points` `6`, `compute_envelope` `(0.0, 0.0, 0.0)` .. `(393.7008, 196.8504, 0.0)`;
  `triangulate`: `2` triangles, none skipped.
- Its `surface_member`s: two surfaces (`geometry_type` `Surface`), `id` `fme-gen-1a9ac79e-2880-47c7-b7c3-c9df5bc17447`
  and `fme-gen-545ee504-7440-4cb6-8713-fc8ba21ac163`, each with `area_3d` `38750.07998016` and `triangulate` → `1`
  triangle.
- Each surface's `patches`: exactly one, a polygon patch (`PolygonPatch::try_from` accepts it, `Triangle::try_from`
  doesn't), without interior rings, its `exterior` a `LinearRing` with `3` points; the patch's `area_3d`
  `38750.07998016`, `triangulate` → `1` triangle.

## `triangle_patches`

OGC garage, the `tin` of the TIN relief: `patches` `12`; its first triangle (`triangles`): `a` `(458883.0, 5438362.0,
114.0)`, `b` `(458868.0, 5438362.0, 112.0)`, `c` `(458875.0, 5438355.0, 112.0)`, `area` `53.42518132865812`, `exterior`
of `geometry_type` `LinearRing`.

## `unresolved_surface_reference`

OGC units, the storey `storey1`: its `lod2_multi_surface` has `6` surface members, three of them only references.

- `area_3d` fails with `UnresolvedReference`, message containing `#Wall_1_PolyID82397_997_453711_16336011` (the first
  reference).
- `points`: `12` (the inline members); `compute_envelope` `(457841.1, 5439082.1, 111.1)` .. `(457853.9, 5439092.9,
  113.9)`.
- `triangulate`: `6` triangles, none skipped (the references are left out).

## `solid_unresolved_reference`

Suites: all except Rust (its `Solid::volume_3d` skips unresolved members and fails with `TooFewElements`; the bridge
API checks the members first, see [`lod2_solid_unresolved`](../conformance/fzk-haus.md#lod2_solid_unresolved)).

FZK LoD2, the building's `lod2_solid`: `volume_3d` fails with `UnresolvedReference`, message containing
`#PolyID7350_878_759628_120742` (the first member, only a reference).

## `triangulate_without_members`

FZK LoD2, the building's `lod2_solid`, whose shell only references its polygons: `points` empty, `compute_envelope`
none; `triangulate` fails with `InvalidArgument`, message containing `requires at least 1 element`.
