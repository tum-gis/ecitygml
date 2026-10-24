// The cases of crates/ecitygml/tests/conformance/asam-opendrive.md.
import 'package:ecitygml/ecitygml.dart';
import 'package:test/test.dart';

import 'helpers.dart';

const roadShapeFile = 'ASAM-UC_RoadShape.gml';
const junctionFile = 'ASAM-Ex_Bidirectional_Junction.gml';

const spaceIds = [
  'UUID_ae81947d-a661-3678-a5ee-eed58b68694f',
  'UUID_6e4de408-1e54-3869-b7ce-1be3f2261421',
  'UUID_9582b02f-5cc7-38f8-b79c-a3a18b31856c',
  'UUID_c772e261-27f1-30b6-8a94-1ccf23e71a74',
  'UUID_656f23c9-92b6-3c98-a1bf-40b5f2625b13',
  'UUID_86f8df09-c972-332b-a279-636373ce4e0c',
  'UUID_144a6807-5844-32b2-bb34-8b2671b1afaa',
];

/// Matches a position within [tolerance] of ([x], [y], [z]).
Matcher closePoint(double x, double y, double z) => equals([close(x), close(y), close(z)]);

/// Matches numbers each within [tolerance] of [expected].
Matcher closeAll(List<double> expected) => equals(expected.map(close).toList());

List<double> point(DirectPosition position) => [position.x(), position.y(), position.z()];

Road road(CityModel cityModel) => items(cityModel.iterFeatures()).map(Road.tryFrom).nonNulls.first;

/// The objects of inline properties; fails on a reference-only property.
List<T> objects<P, T>(Iterator<P> properties, HRef? Function(P) href, T? Function(P) object) =>
    items(properties).map((property) {
      expect(href(property), isNull);
      return object(property)!;
    }).toList();

List<Section> sections(Road road) => objects(road.sections(), (p) => p.href(), (p) => p.object());

List<TrafficSpace> trafficSpaces(Iterator<TrafficSpaceProperty> spaces) =>
    objects(spaces, (p) => p.href(), (p) => p.object());

void expectEnvelope(CityModel cityModel, Matcher lower, Matcher upper) {
  final envelope = cityModel.boundedBy()!.envelope()!;
  expect(point(envelope.lowerCorner()), lower);
  expect(point(envelope.upperCorner()), upper);
}

/// The single boundary of a space, inline, as a feature.
AbstractFeatureKindRef onlyBoundary(Iterator<AbstractSpaceBoundaryProperty> boundaries) {
  final all = objects(boundaries, (p) => p.href(), (p) => p.object());
  expect(all, hasLength(1));
  return AbstractFeatureKindRef.fromSpaceBoundary(all.single);
}

/// The single curve member of an inline multi curve, as a line string: (point count, length).
(int, double) lineString(MultiCurve multiCurve) {
  final members = objects(multiCurve.curveMember(), (p) => p.href(), (p) => p.object());
  expect(members, hasLength(1));
  final curve = LineString.tryFrom(members.single)!;
  return (items(curve.points()).length, curve.length3d());
}

List<String> localIds(Iterator<TrafficSpaceReference> references) =>
    items(references).map((r) => Reference.fromTrafficSpaceReference(r).href()!.localId()!).toList();

