import assert from 'node:assert/strict';
import { test } from 'node:test';

import { Building, BuildingUnit, FeatureType, HeightStatusValue, MeasureAttribute, Storey } from '../lib/index.mjs';
import { features, fixtureBytes, read, readBytes } from './helpers.ts';

const FZK_LOD1 = 'FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml';

function firstBuilding(cityModel: ReturnType<typeof read>): Building {
    const building = [...features(cityModel.iterFeatures())].map((f) => Building.tryFrom(f)).find((b) => b !== null);
    assert.ok(building);
    return building;
}

test('building getters', () => {
    const building = firstBuilding(read(FZK_LOD1));
    assert.equal(building.class_()?.value(), '1000');
    assert.equal(building.functions().next().value?.value(), '1000');
    assert.equal(building.roofType()?.value(), '1030');
    // 64-bit integers are BigInts in JavaScript.
    assert.equal(building.storeysAboveGround(), 2n);
    assert.equal(building.storeysBelowGround(), 0n);

    assert.equal(building.dateOfConstruction()?.year(), 2020);
    assert.equal(building.dateOfDemolition(), null);
    const height = building.heights().next().value;
    assert.ok(height);
    assert.equal(height.lowReference().value(), 'lowestGroundPoint');
    assert.equal(height.status(), HeightStatusValue.Measured);
    assert.equal(height.length().value(), 6.52);
    assert.equal(height.length().uom(), 'm');

    const volume = building.lod1Solid()?.object()?.volume3d() ?? 0;
    assert.ok(Math.abs(volume - 782.1228) < 1e-6, `${volume}`);
    assert.ok(building.buildingParts().next().done);
});

test('building part', () => {
    const original = new TextDecoder().decode(fixtureBytes(FZK_LOD1));
    const part = '<bldg:buildingPart><bldg:BuildingPart gml:id="BP_1"><bldg:storeysAboveGround>1</bldg:storeysAboveGround></bldg:BuildingPart></bldg:buildingPart>';
    const cityModel = readBytes(new TextEncoder().encode(original.replace('</bldg:Building>', part + '</bldg:Building>')));
    const parts = firstBuilding(cityModel).buildingParts();
    const property = parts.next();
    assert.ok(!property.done);
    assert.ok(parts.next().done);
    assert.equal(property.value.object()?.featureId().asStr(), 'BP_1');
    assert.equal(property.value.object()?.storeysAboveGround(), 1n);
});

test('generic attributes and external references', () => {
    const building = firstBuilding(read('FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml'));
    const attributes = building.genericAttributes();
    const area = attributes.next().value;
    assert.ok(area);
    assert.equal(area.name(), 'GrossPlannedArea');
    const measure = MeasureAttribute.tryFrom(area);
    assert.equal(measure?.value().value(), 120.0);
    assert.equal(measure?.value().uom(), 'm2');
    assert.equal(attributes.next().value?.asString()?.value(), 'New Building');
    assert.ok(building.externalReferences().next().done);

    const tum = firstBuilding(read('TUM-Main-Entrance.gml'));
    assert.equal(tum.externalReferences().next().value?.targetResource(), 'DEBYvAAAAABTMIyA');
});

test('building subdivisions', () => {
    // No fixture has subdivisions; they are injected after the storey counts (AbstractBuildingType).
    const anchor = '<bldg:storeysBelowGround>0</bldg:storeysBelowGround>';
    const text = new TextDecoder().decode(fixtureBytes('FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml'));
    const cityModel = readBytes(
        new TextEncoder().encode(
            text.replace(
                anchor,
                anchor +
                    '<bldg:buildingSubdivision><bldg:Storey gml:id="storey_ground"><bldg:class>ground</bldg:class>' +
                    '<bldg:function>living</bldg:function></bldg:Storey></bldg:buildingSubdivision>' +
                    '<bldg:buildingSubdivision><bldg:BuildingUnit gml:id="unit_1"><bldg:usage>residential</bldg:usage>' +
                    '</bldg:BuildingUnit></bldg:buildingSubdivision>',
            ),
        ),
    );
    const iterator = firstBuilding(cityModel).buildingSubdivisions();
    const subdivisions = [];
    for (let result = iterator.next(); !result.done; result = iterator.next()) {
        subdivisions.push(result.value.object());
    }
    assert.deepEqual(
        subdivisions.map((s) => s?.featureType()),
        [FeatureType.Storey, FeatureType.BuildingUnit],
    );
    assert.equal(subdivisions[0]?.class_()?.value(), 'ground');
    assert.equal(subdivisions[0]?.functions().next().value?.value(), 'living');
    assert.equal(subdivisions[1]?.usages().next().value?.value(), 'residential');
    const all = [...features(cityModel.iterFeatures())];
    assert.equal(all.map((f) => Storey.tryFrom(f)).find((s) => s !== null)?.featureId().asStr(), 'storey_ground');
    assert.equal(all.map((f) => BuildingUnit.tryFrom(f)).find((u) => u !== null)?.featureId().asStr(), 'unit_1');
});
