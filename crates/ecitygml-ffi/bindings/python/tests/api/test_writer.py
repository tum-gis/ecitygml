"""The cases of crates/ecitygml/tests/api/writer.md.

Python has no in-memory writer (`GmlWriter(format)` and `data()` aren't bound): where a case writes to memory, it
writes a file with `from_path`.
"""

from pathlib import Path

import pytest

from api.helpers import assert_error, assert_reads_back, feature_types, fixture
from conftest import read_model
from ecitygml import CitygmlFormat, CityModel, ErrorKind, Formatting, GmlWriter, LinearRing, Polygon, WallSurface


@pytest.fixture(scope="module")
def model() -> CityModel:
    return read_model(fixture("fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml"))


def write(city_model: CityModel, path: Path, formatting: Formatting | None = None) -> None:
    writer = GmlWriter.from_path(str(path))
    if formatting is not None:
        writer.with_formatting(formatting)
    writer.finish(city_model)


def text(city_model: CityModel, tmp_path: Path, formatting: Formatting | None = None) -> str:
    """The model written as `Gml` text."""
    path = tmp_path / "out.gml"
    write(city_model, path, formatting)
    return path.read_text()


def test_writer_files(model: CityModel, tmp_path: Path) -> None:
    for name in ["out.gml", "out.gml.gz", "out.gml.zst"]:
        write(model, tmp_path / name)
        assert_reads_back(str(tmp_path / name), model)


def test_writer_overwrites_file(model: CityModel, tmp_path: Path) -> None:
    path = tmp_path / "out.gml"
    path.write_text("x" * 100_000)
    write(model, path)
    assert_reads_back(str(path), model)


def test_writer_base_path_with_format(model: CityModel, tmp_path: Path) -> None:
    (tmp_path / "out.gml.gz").write_text("x" * 100_000)
    GmlWriter.from_base_path_with_format(str(tmp_path / "out"), CitygmlFormat.GmlGz).finish(model)
    assert_reads_back(str(tmp_path / "out.gml.gz"), model)


def test_writer_formatting(model: CityModel, tmp_path: Path) -> None:
    default = text(model, tmp_path)
    lines = default.splitlines()
    assert len(lines) > 1
    assert not any(line.startswith((" ", "\t")) for line in lines)
    assert text(model, tmp_path, Formatting.new_line()) == default
    assert text(model, tmp_path, Formatting.indent(ord(" "), 0)) == default

    compact = text(model, tmp_path, Formatting.compact())
    assert len(compact.splitlines()) < len(lines)

    spaces = text(model, tmp_path, Formatting.indent(ord(" "), 2)).splitlines()
    assert any(line.startswith("  <") for line in spaces)
    assert not any(line.startswith("\t") for line in spaces)

    tabs = text(model, tmp_path, Formatting.indent(ord("\t"), 1))
    assert any(line.startswith("\t<") for line in tabs.splitlines())
    assert feature_types(read_model(tmp_path / "out.gml")) == feature_types(model)


def test_writer_finish_once(model: CityModel, tmp_path: Path) -> None:
    writer = GmlWriter.from_path(str(tmp_path / "out.gml"))
    writer.finish(model)
    with pytest.raises(Exception) as raised:
        writer.finish(model)
    assert_error(raised, ErrorKind.InvalidArgument, "already finished")


def test_writer_unsupported_extension(tmp_path: Path) -> None:
    with pytest.raises(Exception) as raised:
        GmlWriter.from_path(str(tmp_path / "out.txt"))
    assert_error(raised, ErrorKind.InvalidArgument, "txt")


def test_writer_missing_directory(tmp_path: Path) -> None:
    with pytest.raises(Exception) as raised:
        GmlWriter.from_path(str(tmp_path / "missing" / "out.gml"))
    assert_error(raised, ErrorKind.Io, "")


def test_writer_rejects_non_model(tmp_path: Path) -> None:
    writer = GmlWriter.from_path(str(tmp_path / "out.gml"))
    with pytest.raises(TypeError):
        writer.finish("not a model")  # type: ignore[arg-type]


FZK_LOD2 = fixture("fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml")


def test_writer_keeps_references(tmp_path: Path) -> None:
    written = text(read_model(FZK_LOD2), tmp_path)
    assert written.count('xlink:href="#PolyID7350_878_759628_120742"') == 1
    assert written.count('gml:id="PolyID7350_878_759628_120742"') == 1


def wall_coordinates(city_model: CityModel) -> list[tuple[float, float, float]]:
    """The exterior ring positions of every polygon of the wall surfaces' LoD2 multi surfaces, in document order."""
    result = []
    for wall in (w for f in city_model.iter_features() if (w := WallSurface.try_from(f)) is not None):
        if wall.lod2_multi_surface() is None:
            continue
        for member in wall.lod2_multi_surface().object().surface_member():
            polygon = Polygon.try_from(member.object())
            if polygon is not None:
                result.extend((p.x(), p.y(), p.z()) for p in LinearRing.try_from(polygon.exterior()).points())
    return result


def test_writer_preserves_coordinates(tmp_path: Path) -> None:
    model = read_model(FZK_LOD2)
    path = tmp_path / "out.gml"
    write(model, path)
    coordinates = wall_coordinates(model)
    assert coordinates
    assert wall_coordinates(read_model(path)) == coordinates
