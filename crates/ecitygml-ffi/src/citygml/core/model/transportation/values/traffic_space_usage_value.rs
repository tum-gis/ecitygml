//! `TrafficSpaceUsageValue`, mirroring `ecitygml::model::transportation::values::TrafficSpaceUsageValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        TrafficSpaceUsageValue,
        ecitygml::model::transportation::values::TrafficSpaceUsageValue,
        "The `usage` property of a TrafficSpace."
    );
    code_list_value_iterator!(
        TrafficSpaceUsageValueIterator,
        TrafficSpaceUsageValue,
        ecitygml::model::transportation::values::TrafficSpaceUsageValue
    );
}

pub use ffi::{TrafficSpaceUsageValue, TrafficSpaceUsageValueIterator};
