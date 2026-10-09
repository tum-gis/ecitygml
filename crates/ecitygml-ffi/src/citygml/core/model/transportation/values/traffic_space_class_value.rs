//! `TrafficSpaceClassValue`, mirroring `ecitygml::model::transportation::values::TrafficSpaceClassValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        TrafficSpaceClassValue,
        ecitygml::model::transportation::values::TrafficSpaceClassValue,
        "The `class` property of a TrafficSpace."
    );
}

pub use ffi::TrafficSpaceClassValue;
