// The cases of crates/ecitygml/tests/conformance/synthetic.md.
import assert from 'node:assert/strict';
import { describe, test } from 'node:test';

import {
    AbstractFeatureKindRef,
    AbstractRingKind,
    AbstractSpaceBoundaryProperty,
    Bridge,
    BridgePart,
    Building,
    CityFurniture,
    CityModel,
    CitygmlFormat,
    ErrorKind,
    FeatureType,
    GenericAttributeSet,
    GeometryType,
    GmlReader,
    GmlWriter,
    GranularityValue,
    ImplicitGeometry,
    ImplicitGeometryProperty,
    LinearRing,
    LineString,
    MultiSurface,
    PlantCover,
    Point,
    Polygon,
    RelativeToWater,
    RoofSurface,
    Section,
    SolitaryVegetationObject,
    TrafficDirectionValue,
    TrafficSpace,
    TriangulatedSurface,
    Tunnel,
    TunnelPart,
} from '../../lib/index.mjs';
import { all, assertClose, read } from './helpers.ts';

const DATASET = 'synthetic';

type TryFrom<T> = { tryFrom(feature: AbstractFeatureKindRef): T | null };

function featureTypes(cityModel: CityModel): FeatureType[] {
    return all(cityModel.iterFeatures()).map((f) => f.featureType());
}

function allOf<T>(cityModel: CityModel, cls: TryFrom<T>): T[] {
    return all(cityModel.iterFeatures())
        .map((f) => cls.tryFrom(f))
        .filter((x): x is T => x !== null);
}

function only<T>(cityModel: CityModel, cls: TryFrom<T>): T {
    const found = allOf(cityModel, cls);
    assert.equal(found.length, 1);
    return found[0];
}

function withId<T extends { featureId(): { asStr(): string } }>(cityModel: CityModel, cls: TryFrom<T>, id: string): T {
    const found = allOf(cityModel, cls).find((x) => x.featureId().asStr() === id);
    assert.ok(found, id);
    return found;
}

function values(iterator: { next(): IteratorResult<{ value(): string }> }): string[] {
    return all(iterator).map((value) => value.value());
}

function ymd(date: { year(): number; month(): number; day(): number } | null): number[] {
    assert.ok(date);
    return [date.year(), date.month(), date.day()];
}

function roundTrip(cityModel: CityModel): [CityModel, string] {
    const writer = new GmlWriter(CitygmlFormat.Gml);
    writer.finish(cityModel);
    const data = new Uint8Array(writer.data());
    return [new GmlReader(data, CitygmlFormat.Gml).finish(), new TextDecoder().decode(data)];
}

function implicit(property: ImplicitGeometryProperty | null): ImplicitGeometry {
    assert.ok(property);
    assert.equal(property.href(), null);
    const geometry = property.object();
    assert.ok(geometry);
    return geometry;
}

describe('bridge.gml', () => {
    const cityModel = read(DATASET, 'bridge.gml');
    const part = (bridge: Bridge): BridgePart => {
        const parts = all(bridge.bridgeParts());
        assert.equal(parts.length, 1);
        assert.equal(parts[0].href(), null);
        const object = parts[0].object();
        assert.ok(object);
        return object;
    };

    test('bridge city model', () => {
        assert.equal(cityModel.cityObjectsLen(), 1);
        assert.deepEqual(featureTypes(cityModel), [FeatureType.CityModel, FeatureType.Bridge, FeatureType.BridgePart]);
        assert.deepEqual(
            all(cityModel.iterCityObjects()).map((o) => o.featureType()),
            [FeatureType.Bridge, FeatureType.BridgePart],
        );
    });

    test('bridge attributes', () => {
        const bridge = only(cityModel, Bridge);
        assert.equal(bridge.featureId().asStr(), 'bridge_1');
        assert.deepEqual(values(bridge.names()), ['Synthetic bridge']);
        assert.equal(bridge.class_()?.value(), '1000');
        assert.deepEqual(values(bridge.functions()), ['1010', '1020']);
        assert.deepEqual(values(bridge.usages()), ['1000']);
        assert.deepEqual(ymd(bridge.dateOfConstruction()), [1990, 5, 1]);
        assert.equal(all(bridge.heights()).length, 0);
        const bridgePart = part(bridge);
        assert.equal(bridgePart.featureId().asStr(), 'bridge_part_1');
        assert.equal(bridgePart.class_(), null);
        assert.equal(all(bridgePart.functions()).length, 0);
        assert.equal(only(cityModel, BridgePart).featureId().asStr(), 'bridge_part_1');
    });

    test('bridge is movable', () => {
        const bridge = only(cityModel, Bridge);
        assert.equal(bridge.isMovable(), true);
        assert.equal(part(bridge).isMovable(), false);
    });

    test('bridge code spaces', () => {
        const bridge = only(cityModel, Bridge);
        assert.equal(bridge.class_()?.code().codeSpace(), 'https://example.org/bridge_class');
        assert.ok(all(bridge.functions()).every((f) => f.code().codeSpace() === null));
    });

    test('bridge round trip', () => {
        const [written] = roundTrip(cityModel);
        assert.deepEqual(featureTypes(written), featureTypes(cityModel));
        const bridge = only(written, Bridge);
        assert.equal(bridge.class_()?.value(), '1000');
        assert.deepEqual(values(bridge.functions()), ['1010', '1020']);
        assert.deepEqual(ymd(bridge.dateOfConstruction()), [1990, 5, 1]);
        assert.equal(part(bridge).featureId().asStr(), 'bridge_part_1');
    });
});

