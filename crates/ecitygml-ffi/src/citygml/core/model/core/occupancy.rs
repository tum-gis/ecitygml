//! `Occupancy`, mirroring `ecitygml::model::core::Occupancy`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::citygml::core::model::core::values::interval_value::ffi::IntervalValue;
    use crate::citygml::core::model::core::values::occupant_type_value::ffi::OccupantTypeValue;

    /// The number of occupants of a feature, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct Occupancy(ecitygml::model::core::Occupancy);

    impl Occupancy {
        pub fn number_of_occupants(&self) -> i64 {
            self.0.number_of_occupants()
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn interval<'a>(&'a self) -> Option<&'a IntervalValue> {
            self.0.interval().map(IntervalValue::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn occupant_type<'a>(&'a self) -> Option<&'a OccupantTypeValue> {
            self.0
                .occupant_type()
                .map(OccupantTypeValue::transparent_convert)
        }
    }

    /// Iterates over a list of occupancies, borrowed from a city model.
    #[diplomat::opaque_mut]
    pub struct OccupancyIterator<'a>(
        pub(crate) std::slice::Iter<'a, ecitygml::model::core::Occupancy>,
    );

    impl<'a> OccupancyIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<&'a Occupancy> {
            self.0.next().map(Occupancy::transparent_convert)
        }
    }
}

pub use ffi::{Occupancy, OccupancyIterator};
