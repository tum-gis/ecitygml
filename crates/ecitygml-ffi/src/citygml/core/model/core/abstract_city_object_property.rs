//! `AbstractCityObjectProperty`, mirroring `ecitygml::model::core::AbstractCityObjectProperty` (`ArenaProperty<AbstractCityObjectKind>`), and its iterator.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::citygml::core::model::core::abstract_city_object_kind::ffi::AbstractCityObjectKind;
    use crate::gml::core::model::xlink::href::ffi::HRef;
    use egml::model::base::HasAssociationAttributes;

    /// A city object property (inline city object and/or `xlink:href`), borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct AbstractCityObjectProperty(ecitygml::model::core::AbstractCityObjectProperty);

    impl AbstractCityObjectProperty {
        /// The inline city object; none if the property only references one via `href`.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn object<'a>(&'a self) -> Option<&'a AbstractCityObjectKind> {
            self.0
                .object()
                .map(AbstractCityObjectKind::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn href<'a>(&'a self) -> Option<&'a HRef> {
            self.0.href().map(HRef::transparent_convert)
        }
    }

    type Properties<'a> = std::slice::Iter<'a, ecitygml::model::core::AbstractCityObjectProperty>;

    /// Iterates over city object properties, borrowed from a city model.
    #[diplomat::opaque_mut]
    pub struct AbstractCityObjectPropertyIterator<'a>(pub(crate) Properties<'a>);

    impl<'a> AbstractCityObjectPropertyIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<&'a AbstractCityObjectProperty> {
            self.0
                .next()
                .map(AbstractCityObjectProperty::transparent_convert)
        }
    }
}

pub use ffi::{AbstractCityObjectProperty, AbstractCityObjectPropertyIterator};
