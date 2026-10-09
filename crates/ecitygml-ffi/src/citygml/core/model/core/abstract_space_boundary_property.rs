//! `AbstractSpaceBoundaryProperty`, mirroring `ecitygml::model::core::AbstractSpaceBoundaryProperty` (`ArenaProperty<AbstractSpaceBoundaryKind>`), and its iterator.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::citygml::core::model::core::abstract_space_boundary_kind::ffi::AbstractSpaceBoundaryKind;
    use crate::gml::core::model::xlink::href::ffi::HRef;
    use egml::model::base::HasAssociationAttributes;

    /// A space boundary property (inline space boundary and/or `xlink:href`), borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct AbstractSpaceBoundaryProperty(ecitygml::model::core::AbstractSpaceBoundaryProperty);

    impl AbstractSpaceBoundaryProperty {
        /// The inline space boundary; none if the property only references one via `href`.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn object<'a>(&'a self) -> Option<&'a AbstractSpaceBoundaryKind> {
            self.0
                .object()
                .map(AbstractSpaceBoundaryKind::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn href<'a>(&'a self) -> Option<&'a HRef> {
            self.0.href().map(HRef::transparent_convert)
        }
    }

    type Properties<'a> =
        std::slice::Iter<'a, ecitygml::model::core::AbstractSpaceBoundaryProperty>;

    /// Iterates over space boundary properties, borrowed from a city model.
    #[diplomat::opaque_mut]
    pub struct AbstractSpaceBoundaryPropertyIterator<'a>(pub(crate) Properties<'a>);

    impl<'a> AbstractSpaceBoundaryPropertyIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<&'a AbstractSpaceBoundaryProperty> {
            self.0
                .next()
                .map(AbstractSpaceBoundaryProperty::transparent_convert)
        }
    }
}

pub use ffi::{AbstractSpaceBoundaryProperty, AbstractSpaceBoundaryPropertyIterator};
