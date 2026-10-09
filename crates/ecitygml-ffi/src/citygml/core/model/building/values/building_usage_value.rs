//! `BuildingUsageValue`, mirroring `ecitygml::model::building::values::BuildingUsageValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        BuildingUsageValue,
        ecitygml::model::building::values::BuildingUsageValue,
        "The `usage` property of a Building or BuildingPart."
    );
    code_list_value_iterator!(
        BuildingUsageValueIterator,
        BuildingUsageValue,
        ecitygml::model::building::values::BuildingUsageValue
    );
}

pub use ffi::{BuildingUsageValue, BuildingUsageValueIterator};
