// The cases of crates/ecitygml/tests/conformance/fzk-haus.md.
import assert from 'node:assert/strict';
import { describe, test } from 'node:test';

import {
    CityModel,
    CitygmlFormat,
    CompositeSurface,
    DirectPosition,
    DoorSurface,
    FeatureType,
    GmlReader,
    GmlWriter,
    GroundSurface,
    HeightStatusValue,
    LinearRing,
    MeasureAttribute,
    Polygon,
    RelativeToTerrain,
    RoofSurface,
    WallSurface,
    WindowSurface,
} from '../../lib/index.mjs';
import { fixtureBytes } from '../helpers.ts';
import { all, assertClose, boundaries, building, firstName, read } from './helpers.ts';

const LOD1 = 'FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml';
const LOD2 = 'FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml';
const LOD3 = 'FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml';

type Point = [number, number, number];

function point(position: DirectPosition): Point {
    return [position.x(), position.y(), position.z()];
}

function assertPointClose(actual: Point, expected: Point): void {
    actual.forEach((value, i) => assertClose(value, expected[i]));
}

function walls(cityModel: CityModel): WallSurface[] {
    return all(cityModel.iterFeatures()).map((f) => WallSurface.tryFrom(f)).filter((w) => w !== null);
}

function wallsBounded(cityModel: CityModel): boolean[] {
    return walls(cityModel).map((w) => w.boundedBy() !== null);
}

/** The lower corners of the city model's envelope and of the first wall surface's. */
function lowerCorners(cityModel: CityModel): Point[] {
    const model = cityModel.boundedBy()?.envelope();
    const wall = walls(cityModel)[0].boundedBy()?.envelope();
    assert.ok(model && wall);
    return [point(model.lowerCorner()), point(wall.lowerCorner())];
}

