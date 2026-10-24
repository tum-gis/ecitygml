// The cases of crates/ecitygml/tests/conformance/kit-bruecke.md.
import 'package:ecitygml/ecitygml.dart';
import 'package:test/test.dart';

import 'helpers.dart';

const bridgeId = '_Modellbahnbruecke-LoD2-V03_BD.rx3tFkxPQkL5qDXML1W7';

Bridge bridge(CityModel cityModel) => items(cityModel.iterFeatures()).map(Bridge.tryFrom).nonNulls.first;

List<FeatureType> featureTypes(CityModel cityModel) =>
    items(cityModel.iterFeatures()).map((f) => f.featureType()).toList();

void expectEnvelope(Envelope envelope, List<double> lower, List<double> upper) {
  final l = envelope.lowerCorner();
  final u = envelope.upperCorner();
  expect([l.x(), l.y(), l.z()], lower.map(close).toList());
  expect([u.x(), u.y(), u.z()], upper.map(close).toList());
}

void main() {
  group('Modellbahnbruecke-LoD2-V03__v3.gml', () {
    final cityModel = read('kit-bruecke', 'Modellbahnbruecke-LoD2-V03__v3.gml');

    test('bridge city model', () {
      expect(cityModel.cityObjectsLen(), 1);
      expectEnvelope(cityModel.boundedBy()!.envelope()!, [457644.585, 5439126.455, 109.0], [457708.084, 5439157.169, 124.3]);
      expect(featureTypes(cityModel), [
        FeatureType.cityModel,
        FeatureType.bridge,
        FeatureType.appearance,
        ...List.filled(3, FeatureType.parameterizedTexture),
        ...List.filled(2, FeatureType.bridgeInstallation),
        ...List.filled(11, FeatureType.bridgeConstructiveElement),
      ]);
      expect(items(cityModel.iterCityObjects()), hasLength(14));
    });

    test('bridge attributes', () {
      final b = bridge(cityModel);
      expect(b.featureId().asStr(), bridgeId);
      expect(items(b.names()), isEmpty);
      // `class` is reserved in Dart: the getter is `classifier`.
      expect(b.classifier(), isNull);
      expect(items(b.functions()), isEmpty);
      expect(items(b.usages()), isEmpty);
      expect(items(b.bridgeParts()), isEmpty);
      expect(items(b.boundaries()), isEmpty);
      expect(b.dateOfConstruction(), isNull);
      expect(b.creationDate(), isNull);
      expect(items(b.heights()), isEmpty);
      expect(items(b.occupancies()), isEmpty);
      expect(items(b.genericAttributes()), isEmpty);
      expect(items(b.externalReferences()), isEmpty);
    });

    test('bridge geometry', () {
      final b = bridge(cityModel);
      expectEnvelope(b.boundedBy()!.envelope()!, [457645.136, 5439126.692, 115.3], [457707.533, 5439156.931, 116.2]);
      final property = b.lod2MultiSurface()!;
      expect(property.href(), isNull);
      final multiSurface = property.object()!;
      expect(items(multiSurface.surfaceMember()), hasLength(18));
      expect(multiSurface.area3d(), close(795.4201811265907));
      final triangulation = multiSurface.triangulate();
      expect(items(triangulation.surface().triangles()), hasLength(60));
      expect(triangulation.hasSkipped(), isFalse);
      expect(b.lod1Solid(), isNull);
      expect(b.lod2Solid(), isNull);
      expect(b.lod3MultiSurface(), isNull);
    });

    test('bridge round trip', () {
      final writer = GmlWriter(CitygmlFormat.gml)..finish(cityModel);
      final written = GmlReader(writer.data(), CitygmlFormat.gml).finish();
      expect(featureTypes(written), featureTypes(cityModel));
      expect(bridge(written).featureId().asStr(), bridgeId);
    });
  });
}
