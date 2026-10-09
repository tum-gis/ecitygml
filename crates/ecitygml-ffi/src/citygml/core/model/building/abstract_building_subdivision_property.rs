//! `AbstractBuildingSubdivisionProperty`, mirroring `ecitygml::model::building::AbstractBuildingSubdivisionProperty` (`ArenaProperty<AbstractBuildingSubdivisionKind>`), and its iterator.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::citygml::core::model::building::abstract_building_subdivision_kind::ffi::AbstractBuildingSubdivisionKind;
    use crate::gml::core::model::xlink::href::ffi::HRef;
    use egml::model::base::HasAssociationAttributes;

    /// A building subdivision property (inline building subdivision and/or `xlink:href`), borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct AbstractBuildingSubdivisionProperty(
        ecitygml::model::building::AbstractBuildingSubdivisionProperty,
    );

    impl AbstractBuildingSubdivisionProperty {
        /// The inline building subdivision; none if the property only references one via `href`.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn object<'a>(&'a self) -> Option<&'a AbstractBuildingSubdivisionKind> {
            self.0
                .object()
                .map(AbstractBuildingSubdivisionKind::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn href<'a>(&'a self) -> Option<&'a HRef> {
            self.0.href().map(HRef::transparent_convert)
        }
    }

    type Properties<'a> =
        std::slice::Iter<'a, ecitygml::model::building::AbstractBuildingSubdivisionProperty>;

    /// Iterates over building subdivision properties, borrowed from a city model.
    #[diplomat::opaque_mut]
    pub struct AbstractBuildingSubdivisionPropertyIterator<'a>(pub(crate) Properties<'a>);

    impl<'a> AbstractBuildingSubdivisionPropertyIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<&'a AbstractBuildingSubdivisionProperty> {
            self.0
                .next()
                .map(AbstractBuildingSubdivisionProperty::transparent_convert)
        }
    }
}

pub use ffi::{AbstractBuildingSubdivisionProperty, AbstractBuildingSubdivisionPropertyIterator};
