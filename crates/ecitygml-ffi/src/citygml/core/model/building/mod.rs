// Macros first: they are only visible to code after their module (textual scope).
#[macro_use]
mod abstract_building;
#[macro_use]
mod abstract_building_subdivision;

pub mod abstract_building_subdivision_kind;
pub mod abstract_building_subdivision_property;
#[allow(clippy::module_inception)] // mirrors ecitygml-core: `model::building::building`
pub mod building;
pub mod building_part;
pub mod building_part_property;
pub mod building_unit;
pub mod storey;
pub mod values;
