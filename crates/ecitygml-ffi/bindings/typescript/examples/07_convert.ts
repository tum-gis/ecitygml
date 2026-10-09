// Converts a CityGML file: reads it and writes it again, e.g. compressed or indented.
//
// Shows writing with `GmlWriter`. WebAssembly has no file system, so the writer writes to memory:
// `new GmlWriter(format)` with the format picked from the output extension (`.gml`, `.gml.gz` or
// `.gml.zst`), `withFormatting` sets the layout (here indented by two spaces;
// `Formatting.compact()` writes no line breaks at all), `finish` writes the city model and `data()`
// returns the bytes, which Node writes to the file. (The other languages use `GmlWriter.fromPath`.)
// Reading the written file back verifies the result.
//
// Usage: node examples/07_convert.ts input.gml output.gml.gz
//
// Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml, converted to a .gml.gz file:
//
//     Read: 1 city object members, 8 city objects
//     Wrote: gzip-compressed CityGML, indented by 2 spaces
//     Read back: 1 city object members, 8 city objects

import { writeFileSync } from 'node:fs';

import { CityModel, CitygmlFormat, Formatting, GmlWriter } from '../lib/index.mjs';
import { errorText, items, pathArguments, readCityModel } from './common.ts';

const INDENT_SIZE = 2;

function summary(cityModel: CityModel): string {
    return `${cityModel.cityObjectsLen()} city object members, ${[...items(cityModel.iterCityObjects())].length} city objects`;
}

/** The format for an output path and its name; null for other extensions. */
function formatOf(path: string): [CitygmlFormat, string] | null {
    if (path.endsWith('.gml.gz')) return [CitygmlFormat.GmlGz, 'gzip-compressed CityGML'];
    if (path.endsWith('.gml.zst')) return [CitygmlFormat.GmlZst, 'zstd-compressed CityGML'];
    if (path.endsWith('.gml')) return [CitygmlFormat.Gml, 'CityGML'];
    return null;
}

const [inputPath, outputPath] = pathArguments('07_convert', 'input.gml output.gml[.gz|.zst]');
const cityModel = readCityModel(inputPath);
console.log(`Read: ${summary(cityModel)}`);

const format = formatOf(outputPath);
if (!format) {
    console.error(`error: unsupported output extension: ${outputPath}`);
    process.exit(1);
}
try {
    const writer = new GmlWriter(format[0]);
    writer.withFormatting(Formatting.indent(' '.charCodeAt(0), INDENT_SIZE));
    writer.finish(cityModel);
    writeFileSync(outputPath, new Uint8Array(writer.data()));
} catch (error) {
    console.error(`error: ${errorText(error)}`);
    process.exit(1);
}
console.log(`Wrote: ${format[1]}, indented by ${INDENT_SIZE} spaces`);

console.log(`Read back: ${summary(readCityModel(outputPath))}`);