describe('lod1', () => {
    const cityModel = read('fzk-haus', LOD1);

    test('lod1 city model', () => {
        assert.equal(cityModel.cityObjectsLen(), 1);
        const envelope = cityModel.boundedBy()?.envelope();
        assert.ok(envelope);
        const [lower, upper] = [envelope.lowerCorner(), envelope.upperCorner()];
        const corners: [number, number][] = [
            [lower.x(), 457842.0], [lower.y(), 5439083.0], [lower.z(), 111.8],
            [upper.x(), 457854.0], [upper.y(), 5439093.0], [upper.z(), 118.317669],
        ];
        for (const [actual, expected] of corners) {
            assertClose(actual, expected);
        }
    });

    test('lod1 building attributes', () => {
        const b = building(cityModel);
        assert.equal(b.featureId().asStr(), 'UUID_d281adfc-4901-0f52-540b-4cc1a9325f82');
        assert.deepEqual(all(b.names()).map((n) => n.value()), ['AC14-FZK-Haus']);
        assert.equal(b.class_()?.value(), '1000');
        assert.deepEqual(all(b.functions()).map((f) => f.value()), ['1000']);
        assert.deepEqual(all(b.usages()).map((u) => u.value()), ['1000']);
        assert.equal(b.roofType()?.value(), '1030');
        // 64-bit integers are BigInts in JavaScript.
        assert.equal(b.storeysAboveGround(), 2n);
        assert.equal(b.storeysBelowGround(), 0n);

        const date = b.dateOfConstruction();
        assert.deepEqual([date?.year(), date?.month(), date?.day()], [2020, 1, 1]);
        assert.equal(b.dateOfDemolition(), null);
        const heights = all(b.heights());
        assert.equal(heights.length, 1);
        assert.equal(heights[0].highReference().value(), 'topOfConstruction');
        assert.equal(heights[0].lowReference().value(), 'lowestGroundPoint');
        assert.equal(heights[0].status(), HeightStatusValue.Measured);
        assertClose(heights[0].length().value(), 6.52);
        assert.equal(heights[0].length().uom(), 'm');
        assert.equal(all(b.occupancies()).length, 0);
        assert.equal(all(b.buildingParts()).length, 0);
    });

    test('lod1 solid', () => {
        const b = building(cityModel);
        const solid = b.lod1Solid()?.object();
        assert.ok(solid);
        assertClose(solid.volume3d(), 782.1228);
        const triangulation = solid.triangulate();
        assert.equal(all(triangulation.surface().triangles()).length, 12);
        // Plain bool returns are 0/1 in the JavaScript bindings.
        assert.ok(!triangulation.hasSkipped());
        assert.equal(all(b.boundaries()).length, 0);
    });

    test('lod1 envelope measures', () => {
        const envelope = cityModel.boundedBy()?.envelope();
        assert.ok(envelope);
        assertPointClose([envelope.sizeX(), envelope.sizeY(), envelope.sizeZ()], [12.0, 10.0, 6.517669]);
        assertPointClose(point(envelope.center()), [457848.0, 5439088.0, 115.0588345]);
        assertClose(envelope.volume(), 782.12028);
        assert.ok(envelope.contains(envelope.lowerCorner()));
        assert.ok(envelope.contains(envelope.upperCorner()));
        assert.ok(envelope.contains(new DirectPosition(457848.0, 5439088.0, 115.0)));
        assert.ok(!envelope.contains(new DirectPosition(457848.0, 5439088.0, 118.4)));
        assert.ok(!envelope.contains(new DirectPosition(457841.9, 5439088.0, 115.0)));
        assert.equal(cityModel.creationDate(), null);
    });

    test('lod1 building details', () => {
        const buildings = all(cityModel.iterFeatures()).filter((f) => f.featureType() === FeatureType.Building);
        assert.equal(buildings.length, 1);
        const b = building(cityModel);
        assert.equal(b.id()?.asStr(), 'UUID_d281adfc-4901-0f52-540b-4cc1a9325f82');
        const envelope = b.boundedBy()?.envelope();
        assert.ok(envelope);
        assertPointClose(point(envelope.lowerCorner()), [457842.0, 5439083.0, 111.8]);
        assertPointClose(point(envelope.upperCorner()), [457854.0, 5439093.0, 118.31769]);
        assert.equal(b.lod2Solid(), null);
        assert.equal(b.lod0MultiSurface(), null);
    });

    test('lod1 solid structure', () => {
        const solid = building(cityModel).lod1Solid()?.object();
        assert.ok(solid);
        assert.equal(all(solid.interior()).length, 0);
        assert.equal(all(solid.points()).length, 24);
        const shell = solid.exterior();
        assert.ok(shell);
        assertClose(shell.volume3d(), 782.1228);
        const members = all(shell.members());
        assert.equal(members.length, 6);
        const rings = members.map((member) => {
            assert.equal(member.href(), null);
            const surface = member.object();
            assert.ok(surface);
            const polygon = Polygon.tryFrom(surface);
            assert.ok(polygon);
            assert.equal(all(polygon.interior()).length, 0);
            const exterior = polygon.exterior();
            assert.ok(exterior);
            const ring = LinearRing.tryFrom(exterior);
            assert.ok(ring);
            return ring;
        });
        for (const ring of rings) {
            assert.equal(all(ring.points()).length, 4);
            assert.ok(ring.area3d() > 0.0);
        }
        assertPointClose(point(all(rings[0].points())[0]), [457842.0, 5439083.0, 111.8]);
        assertClose(rings[0].length3d(), 44.0);
        assertClose(rings[0].area3d(), 120.0);
    });

    test('lod1 solid triangulation', () => {
        const solid = building(cityModel).lod1Solid()?.object();
        assert.ok(solid);
        const triangulation = solid.triangulate();
        assert.equal(all(triangulation.skipped()).length, 0);
        const surface = triangulation.surface();
        assertClose(surface.area3d(), 526.77836);
        assert.equal(all(surface.points()).length, 36);
        const triangle = all(surface.triangles())[0];
        assertClose(triangle.a().z(), 111.8);
        assertClose(triangle.area(), 60.0);
        const shell = solid.exterior();
        assert.ok(shell);
        assert.equal(all(shell.triangulate().surface().triangles()).length, 12);
        const surfaceKind = all(shell.members())[0].object();
        assert.ok(surfaceKind);
        const first = Polygon.tryFrom(surfaceKind);
        assert.ok(first);
        assert.equal(all(first.triangulate().surface().triangles()).length, 2);
    });

    test('lod1 apply scale', () => {
        const scaled = read('fzk-haus', LOD1);
        scaled.applyScale({ x: 2.0, y: 3.0, z: 0.5 });
        const envelope = scaled.boundedBy()?.envelope();
        assert.ok(envelope);
        assertPointClose([envelope.sizeX(), envelope.sizeY(), envelope.sizeZ()], [24.0, 30.0, 3.2588345]);
    });
});

