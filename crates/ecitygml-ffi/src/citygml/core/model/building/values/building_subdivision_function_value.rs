//! `BuildingSubdivisionFunctionValue`, mirroring `ecitygml::model::building::values::BuildingSubdivisionFunctionValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        BuildingSubdivisionFunctionValue,
        ecitygml::model::building::values::BuildingSubdivisionFunctionValue,
        "The `function` property of a Storey or BuildingUnit (AbstractBuildingSubdivision)."
    );
    code_list_value_iterator!(
        BuildingSubdivisionFunctionValueIterator,
        BuildingSubdivisionFunctionValue,
        ecitygml::model::building::values::BuildingSubdivisionFunctionValue
    );
}

pub use ffi::{BuildingSubdivisionFunctionValue, BuildingSubdivisionFunctionValueIterator};
