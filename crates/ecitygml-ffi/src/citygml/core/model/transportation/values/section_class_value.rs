//! `SectionClassValue`, mirroring `ecitygml::model::transportation::values::SectionClassValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        SectionClassValue,
        ecitygml::model::transportation::values::SectionClassValue,
        "The `class` property of a Section."
    );
}

pub use ffi::SectionClassValue;
