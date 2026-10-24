// The cases of crates/ecitygml/tests/conformance/railway-scene.md.
import 'package:ecitygml/ecitygml.dart';
import 'package:test/test.dart';

import 'helpers.dart';

const templateA = '#Mult_SO043561_5693_194007';
const templateB = '#Mult_SO045475_3243_790864';
const inlineTemplates = {'Forest tree 3', 'Tree1', 'Forest tree 1'};
const templateATrees = {'Forest tree 4', 'Forest tree 9', 'Forest tree 5'};

const wall = FeatureType.wallSurface;
const roof = FeatureType.roofSurface;
const ground = FeatureType.groundSurface;
const closure = FeatureType.closureSurface;

List<FeatureType> featureTypes(CityModel cityModel) =>
    items(cityModel.iterFeatures()).map((f) => f.featureType()).toList();

/// All features a class accepts, in document order.
List<T> allOf<T extends Object>(CityModel cityModel, T? Function(AbstractFeatureKindRef) tryFrom) =>
    items(cityModel.iterFeatures()).map(tryFrom).nonNulls.toList();

/// A tree's inline LoD3 implicit geometry.
ImplicitGeometry implicitGeometry(SolitaryVegetationObject tree) {
  final property = tree.lod3ImplicitRepresentation()!;
  expect(property.href(), isNull);
  return property.object()!;
}

String? templateHref(SolitaryVegetationObject tree) => implicitGeometry(tree).relativeGeometry()?.href()?.toString();

double matrix(ImplicitGeometry geometry, int row, int column) => geometry.transformationMatrix().get(row, column);

