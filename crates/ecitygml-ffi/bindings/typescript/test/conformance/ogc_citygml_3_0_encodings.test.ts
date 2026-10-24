// The cases of crates/ecitygml/tests/conformance/ogc-citygml-3.0-encodings.md.
import assert from 'node:assert/strict';
import { describe, test } from 'node:test';

import {
    AbstractFeatureKindRef,
    Bridge,
    Building,
    BuildingPart,
    BuildingUnit,
    CityModel,
    CitygmlFormat,
    DateTime,
    Envelope,
    FeatureType,
    GmlReader,
    GmlWriter,
    GroundSurface,
    HeightStatusValue,
    LevelOfDetail,
    MultiSurfaceProperty,
    ReliefFeature,
    Road,
    RoofSurface,
    Storey,
    TinRelief,
    TrafficArea,
    WallSurface,
} from '../../lib/index.mjs';
import { all, assertClose, read } from './helpers.ts';

type Point = [number, number, number];

const DATASET = 'ogc-citygml-3.0-encodings';
const { WallSurface: WALL, RoofSurface: ROOF, GroundSurface: GROUND } = FeatureType;

function featureTypes(cityModel: CityModel): FeatureType[] {
    return all(cityModel.iterFeatures()).map((f) => f.featureType());
}

/** All features a class accepts, in document order. */
function allOf<T>(cityModel: CityModel, cls: { tryFrom(feature: AbstractFeatureKindRef): T | null }): T[] {
    return all(cityModel.iterFeatures())
        .map((f) => cls.tryFrom(f))
        .filter((x): x is T => x !== null);
}

function names(feature: { names(): { next(): IteratorResult<{ value(): string }> } }): string[] {
    return all(feature.names()).map((n) => n.value());
}

function assertEnvelope(envelope: Envelope | undefined | null, lower: Point, upper: Point): void {
    assert.ok(envelope);
    for (const [position, expected] of [
        [envelope.lowerCorner(), lower],
        [envelope.upperCorner(), upper],
    ] as const) {
        [position.x(), position.y(), position.z()].forEach((value, i) => assertClose(value, expected[i]));
    }
}

function roundTrip(cityModel: CityModel): CityModel {
    const writer = new GmlWriter(CitygmlFormat.Gml);
    writer.finish(cityModel);
    return new GmlReader(writer.data(), CitygmlFormat.Gml).finish();
}

type Surface = [FeatureType, string, string | null, MultiSurfaceProperty | null];

/** A space's boundaries as [feature type, featureId, first name or null, LoD2 multi surface]; all inline wall, roof or ground surfaces. */
function surfaces(space: { boundaries(): { next(): IteratorResult<any> } }): Surface[] {
    return all(space.boundaries()).map((property) => {
        assert.equal(property.href(), null);
        const object = property.object();
        assert.ok(object);
        const feature = AbstractFeatureKindRef.fromSpaceBoundary(object);
        const surface = WallSurface.tryFrom(feature) ?? RoofSurface.tryFrom(feature) ?? GroundSurface.tryFrom(feature);
        assert.ok(surface, feature.featureType().value);
        return [feature.featureType(), object.featureId().asStr(), names(surface)[0] ?? null, surface.lod2MultiSurface()];
    });
}

function lod2Area(property: MultiSurfaceProperty | null): number {
    const multiSurface = property?.object();
    assert.ok(multiSurface);
    return multiSurface.area3d();
}

function assertHeight(building: { heights(): { next(): IteratorResult<any> } }, length: number): void {
    const heights = all(building.heights());
    assert.equal(heights.length, 1);
    assert.equal(heights[0].highReference().value(), 'highestRoofEdge');
    assert.equal(heights[0].lowReference().value(), 'lowestGroundPoint');
    assert.equal(heights[0].status(), HeightStatusValue.Measured);
    assertClose(heights[0].length().value(), length);
    assert.equal(heights[0].length().uom(), '#m');
}

