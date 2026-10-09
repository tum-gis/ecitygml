//! `LevelOfDetail`, mirroring `ecitygml::model::common::LevelOfDetail`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::error::ffi::Error;

    /// A CityGML level of detail (LoD 0 to 3).
    #[diplomat::enum_convert(ecitygml::model::common::LevelOfDetail)]
    #[derive(Debug, PartialEq, Eq)]
    pub enum LevelOfDetail {
        // Explicit: the discriminants are each language's enum values (e.g. Python's
        // `LevelOfDetail.Two.value`), so they equal `as_index()`.
        Zero = 0,
        One = 1,
        Two = 2,
        Three = 3,
    }

    impl LevelOfDetail {
        /// The level as a number, e.g. 2 for `Two`.
        pub fn as_index(self) -> usize {
            ecitygml::model::common::LevelOfDetail::from(self).as_index()
        }

        /// The level with that number; fails with `InvalidArgument` above 3 (Rust: `TryFrom<u8>`).
        pub fn try_from(value: u8) -> Result<LevelOfDetail, Box<Error>> {
            Ok(ecitygml::model::common::LevelOfDetail::try_from(value)?.into())
        }
    }
}

pub use ffi::LevelOfDetail;
