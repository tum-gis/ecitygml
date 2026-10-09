"""Writing city models with `GmlWriter`.

Ported from the former PyO3 bindings' `test_writer.py`. `write(model, path, indent=...)` is
`GmlWriter.from_path(path)`, `with_formatting(...)` and `finish(model)`, as in Rust; `indent=None`
is `Formatting.compact()`, `indent=2` is `Formatting.indent(ord(" "), 2)`. Not ported (not in the
Diplomat bindings): validating the indent (Rust takes any byte), keyword-only options, the path in
the missing-directory error. Not in Python: writing to memory (`GmlWriter(format)`, `data()`),
which the other languages have.
"""

from pathlib import Path
from typing import Any

import pytest

from conftest import ASAM_JUNCTION, FZK_LOD2, features_of, polygons, read_model, unwrap
from ecitygml import (
    Building,
    CityModel,
    DoorSurface,
    ErrorKind,
    Formatting,
    GmlReader,
    GmlWriter,
    GroundSurface,
    LinearRing,
    Road,
    RoofSurface,
    TrafficSpace,
    WallSurface,
    WindowSurface,
)

FEATURE_CLASSES = [Building, WallSurface, RoofSurface, GroundSurface, DoorSurface, WindowSurface]


def write(model: CityModel, path: Path | str, formatting: Formatting | None = None) -> None:
    writer = GmlWriter.from_path(str(path))
    if formatting is not None:
        writer.with_formatting(formatting)
    writer.finish(model)


def feature_ids(model: CityModel) -> list[str]:
    """The ids of the model's features (not the city model's, which the reader generates anew)."""
    ids = []
    for feature in model.iter_features():
        for cls in FEATURE_CLASSES:
            if (typed := cls.try_from(feature)) is not None:
                ids.append(typed.id().as_str())
    return ids


def wall_coordinates(model: CityModel) -> list[list[tuple[float, float, float]]]:
    """Exterior ring coordinates of every LoD2 wall polygon, in document order."""
    return [
        [(p.x(), p.y(), p.z()) for p in LinearRing.try_from(polygon.exterior()).points()]
        for wall in features_of(model, WallSurface)
        if wall.lod2_multi_surface() is not None
        for polygon in polygons(unwrap(wall.lod2_multi_surface()))
        if polygon.exterior() is not None
    ]


class TestRoundTrip:
    @pytest.mark.parametrize("suffix", [".gml", ".gml.gz", ".gml.zst"])
    def test_preserves_features(self, fzk_lod3_model: CityModel, tmp_path: Path, suffix: str) -> None:
        path = tmp_path / f"out{suffix}"
        write(fzk_lod3_model, path)
        assert feature_ids(read_model(path)) == feature_ids(fzk_lod3_model)

    def test_preserves_geometry(self, tmp_path: Path) -> None:
        path = tmp_path / "out.gml"
        model = read_model(FZK_LOD2)
        write(model, path)
        assert wall_coordinates(read_model(path)) == wall_coordinates(model)

    def test_preserves_transportation(self, tmp_path: Path) -> None:
        path = tmp_path / "out.gml"
        model = read_model(ASAM_JUNCTION)
        write(model, path)
        written = read_model(path)
        assert len(features_of(written, Road)) == 1
        assert len(features_of(written, TrafficSpace)) == len(features_of(model, TrafficSpace))

    def test_accepts_str_path(self, fzk_lod3_model: CityModel, tmp_path: Path) -> None:
        path = tmp_path / "out.gml"
        write(fzk_lod3_model, str(path))
        assert len(features_of(read_model(path), WallSurface)) == 4

    def test_overwrites_existing_file(self, fzk_lod3_model: CityModel, tmp_path: Path) -> None:
        path = tmp_path / "out.gml"
        path.write_text("x" * 10_000_000)
        write(fzk_lod3_model, path)
        assert feature_ids(read_model(path)) == feature_ids(fzk_lod3_model)


class TestIndent:
    def write_text(self, model: CityModel, tmp_path: Path, formatting: Formatting | None = None) -> str:
        path = tmp_path / "out.gml"
        write(model, path, formatting)
        return path.read_text()

    def test_default_puts_elements_on_lines_without_indentation(
        self, fzk_lod3_model: CityModel, tmp_path: Path
    ) -> None:
        lines = self.write_text(fzk_lod3_model, tmp_path).splitlines()
        assert len(lines) > 1
        assert not any(line.startswith((" ", "\t")) for line in lines)

    @pytest.mark.parametrize("formatting", ["indent_zero", "new_line"])
    def test_zero_and_empty_match_default(
        self, fzk_lod3_model: CityModel, tmp_path: Path, formatting: str
    ) -> None:
        # Archived as `indent=0` and `indent=""`.
        chosen = Formatting.indent(ord(" "), 0) if formatting == "indent_zero" else Formatting.new_line()
        default = self.write_text(fzk_lod3_model, tmp_path)
        assert self.write_text(fzk_lod3_model, tmp_path, chosen) == default

    def test_none_is_compact(self, fzk_lod3_model: CityModel, tmp_path: Path) -> None:
        compact = self.write_text(fzk_lod3_model, tmp_path, Formatting.compact())
        default = self.write_text(fzk_lod3_model, tmp_path)
        assert len(compact.splitlines()) < len(default.splitlines())

    def test_int_indents_with_spaces(self, fzk_lod3_model: CityModel, tmp_path: Path) -> None:
        lines = self.write_text(fzk_lod3_model, tmp_path, Formatting.indent(ord(" "), 2)).splitlines()
        assert any(line.startswith("  <") for line in lines)
        assert not any(line.startswith("\t") for line in lines)

    def test_str_indents_with_that_string(self, fzk_lod3_model: CityModel, tmp_path: Path) -> None:
        lines = self.write_text(fzk_lod3_model, tmp_path, Formatting.indent(ord("\t"), 1)).splitlines()
        assert any(line.startswith("\t<") for line in lines)

    def test_indented_output_reads_back(self, fzk_lod3_model: CityModel, tmp_path: Path) -> None:
        path = tmp_path / "out.gml"
        write(fzk_lod3_model, path, Formatting.indent(ord(" "), 4))
        assert feature_ids(read_model(path)) == feature_ids(fzk_lod3_model)


def error_kind(raised: pytest.ExceptionInfo[Any]) -> ErrorKind:
    return raised.value.args[0].kind()


class TestErrors:
    def test_unknown_extension_raises(self, tmp_path: Path) -> None:
        with pytest.raises(Exception, match="txt") as raised:
            GmlWriter.from_path(str(tmp_path / "out.txt"))
        assert error_kind(raised) == ErrorKind.InvalidArgument

    def test_missing_directory_raises_io_error(self, tmp_path: Path) -> None:
        # The former bindings' message named the path; the error here only has the OS message.
        with pytest.raises(Exception) as raised:
            GmlWriter.from_path(str(tmp_path / "missing" / "out.gml"))
        assert error_kind(raised) == ErrorKind.Io

    def test_rejects_non_model(self, tmp_path: Path) -> None:
        writer = GmlWriter.from_path(str(tmp_path / "out.gml"))
        with pytest.raises(TypeError):
            writer.finish("not a model")  # type: ignore[arg-type]

    def test_read_unknown_extension_raises(self, tmp_path: Path) -> None:
        path = tmp_path / "in.txt"
        path.write_text("")
        with pytest.raises(Exception, match="txt") as raised:
            GmlReader.from_path(str(path))
        assert error_kind(raised) == ErrorKind.InvalidArgument
