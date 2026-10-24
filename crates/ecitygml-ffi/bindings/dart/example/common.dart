// Helpers shared by the examples.

import 'dart:io';

import 'package:ecitygml/ecitygml.dart' as ecitygml;

/// Reads a city model from a file (plain, `.gml.gz` or `.gml.zst`), or prints the error and exits with code 1.
ecitygml.CityModel readCityModel(String path) {
  try {
    return ecitygml.GmlReader.fromPath(path).finish();
  } on ecitygml.Error catch (error) {
    fail(error);
  }
}

/// Prints the message of an ecitygml `Error` to standard error and exits with code 1.
Never fail(ecitygml.Error error) {
  stderr.writeln('error: ${error.message()}');
  exit(1);
}

/// Diplomat's iterators implement [Iterator] but not [Iterable]: this makes them usable in `for`.
Iterable<T> items<T>(Iterator<T> iterator) sync* {
  while (iterator.moveNext()) {
    yield iterator.current;
  }
}

/// The single path argument; exits with code 2 and a usage message otherwise.
String pathArgument(List<String> args, String example) => pathArguments(args, example, 'path/to/model.gml').single;

/// The command-line arguments; exits with code 2 and the usage message if their number differs.
List<String> pathArguments(List<String> args, String example, String usage) {
  if (args.length != usage.split(' ').length) {
    stderr.writeln('usage: $example $usage');
    exit(2);
  }
  return args;
}

/// The multi surface of the highest level of detail among a thematic surface's properties (LoD3 first).
ecitygml.MultiSurface? highestLod(List<ecitygml.MultiSurfaceProperty?> properties) {
  for (final property in properties) {
    final object = property?.object();
    if (object != null) {
      return object;
    }
  }
  return null;
}

/// `value.toStringAsFixed(3)`, the precision of the examples' output.
String fixed(double value) => value.toStringAsFixed(3);
