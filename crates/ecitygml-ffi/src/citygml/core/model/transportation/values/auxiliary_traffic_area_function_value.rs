//! `AuxiliaryTrafficAreaFunctionValue`, mirroring `ecitygml::model::transportation::values::AuxiliaryTrafficAreaFunctionValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        AuxiliaryTrafficAreaFunctionValue,
        ecitygml::model::transportation::values::AuxiliaryTrafficAreaFunctionValue,
        "The `function` property of an AuxiliaryTrafficArea."
    );
    code_list_value_iterator!(
        AuxiliaryTrafficAreaFunctionValueIterator,
        AuxiliaryTrafficAreaFunctionValue,
        ecitygml::model::transportation::values::AuxiliaryTrafficAreaFunctionValue
    );
}

pub use ffi::{AuxiliaryTrafficAreaFunctionValue, AuxiliaryTrafficAreaFunctionValueIterator};
