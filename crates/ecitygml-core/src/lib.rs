#![expect(
    clippy::module_inception,
    reason = "the modules mirror the CityGML packages and types, e.g. `model::building::building`"
)]

pub mod arena;
mod error;
pub mod index;
pub mod model;
pub mod resolver;
pub mod store;

#[doc(inline)]
pub use error::Error;
