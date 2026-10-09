// Reads a CityGML file and prints an overview of the city model.
//
// This is the starting point for every program using ecitygml: `GmlReader` reads CityGML data into
// a `CityModel`, which owns all features (see `readCityModel` in common.ts). Errors, e.g. invalid
// XML, are thrown with the ecitygml `Error` as `cause`. Objects borrowed from the city model keep
// it alive; the garbage collector frees the WebAssembly memory.
//
// Usage: node examples/01_read_city_model.ts path/to/model.gml   (Node >= 22.18 runs TypeScript directly)
//
// Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml:
//
//     City object members: 1
//     City objects (at all depths): 8
//     Envelope:
//       lower corner: 457842.000, 5439083.000, 111.800
//       upper corner: 457854.000, 5439093.000, 118.318
//       size: 12.000 x 10.000 x 6.518

import { items, pathArgument, readCityModel } from './common.ts';

const cityModel = readCityModel(pathArgument('01_read_city_model'));

// `cityObjectMember`s are the top-level city objects (e.g. buildings); their boundary surfaces,
// doors and windows are city objects too, which `iterCityObjects()` visits as well.
console.log(`City object members: ${cityModel.cityObjectsLen()}`);
console.log(`City objects (at all depths): ${[...items(cityModel.iterCityObjects())].length}`);

// `boundedBy()` is the `gml:boundedBy` property, a bounding shape holding an envelope; both are
// optional (null when absent), as in the file.
const envelope = cityModel.boundedBy()?.envelope();
if (!envelope) {
    console.log('Envelope: none');
} else {
    const [lower, upper] = [envelope.lowerCorner(), envelope.upperCorner()];
    console.log('Envelope:');
    console.log(`  lower corner: ${lower.x().toFixed(3)}, ${lower.y().toFixed(3)}, ${lower.z().toFixed(3)}`);
    console.log(`  upper corner: ${upper.x().toFixed(3)}, ${upper.y().toFixed(3)}, ${upper.z().toFixed(3)}`);
    console.log(`  size: ${envelope.sizeX().toFixed(3)} x ${envelope.sizeY().toFixed(3)} x ${envelope.sizeZ().toFixed(3)}`);
}
