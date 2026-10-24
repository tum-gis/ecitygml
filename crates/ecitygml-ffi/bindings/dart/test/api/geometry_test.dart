// The cases of crates/ecitygml/tests/api/geometry.md.
import 'package:ecitygml/ecitygml.dart';
import 'package:test/test.dart';

import '../helpers.dart';
import 'helpers.dart';

const tum = 'tum-main-entrance/TUM-Main-Entrance.gml';
const asamRoadShape = 'asam-opendrive/ASAM-UC_RoadShape.gml';
const railway = 'railway-scene/Railway_Scene_LoD3__v3-thinned.gml';
const ogcGarage = 'ogc-citygml-3.0-encodings/Building_and_garage_LOD2-EPSG25832.gml';
const ogcUnits = 'ogc-citygml-3.0-encodings/BuildingUnits_Storeys_xlink.gml';
const ogcRoadOverBridge = 'ogc-citygml-3.0-encodings/Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml';

typedef Point = (double, double, double);

List<T> allOf<T extends Object>(CityModel cityModel, T? Function(AbstractFeatureKindRef) tryFrom) =>
    items(cityModel.iterFeatures()).map(tryFrom).nonNulls.toList();

void expectPosition(DirectPosition actual, Point expected) {
  expect(actual.x(), closeTo(expected.$1, 1e-6));
  expect(actual.y(), closeTo(expected.$2, 1e-6));
  expect(actual.z(), closeTo(expected.$3, 1e-6));
}

void expectEnvelope(Envelope? envelope, Point lower, Point upper) {
  expect(envelope, isNotNull);
  expectPosition(envelope!.lowerCorner(), lower);
  expectPosition(envelope.upperCorner(), upper);
}

