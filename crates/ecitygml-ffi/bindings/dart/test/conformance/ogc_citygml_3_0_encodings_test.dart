// The cases of crates/ecitygml/tests/conformance/ogc-citygml-3.0-encodings.md.
import 'package:ecitygml/ecitygml.dart';
import 'package:test/test.dart';

import 'helpers.dart';

const dataset = 'ogc-citygml-3.0-encodings';

const wall = FeatureType.wallSurface;
const roof = FeatureType.roofSurface;
const ground = FeatureType.groundSurface;

List<FeatureType> featureTypes(CityModel cityModel) =>
    items(cityModel.iterFeatures()).map((f) => f.featureType()).toList();

/// All features a class accepts, in document order.
List<T> allOf<T extends Object>(CityModel cityModel, T? Function(AbstractFeatureKindRef) tryFrom) =>
    items(cityModel.iterFeatures()).map(tryFrom).nonNulls.toList();

List<String> names(Iterator<Code> names) => items(names).map((n) => n.value()).toList();

void expectEnvelope(Envelope envelope, List<double> lower, List<double> upper) {
  final l = envelope.lowerCorner();
  final u = envelope.upperCorner();
  expect([l.x(), l.y(), l.z()], lower.map(close).toList());
  expect([u.x(), u.y(), u.z()], upper.map(close).toList());
}

CityModel roundTrip(CityModel cityModel) {
  final writer = GmlWriter(CitygmlFormat.gml)..finish(cityModel);
  return GmlReader(writer.data(), CitygmlFormat.gml).finish();
}

typedef Surface = ({FeatureType type, String id, String? name, MultiSurfaceProperty? multiSurface});

/// A space's boundaries; all inline wall, roof or ground surfaces.
List<Surface> surfaces(Iterator<AbstractSpaceBoundaryProperty> boundaries) => items(boundaries).map((property) {
  expect(property.href(), isNull);
  final object = property.object()!;
  final id = object.featureId().asStr();
  final feature = AbstractFeatureKindRef.fromSpaceBoundary(object);
  final wallSurface = WallSurface.tryFrom(feature);
  if (wallSurface != null) {
    return (
      type: feature.featureType(),
      id: id,
      name: names(wallSurface.names()).firstOrNull,
      multiSurface: wallSurface.lod2MultiSurface(),
    );
  }
  final roofSurface = RoofSurface.tryFrom(feature);
  if (roofSurface != null) {
    return (
      type: feature.featureType(),
      id: id,
      name: names(roofSurface.names()).firstOrNull,
      multiSurface: roofSurface.lod2MultiSurface(),
    );
  }
  final groundSurface = GroundSurface.tryFrom(feature);
  expect(groundSurface, isNotNull, reason: '${feature.featureType()}');
  return (
    type: feature.featureType(),
    id: id,
    name: names(groundSurface!.names()).firstOrNull,
    multiSurface: groundSurface.lod2MultiSurface(),
  );
}).toList();

double lod2Area(MultiSurfaceProperty? property) => property!.object()!.area3d();

void expectHeight(Iterator<Height> heights, double length) {
  final height = items(heights).single;
  expect(height.highReference().value(), 'highestRoofEdge');
  expect(height.lowReference().value(), 'lowestGroundPoint');
  expect(height.status(), HeightStatusValue.measured);
  expect(height.length().value(), close(length));
  expect(height.length().uom(), '#m');
}

/// The hrefs of a storey's LoD2 surface members (null for inline members).
List<String?> memberHrefs(Storey storey) {
  final property = storey.lod2MultiSurface()!;
  expect(property.href(), isNull);
  return items(property.object()!.surfaceMember()).map((member) {
    expect(member.object() == null, member.href() != null);
    return member.href()?.toString();
  }).toList();
}

