# ecitygml C# bindings

C# bindings for [ecitygml](../../../../README.md), generated with [Diplomat](https://github.com/rust-diplomat/diplomat) into `src/` (namespace `Ecitygml`). Requires .NET 10.

```csharp
using System.Text;
using Ecitygml;

var cityModel = GmlReader.FromPath(Encoding.UTF8.GetBytes("model.gml")).Finish();
Console.WriteLine(cityModel.CityObjectsLen());
```

See [`examples/`](examples) for more.

```sh
mise run build:bindings:dotnet
mise run test:bindings:dotnet
```

See the [ecitygml-ffi README](../../README.md) for details.
