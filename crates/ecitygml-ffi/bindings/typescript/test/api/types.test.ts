// The cases of crates/ecitygml/tests/api/types.md.
import assert from 'node:assert/strict';
import { test } from 'node:test';

import {
    AbstractFeatureKindRef,
    AuxiliaryTrafficArea,
    AuxiliaryTrafficSpace,
    Building,
    CityModel,
    Date,
    DateTime,
    DirectPosition,
    DoorSurface,
    ErrorKind,
    FeatureType,
    GroundSurface,
    LevelOfDetail,
    Road,
    RoofSurface,
    Section,
    SolitaryVegetationObject,
    TrafficArea,
    TrafficSpace,
    WallSurface,
    WindowSurface,
} from '../../lib/index.mjs';
import { features, read } from '../helpers.ts';
import { assertError } from './helpers.ts';

const FZK_LOD1 = 'fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml';
const FZK_LOD2 = 'fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml';
const FZK_LOD3 = 'fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml';
const TUM = 'tum-main-entrance/TUM-Main-Entrance.gml';
const ASAM_ROAD_SHAPE = 'asam-opendrive/ASAM-UC_RoadShape.gml';
const ASAM_JUNCTION = 'asam-opendrive/ASAM-Ex_Bidirectional_Junction.gml';
const RAILWAY = 'railway-scene/Railway_Scene_LoD3__v3-thinned.gml';
const SIG3D = 'http://www.sig3d.org/codelists/citygml/2.0/building/2.0/_AbstractBuilding_';

type TryFrom<T> = { tryFrom(feature: AbstractFeatureKindRef): T | null };

