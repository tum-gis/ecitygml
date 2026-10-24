// The cases of crates/ecitygml/tests/conformance/fzk-haus-citygml-3.0.md.
import 'package:ecitygml/ecitygml.dart';
import 'package:test/test.dart';

import 'helpers.dart';

const dataset = 'fzk-haus-citygml-3.0';
const constructionId = '_FZK-Haus-Storey-Construction_BD.DX9Xm6VLbbyLGAxG2v86';
const testBuildingId = 'KIT-Test-Building-01';
const windowId = '_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz';

List<FeatureType> featureTypes(CityModel cityModel) =>
    items(cityModel.iterFeatures()).map((f) => f.featureType()).toList();

/// The number of features per feature type, over `iterFeatures`.
Map<FeatureType, int> featureTypeCounts(CityModel cityModel) {
  final counts = <FeatureType, int>{};
  for (final type in featureTypes(cityModel)) {
    counts[type] = (counts[type] ?? 0) + 1;
  }
  return counts;
}

List<Storey> storeys(CityModel cityModel) => items(cityModel.iterFeatures()).map(Storey.tryFrom).nonNulls.toList();

void expectCityModel(CityModel cityModel, List<double> lower, List<double> upper) {
  expect(cityModel.cityObjectsLen(), 1);
  final envelope = cityModel.boundedBy()!.envelope()!;
  final l = envelope.lowerCorner();
  final u = envelope.upperCorner();
  expect([l.x(), l.y(), l.z()], lower.map(close).toList());
  expect([u.x(), u.y(), u.z()], upper.map(close).toList());
}

/// The one height and occupancy of the storey examples' buildings.
void expectHeightAndOccupancy(Building b) {
  final height = items(b.heights()).single;
  expect(height.highReference().value(), 'highestRoofEdge');
  expect(height.lowReference().value(), 'lowestGroundPoint');
  expect(height.status(), HeightStatusValue.measured);
  expect(height.length().value(), close(6.52));
  expect(height.length().uom(), 'urn:adv:uom:m');
  expect(items(b.occupancies()).single.numberOfOccupants(), 2);
}

/// The storeys' first names and classes.
void expectStoreys(CityModel cityModel, List<String?> classes) {
  final found = storeys(cityModel);
  expect(found.map((s) => firstName(s.names())), ['Ground Floor', 'Second Floor']);
  // `class` is reserved in Dart: the getter is `classifier`.
  expect(found.map((s) => s.classifier()?.value()), classes);
}

/// A storey's boundaries as (feature type, first name, LoD2 multi surface); all inline wall, roof or ground
/// surfaces.
List<(FeatureType, String, MultiSurfaceProperty?)> boundarySurfaces(Storey storey) =>
    items(storey.boundaries()).map((property) {
      expect(property.href(), isNull);
      final feature = AbstractFeatureKindRef.fromSpaceBoundary(property.object()!);
      final wall = WallSurface.tryFrom(feature);
      if (wall != null) return (feature.featureType(), firstName(wall.names()), wall.lod2MultiSurface());
      final roof = RoofSurface.tryFrom(feature);
      if (roof != null) return (feature.featureType(), firstName(roof.names()), roof.lod2MultiSurface());
      final ground = GroundSurface.tryFrom(feature);
      expect(ground, isNotNull, reason: '${feature.featureType()}');
      return (feature.featureType(), firstName(ground!.names()), ground.lod2MultiSurface());
    }).toList();

/// Writes the city model and reads it back: the same feature types in the same order and the building's id.
void expectRoundTrip(CityModel cityModel, String buildingId) {
  final writer = GmlWriter(CitygmlFormat.gml)..finish(cityModel);
  final written = GmlReader(writer.data(), CitygmlFormat.gml).finish();
  expect(featureTypes(written), featureTypes(cityModel));
  expect(building(written).featureId().asStr(), buildingId);
}

