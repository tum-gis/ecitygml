// The cases of crates/ecitygml/tests/api/iteration.md. Dart can't request a garbage collection, so
// `iterator keeps model alive` relies on the model having no other reference.
import 'package:ecitygml/ecitygml.dart';
import 'package:test/test.dart';

import '../helpers.dart';
import 'helpers.dart';

const asamRoadShape = 'asam-opendrive/ASAM-UC_RoadShape.gml';

/// Takes the first feature of a fresh iterator, which is unreachable afterwards.
FeatureType firstOfFreshIterator(CityModel cityModel) {
  final iterator = cityModel.iterFeatures();
  expect(iterator.moveNext(), isTrue);
  return iterator.current.featureType();
}

void main() {
  test('iterator exhausted', () {
    final iterator = read(fzkLod3).iterFeatures();
    var count = 0;
    while (iterator.moveNext()) {
      count++;
    }
    expect(count, 22);
    expect(iterator.moveNext(), isFalse);
    expect(iterator.moveNext(), isFalse);
  });

  test('iterator stopped early', () {
    final cityModel = read(asamRoadShape);
    expect(firstOfFreshIterator(cityModel), FeatureType.cityModel);
    expect(featureTypes(cityModel), hasLength(11));
    expect(cityModel.cityObjectsLen(), 1);
  });

  test('iterators independent', () {
    final cityModel = read(fzkLod3);
    final (first, second) = (cityModel.iterFeatures(), cityModel.iterFeatures());
    final (a, b) = (<FeatureType>[], <FeatureType>[]);
    while (true) {
      final (x, y) = (first.moveNext(), second.moveNext());
      expect(x, y);
      if (!x) break;
      a.add(first.current.featureType());
      b.add(second.current.featureType());
    }
    expect(a, hasLength(22));
    expect(a, b);
    expect(a, featureTypes(cityModel));
  });

  test('iterator keeps model alive', () {
    final iterator = read(fzkLod3).iterFeatures();
    var walls = 0;
    while (iterator.moveNext()) {
      if (WallSurface.tryFrom(iterator.current) != null) walls++;
    }
    expect(walls, 4);
  });

  test('native iteration', () {
    final iterator = read(fzkLod3).iterFeatures();
    final types = <FeatureType>[];
    while (iterator.moveNext()) {
      types.add(iterator.current.featureType());
    }
    expect(types, hasLength(22));
    expect(types.first, FeatureType.cityModel);
  });
}
