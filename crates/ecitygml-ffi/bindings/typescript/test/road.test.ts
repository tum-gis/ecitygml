import assert from 'node:assert/strict';
import { test } from 'node:test';

import { Road } from '../lib/index.mjs';
import { features, read } from './helpers.ts';

/** Diplomat's iterators have `next()` but no `[Symbol.iterator]`. */
function* items<T>(iterator: { next(): IteratorResult<T> }) {
    for (let result = iterator.next(); !result.done; result = iterator.next()) {
        yield result.value;
    }
}

function firstRoad(name: string): Road {
    const cityModel = read(name);
    const road = [...features(cityModel.iterFeatures())].map((f) => Road.tryFrom(f)).find((r) => r !== null);
    assert.ok(road);
    return road;
}

test('road with a section of traffic and auxiliary traffic spaces', () => {
    const road = firstRoad('ASAM-UC_RoadShape.gml');
    assert.equal(road.class_(), null);
    assert.equal([...items(road.intersections())].length, 0);
    assert.equal([...items(road.trafficSpaces())].length, 0);

    const sections = [...items(road.sections())];
    assert.equal(sections.length, 1);
    const section = sections[0].object();
    assert.ok(section);
    assert.equal([...items(section.trafficSpaces())].length, 2);
    const volume = [...items(section.auxiliaryTrafficSpaces())]
        .map((p) => p.object()?.lod2Solid()?.object()?.volume3d() ?? 0)
        .reduce((sum, v) => sum + v, 0);
    assert.ok(Math.abs(volume - 200.0) < 1e-6, `${volume}`);
});

test('road with sections, an intersection and markings', () => {
    const road = firstRoad('ASAM-Ex_Bidirectional_Junction.gml');
    const sections = [...items(road.sections())].map((p) => p.object());
    assert.deepEqual(
        sections.map((s) => [...items(s!.trafficSpaces())].length),
        [2, 1, 1],
    );
    const markings = [...items(sections[0]!.markings())].map((p) => p.object());
    assert.equal(markings.length, 4);
    assert.ok(markings.every((m) => m?.class_() === null));

    const intersections = [...items(road.intersections())].map((p) => p.object());
    assert.equal(intersections.length, 1);
    assert.equal([...items(intersections[0]!.trafficSpaces())].length, 3);
});
