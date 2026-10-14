import { readFileSync } from 'node:fs';
import { CitygmlFormat, GmlReader, TrafficSpace } from 'ecitygml';

const path = process.argv[2] ?? 'model.gml';

// Parse the CityGML document into the in-memory city model
const bytes = readFileSync(path) as unknown as number[];
const cityModel = new GmlReader(bytes, CitygmlFormat.Gml).finish();

// Traverse all features and keep only those that are traffic spaces,
// using a type-safe conversion that skips all other feature types
const trafficSpaces: TrafficSpace[] = [];
const features = cityModel.iterFeatures();
for (let next = features.next(); !next.done; next = features.next()) {
    const space = TrafficSpace.tryFrom(next.value);
    if (space) {
        trafficSpaces.push(space);
    }
}

// Compute the volumes of the LOD2 solids and sum them up; spaces
// without an LOD2 solid are skipped
let total = 0;
for (const space of trafficSpaces) {
    const solid = space.lod2Solid()?.object();
    if (solid) {
        total += solid.volume3d();
    }
}

console.log(
    `Total volume of traffic spaces (LoD2): ${total.toFixed(3)} m^3`,
);
