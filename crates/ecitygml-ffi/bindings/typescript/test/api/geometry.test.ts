// The cases of crates/ecitygml/tests/api/geometry.md.
import assert from 'node:assert/strict';
import { test } from 'node:test';

import {
    AbstractFeatureKindRef,
    Building,
    CityModel,
    CompositeSurface,
    DirectPosition,
    Envelope,
    ErrorKind,
    GeometryType,
    GroundSurface,
    LinearRing,
    Polygon,
    PolygonPatch,
    SolitaryVegetationObject,
    Storey,
    Surface,
    TinRelief,
    TrafficSpace,
    Triangle,
} from '../../lib/index.mjs';
import { features, read } from '../helpers.ts';
import { assertError } from './helpers.ts';

const FZK_LOD1 = 'fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml';
const FZK_LOD2 = 'fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml';
const TUM = 'tum-main-entrance/TUM-Main-Entrance.gml';
const ASAM_ROAD_SHAPE = 'asam-opendrive/ASAM-UC_RoadShape.gml';
const RAILWAY = 'railway-scene/Railway_Scene_LoD3__v3-thinned.gml';
const OGC_GARAGE = 'ogc-citygml-3.0-encodings/Building_and_garage_LOD2-EPSG25832.gml';
const OGC_UNITS = 'ogc-citygml-3.0-encodings/BuildingUnits_Storeys_xlink.gml';
const OGC_ROAD_OVER_BRIDGE = 'ogc-citygml-3.0-encodings/Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml';

type Point = [number, number, number];
type TryFrom<T> = { tryFrom(feature: AbstractFeatureKindRef): T | null };

function allOf<T>(cityModel: CityModel, type: TryFrom<T>): T[] {
    return [...features(cityModel.iterFeatures())].map((f) => type.tryFrom(f)).filter((x) => x != null);
}

function withId<T extends { featureId(): { asStr(): string } }>(items: T[], id: string): T {
    const found = items.find((x) => x.featureId().asStr() === id);
    assert.ok(found, id);
    return found;
}

/** All items of a Diplomat iterator (they have `next()` but no `[Symbol.iterator]`). */
function all<T>(iterator: { next(): IteratorResult<T> }): T[] {
    const items: T[] = [];
    for (let result = iterator.next(); !result.done; result = iterator.next()) {
        items.push(result.value);
    }
    return items;
}

function assertClose(actual: number, expected: number): void {
    assert.ok(Math.abs(actual - expected) <= 1e-6, `${actual} is not within 1e-6 of ${expected}`);
}

function assertPosition(actual: DirectPosition, expected: Point): void {
    [actual.x(), actual.y(), actual.z()].forEach((value, i) => assertClose(value, expected[i]));
}

function assertEnvelope(envelope: Envelope | null, lower: Point, upper: Point): void {
    assert.ok(envelope);
    assertPosition(envelope.lowerCorner(), lower);
    assertPosition(envelope.upperCorner(), upper);
}

