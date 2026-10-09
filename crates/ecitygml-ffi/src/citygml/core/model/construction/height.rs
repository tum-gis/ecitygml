//! `Height`, mirroring `ecitygml::model::construction::Height`, and its iterator.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::citygml::core::model::construction::enums::height_status_value::ffi::HeightStatusValue;
    use crate::citygml::core::model::construction::values::elevation_reference_value::ffi::ElevationReferenceValue;
    use crate::gml::core::model::measures::length::ffi::Length;

    /// A height of a construction between two reference levels, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct Height(ecitygml::model::construction::Height);

    impl Height {
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn high_reference<'a>(&'a self) -> &'a ElevationReferenceValue {
            ElevationReferenceValue::transparent_convert(self.0.high_reference())
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn low_reference<'a>(&'a self) -> &'a ElevationReferenceValue {
            ElevationReferenceValue::transparent_convert(self.0.low_reference())
        }

        pub fn status(&self) -> HeightStatusValue {
            self.0.status().into()
        }

        /// The height value (`con:value`).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn length<'a>(&'a self) -> &'a Length {
            Length::transparent_convert(self.0.length())
        }
    }

    /// Iterates over heights, borrowed from a city model.
    #[diplomat::opaque_mut]
    pub struct HeightIterator<'a>(
        pub(crate) std::slice::Iter<'a, ecitygml::model::construction::Height>,
    );

    impl<'a> HeightIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<&'a Height> {
            self.0.next().map(Height::transparent_convert)
        }
    }
}

pub use ffi::{Height, HeightIterator};
