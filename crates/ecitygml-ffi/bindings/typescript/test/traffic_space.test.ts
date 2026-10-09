import assert from 'node:assert/strict';
import { test } from 'node:test';

import { GeometryType, GranularityValue, LineString, Polygon, TrafficSpace } from '../lib/index.mjs';
import { features, fixtureBytes, read, readBytes } from './helpers.ts';

test('total traffic-space volume', () => {
    // The traffic-space analysis of the original Python example, with the generated API.
    const cityModel = read('ASAM-UC_RoadShape.gml');
    let totalVolume = 0.0;
    let spaces = 0;
    for (const feature of features(cityModel.iterFeatures())) {
        const space = TrafficSpace.tryFrom(feature);
        if (!space) {
            continue;
        }
        spaces++;
        assert.equal(space.granularity(), GranularityValue.Lane);
        const solid = space.lod2Solid()?.object();
        if (solid) {
            totalVolume += solid.volume3d();
        }
    }
    assert.equal(spaces, 2);
    assert.ok(Math.abs(totalVolume - 1260.0) < 1e-6, `${totalVolume}`);
});

test('lod2 multi curves', () => {
    const cityModel = read('ASAM-UC_RoadShape.gml');
    const spaces = [...features(cityModel.iterFeatures())].map((f) => TrafficSpace.tryFrom(f)).filter((s) => s !== null);
    assert.equal(spaces.length, 2);
    for (const space of spaces) {
        assert.equal(space.lod0MultiCurve(), null);
        assert.equal(space.lod3MultiCurve(), null);
        const multiCurve = space.lod2MultiCurve()?.object();
        assert.ok(multiCurve);
        assert.ok(Math.abs(multiCurve.length3d() - 40.0) < 1e-9);
        assert.ok(multiCurve.computeEnvelope());

        const members = multiCurve.curveMember();
        const member = members.next();
        assert.ok(!member.done);
        assert.ok(members.next().done);
        const curve = member.value.object();
        assert.ok(curve);
        assert.equal(curve.geometryType(), GeometryType.LineString);
        const lineString = LineString.tryFrom(curve);
        assert.ok(lineString);
        assert.ok(Math.abs(lineString.length3d() - 40.0) < 1e-9);
        const points = lineString.points();
        assert.ok(!points.next().done);
        assert.ok(!points.next().done);
        assert.ok(points.next().done);
    }
});

/** A 10 m x 4 m rectangle with a 1 m x 1 m hole (39 m^2), inserted after the first lod2Solid. */
const LOD2_MULTI_SURFACE = '</lod2Solid><lod2MultiSurface><gml:MultiSurface><gml:surfaceMember><gml:Polygon gml:id="PolyID_space"><gml:exterior><gml:LinearRing><gml:posList srsDimension="3">0 0 0 10 0 0 10 4 0 0 4 0 0 0 0</gml:posList></gml:LinearRing></gml:exterior><gml:interior><gml:LinearRing><gml:posList srsDimension="3">1 1 0 1 2 0 2 2 0 2 1 0 1 1 0</gml:posList></gml:LinearRing></gml:interior></gml:Polygon></gml:surfaceMember></gml:MultiSurface></lod2MultiSurface>';

function count(iterator: { next(): IteratorResult<unknown> }): number {
    let n = 0;
    while (!iterator.next().done) {
        n++;
    }
    return n;
}

test('lod2 multi surface', () => {
    const original = new TextDecoder().decode(fixtureBytes('ASAM-UC_RoadShape.gml'));
    const cityModel = readBytes(new TextEncoder().encode(original.replace('</lod2Solid>', LOD2_MULTI_SURFACE)));
    const spaces = [...features(cityModel.iterFeatures())].map((f) => TrafficSpace.tryFrom(f)).filter((s) => s !== null);
    assert.equal(spaces.length, 2);
    assert.equal(spaces[1].lod2MultiSurface(), null);

    const space = spaces[0];
    assert.equal(space.lod0MultiSurface(), null);
    assert.equal(space.lod3MultiSurface(), null);
    const multiSurface = space.lod2MultiSurface()?.object();
    assert.ok(multiSurface);
    assert.ok(Math.abs(multiSurface.area3d() - 39.0) < 1e-9);
    assert.ok(multiSurface.computeEnvelope());
    assert.equal(count(multiSurface.points()), 8);

    const members = multiSurface.surfaceMember();
    const member = members.next();
    assert.ok(!member.done);
    assert.ok(members.next().done);
    const surface = member.value.object();
    assert.ok(surface);
    assert.equal(surface.geometryType(), GeometryType.Polygon);
    assert.equal(surface.id()?.asStr(), 'PolyID_space');
    const polygon = Polygon.tryFrom(surface);
    assert.ok(polygon);
    assert.ok(Math.abs(polygon.area3d() - 39.0) < 1e-9);
    assert.equal(count(polygon.points()), 8);
});

test('lod0 point', () => {
    const original = new TextDecoder().decode(fixtureBytes('ASAM-UC_RoadShape.gml'));
    const cityModel = readBytes(new TextEncoder().encode(original.replace('</lod2Solid>', '</lod2Solid><lod0Point><gml:Point gml:id="PointID_space"><gml:pos srsDimension="3">1.5 -2.5 3.25</gml:pos></gml:Point></lod0Point>')));
    const spaces = [...features(cityModel.iterFeatures())].map((f) => TrafficSpace.tryFrom(f)).filter((s) => s !== null);
    assert.equal(spaces.length, 2);
    assert.equal(spaces[1].lod0Point(), null);

    const point = spaces[0].lod0Point()?.object();
    assert.ok(point);
    assert.equal(point.id()?.asStr(), 'PointID_space');
    const pos = point.pos();
    assert.deepEqual([pos.x(), pos.y(), pos.z()], [1.5, -2.5, 3.25]);
    assert.equal(point.computeEnvelope()?.lowerCorner().x(), 1.5);
});
