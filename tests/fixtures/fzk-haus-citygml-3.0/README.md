# FZK Haus CityGML 3.0

Four of the native CityGML 3.0 [FZK Haus examples](https://www.citygmlwiki.org/index.php?title=FZK_Haus_CityGML_30),
all LoD2 with storeys. Three are taken unchanged from their download archives:

| File | Download page | Contents |
|---|---|---|
| `01-FZK-Haus-LoD2-Tex-Storey-Construction-CG30-V01.gml` | [Storeys, Construction](https://www.citygmlwiki.org/index.php?title=FZK_Haus,_CityGML_3.0,_LoD2,_Storeys,_Construction) | storeys (elevation, sort key) with building constructive elements, occupancy, appearances (textures and materials) |
| `04-FZK-Haus-LoD2-Tex-Storey-CG30-V01-InteriorSurface.gml` | [Storeys, Boundary Surfaces](https://www.citygmlwiki.org/index.php?title=FZK_Haus,_CityGML_3.0,_LoD2,_Storeys,_Boundary_Surfaces) | storeys with building rooms and their ceiling, floor, interior wall and closure surfaces |
| `04-FZK-Haus-LoD2-Tex-Storey-Construction-CG30-V01-Window-Interior.gml` | [Storeys, Construction](https://www.citygmlwiki.org/index.php?title=FZK_Haus,_CityGML_3.0,_LoD2,_Storeys,_Construction) | as `01-…-Construction`, plus doors and windows as fillings of the constructive elements |

They were chosen to cover the most CityGML elements the other fixtures lack. Only the GML files are included,
not the textures from the archives (`app:imageURI` references them; the reader doesn't load them).

One point cloud example is included in thinned form, as the original is 38 MB:

| File | Download page | Contents |
|---|---|---|
| `06-FZK-Haus-LoD2-Tex-Storey-CG30-V01-PointCloud-thinned.gml` | [Storeys, Boundary Surfaces](https://www.citygmlwiki.org/index.php?title=FZK_Haus,_CityGML_3.0,_LoD2,_Storeys,_Boundary_Surfaces) (`06-FZK-Haus-LoD2-Tex-Storey-CG30-V01-PointCloud.zip`) | storeys whose 11 boundary surfaces each have a point cloud (`gml:MultiPoint`) and a qualified area |

It keeps every 1000th point of each point cloud (241 of 240,001 points, 10–40 per surface); everything else,
including the line endings, is byte-identical to the original. To reproduce it from the GML in the archive with
[`thin_point_clouds.rs`](../scripts/thin_point_clouds.rs) (dependency-free, built with `rustc` alone):

```bash
rustc --edition 2024 -O ../scripts/thin_point_clouds.rs -o /tmp/thin_point_clouds
/tmp/thin_point_clouds 06-FZK-Haus-LoD2-Tex-Storey-CG30-V01-PointCloud.gml \
    06-FZK-Haus-LoD2-Tex-Storey-CG30-V01-PointCloud-thinned.gml 1000
```

The other point cloud variants are left out.

Terms of use: "These examples are made by the Institute for Automation and Applied Computer Science (IAI) at the
Karlsruhe Institute of Technology (KIT), and are for unrestricted use." Attribution: Institute for Automation and
Applied Computer Science (IAI) / Karlsruhe Institute of Technology (KIT).