describe('lod2', () => {
    const cityModel = read('fzk-haus', LOD2);

    test('lod2 boundary surfaces', () => {
        const features = boundaries(building(cityModel));
        assert.deepEqual(features.map((f) => f.featureType()), [
            FeatureType.WallSurface,
            FeatureType.WallSurface,
            FeatureType.WallSurface,
            FeatureType.RoofSurface,
            FeatureType.WallSurface,
            FeatureType.RoofSurface,
            FeatureType.GroundSurface,
        ]);
        const walls = features.map((f) => WallSurface.tryFrom(f)).filter((s) => s !== null);
        const roofs = features.map((f) => RoofSurface.tryFrom(f)).filter((s) => s !== null);
        const grounds = features.map((f) => GroundSurface.tryFrom(f)).filter((s) => s !== null);
        assert.deepEqual(walls.map((s) => firstName(s)), [
            'Outer Wall 1 (West)',
            'Outer Wall 2 (South)',
            'Outer Wall 3 (East)',
            'Outer Wall 4 (North)',
        ]);
        assert.deepEqual(roofs.map((s) => firstName(s)), ['Roof 1 (North)', 'Roof 2 (South)']);
        assert.deepEqual(grounds.map((s) => firstName(s)), ['Base Surface']);
    });

    test('lod2 surface areas', () => {
        const features = boundaries(building(cityModel));
        const area = (surfaces: ({ lod2MultiSurface(): { object(): { area3d(): number } | null } | null } | null)[]) =>
            surfaces
                .filter((s) => s !== null)
                .reduce((sum, s) => sum + (s.lod2MultiSurface()?.object()?.area3d() ?? Number.NaN), 0);
        assertClose(area(features.map((f) => WallSurface.tryFrom(f))), 188.62887820601463);
        assertClose(area(features.map((f) => RoofSurface.tryFrom(f))), 138.56406460961398);
        assertClose(area(features.map((f) => GroundSurface.tryFrom(f))), 120.0);
    });

    test('lod2 generic attributes', () => {
        const b = building(cityModel);
        const attributes = all(b.genericAttributes());
        assert.equal(attributes.length, 3);
        const [area, method, landmarked] = attributes;
        const measure = MeasureAttribute.tryFrom(area);
        assert.ok(measure);
        assert.equal(area.name(), 'GrossPlannedArea');
        assertClose(measure.value().value(), 120.0);
        assert.equal(measure.value().uom(), 'm2');
        assert.deepEqual([method.name(), method.asString()?.value()], ['ConstructionMethod', 'New Building']);
        assert.deepEqual([landmarked.name(), landmarked.asString()?.value()], ['IsLandmarked', 'NO']);
        assert.equal(all(b.externalReferences()).length, 0);
    });

    test('lod2 solid unresolved', () => {
        const solid = building(cityModel).lod2Solid()?.object();
        assert.ok(solid);
        assert.throws(() => solid.volume3d());
    });

    test('lod2 building details', () => {
        const b = building(cityModel);
        assert.equal(b.relativeToTerrain(), RelativeToTerrain.EntirelyAboveTerrain);
        assert.equal(b.relativeToWater(), null);
        const created = b.creationDate();
        assert.ok(created);
        assert.deepEqual([created.year(), created.month(), created.day(), created.hour()], [2017, 1, 23, 0]);
        assert.equal(created.offsetSeconds(), 3600);
        assert.equal(created.timestamp(), 1485126000n);
        assert.equal(b.terminationDate(), null);
        assert.equal(b.validFrom(), null);
        assert.equal(b.validTo(), null);

        assert.equal(b.class_()?.value(), '1000');
        assert.deepEqual(all(b.functions()).map((f) => f.value()), ['1000']);
        assert.deepEqual(all(b.usages()).map((u) => u.value()), ['1000']);
        assert.equal(b.roofType()?.value(), '1030');
        assert.deepEqual([b.storeysAboveGround(), b.storeysBelowGround()], [2n, 0n]);
        const date = b.dateOfConstruction();
        assert.deepEqual([date?.year(), date?.month(), date?.day()], [2020, 1, 1]);
        assert.equal(b.dateOfDemolition(), null);
        const heights = all(b.heights());
        assert.equal(heights.length, 1);
        assert.equal(heights[0].highReference().value(), 'topOfConstruction');
        assert.equal(heights[0].lowReference().value(), 'lowestGroundPoint');
        assert.equal(heights[0].status(), HeightStatusValue.Measured);
        assertClose(heights[0].length().value(), 6.52);
        assert.equal(heights[0].length().uom(), 'm');

        assert.equal(all(b.occupancies()).length, 0);
        assert.equal(all(b.relatedTo()).length, 0);
        assert.equal(b.lod1Solid(), null);
        assert.equal(b.boundedBy(), null);
        assert.equal(b.lod1TerrainIntersectionCurve(), null);
        assert.equal(b.lod2TerrainIntersectionCurve(), null);
        assert.equal(b.lod3TerrainIntersectionCurve(), null);
        assert.equal(b.lod1ImplicitRepresentation(), null);
        assert.equal(b.lod2ImplicitRepresentation(), null);
        assert.equal(b.lod3ImplicitRepresentation(), null);
    });

    test('lod2 boundary ids', () => {
        const properties = all(building(cityModel).boundaries());
        assert.ok(properties.every((p) => p.href() === null));
        assert.deepEqual(properties.map((p) => p.object()?.featureId().asStr()), [
            'GML_5856d7ad-5e34-498a-817b-9544bfbb1475',
            'GML_d38cf762-c29d-4491-88c9-bdc89e141978',
            'GML_8e5db638-e46a-4739-a98a-2fc2d39c9069',
            'GML_875d470b-32b4-4985-a4c8-0f02caa342a2',
            'GML_0f30f604-e70d-4dfe-ba35-853bc69609cc',
            'GML_eeb6796a-e261-4d3b-a6f2-475940cca80a',
            'GML_257a8dde-8194-4ca3-b581-abd591dcd6a3',
        ]);
    });

    test('lod2 wall surface', () => {
        const features = boundaries(building(cityModel));
        const wallSurfaces = features.map((f) => WallSurface.tryFrom(f)).filter((w) => w !== null);
        const wall = wallSurfaces[0];
        assert.equal(wall.id()?.asStr(), 'GML_5856d7ad-5e34-498a-817b-9544bfbb1475');
        assert.equal(wall.lod0MultiCurve(), null);
        assert.equal(wall.lod0MultiSurface(), null);
        assert.equal(wall.lod1MultiSurface(), null);
        assert.equal(wall.relativeToTerrain(), null);
        assert.equal(wall.creationDate(), null);
        assert.equal(all(wall.genericAttributes()).length, 0);
        assert.notEqual(wall.boundedBy(), null);
        const multiSurface = wall.lod2MultiSurface()?.object();
        assert.ok(multiSurface);
        assert.equal(all(multiSurface.surfaceMember()).length, 1);
        assert.equal(all(multiSurface.triangulate().surface().triangles()).length, 3);
        assert.ok(wallSurfaces.every((w) => all(w.fillingSurfaces()).length === 0));
        const ground = features.map((f) => GroundSurface.tryFrom(f)).find((g) => g !== null);
        const member = ground?.lod2MultiSurface()?.object()?.surfaceMember().next();
        assert.ok(member && !member.done);
        const surface = member.value.object();
        assert.ok(surface);
        const exterior = Polygon.tryFrom(surface)?.exterior();
        assert.ok(exterior);
        assert.equal(all(exterior.points()).length, 4);
    });

    test('lod2 generic attribute kinds', () => {
        const [area, method, landmarked] = all(building(cityModel).genericAttributes());
        assert.equal(area.asString(), null);
        assert.equal(MeasureAttribute.tryFrom(method), null);
        assert.equal(MeasureAttribute.tryFrom(landmarked), null);
    });

    test('lod2 city objects', () => {
        assert.deepEqual(all(cityModel.iterCityObjects()).map((o) => o.featureType()), [
            FeatureType.Building,
            FeatureType.WallSurface,
            FeatureType.WallSurface,
            FeatureType.WallSurface,
            FeatureType.RoofSurface,
            FeatureType.WallSurface,
            FeatureType.RoofSurface,
            FeatureType.GroundSurface,
        ]);
        const types = all(cityModel.iterFeatures()).map((f) => f.featureType());
        assert.equal(types[0], FeatureType.CityModel);
        assert.equal(types.filter((t) => t === FeatureType.CityModel).length, 1);
    });

    test('lod2 object bounds', () => {
        const reader = new GmlReader(fixtureBytes(`fzk-haus/${LOD2}`) as unknown as number[], CitygmlFormat.Gml);
        reader.withRebuildObjectBounds(false);
        const unbounded = reader.finish();
        assert.deepEqual(wallsBounded(unbounded), [false, false, false, false]);
        unbounded.recomputeChildBoundingShapes();
        assert.deepEqual(wallsBounded(unbounded), [true, true, true, true]);
    });

    test('lod2 apply translation', () => {
        const translated = read('fzk-haus', LOD2);
        for (const corner of lowerCorners(translated)) {
            assertPointClose(corner, [457842.0, 5439083.0, 111.8]);
        }
        translated.applyTranslation({ x: -100.0, y: 200.0, z: 10.0 });
        for (const corner of lowerCorners(translated)) {
            assertPointClose(corner, [457742.0, 5439283.0, 121.8]);
        }
    });
});

