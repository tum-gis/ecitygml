// The cases of crates/ecitygml/tests/api/iteration.md. `native_iteration` is scoped out: the iterators have `next()`
// but no `[Symbol.iterator]`.
import assert from 'node:assert/strict';
import { test } from 'node:test';

import { FeatureType, WallSurface } from '../../lib/index.mjs';
import { features, read } from '../helpers.ts';
import { featureTypes } from './helpers.ts';

const FZK_LOD3 = 'fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml';
const ASAM_ROAD_SHAPE = 'asam-opendrive/ASAM-UC_RoadShape.gml';

/** Requests a garbage collection where Node offers one (`--expose-gc`). */
function collectGarbage(): void {
    (globalThis as { gc?: () => void }).gc?.();
}

test('iterator exhausted', () => {
    const iterator = read(FZK_LOD3).iterFeatures();
    let count = 0;
    while (!iterator.next().done) {
        count++;
    }
    assert.equal(count, 22);
    assert.ok(iterator.next().done);
});

test('iterator stopped early', () => {
    const cityModel = read(ASAM_ROAD_SHAPE);
    let iterator: ReturnType<typeof cityModel.iterFeatures> | null = cityModel.iterFeatures();
    assert.equal(iterator.next().value?.featureType(), FeatureType.CityModel);
    iterator = null;
    collectGarbage();
    assert.equal(featureTypes(cityModel).length, 11);
    assert.equal(cityModel.cityObjectsLen(), 1);
});

test('iterators independent', () => {
    const cityModel = read(FZK_LOD3);
    const [first, second] = [cityModel.iterFeatures(), cityModel.iterFeatures()];
    const [a, b]: unknown[][] = [[], []];
    for (;;) {
        const [x, y] = [first.next(), second.next()];
        assert.equal(x.done, y.done);
        if (x.done || y.done) {
            break;
        }
        a.push(x.value.featureType());
        b.push(y.value.featureType());
    }
    assert.equal(a.length, 22);
    assert.deepEqual(a, b);
    assert.deepEqual(a, featureTypes(cityModel));
});

test('iterator keeps model alive', () => {
    const iterator = read(FZK_LOD3).iterFeatures();
    collectGarbage();
    const walls = [...features(iterator)].filter((f) => WallSurface.tryFrom(f) != null);
    assert.equal(walls.length, 4);
});
