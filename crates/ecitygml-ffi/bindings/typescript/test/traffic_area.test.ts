import assert from 'node:assert/strict';
import { test } from 'node:test';

import { TrafficArea } from '../lib/index.mjs';
import { features, read } from './helpers.ts';

function trafficAreas(name: string): TrafficArea[] {
    const cityModel = read(name);
    return [...features(cityModel.iterFeatures())].map((f) => TrafficArea.tryFrom(f)).filter((a) => a !== null);
}

test('traffic area getters', () => {
    const areas = trafficAreas('ASAM-UC_RoadShape.gml');
    assert.equal(areas.length, 2);

    const area = areas[0];
    assert.equal(area.class_(), null);
    assert.equal(area.functions().next().value?.value(), '1');
    assert.equal(area.usages().next().value?.code().value(), '2');
    assert.equal(area.surfaceMaterial(), null);
    assert.equal(area.lod0MultiCurve(), null);
    assert.ok(area.featureId().asStr().startsWith('UUID_8625bf6f'));
    assert.equal(area.names().next().value?.value(), 'Lane');
});

test('total traffic-area lod2 area', () => {
    const total = trafficAreas('ASAM-UC_RoadShape.gml')
        .map((area) => area.lod2MultiSurface()?.object()?.area3d() ?? 0)
        .reduce((sum, area) => sum + area, 0);
    assert.ok(Math.abs(total - 282.1405004348745) < 1e-6, `${total}`);
});
