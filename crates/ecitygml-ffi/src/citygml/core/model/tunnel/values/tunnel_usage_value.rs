//! `TunnelUsageValue`, mirroring `ecitygml::model::tunnel::values::TunnelUsageValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        TunnelUsageValue,
        ecitygml::model::tunnel::values::TunnelUsageValue,
        "The `usage` property of a Tunnel or TunnelPart."
    );
    code_list_value_iterator!(
        TunnelUsageValueIterator,
        TunnelUsageValue,
        ecitygml::model::tunnel::values::TunnelUsageValue
    );
}

pub use ffi::{TunnelUsageValue, TunnelUsageValueIterator};
