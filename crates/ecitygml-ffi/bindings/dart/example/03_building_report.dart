// Prints a report of every building in a CityGML file: its attributes and its boundary surfaces
// with their doors and windows.
//
// Shows how the bindings mirror the Rust data model:
// - Optional values are null when absent; lists are iterators (possibly empty).
// - Code-list values (class, function, ...) are wrappers with `value()` (and `code()`).
// - Properties referencing other objects (e.g. a building's boundaries) have `object()` and `href()`;
//   `object()` is null if the property only references an object elsewhere via `xlink:href`.
// - Abstract types are converted with `tryFrom`, e.g. a generic attribute to a `MeasureAttribute`,
//   or a boundary (via `AbstractFeatureKindRef.fromSpaceBoundary`) to a `WallSurface`.
// - `class` is reserved in Dart: the `class` getters are named `classifier()`.
//
// Usage: dart run example/03_building_report.dart path/to/model.gml
//
// Output for FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml (shortened):
//
//     Building UUID_d281adfc-4901-0f52-540b-4cc1a9325f82
//       Name: AC14-FZK-Haus
//       Class: 1000
//       ...
//       Boundaries:
//         WallSurface GML_5856d7ad-5e34-498a-817b-9544bfbb1475
//           WindowSurface GML_356b85c1-25a0-49f9-b39e-013fbbafcce4
//         ...

import 'package:ecitygml/ecitygml.dart';

import 'common.dart';

/// The values of code-list values (or codes), comma-separated; "-" if there are none.
String joined(Iterable<String> values) {
  final text = values.join(', ');
  return text.isEmpty ? '-' : text;
}

/// The value of a generic attribute: string, integer, double or measure (value and unit).
String genericAttributeValue(GenericAttributeKind attribute) {
  final string = attribute.asString();
  if (string != null) return string.value();
  final integer = attribute.asInt();
  if (integer != null) return '${integer.value()}';
  final double = attribute.asDouble();
  if (double != null) return fixed(double.value());
  final measure = MeasureAttribute.tryFrom(attribute);
  if (measure != null) return '${fixed(measure.value().value())} ${measure.value().uom()}';
  return '(not shown)'; // e.g. a generic attribute set, which holds further attributes
}

/// Prints the doors and windows of a wall, roof or ground surface.
void printFillingSurfaces(AbstractFillingSurfacePropertyIterator fillings) {
  for (final property in items(fillings)) {
    final filling = property.object();
    if (filling != null) {
      print('      ${filling.featureType()} ${filling.featureId().asStr()}');
    }
  }
}

void printBuilding(Building building) {
  final date = building.dateOfConstruction();
  String pad(int value, int width) => '$value'.padLeft(width, '0');
  print('Building ${building.featureId().asStr()}');
  print('  Name: ${joined(items(building.names()).map((name) => name.value()))}');
  print('  Class: ${building.classifier()?.value() ?? '-'}');
  print('  Functions: ${joined(items(building.functions()).map((function) => function.value()))}');
  print('  Usages: ${joined(items(building.usages()).map((usage) => usage.value()))}');
  print('  Roof type: ${building.roofType()?.value() ?? '-'}');
  print('  Storeys above ground: ${building.storeysAboveGround() ?? '-'}');
  print('  Storeys below ground: ${building.storeysBelowGround() ?? '-'}');
  print(
    '  Date of construction: ${date == null ? '-' : '${pad(date.year(), 4)}-${pad(date.month(), 2)}-${pad(date.day(), 2)}'}',
  );

  print('  Heights:');
  for (final height in items(building.heights())) {
    final length = height.length();
    print(
      '    ${fixed(length.value())} ${length.uom()} (${height.highReference().value()} to ${height.lowReference().value()})',
    );
  }

  print('  Generic attributes:');
  for (final attribute in items(building.genericAttributes())) {
    print('    ${attribute.name()}: ${genericAttributeValue(attribute)}');
  }

  // Each boundary property holds an `AbstractSpaceBoundaryKind` (or only an href). Wall, roof
  // and ground surfaces can have filling surfaces: doors and windows.
  print('  Boundaries:');
  for (final property in items(building.boundaries())) {
    final boundary = property.object();
    if (boundary == null) {
      print('    (reference to ${property.href()})');
      continue;
    }
    print('    ${boundary.featureType()} ${boundary.featureId().asStr()}');
    final feature = AbstractFeatureKindRef.fromSpaceBoundary(boundary);
    final fillings =
        WallSurface.tryFrom(feature)?.fillingSurfaces() ??
        RoofSurface.tryFrom(feature)?.fillingSurfaces() ??
        GroundSurface.tryFrom(feature)?.fillingSurfaces();
    if (fillings != null) {
      printFillingSurfaces(fillings);
    }
  }
}

void main(List<String> args) {
  final cityModel = readCityModel(pathArgument(args, '03_building_report'));
  final buildings = items(cityModel.iterFeatures()).map(Building.tryFrom).nonNulls.toList();
  if (buildings.isEmpty) {
    print('No buildings.');
  }
  for (final (index, building) in buildings.indexed) {
    if (index > 0) print('');
    printBuilding(building);
  }
}
