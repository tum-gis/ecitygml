//! `BuildingPartProperty`, mirroring `ecitygml::model::building::BuildingPartProperty` (`ArenaProperty<BuildingPart>`), and its iterator.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::citygml::core::model::building::building_part::ffi::BuildingPart;
    use crate::gml::core::model::xlink::href::ffi::HRef;
    use egml::model::base::HasAssociationAttributes;

    /// A building part property (inline building part and/or `xlink:href`), borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct BuildingPartProperty(ecitygml::model::building::BuildingPartProperty);

    impl BuildingPartProperty {
        /// The inline building part; none if the property only references one via `href`.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn object<'a>(&'a self) -> Option<&'a BuildingPart> {
            self.0.object().map(BuildingPart::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn href<'a>(&'a self) -> Option<&'a HRef> {
            self.0.href().map(HRef::transparent_convert)
        }
    }

    /// Iterates over building part properties, borrowed from a city model.
    #[diplomat::opaque_mut]
    pub struct BuildingPartPropertyIterator<'a>(
        pub(crate) std::slice::Iter<'a, ecitygml::model::building::BuildingPartProperty>,
    );

    impl<'a> BuildingPartPropertyIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<&'a BuildingPartProperty> {
            self.0.next().map(BuildingPartProperty::transparent_convert)
        }
    }
}

pub use ffi::{BuildingPartProperty, BuildingPartPropertyIterator};
