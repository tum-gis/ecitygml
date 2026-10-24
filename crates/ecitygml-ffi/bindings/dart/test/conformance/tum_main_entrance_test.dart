// The cases of crates/ecitygml/tests/conformance/tum-main-entrance.md.
import 'package:ecitygml/ecitygml.dart';
import 'package:test/test.dart';

import 'helpers.dart';

const entranceId = 'DEBY_LOD2_4959457';

final boundaryTypes = [
  ...List.filled(10, FeatureType.wallSurface),
  FeatureType.groundSurface,
  ...List.filled(3, FeatureType.wallSurface),
  FeatureType.roofSurface,
  FeatureType.roofSurface,
  FeatureType.wallSurface,
];

List<FeatureType> featureTypes(CityModel cityModel) =>
    items(cityModel.iterFeatures()).map((f) => f.featureType()).toList();

/// The area of an inline LoD2 multi surface.
double lod2Area(MultiSurfaceProperty? property) {
  expect(property, isNotNull);
  expect(property!.href(), isNull);
  return property.object()!.area3d();
}

void main() {
  group('TUM-Main-Entrance.gml', () {
    final cityModel = read('tum-main-entrance', 'TUM-Main-Entrance.gml');

    test('entrance city model', () {
      expect(cityModel.cityObjectsLen(), 1);
      final envelope = cityModel.boundedBy()!.envelope()!;
      final lower = envelope.lowerCorner();
      final upper = envelope.upperCorner();
      expect([lower.x(), lower.y(), lower.z()], [close(689975.68), close(5335962.63), close(503.0)]);
      expect([upper.x(), upper.y(), upper.z()], [close(692025.893), close(5338012.713), close(581.62)]);
      expect(featureTypes(cityModel), [FeatureType.cityModel, FeatureType.building, ...boundaryTypes]);
      expect(items(cityModel.iterCityObjects()), hasLength(18));
    });

    test('entrance building attributes', () {
      final b = building(cityModel);
      expect(b.featureId().asStr(), entranceId);
      expect(items(b.names()), isEmpty);
      // `class` is reserved in Dart: the getter is `classifier`.
      expect(b.classifier(), isNull);
      expect(items(b.functions()).map((f) => f.value()), ['31001_3020']);
      expect(items(b.usages()), isEmpty);
      expect(b.roofType()?.value(), '1000');
      expect(b.storeysAboveGround(), 4);
      expect(b.storeysBelowGround(), isNull);

      final height = items(b.heights()).single;
      expect(height.highReference().value(), 'topOfConstruction');
      expect(height.lowReference().value(), 'lowestGroundPoint');
      expect(height.status(), HeightStatusValue.measured);
      expect(height.length().value(), close(19.408));
      expect(height.length().uom(), 'urn:adv:uom:m');

      final created = b.creationDate()!;
      expect([created.year(), created.month(), created.day()], [2025, 1, 2]);
      expect([created.hour(), created.minute()], [0, 0]);
      expect(created.offsetSeconds(), 3600);
      expect(b.boundedBy(), isNull);
      expect(items(b.occupancies()), isEmpty);
      expect(items(b.buildingSubdivisions()), isEmpty);
    });

    test('entrance external reference', () {
      final reference = items(building(cityModel).externalReferences()).single;
      expect(reference.targetResource(), 'DEBYvAAAAABTMIyA');
    });

    test('entrance external reference details', () {
      final reference = items(building(cityModel).externalReferences()).single;
      expect(reference.informationSystem(), 'http://repository.gdi-de.org/schemas/adv/citygml/fdv/art.htm#_9100');
      expect(reference.relationType(), isNull);
    });

    test('entrance generic attributes', () {
      final attributes = items(building(cityModel).genericAttributes()).map((a) => [a.name(), a.asString()!.value()]);
      expect(attributes, [
        ['DatenquelleBodenhoehe', '1100'],
        ['DatenquelleDachhoehe', '1000'],
        ['DatenquelleLage', '1000'],
        ['Gemeindeschluessel', '09162000'],
        ['HoeheDach', '534.450'],
        ['HoeheGrund', '515.042'],
        ['Methode', '2000'],
        ['NiedrigsteTraufeDesGebaeudes', '527.312'],
        ['Grundrissaktualitaet', '2025-02-17'],
        ['Geometrietyp2DReferenz', '3000'],
      ]);
    });

    test('entrance boundaries', () {
      final b = building(cityModel);
      expect(items(b.boundaries()).map((p) => p.href()), everyElement(isNull));
      final features = boundaries(b);
      expect(features.map((f) => f.featureType()), boundaryTypes);

      final walls = features.map(WallSurface.tryFrom).nonNulls.toList();
      expect(walls.first.featureId().asStr(), 'DEBY_LOD2_4959457_ca1db42f-9d12-4f41-972c-c7da1614f0a8_2');
      expect(items(walls.first.names()), isEmpty);
      expect(walls.map((w) => lod2Area(w.lod2MultiSurface())).reduce((a, b) => a + b), close(3783.3908922901974));

      final roofs = features.map(RoofSurface.tryFrom).nonNulls.map((r) => lod2Area(r.lod2MultiSurface())).toList();
      expect(roofs, [close(250.233154296875), close(979.3291015625)]);
      expect(roofs[0] + roofs[1], close(1229.562255859375));

      final grounds = features.map(GroundSurface.tryFrom).nonNulls.map((g) => lod2Area(g.lod2MultiSurface())).toList();
      expect(grounds, [close(1229.562255859375)]);
    });

    test('entrance wall triangulation', () {
      final wall = items(cityModel.iterFeatures()).map(WallSurface.tryFrom).nonNulls.first;
      final multiSurface = wall.lod2MultiSurface()!.object()!;
      expect(items(multiSurface.surfaceMember()), hasLength(1));
      expect(multiSurface.area3d(), close(546.6949745937537));
      final triangulation = multiSurface.triangulate();
      expect(items(triangulation.surface().triangles()), hasLength(4));
      expect(triangulation.hasSkipped(), isFalse);
      expect(triangulation.surface().area3d(), close(546.6949742237184));
    });

    test('entrance solid unresolved', () {
      final property = building(cityModel).lod2Solid()!;
      expect(property.href(), isNull);
      final solid = property.object()!;
      final members = items(solid.exterior()!.members()).toList();
      expect(members, hasLength(17));
      expect(members.map((m) => m.object()), everyElement(isNull));
      expect(solid.volume3d, throwsA(anything));
    });

    test('entrance round trip', () {
      final writer = GmlWriter(CitygmlFormat.gml)..finish(cityModel);
      final written = GmlReader(writer.data(), CitygmlFormat.gml).finish();
      expect(featureTypes(written), featureTypes(cityModel));
      expect(building(written).featureId().asStr(), entranceId);
      List<String> boundaryIds(CityModel model) =>
          items(building(model).boundaries()).map((p) => p.object()!.featureId().asStr()).toList();
      expect(boundaryIds(written), boundaryIds(cityModel));
    });
  });
}
