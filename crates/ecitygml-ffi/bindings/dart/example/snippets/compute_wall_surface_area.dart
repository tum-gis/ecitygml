import 'package:ecitygml/ecitygml.dart';

void main(List<String> args) {
  final path = args.isNotEmpty ? args[0] : 'model.gml';

  // Parse the CityGML document into the in-memory city model
  final cityModel = GmlReader.fromPath(path).finish();

  // Sum up the areas of the LOD2 multi-surfaces of all wall surfaces; other
  // feature types and walls without an LOD2 multi-surface are skipped
  var totalArea = 0.0;
  final features = cityModel.iterFeatures();
  while (features.moveNext()) {
    final wall = WallSurface.tryFrom(features.current);
    final surface = wall?.lod2MultiSurface()?.object();
    if (surface != null) {
      totalArea += surface.area3d();
    }
  }

  print('Total area of wall surfaces (LoD2): ${totalArea.toStringAsFixed(3)} m^2');
}
