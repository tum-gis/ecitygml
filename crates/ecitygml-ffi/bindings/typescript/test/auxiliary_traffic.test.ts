import assert from 'node:assert/strict';
import { test } from 'node:test';

import { AuxiliaryTrafficArea, AuxiliaryTrafficSpace, GranularityValue } from '../lib/index.mjs';
import { features, read } from './helpers.ts';

test('auxiliary traffic spaces', () => {
    const cityModel = read('ASAM-UC_RoadShape.gml');
    const spaces = [...features(cityModel.iterFeatures())]
        .map((f) => AuxiliaryTrafficSpace.tryFrom(f))
        .filter((s) => s !== null);
    assert.equal(spaces.length, 2);
    for (const space of spaces) {
        assert.equal(space.class_(), null);
        assert.ok(space.functions().next().done);
        assert.equal(space.granularity(), GranularityValue.Lane);
        const volume = space.lod2Solid()?.object()?.volume3d() ?? 0;
        assert.ok(Math.abs(volume - 100.0) < 1e-6, `${volume}`);
        const length = space.lod2MultiCurve()?.object()?.length3d() ?? 0;
        assert.ok(Math.abs(length - 40.0) < 1e-9, `${length}`);
    }
});

test('auxiliary traffic areas', () => {
    const cityModel = read('ASAM-UC_RoadShape.gml');
    const areas = [...features(cityModel.iterFeatures())]
        .map((f) => AuxiliaryTrafficArea.tryFrom(f))
        .filter((a) => a !== null);
    assert.equal(areas.length, 2);
    for (const area of areas) {
        assert.equal(area.class_(), null);
        assert.ok(area.functions().next().done);
        assert.equal(area.surfaceMaterial(), null);
        assert.equal(area.names().next().value?.value(), 'Lane');
        const area3d = area.lod2MultiSurface()?.object()?.area3d() ?? 0;
        assert.ok(Math.abs(area3d - 40.0) < 1e-6, `${area3d}`);
    }
});
