# Conformance

The conformance suite: the same fixture tests in every implementation, i.e. the Rust library (reading and
processing), its FFI API and each binding. One case list per fixture dataset (`<dataset>.md` in this folder, named like its
folder in [`tests/fixtures`](../../../../tests/fixtures)) defines the cases; every suite implements exactly these, nothing more and nothing
less. `mise run check:cases` enforces it for this suite and the [API suite](../api/README.md)
([`crates/ecitygml/tests/case_list_check.rs`](../case_list_check.rs), also part of `cargo test`).

## Suites

| Suite | Folder | File per dataset (here `fzk-haus`) |
|---|---|---|
| Rust | `crates/ecitygml/tests/conformance/` | `fzk_haus.rs` |
| Rust FFI | `crates/ecitygml-ffi/tests/conformance/` | `fzk_haus.rs` |
| C | `crates/ecitygml-ffi/bindings/c/tests/conformance/` | `test_fzk_haus.c` |
| C++ | `crates/ecitygml-ffi/bindings/cpp/tests/conformance/` | `test_fzk_haus.cpp` |
| Python | `crates/ecitygml-ffi/bindings/python/tests/conformance/` | `test_fzk_haus.py` |
| TypeScript | `crates/ecitygml-ffi/bindings/typescript/test/conformance/` | `fzk_haus.test.ts` |
| Kotlin | `crates/ecitygml-ffi/bindings/kotlin/src/test/kotlin/io/github/tum_gis/ecitygml/conformance/` | `FzkHausTest.kt` |
| .NET | `crates/ecitygml-ffi/bindings/dotnet/tests/Conformance/` | `FzkHausTests.cs` |
| Dart | `crates/ecitygml-ffi/bindings/dart/test/conformance/` | `fzk_haus_test.dart` |

The dataset name becomes `snake_case` (`fzk-haus-citygml-3.0` → `fzk_haus_citygml_3_0`) or `PascalCase`
(`FzkHausCitygml30`).

## Rules

- **Only conformance cases.** A suite's `conformance/` folder holds the tests of the case lists and their helpers,
  nothing else. Behaviour and language-specific tests (ownership, error mapping, iterator protocols, lifetimes)
  belong to the [API suite](../api/README.md).
- **Same cases, idiomatic tests.** Each case is an ordinary unit test in the suite's style; its name is the case id
  in that language's naming style: `building_count` → `fn building_count`, `test_building_count`,
  `"Building count"`, `'building count'`, `buildingCount`, `BuildingCount`.
- **Same assertions.** A case asserts exactly what its entry lists, through the public API of each suite.
- **Scoped cases.** A case runs in every suite unless its first line is `Suites:` followed by the suites that run it
  or by `all except` and the suites that don't, with the reason (as in the [API suite](../api/README.md#rules)). In
  this suite the reason is always a gap: a getter a suite doesn't expose (yet). Keep the unscoped case for what every
  suite reaches and put the rest into a separate, scoped case (`bridge_attributes` / `bridge_is_movable`).
- **Fixtures, unchanged.** Cases read the files in `tests/fixtures` unchanged; content injected into a fixture is not
  a conformance case. Real data first: the hand-written, schema-valid `tests/fixtures/synthetic` only covers what no
  real fixture has (its case list is [`synthetic.md`](synthetic.md)). The hand-written `tests/fixtures/invalid` is
  input for the API suite only.

## Case lists

A case list `<dataset>.md` (e.g. [`fzk-haus.md`](fzk-haus.md)) has one section per fixture file of the dataset,
and in it one section per case:

````markdown
# `FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml`

## `lod2_boundary_surfaces`

- `boundaries` (feature types): `WallSurface`, `WallSurface`, …
````

The case heading is the case id (`snake_case`, in backticks), prefixed by the fixture file it reads (`lod2_…`), so
ids stay unique within the dataset; the text lists the expected values. The list's introduction states its
conventions, e.g. the floating point tolerance. The suites group the tests per fixture file in the same way (a Rust
module, a Python class, a `describe`/`group`, a nested JUnit or xUnit class, a Catch2 tag) and read each file once
where the language allows it.
