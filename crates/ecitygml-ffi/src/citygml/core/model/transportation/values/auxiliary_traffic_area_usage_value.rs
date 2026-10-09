//! `AuxiliaryTrafficAreaUsageValue`, mirroring `ecitygml::model::transportation::values::AuxiliaryTrafficAreaUsageValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        AuxiliaryTrafficAreaUsageValue,
        ecitygml::model::transportation::values::AuxiliaryTrafficAreaUsageValue,
        "The `usage` property of an AuxiliaryTrafficArea."
    );
    code_list_value_iterator!(
        AuxiliaryTrafficAreaUsageValueIterator,
        AuxiliaryTrafficAreaUsageValue,
        ecitygml::model::transportation::values::AuxiliaryTrafficAreaUsageValue
    );
}

pub use ffi::{AuxiliaryTrafficAreaUsageValue, AuxiliaryTrafficAreaUsageValueIterator};
