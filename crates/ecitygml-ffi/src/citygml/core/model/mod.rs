// Order matters for macros (textual scope): `common` (code-list macro), `core` and `construction`
// (abstract-type macros) come before the modules that invoke them.
#[macro_use]
pub mod common;
#[macro_use]
pub mod core;
#[macro_use]
pub mod construction;
pub mod generics;

#[macro_use]
pub mod bridge;
#[macro_use]
pub mod building;
pub mod city_furniture;
#[macro_use]
pub mod relief;
pub mod transportation;
#[macro_use]
pub mod tunnel;
#[macro_use]
pub mod vegetation;
