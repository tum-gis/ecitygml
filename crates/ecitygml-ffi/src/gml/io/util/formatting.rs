//! `Formatting`, how written GML is laid out, mirroring `egml::io::util::Formatting`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    /// How written GML is laid out. Rust's enum variant `Indent` carries data, which Diplomat enums
    /// can't, so each variant is a named constructor.
    #[diplomat::opaque]
    pub struct Formatting(pub(crate) egml::io::util::Formatting);

    impl Formatting {
        /// All elements on a single line, without whitespace between them.
        #[diplomat::attr(auto, named_constructor = "compact")]
        pub fn compact() -> Box<Formatting> {
            Box::new(Formatting(egml::io::util::Formatting::Compact))
        }

        /// Each element on its own line, without indentation (the default).
        #[diplomat::attr(auto, named_constructor = "new_line")]
        pub fn new_line() -> Box<Formatting> {
            Box::new(Formatting(egml::io::util::Formatting::NewLine))
        }

        /// Each element on its own line, indented by `size` repetitions of the byte `char`, e.g.
        /// `b' '` and 2.
        #[diplomat::attr(auto, named_constructor = "indent")]
        pub fn indent(char: u8, size: usize) -> Box<Formatting> {
            Box::new(Formatting(egml::io::util::Formatting::Indent {
                char,
                size,
            }))
        }
    }
}

pub use ffi::Formatting;
