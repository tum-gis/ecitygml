//! `CityFurnitureUsageValue`, mirroring `ecitygml::model::city_furniture::values::CityFurnitureUsageValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        CityFurnitureUsageValue,
        ecitygml::model::city_furniture::values::CityFurnitureUsageValue,
        "The `usage` property of a CityFurniture."
    );
    code_list_value_iterator!(
        CityFurnitureUsageValueIterator,
        CityFurnitureUsageValue,
        ecitygml::model::city_furniture::values::CityFurnitureUsageValue
    );
}

pub use ffi::CityFurnitureUsageValue;
