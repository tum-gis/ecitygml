# ecitygml Python bindings

Python bindings for ecitygml, generated with [Diplomat](https://github.com/rust-diplomat/diplomat)
(nanobind backend) from the bridges in `crates/ecitygml-ffi`. `src/` is generated
(`mise run generate:bindings`); `pyproject.toml`, `CMakeLists.txt`, `examples/` and `tests/` are
hand-written.

Build and test with `mise run build:bindings:python` and `mise run test:bindings:python`.

## Tests

- `test_city_model.py`, `test_examples.py`: the bindings' own tests and examples.
- The other `test_*.py` files are ported from the tests of the former PyO3 bindings (removed; see
  the git history), with the same file names (except `test_city_model.py` →
  `test_iter_features.py`) and expected values. `conftest.py` translates the former API: filters
  such as `iter_features(Building)` become `try_from`, boundaries are converted with
  `AbstractFeatureKindRef.from_space_boundary`, properties are unwrapped with `.object()`.

Objects returned by `try_from` don't keep their city model alive, so the tests keep every model
referenced (module-scoped fixtures or local variables).

### Not ported

Former tests that weren't ported, because they need something the Diplomat bindings don't have
(by design, or not in the Rust API):

| Missing | Former tests |
|---|---|
| Validating the indent (Rust's `Formatting::Indent` takes any byte), keyword-only options | parts of `test_writer.py` |
| Raising for relative geometries without a class (e.g. `MultiPoint`; `AbstractGeometryKind.geometry_type()` names any geometry) | `test_unbound_relative_geometry_raises` in `test_physical_space.py` |
| Resolving `xlink:href` references within a feature (e.g. the FZK LoD2 solid, which references its boundary polygons) | resolved-solid tests in `test_geometry_completeness.py` |
| Raising instead of skipping in triangulation: egml leaves out `xlink:href`-only members and lists failing ones (e.g. a polygon without exterior) in `Triangulation.skipped()` | parts of `test_geometry_completeness.py` |
| Filter arguments (`iter_features(FeatureType.Marking)`, `iter_city_objects(str)`) and their errors, iterating while the model is mutated (`city_objects_of` filters with `try_from` instead) | parts of `test_city_model.py` |
| `DirectPosition.coords` | parts of `test_geometry.py` |
| `feature_type()` on concrete classes (only feature refs and kinds have it) | feature-type tests, ported via `try_from` |
| Python conveniences: `repr`, `str`/`==` of `Code`, `pathlib.Path` arguments, keyword-only options, the `GenericAttribute` alias | `repr` tests in most files, parts of `test_code_lists.py`, `test_reader.py`, `test_city_object.py` |

Two behaviours differ from the former bindings: `iter_features()` also yields the city model itself, first
(as Rust does), and a missing file's or directory's error message doesn't name the path.

Writing to memory (`GmlWriter(format)` and `data()`) is disabled for Python: Diplomat's nanobind
backend returns byte slices as NumPy arrays, and without NumPy that conversion aborts the
interpreter. Python writes files with `GmlWriter.from_path`; the other languages have both.
