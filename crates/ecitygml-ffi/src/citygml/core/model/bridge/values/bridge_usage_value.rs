//! `BridgeUsageValue`, mirroring `ecitygml::model::bridge::values::BridgeUsageValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        BridgeUsageValue,
        ecitygml::model::bridge::values::BridgeUsageValue,
        "The `usage` property of a Bridge or BridgePart."
    );
    code_list_value_iterator!(
        BridgeUsageValueIterator,
        BridgeUsageValue,
        ecitygml::model::bridge::values::BridgeUsageValue
    );
}

pub use ffi::{BridgeUsageValue, BridgeUsageValueIterator};
