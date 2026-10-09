//! `AuxiliaryTrafficSpaceProperty`, mirroring `ecitygml::model::transportation::AuxiliaryTrafficSpaceProperty` (`ArenaProperty<AuxiliaryTrafficSpace>`), and its iterator.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::citygml::core::model::transportation::auxiliary_traffic_space::ffi::AuxiliaryTrafficSpace;
    use crate::gml::core::model::xlink::href::ffi::HRef;
    use egml::model::base::HasAssociationAttributes;

    /// A auxiliary traffic space property (inline auxiliary traffic space and/or `xlink:href`), borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct AuxiliaryTrafficSpaceProperty(
        ecitygml::model::transportation::AuxiliaryTrafficSpaceProperty,
    );

    impl AuxiliaryTrafficSpaceProperty {
        /// The inline auxiliary traffic space; none if the property only references one via `href`.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn object<'a>(&'a self) -> Option<&'a AuxiliaryTrafficSpace> {
            self.0
                .object()
                .map(AuxiliaryTrafficSpace::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn href<'a>(&'a self) -> Option<&'a HRef> {
            self.0.href().map(HRef::transparent_convert)
        }
    }

    type Properties<'a> =
        std::slice::Iter<'a, ecitygml::model::transportation::AuxiliaryTrafficSpaceProperty>;

    /// Iterates over auxiliary traffic space properties, borrowed from a city model.
    #[diplomat::opaque_mut]
    pub struct AuxiliaryTrafficSpacePropertyIterator<'a>(pub(crate) Properties<'a>);

    impl<'a> AuxiliaryTrafficSpacePropertyIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<&'a AuxiliaryTrafficSpaceProperty> {
            self.0
                .next()
                .map(AuxiliaryTrafficSpaceProperty::transparent_convert)
        }
    }
}

pub use ffi::{AuxiliaryTrafficSpaceProperty, AuxiliaryTrafficSpacePropertyIterator};
