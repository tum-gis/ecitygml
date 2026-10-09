//! `TrafficSpaceFunctionValue`, mirroring `ecitygml::model::transportation::values::TrafficSpaceFunctionValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        TrafficSpaceFunctionValue,
        ecitygml::model::transportation::values::TrafficSpaceFunctionValue,
        "The `function` property of a TrafficSpace."
    );
    code_list_value_iterator!(
        TrafficSpaceFunctionValueIterator,
        TrafficSpaceFunctionValue,
        ecitygml::model::transportation::values::TrafficSpaceFunctionValue
    );
}

pub use ffi::{TrafficSpaceFunctionValue, TrafficSpaceFunctionValueIterator};