describe('Building_and_garage_LOD2-EPSG25832.gml', () => {
    const cityModel = read(DATASET, 'Building_and_garage_LOD2-EPSG25832.gml');
    const building = (model: CityModel): Building => {
        const buildings = allOf(model, Building);
        assert.equal(buildings.length, 1);
        return buildings[0];
    };

    test('garage city model', () => {
        assert.equal(cityModel.cityObjectsLen(), 2);
        assertEnvelope(cityModel.boundedBy()?.envelope(), [458868.0, 5438343.0, 112.0], [458892.0, 5438362.0, 117.0]);
        assert.deepEqual(featureTypes(cityModel), [
            FeatureType.CityModel,
            FeatureType.Building,
            GROUND,
            ...Array(4).fill(WALL),
            ROOF,
            ROOF,
            FeatureType.BuildingPart,
            ...Array(4).fill(WALL),
            GROUND,
            ROOF,
            FeatureType.ReliefFeature,
            FeatureType.TinRelief,
        ]);
        assert.equal(all(cityModel.iterCityObjects()).length, 17);
    });

    test('garage building', () => {
        const b = building(cityModel);
        assert.equal(b.featureId().asStr(), 'GML_7b1a5a6f-ddad-4c3d-a507-3eb9ee0a8e68');
        assert.deepEqual(names(b), ['Example Building LOD2']);
        assert.equal(b.class_(), null);
        assert.deepEqual(
            all(b.functions()).map((f) => f.value()),
            ['1000'],
        );
        assert.equal(all(b.usages()).length, 0);
        assert.equal(b.roofType()?.value(), '1030');
        assert.equal(b.storeysAboveGround(), 1n);
        assert.equal(b.storeysBelowGround(), null);
        const date = b.dateOfConstruction();
        assert.ok(date);
        assert.deepEqual([date.year(), date.month(), date.day()], [1985, 1, 1]);
        assertHeight(b, 6.0);
        const expected: [FeatureType, string, number][] = [
            [GROUND, 'Ground Slab', 50.0],
            [WALL, 'Wall South', 30.0],
            [WALL, 'Wall North', 30.0],
            [WALL, 'Wall East', 20.0],
            [WALL, 'Wall West', 20.0],
            [ROOF, 'Roof North', 32.01562118716424],
            [ROOF, 'Roof South', 32.01562118716424],
        ];
        const actual = surfaces(b);
        assert.deepEqual(
            actual.map(([type, , name]) => [type, name]),
            expected.map(([type, name]) => [type, name]),
        );
        actual.forEach(([, , , multiSurface], i) => assertClose(lod2Area(multiSurface), expected[i][2]));
    });

    test('garage building part', () => {
        const parts = all(building(cityModel).buildingParts());
        assert.equal(parts.length, 1);
        assert.equal(parts[0].href(), null);
        const part = parts[0].object();
        assert.ok(part);
        assert.equal(part.featureId().asStr(), 'GMLID_BUI379228_1244_301');
        assert.deepEqual(names(part), ['Example BuildingPart LOD2']);
        assert.equal(part.class_(), null);
        assert.deepEqual(
            all(part.functions()).map((f) => f.value()),
            ['1630'],
        );
        assert.equal(all(part.usages()).length, 0);
        assert.equal(part.roofType()?.value(), '1010');
        const date = part.dateOfConstruction();
        assert.ok(date);
        assert.deepEqual([date.year(), date.month(), date.day()], [1985, 1, 1]);
        assertHeight(part, 2.5);
        // The west wall's area is left out: its member is a gml:OrientableSurface, not read yet.
        const expected: [FeatureType, string, number | null][] = [
            [WALL, 'Garage Wall East', 9.600000023841858],
            [WALL, 'Garage Wall South', 6.25],
            [WALL, 'Garage Wall West', null],
            [WALL, 'Garage Wall North', 5.75],
            [GROUND, 'Garage Ground Slab', 10.0],
            [ROOF, 'Garage Roof', 10.012492197250394],
        ];
        const actual = surfaces(part);
        assert.deepEqual(
            actual.map(([type, , name]) => [type, name]),
            expected.map(([type, name]) => [type, name]),
        );
        actual.forEach(([, , , multiSurface], i) => {
            const area = expected[i][2];
            if (area !== null) assertClose(lod2Area(multiSurface), area);
        });
    });

    test('garage relief', () => {
        const reliefs = allOf(cityModel, ReliefFeature);
        assert.equal(reliefs.length, 1);
        const relief = reliefs[0];
        assert.equal(relief.featureId().asStr(), 'GML_6bb30328-7599-4500-90ef-766fde6aa67b');
        assert.deepEqual(names(relief), ['Example TIN LOD2']);
        assert.equal(relief.lod(), LevelOfDetail.Two);
        const components = all(relief.reliefComponents());
        assert.equal(components.length, 1);
        assert.equal(components[0].href(), null);
        assert.equal(components[0].object()?.featureType(), FeatureType.TinRelief);

        const tinReliefs = allOf(cityModel, TinRelief);
        assert.equal(tinReliefs.length, 1);
        const tinRelief = tinReliefs[0];
        assert.equal(tinRelief.featureId().asStr(), 'GML_4eb161b0-aa7e-4087-937c-5c4c427c7fc9');
        assert.deepEqual(names(tinRelief), ['Ground']);
        assert.equal(tinRelief.lod(), LevelOfDetail.Two);
        const tin = tinRelief.tin();
        assert.ok(tin);
        assert.equal(tin.href(), null);
        const surface = tin.object();
        assert.ok(surface);
        assert.equal(all(surface.triangles()).length, 12);
        assertClose(surface.area3d(), 399.8446647372588);
    });

    test('garage round trip', () => {
        const written = roundTrip(cityModel);
        assert.deepEqual(featureTypes(written), featureTypes(cityModel));
        const ids = [
            ...allOf(written, Building),
            ...allOf(written, BuildingPart),
            ...allOf(written, ReliefFeature),
            ...allOf(written, TinRelief),
        ].map((x) => x.featureId().asStr());
        assert.deepEqual(ids, [
            'GML_7b1a5a6f-ddad-4c3d-a507-3eb9ee0a8e68',
            'GMLID_BUI379228_1244_301',
            'GML_6bb30328-7599-4500-90ef-766fde6aa67b',
            'GML_4eb161b0-aa7e-4087-937c-5c4c427c7fc9',
        ]);
    });
});

