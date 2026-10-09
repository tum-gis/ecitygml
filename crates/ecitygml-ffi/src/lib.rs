//! Language bindings for ecitygml, generated with [Diplomat](https://github.com/rust-diplomat/diplomat).
//!
//! Every `ffi` module is a Diplomat bridge; `diplomat-tool` generates the bindings from them.
//! The layout mirrors the Rust crates and their modules: `citygml::core::model` ~ ecitygml-core's
//! `model`, `citygml::io` ~ ecitygml-io, `gml::core::model` ~ egml-core's `model`.

// `gml` first: its abstract-type macros are used by `citygml` (textual macro scope).
#[macro_use]
pub mod gml;

pub mod citygml;
pub mod error;
