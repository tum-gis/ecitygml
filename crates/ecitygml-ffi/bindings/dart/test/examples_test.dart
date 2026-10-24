// Runs the examples in example/ and compares their output with the expected output shared by all
// languages: for every `tests/expected/examples/<example>/<dataset>/<fixture>.txt`, the example runs on
// `tests/fixtures/<dataset>/<fixture>.gml` and must print that text. Examples that write a file get a
// temporary output path; if `expected/<example>/<dataset>/<fixture><extension>` exists, the file must match it.
import 'dart:io';

import 'package:test/test.dart';

import 'helpers.dart';

/// Examples with an output file, and its extension.
const outputExtensions = {'06_export_obj': '.obj', '07_convert': '.gml.gz'};

ProcessResult run(String example, List<String> args) =>
    Process.runSync(Platform.resolvedExecutable, ['run', 'example/$example.dart', ...args]);

void main() {
  for (final example in expectedNames('examples')) {
    for (final (fixture, expectedOutput) in expectedOutputs('examples', example)) {
      test('$example $fixture', () {
        final extension = outputExtensions[example];
        final output = extension == null ? null : temporaryPath('output$extension');
        final result = run(example, [fixturePath('$fixture.gml'), ?output]);
        expect(result.exitCode, 0, reason: '${result.stderr}');
        expect(result.stdout, expectedOutput.readAsStringSync());
        final expectedFile = File(expectedOutput.path.replaceFirst(RegExp(r'\.txt$'), extension ?? ''));
        if (output != null && expectedFile.existsSync()) {
          expect(File(output).readAsStringSync(), expectedFile.readAsStringSync());
        }
      });
    }
  }

  test('every example has expected output', () {
    final scripts = Directory('example')
        .listSync()
        .map((entry) => entry.uri.pathSegments.last)
        .where((name) => RegExp(r'^\d\d_.*\.dart$').hasMatch(name));
    expect(
      scripts.map((name) => name.replaceFirst(RegExp(r'\.dart$'), '')).toList()..sort(),
      expectedNames('examples'),
    );
  });

  test('missing file', () {
    final result = run('01_read_city_model', [fixturePath('does-not-exist.gml')]);
    expect(result.exitCode, 1);
    expect(result.stderr, matches(RegExp('no such file', caseSensitive: false)));
  });

  test('wrong arguments', () {
    final result = run('01_read_city_model', []);
    expect(result.exitCode, 2);
    // `dart run` prints "Running build hooks..." to standard error first.
    expect(result.stderr, contains('usage: 01_read_city_model path/to/model.gml'));
  });
}
