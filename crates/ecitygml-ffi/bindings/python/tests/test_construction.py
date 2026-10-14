"""The AbstractConstruction getters and the types they return.

Ported from the former PyO3 bindings' `test_construction.py`. Not ported (not in the Diplomat
bindings): `repr`. Dates are `Date`s with `year()`/`month()`/`day()` instead of
`datetime.date`, and a `Height`'s value is its `length()` with `value()`/`uom()`.
"""

from pathlib import Path
from typing import Any

import pytest

from conftest import FZK_LOD2, features_of, read_model
from ecitygml import Building, GmlWriter, Height, HeightStatusValue, Occupancy

# Properties absent from the fixtures, injected into a copy of the FZK LoD2 building in the
# order of the CityGML 3.0 schema (AbstractConstructionType).
DATE_OF_CONSTRUCTION = "<con:dateOfConstruction>2020-01-01</con:dateOfConstruction>"
DATE_OF_DEMOLITION = DATE_OF_CONSTRUCTION + """
      <con:dateOfDemolition>2050-12-31</con:dateOfDemolition>"""
OCCUPANCY = """</con:height>
      <con:occupancy>
        <Occupancy>
          <numberOfOccupants>4</numberOfOccupants>
          <interval>daytime</interval>
          <occupantType>residents</occupantType>
        </Occupancy>
      </con:occupancy>"""


@pytest.fixture(scope="module")
def extended_model(tmp_path_factory: pytest.TempPathFactory) -> Any:
    tmp_path = tmp_path_factory.mktemp("construction")
    text = FZK_LOD2.read_text()
    for anchor, replacement in [(DATE_OF_CONSTRUCTION, DATE_OF_DEMOLITION), ("</con:height>", OCCUPANCY)]:
        assert text.count(anchor) == 1
        text = text.replace(anchor, replacement)
    path = tmp_path / "fzk_extended.gml"
    path.write_text(text)
    return read_model(path)


@pytest.fixture(scope="module")
def extended_building(extended_model: Any) -> Building:
    return features_of(extended_model, Building)[0]


def ymd(date: Any) -> tuple[int, int, int]:
    return (date.year(), date.month(), date.day())


class TestDates:
    def test_date_of_construction(self, fzk_lod2_building: Building) -> None:
        assert ymd(fzk_lod2_building.date_of_construction()) == (2020, 1, 1)

    def test_date_of_demolition_absent(self, fzk_lod2_building: Building) -> None:
        assert fzk_lod2_building.date_of_demolition() is None

    def test_date_of_demolition(self, extended_building: Building) -> None:
        assert ymd(extended_building.date_of_demolition()) == (2050, 12, 31)


class TestHeights:
    def test_fzk_height(self, fzk_lod2_building: Building) -> None:
        heights = list(fzk_lod2_building.heights())
        assert len(heights) == 1
        height = heights[0]
        assert isinstance(height, Height)
        assert height.high_reference().value() == "topOfConstruction"
        assert height.low_reference().value() == "lowestGroundPoint"
        assert height.status() == HeightStatusValue.Measured
        assert height.length().value() == pytest.approx(6.52)
        assert height.length().uom() == "m"

    def test_tum_height_uom(self, tum_building: Building) -> None:
        height = next(iter(tum_building.heights()))
        assert height.length().value() == pytest.approx(19.408)
        assert height.length().uom() == "urn:adv:uom:m"


class TestOccupancies:
    def test_absent(self, fzk_lod2_building: Building) -> None:
        assert list(fzk_lod2_building.occupancies()) == []

    def test_occupancy(self, extended_building: Building) -> None:
        occupancies = list(extended_building.occupancies())
        assert len(occupancies) == 1
        occupancy = occupancies[0]
        assert isinstance(occupancy, Occupancy)
        assert occupancy.number_of_occupants() == 4
        assert occupancy.interval() is not None and occupancy.interval().value() == "daytime"
        assert occupancy.occupant_type() is not None
        assert occupancy.occupant_type().value() == "residents"


def test_write_round_trip(extended_model: Any, tmp_path: Path) -> None:
    path = tmp_path / "written.gml"
    GmlWriter.from_path(str(path)).finish(extended_model)
    model = read_model(path)
    building = features_of(model, Building)[0]
    assert ymd(building.date_of_construction()) == (2020, 1, 1)
    assert ymd(building.date_of_demolition()) == (2050, 12, 31)
    heights = [(h.length().value(), h.length().uom(), h.status()) for h in building.heights()]
    assert heights == [(pytest.approx(6.52), "m", HeightStatusValue.Measured)]
    occupancies = [(o.number_of_occupants(), o.interval().value()) for o in building.occupancies()]
    assert occupancies == [(4, "daytime")]
