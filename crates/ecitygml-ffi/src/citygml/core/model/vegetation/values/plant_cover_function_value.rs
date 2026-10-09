//! `PlantCoverFunctionValue`, mirroring `ecitygml::model::vegetation::values::PlantCoverFunctionValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        PlantCoverFunctionValue,
        ecitygml::model::vegetation::values::PlantCoverFunctionValue,
        "The `function` property of a PlantCover."
    );
    code_list_value_iterator!(
        PlantCoverFunctionValueIterator,
        PlantCoverFunctionValue,
        ecitygml::model::vegetation::values::PlantCoverFunctionValue
    );
}

pub use ffi::PlantCoverFunctionValue;
