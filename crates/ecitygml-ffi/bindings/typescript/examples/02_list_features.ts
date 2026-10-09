// Lists the feature types of a CityGML file with their counts, and the ids of its buildings.
//
// A city model is a tree of features: the city model, buildings, their wall surfaces, the doors in
// those walls, and so on. `iterFeatures()` visits all of them, depth first in document order, as
// `AbstractFeatureKindRef`s. Each tells its `featureType()`; to use the getters of its concrete
// type, convert it with that type's `tryFrom`, which returns null for other types.
//
// Usage: node examples/02_list_features.ts path/to/model.gml
//
// Output for FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml (shortened):
//
//     Feature type              Count
//     CityModel                     1
//     Building                      1
//     WallSurface                   4
//     ...
//     Total                        22
//
//     Buildings:
//       UUID_d281adfc-4901-0f52-540b-4cc1a9325f82

import { Building } from '../lib/index.mjs';
import { items, pathArgument, readCityModel } from './common.ts';

const row = (name: string, count: string | number) => console.log(`${name.padEnd(24)} ${String(count).padStart(6)}`);

const cityModel = readCityModel(pathArgument('02_list_features'));

// Count the features per type, in the order the types first appear (a Map keeps insertion order).
// `FeatureType.toString()` is the type's name, as Rust's `Display`.
const counts = new Map<string, number>();
for (const feature of items(cityModel.iterFeatures())) {
    const name = feature.featureType().toString();
    counts.set(name, (counts.get(name) ?? 0) + 1);
}

row('Feature type', 'Count');
for (const [name, count] of counts) {
    row(name, count);
}
row('Total', [...counts.values()].reduce((sum, count) => sum + count, 0));

// `Building.tryFrom` turns a feature into a `Building` (or null).
console.log();
console.log('Buildings:');
for (const feature of items(cityModel.iterFeatures())) {
    const building = Building.tryFrom(feature);
    if (building) {
        console.log(`  ${building.featureId().asStr()}`);
    }
}
