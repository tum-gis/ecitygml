// The cases of crates/ecitygml/tests/conformance/fzk-haus.md.
import 'package:ecitygml/ecitygml.dart';
import 'package:test/test.dart';

import '../helpers.dart' show fixtureBytes;
import 'helpers.dart';

const lod1File = 'FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml';
const lod2File = 'FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml';
const lod3File = 'FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml';

/// Matches a position within [tolerance] of ([x], [y], [z]).
Matcher closePoint(double x, double y, double z) => equals([close(x), close(y), close(z)]);

List<double> point(DirectPosition position) => [position.x(), position.y(), position.z()];

Polygon polygonOf(AbstractSurfaceProperty property) => Polygon.tryFrom(property.object()!)!;

List<WallSurface> walls(CityModel cityModel) =>
    items(cityModel.iterFeatures()).map(WallSurface.tryFrom).nonNulls.toList();

/// The lower corners of the city model's envelope and of the first wall surface's.
List<List<double>> lowerCorners(CityModel cityModel) => [
  point(cityModel.boundedBy()!.envelope()!.lowerCorner()),
  point(walls(cityModel).first.boundedBy()!.envelope()!.lowerCorner()),
];

void main() {
  group('lod1', () {
    final cityModel = read('fzk-haus', lod1File);

    test('lod1 city model', () {
      expect(cityModel.cityObjectsLen(), 1);
      final envelope = cityModel.boundedBy()!.envelope()!;
      final lower = envelope.lowerCorner();
      final upper = envelope.upperCorner();
      expect([lower.x(), lower.y(), lower.z()], [close(457842.0), close(5439083.0), close(111.8)]);
      expect([upper.x(), upper.y(), upper.z()], [close(457854.0), close(5439093.0), close(118.317669)]);
    });

    test('lod1 building attributes', () {
      final b = building(cityModel);
      expect(b.featureId().asStr(), 'UUID_d281adfc-4901-0f52-540b-4cc1a9325f82');
      expect(items(b.names()).map((name) => name.value()), ['AC14-FZK-Haus']);
      // `class` is reserved in Dart: the getter is `classifier`.
      expect(b.classifier()?.value(), '1000');
      expect(items(b.functions()).map((function) => function.value()), ['1000']);
      expect(items(b.usages()).map((usage) => usage.value()), ['1000']);
      expect(b.roofType()?.value(), '1030');
      expect([b.storeysAboveGround(), b.storeysBelowGround()], [2, 0]);

      final date = b.dateOfConstruction()!;
      expect([date.year(), date.month(), date.day()], [2020, 1, 1]);
      expect(b.dateOfDemolition(), isNull);
      final height = items(b.heights()).single;
      expect(height.highReference().value(), 'topOfConstruction');
      expect(height.lowReference().value(), 'lowestGroundPoint');
      expect(height.status(), HeightStatusValue.measured);
      expect(height.length().value(), close(6.52));
      expect(height.length().uom(), 'm');
      expect(items(b.occupancies()), isEmpty);
      expect(items(b.buildingParts()), isEmpty);
    });

    test('lod1 solid', () {
      final b = building(cityModel);
      final solid = b.lod1Solid()!.object()!;
      expect(solid.volume3d(), close(782.1228));
      final triangulation = solid.triangulate();
      expect(items(triangulation.surface().triangles()), hasLength(12));
      expect(triangulation.hasSkipped(), isFalse);
      expect(items(b.boundaries()), isEmpty);
    });

    test('lod1 envelope measures', () {
      final envelope = cityModel.boundedBy()!.envelope()!;
      expect([envelope.sizeX(), envelope.sizeY(), envelope.sizeZ()], closePoint(12.0, 10.0, 6.517669));
      expect(point(envelope.center()), closePoint(457848.0, 5439088.0, 115.0588345));
      expect(envelope.volume(), close(782.12028));
      expect(envelope.contains(envelope.lowerCorner()), isTrue);
      expect(envelope.contains(envelope.upperCorner()), isTrue);
      expect(envelope.contains(DirectPosition(457848.0, 5439088.0, 115.0)), isTrue);
      expect(envelope.contains(DirectPosition(457848.0, 5439088.0, 118.4)), isFalse);
      expect(envelope.contains(DirectPosition(457841.9, 5439088.0, 115.0)), isFalse);
      expect(cityModel.creationDate(), isNull);
    });

    test('lod1 building details', () {
      expect(items(cityModel.iterFeatures()).where((f) => f.featureType() == FeatureType.building), hasLength(1));
      final b = building(cityModel);
      expect(b.id()?.asStr(), 'UUID_d281adfc-4901-0f52-540b-4cc1a9325f82');
      final envelope = b.boundedBy()!.envelope()!;
      expect(point(envelope.lowerCorner()), closePoint(457842.0, 5439083.0, 111.8));
      expect(point(envelope.upperCorner()), closePoint(457854.0, 5439093.0, 118.31769));
      expect(b.lod2Solid(), isNull);
      expect(b.lod0MultiSurface(), isNull);
    });

    test('lod1 solid structure', () {
      final solid = building(cityModel).lod1Solid()!.object()!;
      expect(items(solid.interior()), isEmpty);
      expect(items(solid.points()), hasLength(24));
      final shell = solid.exterior()!;
      expect(shell.volume3d(), close(782.1228));
      final members = items(shell.members()).toList();
      expect(members, hasLength(6));
      expect(members.map((m) => m.href()), everyElement(isNull));
      final polygons = members.map(polygonOf).toList();
      expect(polygons.map((p) => items(p.interior())), everyElement(isEmpty));
      final rings = polygons.map((p) => LinearRing.tryFrom(p.exterior()!)!).toList();
      expect(rings.map((r) => items(r.points()).length), List.filled(6, 4));
      expect(rings.map((r) => r.area3d()), everyElement(greaterThan(0.0)));
      expect(point(items(rings[0].points()).first), closePoint(457842.0, 5439083.0, 111.8));
      expect(rings[0].length3d(), close(44.0));
      expect(rings[0].area3d(), close(120.0));
    });

    test('lod1 solid triangulation', () {
      final solid = building(cityModel).lod1Solid()!.object()!;
      final triangulation = solid.triangulate();
      expect(items(triangulation.skipped()), isEmpty);
      final surface = triangulation.surface();
      expect(surface.area3d(), close(526.77836));
      expect(items(surface.points()), hasLength(36));
      final triangle = items(surface.triangles()).first;
      expect(triangle.a().z(), close(111.8));
      expect(triangle.area(), close(60.0));
      final shell = solid.exterior()!;
      expect(items(shell.triangulate().surface().triangles()), hasLength(12));
      final first = polygonOf(items(shell.members()).first);
      expect(items(first.triangulate().surface().triangles()), hasLength(2));
    });

    test('lod1 apply scale', () {
      final scaled = read('fzk-haus', lod1File)..applyScale(Scale3(x: 2.0, y: 3.0, z: 0.5));
      final envelope = scaled.boundedBy()!.envelope()!;
      expect([envelope.sizeX(), envelope.sizeY(), envelope.sizeZ()], closePoint(24.0, 30.0, 3.2588345));
    });
  });

  group('lod2', () {
    final cityModel = read('fzk-haus', lod2File);

    test('lod2 boundary surfaces', () {
      final features = boundaries(building(cityModel));
      expect(features.map((f) => f.featureType()), [
        FeatureType.wallSurface,
        FeatureType.wallSurface,
        FeatureType.wallSurface,
        FeatureType.roofSurface,
        FeatureType.wallSurface,
        FeatureType.roofSurface,
        FeatureType.groundSurface,
      ]);
      expect(features.map(WallSurface.tryFrom).nonNulls.map((s) => firstName(s.names())), [
        'Outer Wall 1 (West)',
        'Outer Wall 2 (South)',
        'Outer Wall 3 (East)',
        'Outer Wall 4 (North)',
      ]);
      expect(features.map(RoofSurface.tryFrom).nonNulls.map((s) => firstName(s.names())), [
        'Roof 1 (North)',
        'Roof 2 (South)',
      ]);
      expect(features.map(GroundSurface.tryFrom).nonNulls.map((s) => firstName(s.names())), ['Base Surface']);
    });

    test('lod2 surface areas', () {
      final features = boundaries(building(cityModel));
      double area(Iterable<MultiSurfaceProperty?> surfaces) =>
          surfaces.map((s) => s!.object()!.area3d()).fold(0.0, (sum, area) => sum + area);
      expect(
        area(features.map(WallSurface.tryFrom).nonNulls.map((s) => s.lod2MultiSurface())),
        close(188.62887820601463),
      );
      expect(
        area(features.map(RoofSurface.tryFrom).nonNulls.map((s) => s.lod2MultiSurface())),
        close(138.56406460961398),
      );
      expect(area(features.map(GroundSurface.tryFrom).nonNulls.map((s) => s.lod2MultiSurface())), close(120.0));
    });

    test('lod2 generic attributes', () {
      final b = building(cityModel);
      final attributes = items(b.genericAttributes()).toList();
      expect(attributes, hasLength(3));
      final measure = MeasureAttribute.tryFrom(attributes[0])!;
      expect(attributes[0].name(), 'GrossPlannedArea');
      expect(measure.value().value(), close(120.0));
      expect(measure.value().uom(), 'm2');
      expect([attributes[1].name(), attributes[1].asString()?.value()], ['ConstructionMethod', 'New Building']);
      expect([attributes[2].name(), attributes[2].asString()?.value()], ['IsLandmarked', 'NO']);
      expect(items(b.externalReferences()), isEmpty);
    });

    test('lod2 solid unresolved', () {
      final solid = building(cityModel).lod2Solid()!.object()!;
      expect(solid.volume3d, throwsA(anything));
    });

    test('lod2 building details', () {
      final b = building(cityModel);
      expect(b.relativeToTerrain(), RelativeToTerrain.entirelyAboveTerrain);
      expect(b.relativeToWater(), isNull);
      final created = b.creationDate()!;
      expect([created.year(), created.month(), created.day(), created.hour()], [2017, 1, 23, 0]);
      expect(created.offsetSeconds(), 3600);
      expect(created.timestamp(), 1485126000);
      expect(b.terminationDate(), isNull);
      expect(b.validFrom(), isNull);
      expect(b.validTo(), isNull);

      expect(b.classifier()?.value(), '1000');
      expect(items(b.functions()).map((function) => function.value()), ['1000']);
      expect(items(b.usages()).map((usage) => usage.value()), ['1000']);
      expect(b.roofType()?.value(), '1030');
      expect([b.storeysAboveGround(), b.storeysBelowGround()], [2, 0]);
      final date = b.dateOfConstruction()!;
      expect([date.year(), date.month(), date.day()], [2020, 1, 1]);
      expect(b.dateOfDemolition(), isNull);
      final height = items(b.heights()).single;
      expect(height.highReference().value(), 'topOfConstruction');
      expect(height.lowReference().value(), 'lowestGroundPoint');
      expect(height.status(), HeightStatusValue.measured);
      expect(height.length().value(), close(6.52));
      expect(height.length().uom(), 'm');

      expect(items(b.occupancies()), isEmpty);
      expect(items(b.relatedTo()), isEmpty);
      expect(b.lod1Solid(), isNull);
      expect(b.boundedBy(), isNull);
      expect(b.lod1TerrainIntersectionCurve(), isNull);
      expect(b.lod2TerrainIntersectionCurve(), isNull);
      expect(b.lod3TerrainIntersectionCurve(), isNull);
      expect(b.lod1ImplicitRepresentation(), isNull);
      expect(b.lod2ImplicitRepresentation(), isNull);
      expect(b.lod3ImplicitRepresentation(), isNull);
    });

    test('lod2 boundary ids', () {
      final properties = items(building(cityModel).boundaries()).toList();
      expect(properties.map((p) => p.href()), everyElement(isNull));
      expect(properties.map((p) => p.object()!.featureId().asStr()), [
        'GML_5856d7ad-5e34-498a-817b-9544bfbb1475',
        'GML_d38cf762-c29d-4491-88c9-bdc89e141978',
        'GML_8e5db638-e46a-4739-a98a-2fc2d39c9069',
        'GML_875d470b-32b4-4985-a4c8-0f02caa342a2',
        'GML_0f30f604-e70d-4dfe-ba35-853bc69609cc',
        'GML_eeb6796a-e261-4d3b-a6f2-475940cca80a',
        'GML_257a8dde-8194-4ca3-b581-abd591dcd6a3',
      ]);
    });

    test('lod2 wall surface', () {
      final features = boundaries(building(cityModel));
      final wallSurfaces = features.map(WallSurface.tryFrom).nonNulls.toList();
      final wall = wallSurfaces.first;
      expect(wall.id()?.asStr(), 'GML_5856d7ad-5e34-498a-817b-9544bfbb1475');
      expect(wall.lod0MultiCurve(), isNull);
      expect(wall.lod0MultiSurface(), isNull);
      expect(wall.lod1MultiSurface(), isNull);
      expect(wall.relativeToTerrain(), isNull);
      expect(wall.creationDate(), isNull);
      expect(items(wall.genericAttributes()), isEmpty);
      expect(wall.boundedBy(), isNotNull);
      final multiSurface = wall.lod2MultiSurface()!.object()!;
      expect(items(multiSurface.surfaceMember()), hasLength(1));
      expect(items(multiSurface.triangulate().surface().triangles()), hasLength(3));
      expect(wallSurfaces.map((w) => items(w.fillingSurfaces())), everyElement(isEmpty));
      final ground = features.map(GroundSurface.tryFrom).nonNulls.first;
      final member = items(ground.lod2MultiSurface()!.object()!.surfaceMember()).first;
      expect(items(polygonOf(member).exterior()!.points()), hasLength(4));
    });

    test('lod2 generic attribute kinds', () {
      final attributes = items(building(cityModel).genericAttributes()).toList();
      expect(attributes[0].asString(), isNull);
      expect(MeasureAttribute.tryFrom(attributes[1]), isNull);
      expect(MeasureAttribute.tryFrom(attributes[2]), isNull);
    });

    test('lod2 city objects', () {
      expect(items(cityModel.iterCityObjects()).map((o) => o.featureType()), [
        FeatureType.building,
        FeatureType.wallSurface,
        FeatureType.wallSurface,
        FeatureType.wallSurface,
        FeatureType.roofSurface,
        FeatureType.wallSurface,
        FeatureType.roofSurface,
        FeatureType.groundSurface,
      ]);
      final types = items(cityModel.iterFeatures()).map((f) => f.featureType()).toList();
      expect(types.first, FeatureType.cityModel);
      expect(types.where((t) => t == FeatureType.cityModel), hasLength(1));
    });

    test('lod2 object bounds', () {
      final reader = GmlReader(fixtureBytes('fzk-haus/$lod2File'), CitygmlFormat.gml)..withRebuildObjectBounds(false);
      final unbounded = reader.finish();
      expect(walls(unbounded).map((w) => w.boundedBy() != null), List.filled(4, false));
      unbounded.recomputeChildBoundingShapes();
      expect(walls(unbounded).map((w) => w.boundedBy() != null), List.filled(4, true));
    });

    test('lod2 apply translation', () {
      final translated = read('fzk-haus', lod2File);
      expect(lowerCorners(translated), everyElement(closePoint(457842.0, 5439083.0, 111.8)));
      translated.applyTranslation(Vector3(x: -100.0, y: 200.0, z: 10.0));
      expect(lowerCorners(translated), everyElement(closePoint(457742.0, 5439283.0, 121.8)));
    });
  });

  group('lod3', () {
    final cityModel = read('fzk-haus', lod3File);

    test('lod3 doors and windows', () {
      final features = items(cityModel.iterFeatures()).toList();
      final doors = features.map(DoorSurface.tryFrom).nonNulls.toList();
      expect(doors.map((d) => firstName(d.names())), ['Door West', 'Door South']);
      final area = doors.map((d) => d.lod3MultiSurface()!.object()!.area3d()).fold(0.0, (sum, a) => sum + a);
      expect(area, close(6.803850099444389));
      expect(features.map(WindowSurface.tryFrom).nonNulls, hasLength(11));
    });

    test('lod3 west wall fillings', () {
      final wall = WallSurface.tryFrom(boundaries(building(cityModel)).first)!;
      expect(firstName(wall.names()), 'Outer Wall 1 (West)');
      final fillings = items(wall.fillingSurfaces()).map((p) => p.object()!);
      expect(fillings.map((f) => (f.featureType(), firstName(f.names()))), [
        (FeatureType.windowSurface, 'Window Round'),
        (FeatureType.windowSurface, 'Window North'),
        (FeatureType.doorSurface, 'Door West'),
        (FeatureType.windowSurface, 'Window South'),
      ]);
    });

    test('lod3 building details', () {
      expect(cityModel.cityObjectsLen(), 1);
      final b = building(cityModel);
      expect(b.relativeToTerrain(), RelativeToTerrain.entirelyAboveTerrain);
      final features = boundaries(b);
      expect(features.map((f) => f.featureType()), [
        FeatureType.wallSurface,
        FeatureType.wallSurface,
        FeatureType.wallSurface,
        FeatureType.roofSurface,
        FeatureType.wallSurface,
        FeatureType.roofSurface,
        FeatureType.groundSurface,
      ]);
      expect(features.map(WallSurface.tryFrom).nonNulls.map((w) => w.lod3MultiSurface()), everyElement(isNotNull));
    });

    test('lod3 fillings', () {
      final features = boundaries(building(cityModel));
      final perWall = features
          .map(WallSurface.tryFrom)
          .nonNulls
          .map((w) => items(w.fillingSurfaces()).toList())
          .toList();
      expect(perWall.map((p) => p.length), [4, 3, 3, 3]);
      final properties = perWall.expand((p) => p).toList();
      expect(properties.map((p) => p.href()), everyElement(isNull));
      final fillings = properties.map((p) => p.object()!).toList();
      final types = fillings.map((f) => f.featureType()).toList();
      expect(
        [
          types.where((t) => t == FeatureType.doorSurface).length,
          types.where((t) => t == FeatureType.windowSurface).length,
        ],
        [2, 11],
      );
      expect(fillings.map((f) => f.lod3MultiSurface()!.object()!.area3d()), everyElement(greaterThan(0.0)));
      expect(features.map(RoofSurface.tryFrom).nonNulls.map((r) => items(r.fillingSurfaces())), everyElement(isEmpty));

      final all = items(cityModel.iterFeatures()).toList();
      final windows = all.map(WindowSurface.tryFrom).nonNulls;
      final area = windows.fold(0.0, (sum, w) => sum + w.lod3MultiSurface()!.object()!.area3d());
      expect(area, close(23.168802611529827));
      final doors = all.map(DoorSurface.tryFrom).nonNulls.toList();
      expect(doors.map((d) => d.featureId().asStr()), [
        'GML_c137f11d-9a8c-4126-9aeb-9a6c9b4e1cbd',
        'GML_2d6ddf04-ee56-42a1-a9b1-b47e4181a629',
      ]);
      expect(doors.map((d) => d.lod2MultiSurface()), everyElement(isNull));
    });

    test('lod3 city objects', () {
      final objects = items(cityModel.iterCityObjects()).map((o) => o.featureType()).toList();
      expect(objects, hasLength(21));
      final kinds = [
        FeatureType.building,
        FeatureType.wallSurface,
        FeatureType.roofSurface,
        FeatureType.groundSurface,
        FeatureType.doorSurface,
        FeatureType.windowSurface,
      ];
      expect(kinds.map((k) => objects.where((t) => t == k).length), [1, 4, 2, 1, 2, 11]);
      final types = items(cityModel.iterFeatures()).map((f) => f.featureType()).toList();
      expect(types, hasLength(22));
      expect(types.first, FeatureType.cityModel);
    });

    test('lod3 composite surface', () {
      final wall = WallSurface.tryFrom(boundaries(building(cityModel))[0])!;
      final member = items(wall.lod3MultiSurface()!.object()!.surfaceMember()).first;
      final composite = CompositeSurface.tryFrom(member.object()!)!;
      final members = items(composite.surfaceMember()).toList();
      expect(members, hasLength(85));
      final start = items(polygonOf(members.first).exterior()!.points()).first;
      expect(point(start), closePoint(457842.0, 5439088.49240388, 115.913175911167));
    });

    test('lod3 round trip', () {
      final writer = GmlWriter(CitygmlFormat.gml)..finish(cityModel);
      final written = GmlReader(writer.data(), CitygmlFormat.gml).finish();
      List<FeatureType> types(CityModel model) => items(model.iterFeatures()).map((f) => f.featureType()).toList();
      expect(types(written), types(cityModel));
      expect(building(written).featureId().asStr(), 'UUID_d281adfc-4901-0f52-540b-4cc1a9325f82');
      // The `feature_id`s of the building's boundaries, then of the wall surfaces' filling surfaces.
      List<String> surfaceIds(CityModel model) => [
        ...items(building(model).boundaries()).map((p) => p.object()!.featureId().asStr()),
        for (final wall in boundaries(building(model)).map(WallSurface.tryFrom).nonNulls)
          ...items(wall.fillingSurfaces()).map((p) => p.object()!.featureId().asStr()),
      ];
      expect(surfaceIds(written), surfaceIds(cityModel));
      final height = items(building(written).heights()).single;
      expect(height.highReference().value(), 'topOfConstruction');
      expect(height.lowReference().value(), 'lowestGroundPoint');
      expect(height.status(), HeightStatusValue.measured);
      expect(height.length().value(), close(6.52));
      expect(height.length().uom(), 'm');
    });
  });
}