describe('tunnel.gml', () => {
    const cityModel = read(DATASET, 'tunnel.gml');
    const part = (tunnel: Tunnel): TunnelPart => {
        const parts = all(tunnel.tunnelParts());
        assert.equal(parts.length, 1);
        assert.equal(parts[0].href(), null);
        const object = parts[0].object();
        assert.ok(object);
        return object;
    };

    test('tunnel city model', () => {
        assert.equal(cityModel.cityObjectsLen(), 1);
        assert.deepEqual(featureTypes(cityModel), [FeatureType.CityModel, FeatureType.Tunnel, FeatureType.TunnelPart]);
        assert.deepEqual(
            all(cityModel.iterCityObjects()).map((o) => o.featureType()),
            [FeatureType.Tunnel, FeatureType.TunnelPart],
        );
    });

    test('tunnel attributes', () => {
        const tunnel = only(cityModel, Tunnel);
        assert.equal(tunnel.featureId().asStr(), 'tunnel_1');
        assert.deepEqual(values(tunnel.names()), ['Synthetic tunnel']);
        assert.equal(tunnel.class_()?.value(), '1000');
        assert.deepEqual(values(tunnel.functions()), ['1010', '1020']);
        assert.deepEqual(values(tunnel.usages()), ['1000']);
        assert.deepEqual(ymd(tunnel.dateOfConstruction()), [1990, 5, 1]);
        assert.equal(all(tunnel.heights()).length, 0);
        const tunnelPart = part(tunnel);
        assert.equal(tunnelPart.featureId().asStr(), 'tunnel_part_1');
        assert.equal(tunnelPart.class_(), null);
        assert.deepEqual(values(tunnelPart.functions()), ['1030']);
        assert.equal(only(cityModel, TunnelPart).featureId().asStr(), 'tunnel_part_1');
    });

    test('tunnel code spaces', () => {
        const tunnel = only(cityModel, Tunnel);
        assert.equal(tunnel.class_()?.code().codeSpace(), 'https://example.org/tunnel_class');
        assert.ok(all(tunnel.functions()).every((f) => f.code().codeSpace() === null));
    });

    test('tunnel round trip', () => {
        const [written] = roundTrip(cityModel);
        assert.deepEqual(featureTypes(written), featureTypes(cityModel));
        const tunnel = only(written, Tunnel);
        assert.equal(tunnel.class_()?.value(), '1000');
        assert.deepEqual(values(tunnel.functions()), ['1010', '1020']);
        assert.deepEqual(values(part(tunnel).functions()), ['1030']);
    });
});

