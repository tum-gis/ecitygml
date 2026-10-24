# ecitygml Kotlin bindings

Kotlin bindings for [ecitygml](../../../../README.md), generated with [Diplomat](https://github.com/rust-diplomat/diplomat) into `src/main` (package `io.github.tum_gis.ecitygml`, loaded via JNA).

```kotlin
import io.github.tum_gis.ecitygml.GmlReader

val cityModel = GmlReader.fromPath("model.gml").getOrThrow().finish().getOrThrow()
println(cityModel.cityObjectsLen())
```

See [`src/examples/`](src/examples) for more.

```sh
mise run build:bindings:kotlin
mise run test:bindings:kotlin
```

See the [ecitygml-ffi README](../../README.md) for details.
