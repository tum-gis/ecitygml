//! `BuildingSubdivisionClassValue`, mirroring `ecitygml::model::building::values::BuildingSubdivisionClassValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        BuildingSubdivisionClassValue,
        ecitygml::model::building::values::BuildingSubdivisionClassValue,
        "The `class` property of a Storey or BuildingUnit (AbstractBuildingSubdivision)."
    );
}

pub use ffi::BuildingSubdivisionClassValue;
