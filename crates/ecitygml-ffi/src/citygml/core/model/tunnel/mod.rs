// Macros first: they are only visible to code after their module (textual scope).
#[macro_use]
mod abstract_tunnel;

#[allow(clippy::module_inception)] // mirrors ecitygml-core: `model::tunnel::tunnel`
pub mod tunnel;
pub mod tunnel_part;
pub mod tunnel_part_property;
pub mod values;
