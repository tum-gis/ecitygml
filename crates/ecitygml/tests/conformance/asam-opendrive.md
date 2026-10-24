# ASAM OpenDRIVE

Cases for the files in [`tests/fixtures/asam-opendrive`](../../../../tests/fixtures/asam-opendrive), grouped per file.
Floating point values are compared within ±1e-6 (absolute); lists are in document order; "the road" is the file's
only road (`iter_features` + `Road::try_from`). rtron derives the UUIDs from the OpenDRIVE ids, so both files share
some of them (the road, the first section, its traffic spaces and traffic areas). Ids are `feature_id`s; a
reference's id is the local id of its `href` (`Reference::from_traffic_space_reference`); .NET, where `HRef::local_id`
isn't bound, takes it from the written href (`#<id>`).

# `ASAM-UC_RoadShape.gml`

## `road_shape_city_model`

- `city_objects_len` (bindings) / `city_object_members_len` (Rust): `1`.
- `iter_features` (feature types): `CityModel`, `Road`, `Section`, `TrafficSpace`, `TrafficArea`, `TrafficSpace`,
  `TrafficArea`, `AuxiliaryTrafficSpace`, `AuxiliaryTrafficArea`, `AuxiliaryTrafficSpace`, `AuxiliaryTrafficArea`.
- `iter_city_objects` (feature types): the same without the `CityModel`.
- `bounded_by` → envelope: lower corner `(-50.21567184593757, -2.4442507170297514, 0.0)`, upper corner
  `(-13.007511850967884, 29.053746110395082, 4.95)`.

## `road_shape_road`

- `feature_id`: `UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f`.
- `class`, `traffic_direction`: none; `functions`, `usages`, `intersections`, `occupancies`, `traffic_spaces`,
  `auxiliary_traffic_spaces`, `markings`, `holes`: empty (the file puts all spaces into the section).
- `sections`: exactly one, inline (`href` none), `feature_id` `UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29`.

## `road_shape_section`

The road's section:

- `class`, `traffic_direction`, `lod0_multi_curve`, `lod1_solid`: none; `markings`, `holes`: empty.
- `traffic_spaces`: inline, `feature_id`s `UUID_ae81947d-a661-3678-a5ee-eed58b68694f`,
  `UUID_6e4de408-1e54-3869-b7ce-1be3f2261421`.
- `auxiliary_traffic_spaces`: inline, `feature_id`s `UUID_12298df9-4982-33a8-ab4a-9953410bbff7`,
  `UUID_f8211bb5-0ce8-36e1-9b84-73d30114f578`.

## `road_shape_traffic_spaces`

The section's traffic spaces:

- `traffic_direction`: `Backwards`, `Forwards`.
- Each: `granularity` `Lane`, `class` none, `functions` `["1"]`, `usages` `["2"]` (code values), `occupancies`
  empty, `space_type` `Open`, `relative_to_terrain` and `creation_date` none, `predecessors` and `successors`
  empty; `boundaries`: exactly one, inline, a `TrafficArea`.

## `road_shape_generic_attributes`

The first traffic space's `generic_attributes` (name, kind, value): `identifier_laneId` int `1`,
`identifier_laneSectionId` int `0`, `identifier_roadId` string `1`, `opendrive_road_length` double `40.0`,
`opendrive_road_rule` string `RIGHT_HAND_TRAFFIC`, `opendrive_laneSection_curvePositionStart` double `0.0`,
`opendrive_lane_type` string `DRIVING`, `opendrive_lane_level` string `false`.

## `road_shape_traffic_space_geometry`

The section's traffic spaces:

- `lod2_solid` → `volume_3d`: `720.0`, `540.0`.
- `lod2_multi_curve`: inline, `length_3d` `40.0`; exactly one curve member, a line string with `2` points and a
  `length_3d` of `40.0`.
- `lod0_multi_curve`, `lod3_multi_curve`, `lod1_solid`, `lod3_solid`, `lod2_multi_surface`: none.

## `road_shape_traffic_areas`

The traffic areas bounding the section's traffic spaces:

- `feature_id`: `UUID_8625bf6f-57cb-3ddf-8fd1-6674b756a2e2`, `UUID_dc110e80-dadc-3c87-b864-2854cc0cb39a`.
- Each: first name `Lane`, `class` none, `functions` `["1"]`, `usages` `["2"]`, `surface_material` none,
  `lod0_multi_curve`, `lod0_multi_surface`, `lod1_multi_surface`, `lod3_multi_surface`, `relative_to_terrain`:
  none; `lod2_multi_surface` with exactly one surface member.
- `lod2_multi_surface` → `area_3d`: `160.79800993793438`, `121.34249049694012`.

## `road_shape_auxiliary_traffic`

- The section's auxiliary traffic spaces, each: `granularity` `Lane`, `class` none, `functions` and `usages`
  empty, `space_type` `Open`, `lod2_solid` → `volume_3d` `100.0`, `lod2_multi_curve` → `length_3d` `40.0`;
  `boundaries`: exactly one, an `AuxiliaryTrafficArea`.
