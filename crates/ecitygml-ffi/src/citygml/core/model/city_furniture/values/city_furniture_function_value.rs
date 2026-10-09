//! `CityFurnitureFunctionValue`, mirroring `ecitygml::model::city_furniture::values::CityFurnitureFunctionValue`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/common/codelist.rs")]
pub mod ffi {
    code_list_value_wrapper!(
        CityFurnitureFunctionValue,
        ecitygml::model::city_furniture::values::CityFurnitureFunctionValue,
        "The `function` property of a CityFurniture."
    );
    code_list_value_iterator!(
        CityFurnitureFunctionValueIterator,
        CityFurnitureFunctionValue,
        ecitygml::model::city_furniture::values::CityFurnitureFunctionValue
    );
}

pub use ffi::CityFurnitureFunctionValue;
