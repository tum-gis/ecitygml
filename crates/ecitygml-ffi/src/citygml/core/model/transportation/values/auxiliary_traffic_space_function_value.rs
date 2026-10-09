//! `AuxiliaryTrafficSpaceFunctionValue`, mirroring `ecitygml::model::transportation::values::AuxiliaryTrafficSpaceFunctionValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        AuxiliaryTrafficSpaceFunctionValue,
        ecitygml::model::transportation::values::AuxiliaryTrafficSpaceFunctionValue,
        "The `function` property of an AuxiliaryTrafficSpace."
    );
    code_list_value_iterator!(
        AuxiliaryTrafficSpaceFunctionValueIterator,
        AuxiliaryTrafficSpaceFunctionValue,
        ecitygml::model::transportation::values::AuxiliaryTrafficSpaceFunctionValue
    );
}

pub use ffi::{AuxiliaryTrafficSpaceFunctionValue, AuxiliaryTrafficSpaceFunctionValueIterator};
