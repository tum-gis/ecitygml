//! `CityFurnitureClassValue`, mirroring `ecitygml::model::city_furniture::values::CityFurnitureClassValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        CityFurnitureClassValue,
        ecitygml::model::city_furniture::values::CityFurnitureClassValue,
        "The `class` property of a CityFurniture."
    );
}

pub use ffi::CityFurnitureClassValue;
