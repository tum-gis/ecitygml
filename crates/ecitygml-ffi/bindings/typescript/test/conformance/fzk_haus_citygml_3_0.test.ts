// The cases of crates/ecitygml/tests/conformance/fzk-haus-citygml-3.0.md.
import assert from 'node:assert/strict';
import { describe, test } from 'node:test';

import {
    AbstractFeatureKindRef,
    Building,
    CityModel,
    CitygmlFormat,
    DirectPosition,
    FeatureType,
    GmlReader,
    GmlWriter,
    GroundSurface,
    HeightStatusValue,
    MultiSurfaceProperty,
    RoofSurface,
    Storey,
    WallSurface,
} from '../../lib/index.mjs';
import { all, assertClose, building, firstName, read } from './helpers.ts';

type Point = [number, number, number];

const DATASET = 'fzk-haus-citygml-3.0';
const CONSTRUCTION_ID = '_FZK-Haus-Storey-Construction_BD.DX9Xm6VLbbyLGAxG2v86';
const TEST_BUILDING_ID = 'KIT-Test-Building-01';
const WINDOW_ID = '_FZK-Haus-Storey-Construction-tex-Windows_BD.CvWEAVLAPO2cqWPW8xrz';

const { WallSurface: WALL, RoofSurface: ROOF, GroundSurface: GROUND } = FeatureType;

function assertPointClose(position: DirectPosition, expected: Point): void {
    [position.x(), position.y(), position.z()].forEach((value, i) => assertClose(value, expected[i]));
}

function featureTypes(cityModel: CityModel): FeatureType[] {
    return all(cityModel.iterFeatures()).map((f) => f.featureType());
}

/** The number of features per feature type (by name), over `iterFeatures`. */
function featureTypeCounts(cityModel: CityModel): Map<string, number> {
    const counts = new Map<string, number>();
    for (const type of featureTypes(cityModel)) {
        counts.set(type.value, (counts.get(type.value) ?? 0) + 1);
    }
    return counts;
}

function storeys(cityModel: CityModel): Storey[] {
    return all(cityModel.iterFeatures())
        .map((f) => Storey.tryFrom(f))
        .filter((s) => s !== null);
}

function assertCityModel(cityModel: CityModel, lower: Point, upper: Point): void {
    assert.equal(cityModel.cityObjectsLen(), 1);
    const envelope = cityModel.boundedBy()?.envelope();
    assert.ok(envelope);
    assertPointClose(envelope.lowerCorner(), lower);
    assertPointClose(envelope.upperCorner(), upper);
}

/** The one height and occupancy of the storey examples' buildings. */
function assertHeightAndOccupancy(b: Building): void {
    const heights = all(b.heights());
    assert.equal(heights.length, 1);
    assert.equal(heights[0].highReference().value(), 'highestRoofEdge');
    assert.equal(heights[0].lowReference().value(), 'lowestGroundPoint');
    assert.equal(heights[0].status(), HeightStatusValue.Measured);
    assertClose(heights[0].length().value(), 6.52);
    assert.equal(heights[0].length().uom(), 'urn:adv:uom:m');
    const occupancies = all(b.occupancies());
    assert.equal(occupancies.length, 1);
    assert.equal(occupancies[0].numberOfOccupants(), 2n);
}

/** The storeys' first names and classes. */
function assertStoreys(cityModel: CityModel, classes: (string | null)[]): void {
    const found = storeys(cityModel);
    assert.deepEqual(
        found.map((s) => firstName(s)),
        ['Ground Floor', 'Second Floor'],
    );
    assert.deepEqual(
        found.map((s) => s.class_()?.value() ?? null),
        classes,
    );
}

