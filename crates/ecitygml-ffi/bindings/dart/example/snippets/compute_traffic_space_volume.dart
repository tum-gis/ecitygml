import 'package:ecitygml/ecitygml.dart';

void main(List<String> args) {
  final path = args.isNotEmpty ? args[0] : 'model.gml';

  // Parse the CityGML document into the in-memory city model
  final cityModel = GmlReader.fromPath(path).finish();

  // Traverse all features and keep only those that are traffic spaces,
  // using a type-safe conversion that skips all other feature types
  final trafficSpaces = <TrafficSpace>[];
  final features = cityModel.iterFeatures();
  while (features.moveNext()) {
    final space = TrafficSpace.tryFrom(features.current);
    if (space != null) {
      trafficSpaces.add(space);
    }
  }

  // Compute the volumes of the LOD2 solids and sum them up; spaces
  // without an LOD2 solid are skipped
  var total = 0.0;
  for (final space in trafficSpaces) {
    final solid = space.lod2Solid()?.object();
    if (solid != null) {
      total += solid.volume3d();
    }
  }

  print('Total volume of traffic spaces (LoD2): ${total.toStringAsFixed(3)} m^3');
}
