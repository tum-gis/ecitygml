// Runs the snippets in example/snippets/ (short programs giving a first impression of the bindings) and
// compares their output with the expected output shared by all languages: for every
// `tests/expected/snippets/<snippet>/<dataset>/<fixture>.txt`, the snippet runs on `tests/fixtures/<dataset>/<fixture>.gml`
// and must print that text. Each runs in a process of its own, because the ids the reader generates for
// features without `gml:id` are numbered per process.
import 'dart:io';

import 'package:test/test.dart';

import 'helpers.dart';

/// Snippets that write a file, and its extension (the snippet's second argument).
const outputExtensions = {'translate_to_local_coordinates': '.gml'};

void main() {
  for (final snippet in expectedNames('snippets')) {
    for (final (fixture, expectedOutput) in expectedOutputs('snippets', snippet)) {
      test('$snippet $fixture', () {
        final extension = outputExtensions[snippet];
        final output = extension == null ? null : temporaryPath('output$extension');
        final result = Process.runSync(Platform.resolvedExecutable, [
          'run',
          'example/snippets/$snippet.dart',
          fixturePath('$fixture.gml'),
          ?output,
        ]);
        expect(result.exitCode, 0, reason: '${result.stderr}');
        expect(result.stdout, expectedOutput.readAsStringSync());
        final expectedFile = File(expectedOutput.path.replaceFirst(RegExp(r'\.txt$'), extension ?? ''));
        if (output != null && expectedFile.existsSync()) {
          expect(File(output).readAsBytesSync(), expectedFile.readAsBytesSync(), reason: '$output differs');
        }
      });
    }
  }

  test('every snippet has expected output', () {
    final scripts = Directory('example/snippets')
        .listSync()
        .map((entry) => entry.uri.pathSegments.last)
        .where((name) => name.endsWith('.dart'));
    expect(
      scripts.map((name) => name.replaceFirst(RegExp(r'\.dart$'), '')).toList()..sort(),
      expectedNames('snippets'),
    );
  });
}
