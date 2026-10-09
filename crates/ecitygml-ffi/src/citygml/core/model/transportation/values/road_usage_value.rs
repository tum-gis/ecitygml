//! `RoadUsageValue`, mirroring `ecitygml::model::transportation::values::RoadUsageValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        RoadUsageValue,
        ecitygml::model::transportation::values::RoadUsageValue,
        "The `usage` property of a Road."
    );
    code_list_value_iterator!(
        RoadUsageValueIterator,
        RoadUsageValue,
        ecitygml::model::transportation::values::RoadUsageValue
    );
}

pub use ffi::{RoadUsageValue, RoadUsageValueIterator};
