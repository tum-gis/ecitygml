//! `TunnelPartProperty`, mirroring `ecitygml::model::tunnel::TunnelPartProperty` (`ArenaProperty<TunnelPart>`), and its iterator.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::citygml::core::model::tunnel::tunnel_part::ffi::TunnelPart;
    use crate::gml::core::model::xlink::href::ffi::HRef;
    use egml::model::base::HasAssociationAttributes;

    /// A tunnel part property (inline tunnel part and/or `xlink:href`), borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct TunnelPartProperty(ecitygml::model::tunnel::TunnelPartProperty);

    impl TunnelPartProperty {
        /// The inline tunnel part; none if the property only references one via `href`.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn object<'a>(&'a self) -> Option<&'a TunnelPart> {
            self.0.object().map(TunnelPart::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn href<'a>(&'a self) -> Option<&'a HRef> {
            self.0.href().map(HRef::transparent_convert)
        }
    }

    /// Iterates over tunnel part properties, borrowed from a city model.
    #[diplomat::opaque_mut]
    pub struct TunnelPartPropertyIterator<'a>(
        pub(crate) std::slice::Iter<'a, ecitygml::model::tunnel::TunnelPartProperty>,
    );

    impl<'a> TunnelPartPropertyIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<&'a TunnelPartProperty> {
            self.0.next().map(TunnelPartProperty::transparent_convert)
        }
    }
}

pub use ffi::{TunnelPartProperty, TunnelPartPropertyIterator};
