# API

The API suite: the same behaviour tests in every implementation, i.e. the Rust library, its FFI API and each binding.
Where the [conformance suite](../conformance/README.md) checks what a fixture contains, this suite checks how the API
behaves: reading and writing, errors, conversions, ownership. One case list per API area (`<area>.md` in this folder)
defines the cases; every suite implements exactly the cases scoped to it, nothing more and nothing less.
`mise run check:cases` enforces it ([`case_list_check.rs`](../case_list_check.rs), also part of `cargo test`).

## Suites

The suites and their file names are those of the conformance suite, in an `api/` folder (.NET: `Api/`) next to
`conformance/`, with the area in place of the dataset: `reader.rs`, `test_reader.c`, `test_reader.py`,
`reader.test.ts`, `ReaderTest.kt`, `ReaderTests.cs`, `reader_test.dart`.

## Rules

The [conformance rules](../conformance/README.md#rules) apply, with two differences:

- **Scoped cases.** A case runs in every suite unless its first line is `Suites:` followed by the suites that run it
  (`Suites: Rust FFI, C, C++, .NET`) or by `all except` and the suites that don't (`Suites: all except Rust`), with
  the reason. Behaviour only some languages have (an in-memory writer, a file system, dynamic typing) is a scoped
  case, never an unlisted test.
- **Inputs.** Cases read the files in [`tests/fixtures`](../../../../tests/fixtures), so every suite reads the same
  bytes; no suite builds its own input. Besides real data, that includes compressed copies of a fixture and the
  hand-written invalid input in [`tests/fixtures/invalid`](../../../../tests/fixtures/invalid).

## Conventions

These hold for every case list:

- `<fixtures>` is `tests/fixtures`, `<tmp>` a fresh temporary directory.
- **Errors.** A case names the `ErrorKind` and a part of the message. Each suite asserts them in its own idiom: a
  `Result` in Rust FFI and C++, an error result in C, the exception carrying the `Error` in Python, Kotlin, .NET, Dart
  and TypeScript. Rust has `ecitygml::io::Error` instead, mapped as the FFI maps it
  ([`error.rs`](../../../ecitygml-ffi/src/error.rs)): `Io` is `StdIo`, `InvalidArgument` is `InvalidFileExtension`,
  `Parse` is any other variant; the message is its `Display`. Outside reading and writing, Rust has
  `ecitygml::Error` or `egml::Error`, mapped likewise: an unresolved surface or curve reference is
  `UnresolvedReference`, anything else `InvalidArgument`.
- **"1 city object"** is `city_objects_len` (bindings) / `city_object_members_len` (Rust).
- **TypeScript** runs in WebAssembly, which has no file system: where a case reads a file, the test reads its bytes
  (Node) and passes them to `GmlReader::new` with the format of the file's extension. Cases that need the library to
  open files are scoped out of TypeScript.