describe('vegetation.gml', () => {
    const cityModel = read(DATASET, 'vegetation.gml');

    test('vegetation city model', () => {
        assert.equal(cityModel.cityObjectsLen(), 3);
        assert.deepEqual(featureTypes(cityModel), [
            FeatureType.CityModel,
            FeatureType.SolitaryVegetationObject,
            FeatureType.SolitaryVegetationObject,
            FeatureType.PlantCover,
        ]);
    });

    test('vegetation tree', () => {
        const tree = withId(cityModel, SolitaryVegetationObject, 'tree_1');
        assert.equal(tree.class_()?.value(), '1000');
        assert.deepEqual(values(tree.functions()), ['1010']);
        assert.deepEqual(values(tree.usages()), ['1020']);
        assert.equal(tree.species()?.value(), 'Quercus robur');
        assertClose(tree.height()!.value(), 12.5);
        assert.equal(tree.height()!.uom(), 'm');
        assertClose(tree.trunkDiameter()!.value(), 0.4);
        assertClose(tree.crownDiameter()!.value(), 5.5);
        assertClose(tree.rootBallDiameter()!.value(), 1.2);
        assertClose(tree.maxRootBallDepth()!.value(), 0.8);
        assert.equal(tree.lod2ImplicitRepresentation(), null);
        assert.equal(tree.lod3ImplicitRepresentation(), null);
        assert.equal(tree.lod1Solid(), null);
        assert.equal(tree.lod1TerrainIntersectionCurve(), null);
    });

    test('vegetation implicit geometry', () => {
        const geometry = implicit(withId(cityModel, SolitaryVegetationObject, 'tree_1').lod1ImplicitRepresentation());
        assert.equal(geometry.objectId().asStr(), 'tree_prototype');
        assert.equal(geometry.mimeType()?.value(), 'model/gltf+json');
        const pos = geometry.referencePoint().object()!.pos();
        assert.deepEqual([pos.x(), pos.y(), pos.z()], [457850.0, 5439090.0, 112.0]);
        const matrix = geometry.transformationMatrix();
        const rows = [0, 1, 2, 3].map((row) => [0, 1, 2, 3].map((column) => matrix.get(row, column)));
        assert.deepEqual(rows, [
            [2, 0, 0, 10],
            [0, 2, 0, 20],
            [0, 0, 3, 30],
            [0, 0, 0, 1],
        ]);
        const relative = geometry.relativeGeometry()?.object();
        assert.ok(relative);
        assert.equal(relative.geometryType(), GeometryType.MultiSurface);
        assert.equal(all(MultiSurface.tryFrom(relative)!.surfaceMember()).length, 1);
        assert.equal(Point.tryFrom(relative), null);
        const triangulation = relative.triangulate();
        assert.ok(!triangulation.hasSkipped());
        assert.equal(all(triangulation.surface().triangles()).length, 1);
    });

    test('vegetation point relative geometry', () => {
        const tree = withId(cityModel, SolitaryVegetationObject, 'tree_2');
        assert.equal(tree.lod1ImplicitRepresentation(), null);
        const geometry = implicit(tree.lod2ImplicitRepresentation());
        assert.equal(geometry.objectId().asStr(), 'point_prototype');
        assert.equal(geometry.mimeType(), null);
        const relative = geometry.relativeGeometry()?.object();
        assert.ok(relative);
        assert.equal(relative.geometryType(), GeometryType.Point);
        const pos = Point.tryFrom(relative)!.pos();
        assert.deepEqual([pos.x(), pos.y(), pos.z()], [0, 0, 0]);
        assert.equal(MultiSurface.tryFrom(relative), null);
    });

    test('vegetation library object', () => {
        const first = implicit(withId(cityModel, SolitaryVegetationObject, 'tree_1').lod1ImplicitRepresentation());
        assert.equal(first.libraryObject(), null);
        const second = implicit(withId(cityModel, SolitaryVegetationObject, 'tree_2').lod2ImplicitRepresentation());
        assert.equal(second.libraryObject(), 'https://example.org/trees/oak.gltf');
    });

    test('vegetation plant cover', () => {
        const cover = only(cityModel, PlantCover);
        assert.equal(cover.featureId().asStr(), 'cover_1');
        assert.equal(cover.class_()?.value(), '2000');
        assert.equal(all(cover.functions()).length, 0);
        assert.equal(all(cover.usages()).length, 0);
        assertClose(cover.averageHeight()!.value(), 2.5);
        assertClose(cover.minHeight()!.value(), 1.0);
        assertClose(cover.maxHeight()!.value(), 4.0);
        assert.equal(cover.lod1ImplicitRepresentation(), null);
        const feature = all(cityModel.iterFeatures()).find((f) => f.featureType() === FeatureType.PlantCover);
        assert.ok(feature);
        assert.equal(SolitaryVegetationObject.tryFrom(feature), null);
    });

    test('vegetation code spaces', () => {
        const tree = withId(cityModel, SolitaryVegetationObject, 'tree_1');
        assert.equal(tree.class_()?.code().codeSpace(), 'https://example.org/tree_class');
        assert.equal(only(cityModel, PlantCover).class_()?.code().codeSpace(), null);
    });

    test('vegetation round trip', () => {
        const [written, text] = roundTrip(cityModel);
        assert.deepEqual(featureTypes(written), featureTypes(cityModel));
        const tree = withId(written, SolitaryVegetationObject, 'tree_1');
        assert.equal(tree.species()?.value(), 'Quercus robur');
        assertClose(tree.height()!.value(), 12.5);
        const geometry = implicit(tree.lod1ImplicitRepresentation());
        assert.equal(geometry.objectId().asStr(), 'tree_prototype');
        assert.equal(geometry.mimeType()?.value(), 'model/gltf+json');
        assertClose(only(written, PlantCover).averageHeight()!.value(), 2.5);
        assert.ok(!text.includes('objectId'));
    });
});