/** A storey's boundaries as [feature type, first name, LoD2 multi surface]; all inline wall, roof or ground surfaces. */
function boundarySurfaces(storey: Storey): [FeatureType, string, MultiSurfaceProperty | null][] {
    return all(storey.boundaries()).map((property) => {
        assert.equal(property.href(), null);
        const object = property.object();
        assert.ok(object);
        const feature = AbstractFeatureKindRef.fromSpaceBoundary(object);
        const surface = WallSurface.tryFrom(feature) ?? RoofSurface.tryFrom(feature) ?? GroundSurface.tryFrom(feature);
        assert.ok(surface, feature.featureType().value);
        return [feature.featureType(), firstName(surface), surface.lod2MultiSurface()];
    });
}

/** Writes the city model and reads it back: the same feature types in the same order and the building's id. */
function assertRoundTrip(cityModel: CityModel, buildingId: string): void {
    const writer = new GmlWriter(CitygmlFormat.Gml);
    writer.finish(cityModel);
    const written = new GmlReader(writer.data(), CitygmlFormat.Gml).finish();
    assert.deepEqual(featureTypes(written), featureTypes(cityModel));
    assert.equal(building(written).featureId().asStr(), buildingId);
}

describe('01-FZK-Haus-LoD2-Tex-Storey-Construction-CG30-V01.gml', () => {
    const cityModel = read(DATASET, '01-FZK-Haus-LoD2-Tex-Storey-Construction-CG30-V01.gml');

    test('construction city model', () => {
        assertCityModel(cityModel, [458899.5, 5438784.5, 113.5], [458912.5, 5438795.5, 120.017691]);
        assert.deepEqual(featureTypes(cityModel), [
            FeatureType.CityModel,
            FeatureType.Building,
            FeatureType.Storey,
            ...Array(5).fill(FeatureType.BuildingConstructiveElement),
            FeatureType.Storey,
            ...Array(6).fill(FeatureType.BuildingConstructiveElement),
            FeatureType.Appearance,
            ...Array(5).fill(FeatureType.ParameterizedTexture),
            ...Array(5).fill(FeatureType.X3dMaterial),
        ]);
        assert.equal(all(cityModel.iterCityObjects()).length, 14);
    });

    test('construction building', () => {
        const b = building(cityModel);
        assert.equal(b.featureId().asStr(), CONSTRUCTION_ID);
        assert.deepEqual(
            all(b.names()).map((n) => n.value()),
            ['KIT FZK-Haus'],
        );
        assert.equal(b.class_(), null);
        assert.deepEqual(
            all(b.functions()).map((f) => f.value()),
            ['31001_1000'],
        );
        assert.equal(all(b.usages()).length, 0);
        assert.equal(b.roofType()?.value(), '3100');
        assert.equal(b.storeysAboveGround(), null);
        assert.equal(b.storeysBelowGround(), null);
        assertHeightAndOccupancy(b);
        assert.equal(all(b.boundaries()).length, 0);
        assert.equal(all(b.genericAttributes()).length, 0);
        assert.equal(b.lod2Solid(), null);
        assert.equal(b.lod2MultiSurface(), null);
    });

    test('construction storeys', () => {
        const subdivisions = all(building(cityModel).buildingSubdivisions());
        assert.equal(subdivisions.length, 2);
        for (const subdivision of subdivisions) {
            assert.equal(subdivision.href(), null);
            assert.equal(subdivision.object()?.featureType(), FeatureType.Storey);
        }
        assertStoreys(cityModel, ['Entrance Floor', 'non Entrance Floor']);
        for (const storey of storeys(cityModel)) {
            assert.equal(all(storey.functions()).length, 0);
            assert.equal(all(storey.usages()).length, 0);
            assert.equal(all(storey.boundaries()).length, 0);
            assert.equal(storey.lod2Solid(), null);
        }
    });

    test('construction round trip', () => {
        assertRoundTrip(cityModel, CONSTRUCTION_ID);
    });
});

