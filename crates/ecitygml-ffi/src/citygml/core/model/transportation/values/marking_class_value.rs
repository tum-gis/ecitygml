//! `MarkingClassValue`, mirroring `ecitygml::model::transportation::values::MarkingClassValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        MarkingClassValue,
        ecitygml::model::transportation::values::MarkingClassValue,
        "The `class` property of a Marking."
    );
}

pub use ffi::MarkingClassValue;
