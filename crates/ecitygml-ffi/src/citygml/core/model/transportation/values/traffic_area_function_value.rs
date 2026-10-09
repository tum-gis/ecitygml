//! `TrafficAreaFunctionValue`, mirroring `ecitygml::model::transportation::values::TrafficAreaFunctionValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        TrafficAreaFunctionValue,
        ecitygml::model::transportation::values::TrafficAreaFunctionValue,
        "The `function` property of a TrafficArea."
    );
    code_list_value_iterator!(
        TrafficAreaFunctionValueIterator,
        TrafficAreaFunctionValue,
        ecitygml::model::transportation::values::TrafficAreaFunctionValue
    );
}

pub use ffi::{TrafficAreaFunctionValue, TrafficAreaFunctionValueIterator};
