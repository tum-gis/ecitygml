//! `SectionProperty`, mirroring `ecitygml::model::transportation::SectionProperty` (`ArenaProperty<Section>`), and its iterator.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::citygml::core::model::transportation::section::ffi::Section;
    use crate::gml::core::model::xlink::href::ffi::HRef;
    use egml::model::base::HasAssociationAttributes;

    /// A section property (inline section and/or `xlink:href`), borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct SectionProperty(ecitygml::model::transportation::SectionProperty);

    impl SectionProperty {
        /// The inline section; none if the property only references one via `href`.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn object<'a>(&'a self) -> Option<&'a Section> {
            self.0.object().map(Section::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn href<'a>(&'a self) -> Option<&'a HRef> {
            self.0.href().map(HRef::transparent_convert)
        }
    }

    /// Iterates over section properties, borrowed from a city model.
    #[diplomat::opaque_mut]
    pub struct SectionPropertyIterator<'a>(
        pub(crate) std::slice::Iter<'a, ecitygml::model::transportation::SectionProperty>,
    );

    impl<'a> SectionPropertyIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<&'a SectionProperty> {
            self.0.next().map(SectionProperty::transparent_convert)
        }
    }
}

pub use ffi::{SectionProperty, SectionPropertyIterator};