describe('city-furniture.gml', () => {
    const cityModel = read(DATASET, 'city-furniture.gml');

    test('furniture attributes', () => {
        const furniture = only(cityModel, CityFurniture);
        assert.equal(furniture.featureId().asStr(), 'sign_1');
        assert.deepEqual(values(furniture.names()), ['Vorschriftzeichen']);
        assert.equal(furniture.class_()?.value(), '1000');
        assert.deepEqual(values(furniture.functions()), ['1080']);
        assert.deepEqual(values(furniture.usages()), ['1090']);
        const property = furniture.lod2MultiSurface();
        assert.ok(property);
        assert.equal(property.href(), null);
        assert.equal(all(property.object()!.surfaceMember()).length, 1);
        assert.equal(furniture.lod1ImplicitRepresentation(), null);
        assert.equal(furniture.lod2TerrainIntersectionCurve(), null);
    });

    test('furniture code spaces', () => {
        assert.equal(only(cityModel, CityFurniture).class_()?.code().codeSpace(), 'https://example.org/furniture_class');
    });
});

function roof(property: AbstractSpaceBoundaryProperty): RoofSurface {
    assert.equal(property.href(), null);
    const roofSurface = RoofSurface.tryFrom(AbstractFeatureKindRef.fromSpaceBoundary(property.object()!));
    assert.ok(roofSurface);
    return roofSurface;
}

function attributeSet(building: Building): GenericAttributeSet {
    const attributes = all(building.genericAttributes());
    assert.equal(attributes.length, 1);
    const set = GenericAttributeSet.tryFrom(attributes[0]);
    assert.ok(set);
    return set;
}

