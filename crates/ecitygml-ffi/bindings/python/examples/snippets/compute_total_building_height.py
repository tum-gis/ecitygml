import sys

from ecitygml import (
    AbstractCityObjectKindRef,
    AbstractFeatureKindRef,
    Building,
    GmlReader,
    HeightStatusValue,
)

path = sys.argv[1] if len(sys.argv) > 1 else "model.gml"

# Parse the CityGML document into the in-memory city model
city_model = GmlReader.from_path(path).finish()

# Sum up the measured heights of the top-level buildings; only heights from
# the lowest ground point to the top of construction given in meters are
# taken into account
total_height = 0.0
for member in city_model.city_object_members():
    city_object = member.object()
    if city_object is None:
        continue
    city_object_ref = AbstractCityObjectKindRef.from_city_object(city_object)
    feature = AbstractFeatureKindRef.from_city_object(city_object_ref)
    building = Building.try_from(feature)
    if building is None:
        continue
    for height in building.heights():
        if (
            height.low_reference().value() == "lowestGroundPoint"
            and height.high_reference().value() == "topOfConstruction"
            and height.status() == HeightStatusValue.Measured
            and height.length().uom() == "urn:adv:uom:m"
        ):
            total_height += height.length().value()

print(f"Total measured height of buildings: {total_height:.3f} m")
