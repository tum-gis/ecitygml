# FZK Haus

The [FZK Haus datasets](https://www.citygmlwiki.org/index.php?title=FZK_Haus) in LoD1, LoD2 and LoD3, made by the
Institute for Automation and Applied Computer Science (IAI) at the Karlsruhe Institute of Technology (KIT). Their
CityGML 2.0 files were upgraded to CityGML 3.0 using [citygml-tools](https://github.com/citygml4j/citygml-tools).

| File | Contents |
|---|---|
| `FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml` | a building with an LoD1 solid |
| `FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml` | a building with wall, roof and ground surfaces |
| `FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml` | as LoD2, plus doors and windows |

LoD1 is also included compressed, to test reading compressed files:

| File | Made with |
|---|---|
| `FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml.gz` | `gzip -9 -n -c FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml > FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml.gz` |
| `FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml.zst` | `zstd -19 -c FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml > FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml.zst` (zstd 1.5.7) |

Attribution: Institute for Automation and Applied Computer Science (IAI) / Karlsruhe Institute of Technology (KIT).