describe('lod3', () => {
    const cityModel = read('fzk-haus', LOD3);

    test('lod3 doors and windows', () => {
        const features = all(cityModel.iterFeatures());
        const doors = features.map((f) => DoorSurface.tryFrom(f)).filter((d) => d !== null);
        assert.deepEqual(doors.map((d) => firstName(d)), ['Door West', 'Door South']);
        const area = doors.reduce((sum, d) => sum + (d.lod3MultiSurface()?.object()?.area3d() ?? Number.NaN), 0);
        assertClose(area, 6.803850099444389);
        assert.equal(features.filter((f) => WindowSurface.tryFrom(f) !== null).length, 11);
    });

    test('lod3 west wall fillings', () => {
        const wall = WallSurface.tryFrom(boundaries(building(cityModel))[0]);
        assert.ok(wall);
        assert.equal(firstName(wall), 'Outer Wall 1 (West)');
        const fillings = all(wall.fillingSurfaces()).map((p) => p.object());
        assert.deepEqual(
            fillings.map((f) => (f ? [f.featureType(), firstName(f)] : null)),
            [
                [FeatureType.WindowSurface, 'Window Round'],
                [FeatureType.WindowSurface, 'Window North'],
                [FeatureType.DoorSurface, 'Door West'],
                [FeatureType.WindowSurface, 'Window South'],
            ],
        );
    });

    test('lod3 building details', () => {
        assert.equal(cityModel.cityObjectsLen(), 1);
        const b = building(cityModel);
        assert.equal(b.relativeToTerrain(), RelativeToTerrain.EntirelyAboveTerrain);
        const features = boundaries(b);
        assert.deepEqual(features.map((f) => f.featureType()), [
            FeatureType.WallSurface,
            FeatureType.WallSurface,
            FeatureType.WallSurface,
            FeatureType.RoofSurface,
            FeatureType.WallSurface,
            FeatureType.RoofSurface,
            FeatureType.GroundSurface,
        ]);
        const wallSurfaces = features.map((f) => WallSurface.tryFrom(f)).filter((w) => w !== null);
        assert.ok(wallSurfaces.every((w) => w.lod3MultiSurface() !== null));
    });

    test('lod3 fillings', () => {
        const features = boundaries(building(cityModel));
        const wallSurfaces = features.map((f) => WallSurface.tryFrom(f)).filter((w) => w !== null);
        const perWall = wallSurfaces.map((w) => all(w.fillingSurfaces()));
        assert.deepEqual(perWall.map((p) => p.length), [4, 3, 3, 3]);
        const properties = perWall.flat();
        assert.ok(properties.every((p) => p.href() === null));
        const fillings = properties.map((p) => p.object()).filter((f) => f !== null);
        const types = fillings.map((f) => f.featureType());
        assert.deepEqual(
            [
                types.filter((t) => t === FeatureType.DoorSurface).length,
                types.filter((t) => t === FeatureType.WindowSurface).length,
            ],
            [2, 11],
        );
        assert.ok(fillings.every((f) => (f.lod3MultiSurface()?.object()?.area3d() ?? Number.NaN) > 0.0));
        const roofs = features.map((f) => RoofSurface.tryFrom(f)).filter((r) => r !== null);
        assert.ok(roofs.every((r) => all(r.fillingSurfaces()).length === 0));

        const allFeatures = all(cityModel.iterFeatures());
        const windows = allFeatures.map((f) => WindowSurface.tryFrom(f)).filter((w) => w !== null);
        const area = windows.reduce((sum, w) => sum + (w.lod3MultiSurface()?.object()?.area3d() ?? Number.NaN), 0);
        assertClose(area, 23.168802611529827);
        const doors = allFeatures.map((f) => DoorSurface.tryFrom(f)).filter((d) => d !== null);
        assert.deepEqual(doors.map((d) => d.featureId().asStr()), [
            'GML_c137f11d-9a8c-4126-9aeb-9a6c9b4e1cbd',
            'GML_2d6ddf04-ee56-42a1-a9b1-b47e4181a629',
        ]);
        assert.ok(doors.every((d) => d.lod2MultiSurface() === null));
    });

    test('lod3 city objects', () => {
        const objects = all(cityModel.iterCityObjects()).map((o) => o.featureType());
        assert.equal(objects.length, 21);
        const count = (type: FeatureType) => objects.filter((t) => t === type).length;
        assert.deepEqual(
            [
                count(FeatureType.Building),
                count(FeatureType.WallSurface),
                count(FeatureType.RoofSurface),
                count(FeatureType.GroundSurface),
                count(FeatureType.DoorSurface),
                count(FeatureType.WindowSurface),
            ],
            [1, 4, 2, 1, 2, 11],
        );
        const types = all(cityModel.iterFeatures()).map((f) => f.featureType());
        assert.equal(types.length, 22);
        assert.equal(types[0], FeatureType.CityModel);
    });

    test('lod3 composite surface', () => {
        const wall = WallSurface.tryFrom(boundaries(building(cityModel))[0]);
        const member = wall?.lod3MultiSurface()?.object()?.surfaceMember().next();
        assert.ok(member && !member.done);
        const surface = member.value.object();
        assert.ok(surface);
        const composite = CompositeSurface.tryFrom(surface);
        assert.ok(composite);
        const members = all(composite.surfaceMember());
        assert.equal(members.length, 85);
        const first = members[0].object();
        assert.ok(first);
        const exterior = Polygon.tryFrom(first)?.exterior();
        assert.ok(exterior);
        assertPointClose(point(all(exterior.points())[0]), [457842.0, 5439088.49240388, 115.913175911167]);
    });

    test('lod3 round trip', () => {
        const writer = new GmlWriter(CitygmlFormat.Gml);
        writer.finish(cityModel);
        const written = new GmlReader(writer.data(), CitygmlFormat.Gml).finish();
        const types = (model: CityModel) => all(model.iterFeatures()).map((f) => f.featureType());
        assert.deepEqual(types(written), types(cityModel));
        assert.equal(building(written).featureId().asStr(), 'UUID_d281adfc-4901-0f52-540b-4cc1a9325f82');
        // The `feature_id`s of the building's boundaries, then of the wall surfaces' filling surfaces.
        const surfaceIds = (model: CityModel) => [
            ...all(building(model).boundaries()).map((p) => p.object()!.featureId().asStr()),
            ...boundaries(building(model))
                .map((b) => WallSurface.tryFrom(b))
                .filter((w) => w != null)
                .flatMap((w) => all(w.fillingSurfaces()).map((p) => p.object()!.featureId().asStr())),
        ];
        assert.deepEqual(surfaceIds(written), surfaceIds(cityModel));
        const heights = all(building(written).heights());
        assert.equal(heights.length, 1);
        assert.equal(heights[0].highReference().value(), 'topOfConstruction');
        assert.equal(heights[0].lowReference().value(), 'lowestGroundPoint');
        assert.equal(heights[0].status(), HeightStatusValue.Measured);
        assertClose(heights[0].length().value(), 6.52);
        assert.equal(heights[0].length().uom(), 'm');
    });
});