- Those auxiliary traffic areas: `feature_id` `UUID_4890681a-e9fa-365e-a676-f89afb453f9b`,
  `UUID_d3c71d48-5222-355e-8037-9677aee30d7e`; each first name `Lane`, `class` none, `functions` and `usages`
  empty, `surface_material` none, `lod2_multi_surface` → `area_3d` `40.0`.

# `ASAM-Ex_Bidirectional_Junction.gml`

## `junction_city_model`

- `city_objects_len` (bindings) / `city_object_members_len` (Rust): `1`.
- `iter_features` (feature types): `CityModel`, `Road`, `Section`, `TrafficSpace`, `TrafficArea`, `TrafficSpace`,
  `TrafficArea`, `Marking`, `Marking`, `Marking`, `Marking`, `Section`, `TrafficSpace`, `TrafficArea`, `Section`,
  `TrafficSpace`, `TrafficArea`, `Intersection`, `TrafficSpace`, `TrafficArea`, `TrafficSpace`, `TrafficArea`,
  `TrafficSpace`, `TrafficArea`.
- `iter_city_objects`: `23`.
- `bounded_by` → envelope: lower corner `(-52.66282419815818, -37.4146115571896, 0.0)`, upper corner
  `(34.10760429351533, 6.338805461729647, 0.0)`.

## `junction_road`

- `feature_id`: `UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f`.
- `sections`: inline, `feature_id`s `UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29`,
  `UUID_ef20f165-2564-373a-a5f8-98fd15f1ae69`, `UUID_4799566b-daf4-3135-aa9d-ec1b34a9167d`; their
  `traffic_spaces`: `2`, `1`, `1`; `markings`: `4`, `0`, `0`; `auxiliary_traffic_spaces`: empty.
- `intersections`: exactly one, inline, `feature_id` `UUID_47b7678d-e8b1-36ca-90b6-5b86cc859571`, `class` none,
  `traffic_spaces` `UUID_656f23c9-92b6-3c98-a1bf-40b5f2625b13`, `UUID_86f8df09-c972-332b-a279-636373ce4e0c`,
  `UUID_144a6807-5844-32b2-bb34-8b2671b1afaa`.

## `junction_traffic_spaces`

The traffic spaces (`iter_features` + `TrafficSpace::try_from`):

- `feature_id`: `UUID_ae81947d-a661-3678-a5ee-eed58b68694f`, `UUID_6e4de408-1e54-3869-b7ce-1be3f2261421`,
  `UUID_9582b02f-5cc7-38f8-b79c-a3a18b31856c`, `UUID_c772e261-27f1-30b6-8a94-1ccf23e71a74`,
  `UUID_656f23c9-92b6-3c98-a1bf-40b5f2625b13`, `UUID_86f8df09-c972-332b-a279-636373ce4e0c`,
  `UUID_144a6807-5844-32b2-bb34-8b2671b1afaa`.
- `traffic_direction`: `Backwards`, then `Forwards` for all others; `lod2_solid`: none.
- `lod2_multi_curve`: one line string each, with `9`, `9`, `5`, `6`, `7`, `8`, `7` points; `length_3d`
  `36.74683751297985`, `36.74683751297985`, `20.0`, `21.746217945006258`, `26.761532846607814`,
  `30.210435770102656`, `30.0`.

## `junction_traffic_areas`

The traffic areas (`iter_features` + `TrafficArea::try_from`), `lod2_multi_surface`: surface members `8`, `8`, `4`,
`5`, `6`, `7`, `6`; `area_3d` `112.81279116484816`, `112.81279116484816`, `61.4`, `66.76088909116919`,
`81.22157625123039`, `92.69041581703632`, `92.1`.

## `junction_traffic_space_links`

`predecessors` / `successors` (local ids) of the traffic spaces, in the order of `junction_traffic_spaces`:

| Traffic space | `predecessors` | `successors` |
|---|---|---|
| `UUID_ae81947d-…` | — | — |
| `UUID_6e4de408-…` | — | `UUID_144a6807-5844-32b2-bb34-8b2671b1afaa` |
| `UUID_9582b02f-…` | `UUID_656f23c9-92b6-3c98-a1bf-40b5f2625b13`, `UUID_86f8df09-c972-332b-a279-636373ce4e0c` | — |
| `UUID_c772e261-…` | — | `UUID_656f23c9-92b6-3c98-a1bf-40b5f2625b13` |
| `UUID_656f23c9-…` | `UUID_c772e261-27f1-30b6-8a94-1ccf23e71a74` | `UUID_9582b02f-5cc7-38f8-b79c-a3a18b31856c` |
| `UUID_86f8df09-…` | `UUID_d7d4aa5a-88c9-328d-9151-a6c043e57d7f` (not in the file) | `UUID_ae81947d-a661-3678-a5ee-eed58b68694f` |
| `UUID_144a6807-…` | `UUID_6e4de408-1e54-3869-b7ce-1be3f2261421` | `UUID_9582b02f-5cc7-38f8-b79c-a3a18b31856c` |

## `junction_markings`

The first section's `markings`: inline; each first name `RoadMarking`, `class` none, `lod0_multi_surface` and
`lod3_multi_surface` none, `lod2_multi_surface` with exactly one surface member; `area_3d` `0.48`, `0.48`, `0.48`,
`0.08962050155758661`.
