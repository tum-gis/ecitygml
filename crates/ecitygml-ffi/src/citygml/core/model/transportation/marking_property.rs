//! `MarkingProperty`, mirroring `ecitygml::model::transportation::MarkingProperty` (`ArenaProperty<Marking>`), and its iterator.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::citygml::core::model::transportation::marking::ffi::Marking;
    use crate::gml::core::model::xlink::href::ffi::HRef;
    use egml::model::base::HasAssociationAttributes;

    /// A marking property (inline marking and/or `xlink:href`), borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct MarkingProperty(ecitygml::model::transportation::MarkingProperty);

    impl MarkingProperty {
        /// The inline marking; none if the property only references one via `href`.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn object<'a>(&'a self) -> Option<&'a Marking> {
            self.0.object().map(Marking::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn href<'a>(&'a self) -> Option<&'a HRef> {
            self.0.href().map(HRef::transparent_convert)
        }
    }

    /// Iterates over marking properties, borrowed from a city model.
    #[diplomat::opaque_mut]
    pub struct MarkingPropertyIterator<'a>(
        pub(crate) std::slice::Iter<'a, ecitygml::model::transportation::MarkingProperty>,
    );

    impl<'a> MarkingPropertyIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<&'a MarkingProperty> {
            self.0.next().map(MarkingProperty::transparent_convert)
        }
    }
}

pub use ffi::{MarkingProperty, MarkingPropertyIterator};
