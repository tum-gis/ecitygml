"""Helpers of the conformance suite (crates/ecitygml/tests/conformance/README.md)."""

from typing import Any

import pytest

from conftest import FIXTURES, read_model
from ecitygml import AbstractFeatureKindRef, Building, CityModel

# The tolerance of floating point comparisons in the case lists.
TOLERANCE = 1e-6


def read(dataset: str, file: str) -> CityModel:
    """Reads `tests/fixtures/<dataset>/<file>`."""
    return read_model(FIXTURES / dataset / file)


def close(value: float) -> Any:
    return pytest.approx(value, abs=TOLERANCE)


def building(city_model: CityModel) -> Building:
    """The city model's first building."""
    return next(b for f in city_model.iter_features() if (b := Building.try_from(f)) is not None)


def boundaries(building: Building) -> list[AbstractFeatureKindRef]:
    """The building's boundaries, as features."""
    return [AbstractFeatureKindRef.from_space_boundary(p.object()) for p in building.boundaries()]


def first_name(feature: Any) -> str:
    return next(iter(feature.names())).value()
