// The cases of crates/ecitygml/tests/api/reader.md.
import 'dart:io';

import 'package:ecitygml/ecitygml.dart';
import 'package:test/test.dart';

import '../helpers.dart';
import 'helpers.dart';

void main() {
  test('reader from bytes', () {
    expect(readBytes(fixtureBytes(fzkLod1), CitygmlFormat.gml).cityObjectsLen(), 1);
  });

  test('reader compressed', () {
    for (final (extension, format) in [('gz', CitygmlFormat.gmlGz), ('zst', CitygmlFormat.gmlZst)]) {
      final path = fixturePath('fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml.$extension');
      expect(readPath(path).cityObjectsLen(), 1, reason: path);
      expect(readBytes(File(path).readAsBytesSync(), format).cityObjectsLen(), 1, reason: path);
    }
  });

  test('reader default rebuilds object bounds', () {
    final walls = items(read(fzkLod2).iterFeatures()).map(WallSurface.tryFrom).nonNulls;
    expect(walls.map((wall) => wall.boundedBy() != null), [true, true, true, true]);
  });

  test('reader finish once', () {
    final reader = GmlReader.fromPath(fixturePath(fzkLod1))..withRebuildObjectBounds(false);
    expect(reader.finish().cityObjectsLen(), 1);
    expect(reader.finish, throwsError(ErrorKind.invalidArgument, 'already finished'));
  });

  test('reader missing file', () {
    expect(() => GmlReader.fromPath(fixturePath('does-not-exist.gml')), throwsError(ErrorKind.io, 'No such file'));
  });

  test('reader unsupported extension', () {
    expect(() => GmlReader.fromPath(fixturePath('README.md')), throwsError(ErrorKind.invalidArgument, 'md'));
  });

  test('reader invalid content', () {
    final reader = GmlReader.fromPath(fixturePath('invalid/unclosed-tag.gml'));
    expect(reader.finish, throwsError(ErrorKind.parse, 'tag not closed'));
  });
}