/** The first feature that `type.tryFrom` accepts. */
function first<T>(cityModel: CityModel, type: TryFrom<T>): T {
    const found = [...features(cityModel.iterFeatures())].map((f) => type.tryFrom(f)).find((x) => x != null);
    assert.ok(found);
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

test('direct position new', () => {
    const position = new DirectPosition(1.0, 2.0, 3.0);
    assert.deepEqual([position.x(), position.y(), position.z()], [1.0, 2.0, 3.0]);
    assertError(() => new DirectPosition(NaN, 0.0, 0.0), ErrorKind.InvalidArgument, 'non-finite');
});

test('level of detail index', () => {
    const levels = [LevelOfDetail.Zero, LevelOfDetail.One, LevelOfDetail.Two, LevelOfDetail.Three];
    levels.forEach((lod, index) => {
        assert.equal(lod.asIndex(), index);
        assert.equal(LevelOfDetail.tryFrom(index), lod);
    });
    assertError(() => LevelOfDetail.tryFrom(4), ErrorKind.InvalidArgument, '4');
});

test('feature type name', () => {
    assert.equal(FeatureType.Building.toString(), 'Building');
    assert.equal(FeatureType.TinRelief.toString(), 'TinRelief');
});

test('date from parts', () => {
    const date = Date.fromParts(2020, 1, 2, 3600);
    assert.deepEqual([date.year(), date.month(), date.day(), date.offsetSeconds()], [2020, 1, 2, 3600]);
    const start = date.startOfDay();
    assert.deepEqual([start.hour(), start.minute(), start.second()], [0, 0, 0]);
    assert.equal(start.toRfc3339(), '2020-01-02T00:00:00+01:00');

    assertError(() => Date.fromParts(2021, 2, 30, 0), ErrorKind.InvalidArgument, 'do not form a valid date');
});

test('date time from parts', () => {
    const dateTime = DateTime.fromParts(2017, 1, 23, 13, 14, 15, 500_000_000, -7200);
    assert.deepEqual([dateTime.year(), dateTime.month(), dateTime.day()], [2017, 1, 23]);
    assert.deepEqual([dateTime.hour(), dateTime.minute(), dateTime.second()], [13, 14, 15]);
    assert.equal(dateTime.nanosecond(), 500_000_000);
    assert.equal(dateTime.offsetSeconds(), -7200);
    assert.equal(dateTime.timestamp(), 1485184455n);
    assert.equal(dateTime.timestampSubsecNanos(), 500_000_000);
    assert.equal(dateTime.toRfc3339(), '2017-01-23T13:14:15.500-02:00');

    assertError(
        () => DateTime.fromParts(2020, 1, 1, 0, 0, 0, 0, 30),
        ErrorKind.InvalidArgument,
        'timezone offset of 30 s is invalid',
    );
});

test('date time read', () => {
    const created = first(read(FZK_LOD2), Building).creationDate();
    assert.equal(created?.toRfc3339(), '2017-01-23T00:00:00+01:00');
});

/** `type.tryFrom` accepts exactly the features of its feature type. */
function assertTryFromMatches(cityModel: CityModel, types: [TryFrom<unknown>, FeatureType][]): void {
    for (const feature of features(cityModel.iterFeatures())) {
        for (const [type, featureType] of types) {
            const accepted = type.tryFrom(feature) != null;
            assert.equal(accepted, feature.featureType() === featureType, `${featureType} as ${feature.featureType()}`);
        }
    }
}

test('try from matches feature type', () => {
    assertTryFromMatches(read(FZK_LOD3), [
        [Building, FeatureType.Building],
        [WallSurface, FeatureType.WallSurface],
        [RoofSurface, FeatureType.RoofSurface],
        [GroundSurface, FeatureType.GroundSurface],
        [DoorSurface, FeatureType.DoorSurface],
        [WindowSurface, FeatureType.WindowSurface],
    ]);
    assertTryFromMatches(read(ASAM_ROAD_SHAPE), [
        [Road, FeatureType.Road],
        [Section, FeatureType.Section],
        [TrafficSpace, FeatureType.TrafficSpace],
        [TrafficArea, FeatureType.TrafficArea],
        [AuxiliaryTrafficSpace, FeatureType.AuxiliaryTrafficSpace],
        [AuxiliaryTrafficArea, FeatureType.AuxiliaryTrafficArea],
    ]);
});

test('feature from city object', () => {
    const cityObject = read(ASAM_JUNCTION).iterCityObjects().next().value;
    assert.ok(cityObject);
    assert.equal(cityObject.featureType(), FeatureType.Road);
    const feature = AbstractFeatureKindRef.fromCityObject(cityObject);
    assert.equal(feature.featureType(), FeatureType.Road);
    assert.equal(Road.tryFrom(feature)?.featureId().asStr(), 'UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f');
    assert.equal(Building.tryFrom(feature), null);
});

test('matrix index out of range', () => {
    const tree = [...features(read(RAILWAY).iterFeatures())]
        .map((f) => SolitaryVegetationObject.tryFrom(f))
        .find((t) => t?.featureId().asStr() === 'GMLID_SO092422_3593_9527');
    const matrix = tree?.lod3ImplicitRepresentation()?.object()?.transformationMatrix();
    assert.ok(matrix);
    assert.equal(matrix.get(3, 3), 1.0);
    for (const [row, column] of [[4, 0], [0, 4]]) {
        assertError(() => matrix.get(row, column), ErrorKind.InvalidArgument, 'out of range');
    }
});

test('gml id', () => {
    const cityModel = read(FZK_LOD1);
    const generated = cityModel.featureId().asStr();
    assert.ok(generated.startsWith('ecitygml-gen-feature-'), generated);
    assert.equal(cityModel.id()?.asStr(), generated);

    const wall = first(read(FZK_LOD2), WallSurface);
    assert.equal(wall.id()?.asStr(), 'GML_5856d7ad-5e34-498a-817b-9544bfbb1475');
    assert.equal(wall.featureId().asStr(), 'GML_5856d7ad-5e34-498a-817b-9544bfbb1475');

    assert.equal(first(read(TUM), Building).id()?.asStr(), 'DEBY_LOD2_4959457');
});

test('code space', () => {
    const building = first(read(FZK_LOD2), Building);
    const code = building.class_()?.code();
    assert.equal(code?.value(), '1000');
    assert.equal(code?.codeSpace(), `${SIG3D}class.xml`);
    assert.deepEqual(all(building.functions()).map((f) => f.code().codeSpace()), [`${SIG3D}function.xml`]);
    assert.deepEqual(all(building.usages()).map((u) => u.code().codeSpace()), [`${SIG3D}usage.xml`]);

    const functions = all(first(read(TUM), Building).functions());
    assert.deepEqual(functions.map((f) => [f.value(), f.code().codeSpace()]), [['31001_3020', null]]);

    const names = all(read(FZK_LOD1).names());
    assert.deepEqual(names.map((n) => [n.value(), n.codeSpace()]), [['AC14-FZK-Haus', null]]);
});
