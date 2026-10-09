//! Bridges for the egml crates: `core` ~ egml-core, `io` ~ egml-io.

// Its abstract-type macros are used by `citygml` (textual macro scope), so they're passed up.
#[macro_use]
pub mod core;
pub mod io;
