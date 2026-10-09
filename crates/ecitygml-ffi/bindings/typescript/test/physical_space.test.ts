import assert from 'node:assert/strict';
import { test } from 'node:test';

import { Building, GeometryType, MultiSurface, Point } from '../lib/index.mjs';
import { features, fixtureBytes, readBytes } from './helpers.ts';

test('terrain intersection curve and implicit representation', () => {
    // No fixture has these; they are injected into the FZK LoD2 building after its solid.
    const text = new TextDecoder().decode(fixtureBytes('FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml'));
    const cityModel = readBytes(
        new TextEncoder().encode(
            text.replace(
                '</lod2Solid>',
                '</lod2Solid>' +
                    '<lod2TerrainIntersectionCurve><gml:MultiCurve><gml:curveMember><gml:LineString>' +
                    '<gml:posList>457842 5439083 111.8 457854 5439083 111.8</gml:posList>' +
                    '</gml:LineString></gml:curveMember></gml:MultiCurve></lod2TerrainIntersectionCurve>' +
                    '<lod1ImplicitRepresentation><ImplicitGeometry gml:id="tree_prototype">' +
                    '<transformationMatrix>2 0 0 10 0 2 0 20 0 0 3 30 0 0 0 1</transformationMatrix>' +
                    '<mimeType>model/gltf+json</mimeType>' +
                    '<referencePoint><gml:Point><gml:pos>457850 5439090 112</gml:pos></gml:Point></referencePoint>' +
                    '<relativeGeometry><gml:Point><gml:pos>0 0 0</gml:pos></gml:Point></relativeGeometry>' +
                    '</ImplicitGeometry></lod1ImplicitRepresentation>',
            ),
        ),
    );
    const building = [...features(cityModel.iterFeatures())].map((f) => Building.tryFrom(f)).find((b) => b !== null);
    assert.ok(building);
    assert.equal(building.lod1TerrainIntersectionCurve(), null);
    assert.ok(Math.abs((building.lod2TerrainIntersectionCurve()?.object()?.length3d() ?? 0) - 12) < 1e-9);

    const implicit = building.lod1ImplicitRepresentation()?.object();
    assert.ok(implicit);
    assert.equal(implicit.objectId().asStr(), 'tree_prototype');
    assert.equal(implicit.mimeType()?.value(), 'model/gltf+json');
    assert.equal(implicit.libraryObject(), null);
    assert.equal(implicit.referencePoint().object()?.pos().z(), 112);
    const matrix = implicit.transformationMatrix();
    assert.equal(matrix.get(0, 3), 10);
    assert.equal(matrix.get(2, 2), 3);
    assert.throws(() => matrix.get(4, 0));

    const geometry = implicit.relativeGeometry()?.object();
    assert.ok(geometry);
    assert.equal(geometry.geometryType(), GeometryType.Point);
    assert.equal(Point.tryFrom(geometry)?.pos().x(), 0);
    assert.equal(MultiSurface.tryFrom(geometry), null);
});
