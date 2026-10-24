# Reader

Cases of `GmlReader`. "FZK LoD1" is `<fixtures>/fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml`, "FZK LoD2" its
LoD2 sibling.

## `reader_from_bytes`

`GmlReader::new` with the bytes of FZK LoD1 and `CitygmlFormat::Gml`, then `finish`: 1 city object.

## `reader_compressed`

`<fixtures>/fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml.gz` and `….gml.zst` (FZK LoD1, compressed with `gzip` and
`zstd`):

- `from_path` (the format follows from the extension), then `finish`: 1 city object each.
- `GmlReader::new` with their bytes and `GmlGz` / `GmlZst`, then `finish`: 1 city object each.

## `reader_default_rebuilds_object_bounds`

FZK LoD2 read without options: each of the 4 wall surfaces has a `bounded_by` (`with_rebuild_object_bounds` defaults to
`true`; for `false` see the conformance case `lod2_object_bounds`).

## `reader_finish_once`

Suites: all except Rust (`finish` takes the reader by value).

`from_path` of FZK LoD1, `with_rebuild_object_bounds(false)`, `finish`: 1 city object; a second `finish` fails with
`InvalidArgument`, message containing `already finished`.

## `reader_missing_file`

Suites: all except TypeScript (no file system).

`from_path("<fixtures>/does-not-exist.gml")` fails with `Io`, message containing `No such file`.

## `reader_unsupported_extension`

`from_path("<fixtures>/README.md")` fails with `InvalidArgument`, message containing `md`. TypeScript too: the extension
is checked before the file is opened.

## `reader_non_utf8_path`

Suites: Rust FFI, C, C++, .NET (the others pass paths as strings, which are valid UTF-8).

`from_path` with the bytes `\xff.gml` fails with `InvalidArgument`, message containing `` `path` ``.

## `reader_invalid_content`

`<fixtures>/invalid/unclosed-tag.gml` (the text `<no-citygml`): `from_path` succeeds, as the content is only read by
`finish`; `finish` fails with `Parse`, message containing `tag not closed`.

## `reader_without_file_system`

Suites: TypeScript.

`from_path` of FZK LoD1 fails with `Io`, message containing `operation not supported on this platform`.
