//! `AbstractReliefComponentProperty`, mirroring `ecitygml::model::relief::AbstractReliefComponentProperty` (`ArenaProperty<AbstractReliefComponentKind>`), and its iterator.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::citygml::core::model::relief::abstract_relief_component_kind::ffi::AbstractReliefComponentKind;
    use crate::gml::core::model::xlink::href::ffi::HRef;
    use egml::model::base::HasAssociationAttributes;

    /// A relief component property (inline relief component and/or `xlink:href`), borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct AbstractReliefComponentProperty(
        ecitygml::model::relief::AbstractReliefComponentProperty,
    );

    impl AbstractReliefComponentProperty {
        /// The inline relief component; none if the property only references one via `href`.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn object<'a>(&'a self) -> Option<&'a AbstractReliefComponentKind> {
            self.0
                .object()
                .map(AbstractReliefComponentKind::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn href<'a>(&'a self) -> Option<&'a HRef> {
            self.0.href().map(HRef::transparent_convert)
        }
    }

    type Properties<'a> =
        std::slice::Iter<'a, ecitygml::model::relief::AbstractReliefComponentProperty>;

    /// Iterates over relief component properties, borrowed from a city model.
    #[diplomat::opaque_mut]
    pub struct AbstractReliefComponentPropertyIterator<'a>(pub(crate) Properties<'a>);

    impl<'a> AbstractReliefComponentPropertyIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<&'a AbstractReliefComponentProperty> {
            self.0
                .next()
                .map(AbstractReliefComponentProperty::transparent_convert)
        }
    }
}

pub use ffi::{AbstractReliefComponentProperty, AbstractReliefComponentPropertyIterator};