describe('04-FZK-Haus-LoD2-Tex-Storey-CG30-V01-InteriorSurface.gml', () => {
    const cityModel = read(DATASET, '04-FZK-Haus-LoD2-Tex-Storey-CG30-V01-InteriorSurface.gml');

    test('interior city model', () => {
        assertCityModel(cityModel, [458900.0, 5438785.0, 113.5], [458912.0, 5438795.0, 120.017691]);
        assert.equal(featureTypes(cityModel).length, 77);
        assert.deepEqual(
            featureTypeCounts(cityModel),
            new Map(
                (
                    [
                        [FeatureType.CityModel, 1],
                        [FeatureType.Building, 1],
                        [FeatureType.Storey, 2],
                        [FeatureType.GroundSurface, 1],
                        [FeatureType.WallSurface, 8],
                        [FeatureType.RoofSurface, 2],
                        [FeatureType.BuildingRoom, 7],
                        [FeatureType.InteriorWallSurface, 27],
                        [FeatureType.CeilingSurface, 8],
                        [FeatureType.FloorSurface, 7],
                        [FeatureType.ClosureSurface, 6],
                        [FeatureType.Appearance, 1],
                        [FeatureType.ParameterizedTexture, 5],
                        [FeatureType.X3dMaterial, 1],
                    ] as const
                ).map(([type, count]) => [type.value, count]),
            ),
        );
        assert.equal(all(cityModel.iterCityObjects()).length, 69);
    });

    test('interior building', () => {
        const b = building(cityModel);
        assert.equal(b.featureId().asStr(), TEST_BUILDING_ID);
        assert.deepEqual(
            all(b.names()).map((n) => n.value()),
            ['KIT Test Building FZK-Haus for CityGML 3.0'],
        );
        assert.equal(b.class_(), null);
        assert.equal(b.roofType(), null);
        assert.equal(all(b.functions()).length, 0);
        assert.equal(all(b.usages()).length, 0);
        assertHeightAndOccupancy(b);
        const attributes = all(b.genericAttributes());
        assert.equal(attributes.length, 1);
        assert.deepEqual(
            [attributes[0].name(), attributes[0].asString()?.value()],
            ['@cityeditor:layer', 'LoD2-Ausgeblendet'],
        );
        assert.equal(all(b.boundaries()).length, 0);
    });

    test('interior solid unresolved', () => {
        const property = building(cityModel).lod2Solid();
        assert.ok(property);
        assert.equal(property.href(), null);
        const solid = property.object();
        assert.ok(solid);
        const shell = solid.exterior();
        assert.ok(shell);
        const members = all(shell.members());
        assert.equal(members.length, 11);
        assert.ok(members.every((member) => member.object() === null));
        assert.throws(() => solid.volume3d());
    });

    test('interior storey boundaries', () => {
        const expected: [FeatureType, string, number][][] = [
            [
                [GROUND, 'Ground', 120.0],
                [WALL, 'Ground Floor / Wall East', 29.0],
                [WALL, 'Ground Floor / Wall South', 34.80000000447035],
                [WALL, 'Ground Floor / Wall West', 29.0],
                [WALL, 'Ground Floor / Wall North', 34.80000000447035],
            ],
            [
                [ROOF, 'Second Floor / Roof South', 69.28203022609509],
                [ROOF, 'Second Floor / Roof North', 69.28203022609509],
                [WALL, 'Second Floor / Wall South', 8.771279998123646],
                [WALL, 'Second Floor / Wall West', 21.743155002593994],
                [WALL, 'Second Floor / Wall East', 21.743155002593994],
                [WALL, 'Second Floor / Wall North', 8.771279998123646],
            ],
        ];
        const found = storeys(cityModel);
        assert.equal(found.length, expected.length);
        found.forEach((storey, i) => {
            const surfaces = boundarySurfaces(storey);
            assert.deepEqual(
                surfaces.map(([type, name]) => [type, name]),
                expected[i].map(([type, name]) => [type, name]),
            );
            surfaces.forEach(([, , multiSurface], j) => {
                const object = multiSurface?.object();
                assert.ok(object);
                assertClose(object.area3d(), expected[i][j][2]);
            });
        });
        assertStoreys(cityModel, [null, null]);
    });

    test('interior round trip', () => {
        assertRoundTrip(cityModel, TEST_BUILDING_ID);
    });
});

