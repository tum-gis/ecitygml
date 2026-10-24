# Arena

Cases of `CityModelArena`, the index of a city model's objects by id. The FFI doesn't bind it yet.

## `arena_lookup`

Suites: Rust (`CityModelArena` isn't bound in the FFI yet).

`CityModelArena::from_city_model` of `<fixtures>/fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml` (read without
options): `iter_city_objects` `8`; `get_city_object_by_id` of the wall surface `GML_5856d7ad-5e34-498a-817b-9544bfbb1475`
finds it, with a `bounded_by` envelope.
