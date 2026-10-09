//! `PlantCoverUsageValue`, mirroring `ecitygml::model::vegetation::values::PlantCoverUsageValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        PlantCoverUsageValue,
        ecitygml::model::vegetation::values::PlantCoverUsageValue,
        "The `usage` property of a PlantCover."
    );
    code_list_value_iterator!(
        PlantCoverUsageValueIterator,
        PlantCoverUsageValue,
        ecitygml::model::vegetation::values::PlantCoverUsageValue
    );
}

pub use ffi::PlantCoverUsageValue;
