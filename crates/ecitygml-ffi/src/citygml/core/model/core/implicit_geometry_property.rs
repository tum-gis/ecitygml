//! `ImplicitGeometryProperty` (`ImplicitGeometryPropertyType`), `Property<ImplicitGeometry>`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::citygml::core::model::core::implicit_geometry::ffi::ImplicitGeometry;
    use crate::gml::core::model::xlink::href::ffi::HRef;
    use egml::model::base::HasAssociationAttributes;

    /// An implicit geometry property (inline implicit geometry and/or `xlink:href`), borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct ImplicitGeometryProperty(ecitygml::model::core::ImplicitGeometryProperty);

    impl ImplicitGeometryProperty {
        /// The inline implicit geometry; none if the property only references one via `href`.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn object<'a>(&'a self) -> Option<&'a ImplicitGeometry> {
            self.0.object().map(ImplicitGeometry::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn href<'a>(&'a self) -> Option<&'a HRef> {
            self.0.href().map(HRef::transparent_convert)
        }
    }
}

pub use ffi::ImplicitGeometryProperty;
