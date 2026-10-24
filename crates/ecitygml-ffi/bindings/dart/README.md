# ecitygml Dart bindings

Dart bindings for [ecitygml](../../../../README.md), generated with [Diplomat](https://github.com/rust-diplomat/diplomat) into `lib/src`. Requires Dart ≥ 3.13.

```dart
import 'package:ecitygml/ecitygml.dart';

final cityModel = GmlReader.fromPath('model.gml').finish();
print(cityModel.cityObjectsLen());
```

See [`example/`](example) for more.

```sh
mise run build:bindings:dart
mise run test:bindings:dart
```

See the [ecitygml-ffi README](../../README.md) for details.