describe('building.gml', () => {
    const cityModel = read(DATASET, 'building.gml');

    test('building city model', () => {
        assert.equal(cityModel.cityObjectsLen(), 2);
        assert.deepEqual(featureTypes(cityModel), [
            FeatureType.CityModel,
            FeatureType.Building,
            FeatureType.RoofSurface,
            FeatureType.WindowSurface,
            FeatureType.Building,
        ]);
        assert.equal(all(cityModel.iterCityObjects()).length, 4);
    });

    test('building relation', () => {
        const relations = all(withId(cityModel, Building, 'building_1').relatedTo());
        assert.equal(relations.length, 1);
        assert.equal(relations[0].href(), null);
        const relation = relations[0].object();
        assert.ok(relation);
        assert.equal(relation.relationType().value(), 'shared');
        assert.equal(relation.relationTo().href()?.toString(), '#building_2');
        const attributes = all(relation.genericAttributes());
        assert.equal(attributes.length, 1);
        assert.equal(attributes[0].name(), 'weight');
        assert.equal(attributes[0].asInt()?.value(), 3n);
    });

    test('building attribute set', () => {
        const set = attributeSet(withId(cityModel, Building, 'building_1'));
        assert.equal(set.name(), 'energy');
        const [demand, label] = all(set.genericAttributes());
        assert.equal(demand.name(), 'demand');
        assertClose(demand.asDouble()!.value(), 12.5);
        assert.equal(label.name(), 'label');
        assert.equal(label.asString()?.value(), 'A+');
    });

    test('building construction', () => {
        const building = withId(cityModel, Building, 'building_1');
        assert.equal(building.relativeToWater(), RelativeToWater.EntirelyAboveWaterSurface);
        assert.deepEqual(ymd(building.dateOfConstruction()), [2020, 1, 1]);
        assert.deepEqual(ymd(building.dateOfDemolition()), [2050, 12, 31]);
        const occupancies = all(building.occupancies());
        assert.equal(occupancies.length, 1);
        assert.equal(occupancies[0].numberOfOccupants(), 4n);
        assert.equal(occupancies[0].interval()?.value(), 'daytime');
        assert.equal(occupancies[0].occupantType()?.value(), 'residents');
    });

    test('building boundaries', () => {
        const boundaries = all(withId(cityModel, Building, 'building_1').boundaries());
        assert.equal(boundaries.length, 2);
        const roofSurface = roof(boundaries[0]);
        assert.equal(roofSurface.featureId().asStr(), 'roof_1');
        const fillings = all(roofSurface.fillingSurfaces());
        assert.equal(fillings.length, 1);
        assert.equal(fillings[0].href(), null);
        const window = fillings[0].object();
        assert.ok(window);
        assert.equal(window.featureType(), FeatureType.WindowSurface);
        assert.equal(window.featureId().asStr(), 'roof_window_1');
        assert.equal(boundaries[1].object(), null);
        assert.equal(boundaries[1].href()?.toString(), '#missing_boundary');
    });

    test('building terrain intersection curve', () => {
        const building = withId(cityModel, Building, 'building_1');
        const property = building.lod2TerrainIntersectionCurve();
        assert.ok(property);
        assert.equal(property.href(), null);
        const multiCurve = property.object();
        assert.ok(multiCurve);
        const members = all(multiCurve.curveMember());
        assert.equal(members.length, 1);
        assert.equal(all(LineString.tryFrom(members[0].object()!)!.points()).length, 2);
        assertClose(multiCurve.length3d(), 12.0);
        assert.equal(building.lod1TerrainIntersectionCurve(), null);
        assert.equal(building.lod3TerrainIntersectionCurve(), null);
    });

    test('building round trip', () => {
        const [written, text] = roundTrip(cityModel);
        assert.deepEqual(featureTypes(written), featureTypes(cityModel));
        const building = withId(written, Building, 'building_1');
        const relation = all(building.relatedTo())[0].object();
        assert.equal(relation?.relationTo().href()?.toString(), '#building_2');
        assert.equal(attributeSet(building).name(), 'energy');
        assert.deepEqual(ymd(building.dateOfDemolition()), [2050, 12, 31]);
        const occupancies = all(building.occupancies());
        assert.equal(occupancies.length, 1);
        assert.equal(occupancies[0].numberOfOccupants(), 4n);
        assert.equal(occupancies[0].interval()?.value(), 'daytime');
        assert.equal(occupancies[0].occupantType()?.value(), 'residents');
        const boundaries = all(building.boundaries());
        const fillings = all(roof(boundaries[0]).fillingSurfaces());
        assert.equal(fillings[0].object()?.featureId().asStr(), 'roof_window_1');
        assert.equal(boundaries[1].href()?.toString(), '#missing_boundary');
        assertClose(building.lod2TerrainIntersectionCurve()!.object()!.length3d(), 12.0);
        assert.ok(!text.includes('TerrainIntersectionCurveProperty'));
    });
});

