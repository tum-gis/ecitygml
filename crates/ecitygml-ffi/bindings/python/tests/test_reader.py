"""Reading with `GmlReader` and the CityModel getters.

Ported from the former PyO3 bindings' `test_reader.py`. Not ported (not in the Diplomat
bindings): `pathlib.Path` arguments, keyword-only options, `repr`. `read(path, rebuild_object_bounds=...)` is
`GmlReader.from_path(path)`, `with_rebuild_object_bounds(...)` and `finish()`, as in Rust; errors
are an `Exception` carrying the `Error` (with `kind()`), not `OSError`.
"""

import pytest

from conftest import ASAM_JUNCTION, FZK_LOD1, FZK_LOD2, features_of, read_model
from ecitygml import Building, CityModel, ErrorKind, GmlReader, Road, Scale3, Vector3, WallSurface


class TestRead:
    def test_returns_city_model(self) -> None:
        assert isinstance(read_model(FZK_LOD2), CityModel)

    def test_missing_file_raises_io_error(self) -> None:
        with pytest.raises(Exception) as raised:
            GmlReader.from_path("/nonexistent/path/file.gml").finish()
        # The former bindings' message named the path; the error here only has the OS message.
        assert raised.value.args[0].kind() == ErrorKind.Io

    def test_rebuilds_object_bounds_by_default(self) -> None:
        model = read_model(FZK_LOD2)
        assert features_of(model, WallSurface)[0].bounded_by() is not None

    def test_rebuild_object_bounds_disabled(self) -> None:
        reader = GmlReader.from_path(str(FZK_LOD2))
        reader.with_rebuild_object_bounds(False)
        model = reader.finish()
        assert features_of(model, WallSurface)[0].bounded_by() is None


class TestCityModel:
    def test_city_objects_len_fzk(self) -> None:
        assert read_model(FZK_LOD2).city_objects_len() == 1

    def test_city_objects_len_asam_junction(self) -> None:
        assert read_model(ASAM_JUNCTION).city_objects_len() == 1

    def test_buildings_returns_list(self) -> None:
        model = read_model(FZK_LOD2)  # keeps the buildings' model alive
        buildings = features_of(model, Building)
        assert isinstance(buildings, list)
        assert len(buildings) == 1

    def test_roads_returns_list(self) -> None:
        model = read_model(ASAM_JUNCTION)  # keeps the roads' model alive
        roads = features_of(model, Road)
        assert isinstance(roads, list)
        assert len(roads) == 1

    def test_empty_roads_for_building_file(self) -> None:
        assert features_of(read_model(FZK_LOD2), Road) == []

    def test_empty_buildings_for_road_file(self) -> None:
        assert features_of(read_model(ASAM_JUNCTION), Building) == []


def test_recompute_child_bounding_shapes() -> None:
    # The former test only checked that it doesn't raise; read without bounds to see the effect.
    reader = GmlReader.from_path(str(FZK_LOD2))
    reader.with_rebuild_object_bounds(False)
    model = reader.finish()
    model.recompute_child_bounding_shapes()
    assert all(w.bounded_by() is not None for w in features_of(model, WallSurface))


def test_apply_translation_and_scale() -> None:
    model = read_model(FZK_LOD1)
    lower = model.bounded_by().envelope().lower_corner()
    x, y, z = lower.x(), lower.y(), lower.z()

    model.apply_translation(Vector3(-100.0, 200.0, 10.0))
    lower = model.bounded_by().envelope().lower_corner()
    assert (lower.x(), lower.y(), lower.z()) == pytest.approx((x - 100.0, y + 200.0, z + 10.0))

    model.apply_scale(Scale3(2.0, 3.0, 0.5))
    envelope = model.bounded_by().envelope()
    assert (envelope.size_x(), envelope.size_y(), envelope.size_z()) == pytest.approx((24.0, 30.0, 6.517669 / 2))
