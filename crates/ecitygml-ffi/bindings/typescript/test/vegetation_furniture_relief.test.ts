import assert from 'node:assert/strict';
import { test } from 'node:test';

import {
    CityFurniture,
    FeatureType,
    LevelOfDetail,
    PlantCover,
    ReliefFeature,
    SolitaryVegetationObject,
    TinRelief,
} from '../lib/index.mjs';
import { features, readMember } from './helpers.ts';

test('solitary vegetation object, plant cover and city furniture', () => {
    const cityModel = readMember(`<cityObjectMember>
    <veg:SolitaryVegetationObject gml:id="tree_1">
      <veg:class>1000</veg:class>
      <veg:species>Quercus robur</veg:species>
      <veg:height uom="m">12.5</veg:height>
    </veg:SolitaryVegetationObject>
  </cityObjectMember>
  <cityObjectMember>
    <veg:PlantCover gml:id="cover_1"><veg:averageHeight uom="m">2.5</veg:averageHeight></veg:PlantCover>
  </cityObjectMember>
  <cityObjectMember>
    <frn:CityFurniture gml:id="sign_1"><frn:function>1080</frn:function></frn:CityFurniture>
  </cityObjectMember>
</CityModel>
`);
    const all = [...features(cityModel.iterFeatures())];
    const tree = all.map((f) => SolitaryVegetationObject.tryFrom(f)).find((t) => t !== null);
    assert.equal(tree?.class_()?.value(), '1000');
    assert.equal(tree?.species()?.value(), 'Quercus robur');
    assert.equal(tree?.height()?.value(), 12.5);
    assert.equal(all.map((f) => PlantCover.tryFrom(f)).find((c) => c !== null)?.averageHeight()?.value(), 2.5);
    const furniture = all.map((f) => CityFurniture.tryFrom(f)).find((c) => c !== null);
    assert.equal(furniture?.functions().next().value?.value(), '1080');
});

test('relief feature and TIN relief', () => {
    const cityModel = readMember(`<cityObjectMember>
    <dem:ReliefFeature gml:id="relief_1">
      <dem:lod>2</dem:lod>
      <dem:reliefComponent>
        <dem:TINRelief gml:id="tin_1">
          <dem:lod>1</dem:lod>
          <dem:tin><gml:TriangulatedSurface><gml:patches><gml:Triangle><gml:exterior><gml:LinearRing>
            <gml:posList>0 0 0 1 0 0 0 1 0 0 0 0</gml:posList>
          </gml:LinearRing></gml:exterior></gml:Triangle></gml:patches></gml:TriangulatedSurface></dem:tin>
        </dem:TINRelief>
      </dem:reliefComponent>
    </dem:ReliefFeature>
  </cityObjectMember>
</CityModel>
`);
    const all = [...features(cityModel.iterFeatures())];
    const relief = all.map((f) => ReliefFeature.tryFrom(f)).find((r) => r !== null);
    assert.ok(relief);
    assert.equal(relief.lod(), LevelOfDetail.Two);
    const component = relief.reliefComponents().next().value?.object();
    assert.equal(component?.featureType(), FeatureType.TinRelief);
    assert.equal(component?.lod(), LevelOfDetail.One);
    const tin = all.map((f) => TinRelief.tryFrom(f)).find((t) => t !== null);
    const triangles = tin?.tin()?.object()?.triangles();
    assert.ok(triangles);
    assert.ok(!triangles.next().done);
    assert.ok(triangles.next().done);
});
