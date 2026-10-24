// The cases of crates/ecitygml/tests/conformance/asam-opendrive.md.
import assert from 'node:assert/strict';
import { describe, test } from 'node:test';

import {
    AbstractFeatureKindRef,
    AbstractSpaceBoundaryPropertyIterator,
    AuxiliaryTrafficArea,
    CityModel,
    DirectPosition,
    FeatureType,
    GranularityValue,
    LineString,
    MultiCurve,
    Reference,
    Road,
    Section,
    SpaceType,
    TrafficArea,
    TrafficDirectionValue,
    TrafficSpace,
    TrafficSpaceReferenceIterator,
} from '../../lib/index.mjs';
import { all, assertClose, read } from './helpers.ts';

const ROAD_SHAPE = 'ASAM-UC_RoadShape.gml';
const JUNCTION = 'ASAM-Ex_Bidirectional_Junction.gml';

const SPACES = [
    'UUID_ae81947d-a661-3678-a5ee-eed58b68694f',
    'UUID_6e4de408-1e54-3869-b7ce-1be3f2261421',
    'UUID_9582b02f-5cc7-38f8-b79c-a3a18b31856c',
    'UUID_c772e261-27f1-30b6-8a94-1ccf23e71a74',
    'UUID_656f23c9-92b6-3c98-a1bf-40b5f2625b13',
    'UUID_86f8df09-c972-332b-a279-636373ce4e0c',
    'UUID_144a6807-5844-32b2-bb34-8b2671b1afaa',
];

type Point = [number, number, number];

function road(cityModel: CityModel): Road {
    const found = all(cityModel.iterFeatures()).map((f) => Road.tryFrom(f)).find((r) => r !== null);
    assert.ok(found);
    return found;
}

/** The objects of inline properties; fails on a reference-only property. */
function objects<T>(properties: { next(): IteratorResult<{ href(): unknown; object(): T | null }> }): T[] {
    return all(properties).map((property) => {
        assert.equal(property.href(), null);
        const object = property.object();
        assert.ok(object !== null);
        return object;
    });
}

function ids(features: { featureId(): { asStr(): string } }[]): string[] {
    return features.map((f) => f.featureId().asStr());
}

function firstName(feature: { names(): { next(): IteratorResult<{ value(): string }> } }): string {
    const name = feature.names().next();
    assert.ok(!name.done);
    return name.value.value();
}

function assertPointClose(position: DirectPosition, expected: Point): void {
    [position.x(), position.y(), position.z()].forEach((value, i) => assertClose(value, expected[i]));
}

function assertEnvelope(cityModel: CityModel, lower: Point, upper: Point): void {
    const envelope = cityModel.boundedBy()?.envelope();
    assert.ok(envelope);
    assertPointClose(envelope.lowerCorner(), lower);
    assertPointClose(envelope.upperCorner(), upper);
}

/** The single boundary of a space, inline, as a feature. */
function onlyBoundary(space: { boundaries(): AbstractSpaceBoundaryPropertyIterator }): AbstractFeatureKindRef {
    const boundaries = objects(space.boundaries());
    assert.equal(boundaries.length, 1);
    return AbstractFeatureKindRef.fromSpaceBoundary(boundaries[0]);
}

/** The single curve member of an inline multi curve, as a line string: [point count, length]. */
function lineString(multiCurve: MultiCurve): [number, number] {
    const members = objects(multiCurve.curveMember());
    assert.equal(members.length, 1);
    const curve = LineString.tryFrom(members[0]);
    assert.ok(curve);
    return [all(curve.points()).length, curve.length3d()];
}

function localIds(references: TrafficSpaceReferenceIterator): (string | null)[] {
    return all(references).map((r) => Reference.fromTrafficSpaceReference(r).href()?.localId() ?? null);
}

function values(iterator: { next(): IteratorResult<{ value(): string }> }): string[] {
    return all(iterator).map((v) => v.value());
}

