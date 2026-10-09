import assert from 'node:assert/strict';
import { test } from 'node:test';

import { DoorSurface, FeatureType, GroundSurface, RoofSurface, WallSurface, WindowSurface } from '../lib/index.mjs';
import { features, read } from './helpers.ts';

test('wall, roof and ground surfaces', () => {
    const all = [...features(read('FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml').iterFeatures())];
    const area = (s: WallSurface | RoofSurface | GroundSurface) => s.lod2MultiSurface()?.object()?.area3d() ?? 0;
    const sum = (values: number[]) => values.reduce((a, b) => a + b, 0);

    const walls = all.map((f) => WallSurface.tryFrom(f)).filter((s) => s !== null);
    assert.deepEqual(
        walls.map((w) => w.names().next().value?.value()),
        ['Outer Wall 1 (West)', 'Outer Wall 2 (South)', 'Outer Wall 3 (East)', 'Outer Wall 4 (North)'],
    );
    assert.ok(Math.abs(sum(walls.map(area)) - 188.62887820601463) < 1e-6);

    const roofs = all.map((f) => RoofSurface.tryFrom(f)).filter((s) => s !== null);
    assert.equal(roofs.length, 2);
    assert.ok(Math.abs(sum(roofs.map(area)) - 138.56406460961398) < 1e-6);

    const grounds = all.map((f) => GroundSurface.tryFrom(f)).filter((s) => s !== null);
    assert.equal(grounds.length, 1);
    assert.equal(grounds[0].names().next().value?.value(), 'Base Surface');
    assert.ok(Math.abs(area(grounds[0]) - 120.0) < 1e-6);
});

test('door and window surfaces, also as filling surfaces', () => {
    const all = [...features(read('FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml').iterFeatures())];
    const doors = all.map((f) => DoorSurface.tryFrom(f)).filter((s) => s !== null);
    assert.deepEqual(doors.map((d) => d.names().next().value?.value()), ['Door West', 'Door South']);
    const doorArea = doors.map((d) => d.lod3MultiSurface()?.object()?.area3d() ?? 0).reduce((a, b) => a + b, 0);
    assert.ok(Math.abs(doorArea - 6.803850099444389) < 1e-6);
    assert.equal(all.map((f) => WindowSurface.tryFrom(f)).filter((s) => s !== null).length, 11);

    const west = all.map((f) => WallSurface.tryFrom(f)).find((w) => w?.names().next().value?.value() === 'Outer Wall 1 (West)');
    assert.ok(west);
    const fillings = [];
    const iterator = west.fillingSurfaces();
    for (let result = iterator.next(); !result.done; result = iterator.next()) {
        const filling = result.value.object();
        assert.ok(filling);
        fillings.push([filling.featureType() == FeatureType.DoorSurface ? 'door' : 'window', filling.names().next().value?.value()]);
    }
    assert.deepEqual(fillings, [
        ['window', 'Window Round'],
        ['window', 'Window North'],
        ['door', 'Door West'],
        ['window', 'Window South'],
    ]);
});
