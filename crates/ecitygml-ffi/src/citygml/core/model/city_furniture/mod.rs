#[expect(
    clippy::module_inception,
    reason = "mirrors ecitygml-core: `model::city_furniture::city_furniture`"
)]
pub mod city_furniture;
pub mod values;
