import sys

from ecitygml import GmlReader, TrafficSpace

path = sys.argv[1] if len(sys.argv) > 1 else "model.gml"

# Parse the CityGML document into the in-memory city model
city_model = GmlReader.from_path(path).finish()

# Traverse all features and keep only those that are traffic spaces,
# using a type-safe conversion that skips all other feature types
traffic_spaces = []
for feature in city_model.iter_features():
    space = TrafficSpace.try_from(feature)
    if space is not None:
        traffic_spaces.append(space)

# Compute the volumes of the LOD2 solids and sum them up; spaces
# without an LOD2 solid are skipped
total = 0.0
for space in traffic_spaces:
    solid_property = space.lod2_solid()
    if solid_property is None:
        continue
    solid = solid_property.object()
    if solid is None:
        continue
    total += solid.volume_3d()

print(f"Total volume of traffic spaces (LoD2): {total:.3f} m^3")
