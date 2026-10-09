//! Code-list value wrappers, mirroring ecitygml-core's `code_list_value_wrapper!`: each wrapper
//! (e.g. `TrafficSpaceFunctionValue`) gets `code()` and `value()`; values that appear in lists
//! (`&[…]` in Rust) also get an iterator type from `code_list_value_iterator!`. Invoked inside a
//! bridge, which includes this file.

#[diplomat::macro_rules]
macro_rules! code_list_value_wrapper {
    ($name:ident, $rust:ty, $doc:literal) => {
        #[doc = $doc]
        #[diplomat::opaque]
        #[diplomat::transparent_convert]
        pub struct $name($rust);

        impl $name {
            #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
            pub fn code<'a>(&'a self) -> &'a crate::gml::core::model::basic_types::code::ffi::Code {
                crate::gml::core::model::basic_types::code::ffi::Code::transparent_convert(
                    self.0.code(),
                )
            }

            #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
            pub fn value<'a>(&'a self) -> &'a str {
                self.0.value()
            }
        }
    };
}

/// The iterator over a list of code-list values (Diplomat macros can't have several arms, so this is
/// a separate macro, invoked next to `code_list_value_wrapper!` for values that appear in lists).
#[diplomat::macro_rules]
macro_rules! code_list_value_iterator {
    ($iterator:ident, $name:ident, $rust:ty) => {
        /// Iterates over a list of code-list values, borrowed from a city model.
        #[diplomat::opaque_mut]
        pub struct $iterator<'a>(pub(crate) std::slice::Iter<'a, $rust>);

        impl<'a> $iterator<'a> {
            #[diplomat::attr(auto, iterator)]
            #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
            pub fn next(&mut self) -> Option<&'a $name> {
                self.0.next().map($name::transparent_convert)
            }
        }
    };
}
