// The cases of crates/ecitygml/tests/api/writer.md.
import 'dart:convert';
import 'dart:io';

import 'package:ecitygml/ecitygml.dart';
import 'package:test/test.dart';

import '../helpers.dart';
import 'helpers.dart';

void main() {
  late final CityModel model;
  setUpAll(() => model = read(fzkLod3));

  void expectReadsBack(String path) => expect(featureTypes(readPath(path)), featureTypes(model), reason: path);

  /// The model written as `Gml` text.
  String text([Formatting? formatting]) {
    final writer = GmlWriter(CitygmlFormat.gml);
    if (formatting != null) {
      writer.withFormatting(formatting);
    }
    writer.finish(model);
    return utf8.decode(writer.data());
  }

  List<String> lines(String text) => const LineSplitter().convert(text);

  test('writer in memory', () {
    for (final format in CitygmlFormat.values) {
      final writer = GmlWriter(format);
      expect(writer.data(), isEmpty);
      writer.finish(model);
      expect(featureTypes(readBytes(writer.data(), format)), featureTypes(model), reason: '$format');
    }
    expect(text(), contains('<bldg:Building'));
  });

  test('writer files', () {
    for (final name in ['out.gml', 'out.gml.gz', 'out.gml.zst']) {
      final path = temporaryPath(name);
      GmlWriter.fromPath(path).finish(model);
      expectReadsBack(path);
    }
  });

  test('writer overwrites file', () {
    final path = temporaryPath('out.gml');
    File(path).writeAsStringSync('x' * 100000);
    GmlWriter.fromPath(path).finish(model);
    expectReadsBack(path);
  });

  test('writer base path with format', () {
    final base = temporaryPath('out');
    File('$base.gml.gz').writeAsStringSync('x' * 100000);
    GmlWriter.fromBasePathWithFormat(base, CitygmlFormat.gmlGz).finish(model);
    expectReadsBack('$base.gml.gz');
  });

  test('writer formatting', () {
    final defaultText = text();
    expect(lines(defaultText).length, greaterThan(1));
    expect(lines(defaultText).any((line) => line.startsWith(' ') || line.startsWith('\t')), isFalse);
    expect(text(Formatting.newLine()), defaultText);
    expect(text(Formatting.indent(' '.codeUnitAt(0), 0)), defaultText);

    expect(lines(text(Formatting.compact())).length, lessThan(lines(defaultText).length));

    final spaces = lines(text(Formatting.indent(' '.codeUnitAt(0), 2)));
    expect(spaces.any((line) => line.startsWith('  <')), isTrue);
    expect(spaces.any((line) => line.startsWith('\t')), isFalse);

    final tabs = text(Formatting.indent('\t'.codeUnitAt(0), 1));
    expect(lines(tabs).any((line) => line.startsWith('\t<')), isTrue);
    expect(featureTypes(readBytes(utf8.encode(tabs))), featureTypes(model));
  });

  test('writer finish once', () {
    final writer = GmlWriter(CitygmlFormat.gml)..finish(model);
    expect(() => writer.finish(model), throwsError(ErrorKind.invalidArgument, 'already finished'));
  });

  test('writer unsupported extension', () {
    expect(() => GmlWriter.fromPath(temporaryPath('out.txt')), throwsError(ErrorKind.invalidArgument, 'txt'));
  });

  test('writer missing directory', () {
    expect(() => GmlWriter.fromPath(temporaryPath('missing/out.gml')), throwsError(ErrorKind.io, ''));
  });

  const fzkLod2 = 'fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml';

  String textOf(CityModel cityModel) {
    final writer = GmlWriter(CitygmlFormat.gml)..finish(cityModel);
    return utf8.decode(writer.data());
  }

  int occurrences(String text, String part) => text.split(part).length - 1;

  test('writer keeps references', () {
    final text = textOf(read(fzkLod2));
    expect(occurrences(text, 'xlink:href="#PolyID7350_878_759628_120742"'), 1);
    expect(occurrences(text, 'gml:id="PolyID7350_878_759628_120742"'), 1);
  });

  /// The exterior ring positions of every polygon of the wall surfaces' LoD2 multi surfaces, in document order.
  List<List<double>> wallCoordinates(CityModel cityModel) => [
        for (final wall in items(cityModel.iterFeatures()).map(WallSurface.tryFrom).nonNulls)
          if (wall.lod2MultiSurface()?.object() case final multiSurface?)
            for (final member in items(multiSurface.surfaceMember()))
              if (Polygon.tryFrom(member.object()!) case final polygon?)
                for (final p in items(LinearRing.tryFrom(polygon.exterior()!)!.points())) [p.x(), p.y(), p.z()],
      ];

  test('writer preserves coordinates', () {
    final cityModel = read(fzkLod2);
    final written = readBytes(utf8.encode(textOf(cityModel)));
    final coordinates = wallCoordinates(cityModel);
    expect(coordinates, isNotEmpty);
    expect(wallCoordinates(written), coordinates);
  });
}
