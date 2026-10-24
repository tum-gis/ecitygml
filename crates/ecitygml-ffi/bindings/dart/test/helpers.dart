import 'dart:convert';
import 'dart:io';

import 'package:ecitygml/ecitygml.dart';
import 'package:test/test.dart';

const fzkLod1 = 'fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml';
const fzkLod2 = 'fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml';
const fzkLod3 = 'fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml';

/// `dart test` runs with the package root as working directory.
final fixtures = Directory('../../../../tests/fixtures').absolute.uri;

String fixturePath(String name) => fixtures.resolve(name).toFilePath();

/// The expected outputs shared by all languages: `tests/expected/<kind>/<name>/<dataset>/<fixture>.txt`.
final expected = Directory('../../../../tests/expected').absolute;

/// The sorted names of the examples or snippets (`kind`) with expected output.
List<String> expectedNames(String kind) =>
    // A directory's URI ends with '/', so its name is the last non-empty segment.
    Directory('${expected.path}/$kind').listSync().whereType<Directory>().map((directory) {
      return directory.uri.pathSegments.lastWhere((segment) => segment.isNotEmpty);
    }).toList()..sort();

/// The fixtures with expected output of an example or snippet, as `<dataset>/<fixture>` (their path below
/// `tests/fixtures`), and the `.txt` file holding it.
List<(String, File)> expectedOutputs(String kind, String name) {
  final files = Directory('${expected.path}/$kind/$name')
      .listSync(recursive: true)
      .whereType<File>()
      .where((file) => file.path.endsWith('.txt'));
  return [
    for (final file in files)
      (
        file.uri.pathSegments.reversed.take(2).toList().reversed.join('/').replaceFirst(RegExp(r'\.txt$'), ''),
        file,
      ),
  ]..sort((a, b) => a.$1.compareTo(b.$1));
}

/// A path in a new temporary directory, deleted after the test.
String temporaryPath(String name) {
  final directory = Directory.systemTemp.createTempSync('ecitygml-dart-');
  addTearDown(() => directory.deleteSync(recursive: true));
  return '${directory.path}/$name';
}

List<int> fixtureBytes(String name) => File(fixturePath(name)).readAsBytesSync();

/// `GmlReader::new(data, format).finish()`, as in Rust.
CityModel readBytes(List<int> data, [CitygmlFormat format = CitygmlFormat.gml]) => GmlReader(data, format).finish();

CityModel read(String name) => GmlReader.fromPath(fixturePath(name)).finish();

/// A fixture with `from` replaced by `to` (to inject content no fixture has).
CityModel readReplaced(String name, String from, String to) {
  final text = utf8.decode(fixtureBytes(name));
  if (!text.contains(from)) {
    throw ArgumentError('$from not found in $name');
  }
  return readBytes(utf8.encode(text.replaceFirst(from, to)));
}

/// Diplomat's iterators implement [Iterator] but not [Iterable]: this makes them usable in `for`.
Iterable<T> items<T>(Iterator<T> iterator) sync* {
  while (iterator.moveNext()) {
    yield iterator.current;
  }
}

Building firstBuilding(CityModel cityModel) => items(cityModel.iterFeatures()).map(Building.tryFrom).nonNulls.first;
