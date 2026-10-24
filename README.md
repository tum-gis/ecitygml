# ecitygml

A Rust library for reading, writing, and processing [CityGML](https://www.ogc.org/standards/citygml/) data, including an inspector GUI and a CLI.

![ecitygml inspector GUI](https://sensordb.org/assets/splash/ecitygml-splash.png)

Features:

- Nearly complete support for the CityGML 3.0 conceptual model (except Dynamizer, Versioning, and parts of Appearance)
- High-performance reading and writing of GML-encoded data, with on-the-fly (de)compression (`.gml.gz`, `.gml.zst`)
- Bindings for [C](crates/ecitygml-ffi/bindings/c), [C++](crates/ecitygml-ffi/bindings/cpp), [Python](crates/ecitygml-ffi/bindings/python), [Kotlin](crates/ecitygml-ffi/bindings/kotlin), [Dart](crates/ecitygml-ffi/bindings/dart), [C#](crates/ecitygml-ffi/bindings/dotnet), and [JavaScript/TypeScript](crates/ecitygml-ffi/bindings/typescript) (WebAssembly, runs in the browser)
- Geometry operations, including triangulation and spatial transforms (see [egml](https://github.com/tum-gis/egml))
- Arena representation that flattens the hierarchy for direct access to every feature
- In-memory BVH index for fast spatial queries of city objects by envelope or point

> Early stage of development. Developed by [Benedikt Schwab](https://www.asg.ed.tum.de/en/gis/our-team/staff/benedikt-schwab/) at the [TUM Chair of Geoinformatics](https://github.com/tum-gis). Contributions welcome.

---

## ecitygml-gui

A GUI for inspecting CitGML 3.0 datasets.

Download pre-built executables for your platform from the [release page](https://github.com/tum-gis/ecitygml/releases).

On macOS, you need to remove the quarantine attribute after downloading:

```sh
xattr -d com.apple.quarantine ./ecitygml-gui
```

From source:

```sh
cargo install ecitygml-gui@0.0.2-alpha.5 # replace with the latest version
```

---

## ecitygml (library)

A Rust library for reading, writing, and processing CityGML 3.0 data in your own application.

### Installation

```toml
[dependencies]
ecitygml = "0.0.2-alpha.5" # replace with the latest version
```

## License

Licensed under either of [MIT](LICENSE-MIT) or [Apache-2.0](LICENSE-APACHE) at your option.
