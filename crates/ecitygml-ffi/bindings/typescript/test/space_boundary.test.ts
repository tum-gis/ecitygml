import assert from 'node:assert/strict';
import { test } from 'node:test';

import { AbstractFeatureKindRef, Building, FeatureType, TrafficArea, TrafficSpace, WallSurface } from '../lib/index.mjs';
import { features, read } from './helpers.ts';

/** Diplomat's iterators have `next()` but no `[Symbol.iterator]`. */
function* items<T>(iterator: { next(): IteratorResult<T> }) {
    for (let result = iterator.next(); !result.done; result = iterator.next()) {
        yield result.value;
    }
}

test('building boundaries', () => {
    const cityModel = read('FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml');
    const building = [...features(cityModel.iterFeatures())].map((f) => Building.tryFrom(f)).find((b) => b !== null);
    assert.ok(building);
    const boundaries = [...items(building.boundaries())].map((p) => p.object());
    assert.equal(boundaries.length, 7);
    assert.equal(boundaries.filter((b) => b?.featureType() == FeatureType.RoofSurface).length, 2);

    const walls = boundaries
        .map((b) => WallSurface.tryFrom(AbstractFeatureKindRef.fromSpaceBoundary(b!)))
        .filter((w) => w !== null);
    assert.equal(walls.length, 4);
    const wallArea = walls.map((w) => w.lod2MultiSurface()?.object()?.area3d() ?? 0).reduce((a, b) => a + b, 0);
    assert.ok(Math.abs(wallArea - 188.62887820601463) < 1e-6);
});

test('traffic space boundaries', () => {
    const cityModel = read('ASAM-UC_RoadShape.gml');
    const spaces = [...features(cityModel.iterFeatures())].map((f) => TrafficSpace.tryFrom(f)).filter((s) => s !== null);
    const areas = spaces.flatMap((s) => [...items(s.boundaries())])
        .map((p) => TrafficArea.tryFrom(AbstractFeatureKindRef.fromSpaceBoundary(p.object()!)));
    assert.equal(areas.length, 2);
    const total = areas.map((a) => a?.lod2MultiSurface()?.object()?.area3d() ?? 0).reduce((a, b) => a + b, 0);
    assert.ok(Math.abs(total - 282.1405004348745) < 1e-6);
});
