import assert from 'node:assert/strict';
import { test } from 'node:test';

import { AbstractFeatureKindRef, Building, CitygmlFormat, DateTime, DirectPosition, FeatureType, LevelOfDetail, GmlReader, LinearRing, Polygon, Road, WallSurface } from '../lib/index.mjs';
import { features, fixtureBytes, read, readBytes } from './helpers.ts';

const FZK_LOD1 = 'FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml';

test('bounded_by envelope', () => {
    const envelope = read(FZK_LOD1).boundedBy()?.envelope();
    assert.ok(envelope);
    assert.equal(envelope.sizeX(), 12.0);
    assert.equal(envelope.sizeY(), 10.0);
    assert.ok(Math.abs(envelope.sizeZ() - 6.517669) < 1e-9);
    assert.equal(envelope.lowerCorner().x(), 457842.0);
});

test('envelope volume and contains', () => {
    const envelope = read(FZK_LOD1).boundedBy()?.envelope();
    assert.ok(envelope);
    assert.ok(Math.abs(envelope.volume() - 782.12028) < 1e-6);
    assert.ok(envelope.contains(envelope.lowerCorner()));
    assert.ok(envelope.contains(envelope.upperCorner()));
    assert.ok(!envelope.contains(new DirectPosition(457848.0, 5439088.0, 118.4)));
});

test('level of detail', () => {
    assert.equal(LevelOfDetail.Two.asIndex(), 2);
    assert.equal(LevelOfDetail.tryFrom(3), LevelOfDetail.Three);
    assert.throws(() => LevelOfDetail.tryFrom(4));
});

test('feature id and lifespan', () => {
    const original = new TextDecoder().decode(fixtureBytes(FZK_LOD1));
    const modified = original
        .replace('<CityModel ', '<CityModel gml:id="CM_1" ')
        .replace('</gml:boundedBy>', '</gml:boundedBy>\n  <creationDate>2017-01-23T00:00:00+01:00</creationDate>');
    const cityModel = readBytes(new TextEncoder().encode(modified));
    assert.equal(cityModel.featureId().asStr(), 'CM_1');

    const creationDate = cityModel.creationDate();
    assert.ok(creationDate);
    assert.equal(creationDate.toRfc3339(), '2017-01-23T00:00:00+01:00');
    assert.equal(creationDate.offsetSeconds(), 3600);
    assert.equal(cityModel.validTo(), null);
});

test('gml id and names', () => {
    const names = read(FZK_LOD1).names();
    const name = names.next();
    assert.ok(!name.done);
    assert.equal(name.value.value(), 'AC14-FZK-Haus');
    assert.equal(name.value.codeSpace(), null);
    assert.ok(names.next().done);

    const original = new TextDecoder().decode(fixtureBytes(FZK_LOD1));
    const modified = original.replace('<CityModel ', '<CityModel gml:id="CM_gml" ');
    assert.equal(readBytes(new TextEncoder().encode(modified)).id()?.asStr(), 'CM_gml');
});

test('iter_features yields typed features', () => {
    const types = [...features(read(FZK_LOD1).iterFeatures())].map((feature) => feature.featureType());
    assert.ok(types.some((type) => type == FeatureType.Building));
});

test('DateTime.fromParts', () => {
    const dateTime = DateTime.fromParts(2017, 1, 23, 13, 14, 15, 0, -7200);
    assert.equal(dateTime.hour(), 13);
    assert.equal(dateTime.toRfc3339(), '2017-01-23T13:14:15-02:00');
});

test('solid shell, polygons and linear rings', () => {
    const cityModel = read(FZK_LOD1);
    const building = [...features(cityModel.iterFeatures())].map((f) => Building.tryFrom(f)).find((b) => b !== null);
    const shell = building?.lod1Solid()?.object()?.exterior();
    assert.ok(shell);
    const members = shell.members();
    let polygons = 0;
    for (let member = members.next(); !member.done; member = members.next()) {
        const polygon = Polygon.tryFrom(member.value.object()!);
        assert.ok(polygon);
        assert.ok(polygon.interior().next().done);
        const ring = LinearRing.tryFrom(polygon.exterior()!);
        assert.ok(ring);
        let points = 0;
        const positions = ring.points();
        while (!positions.next().done) {
            points++;
        }
        assert.equal(points, 4);
        polygons++;
    }
    assert.equal(polygons, 6);
    assert.ok(Math.abs(shell.volume3d() - 782.1228) < 1e-6);
});

test('solid triangulation', () => {
    const cityModel = read(FZK_LOD1);
    const building = [...features(cityModel.iterFeatures())].map((f) => Building.tryFrom(f)).find((b) => b !== null);
    const triangulation = building?.lod1Solid()?.object()?.triangulate();
    assert.ok(triangulation);
    // Diplomat's JS backend returns `bool` as the raw WebAssembly integer (0/1), not `false`/`true`.
    assert.ok(!triangulation.hasSkipped());
    const triangles = triangulation.surface().triangles();
    let count = 0;
    while (!triangles.next().done) {
        count++;
    }
    assert.equal(count, 12);
    assert.ok(Math.abs(triangulation.surface().area3d() - 526.77836) < 1e-3);
});

test('iter_city_objects', () => {
    const iterator = read('FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml').iterCityObjects();
    const types = [];
    for (let result = iterator.next(); !result.done; result = iterator.next()) {
        types.push(result.value.featureType());
    }
    assert.ok(!types.includes(FeatureType.CityModel));
    assert.equal(types.filter((t) => t === FeatureType.Building).length, 1);
    assert.equal(types.filter((t) => t === FeatureType.WallSurface).length, 4);

    const first = read('ASAM-Ex_Bidirectional_Junction.gml').iterCityObjects().next().value;
    assert.ok(first);
    const road = Road.tryFrom(AbstractFeatureKindRef.fromCityObject(first));
    assert.equal(road?.featureId().asStr(), 'UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f');
});

test('recompute_child_bounding_shapes', () => {
    const data = fixtureBytes('FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml');
    const reader = new GmlReader(data as unknown as number[], CitygmlFormat.Gml);
    reader.withRebuildObjectBounds(false);
    const cityModel = reader.finish();
    const wallBounded = () =>
        [...features(cityModel.iterFeatures())].map((f) => WallSurface.tryFrom(f)).find((w) => w !== null)?.boundedBy() !==
        null;
    assert.ok(!wallBounded());
    cityModel.recomputeChildBoundingShapes();
    assert.ok(wallBounded());
});

test('apply_translation and apply_scale', () => {
    const cityModel = read(FZK_LOD1);
    const lowerCorner = () => {
        const lower = cityModel.boundedBy()!.envelope()!.lowerCorner();
        return [lower.x(), lower.y(), lower.z()];
    };
    const [x, y, z] = lowerCorner();
    cityModel.applyTranslation({ x: -100.0, y: 200.0, z: 10.0 });
    const moved = lowerCorner();
    [x - 100.0, y + 200.0, z + 10.0].forEach((expected, axis) => assert.ok(Math.abs(moved[axis] - expected) < 1e-6));

    cityModel.applyScale({ x: 2.0, y: 3.0, z: 0.5 });
    const envelope = cityModel.boundedBy()!.envelope()!;
    assert.ok(Math.abs(envelope.sizeX() - 24.0) < 1e-6);
    assert.ok(Math.abs(envelope.sizeY() - 30.0) < 1e-6);
    assert.ok(Math.abs(envelope.sizeZ() - 6.517669 / 2) < 1e-6);
});