void main() {
  group('Railway_Scene_LoD3__v3-thinned.gml', () {
    final cityModel = read('railway-scene', 'Railway_Scene_LoD3__v3-thinned.gml');

    test('railway city model', () {
      expect(cityModel.cityObjectsLen(), 52);
      expect(cityModel.boundedBy(), isNull);
      final types = featureTypes(cityModel);
      expect(types, hasLength(232));
      expect(types.first, FeatureType.cityModel);
      final counts = <FeatureType, int>{};
      for (final type in types) {
        counts[type] = (counts[type] ?? 0) + 1;
      }
      expect(counts, {
        FeatureType.cityModel: 1,
        FeatureType.solitaryVegetationObject: 15,
        FeatureType.tunnel: 4,
        FeatureType.tunnelInstallation: 8,
        FeatureType.railway: 10,
        FeatureType.bridge: 4,
        FeatureType.bridgeConstructiveElement: 3,
        FeatureType.bridgeInstallation: 2,
        FeatureType.building: 3,
        FeatureType.buildingInstallation: 56,
        FeatureType.cityFurniture: 11,
        FeatureType.cityObjectGroup: 1,
        FeatureType.genericOccupiedSpace: 2,
        FeatureType.waterBody: 1,
        FeatureType.waterSurface: 1,
        FeatureType.waterGroundSurface: 1,
        FeatureType.reliefFeature: 1,
        FeatureType.tinRelief: 1,
        wall: 33,
        roof: 12,
        ground: 7,
        closure: 8,
        FeatureType.doorSurface: 9,
        FeatureType.windowSurface: 34,
        FeatureType.outerCeilingSurface: 3,
        FeatureType.outerFloorSurface: 1,
      });
      expect(items(cityModel.iterCityObjects()), hasLength(231));
    });

    test('railway tunnels', () {
      const expected = [
        ('GMLID_BUI142242_863_347', 'Tunnel KIT/KHH-3', [ground, wall, roof, wall, closure, closure]),
        ('GMLID_BUI336993_213_9312', 'Tunnel KIT/KHH-2', [wall, roof, wall, closure, closure, ground]),
        ('GMLID_BUI289877_1911_4122', 'Tunnel KIT/KHH-4', [wall, ground, closure, wall, roof, closure]),
        ('GMLID_BUI180021_673_14143', 'Tunnel KIT/KHH-1', [ground, wall, roof, closure, closure, wall]),
      ];
      final tunnels = allOf(cityModel, Tunnel.tryFrom);
      expect(tunnels, hasLength(expected.length));
      for (var i = 0; i < tunnels.length; i++) {
        final tunnel = tunnels[i];
        final (id, name, boundaries) = expected[i];
        expect(tunnel.featureId().asStr(), id);
        expect(firstName(tunnel.names()), name);
        final properties = items(tunnel.boundaries()).toList();
        expect(properties.map((p) => p.href()), everyElement(isNull));
        expect(properties.map((p) => p.object()!.featureType()), boundaries);
        // `class` is reserved in Dart: the getter is `classifier`.
        expect(tunnel.classifier(), isNull);
        expect(items(tunnel.functions()), isEmpty);
        expect(items(tunnel.usages()), isEmpty);
        expect(items(tunnel.tunnelParts()), isEmpty);
        final created = tunnel.creationDate()!;
        expect([created.year(), created.month(), created.day()], [2015, 3, 6]);
        expect([created.hour(), created.minute()], [0, 0]);
        expect(created.offsetSeconds(), 3600);
        expect(tunnel.relativeToTerrain(), RelativeToTerrain.entirelyAboveTerrain);
      }
    });

    test('railway trees', () {
      const expected = [
        ('GMLID_SO0158953_776_12462', 'Forest tree 3', '1070', '1800', <String>[]),
        ('GMLID_SO092422_3593_9527', 'Tree1', null, '9999', ['LOD3']),
        ('GMLID_SO0200811_525_4986', 'Forest tree 1', '1060', '1640', <String>[]),
        ('GMLID_SO0321978_1466_7441', 'Forest tree 4', '1070', '1800', <String>[]),
        ('GMLID_SO0260143_1214_1315', 'Forest tree 11', '1060', '1640', <String>[]),
        ('GMLID_SO0400934_2926_3381', 'Forest tree 12', '1060', '1640', <String>[]),
        ('GMLID_SO0124800_3522_13577', 'Forest tree 13', '1060', '1640', <String>[]),
        ('GMLID_SO0443764_1492_9667', 'Forest tree 14', '1060', '1640', <String>[]),
        ('GMLID_SO015374_872_14131', 'Forest tree 2', '1060', '1640', <String>[]),
        ('GMLID_SO081792_2341_11961', 'Forest tree 10', '1060', '1640', <String>[]),
        ('GMLID_SO0283142_1335_8999', 'Forest tree 7', '1060', '1640', <String>[]),
        ('GMLID_SO0107241_3793_12555', 'Forest tree 9', '1070', '1800', <String>[]),
        ('GMLID_SO0286258_965_2893', 'Forest tree 5', '1070', '1800', <String>[]),
        ('GMLID_SO0410128_214_10515', 'Forest tree 6', '1060', '1640', <String>[]),
        ('GMLID_SO086970_1053_8814', 'Forest tree 8', '1060', '1640', <String>[]),
      ];
      final trees = allOf(cityModel, SolitaryVegetationObject.tryFrom);
      expect(trees, hasLength(expected.length));
      for (var i = 0; i < trees.length; i++) {
        final tree = trees[i];
        final (id, name, classifier, species, functions) = expected[i];
        expect(tree.featureId().asStr(), id);
        expect(firstName(tree.names()), name);
        expect(tree.classifier()?.value(), classifier);
        expect(tree.species()?.value(), species);
        expect(items(tree.functions()).map((f) => f.value()), functions);
        expect(items(tree.usages()), isEmpty);
        expect(tree.lod1ImplicitRepresentation(), isNull);
        expect(tree.lod2ImplicitRepresentation(), isNull);
      }
    });

    test('railway tree templates', () {
      for (final tree in allOf(cityModel, SolitaryVegetationObject.tryFrom)) {
        final geometry = implicitGeometry(tree);
        expect(geometry.mimeType(), isNull);
        expect(
          [for (var i = 0; i < 4; i++) matrix(geometry, i, i)],
          [close(30.0), close(30.0), close(30.0), close(1.0)],
        );
        final name = firstName(tree.names());
        final property = geometry.relativeGeometry()!;
        if (inlineTemplates.contains(name)) {
          expect(property.href(), isNull);
          final multiSurface = MultiSurface.tryFrom(property.object()!);
          expect(multiSurface, isNotNull, reason: name);
          expect(items(multiSurface!.surfaceMember()), hasLength(1));
        } else {
          expect(property.object(), isNull);
          expect(templateHref(tree), templateATrees.contains(name) ? templateA : templateB, reason: name);
        }
      }
    });

    test('railway tree placement', () {
      for (final tree in allOf(cityModel, SolitaryVegetationObject.tryFrom)) {
        final geometry = implicitGeometry(tree);
        final pos = geometry.referencePoint().object()!.pos();
        final name = firstName(tree.names());
        final reference = name == 'Tree1'
            ? [-568.8000793496976, 457.60044759869743, 105.00139681350242]
            : [-600.0, 400.0, -150.0];
        expect([pos.x(), pos.y(), pos.z()], reference.map(close).toList());
        final translation = switch (name) {
          'Tree1' => [0.0, 0.0, 0.0],
          'Forest tree 3' => [39.4421005419207, 220.3838834926932, 268.5013679006178],
          _ => null,
        };
        if (translation != null) {
          expect([for (var row = 0; row < 3; row++) matrix(geometry, row, 3)], translation.map(close).toList());
        }
      }
    });

    test('railway furniture', () {
      const expected = [
        ('GMLID_7431654_78949_792', '1090'),
        ('GMLID_0528986_170479_94', 'OTHERS'),
        ('GMLID_4323540_367099_910', '1090'),
        ('GMLID_1381455_184173_656', 'OTHERS'),
        ('GMLID_1429491_351612_1485', '1090'),
        ('GMLID_5361967_192822_672', '1090'),
        ('GMLID_2108434_31807_876', '1090'),
        ('GMLID_0373494_301709_129', '1540'),
        ('GMLID_6162422_289094_1279', '1090'),
        ('GMLID_3313190_307178_612', '1090'),
        ('GMLID_855011_330784_753', '1540'),
      ];
      final furniture = allOf(cityModel, CityFurniture.tryFrom);
      expect(furniture, hasLength(expected.length));
      for (var i = 0; i < furniture.length; i++) {
        final item = furniture[i];
        expect(item.featureId().asStr(), expected[i].$1);
        expect(items(item.functions()).map((f) => f.value()), [expected[i].$2]);
        expect(item.classifier(), isNull);
        expect(items(item.usages()), isEmpty);
        expect(item.lod3ImplicitRepresentation(), isNull);
        final property = item.lod3MultiSurface()!;
        expect(property.href(), isNull);
        expect(items(property.object()!.surfaceMember()), hasLength(1));
      }
    });

    test('railway relief', () {
      final relief = allOf(cityModel, ReliefFeature.tryFrom).single;
      expect(relief.featureId().asStr(), 'GMLID_TIN436865_187531_1154');
      expect(items(relief.names()), isEmpty);
      expect(relief.lod(), LevelOfDetail.three);
      final component = items(relief.reliefComponents()).single;
      expect(component.href(), isNull);
      expect(component.object()!.featureType(), FeatureType.tinRelief);

      final tinRelief = allOf(cityModel, TinRelief.tryFrom).single;
      expect(tinRelief.featureId().asStr(), 'UUID_5aa70b07-6bbf-427b-8222-d72ed77dbfa9');
      expect(tinRelief.lod(), LevelOfDetail.three);
      final tin = tinRelief.tin()!;
      expect(tin.href(), isNull);
      final surface = tin.object()!;
      expect(items(surface.triangles()), hasLength(1));
      expect(surface.area3d(), close(3.2750424144626247));
    });

    test('railway buildings and bridges', () {
      expect(
        allOf(
          cityModel,
          Building.tryFrom,
        ).map((b) => (b.featureId().asStr(), firstName(b.names()), items(b.boundaries()).length)),
        [
          ('GMLID_BUI184698_512_898', 'Station KIT/KHH-1', 13),
          ('GMLID_BUI46739_1739_10911', 'Chapel KIT/KHH-1', 19),
          ('GMLID_BUI130363_1235_6047', 'Boatshouse KIT/KHH-1', 8),
        ],
      );
      expect(allOf(cityModel, Bridge.tryFrom).map((b) => (b.featureId().asStr(), firstName(b.names()))), [
        ('GMLID_BUI205585_1385_1373', 'Bridge KIT 4'),
        ('GMLID_BUI51891_765_738', 'Bridge KIT 3'),
        ('GMLID_BUI100628_817_8083', 'Bridge KIT 2'),
        ('GMLID_BUI30683_572_6686', 'Bridge KIT 1'),
      ]);
    });

    test('railway round trip', () {
      final writer = GmlWriter(CitygmlFormat.gml)..finish(cityModel);
      final written = GmlReader(writer.data(), CitygmlFormat.gml).finish();
      expect(featureTypes(written), featureTypes(cityModel));
      List<String> ids(CityModel model) => [
        ...allOf(model, Tunnel.tryFrom).map((x) => x.featureId().asStr()),
        ...allOf(model, SolitaryVegetationObject.tryFrom).map((x) => x.featureId().asStr()),
        ...allOf(model, CityFurniture.tryFrom).map((x) => x.featureId().asStr()),
        ...allOf(model, Building.tryFrom).map((x) => x.featureId().asStr()),
        ...allOf(model, Bridge.tryFrom).map((x) => x.featureId().asStr()),
      ];
      List<String?> hrefs(CityModel model) => allOf(model, SolitaryVegetationObject.tryFrom).map(templateHref).toList();
      expect(ids(written), ids(cityModel));
      expect(hrefs(written), hrefs(cityModel));
    });
  });
}
