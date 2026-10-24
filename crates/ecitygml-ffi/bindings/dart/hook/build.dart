import 'dart:io';

import 'package:code_assets/code_assets.dart';
import 'package:hooks/hooks.dart';

/// Bundles the native library built by `cargo build -p ecitygml-ffi` (see `mise run build:bindings:dart`).
///
/// The library comes from `target/<profile>`, where the profile (`debug` or `release`) is read from
/// `target/bindings-dart/profile` (written by `mise run build:bindings:dart [--release]`), and is `debug` without it.
/// Hooks don't see the environment, so the profile can't be passed as an environment variable.
///
/// The asset id `package:ecitygml/src/lib.g.dart` is the library the generated `@Native` functions resolve against.
void main(List<String> args) async {
  await build(args, (input, output) async {
    if (!input.config.buildCodeAssets) {
      return;
    }
    final profileFile = input.packageRoot.resolve('../../../../target/bindings-dart/profile');
    final profile = File.fromUri(profileFile).existsSync()
        ? File.fromUri(profileFile).readAsStringSync().trim()
        : 'debug';
    if (profile != 'debug' && profile != 'release') {
      throw StateError('${profileFile.toFilePath()} must contain `debug` or `release`, not `$profile`.');
    }
    final fileName = input.config.code.targetOS.dylibFileName('ecitygml_ffi');
    final library = input.packageRoot.resolve('../../../../target/$profile/$fileName');
    if (!File.fromUri(library).existsSync()) {
      final flag = profile == 'release' ? ' --release' : '';
      throw StateError('${library.toFilePath()} not found: run `cargo build -p ecitygml-ffi$flag` first.');
    }
    output.assets.code.add(
      CodeAsset(package: input.packageName, name: 'src/lib.g.dart', linkMode: DynamicLoadingBundled(), file: library),
    );
    output.dependencies.add(library);
    output.dependencies.add(profileFile);
  });
}
