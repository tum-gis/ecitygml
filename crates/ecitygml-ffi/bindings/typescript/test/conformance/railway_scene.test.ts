// The cases of crates/ecitygml/tests/conformance/railway-scene.md.
import assert from 'node:assert/strict';
import { describe, test } from 'node:test';

import {
    AbstractFeatureKindRef,
    Bridge,
    Building,
    CityFurniture,
    CityModel,
    CitygmlFormat,
    FeatureType,
    GmlReader,
    GmlWriter,
    ImplicitGeometry,
    LevelOfDetail,
    MultiSurface,
    RelativeToTerrain,
    ReliefFeature,
    SolitaryVegetationObject,
    TinRelief,
    Tunnel,
} from '../../lib/index.mjs';
import { all, assertClose, firstName, read } from './helpers.ts';

const TEMPLATE_A = '#Mult_SO043561_5693_194007';
const TEMPLATE_B = '#Mult_SO045475_3243_790864';
const INLINE_TEMPLATES = new Set(['Forest tree 3', 'Tree1', 'Forest tree 1']);
const TEMPLATE_A_TREES = new Set(['Forest tree 4', 'Forest tree 9', 'Forest tree 5']);

const { WallSurface: WALL, RoofSurface: ROOF, GroundSurface: GROUND, ClosureSurface: CLOSURE } = FeatureType;

function featureTypes(cityModel: CityModel): FeatureType[] {
    return all(cityModel.iterFeatures()).map((f) => f.featureType());
}

/** All features a class accepts, in document order. */
function allOf<T>(cityModel: CityModel, cls: { tryFrom(feature: AbstractFeatureKindRef): T | null }): T[] {
    return all(cityModel.iterFeatures())
        .map((f) => cls.tryFrom(f))
        .filter((x): x is T => x !== null);
}

/** A tree's inline LoD3 implicit geometry. */
function implicitGeometry(tree: SolitaryVegetationObject): ImplicitGeometry {
    const property = tree.lod3ImplicitRepresentation();
    assert.ok(property);
    assert.equal(property.href(), null);
    const geometry = property.object();
    assert.ok(geometry);
    return geometry;
}

function templateHref(tree: SolitaryVegetationObject): string | null {
    return implicitGeometry(tree).relativeGeometry()?.href()?.toString() ?? null;
}

