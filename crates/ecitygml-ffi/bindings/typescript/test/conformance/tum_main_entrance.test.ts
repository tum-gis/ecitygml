// The cases of crates/ecitygml/tests/conformance/tum-main-entrance.md.
import assert from 'node:assert/strict';
import { describe, test } from 'node:test';

import {
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
    WallSurface,
} from '../../lib/index.mjs';
import { all, assertClose, boundaries, building, read } from './helpers.ts';

type Point = [number, number, number];

const { WallSurface: WALL, GroundSurface: GROUND, RoofSurface: ROOF } = FeatureType;
const BOUNDARY_TYPES = [...Array(10).fill(WALL), GROUND, ...Array(3).fill(WALL), ROOF, ROOF, WALL];

function assertPointClose(position: DirectPosition, expected: Point): void {
    [position.x(), position.y(), position.z()].forEach((value, i) => assertClose(value, expected[i]));
}

function featureTypes(cityModel: CityModel): FeatureType[] {
    return all(cityModel.iterFeatures()).map((f) => f.featureType());
}

/** The area of an inline LoD2 multi surface. */
function lod2Area(property: MultiSurfaceProperty | null): number {
    assert.ok(property);
    assert.equal(property.href(), null);
    const multiSurface = property.object();
    assert.ok(multiSurface);
    return multiSurface.area3d();
}

