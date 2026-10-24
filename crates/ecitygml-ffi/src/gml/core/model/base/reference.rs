//! `Reference` (`gml:ReferenceType`), a by-reference-only property.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::gml::core::model::xlink::href::ffi::HRef;
    use egml::model::base::HasAssociationAttributes;

    /// A reference to an object by `xlink:href`, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct Reference(egml::model::base::Reference);

    impl Reference {
        /// An owned copy of a traffic space reference (Rust: `From<&TrafficSpaceReference>`).
        pub fn from_traffic_space_reference(
            reference: &crate::citygml::core::model::transportation::traffic_space_reference::ffi::TrafficSpaceReference,
        ) -> Box<Reference> {
            Box::new(Reference(egml::model::base::Reference::from(&reference.0)))
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn href<'a>(&'a self) -> Option<&'a HRef> {
            self.0.href().map(HRef::transparent_convert)
        }
    }
}

pub use ffi::Reference;
