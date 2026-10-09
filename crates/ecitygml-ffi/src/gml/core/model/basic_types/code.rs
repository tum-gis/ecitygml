//! `Code`, a term from a code list (`gml:CodeType`).

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    /// A code-list value with an optional code space, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct Code(egml::model::basic_types::Code);

    impl Code {
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn value<'a>(&'a self) -> &'a str {
            self.0.value()
        }

        // Not in .NET: diplomat-tool 0.16 can't return an optional borrowed string there yet.
        #[diplomat::attr(dotnet, disable)]
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn code_space<'a>(&'a self) -> Option<&'a str> {
            self.0.code_space()
        }
    }

    /// Iterates over a list of codes (e.g. `gml:name`s), borrowed from a city model.
    #[diplomat::opaque_mut]
    pub struct CodeIterator<'a>(pub(crate) std::slice::Iter<'a, egml::model::basic_types::Code>);

    impl<'a> CodeIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<&'a Code> {
            self.0.next().map(Code::transparent_convert)
        }
    }
}

pub use ffi::{Code, CodeIterator};