/// The relations of the roof surfaces and traffic areas, in document order: (city object, relation type, href).
List<(String, String, String?)> relations(CityModel cityModel) {
  final result = <(String, String, String?)>[];
  for (final feature in items(cityModel.iterFeatures())) {
    final roofSurface = RoofSurface.tryFrom(feature);
    final area = TrafficArea.tryFrom(feature);
    final (String, Iterator<CityObjectRelationProperty>)? entry = roofSurface != null
        ? (roofSurface.featureId().asStr(), roofSurface.relatedTo())
        : area != null
        ? (area.featureId().asStr(), area.relatedTo())
        : null;
    if (entry == null) continue;
    for (final property in items(entry.$2)) {
      expect(property.href(), isNull);
      final relation = property.object()!;
      expect(items(relation.genericAttributes()), isEmpty);
      result.add((entry.$1, relation.relationType().value(), relation.relationTo().href()?.toString()));
    }
  }
  return result;
}

/// (year, month, day) of a date time at 00:00 UTC.
(int, int, int)? date(DateTime? dateTime) {
  if (dateTime == null) return null;
  expect([dateTime.hour(), dateTime.minute(), dateTime.offsetSeconds()], [0, 0, 0]);
  return (dateTime.year(), dateTime.month(), dateTime.day());
}