void main() {
  group('road shape', () {
    final cityModel = read('asam-opendrive', roadShapeFile);

    Section section() {
      final all = sections(road(cityModel));
      expect(all, hasLength(1));
      return all.single;
    }

    List<TrafficSpace> spaces() => trafficSpaces(section().trafficSpaces());

    test('road shape city model', () {
      expect(cityModel.cityObjectsLen(), 1);
      final types = [
        FeatureType.cityModel,
        FeatureType.road,
        FeatureType.section,
        FeatureType.trafficSpace,
        FeatureType.trafficArea,
        FeatureType.trafficSpace,
        FeatureType.trafficArea,
        FeatureType.auxiliaryTrafficSpace,
        FeatureType.auxiliaryTrafficArea,
        FeatureType.auxiliaryTrafficSpace,
        FeatureType.auxiliaryTrafficArea,
      ];
      expect(items(cityModel.iterFeatures()).map((f) => f.featureType()), types);
      expect(items(cityModel.iterCityObjects()).map((o) => o.featureType()), types.skip(1));
      expectEnvelope(
        cityModel,
        closePoint(-50.21567184593757, -2.4442507170297514, 0.0),
        closePoint(-13.007511850967884, 29.053746110395082, 4.95),
      );
    });

    test('road shape road', () {
      final r = road(cityModel);
      expect(r.featureId().asStr(), 'UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f');
      expect(r.classifier(), isNull);
      expect(r.trafficDirection(), isNull);
      for (final empty in <Iterator<Object>>[
        r.functions(),
        r.usages(),
        r.intersections(),
        r.occupancies(),
        r.trafficSpaces(),
        r.auxiliaryTrafficSpaces(),
        r.markings(),
        r.holes(),
      ]) {
        expect(items(empty), isEmpty);
      }
      expect(section().featureId().asStr(), 'UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29');
    });

    test('road shape section', () {
      final s = section();
      expect(s.classifier(), isNull);
      expect(s.trafficDirection(), isNull);
      expect(s.lod0MultiCurve(), isNull);
      expect(s.lod1Solid(), isNull);
      expect(items(s.markings()), isEmpty);
      expect(items(s.holes()), isEmpty);
      expect(trafficSpaces(s.trafficSpaces()).map((t) => t.featureId().asStr()), [
        'UUID_ae81947d-a661-3678-a5ee-eed58b68694f',
        'UUID_6e4de408-1e54-3869-b7ce-1be3f2261421',
      ]);
      expect(
        objects(s.auxiliaryTrafficSpaces(), (p) => p.href(), (p) => p.object()).map((t) => t.featureId().asStr()),
        ['UUID_12298df9-4982-33a8-ab4a-9953410bbff7', 'UUID_f8211bb5-0ce8-36e1-9b84-73d30114f578'],
      );
    });

    test('road shape traffic spaces', () {
      final all = spaces();
      expect(all.map((s) => s.trafficDirection()), [TrafficDirectionValue.backwards, TrafficDirectionValue.forwards]);
      for (final space in all) {
        expect(space.granularity(), GranularityValue.lane);
        expect(space.classifier(), isNull);
        expect(items(space.functions()).map((f) => f.value()), ['1']);
        expect(items(space.usages()).map((u) => u.value()), ['2']);
        expect(items(space.occupancies()), isEmpty);
        expect(space.spaceType(), SpaceType.open);
        expect(space.relativeToTerrain(), isNull);
        expect(space.creationDate(), isNull);
        expect(items(space.predecessors()), isEmpty);
        expect(items(space.successors()), isEmpty);
        expect(TrafficArea.tryFrom(onlyBoundary(space.boundaries())), isNotNull);
      }
    });

    test('road shape generic attributes', () {
      final attributes = items(spaces()[0].genericAttributes()).map((a) {
        final integer = a.asInt();
        final number = a.asDouble();
        if (integer != null) return [a.name(), 'int', integer.value()];
        if (number != null) return [a.name(), 'double', number.value()];
        return [a.name(), 'string', a.asString()!.value()];
      });
      expect(attributes, [
        ['identifier_laneId', 'int', 1],
        ['identifier_laneSectionId', 'int', 0],
        ['identifier_roadId', 'string', '1'],
        ['opendrive_road_length', 'double', 40.0],
        ['opendrive_road_rule', 'string', 'RIGHT_HAND_TRAFFIC'],
        ['opendrive_laneSection_curvePositionStart', 'double', 0.0],
        ['opendrive_lane_type', 'string', 'DRIVING'],
        ['opendrive_lane_level', 'string', 'false'],
      ]);
    });

    test('road shape traffic space geometry', () {
      final all = spaces();
      expect(all.map((s) => s.lod2Solid()!.object()!.volume3d()), closeAll([720.0, 540.0]));
      for (final space in all) {
        final property = space.lod2MultiCurve()!;
        expect(property.href(), isNull);
        final multiCurve = property.object()!;
        expect(multiCurve.length3d(), close(40.0));
        final (points, length) = lineString(multiCurve);
        expect(points, 2);
        expect(length, close(40.0));
        expect(space.lod0MultiCurve(), isNull);
        expect(space.lod3MultiCurve(), isNull);
        expect(space.lod1Solid(), isNull);
        expect(space.lod3Solid(), isNull);
        expect(space.lod2MultiSurface(), isNull);
      }
    });

    test('road shape traffic areas', () {
      final areas = spaces().map((s) => TrafficArea.tryFrom(onlyBoundary(s.boundaries()))!).toList();
      expect(areas.map((a) => a.featureId().asStr()), [
        'UUID_8625bf6f-57cb-3ddf-8fd1-6674b756a2e2',
        'UUID_dc110e80-dadc-3c87-b864-2854cc0cb39a',
      ]);
      for (final area in areas) {
        expect(firstName(area.names()), 'Lane');
        expect(area.classifier(), isNull);
        expect(items(area.functions()).map((f) => f.value()), ['1']);
        expect(items(area.usages()).map((u) => u.value()), ['2']);
        expect(area.surfaceMaterial(), isNull);
        expect(area.lod0MultiCurve(), isNull);
        expect(area.lod0MultiSurface(), isNull);
        expect(area.lod1MultiSurface(), isNull);
        expect(area.lod3MultiSurface(), isNull);
        expect(area.relativeToTerrain(), isNull);
        expect(items(area.lod2MultiSurface()!.object()!.surfaceMember()), hasLength(1));
      }
      expect(
        areas.map((a) => a.lod2MultiSurface()!.object()!.area3d()),
        closeAll([160.79800993793438, 121.34249049694012]),
      );
    });

    test('road shape auxiliary traffic', () {
      final all = objects(section().auxiliaryTrafficSpaces(), (p) => p.href(), (p) => p.object());
      for (final space in all) {
        expect(space.granularity(), GranularityValue.lane);
        expect(space.classifier(), isNull);
        expect(items(space.functions()), isEmpty);
        expect(items(space.usages()), isEmpty);
        expect(space.spaceType(), SpaceType.open);
        expect(space.lod2Solid()!.object()!.volume3d(), close(100.0));
        expect(space.lod2MultiCurve()!.object()!.length3d(), close(40.0));
      }
      final areas = all.map((s) => AuxiliaryTrafficArea.tryFrom(onlyBoundary(s.boundaries()))!).toList();
      expect(areas.map((a) => a.featureId().asStr()), [
        'UUID_4890681a-e9fa-365e-a676-f89afb453f9b',
        'UUID_d3c71d48-5222-355e-8037-9677aee30d7e',
      ]);
      for (final area in areas) {
        expect(firstName(area.names()), 'Lane');
        expect(area.classifier(), isNull);
        expect(items(area.functions()), isEmpty);
        expect(items(area.usages()), isEmpty);
        expect(area.surfaceMaterial(), isNull);
        expect(area.lod2MultiSurface()!.object()!.area3d(), close(40.0));
      }
    });
  });

  group('junction', () {
    final cityModel = read('asam-opendrive', junctionFile);

    List<TrafficSpace> spaces() => items(cityModel.iterFeatures()).map(TrafficSpace.tryFrom).nonNulls.toList();

    test('junction city model', () {
      expect(cityModel.cityObjectsLen(), 1);
      expect(items(cityModel.iterFeatures()).map((f) => f.featureType()), [
        FeatureType.cityModel,
        FeatureType.road,
        FeatureType.section,
        FeatureType.trafficSpace,
        FeatureType.trafficArea,
        FeatureType.trafficSpace,
        FeatureType.trafficArea,
        FeatureType.marking,
        FeatureType.marking,
        FeatureType.marking,
        FeatureType.marking,
        FeatureType.section,
        FeatureType.trafficSpace,
        FeatureType.trafficArea,
        FeatureType.section,
        FeatureType.trafficSpace,
        FeatureType.trafficArea,
        FeatureType.intersection,
        FeatureType.trafficSpace,
        FeatureType.trafficArea,
        FeatureType.trafficSpace,
        FeatureType.trafficArea,
        FeatureType.trafficSpace,
        FeatureType.trafficArea,
      ]);
      expect(items(cityModel.iterCityObjects()), hasLength(23));
      expectEnvelope(
        cityModel,
        closePoint(-52.66282419815818, -37.4146115571896, 0.0),
        closePoint(34.10760429351533, 6.338805461729647, 0.0),
      );
    });

    test('junction road', () {
      final r = road(cityModel);
      expect(r.featureId().asStr(), 'UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f');
      final all = sections(r);
      expect(all.map((s) => s.featureId().asStr()), [
        'UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29',
        'UUID_ef20f165-2564-373a-a5f8-98fd15f1ae69',
        'UUID_4799566b-daf4-3135-aa9d-ec1b34a9167d',
      ]);
      expect(all.map((s) => items(s.trafficSpaces()).length), [2, 1, 1]);
      expect(all.map((s) => items(s.markings()).length), [4, 0, 0]);
      expect(all.map((s) => items(s.auxiliaryTrafficSpaces())), everyElement(isEmpty));
      final intersections = objects(r.intersections(), (p) => p.href(), (p) => p.object());
      expect(intersections, hasLength(1));
      final intersection = intersections.single;
      expect(intersection.featureId().asStr(), 'UUID_47b7678d-e8b1-36ca-90b6-5b86cc859571');
      expect(intersection.classifier(), isNull);
      expect(trafficSpaces(intersection.trafficSpaces()).map((t) => t.featureId().asStr()), spaceIds.sublist(4));
    });

    test('junction traffic spaces', () {
      final all = spaces();
      expect(all.map((s) => s.featureId().asStr()), spaceIds);
      expect(all.map((s) => s.trafficDirection()), [
        TrafficDirectionValue.backwards,
        ...List.filled(6, TrafficDirectionValue.forwards),
      ]);
      expect(all.map((s) => s.lod2Solid()), everyElement(isNull));
      final curves = all.map((s) => lineString(s.lod2MultiCurve()!.object()!)).toList();
      expect(curves.map((c) => c.$1), [9, 9, 5, 6, 7, 8, 7]);
      expect(
        curves.map((c) => c.$2),
        closeAll([
          36.74683751297985,
          36.74683751297985,
          20.0,
          21.746217945006258,
          26.761532846607814,
          30.210435770102656,
          30.0,
        ]),
      );
    });

    test('junction traffic areas', () {
      final surfaces = items(cityModel.iterFeatures())
          .map(TrafficArea.tryFrom)
          .nonNulls
          .map((a) => a.lod2MultiSurface()!.object()!)
          .toList();
      expect(surfaces.map((s) => items(s.surfaceMember()).length), [8, 8, 4, 5, 6, 7, 6]);
      expect(
        surfaces.map((s) => s.area3d()),
        closeAll([
          112.81279116484816,
          112.81279116484816,
          61.4,
          66.76088909116919,
          81.22157625123039,
          92.69041581703632,
          92.1,
        ]),
      );
    });

    test('junction traffic space links', () {
      final [s0, s1, s2, s3, s4, s5, s6] = spaceIds;
      expect(spaces().map((s) => [localIds(s.predecessors()), localIds(s.successors())]), [
        [<String>[], <String>[]],
        [
          <String>[],
          [s6],
        ],
        [
          [s4, s5],
          <String>[],
        ],
        [
          <String>[],
          [s4],
        ],
        [
          [s3],
          [s2],
        ],
        [
          ['UUID_d7d4aa5a-88c9-328d-9151-a6c043e57d7f'],
          [s0],
        ],
        [
          [s1],
          [s2],
        ],
      ]);
    });

    test('junction markings', () {
      final section = sections(road(cityModel)).first;
      final markings = objects(section.markings(), (p) => p.href(), (p) => p.object());
      for (final marking in markings) {
        expect(firstName(marking.names()), 'RoadMarking');
        expect(marking.classifier(), isNull);
        expect(marking.lod0MultiSurface(), isNull);
        expect(marking.lod3MultiSurface(), isNull);
        expect(items(marking.lod2MultiSurface()!.object()!.surfaceMember()), hasLength(1));
      }
      expect(
        markings.map((m) => m.lod2MultiSurface()!.object()!.area3d()),
        closeAll([0.48, 0.48, 0.48, 0.08962050155758661]),
      );
    });
  });
}