describe('road shape', () => {
    const cityModel = read('asam-opendrive', ROAD_SHAPE);

    const section = (): Section => {
        const sections = objects(road(cityModel).sections());
        assert.equal(sections.length, 1);
        return sections[0];
    };
    const trafficSpaces = (): TrafficSpace[] => objects(section().trafficSpaces());

    test('road shape city model', () => {
        assert.equal(cityModel.cityObjectsLen(), 1);
        const types = [
            FeatureType.CityModel,
            FeatureType.Road,
            FeatureType.Section,
            FeatureType.TrafficSpace,
            FeatureType.TrafficArea,
            FeatureType.TrafficSpace,
            FeatureType.TrafficArea,
            FeatureType.AuxiliaryTrafficSpace,
            FeatureType.AuxiliaryTrafficArea,
            FeatureType.AuxiliaryTrafficSpace,
            FeatureType.AuxiliaryTrafficArea,
        ];
        assert.deepEqual(all(cityModel.iterFeatures()).map((f) => f.featureType()), types);
        assert.deepEqual(all(cityModel.iterCityObjects()).map((o) => o.featureType()), types.slice(1));
        assertEnvelope(
            cityModel,
            [-50.21567184593757, -2.4442507170297514, 0.0],
            [-13.007511850967884, 29.053746110395082, 4.95],
        );
    });

    test('road shape road', () => {
        const r = road(cityModel);
        assert.equal(r.featureId().asStr(), 'UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f');
        assert.equal(r.class_(), null);
        assert.equal(r.trafficDirection(), null);
        for (const empty of [
            r.functions(),
            r.usages(),
            r.intersections(),
            r.occupancies(),
            r.trafficSpaces(),
            r.auxiliaryTrafficSpaces(),
            r.markings(),
            r.holes(),
        ]) {
            assert.equal(all(empty).length, 0);
        }
        assert.equal(section().featureId().asStr(), 'UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29');
    });

    test('road shape section', () => {
        const s = section();
        assert.equal(s.class_(), null);
        assert.equal(s.trafficDirection(), null);
        assert.equal(s.lod0MultiCurve(), null);
        assert.equal(s.lod1Solid(), null);
        assert.equal(all(s.markings()).length, 0);
        assert.equal(all(s.holes()).length, 0);
        assert.deepEqual(ids(objects(s.trafficSpaces())), [
            'UUID_ae81947d-a661-3678-a5ee-eed58b68694f',
            'UUID_6e4de408-1e54-3869-b7ce-1be3f2261421',
        ]);
        assert.deepEqual(ids(objects(s.auxiliaryTrafficSpaces())), [
            'UUID_12298df9-4982-33a8-ab4a-9953410bbff7',
            'UUID_f8211bb5-0ce8-36e1-9b84-73d30114f578',
        ]);
    });

    test('road shape traffic spaces', () => {
        const spaces = trafficSpaces();
        assert.deepEqual(spaces.map((s) => s.trafficDirection()), [
            TrafficDirectionValue.Backwards,
            TrafficDirectionValue.Forwards,
        ]);
        for (const space of spaces) {
            assert.equal(space.granularity(), GranularityValue.Lane);
            assert.equal(space.class_(), null);
            assert.deepEqual(values(space.functions()), ['1']);
            assert.deepEqual(values(space.usages()), ['2']);
            assert.equal(all(space.occupancies()).length, 0);
            assert.equal(space.spaceType(), SpaceType.Open);
            assert.equal(space.relativeToTerrain(), null);
            assert.equal(space.creationDate(), null);
            assert.equal(all(space.predecessors()).length, 0);
            assert.equal(all(space.successors()).length, 0);
            assert.ok(TrafficArea.tryFrom(onlyBoundary(space)));
        }
    });

    test('road shape generic attributes', () => {
        const attributes = all(trafficSpaces()[0].genericAttributes()).map((a) => {
            const int = a.asInt();
            const double = a.asDouble();
            // 64-bit integers are BigInts in JavaScript.
            if (int) return [a.name(), 'int', int.value()];
            if (double) return [a.name(), 'double', double.value()];
            return [a.name(), 'string', a.asString()?.value()];
        });
        assert.deepEqual(attributes, [
            ['identifier_laneId', 'int', 1n],
            ['identifier_laneSectionId', 'int', 0n],
            ['identifier_roadId', 'string', '1'],
            ['opendrive_road_length', 'double', 40.0],
            ['opendrive_road_rule', 'string', 'RIGHT_HAND_TRAFFIC'],
            ['opendrive_laneSection_curvePositionStart', 'double', 0.0],
            ['opendrive_lane_type', 'string', 'DRIVING'],
            ['opendrive_lane_level', 'string', 'false'],
        ]);
    });

    test('road shape traffic space geometry', () => {
        const spaces = trafficSpaces();
        const volumes = spaces.map((s) => s.lod2Solid()?.object()?.volume3d() ?? Number.NaN);
        assertClose(volumes[0], 720.0);
        assertClose(volumes[1], 540.0);
        for (const space of spaces) {
            const property = space.lod2MultiCurve();
            assert.ok(property);
            assert.equal(property.href(), null);
            const multiCurve = property.object();
            assert.ok(multiCurve);
            assertClose(multiCurve.length3d(), 40.0);
            const [points, length] = lineString(multiCurve);
            assert.equal(points, 2);
            assertClose(length, 40.0);
            assert.equal(space.lod0MultiCurve(), null);
            assert.equal(space.lod3MultiCurve(), null);
            assert.equal(space.lod1Solid(), null);
            assert.equal(space.lod3Solid(), null);
            assert.equal(space.lod2MultiSurface(), null);
        }
    });

    test('road shape traffic areas', () => {
        const areas = trafficSpaces().map((s) => {
            const area = TrafficArea.tryFrom(onlyBoundary(s));
            assert.ok(area);
            return area;
        });
        assert.deepEqual(ids(areas), [
            'UUID_8625bf6f-57cb-3ddf-8fd1-6674b756a2e2',
            'UUID_dc110e80-dadc-3c87-b864-2854cc0cb39a',
        ]);
        const area3d: number[] = [];
        for (const area of areas) {
            assert.equal(firstName(area), 'Lane');
            assert.equal(area.class_(), null);
            assert.deepEqual(values(area.functions()), ['1']);
            assert.deepEqual(values(area.usages()), ['2']);
            assert.equal(area.surfaceMaterial(), null);
            assert.equal(area.lod0MultiCurve(), null);
            assert.equal(area.lod0MultiSurface(), null);
            assert.equal(area.lod1MultiSurface(), null);
            assert.equal(area.lod3MultiSurface(), null);
            assert.equal(area.relativeToTerrain(), null);
            const multiSurface = area.lod2MultiSurface()?.object();
            assert.ok(multiSurface);
            assert.equal(all(multiSurface.surfaceMember()).length, 1);
            area3d.push(multiSurface.area3d());
        }
        assertClose(area3d[0], 160.79800993793438);
        assertClose(area3d[1], 121.34249049694012);
    });

    test('road shape auxiliary traffic', () => {
        const spaces = objects(section().auxiliaryTrafficSpaces());
        for (const space of spaces) {
            assert.equal(space.granularity(), GranularityValue.Lane);
            assert.equal(space.class_(), null);
            assert.equal(all(space.functions()).length, 0);
            assert.equal(all(space.usages()).length, 0);
            assert.equal(space.spaceType(), SpaceType.Open);
            assertClose(space.lod2Solid()?.object()?.volume3d() ?? Number.NaN, 100.0);
            assertClose(space.lod2MultiCurve()?.object()?.length3d() ?? Number.NaN, 40.0);
        }
        const areas = spaces.map((s) => {
            const area = AuxiliaryTrafficArea.tryFrom(onlyBoundary(s));
            assert.ok(area);
            return area;
        });
        assert.deepEqual(ids(areas), [
            'UUID_4890681a-e9fa-365e-a676-f89afb453f9b',
            'UUID_d3c71d48-5222-355e-8037-9677aee30d7e',
        ]);
        for (const area of areas) {
            assert.equal(firstName(area), 'Lane');
            assert.equal(area.class_(), null);
            assert.equal(all(area.functions()).length, 0);
            assert.equal(all(area.usages()).length, 0);
            assert.equal(area.surfaceMaterial(), null);
            assertClose(area.lod2MultiSurface()?.object()?.area3d() ?? Number.NaN, 40.0);
        }
    });
});

