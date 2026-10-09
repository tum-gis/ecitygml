//! `AbstractFillingSurfaceProperty`, mirroring `ecitygml::model::construction::AbstractFillingSurfaceProperty` (`ArenaProperty<AbstractFillingSurfaceKind>`), and its iterator.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::citygml::core::model::construction::abstract_filling_surface_kind::ffi::AbstractFillingSurfaceKind;
    use crate::gml::core::model::xlink::href::ffi::HRef;
    use egml::model::base::HasAssociationAttributes;

    /// A filling surface property (inline filling surface and/or `xlink:href`), borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct AbstractFillingSurfaceProperty(
        ecitygml::model::construction::AbstractFillingSurfaceProperty,
    );

    impl AbstractFillingSurfaceProperty {
        /// The inline filling surface; none if the property only references one via `href`.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn object<'a>(&'a self) -> Option<&'a AbstractFillingSurfaceKind> {
            self.0
                .object()
                .map(AbstractFillingSurfaceKind::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn href<'a>(&'a self) -> Option<&'a HRef> {
            self.0.href().map(HRef::transparent_convert)
        }
    }

    type Properties<'a> =
        std::slice::Iter<'a, ecitygml::model::construction::AbstractFillingSurfaceProperty>;

    /// Iterates over filling surface properties, borrowed from a city model.
    #[diplomat::opaque_mut]
    pub struct AbstractFillingSurfacePropertyIterator<'a>(pub(crate) Properties<'a>);

    impl<'a> AbstractFillingSurfacePropertyIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<&'a AbstractFillingSurfaceProperty> {
            self.0
                .next()
                .map(AbstractFillingSurfaceProperty::transparent_convert)
        }
    }
}

pub use ffi::{AbstractFillingSurfaceProperty, AbstractFillingSurfacePropertyIterator};
