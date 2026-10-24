# Fixtures

CityGML 3.0 test data, one folder per source dataset, one folder of hand-written CityGML for content no real dataset has, and one folder of deliberately invalid input. Each folder's README states where the files come from and
how they were processed. File names are kept as published, so each file can be traced back to its download. All `.gml` files are kept byte-identical to what was added (`.gitattributes`: no line-ending
conversion).

| Folder | Provider | Processing |
|---|---|---|
| [`fzk-haus/`](fzk-haus/README.md) | IAI / KIT | CityGML 2.0 upgraded with citygml-tools; LoD1 also compressed |
| [`fzk-haus-citygml-3.0/`](fzk-haus-citygml-3.0/README.md) | IAI / KIT | none; one point cloud thinned |
| [`kit-bruecke/`](kit-bruecke/README.md) | IAI / KIT | CityGML 2.0 upgraded with citygml-tools |
| [`tum-main-entrance/`](tum-main-entrance/README.md) | Bavarian State Mapping Agency (LDBV) | converted with citygml-tools, one building selected |
| [`asam-opendrive/`](asam-opendrive/README.md) | ASAM | OpenDRIVE converted with rtron |
| [`ogc-citygml-3.0-encodings/`](ogc-citygml-3.0-encodings/README.md) | OGC | none; two files not read yet |
| [`railway-scene/`](railway-scene/README.md) | 3DCityDB (GeoRES, IAI / KIT, virtualcitySYSTEMS) | CityGML 2.0 upgraded with citygml-tools; geometry thinned |
| [`synthetic/`](synthetic/README.md) | — | hand-written, not real data: schema-valid CityGML for content no real fixture has |
| [`invalid/`](invalid/README.md) | — | hand-written, not real data: input the reader must reject |

[`scripts/`](scripts) holds the tools used to derive fixtures (thinning point clouds and geometry) and the schema `mise run check:fixtures` validates the synthetic fixtures against.
