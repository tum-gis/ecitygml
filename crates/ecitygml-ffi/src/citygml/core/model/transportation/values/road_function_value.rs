//! `RoadFunctionValue`, mirroring `ecitygml::model::transportation::values::RoadFunctionValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        RoadFunctionValue,
        ecitygml::model::transportation::values::RoadFunctionValue,
        "The `function` property of a Road."
    );
    code_list_value_iterator!(
        RoadFunctionValueIterator,
        RoadFunctionValue,
        ecitygml::model::transportation::values::RoadFunctionValue
    );
}

pub use ffi::{RoadFunctionValue, RoadFunctionValueIterator};