/** The hrefs of a storey's LoD2 surface members (null for inline members). */
function memberHrefs(storey: Storey): (string | null)[] {
    const property = storey.lod2MultiSurface();
    assert.ok(property);
    assert.equal(property.href(), null);
    const multiSurface = property.object();
    assert.ok(multiSurface);
    return all(multiSurface.surfaceMember()).map((member) => {
        assert.equal(member.object() === null, member.href() !== null);
        return member.href()?.toString() ?? null;
    });
}

describe('BuildingUnits_Storeys_xlink.gml', () => {
    const cityModel = read(DATASET, 'BuildingUnits_Storeys_xlink.gml');

    test('units city model', () => {
        assert.equal(cityModel.cityObjectsLen(), 1);
        assertEnvelope(cityModel.boundedBy()?.envelope(), [457841.0, 5439082.0, 111.0], [457854.0, 5439093.0, 121.0]);
        const room = (walls: number) => [
            FeatureType.BuildingRoom,
            ...Array(walls).fill(FeatureType.InteriorWallSurface),
            FeatureType.FloorSurface,
            FeatureType.CeilingSurface,
        ];
        assert.deepEqual(featureTypes(cityModel), [
            FeatureType.CityModel,
            FeatureType.Building,
            ...Array(3).fill(WALL),
            ROOF,
            WALL,
            ROOF,
            GROUND,
            ...room(8),
            ...room(8),
            ...room(4),
            FeatureType.BuildingUnit,
            FeatureType.BuildingUnit,
            FeatureType.Storey,
            FeatureType.Storey,
        ]);
        assert.equal(all(cityModel.iterCityObjects()).length, 41);
    });

    test('units building', () => {
        const [b] = allOf(cityModel, Building);
        assert.equal(b.featureId().asStr(), 'building_unit_example_1');
        assert.equal(all(b.names()).length, 0);
        assert.equal(all(b.functions()).length, 0);
        assert.equal(all(b.usages()).length, 0);
        assert.equal(b.class_(), null);
        assert.equal(b.roofType(), null);
        const expected: [FeatureType, string, number][] = [
            [WALL, 'Outer Wall 1 (West)', 89.375],
            [WALL, 'Outer Wall 2 (South)', 81.25],
            [WALL, 'Outer Wall 3 (East)', 89.375],
            [ROOF, 'Roof 1 (North)', 86.53792521201326],
            [WALL, 'Outer Wall 4 (North)', 81.25],
            [ROOF, 'Roof 2 (South)', 86.53792521201326],
            [GROUND, 'Base Surface', 143.0],
        ];
        const actual = surfaces(b);
        assert.deepEqual(
            actual.map(([type, , name]) => [type, name]),
            expected.map(([type, name]) => [type, name]),
        );
        actual.forEach(([, , , multiSurface], i) => assertClose(lod2Area(multiSurface), expected[i][2]));
    });

    test('units subdivisions', () => {
        const [b] = allOf(cityModel, Building);
        const subdivisions = all(b.buildingSubdivisions());
        assert.ok(subdivisions.every((p) => p.href() === null));
        assert.deepEqual(
            subdivisions.map((p) => p.object()?.featureType()),
            [FeatureType.BuildingUnit, FeatureType.BuildingUnit, FeatureType.Storey, FeatureType.Storey],
        );
        const units = allOf(cityModel, BuildingUnit);
        assert.deepEqual(
            units.map((u) => u.featureId().asStr()),
            ['BuildingUnit_apartment1', 'BuildingUnit_apartment2'],
        );
        for (const unit of units) {
            assert.deepEqual(
                all(unit.functions()).map((f) => f.value()),
                ['apartment'],
            );
            assert.equal(unit.class_(), null);
            assert.equal(all(unit.usages()).length, 0);
            assert.equal(all(unit.boundaries()).length, 0);
            assert.equal(unit.lod2MultiSurface(), null);
        }
        const storeys = allOf(cityModel, Storey);
        assert.deepEqual(
            storeys.map((s) => s.featureId().asStr()),
            ['storey1', 'storey2'],
        );
        for (const storey of storeys) {
            assert.equal(all(storey.names()).length, 0);
            assert.equal(storey.class_(), null);
            assert.equal(all(storey.functions()).length, 0);
            assert.equal(all(storey.usages()).length, 0);
            assert.equal(all(storey.boundaries()).length, 0);
        }
    });

    test('units storey geometry', () => {
        const expected: [string[], Point, Point][] = [
            [
                [
                    '#Wall_1_PolyID82397_997_453711_16336011',
                    '#Wall_1_PolyID82397_997_453711_16336012',
                    '#Wall_1_PolyID82397_997_453711_163360136',
                ],
                [457841.1, 5439082.1, 111.1],
                [457853.9, 5439092.9, 113.9],
            ],
            [
                [
                    '#Wall_1_PolyID82397_997_453711_163360112',
                    '#Wall_1_PolyID82397_997_453711_163360122',
                    '#Wall_1_PolyID82397_997_453711_1633601362',
                ],
                [457841.1, 5439082.1, 114.1],
                [457853.9, 5439092.9, 116.9],
            ],
        ];
        const storeys = allOf(cityModel, Storey);
        assert.equal(storeys.length, expected.length);
        storeys.forEach((storey, i) => {
            const [hrefs, lower, upper] = expected[i];
            assert.deepEqual(memberHrefs(storey), [null, ...hrefs, null, null]);
            const multiSurface = storey.lod2MultiSurface()?.object();
            assert.ok(multiSurface);
            assert.throws(() => multiSurface.area3d());
            assertEnvelope(storey.boundedBy()?.envelope(), lower, upper);
        });
    });

    test('units round trip', () => {
        const written = roundTrip(cityModel);
        assert.deepEqual(featureTypes(written), featureTypes(cityModel));
        const [b] = allOf(written, Building);
        assert.equal(b.featureId().asStr(), 'building_unit_example_1');
        assert.deepEqual(allOf(written, Storey).map(memberHrefs), allOf(cityModel, Storey).map(memberHrefs));
    });
});