void main() {
  group('Building_and_garage_LOD2-EPSG25832.gml', () {
    final cityModel = read(dataset, 'Building_and_garage_LOD2-EPSG25832.gml');
    Building theBuilding() => allOf(cityModel, Building.tryFrom).single;

    test('garage city model', () {
      expect(cityModel.cityObjectsLen(), 2);
      expectEnvelope(cityModel.boundedBy()!.envelope()!, [458868.0, 5438343.0, 112.0], [458892.0, 5438362.0, 117.0]);
      expect(featureTypes(cityModel), [
        FeatureType.cityModel,
        FeatureType.building,
        ground,
        ...List.filled(4, wall),
        roof,
        roof,
        FeatureType.buildingPart,
        ...List.filled(4, wall),
        ground,
        roof,
        FeatureType.reliefFeature,
        FeatureType.tinRelief,
      ]);
      expect(items(cityModel.iterCityObjects()), hasLength(17));
    });

    test('garage building', () {
      final b = theBuilding();
      expect(b.featureId().asStr(), 'GML_7b1a5a6f-ddad-4c3d-a507-3eb9ee0a8e68');
      expect(names(b.names()), ['Example Building LOD2']);
      // `class` is reserved in Dart: the getter is `classifier`.
      expect(b.classifier(), isNull);
      expect(items(b.functions()).map((f) => f.value()), ['1000']);
      expect(items(b.usages()), isEmpty);
      expect(b.roofType()?.value(), '1030');
      expect(b.storeysAboveGround(), 1);
      expect(b.storeysBelowGround(), isNull);
      final date = b.dateOfConstruction()!;
      expect([date.year(), date.month(), date.day()], [1985, 1, 1]);
      expectHeight(b.heights(), 6.0);
      const expected = [
        (ground, 'Ground Slab', 50.0),
        (wall, 'Wall South', 30.0),
        (wall, 'Wall North', 30.0),
        (wall, 'Wall East', 20.0),
        (wall, 'Wall West', 20.0),
        (roof, 'Roof North', 32.01562118716424),
        (roof, 'Roof South', 32.01562118716424),
      ];
      final actual = surfaces(b.boundaries());
      expect(actual.map((s) => (s.type, s.name)), expected.map((e) => (e.$1, e.$2)));
      expect(actual.map((s) => lod2Area(s.multiSurface)), expected.map((e) => close(e.$3)));
    });

    test('garage building part', () {
      final property = items(theBuilding().buildingParts()).single;
      expect(property.href(), isNull);
      final part = property.object()!;
      expect(part.featureId().asStr(), 'GMLID_BUI379228_1244_301');
      expect(names(part.names()), ['Example BuildingPart LOD2']);
      expect(part.classifier(), isNull);
      expect(items(part.functions()).map((f) => f.value()), ['1630']);
      expect(items(part.usages()), isEmpty);
      expect(part.roofType()?.value(), '1010');
      final date = part.dateOfConstruction()!;
      expect([date.year(), date.month(), date.day()], [1985, 1, 1]);
      expectHeight(part.heights(), 2.5);
      // The west wall's area is left out: its member is a gml:OrientableSurface, not read yet.
      const expected = [
        (wall, 'Garage Wall East', 9.600000023841858),
        (wall, 'Garage Wall South', 6.25),
        (wall, 'Garage Wall West', null),
        (wall, 'Garage Wall North', 5.75),
        (ground, 'Garage Ground Slab', 10.0),
        (roof, 'Garage Roof', 10.012492197250394),
      ];
      final actual = surfaces(part.boundaries());
      expect(actual.map((s) => (s.type, s.name)), expected.map((e) => (e.$1, e.$2)));
      for (var i = 0; i < actual.length; i++) {
        final area = expected[i].$3;
        if (area != null) expect(lod2Area(actual[i].multiSurface), close(area));
      }
    });

    test('garage relief', () {
      final relief = allOf(cityModel, ReliefFeature.tryFrom).single;
      expect(relief.featureId().asStr(), 'GML_6bb30328-7599-4500-90ef-766fde6aa67b');
      expect(names(relief.names()), ['Example TIN LOD2']);
      expect(relief.lod(), LevelOfDetail.two);
      final component = items(relief.reliefComponents()).single;
      expect(component.href(), isNull);
      expect(component.object()!.featureType(), FeatureType.tinRelief);

      final tinRelief = allOf(cityModel, TinRelief.tryFrom).single;
      expect(tinRelief.featureId().asStr(), 'GML_4eb161b0-aa7e-4087-937c-5c4c427c7fc9');
      expect(names(tinRelief.names()), ['Ground']);
      expect(tinRelief.lod(), LevelOfDetail.two);
      final tin = tinRelief.tin()!;
      expect(tin.href(), isNull);
      final surface = tin.object()!;
      expect(items(surface.triangles()), hasLength(12));
      expect(surface.area3d(), close(399.8446647372588));
    });

    test('garage round trip', () {
      final written = roundTrip(cityModel);
      expect(featureTypes(written), featureTypes(cityModel));
      final ids = [
        ...allOf(written, Building.tryFrom).map((b) => b.featureId().asStr()),
        ...allOf(written, BuildingPart.tryFrom).map((p) => p.featureId().asStr()),
        ...allOf(written, ReliefFeature.tryFrom).map((r) => r.featureId().asStr()),
        ...allOf(written, TinRelief.tryFrom).map((t) => t.featureId().asStr()),
      ];
      expect(ids, [
        'GML_7b1a5a6f-ddad-4c3d-a507-3eb9ee0a8e68',
        'GMLID_BUI379228_1244_301',
        'GML_6bb30328-7599-4500-90ef-766fde6aa67b',
        'GML_4eb161b0-aa7e-4087-937c-5c4c427c7fc9',
      ]);
    });
  });

  group('BuildingUnits_Storeys_xlink.gml', () {
    final cityModel = read(dataset, 'BuildingUnits_Storeys_xlink.gml');

    test('units city model', () {
      expect(cityModel.cityObjectsLen(), 1);
      expectEnvelope(cityModel.boundedBy()!.envelope()!, [457841.0, 5439082.0, 111.0], [457854.0, 5439093.0, 121.0]);
      List<FeatureType> room(int walls) => [
        FeatureType.buildingRoom,
        ...List.filled(walls, FeatureType.interiorWallSurface),
        FeatureType.floorSurface,
        FeatureType.ceilingSurface,
      ];
      expect(featureTypes(cityModel), [
        FeatureType.cityModel,
        FeatureType.building,
        ...List.filled(3, wall),
        roof,
        wall,
        roof,
        ground,
        ...room(8),
        ...room(8),
        ...room(4),
        FeatureType.buildingUnit,
        FeatureType.buildingUnit,
        FeatureType.storey,
        FeatureType.storey,
      ]);
      expect(items(cityModel.iterCityObjects()), hasLength(41));
    });

    test('units building', () {
      final b = allOf(cityModel, Building.tryFrom).single;
      expect(b.featureId().asStr(), 'building_unit_example_1');
      expect(items(b.names()), isEmpty);
      expect(items(b.functions()), isEmpty);
      expect(items(b.usages()), isEmpty);
      expect(b.classifier(), isNull);
      expect(b.roofType(), isNull);
      const expected = [
        (wall, 'Outer Wall 1 (West)', 89.375),
        (wall, 'Outer Wall 2 (South)', 81.25),
        (wall, 'Outer Wall 3 (East)', 89.375),
        (roof, 'Roof 1 (North)', 86.53792521201326),
        (wall, 'Outer Wall 4 (North)', 81.25),
        (roof, 'Roof 2 (South)', 86.53792521201326),
        (ground, 'Base Surface', 143.0),
      ];
      final actual = surfaces(b.boundaries());
      expect(actual.map((s) => (s.type, s.name)), expected.map((e) => (e.$1, e.$2)));
      expect(actual.map((s) => lod2Area(s.multiSurface)), expected.map((e) => close(e.$3)));
    });

    test('units subdivisions', () {
      final b = allOf(cityModel, Building.tryFrom).single;
      final subdivisions = items(b.buildingSubdivisions()).toList();
      expect(subdivisions.map((s) => s.href()), everyElement(isNull));
      expect(subdivisions.map((s) => s.object()!.featureType()), [
        FeatureType.buildingUnit,
        FeatureType.buildingUnit,
        FeatureType.storey,
        FeatureType.storey,
      ]);
      final units = allOf(cityModel, BuildingUnit.tryFrom);
      expect(units.map((u) => u.featureId().asStr()), ['BuildingUnit_apartment1', 'BuildingUnit_apartment2']);
      for (final unit in units) {
        expect(items(unit.functions()).map((f) => f.value()), ['apartment']);
        expect(unit.classifier(), isNull);
        expect(items(unit.usages()), isEmpty);
        expect(items(unit.boundaries()), isEmpty);
        expect(unit.lod2MultiSurface(), isNull);
      }
      final storeys = allOf(cityModel, Storey.tryFrom);
      expect(storeys.map((s) => s.featureId().asStr()), ['storey1', 'storey2']);
      for (final storey in storeys) {
        expect(items(storey.names()), isEmpty);
        expect(storey.classifier(), isNull);
        expect(items(storey.functions()), isEmpty);
        expect(items(storey.usages()), isEmpty);
        expect(items(storey.boundaries()), isEmpty);
      }
    });

    test('units storey geometry', () {
      const expected = [
        (
          [
            '#Wall_1_PolyID82397_997_453711_16336011',
            '#Wall_1_PolyID82397_997_453711_16336012',
            '#Wall_1_PolyID82397_997_453711_163360136',
          ],
          [457841.1, 5439082.1, 111.1],
          [457853.9, 5439092.9, 113.9],
        ),
        (
          [
            '#Wall_1_PolyID82397_997_453711_163360112',
            '#Wall_1_PolyID82397_997_453711_163360122',
            '#Wall_1_PolyID82397_997_453711_1633601362',
          ],
          [457841.1, 5439082.1, 114.1],
          [457853.9, 5439092.9, 116.9],
        ),
      ];
      final storeys = allOf(cityModel, Storey.tryFrom);
      expect(storeys, hasLength(expected.length));
      for (var i = 0; i < storeys.length; i++) {
        final (hrefs, lower, upper) = expected[i];
        expect(memberHrefs(storeys[i]), [null, ...hrefs, null, null]);
        final multiSurface = storeys[i].lod2MultiSurface()!.object()!;
        expect(multiSurface.area3d, throwsA(anything));
        expectEnvelope(storeys[i].boundedBy()!.envelope()!, lower, upper);
      }
    });

    test('units round trip', () {
      final written = roundTrip(cityModel);
      expect(featureTypes(written), featureTypes(cityModel));
      expect(allOf(written, Building.tryFrom).single.featureId().asStr(), 'building_unit_example_1');
      expect(
        allOf(written, Storey.tryFrom).map(memberHrefs).toList(),
        allOf(cityModel, Storey.tryFrom).map(memberHrefs).toList(),
      );
    });
  });

  group('Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml', () {
    final cityModel = read(dataset, 'Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml');

    test('road bridge city model', () {
      expect(cityModel.cityObjectsLen(), 2);
      expect(cityModel.boundedBy(), isNull);
      const section = [
        FeatureType.section,
        FeatureType.trafficSpace,
        FeatureType.trafficArea,
        FeatureType.trafficSpace,
        FeatureType.trafficArea,
      ];
      expect(featureTypes(cityModel), [
        FeatureType.cityModel,
        FeatureType.bridge,
        ground,
        roof,
        roof,
        ...List.filled(4, wall),
        FeatureType.road,
        ...section,
        ...section,
        ...section,
      ]);
      expect(items(cityModel.iterCityObjects()), hasLength(24));
    });

    test('road bridge bridge', () {
      final bridge = allOf(cityModel, Bridge.tryFrom).single;
      expect(bridge.featureId().asStr(), 'id_bridge1');
      expect(items(bridge.names()), isEmpty);
      expect(items(bridge.relatedTo()), isEmpty);
      const expected = [
        ('id_groundsurface1', 77500.15996032),
        ('id_roofsurface1', 38750.07998016),
        ('id_roofsurface2', 38750.07998016),
        ('id_wallsurface4', 10075.02000744),
        ('id_wallsurface1', 20150.04001488),
        ('id_wallsurface2', 10075.02000744),
        ('id_wallsurface3', 20150.04001488),
      ];
      final actual = surfaces(bridge.boundaries());
      expect(actual.map((s) => s.id), expected.map((e) => e.$1));
      expect(actual.map((s) => lod2Area(s.multiSurface)), expected.map((e) => close(e.$2)));
    });

    test('road bridge road', () {
      final road = allOf(cityModel, Road.tryFrom).single;
      expect(road.featureId().asStr(), 'id_road1');
      expect(items(road.relatedTo()), isEmpty);
      expect(items(road.trafficSpaces()), isEmpty);
      expect(items(road.auxiliaryTrafficSpaces()), isEmpty);
      final sections = items(road.sections()).map((p) {
        expect(p.href(), isNull);
        return p.object()!;
      }).toList();
      expect(sections.map((s) => s.featureId().asStr()), ['id_section1', 'id_section2', 'id_section3']);
      final spaces = sections
          .expand(
            (section) => items(section.trafficSpaces()).map((p) {
              expect(p.href(), isNull);
              return p.object()!;
            }),
          )
          .toList();
      const numbers = [1, 2, 5, 6, 3, 4];
      expect(spaces.map((s) => s.featureId().asStr()), numbers.map((n) => 'id_trafficspace$n'));
      for (var i = 0; i < spaces.length; i++) {
        final boundary = items(spaces[i].boundaries()).single;
        expect(boundary.href(), isNull);
        final area = boundary.object()!;
        expect(area.featureType(), FeatureType.trafficArea);
        expect(area.featureId().asStr(), 'id_trafficarea${numbers[i]}');
      }
    });

    test('road bridge relations', () {
      expect(relations(cityModel), [
        ('id_roofsurface1', 'equal', 'id_trafficarea5'),
        ('id_roofsurface2', 'equal', 'id_trafficarea6'),
        ('id_trafficarea5', 'equal', 'id_roofSurface1'),
        ('id_trafficarea6', 'equal', 'id_roofSurface2'),
      ]);
      expect(allOf(cityModel, WallSurface.tryFrom).every((w) => items(w.relatedTo()).isEmpty), isTrue);
      expect(allOf(cityModel, GroundSurface.tryFrom).every((g) => items(g.relatedTo()).isEmpty), isTrue);
    });

    test('road bridge round trip', () {
      final written = roundTrip(cityModel);
      expect(featureTypes(written), featureTypes(cityModel));
      expect(allOf(written, Bridge.tryFrom).map((b) => b.featureId().asStr()), ['id_bridge1']);
      expect(allOf(written, Road.tryFrom).map((r) => r.featureId().asStr()), ['id_road1']);
      expect(relations(written), relations(cityModel));
    });
  });

  group('historicalSuccession_CityGML_3.0_LOD2_Versioning.gml', () {
    final cityModel = read(dataset, 'historicalSuccession_CityGML_3.0_LOD2_Versioning.gml');

    test('versioning city model', () {
      expect(cityModel.cityObjectsLen(), 4);
      expect(cityModel.boundedBy(), isNull);
      final types = featureTypes(cityModel);
      expect(types, hasLength(60));
      expect(types.first, FeatureType.cityModel);
      final counts = <FeatureType, int>{};
      for (final type in types) {
        counts[type] = (counts[type] ?? 0) + 1;
      }
      expect(counts, {
        FeatureType.cityModel: 1,
        FeatureType.building: 4,
        FeatureType.buildingPart: 5,
        roof: 14,
        wall: 31,
        ground: 5,
      });
      expect(items(cityModel.iterCityObjects()), hasLength(59));
    });

    test('versioning buildings', () {
      const expected = [
        ('BU_69381AL47_2000-01-01', 'Building A', (2000, 1, 1), (2015, 1, 1), ['BU_69381AL47_1']),
        ('BU_69381AL49_2000-01-01', 'Building B', (2000, 1, 1), (2015, 1, 1), ['BU_69381AL49_1_2000-01-01']),
        (
          'BU_69381AL49_2015-01-01',
          'Building B',
          (2015, 1, 1),
          null,
          ['BU_69381AL49_1_2015-01-01', 'BU_69381AL49_2_2015-01-01'],
        ),
        ('BU_69381AL50_2015-01-01', 'Building C', (2015, 1, 1), null, ['BU_69381AL50_1']),
      ];
      final buildings = allOf(cityModel, Building.tryFrom);
      expect(buildings, hasLength(expected.length));
      for (var i = 0; i < buildings.length; i++) {
        final b = buildings[i];
        final (id, name, created, terminated, parts) = expected[i];
        expect(b.featureId().asStr(), id);
        expect(names(b.names()).first, name);
        expect(date(b.creationDate()), created);
        expect(date(b.terminationDate()), terminated);
        final properties = items(b.buildingParts()).toList();
        expect(properties.map((p) => p.href()), everyElement(isNull));
        expect(properties.map((p) => p.object()!.featureId().asStr()), parts);
        expect(items(b.heights()), isEmpty);
        expect(items(b.boundaries()), isEmpty);
      }
    });

    test('versioning building parts', () {
      const expected = [
        ('BU_69381AL47_1', 13.015, 8),
        ('BU_69381AL49_1_2000-01-01', 10.63, 9),
        ('BU_69381AL49_1_2015-01-01', 10.63, 9),
        ('BU_69381AL49_2_2015-01-01', 8.743, 7),
        ('BU_69381AL50_1', 18.215, 17),
      ];
      final parts = allOf(cityModel, BuildingPart.tryFrom);
      expect(parts, hasLength(expected.length));
      for (var i = 0; i < parts.length; i++) {
        final (id, height, boundaries) = expected[i];
        expect(parts[i].featureId().asStr(), id);
        expectHeight(parts[i].heights(), height);
        expect(items(parts[i].boundaries()), hasLength(boundaries));
        expect(parts[i].creationDate(), isNull);
        expect(items(parts[i].names()), isEmpty);
      }
    });

    test('versioning round trip', () {
      final written = roundTrip(cityModel);
      expect(featureTypes(written), featureTypes(cityModel));
      List<String> ids(CityModel model) => [
        ...allOf(model, Building.tryFrom).map((b) => b.featureId().asStr()),
        ...allOf(model, BuildingPart.tryFrom).map((p) => p.featureId().asStr()),
      ];
      List<((int, int, int)?, (int, int, int)?)> dates(CityModel model) =>
          allOf(model, Building.tryFrom).map((b) => (date(b.creationDate()), date(b.terminationDate()))).toList();
      expect(ids(written), ids(cityModel));
      expect(dates(written), dates(cityModel));
    });
  });
}
