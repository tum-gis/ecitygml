//! `AbstractCurveProperty` (`gml:CurvePropertyType`), egml's `Property<AbstractCurveKind>`, and its iterator.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::gml::core::model::geometry::primitives::abstract_curve_kind::ffi::AbstractCurveKind;
    use crate::gml::core::model::xlink::href::ffi::HRef;
    use egml::model::base::HasAssociationAttributes;

    /// A curve property (inline curve and/or `xlink:href`), borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct AbstractCurveProperty(egml::model::geometry::primitives::AbstractCurveProperty);

    impl AbstractCurveProperty {
        /// The inline curve; none if the property only references one via `href`.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn object<'a>(&'a self) -> Option<&'a AbstractCurveKind> {
            self.0.object().map(AbstractCurveKind::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn href<'a>(&'a self) -> Option<&'a HRef> {
            self.0.href().map(HRef::transparent_convert)
        }
    }

    /// Iterates over curve properties, borrowed from a city model.
    #[diplomat::opaque_mut]
    pub struct AbstractCurvePropertyIterator<'a>(
        pub(crate) std::slice::Iter<'a, egml::model::geometry::primitives::AbstractCurveProperty>,
    );

    impl<'a> AbstractCurvePropertyIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<&'a AbstractCurveProperty> {
            self.0
                .next()
                .map(AbstractCurveProperty::transparent_convert)
        }
    }
}

pub use ffi::{AbstractCurveProperty, AbstractCurvePropertyIterator};
