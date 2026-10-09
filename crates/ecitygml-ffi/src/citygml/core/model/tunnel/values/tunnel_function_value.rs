//! `TunnelFunctionValue`, mirroring `ecitygml::model::tunnel::values::TunnelFunctionValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        TunnelFunctionValue,
        ecitygml::model::tunnel::values::TunnelFunctionValue,
        "The `function` property of a Tunnel or TunnelPart."
    );
    code_list_value_iterator!(
        TunnelFunctionValueIterator,
        TunnelFunctionValue,
        ecitygml::model::tunnel::values::TunnelFunctionValue
    );
}

pub use ffi::{TunnelFunctionValue, TunnelFunctionValueIterator};
