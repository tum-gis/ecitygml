import { readFileSync } from 'node:fs';

import { CitygmlFormat, GmlReader, WallSurface } from 'ecitygml';

const path = process.argv[2] ?? 'model.gml';

// Parse the CityGML document into the in-memory city model
const bytes = readFileSync(path) as unknown as number[];
const cityModel = new GmlReader(bytes, CitygmlFormat.Gml).finish();

// Sum up the areas of the LOD2 multi-surfaces of all wall surfaces; other
// feature types and walls without an LOD2 multi-surface are skipped
let totalArea = 0.0;
const features = cityModel.iterFeatures();
for (let next = features.next(); !next.done; next = features.next()) {
    const wall = WallSurface.tryFrom(next.value);
    const surface = wall?.lod2MultiSurface()?.object();
    if (surface) {
        totalArea += surface.area3d();
    }
}

console.log(
    `Total area of wall surfaces (LoD2): ${totalArea.toFixed(3)} m^2`,
);
