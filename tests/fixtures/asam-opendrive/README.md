# ASAM OpenDRIVE

The two road networks were converted from the official [OpenDRIVE examples](https://www.asam.net/standards/detail/opendrive/)
to CityGML 3.0 using [rtron](https://github.com/tum-gis/rtron):

```bash
opendrive-to-citygml ./ASAM_examples_181/Ex_Bidirectional_Junction ./output --discretization-step-size 5.0 --skip-lane-surface-extrusions
```

```bash
opendrive-to-citygml ./ASAM_examples_181/UC_RoadShape ./output --discretization-step-size 50.0
```

| File | Contents |
|---|---|
| `ASAM-Ex_Bidirectional_Junction.gml` | a road with sections, an intersection and traffic spaces linked by predecessors and successors |
| `ASAM-UC_RoadShape.gml` | a road with one section, traffic spaces and auxiliary traffic spaces |