void main() {
  test('compute envelope', () {
    final solid = allOf(read(fzkLod1), Building.tryFrom)[0].lod1Solid()!.object()!;
    const lower = (457842.0, 5439083.0, 111.8);
    const upper = (457854.0, 5439093.0, 118.31769);
    expectEnvelope(solid.computeEnvelope(), lower, upper);
    final shell = solid.exterior()!;
    expectEnvelope(shell.computeEnvelope(), lower, upper);
    expectEnvelope(solid.triangulate().surface().computeEnvelope(), lower, upper);
    final first = Polygon.tryFrom(items(shell.members()).first.object()!)!;
    const ground = (457854.0, 5439093.0, 111.8);
    expectEnvelope(first.computeEnvelope(), lower, ground);
    expectEnvelope(first.exterior()!.computeEnvelope(), lower, ground);

    final space = allOf(read(asamRoadShape), TrafficSpace.tryFrom)[0];
    final multiCurve = space.lod2MultiCurve()!.object()!;
    const curveLower = (-48.38872036507727, 2.3148451158285663, 0.25);
    const curveUpper = (-16.661414812688488, 26.674198193965925, 0.25);
    expectEnvelope(multiCurve.computeEnvelope(), curveLower, curveUpper);
    final members = items(multiCurve.curveMember()).toList();
    expect(members, hasLength(1));
    expectEnvelope(members.single.object()!.computeEnvelope(), curveLower, curveUpper);
    final spaceSolid = space.lod2Solid()!.object()!;
    expectEnvelope(spaceSolid.computeEnvelope(), (-49.60668801898414, 0.7284798382091271, 0.05),
        (-15.44344715878162, 28.260563471585364, 4.95));
    expect(items(spaceSolid.points()), hasLength(24));

    final tree = allOf(read(railway), SolitaryVegetationObject.tryFrom)
        .firstWhere((tree) => tree.featureId().asStr() == 'GMLID_SO092422_3593_9527');
    final point = tree.lod3ImplicitRepresentation()!.object()!.referencePoint().object()!;
    const reference = (-568.8000793496976, 457.60044759869743, 105.00139681350242);
    expectEnvelope(point.computeEnvelope(), reference, reference);

    final tin = allOf(read(ogcGarage), TinRelief.tryFrom)[0].tin()!.object()!;
    expectEnvelope(tin.computeEnvelope(), (458868.0, 5438343.0, 112.0), (458892.0, 5438362.0, 114.0));
  });

  test('polygon interior rings', () {
    final grounds = allOf(read(tum), GroundSurface.tryFrom);
    expect(grounds, hasLength(1));
    final multiSurface = grounds.single.lod2MultiSurface()!.object()!;
    final members = items(multiSurface.surfaceMember()).toList();
    expect(members, hasLength(1));
    final polygon = Polygon.tryFrom(members.single.object()!)!;
    expect(polygon.id()?.asStr(), 'DEBY_LOD2_4959457_2470b16f-99f0-43c3-9a27-bd4fc3822c91_2_poly');
    final exterior = LinearRing.tryFrom(polygon.exterior()!)!;
    expect(items(exterior.points()), hasLength(11));
    expect(exterior.area3d(), closeTo(1371.825439453125, 1e-6));
    expect(exterior.length3d(), closeTo(150.78554397170106, 1e-6));
    final interiors = items(polygon.interior()).toList();
    expect(interiors, hasLength(1));
    final interior = LinearRing.tryFrom(interiors.single)!;
    expect(items(interior.points()), hasLength(4));
    expect(interior.area3d(), closeTo(142.26318359375, 1e-6));
    expect(interior.length3d(), closeTo(47.7096809282068, 1e-6));
    expect(polygon.area3d(), closeTo(1229.562255859375, 1e-6));
    expect(items(polygon.points()), hasLength(15));
    expectEnvelope(polygon.computeEnvelope(), (691009.16, 5335994.57, 515.042), (691054.07, 5336047.41, 515.042));
    final triangulation = multiSurface.triangulate();
    expect(triangulation.hasSkipped(), isFalse);
    expect(items(triangulation.surface().triangles()), hasLength(15));
    expect(triangulation.surface().area3d(), closeTo(1229.5620994984272, 1e-6));
  });

  test('composite surface and patches', () {
    final ground = allOf(read(ogcRoadOverBridge), GroundSurface.tryFrom)
        .firstWhere((ground) => ground.featureId().asStr() == 'id_groundsurface1');
    final multiSurface = ground.lod2MultiSurface()!.object()!;
    expect(multiSurface.id()?.asStr(), 'id_groundsurface1-0');
    expect(multiSurface.area3d(), closeTo(77500.15996032, 1e-6));
    final members = items(multiSurface.surfaceMember()).toList();
    expect(members, hasLength(1));
    final kind = members.single.object()!;
    expect(kind.geometryType(), GeometryType.compositeSurface);
    expect(Polygon.tryFrom(kind), isNull);
    final composite = CompositeSurface.tryFrom(kind)!;
    expect(composite.id()?.asStr(), 'id_groundsurface1-1');
    expect(composite.area3d(), closeTo(77500.15996032, 1e-6));
    expect(items(composite.points()), hasLength(6));
    expectEnvelope(composite.computeEnvelope(), (0.0, 0.0, 0.0), (393.7008, 196.8504, 0.0));
    final triangulation = composite.triangulate();
    expect(triangulation.hasSkipped(), isFalse);
    expect(items(triangulation.surface().triangles()), hasLength(2));

    const ids = ['fme-gen-1a9ac79e-2880-47c7-b7c3-c9df5bc17447', 'fme-gen-545ee504-7440-4cb6-8713-fc8ba21ac163'];
    final surfaces = items(composite.surfaceMember()).map((member) => member.object()!).toList();
    expect(surfaces, hasLength(ids.length));
    for (final (i, surfaceKind) in surfaces.indexed) {
      expect(surfaceKind.geometryType(), GeometryType.surface);
      final surface = Surface.tryFrom(surfaceKind)!;
      expect(surface.id()?.asStr(), ids[i]);
      expect(surface.area3d(), closeTo(38750.07998016, 1e-6));
      expect(items(surface.triangulate().surface().triangles()), hasLength(1));
      final patches = items(surface.patches()).toList();
      expect(patches, hasLength(1));
      expect(Triangle.tryFrom(patches.single), isNull);
      final polygonPatch = PolygonPatch.tryFrom(patches.single)!;
      expect(items(polygonPatch.interior()), isEmpty);
      expect(items(LinearRing.tryFrom(polygonPatch.exterior()!)!.points()), hasLength(3));
      expect(patches.single.area3d(), closeTo(38750.07998016, 1e-6));
      expect(items(patches.single.triangulate().surface().triangles()), hasLength(1));
    }
  });

  test('triangle patches', () {
    final tin = allOf(read(ogcGarage), TinRelief.tryFrom)[0].tin()!.object()!;
    expect(items(tin.surface().patches()), hasLength(12));
    final triangle = items(tin.triangles()).first;
    expectPosition(triangle.a(), (458883.0, 5438362.0, 114.0));
    expectPosition(triangle.b(), (458868.0, 5438362.0, 112.0));
    expectPosition(triangle.c(), (458875.0, 5438355.0, 112.0));
    expect(triangle.area(), closeTo(53.42518132865812, 1e-6));
    expect(triangle.exterior().geometryType(), GeometryType.linearRing);
  });

  test('unresolved surface reference', () {
    final storey = allOf(read(ogcUnits), Storey.tryFrom).firstWhere((storey) => storey.featureId().asStr() == 'storey1');
    final multiSurface = storey.lod2MultiSurface()!.object()!;
    expect(items(multiSurface.surfaceMember()), hasLength(6));
    expect(() => multiSurface.area3d(),
        throwsError(ErrorKind.unresolvedReference, '#Wall_1_PolyID82397_997_453711_16336011'));
    expect(items(multiSurface.points()), hasLength(12));
    expectEnvelope(multiSurface.computeEnvelope(), (457841.1, 5439082.1, 111.1), (457853.9, 5439092.9, 113.9));
    final triangulation = multiSurface.triangulate();
    expect(triangulation.hasSkipped(), isFalse);
    expect(items(triangulation.surface().triangles()), hasLength(6));
  });

  test('solid unresolved reference', () {
    final solid = allOf(read(fzkLod2), Building.tryFrom)[0].lod2Solid()!.object()!;
    expect(() => solid.volume3d(), throwsError(ErrorKind.unresolvedReference, '#PolyID7350_878_759628_120742'));
  });

  test('triangulate without members', () {
    final solid = allOf(read(fzkLod2), Building.tryFrom)[0].lod2Solid()!.object()!;
    expect(items(solid.points()), isEmpty);
    expect(solid.computeEnvelope(), isNull);
    expect(() => solid.triangulate(), throwsError(ErrorKind.invalidArgument, 'requires at least 1 element'));
  });
}
