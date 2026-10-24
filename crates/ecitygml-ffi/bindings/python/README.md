# ecitygml Python bindings

Python bindings for [ecitygml](../../../../README.md), generated with [Diplomat](https://github.com/rust-diplomat/diplomat) (nanobind) into `src/`. Requires CPython ≥ 3.12.

```python
from ecitygml import GmlReader

city_model = GmlReader.from_path("model.gml").finish()
print(city_model.city_objects_len())
```

See [`examples/`](examples) for more.

```sh
mise run build:bindings:python
mise run test:bindings:python
```

See the [ecitygml-ffi README](../../README.md) for details.