test('compute envelope', () => {
    const solid = allOf(read(FZK_LOD1), Building)[0].lod1Solid()?.object();
    assert.ok(solid);
    const lower: Point = [457842.0, 5439083.0, 111.8];
    assertEnvelope(solid.computeEnvelope(), lower, [457854.0, 5439093.0, 118.31769]);
    const shell = solid.exterior();
    assert.ok(shell);
    assertEnvelope(shell.computeEnvelope(), lower, [457854.0, 5439093.0, 118.31769]);
    assertEnvelope(solid.triangulate().surface().computeEnvelope(), lower, [457854.0, 5439093.0, 118.31769]);
    const first = Polygon.tryFrom(shell.members().next().value!.object()!);
    assert.ok(first);
    const ground: Point = [457854.0, 5439093.0, 111.8];
    assertEnvelope(first.computeEnvelope(), lower, ground);
    assertEnvelope(first.exterior()!.computeEnvelope(), lower, ground);

    const space = allOf(read(ASAM_ROAD_SHAPE), TrafficSpace)[0];
    const multiCurve = space.lod2MultiCurve()?.object();
    assert.ok(multiCurve);
    const curveLower: Point = [-48.38872036507727, 2.3148451158285663, 0.25];
    const curveUpper: Point = [-16.661414812688488, 26.674198193965925, 0.25];
    assertEnvelope(multiCurve.computeEnvelope(), curveLower, curveUpper);
    const members = all(multiCurve.curveMember());
    assert.equal(members.length, 1);
    assertEnvelope(members[0].object()!.computeEnvelope(), curveLower, curveUpper);
    const spaceSolid = space.lod2Solid()?.object();
    assert.ok(spaceSolid);
    assertEnvelope(
        spaceSolid.computeEnvelope(),
        [-49.60668801898414, 0.7284798382091271, 0.05],
        [-15.44344715878162, 28.260563471585364, 4.95],
    );
    assert.equal(all(spaceSolid.points()).length, 24);

    const tree = withId(allOf(read(RAILWAY), SolitaryVegetationObject), 'GMLID_SO092422_3593_9527');
    const point = tree.lod3ImplicitRepresentation()?.object()?.referencePoint().object();
    assert.ok(point);
    const reference: Point = [-568.8000793496976, 457.60044759869743, 105.00139681350242];
    assertEnvelope(point.computeEnvelope(), reference, reference);

    const tin = allOf(read(OGC_GARAGE), TinRelief)[0].tin()?.object();
    assert.ok(tin);
    assertEnvelope(tin.computeEnvelope(), [458868.0, 5438343.0, 112.0], [458892.0, 5438362.0, 114.0]);
});

test('polygon interior rings', () => {
    const grounds = allOf(read(TUM), GroundSurface);
    assert.equal(grounds.length, 1);
    const multiSurface = grounds[0].lod2MultiSurface()?.object();
    assert.ok(multiSurface);
    const members = all(multiSurface.surfaceMember());
    assert.equal(members.length, 1);
    const polygon = Polygon.tryFrom(members[0].object()!);
    assert.ok(polygon);
    assert.equal(polygon.id()?.asStr(), 'DEBY_LOD2_4959457_2470b16f-99f0-43c3-9a27-bd4fc3822c91_2_poly');
    const exterior = LinearRing.tryFrom(polygon.exterior()!);
    assert.ok(exterior);
    assert.equal(all(exterior.points()).length, 11);
    assertClose(exterior.area3d(), 1371.825439453125);
    assertClose(exterior.length3d(), 150.78554397170106);
    const interiors = all(polygon.interior());
    assert.equal(interiors.length, 1);
    const interior = LinearRing.tryFrom(interiors[0]);
    assert.ok(interior);
    assert.equal(all(interior.points()).length, 4);
    assertClose(interior.area3d(), 142.26318359375);
    assertClose(interior.length3d(), 47.7096809282068);
    assertClose(polygon.area3d(), 1229.562255859375);
    assert.equal(all(polygon.points()).length, 15);
    assertEnvelope(polygon.computeEnvelope(), [691009.16, 5335994.57, 515.042], [691054.07, 5336047.41, 515.042]);
    const triangulation = multiSurface.triangulate();
    assert.ok(!triangulation.hasSkipped());
    assert.equal(all(triangulation.surface().triangles()).length, 15);
    assertClose(triangulation.surface().area3d(), 1229.5620994984272);
});

