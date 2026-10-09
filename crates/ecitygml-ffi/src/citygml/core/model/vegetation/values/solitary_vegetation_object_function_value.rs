//! `SolitaryVegetationObjectFunctionValue`, mirroring `ecitygml::model::vegetation::values::SolitaryVegetationObjectFunctionValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        SolitaryVegetationObjectFunctionValue,
        ecitygml::model::vegetation::values::SolitaryVegetationObjectFunctionValue,
        "The `function` property of a SolitaryVegetationObject."
    );
    code_list_value_iterator!(
        SolitaryVegetationObjectFunctionValueIterator,
        SolitaryVegetationObjectFunctionValue,
        ecitygml::model::vegetation::values::SolitaryVegetationObjectFunctionValue
    );
}

pub use ffi::SolitaryVegetationObjectFunctionValue;
