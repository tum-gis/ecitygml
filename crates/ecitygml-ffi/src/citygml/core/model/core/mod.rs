// Macros first: they are only visible to code after their module (textual scope).
#[macro_use]
mod abstract_city_object;
#[macro_use]
mod abstract_feature;
#[macro_use]
mod abstract_feature_with_lifespan;
#[macro_use]
mod abstract_logical_space;
#[macro_use]
mod abstract_occupied_space;
#[macro_use]
mod abstract_physical_space;
#[macro_use]
mod abstract_space;
#[macro_use]
mod abstract_space_boundary;
#[macro_use]
mod abstract_thematic_surface;
#[macro_use]
mod abstract_unoccupied_space;

pub mod abstract_city_object_kind;
pub mod abstract_city_object_property;
pub mod abstract_space_boundary_kind;
pub mod abstract_space_boundary_property;
pub mod city_model;
pub mod city_object_relation;
pub mod city_object_relation_property;
pub mod enums;
pub mod external_reference;
pub mod implicit_geometry;
pub mod implicit_geometry_property;
pub mod occupancy;
pub mod refs;
pub mod transformation_matrix_4x4;
pub mod values;
