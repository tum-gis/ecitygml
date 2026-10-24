// The cases of crates/ecitygml/tests/api/types.md.
import 'package:ecitygml/ecitygml.dart';
import 'package:test/test.dart';

import '../helpers.dart';
import 'helpers.dart';

const tum = 'tum-main-entrance/TUM-Main-Entrance.gml';
const asamRoadShape = 'asam-opendrive/ASAM-UC_RoadShape.gml';
const asamJunction = 'asam-opendrive/ASAM-Ex_Bidirectional_Junction.gml';
const railway = 'railway-scene/Railway_Scene_LoD3__v3-thinned.gml';
const sig3d = 'http://www.sig3d.org/codelists/citygml/2.0/building/2.0/_AbstractBuilding_';

/// The first feature that `tryFrom` accepts.
T first<T extends Object>(CityModel cityModel, T? Function(AbstractFeatureKindRef) tryFrom) =>
    items(cityModel.iterFeatures()).map(tryFrom).nonNulls.first;

/// `tryFrom` accepts exactly the features of its feature type.
void expectTryFromMatches(CityModel cityModel, List<(Object? Function(AbstractFeatureKindRef), FeatureType)> types) {
  for (final feature in items(cityModel.iterFeatures())) {
    for (final (tryFrom, featureType) in types) {
      expect(tryFrom(feature) != null, feature.featureType() == featureType,
          reason: '$featureType as ${feature.featureType()}');
    }
  }
}

void main() {
  test('direct position new', () {
    final position = DirectPosition(1.0, 2.0, 3.0);
    expect([position.x(), position.y(), position.z()], [1.0, 2.0, 3.0]);
    expect(() => DirectPosition(double.nan, 0.0, 0.0), throwsError(ErrorKind.invalidArgument, 'non-finite'));
  });

  test('level of detail index', () {
    final levels = [LevelOfDetail.zero, LevelOfDetail.one, LevelOfDetail.two, LevelOfDetail.three];
    for (final (index, lod) in levels.indexed) {
      expect(lod.asIndex(), index);
      expect(LevelOfDetail.tryFrom(index), lod);
    }
    expect(() => LevelOfDetail.tryFrom(4), throwsError(ErrorKind.invalidArgument, '4'));
  });

  test('feature type name', () {
    expect(FeatureType.building.toString(), 'Building');
    expect(FeatureType.tinRelief.toString(), 'TinRelief');
  });

  test('date from parts', () {
    final date = Date.fromParts(2020, 1, 2, 3600);
    expect([date.year(), date.month(), date.day(), date.offsetSeconds()], [2020, 1, 2, 3600]);
    final start = date.startOfDay();
    expect([start.hour(), start.minute(), start.second()], [0, 0, 0]);
    expect(start.toRfc3339(), '2020-01-02T00:00:00+01:00');

    expect(() => Date.fromParts(2021, 2, 30, 0), throwsError(ErrorKind.invalidArgument, 'do not form a valid date'));
  });

  test('date time from parts', () {
    final dateTime = DateTime.fromParts(2017, 1, 23, 13, 14, 15, 500000000, -7200);
    expect([dateTime.year(), dateTime.month(), dateTime.day()], [2017, 1, 23]);
    expect([dateTime.hour(), dateTime.minute(), dateTime.second()], [13, 14, 15]);
    expect(dateTime.nanosecond(), 500000000);
    expect(dateTime.offsetSeconds(), -7200);
    expect(dateTime.timestamp(), 1485184455);
    expect(dateTime.timestampSubsecNanos(), 500000000);
    expect(dateTime.toRfc3339(), '2017-01-23T13:14:15.500-02:00');

    expect(() => DateTime.fromParts(2020, 1, 1, 0, 0, 0, 0, 30),
        throwsError(ErrorKind.invalidArgument, 'timezone offset of 30 s is invalid'));
  });

  test('date time read', () {
    expect(first(read(fzkLod2), Building.tryFrom).creationDate()?.toRfc3339(), '2017-01-23T00:00:00+01:00');
  });

  test('try from matches feature type', () {
    expectTryFromMatches(read(fzkLod3), [
      (Building.tryFrom, FeatureType.building),
      (WallSurface.tryFrom, FeatureType.wallSurface),
      (RoofSurface.tryFrom, FeatureType.roofSurface),
      (GroundSurface.tryFrom, FeatureType.groundSurface),
      (DoorSurface.tryFrom, FeatureType.doorSurface),
      (WindowSurface.tryFrom, FeatureType.windowSurface),
    ]);
    expectTryFromMatches(read(asamRoadShape), [
      (Road.tryFrom, FeatureType.road),
      (Section.tryFrom, FeatureType.section),
      (TrafficSpace.tryFrom, FeatureType.trafficSpace),
      (TrafficArea.tryFrom, FeatureType.trafficArea),
      (AuxiliaryTrafficSpace.tryFrom, FeatureType.auxiliaryTrafficSpace),
      (AuxiliaryTrafficArea.tryFrom, FeatureType.auxiliaryTrafficArea),
    ]);
  });

  test('feature from city object', () {
    final cityObject = items(read(asamJunction).iterCityObjects()).first;
    expect(cityObject.featureType(), FeatureType.road);
    final feature = AbstractFeatureKindRef.fromCityObject(cityObject);
    expect(feature.featureType(), FeatureType.road);
    expect(Road.tryFrom(feature)?.featureId().asStr(), 'UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f');
    expect(Building.tryFrom(feature), isNull);
  });

  test('matrix index out of range', () {
    final tree = items(read(railway).iterFeatures())
        .map(SolitaryVegetationObject.tryFrom)
        .nonNulls
        .firstWhere((tree) => tree.featureId().asStr() == 'GMLID_SO092422_3593_9527');
    final matrix = tree.lod3ImplicitRepresentation()!.object()!.transformationMatrix();
    expect(matrix.get(3, 3), 1.0);
    for (final (row, column) in [(4, 0), (0, 4)]) {
      expect(() => matrix.get(row, column), throwsError(ErrorKind.invalidArgument, 'out of range'));
    }
  });

  test('gml id', () {
    final cityModel = read(fzkLod1);
    final generated = cityModel.featureId().asStr();
    expect(generated, startsWith('ecitygml-gen-feature-'));
    expect(cityModel.id()?.asStr(), generated);

    final wall = first(read(fzkLod2), WallSurface.tryFrom);
    expect(wall.id()?.asStr(), 'GML_5856d7ad-5e34-498a-817b-9544bfbb1475');
    expect(wall.featureId().asStr(), 'GML_5856d7ad-5e34-498a-817b-9544bfbb1475');

    expect(first(read(tum), Building.tryFrom).id()?.asStr(), 'DEBY_LOD2_4959457');
  });

  test('code space', () {
    final building = first(read(fzkLod2), Building.tryFrom);
    final code = building.classifier()!.code();
    expect((code.value(), code.codeSpace()), ('1000', '${sig3d}class.xml'));
    expect(items(building.functions()).map((f) => f.code().codeSpace()), ['${sig3d}function.xml']);
    expect(items(building.usages()).map((u) => u.code().codeSpace()), ['${sig3d}usage.xml']);

    final functions = items(first(read(tum), Building.tryFrom).functions());
    expect(functions.map((f) => (f.value(), f.code().codeSpace())), [('31001_3020', null)]);

    final names = items(read(fzkLod1).names());
    expect(names.map((n) => (n.value(), n.codeSpace())), [('AC14-FZK-Haus', null)]);
  });
}
