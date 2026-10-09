"""The code-list getters of AbstractBuilding and the `Code` they wrap.

Ported from the former PyO3 bindings' `test_code_lists.py`. Not ported (not in the Diplomat
bindings): `str`, `repr` and `==` of `Code`. Code-list values (e.g. `BuildingClassValue`) mirror
Rust: `value()` is the code's value, `code()` the `Code` with its code space.
"""

from conftest import FZK_LOD2, features_of, read_model
from ecitygml import Building, Code

SIG3D = "http://www.sig3d.org/codelists/citygml/2.0/building/2.0/_AbstractBuilding_"


class TestAbstractBuilding:
    def test_class_with_code_space(self, fzk_lod2_building: Building) -> None:
        class_ = fzk_lod2_building.class_()
        assert class_ is not None
        assert class_.value() == "1000"
        assert class_.code().code_space() == SIG3D + "class.xml"
        assert isinstance(class_.code(), Code)

    def test_functions_and_usages(self, fzk_lod2_building: Building) -> None:
        functions = [(f.code().value(), f.code().code_space()) for f in fzk_lod2_building.functions()]
        assert functions == [("1000", SIG3D + "function.xml")]
        usages = [(u.code().value(), u.code().code_space()) for u in fzk_lod2_building.usages()]
        assert usages == [("1000", SIG3D + "usage.xml")]

    def test_roof_type(self, fzk_lod2_building: Building) -> None:
        roof_type = fzk_lod2_building.roof_type()
        assert roof_type is not None
        assert roof_type.value() == "1030"

    def test_storeys(self, fzk_lod2_building: Building, tum_building: Building) -> None:
        assert fzk_lod2_building.storeys_above_ground() == 2
        assert fzk_lod2_building.storeys_below_ground() == 0
        assert tum_building.storeys_above_ground() == 4
        assert tum_building.storeys_below_ground() is None

    def test_code_without_code_space(self, tum_building: Building) -> None:
        assert tum_building.class_() is None
        functions = [(f.code().value(), f.code().code_space()) for f in tum_building.functions()]
        assert functions == [("31001_3020", None)]
        assert list(tum_building.usages()) == []


def test_buildings_read_twice_have_equal_codes(fzk_lod2_model: object) -> None:
    # Archived `TestCode.test_equality` compared `Code`s with `==`; here their fields are compared.
    again_model = read_model(FZK_LOD2)
    first = features_of(fzk_lod2_model, Building)[0].class_().code()
    again = features_of(again_model, Building)[0].class_().code()
    assert (first.value(), first.code_space()) == (again.value(), again.code_space())
