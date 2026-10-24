"""The cases of crates/ecitygml/tests/api/reader.md."""

from pathlib import Path

import pytest

from api.helpers import assert_error, fixture
from conftest import read_model
from ecitygml import CitygmlFormat, ErrorKind, GmlReader, WallSurface

FZK_LOD1 = fixture("fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml")
FZK_LOD2 = fixture("fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml")


def test_reader_from_bytes() -> None:
    data = Path(FZK_LOD1).read_bytes()
    assert GmlReader(data, CitygmlFormat.Gml).finish().city_objects_len() == 1


def test_reader_compressed() -> None:
    for extension, format in [("gz", CitygmlFormat.GmlGz), ("zst", CitygmlFormat.GmlZst)]:
        path = fixture(f"fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml.{extension}")
        assert read_model(path).city_objects_len() == 1, path
        assert GmlReader(Path(path).read_bytes(), format).finish().city_objects_len() == 1, path


def test_reader_default_rebuilds_object_bounds() -> None:
    city_model = read_model(FZK_LOD2)
    walls = [w for f in city_model.iter_features() if (w := WallSurface.try_from(f)) is not None]
    assert [wall.bounded_by() is not None for wall in walls] == [True] * 4


def test_reader_finish_once() -> None:
    reader = GmlReader.from_path(FZK_LOD1)
    reader.with_rebuild_object_bounds(False)
    assert reader.finish().city_objects_len() == 1
    with pytest.raises(Exception) as raised:
        reader.finish()
    assert_error(raised, ErrorKind.InvalidArgument, "already finished")


def test_reader_missing_file() -> None:
    with pytest.raises(Exception) as raised:
        GmlReader.from_path(fixture("does-not-exist.gml"))
    assert_error(raised, ErrorKind.Io, "No such file")


def test_reader_unsupported_extension() -> None:
    with pytest.raises(Exception) as raised:
        GmlReader.from_path(fixture("README.md"))
    assert_error(raised, ErrorKind.InvalidArgument, "md")


def test_reader_invalid_content() -> None:
    reader = GmlReader.from_path(fixture("invalid/unclosed-tag.gml"))
    with pytest.raises(Exception) as raised:
        reader.finish()
    assert_error(raised, ErrorKind.Parse, "tag not closed")
