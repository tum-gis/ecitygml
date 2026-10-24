// The cases of crates/ecitygml/tests/conformance/kit-bruecke.md.
import assert from 'node:assert/strict';
import { describe, test } from 'node:test';

import { Bridge, CityModel, CitygmlFormat, Envelope, FeatureType, GmlReader, GmlWriter } from '../../lib/index.mjs';
import { all, assertClose, read } from './helpers.ts';

type Point = [number, number, number];

const BRIDGE_ID = '_Modellbahnbruecke-LoD2-V03_BD.rx3tFkxPQkL5qDXML1W7';

function bridge(cityModel: CityModel): Bridge {
    const found = all(cityModel.iterFeatures())
        .map((f) => Bridge.tryFrom(f))
        .find((b) => b !== null);
    assert.ok(found);
    return found;
}

function featureTypes(cityModel: CityModel): FeatureType[] {
    return all(cityModel.iterFeatures()).map((f) => f.featureType());
}

function assertEnvelope(envelope: Envelope | undefined, lower: Point, upper: Point): void {
    assert.ok(envelope);
    for (const [position, expected] of [
        [envelope.lowerCorner(), lower],
        [envelope.upperCorner(), upper],
    ] as const) {
        [position.x(), position.y(), position.z()].forEach((value, i) => assertClose(value, expected[i]));
    }
}

describe('Modellbahnbruecke-LoD2-V03__v3.gml', () => {
    const cityModel = read('kit-bruecke', 'Modellbahnbruecke-LoD2-V03__v3.gml');

    test('bridge city model', () => {
        assert.equal(cityModel.cityObjectsLen(), 1);
        assertEnvelope(cityModel.boundedBy()?.envelope(), [457644.585, 5439126.455, 109.0], [457708.084, 5439157.169, 124.3]);
        assert.deepEqual(featureTypes(cityModel), [
            FeatureType.CityModel,
            FeatureType.Bridge,
            FeatureType.Appearance,
            ...Array(3).fill(FeatureType.ParameterizedTexture),
            ...Array(2).fill(FeatureType.BridgeInstallation),
            ...Array(11).fill(FeatureType.BridgeConstructiveElement),
        ]);
        assert.equal(all(cityModel.iterCityObjects()).length, 14);
    });

    test('bridge attributes', () => {
        const b = bridge(cityModel);
        assert.equal(b.featureId().asStr(), BRIDGE_ID);
        assert.equal(all(b.names()).length, 0);
        assert.equal(b.class_(), null);
        assert.equal(all(b.functions()).length, 0);
        assert.equal(all(b.usages()).length, 0);
        assert.equal(all(b.bridgeParts()).length, 0);
        assert.equal(all(b.boundaries()).length, 0);
        assert.equal(b.dateOfConstruction(), null);
        assert.equal(b.creationDate(), null);
        assert.equal(all(b.heights()).length, 0);
        assert.equal(all(b.occupancies()).length, 0);
        assert.equal(all(b.genericAttributes()).length, 0);
        assert.equal(all(b.externalReferences()).length, 0);
    });

    test('bridge geometry', () => {
        const b = bridge(cityModel);
        assertEnvelope(b.boundedBy()?.envelope(), [457645.136, 5439126.692, 115.3], [457707.533, 5439156.931, 116.2]);
        const property = b.lod2MultiSurface();
        assert.ok(property);
        assert.equal(property.href(), null);
        const multiSurface = property.object();
        assert.ok(multiSurface);
        assert.equal(all(multiSurface.surfaceMember()).length, 18);
        assertClose(multiSurface.area3d(), 795.4201811265907);
        const triangulation = multiSurface.triangulate();
        assert.equal(all(triangulation.surface().triangles()).length, 60);
        assert.ok(!triangulation.hasSkipped());
        assert.equal(b.lod1Solid(), null);
        assert.equal(b.lod2Solid(), null);
        assert.equal(b.lod3MultiSurface(), null);
    });

    test('bridge round trip', () => {
        const writer = new GmlWriter(CitygmlFormat.Gml);
        writer.finish(cityModel);
        const written = new GmlReader(writer.data(), CitygmlFormat.Gml).finish();
        assert.deepEqual(featureTypes(written), featureTypes(cityModel));
        assert.equal(bridge(written).featureId().asStr(), BRIDGE_ID);
    });
});
