# Writer

Cases of `GmlWriter` and `Formatting`. "The model" is `<fixtures>/fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml`;
"reads back" means that reading what was written gives the model's `iter_features` feature types in the same order
(the conformance case `lod3_round_trip` checks the content).

- **Rust** writes to memory with `GmlWriter::new(&mut Vec<u8>, format)`; the vector is the data. Its `Formatting` is
  the enum `egml::io::util::Formatting`: `new_line()` is `NewLine`, `compact()` `Compact`, `indent(c, n)`
  `Indent { .. }`.
- **Python** has no in-memory writer (`GmlWriter::new` and `data` aren't bound, see the bridge): where a case writes
  to memory, it writes `<tmp>/out.gml` with `from_path` and reads that file.

## `writer_in_memory`

Suites: all except Python (no in-memory writer).

For `Gml`, `GmlGz` and `GmlZst`, `GmlWriter::new(format)`: `data` is empty before `finish`; after `finish(model)` it
reads back with `GmlReader::new(data, format)`. The `Gml` data contains `<bldg:Building`.

## `writer_files`

Suites: all except TypeScript (no file system).

`from_path` for `<tmp>/out.gml`, `<tmp>/out.gml.gz` and `<tmp>/out.gml.zst` (the format follows from the extension),
then `finish(model)`: each file reads back with `from_path`.

## `writer_overwrites_file`

Suites: all except TypeScript (no file system).

`<tmp>/out.gml` holds 100 000 × `x`; `from_path` and `finish(model)` replace it: the file reads back.

## `writer_base_path_with_format`

Suites: all except TypeScript (no file system).

`<tmp>/out.gml.gz` holds 100 000 × `x`; `from_base_path_with_format("<tmp>/out", GmlGz)` and `finish(model)` replace
it: the file reads back.

## `writer_formatting`

The model written as `Gml` text:

- Default (no `with_formatting`): more than one line, no line starts with a space or a tab.
- `Formatting::new_line()` and `Formatting::indent(b' ', 0)`: the same text as the default.
- `Formatting::compact()`: fewer lines than the default.
- `Formatting::indent(b' ', 2)`: a line starts with `  <`, none with a tab.
- `Formatting::indent(b'\t', 1)`: a line starts with `\t<`; the text reads back.

## `writer_keeps_references`

`<fixtures>/fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml`, whose solid references the wall polygons by
`xlink:href`, written as `Gml` text: it contains `xlink:href="#PolyID7350_878_759628_120742"` exactly once (the
reference isn't resolved into a copy) and `gml:id="PolyID7350_878_759628_120742"` exactly once.

## `writer_preserves_coordinates`

The same LoD2 file written as `Gml` and read back: the exterior ring positions (x, y, z) of every polygon of the wall
surfaces' `lod2_multi_surface` are the same as read, in document order.

## `writer_finish_once`

Suites: all except Rust (`finish` takes the writer by value).

After `finish(model)`, a second `finish(model)` fails with `InvalidArgument`, message containing `already finished`.

## `writer_unsupported_extension`

`from_path("<tmp>/out.txt")` fails with `InvalidArgument`, message containing `txt`. TypeScript too: the extension is
checked before the file is created.

## `writer_missing_directory`

Suites: all except TypeScript (no file system).

`from_path("<tmp>/missing/out.gml")` fails with `Io`.

## `writer_without_file_system`

Suites: TypeScript.

`from_path("out.gml")` fails with `Io`, message containing `operation not supported on this platform`.

## `writer_rejects_non_model`

Suites: Python (dynamically typed; elsewhere the compiler rejects it).

`finish("not a model")` raises `TypeError`.
