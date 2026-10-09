// Macros first: they are only visible to code after their module (textual scope).
#[macro_use]
mod abstract_object;

#[macro_use]
pub mod base;
pub mod basic_types;
#[macro_use]
pub mod common;
#[macro_use]
pub mod feature;
pub mod geometry;
pub mod measures;
pub mod xlink;
pub mod xs;