/** The relations of the roof surfaces and traffic areas, in document order: [city object, relation type, href of relationTo]. */
function relations(cityModel: CityModel): [string, string, string | null][] {
    return all(cityModel.iterFeatures()).flatMap((feature) => {
        const object = RoofSurface.tryFrom(feature) ?? TrafficArea.tryFrom(feature);
        if (object === null) return [];
        return all(object.relatedTo()).map((property): [string, string, string | null] => {
            assert.equal(property.href(), null);
            const relation = property.object();
            assert.ok(relation);
            assert.equal(all(relation.genericAttributes()).length, 0);
            return [object.featureId().asStr(), relation.relationType().value(), relation.relationTo().href()?.toString() ?? null];
        });
    });
}

describe('Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml', () => {
    const cityModel = read(DATASET, 'Road_over_Bridge_CityGML3.0_LOD2_with_CityObjectRelations.gml');

    test('road bridge city model', () => {
        assert.equal(cityModel.cityObjectsLen(), 2);
        assert.equal(cityModel.boundedBy(), null);
        const section = [FeatureType.Section, FeatureType.TrafficSpace, FeatureType.TrafficArea, FeatureType.TrafficSpace, FeatureType.TrafficArea];
        assert.deepEqual(featureTypes(cityModel), [
            FeatureType.CityModel,
            FeatureType.Bridge,
            GROUND,
            ROOF,
            ROOF,
            ...Array(4).fill(WALL),
            FeatureType.Road,
            ...section,
            ...section,
            ...section,
        ]);
        assert.equal(all(cityModel.iterCityObjects()).length, 24);
    });

    test('road bridge bridge', () => {
        const [bridge] = allOf(cityModel, Bridge);
        assert.equal(bridge.featureId().asStr(), 'id_bridge1');
        assert.equal(all(bridge.names()).length, 0);
        assert.equal(all(bridge.relatedTo()).length, 0);
        const expected: [string, number][] = [
            ['id_groundsurface1', 77500.15996032],
            ['id_roofsurface1', 38750.07998016],
            ['id_roofsurface2', 38750.07998016],
            ['id_wallsurface4', 10075.02000744],
            ['id_wallsurface1', 20150.04001488],
            ['id_wallsurface2', 10075.02000744],
            ['id_wallsurface3', 20150.04001488],
        ];
        const actual = surfaces(bridge);
        assert.deepEqual(
            actual.map(([, id]) => id),
            expected.map(([id]) => id),
        );
        actual.forEach(([, , , multiSurface], i) => assertClose(lod2Area(multiSurface), expected[i][1]));
    });

    test('road bridge road', () => {
        const [road] = allOf(cityModel, Road);
        assert.equal(road.featureId().asStr(), 'id_road1');
        assert.equal(all(road.relatedTo()).length, 0);
        assert.equal(all(road.trafficSpaces()).length, 0);
        assert.equal(all(road.auxiliaryTrafficSpaces()).length, 0);
        const sections = all(road.sections()).map((property) => {
            assert.equal(property.href(), null);
            const section = property.object();
            assert.ok(section);
            return section;
        });
        assert.deepEqual(
            sections.map((s) => s.featureId().asStr()),
            ['id_section1', 'id_section2', 'id_section3'],
        );
        const spaces = sections.flatMap((section) =>
            all(section.trafficSpaces()).map((property) => {
                assert.equal(property.href(), null);
                const space = property.object();
                assert.ok(space);
                return space;
            }),
        );
        const numbers = [1, 2, 5, 6, 3, 4];
        assert.deepEqual(
            spaces.map((s) => s.featureId().asStr()),
            numbers.map((n) => `id_trafficspace${n}`),
        );
        spaces.forEach((space, i) => {
            const boundaries = all(space.boundaries());
            assert.equal(boundaries.length, 1);
            assert.equal(boundaries[0].href(), null);
            const area = boundaries[0].object();
            assert.ok(area);
            assert.equal(area.featureType(), FeatureType.TrafficArea);
            assert.equal(area.featureId().asStr(), `id_trafficarea${numbers[i]}`);
        });
    });

    test('road bridge relations', () => {
        assert.deepEqual(relations(cityModel), [
            ['id_roofsurface1', 'equal', 'id_trafficarea5'],
            ['id_roofsurface2', 'equal', 'id_trafficarea6'],
            ['id_trafficarea5', 'equal', 'id_roofSurface1'],
            ['id_trafficarea6', 'equal', 'id_roofSurface2'],
        ]);
        assert.ok(allOf(cityModel, WallSurface).every((w) => all(w.relatedTo()).length === 0));
        assert.ok(allOf(cityModel, GroundSurface).every((g) => all(g.relatedTo()).length === 0));
    });

    test('road bridge round trip', () => {
        const written = roundTrip(cityModel);
        assert.deepEqual(featureTypes(written), featureTypes(cityModel));
        assert.deepEqual(
            allOf(written, Bridge).map((b) => b.featureId().asStr()),
            ['id_bridge1'],
        );
        assert.deepEqual(
            allOf(written, Road).map((r) => r.featureId().asStr()),
            ['id_road1'],
        );
        assert.deepEqual(relations(written), relations(cityModel));
    });
});

