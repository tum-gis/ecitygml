//! `GmlWriter`, which writes a city model as CityGML.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::citygml::core::model::core::city_model::ffi::CityModel;
    use crate::citygml::io::format::ffi::CitygmlFormat;
    use crate::error::ffi::{Error, ErrorKind};
    use crate::gml::io::util::formatting::ffi::Formatting;

    /// Writes CityGML to a file or to memory. Rust's builder methods take the writer by value and
    /// `finish` consumes it, which Diplomat can't express: here they modify it in place, and
    /// `finish` can be called only once.
    #[diplomat::opaque_mut]
    pub struct GmlWriter(super::Writer);

    impl GmlWriter {
        /// Writes CityGML of the given `format` to memory, e.g. in WebAssembly, where there is no
        /// file system; read it with `data` after `finish`. Not in Python (see `data`).
        #[diplomat::attr(nanobind, disable)]
        #[diplomat::attr(supports = constructors, constructor)]
        // C++ and Kotlin have no constructors here and can't use `new` as a method name.
        #[diplomat::attr(not(supports = constructors), rename = "create")]
        pub fn new(format: CitygmlFormat) -> Box<GmlWriter> {
            Box::new(GmlWriter(super::Writer::Bytes {
                format: format.into(),
                formatting: Default::default(),
                data: Vec::new(),
                finished: false,
            }))
        }

        /// Creates (or truncates) the file at `path`; its extension (`.gml`, `.gml.gz` or
        /// `.gml.zst`) sets the format.
        #[diplomat::attr(auto, named_constructor = "from_path")]
        pub fn from_path(path: &DiplomatStr) -> Result<Box<GmlWriter>, Box<Error>> {
            let path = crate::error::utf8(path, "path")?;
            Ok(Box::new(GmlWriter(super::Writer::File(Some(
                ecitygml::io::GmlWriter::from_path(path)?,
            )))))
        }

        /// Creates (or truncates) the file `<base_path>.<extension of format>`.
        #[diplomat::attr(auto, named_constructor = "from_base_path_with_format")]
        pub fn from_base_path_with_format(
            base_path: &DiplomatStr,
            format: CitygmlFormat,
        ) -> Result<Box<GmlWriter>, Box<Error>> {
            let base_path = crate::error::utf8(base_path, "base_path")?;
            Ok(Box::new(GmlWriter(super::Writer::File(Some(
                ecitygml::io::GmlWriter::from_base_path_with_format(base_path, format.into())?,
            )))))
        }

        /// How the GML is laid out (default: `Formatting::new_line`). Has no effect after `finish`.
        pub fn with_formatting(&mut self, formatting: &Formatting) {
            self.0.set_formatting(formatting.0);
        }

        /// Writes the city model; fails with `InvalidArgument` if called a second time.
        pub fn finish(&mut self, city_model: &CityModel) -> Result<(), Box<Error>> {
            self.0.finish(&city_model.0)
        }

        /// What a writer created with `new` has written (empty before `finish`, and for files).
        /// Not in Rust, where the caller keeps the writer it passes to `GmlWriter::new`. Not in
        /// Python: Diplomat's nanobind backend returns byte slices as NumPy arrays, and without NumPy
        /// the conversion aborts the interpreter; Python writes files with `from_path` instead.
        #[diplomat::attr(nanobind, disable)]
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn data<'a>(&'a self) -> &'a [u8] {
            match &self.0 {
                super::Writer::Bytes { data, .. } => data,
                super::Writer::File(_) => &[],
            }
        }
    }

    pub(crate) fn already_finished() -> Box<Error> {
        crate::error::Error::new(ErrorKind::InvalidArgument, "the writer is already finished")
    }
}

pub use ffi::GmlWriter;

/// The Rust writers behind the binding: ecitygml-io's `GmlWriter` is generic over its target and
/// consumes itself on `finish`, so the in-memory variant keeps its buffer and creates the Rust
/// writer only when finishing.
pub(crate) enum Writer {
    File(Option<ecitygml::io::GmlWriter<std::fs::File>>),
    Bytes {
        format: ecitygml::io::CitygmlFormat,
        formatting: egml::io::util::Formatting,
        data: Vec<u8>,
        finished: bool,
    },
}

impl Writer {
    fn set_formatting(&mut self, new: egml::io::util::Formatting) {
        match self {
            Writer::File(writer) => *writer = writer.take().map(|w| w.with_formatting(new)),
            Writer::Bytes { formatting, .. } => *formatting = new,
        }
    }

    fn finish(
        &mut self,
        city_model: &ecitygml::model::core::CityModel,
    ) -> Result<(), Box<crate::error::Error>> {
        match self {
            Writer::File(writer) => {
                let writer = writer.take().ok_or_else(ffi::already_finished)?;
                Ok(writer.finish(city_model)?)
            }
            Writer::Bytes {
                format,
                formatting,
                data,
                finished,
            } => {
                if *finished {
                    return Err(ffi::already_finished());
                }
                *finished = true;
                Ok(ecitygml::io::GmlWriter::new(&mut *data, *format)
                    .with_formatting(*formatting)
                    .finish(city_model)?)
            }
        }
    }
}
