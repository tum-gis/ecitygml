//! `BuildingSubdivisionUsageValue`, mirroring `ecitygml::model::building::values::BuildingSubdivisionUsageValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        BuildingSubdivisionUsageValue,
        ecitygml::model::building::values::BuildingSubdivisionUsageValue,
        "The `usage` property of a Storey or BuildingUnit (AbstractBuildingSubdivision)."
    );
    code_list_value_iterator!(
        BuildingSubdivisionUsageValueIterator,
        BuildingSubdivisionUsageValue,
        ecitygml::model::building::values::BuildingSubdivisionUsageValue
    );
}

pub use ffi::{BuildingSubdivisionUsageValue, BuildingSubdivisionUsageValueIterator};
