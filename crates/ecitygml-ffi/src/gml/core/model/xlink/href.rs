//! `HRef`, an `xlink:href` reference.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use diplomat_runtime::DiplomatWrite;
    use std::fmt::Write;

    /// An `xlink:href` reference (local `#id` or remote URI), borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct HRef(egml::model::xlink::HRef);

    impl HRef {
        /// The referenced `gml:id` of a local reference (`#id`), or none for a remote one.
        // Not in .NET: diplomat-tool 0.16 can't return an optional borrowed string there yet.
        #[diplomat::attr(dotnet, disable)]
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn local_id<'a>(&'a self) -> Option<&'a str> {
            self.0.local_id()
        }

        pub fn is_local(&self) -> bool {
            self.0.is_local()
        }

        /// The reference as written in GML (Rust: `Display`).
        #[allow(clippy::inherent_to_string)]
        pub fn to_string(&self, write: &mut DiplomatWrite) {
            let _ = write!(write, "{}", self.0);
        }
    }
}

pub use ffi::HRef;
