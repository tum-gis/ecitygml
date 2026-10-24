"""Shared by the conformance and API suites: the fixtures folder and reading a city model."""

from pathlib import Path

from ecitygml import CityModel, GmlReader

FIXTURES = Path(__file__).parents[5] / "tests" / "fixtures"


def read_model(path: Path | str) -> CityModel:
    """`GmlReader::from_path(path)?.finish()`, as in Rust."""
    return GmlReader.from_path(str(path)).finish()
