# Iteration

Cases of the iterators the API returns (`iter_features` here, as all of them work alike): how far they go, what
happens when they are dropped early or run side by side, and how they fit each language. "FZK LoD3" is
`<fixtures>/fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml`, "ASAM road shape"
`<fixtures>/asam-opendrive/ASAM-UC_RoadShape.gml`. "`next`" is the iterator's own `next` (Python: `next(iterator)`,
Kotlin: `hasNext`/`next`, Dart: `moveNext`/`current`), "none" the end of the iteration in the language's form.

## `iterator_exhausted`

`iter_features` of FZK LoD3 yields `22` features, then none, and none again on a further `next`.

## `iterator_stopped_early`

ASAM road shape: an `iter_features` iterator is dropped (C: destroyed) after its first feature, the city model; a new
`iter_features` over the same model still yields all `11` features, and `city_objects_len` (Rust:
`city_object_members_len`) is still `1`.

## `iterators_independent`

Two `iter_features` iterators over the same FZK LoD3 model, advanced alternately (one feature from the first, one from
the second, …), each yield the same `22` feature types in the same order.

## `iterator_keeps_model_alive`

Suites: Python, TypeScript, Kotlin, .NET, Dart (garbage-collected; Rust's borrow checker rules the case out, and in C
and C++ the caller owns the model).

An `iter_features` iterator taken from a model read without keeping any other reference to it (after a garbage
collection, where the language can request one) still iterates the whole model: `4` of FZK LoD3's features are wall
surfaces (`WallSurface::try_from`).

## `native_iteration`

Suites: Rust, Python, Kotlin, Dart (their iterators are the language's iterators: `Iterator`, the iterator protocol,
`kotlin.collections.Iterator`, `dart:core` `Iterator`).

A `for` loop (Dart: `while (iterator.moveNext())`) over `iter_features` of FZK LoD3 visits `22` features, the first of
feature type `CityModel`.
