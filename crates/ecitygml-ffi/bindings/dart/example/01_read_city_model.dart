// Reads a CityGML file and prints an overview of the city model.
//
// This is the starting point for every program using ecitygml: `GmlReader` reads CityGML data into
// a `CityModel`, which owns all features (see `readCityModel` in common.dart). Errors, e.g. invalid
// XML or a missing file, are thrown as the ecitygml `Error`. Objects borrowed from the city model keep
// it alive; native memory is freed by finalizers once the garbage collector drops the objects.
//
// Usage: dart run example/01_read_city_model.dart path/to/model.gml
//
// Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml:
//
//     City object members: 1
//     City objects (at all depths): 8
//     Envelope:
//       lower corner: 457842.000, 5439083.000, 111.800
//       upper corner: 457854.000, 5439093.000, 118.318
//       size: 12.000 x 10.000 x 6.518

import 'common.dart';

void main(List<String> args) {
  final cityModel = readCityModel(pathArgument(args, '01_read_city_model'));

  // `cityObjectMember`s are the top-level city objects (e.g. buildings); their boundary surfaces,
  // doors and windows are city objects too, which `iterCityObjects()` visits as well.
  print('City object members: ${cityModel.cityObjectsLen()}');
  print('City objects (at all depths): ${items(cityModel.iterCityObjects()).length}');

  // `boundedBy()` is the `gml:boundedBy` property, a bounding shape holding an envelope; both are
  // optional (null when absent), as in the file.
  final envelope = cityModel.boundedBy()?.envelope();
  if (envelope == null) {
    print('Envelope: none');
    return;
  }
  final (lower, upper) = (envelope.lowerCorner(), envelope.upperCorner());
  print('Envelope:');
  print('  lower corner: ${fixed(lower.x())}, ${fixed(lower.y())}, ${fixed(lower.z())}');
  print('  upper corner: ${fixed(upper.x())}, ${fixed(upper.y())}, ${fixed(upper.z())}');
  print('  size: ${fixed(envelope.sizeX())} x ${fixed(envelope.sizeY())} x ${fixed(envelope.sizeZ())}');
}
