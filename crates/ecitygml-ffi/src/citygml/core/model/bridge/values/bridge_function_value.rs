//! `BridgeFunctionValue`, mirroring `ecitygml::model::bridge::values::BridgeFunctionValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        BridgeFunctionValue,
        ecitygml::model::bridge::values::BridgeFunctionValue,
        "The `function` property of a Bridge or BridgePart."
    );
    code_list_value_iterator!(
        BridgeFunctionValueIterator,
        BridgeFunctionValue,
        ecitygml::model::bridge::values::BridgeFunctionValue
    );
}

pub use ffi::{BridgeFunctionValue, BridgeFunctionValueIterator};