describe('TUM-Main-Entrance.gml', () => {
    const cityModel = read('tum-main-entrance', 'TUM-Main-Entrance.gml');

    test('entrance city model', () => {
        assert.equal(cityModel.cityObjectsLen(), 1);
        const envelope = cityModel.boundedBy()?.envelope();
        assert.ok(envelope);
        assertPointClose(envelope.lowerCorner(), [689975.68, 5335962.63, 503.0]);
        assertPointClose(envelope.upperCorner(), [692025.893, 5338012.713, 581.62]);
        assert.deepEqual(featureTypes(cityModel), [FeatureType.CityModel, FeatureType.Building, ...BOUNDARY_TYPES]);
        assert.equal(all(cityModel.iterCityObjects()).length, 18);
    });

    test('entrance building attributes', () => {
        const b = building(cityModel);
        assert.equal(b.featureId().asStr(), 'DEBY_LOD2_4959457');
        assert.equal(all(b.names()).length, 0);
        assert.equal(b.class_(), null);
        const functions = all(b.functions());
        assert.equal(functions.length, 1);
        assert.equal(functions[0].value(), '31001_3020');
        assert.equal(all(b.usages()).length, 0);
        assert.equal(b.roofType()?.value(), '1000');
        assert.equal(b.storeysAboveGround(), 4n);
        assert.equal(b.storeysBelowGround(), null);

        const heights = all(b.heights());
        assert.equal(heights.length, 1);
        assert.equal(heights[0].highReference().value(), 'topOfConstruction');
        assert.equal(heights[0].lowReference().value(), 'lowestGroundPoint');
        assert.equal(heights[0].status(), HeightStatusValue.Measured);
        assertClose(heights[0].length().value(), 19.408);
        assert.equal(heights[0].length().uom(), 'urn:adv:uom:m');

        const created = b.creationDate();
        assert.ok(created);
        assert.deepEqual([created.year(), created.month(), created.day()], [2025, 1, 2]);
        assert.deepEqual([created.hour(), created.minute()], [0, 0]);
        assert.equal(created.offsetSeconds(), 3600);
        assert.equal(b.boundedBy(), null);
        assert.equal(all(b.occupancies()).length, 0);
        assert.equal(all(b.buildingSubdivisions()).length, 0);
    });

    test('entrance external reference', () => {
        const references = all(building(cityModel).externalReferences());
        assert.equal(references.length, 1);
        assert.equal(references[0].targetResource(), 'DEBYvAAAAABTMIyA');
    });

    test('entrance external reference details', () => {
        const references = all(building(cityModel).externalReferences());
        assert.equal(references.length, 1);
        assert.equal(references[0].informationSystem(), 'http://repository.gdi-de.org/schemas/adv/citygml/fdv/art.htm#_9100');
        assert.equal(references[0].relationType(), null);
    });

    test('entrance generic attributes', () => {
        const attributes = all(building(cityModel).genericAttributes()).map((a) => {
            const string = a.asString();
            assert.ok(string);
            return [a.name(), string.value()];
        });
        assert.deepEqual(attributes, [
            ['DatenquelleBodenhoehe', '1100'],
            ['DatenquelleDachhoehe', '1000'],
            ['DatenquelleLage', '1000'],
            ['Gemeindeschluessel', '09162000'],
            ['HoeheDach', '534.450'],
            ['HoeheGrund', '515.042'],
            ['Methode', '2000'],
            ['NiedrigsteTraufeDesGebaeudes', '527.312'],
            ['Grundrissaktualitaet', '2025-02-17'],
            ['Geometrietyp2DReferenz', '3000'],
        ]);
    });

    test('entrance boundaries', () => {
        const b = building(cityModel);
        assert.ok(all(b.boundaries()).every((p) => p.href() === null));
        const features = boundaries(b);
        assert.deepEqual(
            features.map((f) => f.featureType()),
            BOUNDARY_TYPES,
        );

        const walls = features.map((f) => WallSurface.tryFrom(f)).filter((w) => w !== null);
        assert.equal(walls[0].featureId().asStr(), 'DEBY_LOD2_4959457_ca1db42f-9d12-4f41-972c-c7da1614f0a8_2');
        assert.equal(all(walls[0].names()).length, 0);
        assertClose(
            walls.reduce((sum, w) => sum + lod2Area(w.lod2MultiSurface()), 0),
            3783.3908922901974,
        );

        const roofs = features
            .map((f) => RoofSurface.tryFrom(f))
            .filter((r) => r !== null)
            .map((r) => lod2Area(r.lod2MultiSurface()));
        assert.equal(roofs.length, 2);
        assertClose(roofs[0], 250.233154296875);
        assertClose(roofs[1], 979.3291015625);
        assertClose(roofs[0] + roofs[1], 1229.562255859375);

        const grounds = features
            .map((f) => GroundSurface.tryFrom(f))
            .filter((g) => g !== null)
            .map((g) => lod2Area(g.lod2MultiSurface()));
        assert.equal(grounds.length, 1);
        assertClose(grounds[0], 1229.562255859375);
    });

    test('entrance wall triangulation', () => {
        const wall = all(cityModel.iterFeatures())
            .map((f) => WallSurface.tryFrom(f))
            .find((w) => w !== null);
        assert.ok(wall);
        const multiSurface = wall.lod2MultiSurface()?.object();
        assert.ok(multiSurface);
        assert.equal(all(multiSurface.surfaceMember()).length, 1);
        assertClose(multiSurface.area3d(), 546.6949745937537);
        const triangulation = multiSurface.triangulate();
        assert.equal(all(triangulation.surface().triangles()).length, 4);
        assert.ok(!triangulation.hasSkipped());
        assertClose(triangulation.surface().area3d(), 546.6949742237184);
    });

    test('entrance solid unresolved', () => {
        const property = building(cityModel).lod2Solid();
        assert.ok(property);
        assert.equal(property.href(), null);
        const solid = property.object();
        assert.ok(solid);
        const shell = solid.exterior();
        assert.ok(shell);
        const members = all(shell.members());
        assert.equal(members.length, 17);
        assert.ok(members.every((member) => member.object() === null));
        assert.throws(() => solid.volume3d());
    });

    test('entrance round trip', () => {
        const writer = new GmlWriter(CitygmlFormat.Gml);
        writer.finish(cityModel);
        const written = new GmlReader(writer.data(), CitygmlFormat.Gml).finish();
        assert.deepEqual(featureTypes(written), featureTypes(cityModel));
        assert.equal(building(written).featureId().asStr(), 'DEBY_LOD2_4959457');
        const boundaryIds = (model: CityModel) =>
            all(building(model).boundaries()).map((p) => p.object()!.featureId().asStr());
        assert.deepEqual(boundaryIds(written), boundaryIds(cityModel));
    });
});
