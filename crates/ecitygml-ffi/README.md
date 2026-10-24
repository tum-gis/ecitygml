# ecitygml-ffi

Language bindings for ecitygml, generated with [Diplomat](https://github.com/rust-diplomat/diplomat). Currently C, C++, Python, Kotlin,
TypeScript, C# (.NET) and Dart.

The library is at an early stage of development.

## Generating the bindings

Each `ffi` module in `src/` is a Diplomat bridge. `diplomat-tool` (same version as the `diplomat` crate, currently
0.16.1) generates the bindings into [`bindings/c/include`](bindings/c/include), [`bindings/cpp/include`](bindings/cpp/include) and
[`bindings/python/src`](bindings/python/src), [`bindings/kotlin/src/main`](bindings/kotlin/src/main) and
[`bindings/typescript/lib`](bindings/typescript/lib), [`bindings/dotnet/src`](bindings/dotnet/src) and
[`bindings/dart/lib/src`](bindings/dart/lib/src), configured by
[`config.toml`](config.toml):

```sh
mise run generate:bindings    # all languages (c, cpp, nanobind, kotlin, js, dotnet, dart)
mise run check:bindings       # fails if the committed bindings are out of date (for CI)
mise run build:bindings:c     # builds the library and bindings/c (CMake: Unity unit tests with ASan/UBSan, examples)
mise run test:bindings:c      # CTest: unit tests and examples (total traffic-space volume: 1260 m^3)
mise run build:bindings:cpp   # builds the library and bindings/cpp (CMake: Catch2 unit tests, examples)
mise run test:bindings:cpp    # CTest: unit tests and examples
mise run build:bindings:python   # static library + nanobind extension into bindings/python/.venv (CMake, uv)
mise run test:bindings:python    # pytest
mise run build:bindings:kotlin   # Gradle (JDK 21 and Gradle 9.8 installed by mise)
mise run test:bindings:kotlin    # JUnit, loads target/<profile>/libecitygml_ffi via JNA
mise run build:bindings:typescript   # WebAssembly module (wasm32-unknown-unknown)
mise run test:bindings:typescript    # node --test (Node >= 22.18 runs the .ts tests directly)
mise run build:bindings:dotnet   # C# library, examples and xUnit tests (.NET 10 SDK installed by mise)
mise run test:bindings:dotnet    # dotnet test (also runs the examples), loads target/<profile>/libecitygml_ffi
mise run build:bindings:dart     # library and dart pub get (Dart 3.13 installed by mise)
mise run test:bindings:dart      # dart analyze and dart test; the build hook bundles target/<profile>/libecitygml_ffi
```

Each `test:bindings:<language>` builds its bindings first; `mise run 'test:bindings:*'` builds and tests all of them.
All of them use the debug build of the library (`target/debug`); with `--release` (`-r`), e.g.
`mise run test:bindings:c --release`, they build and use the release build (`target/release`) instead. C and C++
are built in `target/bindings-<language>` (debug) or `target/bindings-<language>-release`.

The generated bindings are committed and the build tasks use them as they are: run `generate:bindings` whenever a
bridge in `src/` changes. CI fails via `check:bindings` if they are out of date. Only `generate:bindings` needs
`diplomat-tool`, which mise installs (task `tools`).

## Usage

### C++ (`-I bindings/cpp/include`, C++17, namespace `ecitygml`)

```cpp
#include <ecitygml/CityModel.hpp>
#include <ecitygml/Error.hpp>
#include <ecitygml/GmlReader.hpp>

// each step returns diplomat::result<unique_ptr<…>, unique_ptr<Error>>; check is_err() as below
auto reader = std::move(ecitygml::GmlReader::from_path(path).ok().value());
reader->with_rebuild_object_bounds(true);   // optional
auto result = reader->finish();
if (result.is_err()) {
    std::cerr << std::move(result).err().value()->message() << "\n";
    return 1;
}
auto city_model = std::move(std::move(result).ok().value());
std::cout << city_model->city_objects_len() << "\n";
```

See [`bindings/cpp/examples/01_read_city_model.cpp`](bindings/cpp/examples/01_read_city_model.cpp). The C++ headers declare the C functions themselves, so C++ users don't
need `bindings/c`. `bindings/cpp` also holds the hand-written `CMakeLists.txt`, unit tests (`tests/`) and examples
(`examples/`); only `include/` is generated.

### Python (`bindings/python`, nanobind)

```python
from ecitygml import GmlReader

city_model = GmlReader.from_path("model.gml").finish()   # raises Exception(Error); str(error) is the message
print(city_model.city_objects_len())
```

Examples in `examples/` (see [Examples](#examples)), run by `tests/test_examples.py`.

The extension statically links the Rust library (`cargo build -p ecitygml-ffi`; the release build with
`-C cmake.define.ECITYGML_FFI_LIBRARY_DIR=<repository>/target/release`, as `mise run build:bindings:python --release` passes) and is built by
scikit-build-core from `pyproject.toml`/`CMakeLists.txt` (hand-written; only `src/` is generated). It targets the
stable ABI (CPython ≥ 3.12), needs a C++20 compiler and ships a type stub (`ecitygml.pyi`). nanobind is pinned to 2.4.0
because the generated code uses nanobind internals. The venv uses a uv-managed Python (`--managed-python`), which ships the headers
nanobind needs; scikit-build-core fetches CMake and Ninja from PyPI if they are missing.

### Kotlin (`bindings/kotlin`, package `io.github.tum_gis.ecitygml`)

```kotlin
val cityModel = GmlReader.fromPath("model.gml").getOrThrow().finish().getOrThrow()   // exceptions are `Error`s
println(cityModel.cityObjectsLen())
```

Examples in `src/examples` (see [Examples](#examples), e.g. `gradle run01ReadCityModel --args="model.gml"`),
run by the tests as well.

The JVM loads `libecitygml_ffi` with JNA (`jna.library.path`). `build.gradle.kts` and `src/test` are hand-written;
only `src/main` is generated. An `Error`'s text comes from `message()` (its `Throwable.message` is generic).

### TypeScript / JavaScript (`bindings/typescript`, WebAssembly)

```ts
import { CitygmlFormat, GmlReader } from 'ecitygml';

const cityModel = new GmlReader(bytes, CitygmlFormat.Gml).finish();   // throws an Error whose `cause` is ours
console.log(cityModel.cityObjectsLen());
```

Examples in `examples/` (see [Examples](#examples), e.g. `node examples/01_read_city_model.ts model.gml`),
run by `test/examples.test.ts` as well.

Diplomat's JS backend generates ES modules with TypeScript declarations into `lib/`; `package.json`,
`diplomat.config.mjs` (path of the `.wasm`) and `test/` are hand-written.

- There is no file system: read with `new GmlReader(data, format)` (`.gml`, `.gml.gz`, `.gml.zst`); `fromPath` fails
  with `Io`. The constructor exists in every language (C `ecitygml_GmlReader_new`, C++/Kotlin `GmlReader::create`).
- The build is pure Rust and needs no C toolchain: on WebAssembly, ecitygml-io uses `ruzstd` instead of zstd's C library
  (writing then uses ruzstd's fastest level, about zstd level 1). The module has no imports.
- The deserializer runs on the main thread (no threads in WebAssembly), with a 32 MiB stack set at link time.
- Iterators have `next()` but no `[Symbol.iterator]`; an `Error`'s message is `toString()`.

### C (`-I bindings/c/include`)

```c
#include "CityModel.h"
#include "Error.h"
#include "GmlReader.h"

ecitygml_GmlReader_from_path_result reader = ecitygml_GmlReader_from_path((DiplomatStringView){path, strlen(path)});
if (!reader.is_ok) { /* ecitygml_Error_kind/_message(reader.err, …); ecitygml_Error_destroy(reader.err) */ }
ecitygml_GmlReader_finish_result city_model = ecitygml_GmlReader_finish(reader.ok);
ecitygml_GmlReader_destroy(reader.ok);
if (!city_model.is_ok) { /* same for city_model.err */ }
printf("%zu\n", ecitygml_CityModel_city_objects_len(city_model.ok));
ecitygml_CityModel_destroy(city_model.ok);
```

See [`bindings/c/examples/01_read_city_model.c`](bindings/c/examples/01_read_city_model.c) and the other
[examples](#examples), which every language has.

Reading mirrors ecitygml-io's `GmlReader` (`from_path`, `with_rebuild_object_bounds`, `finish`). Rust's builder methods
take the reader by value, which Diplomat can't express: here they modify it in place, and `finish` works only once.

C conventions:

- Functions are named `ecitygml_<Type>_<method>`; types keep their Rust names (`CityModel`, `Error`).
- Owned objects (`CityModel*`, `Error*`) are freed with `ecitygml_<Type>_destroy`.
- Fallible functions return a `*_result` struct with `is_ok` and either `ok` or `err`.
- Strings are passed as `DiplomatStringView` (pointer + length, UTF-8) and returned through a `DiplomatWrite`
  (e.g. `diplomat_buffer_write_create`).

### C# / .NET (`bindings/dotnet`, namespace `Ecitygml`, .NET 10)

```csharp
using System.Text;
using Ecitygml;

var cityModel = GmlReader.FromPath(Encoding.UTF8.GetBytes("model.gml")).Finish();   // throws ErrorException
Console.WriteLine(cityModel.CityObjectsLen());
var features = cityModel.IterFeatures();
for (var feature = features.Next(); feature != null; feature = features.Next()) { /* Building.TryFrom(feature) … */ }
```

`Ecitygml.csproj` compiles the generated `src/` (`AllowUnsafeBlocks`) and copies `libecitygml_ffi` next to every
project referencing it (the generated code loads it with `DllImport`): the xUnit tests in `tests/` and the examples in
`examples/`, a console application (see [Examples](#examples), e.g.
`dotnet run --project examples -- 01_read_city_model model.gml`), which the tests run as well.

- Errors are thrown as `ErrorException`; its `Inner` is the ecitygml `Error` (`Kind()`, `Message()`).
- Absent values are C# nullable types. Iterators have `Next()` (null at the end) but are not `IEnumerable`.
- Paths are UTF-8 `byte[]`, and borrowed strings are `DiplomatBorrowedSpan<byte>`: copy them with `Clone()` and
  decode with `Encoding.UTF8.GetString`.
- Diplomat's .NET backend can't return an optional borrowed string yet, so `Code.code_space`, `HRef.local_id`,
  `ImplicitGeometry.library_object` and `ExternalReference.information_system`/`relation_type` are disabled for .NET
  (`#[diplomat::attr(dotnet, disable)]`).

### Dart (`bindings/dart`, package `ecitygml`, Dart ≥ 3.13)

```dart
import 'package:ecitygml/ecitygml.dart';

final cityModel = GmlReader.fromPath('model.gml').finish();   // throws the ecitygml Error (kind(), message())
print(cityModel.cityObjectsLen());
```

Diplomat's Dart backend generates `lib/src` (`@Native` functions); `pubspec.yaml`, `lib/ecitygml.dart`,
`hook/build.dart`, `test/` and `example/` are hand-written. The build hook (native assets) registers
`target/debug/libecitygml_ffi` as the code asset the generated functions resolve against, so `dart test` and
`dart run` find it without a library path; build it first (`cargo build -p ecitygml-ffi`). Hooks don't see the
environment: `mise run build:bindings:dart --release` writes `release` to `target/bindings-dart/profile`, which makes
the hook take `target/release/libecitygml_ffi` instead (until the task runs again without `--release`).

- `class` is reserved in Dart, so the `class` getters are `classifier()` (`#[diplomat::attr(dart, rename = ...)]`).
- Iterators implement `Iterator` (`moveNext()`/`current`) but not `Iterable`; the tests and examples wrap them
  with a `sync*` generator. Native memory is freed by finalizers; borrowed objects keep their owner alive.
- Borrowed objects are views into the model, e.g. an envelope's `lowerCorner()` moves with `applyTranslation`: copy
  the values you need before modifying the model.
- Examples in `example/` (see [Examples](#examples), e.g. `dart run example/01_read_city_model.dart model.gml`) and
  snippets in `example/snippets/`, run by `test/examples_test.dart` and `test/snippets_test.dart`. Dart has no union
  types, so the examples pass the getters of wall, roof and ground surfaces (or traffic spaces) separately.

## Examples

Every language has the same examples, with the same command-line interface and output. They are
numbered in the order to learn them: each builds on the previous ones. Each example's header
explains what it shows; the comments point out how the language handles ownership, errors and
absent values.

| Example | Shows |
|---|---|
| `01_read_city_model` | Reading a file, error handling, the city model's members, city objects and envelope |
| `02_list_features` | `iter_features()`, `feature_type()`, converting features with `try_from` |
| `03_building_report` | Properties (`object()`/`href()`), code lists, measures, dates, generic attributes, boundaries with their doors and windows |
| `04_road_network` | The transportation hierarchy (road, section, intersection, traffic spaces, traffic areas): centre-line lengths, areas, solid volumes and totals, e.g. the total traffic-space volume |
| `05_measure_geometry` | Areas, triangle counts and solid volumes of buildings; handling a calculation that fails (a solid made of unresolved `xlink:href` references) |
| `06_export_obj` | Triangulating geometry and writing your own file format (Wavefront OBJ) |
| `07_convert` | Writing CityGML with `GmlWriter`: format from the extension (`.gml`, `.gml.gz`, `.gml.zst`), formatting, reading back |

All take the path of a CityGML file (`06_export_obj` and `07_convert` also the output path) and
exit with 0, 1 on errors (message on standard error) and 2 on wrong arguments. The fixtures are in
`tests/fixtures/<dataset>/` at the repository root, one folder per source dataset (see its README).

| Language | Source | Run |
|---|---|---|
| C | `bindings/c/examples/<example>.c`, e.g. `01_read_city_model.c` | built by `mise run build:bindings:c`: `target/bindings-c/<example> model.gml` |
| C++ | `bindings/cpp/examples/<example>.cpp` | built by `mise run build:bindings:cpp`: `target/bindings-cpp/<example> model.gml` |
| Python | `bindings/python/examples/<example>.py` | `python examples/<example>.py model.gml` |
| Kotlin | `bindings/kotlin/src/examples/…/<NN>_<Example>.kt`, e.g. `01_ReadCityModel.kt` | `gradle run<NN><Example> --args="model.gml"`, e.g. `run01ReadCityModel` |
| TypeScript | `bindings/typescript/examples/<example>.ts` | `node examples/<example>.ts model.gml` (Node ≥ 22.18) |
| C# | `bindings/dotnet/examples/<NN>_<Example>.cs`, e.g. `01_ReadCityModel.cs` | `dotnet run --project examples -- <example> model.gml` |
| Dart | `bindings/dart/example/<example>.dart` | `dart run example/<example>.dart model.gml` |

Differences between the languages are limited to what the language requires: TypeScript runs on
WebAssembly without a file system, so it reads and writes files with Node and hands the bytes to
the bindings (`07_convert` writes with `new GmlWriter(format)` and `data()`); Python can't return
byte slices without NumPy, so it writes with `GmlWriter.from_path` like C, C++, Kotlin and C#.

### Expected output

[`tests/expected/examples/<example>/<dataset>/<fixture>.txt`](../../tests/expected/examples) at the repository root is
what the example prints for `tests/fixtures/<dataset>/<fixture>.gml`;
`tests/expected/examples/06_export_obj/<dataset>/<fixture>.obj` is the file it writes. Every language's tests discover these files and compare (C and C++ under CTest, via
`bindings/{c,cpp}/examples/CMakeLists.txt` and `cmake/compare_output.cmake`), so the languages can't drift apart, and
a new test case is just a new file. The Rust examples in [`crates/ecitygml/examples`](../ecitygml/examples) are the
reference and are checked against the same files. When changing an example, change it in every language and update
its expected output.

### Snippets

Snippets are short programs that give a first impression of each language, e.g. for a README: not examples to
learn from, so they have no comments. Every language has the same snippets as Rust
([`crates/ecitygml/examples/snippets`](../ecitygml/examples/snippets)), which run like the examples, against
`tests/expected/snippets/<snippet>/<dataset>/<fixture>.txt` at the repository root:

| Snippet | Computes | Fixture |
|---|---|---|
| `compute_wall_surface_area` | The total LoD2 area of all wall surfaces | `fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3` |
| `compute_traffic_space_volume` | The total LoD2 solid volume of all traffic spaces (collects them first, as in Rust) | `asam-opendrive/ASAM-UC_RoadShape` |
| `compute_total_building_height` | The sum of the building heights from `lowestGroundPoint` to `topOfConstruction` that are measured and in `urn:adv:uom:m` | `tum-main-entrance/TUM-Main-Entrance` |
| `translate_to_local_coordinates` | Translates the city model so that the center of its envelope is the origin, and writes it (second argument) | `fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3` |

| Language | Snippet files | Run by |
|---|---|---|
| C, C++ | `bindings/{c,cpp}/examples/snippets/<snippet>.{c,cpp}` | CTest, via `bindings/{c,cpp}/examples/snippets/CMakeLists.txt` |
| Python | `bindings/python/examples/snippets/<snippet>.py` | `tests/test_snippets.py` |
| Kotlin | `bindings/kotlin/src/examples/…/snippets/ComputeWallSurfaceArea.kt` etc. (`gradle runComputeWallSurfaceArea --args="model.gml"`) | `SnippetsTest.kt` |
| TypeScript | `bindings/typescript/examples/snippets/<snippet>.ts` (imports the package as `ecitygml`) | `test/snippets.test.ts` |
| C# | `bindings/dotnet/examples/snippets/ComputeWallSurfaceArea.cs` etc., file-based apps (`dotnet run --file …`) | `tests/SnippetsTests.cs` |
| Dart | `bindings/dart/example/snippets/<snippet>.dart` (`dart run example/snippets/<snippet>.dart model.gml`) | `test/snippets_test.dart` |

Each reads `model.gml`, or the file given as its first argument. A snippet that writes a file takes its path as the
second argument; the tests compare the written file byte for byte with `<fixture><extension>` next to the expected
output. They run every snippet in a process of its own (Kotlin: a JVM of its own), because the ids the reader
generates for features without `gml:id` are numbered per process. A new snippet needs an entry in `SnippetsTest.kt`
and `SnippetsTests.cs` (their file names are PascalCase); the other languages find it by its file name.

## What is bound

- Reading: `GmlReader` (`from_path`, `with_rebuild_object_bounds`, `finish`).
- `CityModel`: `city_objects_len`, `iter_features` (yields `AbstractFeatureKindRef`, with `feature_type()`),
  `city_object_members` (yields `AbstractCityObjectProperty`; its `object()` is an `AbstractCityObjectKind`, converted
  with `AbstractCityObjectKindRef::from_city_object` and `AbstractFeatureKindRef::from_city_object`).
- Transformations (egml `ApplyTransform`, macro `impl_apply_transform_methods!`): `CityModel::apply_translation`
  (`Vector3`) and `apply_scale` (`Scale3`; the center of a model comes from `Envelope::center`), which move the geometry and every stored envelope. `Vector3` and
  `Scale3` are structs, passed by value (C: `(Vector3){x, y, z}`, TypeScript: `{ x, y, z }`). Only on `CityModel`:
  everything below it is reached through read-only references. Rotations, isometries and general transforms are
  not bound yet.
- `TrafficSpace`: reached with `TrafficSpace::try_from(&feature)` (Rust: `<&TrafficSpace>::try_from`); own getters
  `class`, `functions`, `usages`, `granularity`, `traffic_direction`, `occupancies`.
- Abstract types, generated into every type that derives from them (one macro per abstract type; each type invokes
  the macro of every ancestor itself, because Diplomat expands macros only one level deep):
  AbstractCityObject (`relative_to_terrain`, `relative_to_water`), AbstractSpace (`space_type`, `lod1/2/3_solid`),
  AbstractPhysicalSpace and AbstractUnoccupiedSpace (no getters yet), AbstractFeatureWithLifespan (lifespan dates),
  AbstractFeature (`feature_id`), egml AbstractFeature (`bounded_by`).
- Geometry: `SolidProperty` (`object`, `href` → `HRef`), `Solid` (`volume_3d`, `compute_envelope`, `points`).
  `Solid::volume_3d` is stricter than Rust: it fails with `UnresolvedReference` for `xlink:href`-only shell members
  and with `InvalidArgument` for members that can't be triangulated (Rust skips them, or panics on some), so a
  volume is never computed from an incomplete shell.
- Lists (`&[T]` in Rust) are returned as iterators (`next()`; Python/Kotlin/JS iterate them directly).
- Not bound yet: geometry beyond solids (`Shell` and its surfaces, multi-surfaces, multi-curves, terrain intersection curves), volumes, areas,
  boundaries, point clouds, external references, generic attributes, appearances, relations, traffic-space
  predecessors/successors and clearance spaces, other feature types.

Python note: Diplomat's Python enums compare with `==` but don't hash consistently; don't put them in sets or dicts.

## Contributing

The library is developed at the [TUM Chair of Geoinformatics](https://github.com/tum-gis) and contributions are highly welcome.
