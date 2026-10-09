//! `IntersectionProperty`, mirroring `ecitygml::model::transportation::IntersectionProperty` (`ArenaProperty<Intersection>`), and its iterator.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::citygml::core::model::transportation::intersection::ffi::Intersection;
    use crate::gml::core::model::xlink::href::ffi::HRef;
    use egml::model::base::HasAssociationAttributes;

    /// A intersection property (inline intersection and/or `xlink:href`), borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct IntersectionProperty(ecitygml::model::transportation::IntersectionProperty);

    impl IntersectionProperty {
        /// The inline intersection; none if the property only references one via `href`.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn object<'a>(&'a self) -> Option<&'a Intersection> {
            self.0.object().map(Intersection::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn href<'a>(&'a self) -> Option<&'a HRef> {
            self.0.href().map(HRef::transparent_convert)
        }
    }

    /// Iterates over intersection properties, borrowed from a city model.
    #[diplomat::opaque_mut]
    pub struct IntersectionPropertyIterator<'a>(
        pub(crate) std::slice::Iter<'a, ecitygml::model::transportation::IntersectionProperty>,
    );

    impl<'a> IntersectionPropertyIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<&'a IntersectionProperty> {
            self.0.next().map(IntersectionProperty::transparent_convert)
        }
    }
}

pub use ffi::{IntersectionProperty, IntersectionPropertyIterator};
