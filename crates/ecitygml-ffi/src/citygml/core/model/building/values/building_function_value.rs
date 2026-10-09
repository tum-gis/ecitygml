//! `BuildingFunctionValue`, mirroring `ecitygml::model::building::values::BuildingFunctionValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        BuildingFunctionValue,
        ecitygml::model::building::values::BuildingFunctionValue,
        "The `function` property of a Building or BuildingPart."
    );
    code_list_value_iterator!(
        BuildingFunctionValueIterator,
        BuildingFunctionValue,
        ecitygml::model::building::values::BuildingFunctionValue
    );
}

pub use ffi::{BuildingFunctionValue, BuildingFunctionValueIterator};
