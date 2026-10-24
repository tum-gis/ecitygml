import 'package:ecitygml/ecitygml.dart';

void main(List<String> args) {
  final inputPath = args.isNotEmpty ? args[0] : 'model.gml';
  final outputPath = args.length > 1 ? args[1] : 'model_local.gml';

  // Parse the CityGML document, keeping the envelopes of the objects as given
  // in the file instead of recomputing them from their geometry
  final reader = GmlReader.fromPath(inputPath)..withRebuildObjectBounds(false);
  final cityModel = reader.finish();

  // Move the center of the city model's envelope to the origin
  final center = cityModel.boundedBy()!.envelope()!.center();
  final offset = Vector3(x: -center.x(), y: -center.y(), z: -center.z());
  cityModel.applyTranslation(offset);

  // Write the translated city model as a CityGML document
  GmlWriter.fromPath(outputPath).finish(cityModel);

  print(
    'Translated the city model by (${offset.x.toStringAsFixed(3)}, '
    '${offset.y.toStringAsFixed(3)}, ${offset.z.toStringAsFixed(3)}) to local coordinates',
  );
}
