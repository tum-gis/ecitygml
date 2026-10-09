//! `TrafficSpaceProperty`, mirroring `ecitygml::model::transportation::TrafficSpaceProperty` (`ArenaProperty<TrafficSpace>`), and its iterator.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::citygml::core::model::transportation::traffic_space::ffi::TrafficSpace;
    use crate::gml::core::model::xlink::href::ffi::HRef;
    use egml::model::base::HasAssociationAttributes;

    /// A traffic space property (inline traffic space and/or `xlink:href`), borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct TrafficSpaceProperty(ecitygml::model::transportation::TrafficSpaceProperty);

    impl TrafficSpaceProperty {
        /// The inline traffic space; none if the property only references one via `href`.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn object<'a>(&'a self) -> Option<&'a TrafficSpace> {
            self.0.object().map(TrafficSpace::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn href<'a>(&'a self) -> Option<&'a HRef> {
            self.0.href().map(HRef::transparent_convert)
        }
    }

    /// Iterates over traffic space properties, borrowed from a city model.
    #[diplomat::opaque_mut]
    pub struct TrafficSpacePropertyIterator<'a>(
        pub(crate) std::slice::Iter<'a, ecitygml::model::transportation::TrafficSpaceProperty>,
    );

    impl<'a> TrafficSpacePropertyIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<&'a TrafficSpaceProperty> {
            self.0.next().map(TrafficSpaceProperty::transparent_convert)
        }
    }
}

pub use ffi::{TrafficSpaceProperty, TrafficSpacePropertyIterator};
