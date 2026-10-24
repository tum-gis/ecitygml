# ecitygml C bindings

C bindings for [ecitygml](../../../../README.md), generated with [Diplomat](https://github.com/rust-diplomat/diplomat) into `include/`.

```c
#include "CityModel.h"
#include "GmlReader.h"

ecitygml_GmlReader_from_path_result reader = ecitygml_GmlReader_from_path((DiplomatStringView){path, strlen(path)});
ecitygml_GmlReader_finish_result city_model = ecitygml_GmlReader_finish(reader.ok);
printf("%zu\n", ecitygml_CityModel_city_objects_len(city_model.ok));
ecitygml_CityModel_destroy(city_model.ok);
ecitygml_GmlReader_destroy(reader.ok);
```

Error handling is left out above; see [`examples/`](examples) for complete programs.

```sh
mise run build:bindings:c
mise run test:bindings:c
```

See the [ecitygml-ffi README](../../README.md) for details.