describe('transportation.gml', () => {
    const cityModel = read(DATASET, 'transportation.gml');

    test('transportation section', () => {
        const section = only(cityModel, Section);
        assert.equal(section.featureId().asStr(), 'section_1');
        assert.equal(section.trafficDirection(), TrafficDirectionValue.Both);
        const occupancies = all(section.occupancies());
        assert.equal(occupancies.length, 1);
        assert.equal(occupancies[0].numberOfOccupants(), 120n);
        assert.equal(occupancies[0].interval()?.value(), 'peakHour');
        const spaces = all(section.trafficSpaces());
        assert.equal(spaces.length, 1);
        assert.equal(spaces[0].href(), null);
        const space = spaces[0].object();
        assert.ok(space);
        assert.equal(space.featureId().asStr(), 'space_1');
        assert.equal(space.granularity(), GranularityValue.Lane);
    });

    test('transportation point', () => {
        const property = only(cityModel, TrafficSpace).lod0Point();
        assert.ok(property);
        assert.equal(property.href(), null);
        const point = property.object();
        assert.ok(point);
        assert.equal(point.id()?.asStr(), 'point_1');
        const pos = point.pos();
        assert.deepEqual([pos.x(), pos.y(), pos.z()], [1.5, -2.5, 3.25]);
        const envelope = point.computeEnvelope();
        assert.ok(envelope);
        for (const corner of [envelope.lowerCorner(), envelope.upperCorner()]) {
            assert.deepEqual([corner.x(), corner.y(), corner.z()], [1.5, -2.5, 3.25]);
        }
    });

    test('transportation curves', () => {
        const multiCurve = only(cityModel, TrafficSpace).lod0MultiCurve()?.object();
        assert.ok(multiCurve);
        const [line, ring, reference] = all(multiCurve.curveMember());
        const lineKind = line.object();
        assert.ok(lineKind);
        assert.equal(lineKind.geometryType(), GeometryType.LineString);
        assert.equal(AbstractRingKind.tryFrom(lineKind), null);
        const lineString = LineString.tryFrom(lineKind);
        assert.ok(lineString);
        assert.equal(all(lineString.points()).length, 2);
        assertClose(lineString.length3d(), 5.0);
        const ringKind = ring.object();
        assert.ok(ringKind);
        assert.equal(ringKind.geometryType(), GeometryType.LinearRing);
        const linearRing = LinearRing.tryFrom(AbstractRingKind.tryFrom(ringKind)!);
        assert.ok(linearRing);
        assert.equal(all(linearRing.points()).length, 3);
        assertClose(linearRing.length3d(), 2 + Math.SQRT2);
        assert.equal(reference.object(), null);
        assert.equal(reference.href()?.toString(), '#missing_curve');
        assert.throws(
            () => multiCurve.length3d(),
            (error: Error) => {
                assert.equal((error.cause as { kind(): ErrorKind }).kind(), ErrorKind.UnresolvedReference);
                assert.ok(error.message.includes('#missing_curve'), error.message);
                return true;
            },
        );
    });
});

describe('geometry.gml', () => {
    const cityModel = read(DATASET, 'geometry.gml');

    test('geometry skipped members', () => {
        const multiSurface = withId(cityModel, Building, 'geometry_1').lod2MultiSurface()?.object();
        assert.ok(multiSurface);
        const [square, collinear, tinKind] = all(multiSurface.surfaceMember()).map((m) => m.object()!);
        for (const [kind, id] of [
            [square, 'square'],
            [collinear, 'collinear'],
        ] as const) {
            assert.equal(kind.geometryType(), GeometryType.Polygon);
            assert.equal(kind.id()?.asStr(), id);
        }
        assertClose(collinear.area3d(), 0.0);
        assert.equal(tinKind.geometryType(), GeometryType.TriangulatedSurface);
        assert.equal(Polygon.tryFrom(tinKind), null);
        const tin = TriangulatedSurface.tryFrom(tinKind);
        assert.ok(tin);
        assert.equal(tin.id()?.asStr(), 'tin');
        assert.equal(all(tin.triangles()).length, 2);
        assert.equal(all(tin.surface().patches()).length, 2);
        assertClose(tin.area3d(), 1.0);
        const triangulation = multiSurface.triangulate();
        assert.equal(all(triangulation.surface().triangles()).length, 4);
        assert.ok(triangulation.hasSkipped());
        const skipped = all(triangulation.skipped());
        assert.equal(skipped.length, 1);
        assert.equal(skipped[0].kind(), ErrorKind.InvalidArgument);
        assert.ok(skipped[0].toString().includes('earcut produced no triangles'));
    });
});
