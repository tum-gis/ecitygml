// Helpers of the API suite (crates/ecitygml/tests/api/README.md).
import 'package:ecitygml/ecitygml.dart';
import 'package:test/test.dart';

import '../helpers.dart' as shared;

/// Reads the file at `path`.
CityModel readPath(String path) => GmlReader.fromPath(path).finish();

List<FeatureType> featureTypes(CityModel cityModel) =>
    shared.items(cityModel.iterFeatures()).map((feature) => feature.featureType()).toList();

/// Matches a function throwing an error of `kind` whose message contains `part`.
Matcher throwsError(ErrorKind kind, String part) =>
    throwsA(isA<Error>().having((e) => e.kind(), 'kind', kind).having((e) => e.message(), 'message', contains(part)));
