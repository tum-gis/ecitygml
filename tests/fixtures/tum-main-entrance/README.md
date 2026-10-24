# TUM Main Entrance

`TUM-Main-Entrance.gml` is the main entrance building of the Technical University of Munich, from the Bavarian State
Mapping Agency's [OpenData portal](https://geodaten.bayern.de/opengeodata/OpenDataDetail.html?pn=lod2) (LoD2 building
models). The tile [690_5336.gml](https://download1.bayernwolke.de/a/lod2/citygml/690_5336.gml) was converted to
CityGML 3.0 using [citygml-tools](https://github.com/citygml4j/citygml-tools) and then filtered for the main entrance
with ID `DEBY_LOD2_4959457`:

```bash
subset -i DEBY_LOD2_4959457 ./690_5336.gml
```

Terms of use: [Creative Commons Attribution 4.0 (CC BY 4.0)](https://creativecommons.org/licenses/by/4.0/), as stated in
the dataset's [metadata record](https://advmis.geodatenzentrum.de/trefferanzeige?docuuid=c6a7f0be-35b7-43a5-8dc2-458fe913821c)
("3D Gebäudemodell LoD2", Landesamt für Digitalisierung, Breitband und Vermessung). The file is modified (converted and
reduced to one building), which CC BY 4.0 requires to be indicated. Attribution:

> Datenquelle: Bayerische Vermessungsverwaltung – www.geodaten.bayern.de (Daten verändert), Lizenz: CC BY 4.0
