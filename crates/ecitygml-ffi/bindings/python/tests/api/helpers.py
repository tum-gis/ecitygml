"""Helpers of the API suite (crates/ecitygml/tests/api/README.md)."""

from typing import Any

import pytest

from conftest import FIXTURES, read_model
from ecitygml import CityModel, Error, ErrorKind


def fixture(path: str) -> str:
    """`tests/fixtures/<path>`."""
    return str(FIXTURES / path)


def feature_types(city_model: CityModel) -> list[str]:
    """The `iter_features` feature types, as strings: two returned `FeatureType`s never compare equal."""
    return [str(feature.feature_type()) for feature in city_model.iter_features()]


def assert_reads_back(path: str, city_model: CityModel) -> None:
    assert feature_types(read_model(path)) == feature_types(city_model), path


def assert_error(raised: pytest.ExceptionInfo[Any], kind: ErrorKind, part: str) -> None:
    """Asserts the kind of the raised exception's `Error` and that its message contains `part`."""
    error = raised.value.args[0]
    assert isinstance(error, Error)
    assert error.kind() == kind
    assert part in str(error)
