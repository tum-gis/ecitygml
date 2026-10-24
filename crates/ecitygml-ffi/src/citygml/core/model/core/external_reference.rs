//! `ExternalReference`, mirroring `ecitygml::model::core::ExternalReference`, and its iterator.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    /// A reference to an object in another information system, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct ExternalReference(ecitygml::model::core::ExternalReference);

    impl ExternalReference {
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn target_resource<'a>(&'a self) -> &'a str {
            self.0.target_resource.as_str()
        }

        // Not in .NET: diplomat-tool 0.16 can't return an optional borrowed string there yet.
        #[diplomat::attr(dotnet, disable)]
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn information_system<'a>(&'a self) -> Option<&'a str> {
            self.0
                .information_system
                .as_ref()
                .map(egml::model::xs::AnyUri::as_str)
        }

        // Not in .NET: diplomat-tool 0.16 can't return an optional borrowed string there yet.
        #[diplomat::attr(dotnet, disable)]
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn relation_type<'a>(&'a self) -> Option<&'a str> {
            self.0
                .relation_type
                .as_ref()
                .map(egml::model::xs::AnyUri::as_str)
        }
    }

    /// Iterates over external references, borrowed from a city model.
    #[diplomat::opaque_mut]
    pub struct ExternalReferenceIterator<'a>(
        pub(crate) std::slice::Iter<'a, ecitygml::model::core::ExternalReference>,
    );

    impl<'a> ExternalReferenceIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<&'a ExternalReference> {
            self.0.next().map(ExternalReference::transparent_convert)
        }
    }
}

pub use ffi::{ExternalReference, ExternalReferenceIterator};