void main() {
  group('01-FZK-Haus-LoD2-Tex-Storey-Construction-CG30-V01.gml', () {
    final cityModel = read(dataset, '01-FZK-Haus-LoD2-Tex-Storey-Construction-CG30-V01.gml');

    test('construction city model', () {
      expectCityModel(cityModel, [458899.5, 5438784.5, 113.5], [458912.5, 5438795.5, 120.017691]);
      expect(featureTypes(cityModel), [
        FeatureType.cityModel,
        FeatureType.building,
        FeatureType.storey,
        ...List.filled(5, FeatureType.buildingConstructiveElement),
        FeatureType.storey,
        ...List.filled(6, FeatureType.buildingConstructiveElement),
        FeatureType.appearance,
        ...List.filled(5, FeatureType.parameterizedTexture),
        ...List.filled(5, FeatureType.x3dMaterial),
      ]);
      expect(items(cityModel.iterCityObjects()), hasLength(14));
    });

    test('construction building', () {
      final b = building(cityModel);
      expect(b.featureId().asStr(), constructionId);
      expect(items(b.names()).map((n) => n.value()), ['KIT FZK-Haus']);
      expect(b.classifier(), isNull);
      expect(items(b.functions()).map((f) => f.value()), ['31001_1000']);
      expect(items(b.usages()), isEmpty);
      expect(b.roofType()?.value(), '3100');
      expect(b.storeysAboveGround(), isNull);
      expect(b.storeysBelowGround(), isNull);
      expectHeightAndOccupancy(b);
      expect(items(b.boundaries()), isEmpty);
      expect(items(b.genericAttributes()), isEmpty);
      expect(b.lod2Solid(), isNull);
      expect(b.lod2MultiSurface(), isNull);
    });

    test('construction storeys', () {
      final subdivisions = items(building(cityModel).buildingSubdivisions()).toList();
      expect(subdivisions, hasLength(2));
      for (final subdivision in subdivisions) {
        expect(subdivision.href(), isNull);
        expect(subdivision.object()!.featureType(), FeatureType.storey);
      }
      expectStoreys(cityModel, ['Entrance Floor', 'non Entrance Floor']);
      for (final storey in storeys(cityModel)) {
        expect(items(storey.functions()), isEmpty);
        expect(items(storey.usages()), isEmpty);
        expect(items(storey.boundaries()), isEmpty);
        expect(storey.lod2Solid(), isNull);
      }
    });

    test('construction round trip', () => expectRoundTrip(cityModel, constructionId));
  });

  group('04-FZK-Haus-LoD2-Tex-Storey-CG30-V01-InteriorSurface.gml', () {
    final cityModel = read(dataset, '04-FZK-Haus-LoD2-Tex-Storey-CG30-V01-InteriorSurface.gml');

    test('interior city model', () {
      expectCityModel(cityModel, [458900.0, 5438785.0, 113.5], [458912.0, 5438795.0, 120.017691]);
      expect(featureTypes(cityModel), hasLength(77));
      expect(featureTypeCounts(cityModel), {
        FeatureType.cityModel: 1,
        FeatureType.building: 1,
        FeatureType.storey: 2,
        FeatureType.groundSurface: 1,
        FeatureType.wallSurface: 8,
        FeatureType.roofSurface: 2,
        FeatureType.buildingRoom: 7,
        FeatureType.interiorWallSurface: 27,
        FeatureType.ceilingSurface: 8,
        FeatureType.floorSurface: 7,
        FeatureType.closureSurface: 6,
        FeatureType.appearance: 1,
        FeatureType.parameterizedTexture: 5,
        FeatureType.x3dMaterial: 1,
      });
      expect(items(cityModel.iterCityObjects()), hasLength(69));
    });

    test('interior building', () {
      final b = building(cityModel);
      expect(b.featureId().asStr(), testBuildingId);
      expect(items(b.names()).map((n) => n.value()), ['KIT Test Building FZK-Haus for CityGML 3.0']);
      expect(b.classifier(), isNull);
      expect(b.roofType(), isNull);
      expect(items(b.functions()), isEmpty);
      expect(items(b.usages()), isEmpty);
      expectHeightAndOccupancy(b);
      final attribute = items(b.genericAttributes()).single;
      expect([attribute.name(), attribute.asString()?.value()], ['@cityeditor:layer', 'LoD2-Ausgeblendet']);
      expect(items(b.boundaries()), isEmpty);
    });

    test('interior solid unresolved', () {
      final property = building(cityModel).lod2Solid()!;
      expect(property.href(), isNull);
      final solid = property.object()!;
      final members = items(solid.exterior()!.members()).toList();
      expect(members, hasLength(11));
      expect(members.map((m) => m.object()), everyElement(isNull));
      expect(solid.volume3d, throwsA(anything));
    });

    test('interior storey boundaries', () {
      const expected = [
        [
          (FeatureType.groundSurface, 'Ground', 120.0),
          (FeatureType.wallSurface, 'Ground Floor / Wall East', 29.0),
          (FeatureType.wallSurface, 'Ground Floor / Wall South', 34.80000000447035),
          (FeatureType.wallSurface, 'Ground Floor / Wall West', 29.0),
          (FeatureType.wallSurface, 'Ground Floor / Wall North', 34.80000000447035),
        ],
        [
          (FeatureType.roofSurface, 'Second Floor / Roof South', 69.28203022609509),
          (FeatureType.roofSurface, 'Second Floor / Roof North', 69.28203022609509),
          (FeatureType.wallSurface, 'Second Floor / Wall South', 8.771279998123646),
          (FeatureType.wallSurface, 'Second Floor / Wall West', 21.743155002593994),
          (FeatureType.wallSurface, 'Second Floor / Wall East', 21.743155002593994),
          (FeatureType.wallSurface, 'Second Floor / Wall North', 8.771279998123646),
        ],
      ];
      final found = storeys(cityModel);
      expect(found, hasLength(expected.length));
      for (var i = 0; i < found.length; i++) {
        final actual = boundarySurfaces(found[i]);
        expect(actual.map((s) => (s.$1, s.$2)), expected[i].map((s) => (s.$1, s.$2)));
        expect(actual.map((s) => s.$3!.object()!.area3d()), expected[i].map((s) => close(s.$3)));
      }
      expectStoreys(cityModel, [null, null]);
    });

    test('interior round trip', () => expectRoundTrip(cityModel, testBuildingId));
  });

  group('04-FZK-Haus-LoD2-Tex-Storey-Construction-CG30-V01-Window-Interior.gml', () {
    final cityModel = read(dataset, '04-FZK-Haus-LoD2-Tex-Storey-Construction-CG30-V01-Window-Interior.gml');

    test('window city model', () {
      expectCityModel(cityModel, [458899.5, 5438784.5, 113.5], [458912.5, 5438795.5, 120.017691]);
      expect(featureTypes(cityModel), hasLength(54));
      expect(featureTypeCounts(cityModel), {
        FeatureType.cityModel: 1,
        FeatureType.building: 1,
        FeatureType.storey: 2,
        FeatureType.buildingConstructiveElement: 18,
        FeatureType.door: 5,
        FeatureType.window: 11,
        FeatureType.appearance: 2,
        FeatureType.parameterizedTexture: 5,
        FeatureType.x3dMaterial: 9,
      });
      expect(items(cityModel.iterCityObjects()), hasLength(37));
    });

    test('window building', () {
      final b = building(cityModel);
      expect(b.featureId().asStr(), windowId);
      expect(items(b.names()).map((n) => n.value()), ['KIT FZK-Haus']);
      expect(items(b.functions()).map((f) => f.value()), ['31001_1000']);
      expect(b.roofType()?.value(), '3100');
      expect(items(b.boundaries()), isEmpty);
      expectStoreys(cityModel, ['Entrance Floor', 'non Entrance Floor']);
    });

    test('window round trip', () => expectRoundTrip(cityModel, windowId));
  });

  group('06-FZK-Haus-LoD2-Tex-Storey-CG30-V01-PointCloud-thinned.gml', () {
    final cityModel = read(dataset, '06-FZK-Haus-LoD2-Tex-Storey-CG30-V01-PointCloud-thinned.gml');

    test('point cloud city model', () {
      expectCityModel(cityModel, [458900.0, 5438785.0, 113.5], [458912.0, 5438795.0, 120.017691]);
      expect(featureTypes(cityModel), [
        FeatureType.cityModel,
        FeatureType.building,
        FeatureType.storey,
        FeatureType.groundSurface,
        ...List.filled(4, FeatureType.wallSurface),
        FeatureType.storey,
        FeatureType.roofSurface,
        FeatureType.roofSurface,
        ...List.filled(4, FeatureType.wallSurface),
      ]);
    });

    test('point cloud storey boundaries', () {
      final b = building(cityModel);
      expect(b.featureId().asStr(), testBuildingId);
      expect(items(b.boundaries()), isEmpty);
      const expected = [
        [
          (FeatureType.groundSurface, ' Ground Floor / GroundSurface'),
          (FeatureType.wallSurface, 'Ground Floor / Wall East'),
          (FeatureType.wallSurface, 'Ground Floor / Wall South'),
          (FeatureType.wallSurface, 'Ground Floor / Wall West'),
          (FeatureType.wallSurface, 'Ground Floor / Wall North'),
        ],
        [
          (FeatureType.roofSurface, 'Second Floor / Roof North'),
          (FeatureType.roofSurface, 'Second Floor / Roof South'),
          (FeatureType.wallSurface, 'Second Floor / Wall South'),
          (FeatureType.wallSurface, 'Second Floor / Wall West'),
          (FeatureType.wallSurface, 'Second Floor / Wall East'),
          (FeatureType.wallSurface, 'Second Floor / Wall North'),
        ],
      ];
      final found = storeys(cityModel);
      expect(found, hasLength(expected.length));
      for (var i = 0; i < found.length; i++) {
        final actual = boundarySurfaces(found[i]);
        expect(actual.map((s) => (s.$1, s.$2)), expected[i]);
        expect(actual.map((s) => s.$3), everyElement(isNull));
      }
    });

    test('point cloud round trip', () => expectRoundTrip(cityModel, testBuildingId));
  });
}