describe('04-FZK-Haus-LoD2-Tex-Storey-Construction-CG30-V01-Window-Interior.gml', () => {
    const cityModel = read(DATASET, '04-FZK-Haus-LoD2-Tex-Storey-Construction-CG30-V01-Window-Interior.gml');

    test('window city model', () => {
        assertCityModel(cityModel, [458899.5, 5438784.5, 113.5], [458912.5, 5438795.5, 120.017691]);
        assert.equal(featureTypes(cityModel).length, 54);
        assert.deepEqual(
            featureTypeCounts(cityModel),
            new Map(
                (
                    [
                        [FeatureType.CityModel, 1],
                        [FeatureType.Building, 1],
                        [FeatureType.Storey, 2],
                        [FeatureType.BuildingConstructiveElement, 18],
                        [FeatureType.Door, 5],
                        [FeatureType.Window, 11],
                        [FeatureType.Appearance, 2],
                        [FeatureType.ParameterizedTexture, 5],
                        [FeatureType.X3dMaterial, 9],
                    ] as const
                ).map(([type, count]) => [type.value, count]),
            ),
        );
        assert.equal(all(cityModel.iterCityObjects()).length, 37);
    });

    test('window building', () => {
        const b = building(cityModel);
        assert.equal(b.featureId().asStr(), WINDOW_ID);
        assert.deepEqual(
            all(b.names()).map((n) => n.value()),
            ['KIT FZK-Haus'],
        );
        assert.deepEqual(
            all(b.functions()).map((f) => f.value()),
            ['31001_1000'],
        );
        assert.equal(b.roofType()?.value(), '3100');
        assert.equal(all(b.boundaries()).length, 0);
        assertStoreys(cityModel, ['Entrance Floor', 'non Entrance Floor']);
    });

    test('window round trip', () => {
        assertRoundTrip(cityModel, WINDOW_ID);
    });
});

describe('06-FZK-Haus-LoD2-Tex-Storey-CG30-V01-PointCloud-thinned.gml', () => {
    const cityModel = read(DATASET, '06-FZK-Haus-LoD2-Tex-Storey-CG30-V01-PointCloud-thinned.gml');

    test('point cloud city model', () => {
        assertCityModel(cityModel, [458900.0, 5438785.0, 113.5], [458912.0, 5438795.0, 120.017691]);
        assert.deepEqual(featureTypes(cityModel), [
            FeatureType.CityModel,
            FeatureType.Building,
            FeatureType.Storey,
            GROUND,
            ...Array(4).fill(WALL),
            FeatureType.Storey,
            ROOF,
            ROOF,
            ...Array(4).fill(WALL),
        ]);
    });

    test('point cloud storey boundaries', () => {
        const b = building(cityModel);
        assert.equal(b.featureId().asStr(), TEST_BUILDING_ID);
        assert.equal(all(b.boundaries()).length, 0);
        const expected: [FeatureType, string][][] = [
            [
                [GROUND, ' Ground Floor / GroundSurface'],
                [WALL, 'Ground Floor / Wall East'],
                [WALL, 'Ground Floor / Wall South'],
                [WALL, 'Ground Floor / Wall West'],
                [WALL, 'Ground Floor / Wall North'],
            ],
            [
                [ROOF, 'Second Floor / Roof North'],
                [ROOF, 'Second Floor / Roof South'],
                [WALL, 'Second Floor / Wall South'],
                [WALL, 'Second Floor / Wall West'],
                [WALL, 'Second Floor / Wall East'],
                [WALL, 'Second Floor / Wall North'],
            ],
        ];
        const found = storeys(cityModel);
        assert.equal(found.length, expected.length);
        found.forEach((storey, i) => {
            const surfaces = boundarySurfaces(storey);
            assert.deepEqual(
                surfaces.map(([type, name]) => [type, name]),
                expected[i],
            );
            assert.ok(surfaces.every(([, , multiSurface]) => multiSurface === null));
        });
    });

    test('point cloud round trip', () => {
        assertRoundTrip(cityModel, TEST_BUILDING_ID);
    });
});