/** [year, month, day] of a date time at 00:00 UTC. */
function date(dateTime: DateTime | null): [number, number, number] | null {
    if (dateTime === null) return null;
    assert.deepEqual([dateTime.hour(), dateTime.minute(), dateTime.offsetSeconds()], [0, 0, 0]);
    return [dateTime.year(), dateTime.month(), dateTime.day()];
}

describe('historicalSuccession_CityGML_3.0_LOD2_Versioning.gml', () => {
    const cityModel = read(DATASET, 'historicalSuccession_CityGML_3.0_LOD2_Versioning.gml');

    test('versioning city model', () => {
        assert.equal(cityModel.cityObjectsLen(), 4);
        assert.equal(cityModel.boundedBy(), null);
        const types = featureTypes(cityModel);
        assert.equal(types.length, 60);
        assert.equal(types[0], FeatureType.CityModel);
        const counts = new Map<string, number>();
        for (const type of types) counts.set(type.value, (counts.get(type.value) ?? 0) + 1);
        assert.deepEqual(
            counts,
            new Map(
                (
                    [
                        [FeatureType.CityModel, 1],
                        [FeatureType.Building, 4],
                        [FeatureType.BuildingPart, 5],
                        [ROOF, 14],
                        [WALL, 31],
                        [GROUND, 5],
                    ] as const
                ).map(([type, count]) => [type.value, count]),
            ),
        );
        assert.equal(all(cityModel.iterCityObjects()).length, 59);
    });

    test('versioning buildings', () => {
        const expected: [string, string, [number, number, number], [number, number, number] | null, string[]][] = [
            ['BU_69381AL47_2000-01-01', 'Building A', [2000, 1, 1], [2015, 1, 1], ['BU_69381AL47_1']],
            ['BU_69381AL49_2000-01-01', 'Building B', [2000, 1, 1], [2015, 1, 1], ['BU_69381AL49_1_2000-01-01']],
            ['BU_69381AL49_2015-01-01', 'Building B', [2015, 1, 1], null, ['BU_69381AL49_1_2015-01-01', 'BU_69381AL49_2_2015-01-01']],
            ['BU_69381AL50_2015-01-01', 'Building C', [2015, 1, 1], null, ['BU_69381AL50_1']],
        ];
        const buildings = allOf(cityModel, Building);
        assert.equal(buildings.length, expected.length);
        buildings.forEach((b, i) => {
            const [id, name, created, terminated, parts] = expected[i];
            assert.equal(b.featureId().asStr(), id);
            assert.equal(names(b)[0], name);
            assert.deepEqual(date(b.creationDate()), created);
            assert.deepEqual(date(b.terminationDate()), terminated);
            const properties = all(b.buildingParts());
            assert.ok(properties.every((p) => p.href() === null));
            assert.deepEqual(
                properties.map((p) => p.object()?.featureId().asStr()),
                parts,
            );
            assert.equal(all(b.heights()).length, 0);
            assert.equal(all(b.boundaries()).length, 0);
        });
    });

    test('versioning building parts', () => {
        const expected: [string, number, number][] = [
            ['BU_69381AL47_1', 13.015, 8],
            ['BU_69381AL49_1_2000-01-01', 10.63, 9],
            ['BU_69381AL49_1_2015-01-01', 10.63, 9],
            ['BU_69381AL49_2_2015-01-01', 8.743, 7],
            ['BU_69381AL50_1', 18.215, 17],
        ];
        const parts = allOf(cityModel, BuildingPart);
        assert.equal(parts.length, expected.length);
        parts.forEach((part, i) => {
            const [id, height, boundaries] = expected[i];
            assert.equal(part.featureId().asStr(), id);
            assertHeight(part, height);
            assert.equal(all(part.boundaries()).length, boundaries);
            assert.equal(part.creationDate(), null);
            assert.equal(all(part.names()).length, 0);
        });
    });

    test('versioning round trip', () => {
        const written = roundTrip(cityModel);
        assert.deepEqual(featureTypes(written), featureTypes(cityModel));
        const ids = (model: CityModel) => [...allOf(model, Building), ...allOf(model, BuildingPart)].map((x) => x.featureId().asStr());
        const dates = (model: CityModel) => allOf(model, Building).map((b) => [date(b.creationDate()), date(b.terminationDate())]);
        assert.deepEqual(ids(written), ids(cityModel));
        assert.deepEqual(dates(written), dates(cityModel));
    });
});
