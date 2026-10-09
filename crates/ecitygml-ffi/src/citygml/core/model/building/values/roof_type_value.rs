//! `RoofTypeValue`, mirroring `ecitygml::model::building::values::RoofTypeValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        RoofTypeValue,
        ecitygml::model::building::values::RoofTypeValue,
        "The `roofType` property of a Building or BuildingPart."
    );
}

pub use ffi::RoofTypeValue;
