// Lists the feature types of a CityGML file with their counts, and the ids of its buildings.
//
// A city model is a tree of features: the city model, buildings, their wall surfaces, the doors in
// those walls, and so on. `iterFeatures()` visits all of them, depth first in document order, as
// `AbstractFeatureKindRef`s. Each tells its `featureType()`; to use the getters of its concrete
// type, convert it with that type's `tryFrom`, which returns null for other types.
//
// Usage: dart run example/02_list_features.dart path/to/model.gml
//
// Output for FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml (shortened):
//
//     Feature type              Count
//     CityModel                     1
//     Building                      1
//     WallSurface                   4
//     ...
//     Total                        22
//
//     Buildings:
//       UUID_d281adfc-4901-0f52-540b-4cc1a9325f82

import 'package:ecitygml/ecitygml.dart';

import 'common.dart';

void row(String name, Object count) => print('${name.padRight(24)} ${'$count'.padLeft(6)}');

void main(List<String> args) {
  final cityModel = readCityModel(pathArgument(args, '02_list_features'));

  // Count the features per type, in the order the types first appear (Dart's default map keeps
  // insertion order). `FeatureType.toString()` is the type's name, as Rust's `Display`.
  final counts = <String, int>{};
  for (final feature in items(cityModel.iterFeatures())) {
    counts.update(feature.featureType().toString(), (count) => count + 1, ifAbsent: () => 1);
  }

  row('Feature type', 'Count');
  counts.forEach(row);
  row('Total', counts.values.fold<int>(0, (sum, count) => sum + count));

  // `Building.tryFrom` turns a feature into a `Building` (or null).
  print('');
  print('Buildings:');
  for (final feature in items(cityModel.iterFeatures())) {
    final building = Building.tryFrom(feature);
    if (building != null) {
      print('  ${building.featureId().asStr()}');
    }
  }
}