test('composite surface and patches', () => {
    const ground = withId(allOf(read(OGC_ROAD_OVER_BRIDGE), GroundSurface), 'id_groundsurface1');
    const multiSurface = ground.lod2MultiSurface()?.object();
    assert.ok(multiSurface);
    assert.equal(multiSurface.id()?.asStr(), 'id_groundsurface1-0');
    assertClose(multiSurface.area3d(), 77500.15996032);
    const members = all(multiSurface.surfaceMember());
    assert.equal(members.length, 1);
    const kind = members[0].object();
    assert.ok(kind);
    assert.equal(kind.geometryType(), GeometryType.CompositeSurface);
    assert.equal(Polygon.tryFrom(kind), null);
    const composite = CompositeSurface.tryFrom(kind);
    assert.ok(composite);
    assert.equal(composite.id()?.asStr(), 'id_groundsurface1-1');
    assertClose(composite.area3d(), 77500.15996032);
    assert.equal(all(composite.points()).length, 6);
    assertEnvelope(composite.computeEnvelope(), [0.0, 0.0, 0.0], [393.7008, 196.8504, 0.0]);
    const triangulation = composite.triangulate();
    assert.ok(!triangulation.hasSkipped());
    assert.equal(all(triangulation.surface().triangles()).length, 2);

    const ids = ['fme-gen-1a9ac79e-2880-47c7-b7c3-c9df5bc17447', 'fme-gen-545ee504-7440-4cb6-8713-fc8ba21ac163'];
    const surfaces = all(composite.surfaceMember()).map((member) => member.object()!);
    assert.equal(surfaces.length, ids.length);
    surfaces.forEach((surfaceKind, i) => {
        assert.equal(surfaceKind.geometryType(), GeometryType.Surface);
        const surface = Surface.tryFrom(surfaceKind);
        assert.ok(surface);
        assert.equal(surface.id()?.asStr(), ids[i]);
        assertClose(surface.area3d(), 38750.07998016);
        assert.equal(all(surface.triangulate().surface().triangles()).length, 1);
        const patches = all(surface.patches());
        assert.equal(patches.length, 1);
        assert.equal(Triangle.tryFrom(patches[0]), null);
        const polygonPatch = PolygonPatch.tryFrom(patches[0]);
        assert.ok(polygonPatch);
        assert.equal(all(polygonPatch.interior()).length, 0);
        assert.equal(all(LinearRing.tryFrom(polygonPatch.exterior()!)!.points()).length, 3);
        assertClose(patches[0].area3d(), 38750.07998016);
        assert.equal(all(patches[0].triangulate().surface().triangles()).length, 1);
    });
});

test('triangle patches', () => {
    const tin = allOf(read(OGC_GARAGE), TinRelief)[0].tin()?.object();
    assert.ok(tin);
    assert.equal(all(tin.surface().patches()).length, 12);
    const triangle = tin.triangles().next().value;
    assert.ok(triangle);
    assertPosition(triangle.a(), [458883.0, 5438362.0, 114.0]);
    assertPosition(triangle.b(), [458868.0, 5438362.0, 112.0]);
    assertPosition(triangle.c(), [458875.0, 5438355.0, 112.0]);
    assertClose(triangle.area(), 53.42518132865812);
    assert.equal(triangle.exterior().geometryType(), GeometryType.LinearRing);
});

test('unresolved surface reference', () => {
    const storey = withId(allOf(read(OGC_UNITS), Storey), 'storey1');
    const multiSurface = storey.lod2MultiSurface()?.object();
    assert.ok(multiSurface);
    assert.equal(all(multiSurface.surfaceMember()).length, 6);
    assertError(() => multiSurface.area3d(), ErrorKind.UnresolvedReference, '#Wall_1_PolyID82397_997_453711_16336011');
    assert.equal(all(multiSurface.points()).length, 12);
    assertEnvelope(multiSurface.computeEnvelope(), [457841.1, 5439082.1, 111.1], [457853.9, 5439092.9, 113.9]);
    const triangulation = multiSurface.triangulate();
    assert.ok(!triangulation.hasSkipped());
    assert.equal(all(triangulation.surface().triangles()).length, 6);
});

test('solid unresolved reference', () => {
    const solid = allOf(read(FZK_LOD2), Building)[0].lod2Solid()?.object();
    assert.ok(solid);
    assertError(() => solid.volume3d(), ErrorKind.UnresolvedReference, '#PolyID7350_878_759628_120742');
});

test('triangulate without members', () => {
    const solid = allOf(read(FZK_LOD2), Building)[0].lod2Solid()?.object();
    assert.ok(solid);
    assert.equal(all(solid.points()).length, 0);
    assert.equal(solid.computeEnvelope(), null);
    assertError(() => solid.triangulate(), ErrorKind.InvalidArgument, 'requires at least 1 element');
});
