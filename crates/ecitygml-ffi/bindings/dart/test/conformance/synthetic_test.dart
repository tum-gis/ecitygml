// The cases of crates/ecitygml/tests/conformance/synthetic.md.
import 'dart:convert';
import 'dart:math';

import 'package:ecitygml/ecitygml.dart';
import 'package:test/test.dart';

import 'helpers.dart';

const dataset = 'synthetic';

List<FeatureType> featureTypes(CityModel cityModel) =>
    items(cityModel.iterFeatures()).map((f) => f.featureType()).toList();

List<T> allOf<T extends Object>(CityModel cityModel, T? Function(AbstractFeatureKindRef) tryFrom) =>
    items(cityModel.iterFeatures()).map(tryFrom).nonNulls.toList();

T only<T extends Object>(CityModel cityModel, T? Function(AbstractFeatureKindRef) tryFrom) =>
    allOf(cityModel, tryFrom).single;

List<int> ymd(Date? date) => [date!.year(), date.month(), date.day()];

(CityModel, String) roundTrip(CityModel cityModel) {
  final writer = GmlWriter(CitygmlFormat.gml)..finish(cityModel);
  final data = writer.data();
  return (GmlReader(data, CitygmlFormat.gml).finish(), utf8.decode(data));
}

ImplicitGeometry implicit(ImplicitGeometryProperty? property) {
  expect(property, isNotNull);
  expect(property!.href(), isNull);
  return property.object()!;
}

RoofSurface roof(AbstractSpaceBoundaryProperty property) {
  expect(property.href(), isNull);
  return RoofSurface.tryFrom(AbstractFeatureKindRef.fromSpaceBoundary(property.object()!))!;
}

GenericAttributeSet attributeSet(Building building) =>
    GenericAttributeSet.tryFrom(items(building.genericAttributes()).single)!;

