# ecitygml JavaScript/TypeScript bindings

JavaScript/TypeScript bindings for [ecitygml](../../../../README.md), generated with [Diplomat](https://github.com/rust-diplomat/diplomat) into `lib/` and running on WebAssembly.

```ts
import { CitygmlFormat, GmlReader } from 'ecitygml';

const cityModel = new GmlReader(bytes, CitygmlFormat.Gml).finish();
console.log(cityModel.cityObjectsLen());
```

WebAssembly has no file system, so the reader takes the file's bytes. See [`examples/`](examples) for more.

```sh
mise run build:bindings:typescript
mise run test:bindings:typescript
```

See the [ecitygml-ffi README](../../README.md) for details.
