import sys

from ecitygml import GmlReader, GmlWriter, Vector3

input_path = sys.argv[1] if len(sys.argv) > 1 else "model.gml"
output_path = sys.argv[2] if len(sys.argv) > 2 else "model_local.gml"

# Parse the CityGML document, keeping the envelopes of the objects as given
# in the file instead of recomputing them from their geometry
reader = GmlReader.from_path(input_path)
reader.with_rebuild_object_bounds(False)
city_model = reader.finish()

# Move the center of the city model's envelope to the origin
center = city_model.bounded_by().envelope().center()
offset = Vector3(-center.x(), -center.y(), -center.z())
city_model.apply_translation(offset)

# Write the translated city model as a CityGML document
GmlWriter.from_path(output_path).finish(city_model)

print(
    f"Translated the city model by ({offset.x:.3f}, {offset.y:.3f}, "
    f"{offset.z:.3f}) to local coordinates"
)