void main() {
  group('bridge.gml', () {
    final cityModel = read(dataset, 'bridge.gml');
    BridgePart part(Bridge bridge) {
      final property = items(bridge.bridgeParts()).single;
      expect(property.href(), isNull);
      return property.object()!;
    }

    test('bridge city model', () {
      expect(cityModel.cityObjectsLen(), 1);
      expect(featureTypes(cityModel), [FeatureType.cityModel, FeatureType.bridge, FeatureType.bridgePart]);
      expect(items(cityModel.iterCityObjects()).map((o) => o.featureType()), [FeatureType.bridge, FeatureType.bridgePart]);
    });

    test('bridge attributes', () {
      final bridge = only(cityModel, Bridge.tryFrom);
      expect(bridge.featureId().asStr(), 'bridge_1');
      expect(items(bridge.names()).map((n) => n.value()), ['Synthetic bridge']);
      expect(bridge.classifier()?.value(), '1000');
      expect(items(bridge.functions()).map((f) => f.value()), ['1010', '1020']);
      expect(items(bridge.usages()).map((u) => u.value()), ['1000']);
      expect(ymd(bridge.dateOfConstruction()), [1990, 5, 1]);
      expect(items(bridge.heights()), isEmpty);
      final bridgePart = part(bridge);
      expect(bridgePart.featureId().asStr(), 'bridge_part_1');
      expect(bridgePart.classifier(), isNull);
      expect(items(bridgePart.functions()), isEmpty);
      expect(only(cityModel, BridgePart.tryFrom).featureId().asStr(), 'bridge_part_1');
    });

    test('bridge is movable', () {
      final bridge = only(cityModel, Bridge.tryFrom);
      expect(bridge.isMovable(), isTrue);
      expect(part(bridge).isMovable(), isFalse);
    });

    test('bridge code spaces', () {
      final bridge = only(cityModel, Bridge.tryFrom);
      expect(bridge.classifier()?.code().codeSpace(), 'https://example.org/bridge_class');
      expect(items(bridge.functions()).every((f) => f.code().codeSpace() == null), isTrue);
    });

    test('bridge round trip', () {
      final (written, _) = roundTrip(cityModel);
      expect(featureTypes(written), featureTypes(cityModel));
      final bridge = only(written, Bridge.tryFrom);
      expect(bridge.classifier()?.value(), '1000');
      expect(items(bridge.functions()).map((f) => f.value()), ['1010', '1020']);
      expect(ymd(bridge.dateOfConstruction()), [1990, 5, 1]);
      expect(part(bridge).featureId().asStr(), 'bridge_part_1');
    });
  });

  group('tunnel.gml', () {
    final cityModel = read(dataset, 'tunnel.gml');
    TunnelPart part(Tunnel tunnel) {
      final property = items(tunnel.tunnelParts()).single;
      expect(property.href(), isNull);
      return property.object()!;
    }

    test('tunnel city model', () {
      expect(cityModel.cityObjectsLen(), 1);
      expect(featureTypes(cityModel), [FeatureType.cityModel, FeatureType.tunnel, FeatureType.tunnelPart]);
      expect(items(cityModel.iterCityObjects()).map((o) => o.featureType()), [FeatureType.tunnel, FeatureType.tunnelPart]);
    });

    test('tunnel attributes', () {
      final tunnel = only(cityModel, Tunnel.tryFrom);
      expect(tunnel.featureId().asStr(), 'tunnel_1');
      expect(items(tunnel.names()).map((n) => n.value()), ['Synthetic tunnel']);
      expect(tunnel.classifier()?.value(), '1000');
      expect(items(tunnel.functions()).map((f) => f.value()), ['1010', '1020']);
      expect(items(tunnel.usages()).map((u) => u.value()), ['1000']);
      expect(ymd(tunnel.dateOfConstruction()), [1990, 5, 1]);
      expect(items(tunnel.heights()), isEmpty);
      final tunnelPart = part(tunnel);
      expect(tunnelPart.featureId().asStr(), 'tunnel_part_1');
      expect(tunnelPart.classifier(), isNull);
      expect(items(tunnelPart.functions()).map((f) => f.value()), ['1030']);
      expect(only(cityModel, TunnelPart.tryFrom).featureId().asStr(), 'tunnel_part_1');
    });

    test('tunnel code spaces', () {
      final tunnel = only(cityModel, Tunnel.tryFrom);
      expect(tunnel.classifier()?.code().codeSpace(), 'https://example.org/tunnel_class');
      expect(items(tunnel.functions()).every((f) => f.code().codeSpace() == null), isTrue);
    });

    test('tunnel round trip', () {
      final (written, _) = roundTrip(cityModel);
      expect(featureTypes(written), featureTypes(cityModel));
      final tunnel = only(written, Tunnel.tryFrom);
      expect(tunnel.classifier()?.value(), '1000');
      expect(items(tunnel.functions()).map((f) => f.value()), ['1010', '1020']);
      expect(items(part(tunnel).functions()).map((f) => f.value()), ['1030']);
    });
  });

  group('vegetation.gml', () {
    final cityModel = read(dataset, 'vegetation.gml');
    SolitaryVegetationObject tree(CityModel model, String id) =>
        allOf(model, SolitaryVegetationObject.tryFrom).singleWhere((t) => t.featureId().asStr() == id);

    test('vegetation city model', () {
      expect(cityModel.cityObjectsLen(), 3);
      expect(featureTypes(cityModel), [
        FeatureType.cityModel,
        FeatureType.solitaryVegetationObject,
        FeatureType.solitaryVegetationObject,
        FeatureType.plantCover,
      ]);
    });

    test('vegetation tree', () {
      final t = tree(cityModel, 'tree_1');
      expect(t.classifier()?.value(), '1000');
      expect(items(t.functions()).map((f) => f.value()), ['1010']);
      expect(items(t.usages()).map((u) => u.value()), ['1020']);
      expect(t.species()?.value(), 'Quercus robur');
      expect(t.height()!.value(), close(12.5));
      expect(t.height()!.uom(), 'm');
      expect(t.trunkDiameter()!.value(), close(0.4));
      expect(t.crownDiameter()!.value(), close(5.5));
      expect(t.rootBallDiameter()!.value(), close(1.2));
      expect(t.maxRootBallDepth()!.value(), close(0.8));
      expect(t.lod2ImplicitRepresentation(), isNull);
      expect(t.lod3ImplicitRepresentation(), isNull);
      expect(t.lod1Solid(), isNull);
      expect(t.lod1TerrainIntersectionCurve(), isNull);
    });

    test('vegetation implicit geometry', () {
      final geometry = implicit(tree(cityModel, 'tree_1').lod1ImplicitRepresentation());
      expect(geometry.objectId().asStr(), 'tree_prototype');
      expect(geometry.mimeType()?.value(), 'model/gltf+json');
      final pos = geometry.referencePoint().object()!.pos();
      expect([pos.x(), pos.y(), pos.z()], [457850.0, 5439090.0, 112.0]);
      final matrix = geometry.transformationMatrix();
      final rows = [for (var row = 0; row < 4; row++) [for (var column = 0; column < 4; column++) matrix.get(row, column)]];
      expect(rows, [
        [2.0, 0.0, 0.0, 10.0],
        [0.0, 2.0, 0.0, 20.0],
        [0.0, 0.0, 3.0, 30.0],
        [0.0, 0.0, 0.0, 1.0],
      ]);
      final relative = geometry.relativeGeometry()!.object()!;
      expect(relative.geometryType(), GeometryType.multiSurface);
      expect(items(MultiSurface.tryFrom(relative)!.surfaceMember()), hasLength(1));
      expect(Point.tryFrom(relative), isNull);
      final triangulation = relative.triangulate();
      expect(triangulation.hasSkipped(), isFalse);
      expect(items(triangulation.surface().triangles()), hasLength(1));
    });

    test('vegetation point relative geometry', () {
      final t = tree(cityModel, 'tree_2');
      expect(t.lod1ImplicitRepresentation(), isNull);
      final geometry = implicit(t.lod2ImplicitRepresentation());
      expect(geometry.objectId().asStr(), 'point_prototype');
      expect(geometry.mimeType(), isNull);
      final relative = geometry.relativeGeometry()!.object()!;
      expect(relative.geometryType(), GeometryType.point);
      final pos = Point.tryFrom(relative)!.pos();
      expect([pos.x(), pos.y(), pos.z()], [0.0, 0.0, 0.0]);
      expect(MultiSurface.tryFrom(relative), isNull);
    });

    test('vegetation library object', () {
      expect(implicit(tree(cityModel, 'tree_1').lod1ImplicitRepresentation()).libraryObject(), isNull);
      expect(implicit(tree(cityModel, 'tree_2').lod2ImplicitRepresentation()).libraryObject(),
          'https://example.org/trees/oak.gltf');
    });

    test('vegetation plant cover', () {
      final cover = only(cityModel, PlantCover.tryFrom);
      expect(cover.featureId().asStr(), 'cover_1');
      expect(cover.classifier()?.value(), '2000');
      expect(items(cover.functions()), isEmpty);
      expect(items(cover.usages()), isEmpty);
      expect(cover.averageHeight()!.value(), close(2.5));
      expect(cover.minHeight()!.value(), close(1.0));
      expect(cover.maxHeight()!.value(), close(4.0));
      expect(cover.lod1ImplicitRepresentation(), isNull);
      final feature = items(cityModel.iterFeatures()).singleWhere((f) => f.featureType() == FeatureType.plantCover);
      expect(SolitaryVegetationObject.tryFrom(feature), isNull);
    });

    test('vegetation code spaces', () {
      expect(tree(cityModel, 'tree_1').classifier()?.code().codeSpace(), 'https://example.org/tree_class');
      expect(only(cityModel, PlantCover.tryFrom).classifier()?.code().codeSpace(), isNull);
    });

    test('vegetation round trip', () {
      final (written, text) = roundTrip(cityModel);
      expect(featureTypes(written), featureTypes(cityModel));
      final t = tree(written, 'tree_1');
      expect(t.species()?.value(), 'Quercus robur');
      expect(t.height()!.value(), close(12.5));
      final geometry = implicit(t.lod1ImplicitRepresentation());
      expect(geometry.objectId().asStr(), 'tree_prototype');
      expect(geometry.mimeType()?.value(), 'model/gltf+json');
      expect(only(written, PlantCover.tryFrom).averageHeight()!.value(), close(2.5));
      expect(text, isNot(contains('objectId')));
    });
  });

  group('city-furniture.gml', () {
    final cityModel = read(dataset, 'city-furniture.gml');

    test('furniture attributes', () {
      final furniture = only(cityModel, CityFurniture.tryFrom);
      expect(furniture.featureId().asStr(), 'sign_1');
      expect(items(furniture.names()).map((n) => n.value()), ['Vorschriftzeichen']);
      expect(furniture.classifier()?.value(), '1000');
      expect(items(furniture.functions()).map((f) => f.value()), ['1080']);
      expect(items(furniture.usages()).map((u) => u.value()), ['1090']);
      final property = furniture.lod2MultiSurface()!;
      expect(property.href(), isNull);
      expect(items(property.object()!.surfaceMember()), hasLength(1));
      expect(furniture.lod1ImplicitRepresentation(), isNull);
      expect(furniture.lod2TerrainIntersectionCurve(), isNull);
    });

    test('furniture code spaces', () {
      expect(only(cityModel, CityFurniture.tryFrom).classifier()?.code().codeSpace(), 'https://example.org/furniture_class');
    });
  });

  group('building.gml', () {
    final cityModel = read(dataset, 'building.gml');
    Building building1(CityModel model) =>
        allOf(model, Building.tryFrom).singleWhere((b) => b.featureId().asStr() == 'building_1');

    test('building city model', () {
      expect(cityModel.cityObjectsLen(), 2);
      expect(featureTypes(cityModel), [
        FeatureType.cityModel,
        FeatureType.building,
        FeatureType.roofSurface,
        FeatureType.windowSurface,
        FeatureType.building,
      ]);
      expect(items(cityModel.iterCityObjects()), hasLength(4));
    });

    test('building relation', () {
      final property = items(building1(cityModel).relatedTo()).single;
      expect(property.href(), isNull);
      final relation = property.object()!;
      expect(relation.relationType().value(), 'shared');
      expect(relation.relationTo().href()?.toString(), '#building_2');
      final weight = items(relation.genericAttributes()).single;
      expect(weight.name(), 'weight');
      expect(weight.asInt()?.value(), 3);
    });

    test('building attribute set', () {
      final set = attributeSet(building1(cityModel));
      expect(set.name(), 'energy');
      final attributes = items(set.genericAttributes()).toList();
      expect(attributes, hasLength(2));
      expect(attributes[0].name(), 'demand');
      expect(attributes[0].asDouble()!.value(), close(12.5));
      expect(attributes[1].name(), 'label');
      expect(attributes[1].asString()?.value(), 'A+');
    });

    test('building construction', () {
      final building = building1(cityModel);
      expect(building.relativeToWater(), RelativeToWater.entirelyAboveWaterSurface);
      expect(ymd(building.dateOfConstruction()), [2020, 1, 1]);
      expect(ymd(building.dateOfDemolition()), [2050, 12, 31]);
      final occupancy = items(building.occupancies()).single;
      expect(occupancy.numberOfOccupants(), 4);
      expect(occupancy.interval()?.value(), 'daytime');
      expect(occupancy.occupantType()?.value(), 'residents');
    });

    test('building boundaries', () {
      final boundaries = items(building1(cityModel).boundaries()).toList();
      expect(boundaries, hasLength(2));
      final roofSurface = roof(boundaries[0]);
      expect(roofSurface.featureId().asStr(), 'roof_1');
      final filling = items(roofSurface.fillingSurfaces()).single;
      expect(filling.href(), isNull);
      final window = filling.object()!;
      expect(window.featureType(), FeatureType.windowSurface);
      expect(window.featureId().asStr(), 'roof_window_1');
      expect(boundaries[1].object(), isNull);
      expect(boundaries[1].href()?.toString(), '#missing_boundary');
    });

    test('building terrain intersection curve', () {
      final building = building1(cityModel);
      final property = building.lod2TerrainIntersectionCurve()!;
      expect(property.href(), isNull);
      final multiCurve = property.object()!;
      final member = items(multiCurve.curveMember()).single;
      expect(items(LineString.tryFrom(member.object()!)!.points()), hasLength(2));
      expect(multiCurve.length3d(), close(12.0));
      expect(building.lod1TerrainIntersectionCurve(), isNull);
      expect(building.lod3TerrainIntersectionCurve(), isNull);
    });

    test('building round trip', () {
      final (written, text) = roundTrip(cityModel);
      expect(featureTypes(written), featureTypes(cityModel));
      final building = building1(written);
      final relation = items(building.relatedTo()).single.object()!;
      expect(relation.relationTo().href()?.toString(), '#building_2');
      expect(attributeSet(building).name(), 'energy');
      expect(ymd(building.dateOfDemolition()), [2050, 12, 31]);
      final occupancy = items(building.occupancies()).single;
      expect(occupancy.numberOfOccupants(), 4);
      expect(occupancy.interval()?.value(), 'daytime');
      expect(occupancy.occupantType()?.value(), 'residents');
      final boundaries = items(building.boundaries()).toList();
      expect(items(roof(boundaries[0]).fillingSurfaces()).single.object()!.featureId().asStr(), 'roof_window_1');
      expect(boundaries[1].href()?.toString(), '#missing_boundary');
      expect(building.lod2TerrainIntersectionCurve()!.object()!.length3d(), close(12.0));
      expect(text, isNot(contains('TerrainIntersectionCurveProperty')));
    });
  });

  group('transportation.gml', () {
    final cityModel = read(dataset, 'transportation.gml');

    test('transportation section', () {
      final section = only(cityModel, Section.tryFrom);
      expect(section.featureId().asStr(), 'section_1');
      expect(section.trafficDirection(), TrafficDirectionValue.both);
      final occupancy = items(section.occupancies()).single;
      expect(occupancy.numberOfOccupants(), 120);
      expect(occupancy.interval()?.value(), 'peakHour');
      final property = items(section.trafficSpaces()).single;
      expect(property.href(), isNull);
      final space = property.object()!;
      expect(space.featureId().asStr(), 'space_1');
      expect(space.granularity(), GranularityValue.lane);
    });

    test('transportation point', () {
      final property = only(cityModel, TrafficSpace.tryFrom).lod0Point()!;
      expect(property.href(), isNull);
      final point = property.object()!;
      expect(point.id()?.asStr(), 'point_1');
      final pos = point.pos();
      expect([pos.x(), pos.y(), pos.z()], [1.5, -2.5, 3.25]);
      final envelope = point.computeEnvelope()!;
      for (final corner in [envelope.lowerCorner(), envelope.upperCorner()]) {
        expect([corner.x(), corner.y(), corner.z()], [1.5, -2.5, 3.25]);
      }
    });

    test('transportation curves', () {
      final multiCurve = only(cityModel, TrafficSpace.tryFrom).lod0MultiCurve()!.object()!;
      final members = items(multiCurve.curveMember()).toList();
      expect(members, hasLength(3));
      final line = members[0].object()!;
      expect(line.geometryType(), GeometryType.lineString);
      expect(AbstractRingKind.tryFrom(line), isNull);
      final lineString = LineString.tryFrom(line)!;
      expect(items(lineString.points()), hasLength(2));
      expect(lineString.length3d(), close(5.0));
      final ring = members[1].object()!;
      expect(ring.geometryType(), GeometryType.linearRing);
      final linearRing = LinearRing.tryFrom(AbstractRingKind.tryFrom(ring)!)!;
      expect(items(linearRing.points()), hasLength(3));
      expect(linearRing.length3d(), close(2 + sqrt2));
      expect(members[2].object(), isNull);
      expect(members[2].href()?.toString(), '#missing_curve');
      expect(
        () => multiCurve.length3d(),
        throwsA(isA<Error>()
            .having((e) => e.kind(), 'kind', ErrorKind.unresolvedReference)
            .having((e) => e.message(), 'message', contains('#missing_curve'))),
      );
    });
  });

  group('geometry.gml', () {
    final cityModel = read(dataset, 'geometry.gml');

    test('geometry skipped members', () {
      final building = allOf(cityModel, Building.tryFrom).singleWhere((b) => b.featureId().asStr() == 'geometry_1');
      final multiSurface = building.lod2MultiSurface()!.object()!;
      final members = items(multiSurface.surfaceMember()).map((m) => m.object()!).toList();
      expect(members, hasLength(3));
      for (final (kind, id) in [(members[0], 'square'), (members[1], 'collinear')]) {
        expect(kind.geometryType(), GeometryType.polygon);
        expect(kind.id()?.asStr(), id);
      }
      expect(members[1].area3d(), close(0.0));
      expect(members[2].geometryType(), GeometryType.triangulatedSurface);
      expect(Polygon.tryFrom(members[2]), isNull);
      final tin = TriangulatedSurface.tryFrom(members[2])!;
      expect(tin.id()?.asStr(), 'tin');
      expect(items(tin.triangles()), hasLength(2));
      expect(items(tin.surface().patches()), hasLength(2));
      expect(tin.area3d(), close(1.0));
      final triangulation = multiSurface.triangulate();
      expect(items(triangulation.surface().triangles()), hasLength(4));
      expect(triangulation.hasSkipped(), isTrue);
      final error = items(triangulation.skipped()).single;
      expect(error.kind(), ErrorKind.invalidArgument);
      expect(error.message(), contains('earcut produced no triangles'));
    });
  });
}
