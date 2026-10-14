import { readFileSync } from 'node:fs';

import {
    AbstractCityObjectKindRef,
    AbstractFeatureKindRef,
    Building,
    CitygmlFormat,
    GmlReader,
    HeightStatusValue,
} from 'ecitygml';

const path = process.argv[2] ?? 'model.gml';

// Parse the CityGML document into the in-memory city model
const bytes = readFileSync(path) as unknown as number[];
const cityModel = new GmlReader(bytes, CitygmlFormat.Gml).finish();

// Sum up the measured heights of the top-level buildings; only heights from
// the lowest ground point to the top of construction given in meters are
// taken into account
let totalHeight = 0.0;
const members = cityModel.cityObjectMembers();
for (let member = members.next(); !member.done; member = members.next()) {
    const cityObject = member.value.object();
    if (!cityObject) continue;
    const cityObjectRef = AbstractCityObjectKindRef.fromCityObject(cityObject);
    const feature = AbstractFeatureKindRef.fromCityObject(cityObjectRef);
    const building = Building.tryFrom(feature);
    if (!building) continue;
    const heights = building.heights();
    for (let next = heights.next(); !next.done; next = heights.next()) {
        const height = next.value;
        if (height.lowReference().value() === 'lowestGroundPoint'
            && height.highReference().value() === 'topOfConstruction'
            && height.status() === HeightStatusValue.Measured
            && height.length().uom() === 'urn:adv:uom:m') {
            totalHeight += height.length().value();
        }
    }
}

console.log(`Total measured height of buildings: ${totalHeight.toFixed(3)} m`);