describe('Railway_Scene_LoD3__v3-thinned.gml', () => {
    const cityModel = read('railway-scene', 'Railway_Scene_LoD3__v3-thinned.gml');

    test('railway city model', () => {
        assert.equal(cityModel.cityObjectsLen(), 52);
        assert.equal(cityModel.boundedBy(), null);
        const types = featureTypes(cityModel);
        assert.equal(types.length, 232);
        assert.equal(types[0], FeatureType.CityModel);
        const counts = new Map<string, number>();
        for (const type of types) counts.set(type.value, (counts.get(type.value) ?? 0) + 1);
        const expected: [FeatureType, number][] = [
            [FeatureType.CityModel, 1],
            [FeatureType.SolitaryVegetationObject, 15],
            [FeatureType.Tunnel, 4],
            [FeatureType.TunnelInstallation, 8],
            [FeatureType.Railway, 10],
            [FeatureType.Bridge, 4],
            [FeatureType.BridgeConstructiveElement, 3],
            [FeatureType.BridgeInstallation, 2],
            [FeatureType.Building, 3],
            [FeatureType.BuildingInstallation, 56],
            [FeatureType.CityFurniture, 11],
            [FeatureType.CityObjectGroup, 1],
            [FeatureType.GenericOccupiedSpace, 2],
            [FeatureType.WaterBody, 1],
            [FeatureType.WaterSurface, 1],
            [FeatureType.WaterGroundSurface, 1],
            [FeatureType.ReliefFeature, 1],
            [FeatureType.TinRelief, 1],
            [WALL, 33],
            [ROOF, 12],
            [GROUND, 7],
            [CLOSURE, 8],
            [FeatureType.DoorSurface, 9],
            [FeatureType.WindowSurface, 34],
            [FeatureType.OuterCeilingSurface, 3],
            [FeatureType.OuterFloorSurface, 1],
        ];
        assert.deepEqual(counts, new Map(expected.map(([type, count]) => [type.value, count])));
        assert.equal(all(cityModel.iterCityObjects()).length, 231);
    });

    test('railway tunnels', () => {
        const expected: [string, string, FeatureType[]][] = [
            ['GMLID_BUI142242_863_347', 'Tunnel KIT/KHH-3', [GROUND, WALL, ROOF, WALL, CLOSURE, CLOSURE]],
            ['GMLID_BUI336993_213_9312', 'Tunnel KIT/KHH-2', [WALL, ROOF, WALL, CLOSURE, CLOSURE, GROUND]],
            ['GMLID_BUI289877_1911_4122', 'Tunnel KIT/KHH-4', [WALL, GROUND, CLOSURE, WALL, ROOF, CLOSURE]],
            ['GMLID_BUI180021_673_14143', 'Tunnel KIT/KHH-1', [GROUND, WALL, ROOF, CLOSURE, CLOSURE, WALL]],
        ];
        const tunnels = allOf(cityModel, Tunnel);
        assert.equal(tunnels.length, expected.length);
        tunnels.forEach((tunnel, i) => {
            const [id, name, boundaries] = expected[i];
            assert.equal(tunnel.featureId().asStr(), id);
            assert.equal(firstName(tunnel), name);
            const properties = all(tunnel.boundaries());
            assert.ok(properties.every((p) => p.href() === null));
            assert.deepEqual(
                properties.map((p) => p.object()?.featureType()),
                boundaries,
            );
            assert.equal(tunnel.class_(), null);
            assert.equal(all(tunnel.functions()).length, 0);
            assert.equal(all(tunnel.usages()).length, 0);
            assert.equal(all(tunnel.tunnelParts()).length, 0);
            const created = tunnel.creationDate();
            assert.ok(created);
            assert.deepEqual([created.year(), created.month(), created.day()], [2015, 3, 6]);
            assert.deepEqual([created.hour(), created.minute()], [0, 0]);
            assert.equal(created.offsetSeconds(), 3600);
            assert.equal(tunnel.relativeToTerrain(), RelativeToTerrain.EntirelyAboveTerrain);
        });
    });

    test('railway trees', () => {
        const expected: [string, string, string | null, string, string[]][] = [
            ['GMLID_SO0158953_776_12462', 'Forest tree 3', '1070', '1800', []],
            ['GMLID_SO092422_3593_9527', 'Tree1', null, '9999', ['LOD3']],
            ['GMLID_SO0200811_525_4986', 'Forest tree 1', '1060', '1640', []],
            ['GMLID_SO0321978_1466_7441', 'Forest tree 4', '1070', '1800', []],
            ['GMLID_SO0260143_1214_1315', 'Forest tree 11', '1060', '1640', []],
            ['GMLID_SO0400934_2926_3381', 'Forest tree 12', '1060', '1640', []],
            ['GMLID_SO0124800_3522_13577', 'Forest tree 13', '1060', '1640', []],
            ['GMLID_SO0443764_1492_9667', 'Forest tree 14', '1060', '1640', []],
            ['GMLID_SO015374_872_14131', 'Forest tree 2', '1060', '1640', []],
            ['GMLID_SO081792_2341_11961', 'Forest tree 10', '1060', '1640', []],
            ['GMLID_SO0283142_1335_8999', 'Forest tree 7', '1060', '1640', []],
            ['GMLID_SO0107241_3793_12555', 'Forest tree 9', '1070', '1800', []],
            ['GMLID_SO0286258_965_2893', 'Forest tree 5', '1070', '1800', []],
            ['GMLID_SO0410128_214_10515', 'Forest tree 6', '1060', '1640', []],
            ['GMLID_SO086970_1053_8814', 'Forest tree 8', '1060', '1640', []],
        ];
        const trees = allOf(cityModel, SolitaryVegetationObject);
        assert.equal(trees.length, expected.length);
        trees.forEach((tree, i) => {
            const [id, name, class_, species, functions] = expected[i];
            assert.equal(tree.featureId().asStr(), id);
            assert.equal(firstName(tree), name);
            assert.equal(tree.class_()?.value() ?? null, class_);
            assert.equal(tree.species()?.value(), species);
            assert.deepEqual(
                all(tree.functions()).map((f) => f.value()),
                functions,
            );
            assert.equal(all(tree.usages()).length, 0);
            assert.equal(tree.lod1ImplicitRepresentation(), null);
            assert.equal(tree.lod2ImplicitRepresentation(), null);
        });
    });

    test('railway tree templates', () => {
        for (const tree of allOf(cityModel, SolitaryVegetationObject)) {
            const geometry = implicitGeometry(tree);
            assert.equal(geometry.mimeType(), null);
            const matrix = geometry.transformationMatrix();
            [30.0, 30.0, 30.0, 1.0].forEach((value, i) => assertClose(matrix.get(i, i), value));
            const name = firstName(tree);
            const property = geometry.relativeGeometry();
            assert.ok(property);
            if (INLINE_TEMPLATES.has(name)) {
                assert.equal(property.href(), null);
                const object = property.object();
                assert.ok(object);
                const multiSurface = MultiSurface.tryFrom(object);
                assert.ok(multiSurface, name);
                assert.equal(all(multiSurface.surfaceMember()).length, 1);
            } else {
                assert.equal(property.object(), null);
                assert.equal(templateHref(tree), TEMPLATE_A_TREES.has(name) ? TEMPLATE_A : TEMPLATE_B, name);
            }
        }
    });

    test('railway tree placement', () => {
        for (const tree of allOf(cityModel, SolitaryVegetationObject)) {
            const geometry = implicitGeometry(tree);
            const point = geometry.referencePoint().object();
            assert.ok(point);
            const pos = point.pos();
            const matrix = geometry.transformationMatrix();
            const translation = [matrix.get(0, 3), matrix.get(1, 3), matrix.get(2, 3)];
            const name = firstName(tree);
            const reference =
                name === 'Tree1' ? [-568.8000793496976, 457.60044759869743, 105.00139681350242] : [-600.0, 400.0, -150.0];
            [pos.x(), pos.y(), pos.z()].forEach((value, i) => assertClose(value, reference[i]));
            const expected =
                name === 'Tree1'
                    ? [0.0, 0.0, 0.0]
                    : name === 'Forest tree 3'
                      ? [39.4421005419207, 220.3838834926932, 268.5013679006178]
                      : null;
            if (expected !== null) translation.forEach((value, i) => assertClose(value, expected[i]));
        }
    });

    test('railway furniture', () => {
        const expected: [string, string][] = [
            ['GMLID_7431654_78949_792', '1090'],
            ['GMLID_0528986_170479_94', 'OTHERS'],
            ['GMLID_4323540_367099_910', '1090'],
            ['GMLID_1381455_184173_656', 'OTHERS'],
            ['GMLID_1429491_351612_1485', '1090'],
            ['GMLID_5361967_192822_672', '1090'],
            ['GMLID_2108434_31807_876', '1090'],
            ['GMLID_0373494_301709_129', '1540'],
            ['GMLID_6162422_289094_1279', '1090'],
            ['GMLID_3313190_307178_612', '1090'],
            ['GMLID_855011_330784_753', '1540'],
        ];
        const furniture = allOf(cityModel, CityFurniture);
        assert.deepEqual(
            furniture.map((f) => [f.featureId().asStr(), all(f.functions()).map((x) => x.value())]),
            expected.map(([id, function_]) => [id, [function_]]),
        );
        for (const item of furniture) {
            assert.equal(item.class_(), null);
            assert.equal(all(item.usages()).length, 0);
            assert.equal(item.lod3ImplicitRepresentation(), null);
            const property = item.lod3MultiSurface();
            assert.ok(property);
            assert.equal(property.href(), null);
            const multiSurface = property.object();
            assert.ok(multiSurface);
            assert.equal(all(multiSurface.surfaceMember()).length, 1);
        }
    });

    test('railway relief', () => {
        const reliefs = allOf(cityModel, ReliefFeature);
        assert.equal(reliefs.length, 1);
        const relief = reliefs[0];
        assert.equal(relief.featureId().asStr(), 'GMLID_TIN436865_187531_1154');
        assert.equal(all(relief.names()).length, 0);
        assert.equal(relief.lod(), LevelOfDetail.Three);
        const components = all(relief.reliefComponents());
        assert.equal(components.length, 1);
        assert.equal(components[0].href(), null);
        assert.equal(components[0].object()?.featureType(), FeatureType.TinRelief);

        const tinReliefs = allOf(cityModel, TinRelief);
        assert.equal(tinReliefs.length, 1);
        const tinRelief = tinReliefs[0];
        assert.equal(tinRelief.featureId().asStr(), 'UUID_5aa70b07-6bbf-427b-8222-d72ed77dbfa9');
        assert.equal(tinRelief.lod(), LevelOfDetail.Three);
        const tin = tinRelief.tin();
        assert.ok(tin);
        assert.equal(tin.href(), null);
        const surface = tin.object();
        assert.ok(surface);
        assert.equal(all(surface.triangles()).length, 1);
        assertClose(surface.area3d(), 3.2750424144626247);
    });

    test('railway buildings and bridges', () => {
        assert.deepEqual(
            allOf(cityModel, Building).map((b) => [b.featureId().asStr(), firstName(b), all(b.boundaries()).length]),
            [
                ['GMLID_BUI184698_512_898', 'Station KIT/KHH-1', 13],
                ['GMLID_BUI46739_1739_10911', 'Chapel KIT/KHH-1', 19],
                ['GMLID_BUI130363_1235_6047', 'Boatshouse KIT/KHH-1', 8],
            ],
        );
        assert.deepEqual(
            allOf(cityModel, Bridge).map((b) => [b.featureId().asStr(), firstName(b)]),
            [
                ['GMLID_BUI205585_1385_1373', 'Bridge KIT 4'],
                ['GMLID_BUI51891_765_738', 'Bridge KIT 3'],
                ['GMLID_BUI100628_817_8083', 'Bridge KIT 2'],
                ['GMLID_BUI30683_572_6686', 'Bridge KIT 1'],
            ],
        );
    });

    test('railway round trip', () => {
        const writer = new GmlWriter(CitygmlFormat.Gml);
        writer.finish(cityModel);
        const written = new GmlReader(writer.data(), CitygmlFormat.Gml).finish();
        assert.deepEqual(featureTypes(written), featureTypes(cityModel));
        const ids = (model: CityModel) =>
            [
                ...allOf(model, Tunnel),
                ...allOf(model, SolitaryVegetationObject),
                ...allOf(model, CityFurniture),
                ...allOf(model, Building),
                ...allOf(model, Bridge),
            ].map((x) => x.featureId().asStr());
        assert.deepEqual(ids(written), ids(cityModel));
        const hrefs = (model: CityModel) => allOf(model, SolitaryVegetationObject).map(templateHref);
        assert.deepEqual(hrefs(written), hrefs(cityModel));
    });
});
