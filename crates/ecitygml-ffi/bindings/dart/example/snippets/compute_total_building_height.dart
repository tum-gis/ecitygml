import 'package:ecitygml/ecitygml.dart';

void main(List<String> args) {
  final path = args.isNotEmpty ? args[0] : 'model.gml';

  // Parse the CityGML document into the in-memory city model
  final cityModel = GmlReader.fromPath(path).finish();

  // Sum up the measured heights of the top-level buildings; only heights from
  // the lowest ground point to the top of construction given in meters are
  // taken into account
  var totalHeight = 0.0;
  final members = cityModel.cityObjectMembers();
  while (members.moveNext()) {
    final cityObject = members.current.object();
    if (cityObject == null) continue;
    final cityObjectRef = AbstractCityObjectKindRef.fromCityObject(cityObject);
    final feature = AbstractFeatureKindRef.fromCityObject(cityObjectRef);
    final building = Building.tryFrom(feature);
    if (building == null) continue;
    final heights = building.heights();
    while (heights.moveNext()) {
      final height = heights.current;
      if (height.lowReference().value() == 'lowestGroundPoint' &&
          height.highReference().value() == 'topOfConstruction' &&
          height.status() == HeightStatusValue.measured &&
          height.length().uom() == 'urn:adv:uom:m') {
        totalHeight += height.length().value();
      }
    }
  }

  print('Total measured height of buildings: ${totalHeight.toStringAsFixed(3)} m');
}
