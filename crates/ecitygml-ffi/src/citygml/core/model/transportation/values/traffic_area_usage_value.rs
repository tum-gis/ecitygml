//! `TrafficAreaUsageValue`, mirroring `ecitygml::model::transportation::values::TrafficAreaUsageValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        TrafficAreaUsageValue,
        ecitygml::model::transportation::values::TrafficAreaUsageValue,
        "The `usage` property of a TrafficArea."
    );
    code_list_value_iterator!(
        TrafficAreaUsageValueIterator,
        TrafficAreaUsageValue,
        ecitygml::model::transportation::values::TrafficAreaUsageValue
    );
}

pub use ffi::{TrafficAreaUsageValue, TrafficAreaUsageValueIterator};
