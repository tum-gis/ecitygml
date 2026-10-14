// Macros first: they are only visible to code after their module (textual scope).
#[macro_use]
mod abstract_bridge;

#[expect(
    clippy::module_inception,
    reason = "mirrors ecitygml-core: `model::bridge::bridge`"
)]
pub mod bridge;
pub mod bridge_part;
pub mod bridge_part_property;
pub mod values;
