// Converts a CityGML file: reads it and writes it again, e.g. compressed or indented.
//
// Shows writing with `GmlWriter`: `GmlWriter.fromPath` picks the format from the output extension
// (`.gml`, `.gml.gz` or `.gml.zst`), `withFormatting` sets the layout (here indented by two spaces;
// `Formatting.compact()` writes no line breaks at all) and `finish` writes the city model; it works
// only once. Reading the written file back verifies the result.
//
// Usage: dart run example/07_convert.dart input.gml output.gml.gz
//
// Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml, converted to a .gml.gz file:
//
//     Read: 1 city object members, 8 city objects
//     Wrote: gzip-compressed CityGML, indented by 2 spaces
//     Read back: 1 city object members, 8 city objects

import 'dart:io';

import 'package:ecitygml/ecitygml.dart';

import 'common.dart';

const indentSize = 2;

String summary(CityModel cityModel) =>
    '${cityModel.cityObjectsLen()} city object members, ${items(cityModel.iterCityObjects()).length} city objects';

/// The name of the format for an output path; null for other extensions.
String? formatName(String path) {
  if (path.endsWith('.gml.gz')) return 'gzip-compressed CityGML';
  if (path.endsWith('.gml.zst')) return 'zstd-compressed CityGML';
  if (path.endsWith('.gml')) return 'CityGML';
  return null;
}

void main(List<String> args) {
  final [inputPath, outputPath] = pathArguments(args, '07_convert', 'input.gml output.gml[.gz|.zst]');
  final cityModel = readCityModel(inputPath);
  print('Read: ${summary(cityModel)}');

  final format = formatName(outputPath);
  if (format == null) {
    stderr.writeln('error: unsupported output extension: $outputPath');
    exit(1);
  }
  try {
    final writer = GmlWriter.fromPath(outputPath)..withFormatting(Formatting.indent(' '.codeUnitAt(0), indentSize));
    writer.finish(cityModel);
  } on Error catch (error) {
    fail(error);
  }
  print('Wrote: $format, indented by $indentSize spaces');

  print('Read back: ${summary(readCityModel(outputPath))}');
}
