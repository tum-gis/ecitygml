# Railway Scene

The LoD3 Railway Scene, a fictional scene with 52 top-level features from ten CityGML modules: tunnels with tunnel
installations, trees (`SolitaryVegetationObject`) with implicit geometry, city furniture, railways, bridges, buildings,
a water body, a TIN relief, a city object group and generic city objects. It was produced with the CityGML Export
Plugin for SketchUp by GeoRES, edited by Karl-Heinz Häfele (IAI, Karlsruhe Institute of Technology) and post-processed
with citygml4j by Claus Nagel (virtualcitySYSTEMS), as the file's comments state.

Source: `Railway_Scene_LoD3.zip` from the 3DCityDB Importer/Exporter repository,
[`resources/samples/Railway Scene/`](https://github.com/3dcitydb/importer-exporter/tree/92e08aa306611ee850e065bb542bb3d60791a54f/resources/samples/Railway%20Scene)
at commit `92e08aa`, as linked from the
[3DCityDB WFS Docker documentation](https://3dcitydb-docs.readthedocs.io/en/latest/wfs/docker.html). Its CityGML 2.0
file `Railway_Scene_LoD3.gml` (SHA-256 `a4a91b771d2aa4c95d96b285281860f8a8aefb2c75a1ac704ab52c042880bc17`) was upgraded
to CityGML 3.0 using [citygml-tools](https://github.com/citygml4j/citygml-tools) (`Railway_Scene_LoD3__v3.gml`,
54 MB); the textures are not included.

The upgraded file is included in thinned form, as `Railway_Scene_LoD3__v3-thinned.gml` (413 KB). The thinning removes
the 151 global appearances (`appearanceMember`s of the city model), every `surfaceMember` of a `MultiSurface` or
`CompositeSurface` but the first, and every `Triangle` of the TIN but the first (kept: 210 of 43,527 surface members, 1
of 22,022 triangles); everything else, including all features, attributes, ids and references, is byte-identical to
the upgraded file. Areas and volumes of the thinned geometry are therefore not those of the original scene. To
reproduce it with [`thin_geometry.rs`](../scripts/thin_geometry.rs) (dependency-free, built with `rustc` alone):

```bash
rustc --edition 2024 -O ../scripts/thin_geometry.rs -o /tmp/thin_geometry
/tmp/thin_geometry Railway_Scene_LoD3__v3.gml Railway_Scene_LoD3__v3-thinned.gml
```

Terms of use: Apache License 2.0, the license of the 3DCityDB Importer/Exporter repository; see [`LICENSE`](LICENSE).
The included file is modified from the original as described above.
