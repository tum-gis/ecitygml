//! `BuildingClassValue`, mirroring `ecitygml::model::building::values::BuildingClassValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        BuildingClassValue,
        ecitygml::model::building::values::BuildingClassValue,
        "The `class` property of a Building or BuildingPart."
    );
}

pub use ffi::BuildingClassValue;