describe('junction', () => {
    const cityModel = read('asam-opendrive', JUNCTION);

    const trafficSpaces = (): TrafficSpace[] =>
        all(cityModel.iterFeatures()).map((f) => TrafficSpace.tryFrom(f)).filter((s) => s !== null);

    test('junction city model', () => {
        assert.equal(cityModel.cityObjectsLen(), 1);
        const T = FeatureType;
        assert.deepEqual(all(cityModel.iterFeatures()).map((f) => f.featureType()), [
            T.CityModel, T.Road, T.Section, T.TrafficSpace, T.TrafficArea, T.TrafficSpace, T.TrafficArea,
            T.Marking, T.Marking, T.Marking, T.Marking, T.Section, T.TrafficSpace, T.TrafficArea, T.Section,
            T.TrafficSpace, T.TrafficArea, T.Intersection, T.TrafficSpace, T.TrafficArea, T.TrafficSpace,
            T.TrafficArea, T.TrafficSpace, T.TrafficArea,
        ]);
        assert.equal(all(cityModel.iterCityObjects()).length, 23);
        assertEnvelope(
            cityModel,
            [-52.66282419815818, -37.4146115571896, 0.0],
            [34.10760429351533, 6.338805461729647, 0.0],
        );
    });

    test('junction road', () => {
        const r = road(cityModel);
        assert.equal(r.featureId().asStr(), 'UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f');
        const sections = objects(r.sections());
        assert.deepEqual(ids(sections), [
            'UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29',
            'UUID_ef20f165-2564-373a-a5f8-98fd15f1ae69',
            'UUID_4799566b-daf4-3135-aa9d-ec1b34a9167d',
        ]);
        assert.deepEqual(sections.map((s) => all(s.trafficSpaces()).length), [2, 1, 1]);
        assert.deepEqual(sections.map((s) => all(s.markings()).length), [4, 0, 0]);
        assert.ok(sections.every((s) => all(s.auxiliaryTrafficSpaces()).length === 0));
        const intersections = objects(r.intersections());
        assert.equal(intersections.length, 1);
        assert.equal(intersections[0].featureId().asStr(), 'UUID_47b7678d-e8b1-36ca-90b6-5b86cc859571');
        assert.equal(intersections[0].class_(), null);
        assert.deepEqual(ids(objects(intersections[0].trafficSpaces())), SPACES.slice(4));
    });

    test('junction traffic spaces', () => {
        const spaces = trafficSpaces();
        assert.deepEqual(ids(spaces), SPACES);
        assert.deepEqual(spaces.map((s) => s.trafficDirection()), [
            TrafficDirectionValue.Backwards,
            ...Array(6).fill(TrafficDirectionValue.Forwards),
        ]);
        assert.ok(spaces.every((s) => s.lod2Solid() === null));
        const curves = spaces.map((s) => {
            const multiCurve = s.lod2MultiCurve()?.object();
            assert.ok(multiCurve);
            return lineString(multiCurve);
        });
        assert.deepEqual(curves.map(([points]) => points), [9, 9, 5, 6, 7, 8, 7]);
        const lengths = [
            36.74683751297985, 36.74683751297985, 20.0, 21.746217945006258, 26.761532846607814, 30.210435770102656,
            30.0,
        ];
        curves.forEach(([, length], i) => assertClose(length, lengths[i]));
    });

    test('junction traffic areas', () => {
        const surfaces = all(cityModel.iterFeatures())
            .map((f) => TrafficArea.tryFrom(f))
            .filter((a) => a !== null)
            .map((a) => {
                const multiSurface = a.lod2MultiSurface()?.object();
                assert.ok(multiSurface);
                return multiSurface;
            });
        assert.deepEqual(surfaces.map((s) => all(s.surfaceMember()).length), [8, 8, 4, 5, 6, 7, 6]);
        const areas = [
            112.81279116484816, 112.81279116484816, 61.4, 66.76088909116919, 81.22157625123039, 92.69041581703632,
            92.1,
        ];
        surfaces.forEach((s, i) => assertClose(s.area3d(), areas[i]));
    });

    test('junction traffic space links', () => {
        const [s0, s1, s2, s3, s4, s5, s6] = SPACES;
        assert.deepEqual(trafficSpaces().map((s) => [localIds(s.predecessors()), localIds(s.successors())]), [
            [[], []],
            [[], [s6]],
            [[s4, s5], []],
            [[], [s4]],
            [[s3], [s2]],
            [['UUID_d7d4aa5a-88c9-328d-9151-a6c043e57d7f'], [s0]],
            [[s1], [s2]],
        ]);
    });

    test('junction markings', () => {
        const section = objects(road(cityModel).sections())[0];
        const markings = objects(section.markings());
        const areas: number[] = [];
        for (const marking of markings) {
            assert.equal(firstName(marking), 'RoadMarking');
            assert.equal(marking.class_(), null);
            assert.equal(marking.lod0MultiSurface(), null);
            assert.equal(marking.lod3MultiSurface(), null);
            const multiSurface = marking.lod2MultiSurface()?.object();
            assert.ok(multiSurface);
            assert.equal(all(multiSurface.surfaceMember()).length, 1);
            areas.push(multiSurface.area3d());
        }
        assert.equal(areas.length, 4);
        [0.48, 0.48, 0.48, 0.08962050155758661].forEach((expected, i) => assertClose(areas[i], expected));
    });
});
