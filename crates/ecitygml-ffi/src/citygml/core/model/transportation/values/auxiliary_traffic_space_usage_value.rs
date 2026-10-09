//! `AuxiliaryTrafficSpaceUsageValue`, mirroring `ecitygml::model::transportation::values::AuxiliaryTrafficSpaceUsageValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        AuxiliaryTrafficSpaceUsageValue,
        ecitygml::model::transportation::values::AuxiliaryTrafficSpaceUsageValue,
        "The `usage` property of an AuxiliaryTrafficSpace."
    );
    code_list_value_iterator!(
        AuxiliaryTrafficSpaceUsageValueIterator,
        AuxiliaryTrafficSpaceUsageValue,
        ecitygml::model::transportation::values::AuxiliaryTrafficSpaceUsageValue
    );
}

pub use ffi::{AuxiliaryTrafficSpaceUsageValue, AuxiliaryTrafficSpaceUsageValueIterator};
