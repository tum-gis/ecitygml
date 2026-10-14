import { readFileSync, writeFileSync } from 'node:fs';

import { CitygmlFormat, GmlReader, GmlWriter } from 'ecitygml';

const [inputPath = 'model.gml', outputPath = 'model_local.gml'] =
    process.argv.slice(2);

// Parse the CityGML document, keeping the envelopes of the objects as given
// in the file instead of recomputing them from their geometry
const bytes = readFileSync(inputPath) as unknown as number[];
const reader = new GmlReader(bytes, CitygmlFormat.Gml);
reader.withRebuildObjectBounds(false);
const cityModel = reader.finish();

// Move the center of the city model's envelope to the origin
const center = cityModel.boundedBy()!.envelope()!.center();
const offset = { x: -center.x(), y: -center.y(), z: -center.z() };
cityModel.applyTranslation(offset);

// Write the translated city model as a CityGML document
const writer = new GmlWriter(CitygmlFormat.Gml);
writer.finish(cityModel);
writeFileSync(outputPath, new Uint8Array(writer.data()));

const { x, y, z } = offset;
console.log(
    `Translated the city model by (${x.toFixed(3)}, ${y.toFixed(3)}, `
    + `${z.toFixed(3)}) to local coordinates`,
);
