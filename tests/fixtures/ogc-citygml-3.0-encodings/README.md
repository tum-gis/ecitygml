# OGC CityGML 3.0 Encodings

Example files from the OGC's [CityGML-3.0Encodings](https://github.com/opengeospatial/CityGML-3.0Encodings)
repository, taken unchanged from commit
[`910208e`](https://github.com/opengeospatial/CityGML-3.0Encodings/tree/910208e67abe98bcbb8cada4f90de233c451977e),
folder `Moved_to_CITYGML-3.0Encoding_CityGML/Examples/`. They were chosen for CityGML elements the other fixtures
lack. The OGC's current repository, [CityGML3.0-GML-Encoding](https://github.com/opengeospatial/CityGML3.0-GML-Encoding),
has newer versions of the same files but no licence, so the MIT-licensed copies are used.

| File | Path under `Examples/` | Contents |
|---|---|---|
| `Building_and_garage_LOD2-EPSG25832.gml` | `Examples-from-CityGML-2.0/building/CityGMLv3/` | a building with a building part (the garage), a TIN relief |
| `BuildingUnits_Storeys_xlink.gml` | `Building/` | two storeys and building units with partly own geometry, shared by `xlink:href`; building rooms |
| `Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml` | `Transportation/Basic examples/` | a road over a bridge, related by city object relations |
| `historicalSuccession_CityGML_3.0_LOD2_Versioning.gml` | `Versioning/Basic examples/` | four buildings with building parts and termination dates, two versions and a version transition |
| `Building_CityGML3.0_LOD2_with_several_attributes.gml` | `Building/` | a building with an external reference, generic attributes and an address |
| `LocalCRS_CityGML3.gml` | `Core/` | a city model in a local engineering CRS, with a TIN relief |

**Not read yet.** The reader rejects the last two files, both valid GML:

- `Building_CityGML3.0_LOD2_with_several_attributes.gml`: the address location is a 2D `gml:pos`
  (`srsName="urn:ogc:def:crs:EPSG::4326"`), and the reader requires three values per position.
- `LocalCRS_CityGML3.gml`: the city model's `gml:Envelope` gives its corners as two `gml:pos` (allowed, though
  deprecated, in GML 3.2) instead of `gml:lowerCorner` and `gml:upperCorner`, which the reader requires.

Terms of use: MIT License, see [`LICENSE`](LICENSE) (copied from the repository; "Copyright (c) 2013 3DXScape").
