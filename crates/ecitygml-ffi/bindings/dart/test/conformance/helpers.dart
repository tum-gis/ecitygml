// Helpers of the conformance suite (crates/ecitygml/tests/conformance/README.md).
import 'package:ecitygml/ecitygml.dart';
import 'package:test/test.dart';

import '../helpers.dart' as shared;

/// The tolerance of floating point comparisons in the case lists.
const tolerance = 1e-6;

/// Reads `tests/fixtures/<dataset>/<file>`.
CityModel read(String dataset, String file) => shared.read('$dataset/$file');

/// Matches a number within [tolerance] of [expected].
Matcher close(num expected) => closeTo(expected, tolerance);

/// Diplomat's iterators implement [Iterator] but not [Iterable]: this makes them usable in `for`.
Iterable<T> items<T>(Iterator<T> iterator) => shared.items(iterator);

/// The city model's first building.
Building building(CityModel cityModel) => items(cityModel.iterFeatures()).map(Building.tryFrom).nonNulls.first;

/// The building's boundaries, as features.
List<AbstractFeatureKindRef> boundaries(Building building) =>
    items(building.boundaries()).map((p) => AbstractFeatureKindRef.fromSpaceBoundary(p.object()!)).toList();

/// The first of a feature's names (`names()`).
String firstName(Iterator<Code> names) => items(names).first.value();
