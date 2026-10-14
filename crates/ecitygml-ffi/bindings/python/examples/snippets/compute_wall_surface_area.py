import sys

from ecitygml import GmlReader, WallSurface

path = sys.argv[1] if len(sys.argv) > 1 else "model.gml"

# Parse the CityGML document into the in-memory city model
city_model = GmlReader.from_path(path).finish()

# Sum up the areas of the LOD2 multi-surfaces of all wall surfaces; other
# feature types and walls without an LOD2 multi-surface are skipped
total_area = 0.0
for feature in city_model.iter_features():
    wall = WallSurface.try_from(feature)
    if wall is None:
        continue
    surface_property = wall.lod2_multi_surface()
    if surface_property is None:
        continue
    surface = surface_property.object()
    if surface is None:
        continue
    total_area += surface.area_3d()

print(f"Total area of wall surfaces (LoD2): {total_area:.3f} m^2")
