# ecitygml C++ bindings

C++17 bindings for [ecitygml](../../../../README.md), generated with [Diplomat](https://github.com/rust-diplomat/diplomat) into `include/` (namespace `ecitygml`).

```cpp
#include <ecitygml/CityModel.hpp>
#include <ecitygml/GmlReader.hpp>

auto reader = std::move(ecitygml::GmlReader::from_path(path).ok().value());
auto city_model = std::move(reader->finish().ok().value());
std::cout << city_model->city_objects_len() << "\n";
```

Error handling is left out above; see [`examples/`](examples) for complete programs.

```sh
mise run build:bindings:cpp
mise run test:bindings:cpp
```

See the [ecitygml-ffi README](../../README.md) for details.
