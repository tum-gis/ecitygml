//! `GmlReader`, which reads a CityGML file into a city model.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::citygml::core::model::core::city_model::ffi::CityModel;
    use crate::citygml::io::format::ffi::CitygmlFormat;
    use crate::error::ffi::{Error, ErrorKind};

    /// Reads CityGML from a file or from memory. Rust's builder methods take the reader by value,
    /// which Diplomat can't express: here they modify it in place, and `finish` can be called only once.
    #[diplomat::opaque_mut]
    pub struct GmlReader(Option<super::Reader>);

    impl GmlReader {
        /// Reads CityGML content of the given `format` from memory, e.g. in WebAssembly, where there is
        /// no file system. The data is copied.
        #[diplomat::attr(supports = constructors, constructor)]
        // C++ and Kotlin have no constructors here and can't use `new` as a method name.
        #[diplomat::attr(not(supports = constructors), rename = "create")]
        pub fn new(data: &[u8], format: CitygmlFormat) -> Box<GmlReader> {
            Box::new(GmlReader(Some(super::Reader::Bytes(
                ecitygml::io::GmlReader::new(std::io::Cursor::new(data.to_vec()), format.into()),
            ))))
        }

        /// Opens the CityGML file at `path` (`.gml`, `.gml.gz` or `.gml.zst`).
        #[diplomat::attr(auto, named_constructor = "from_path")]
        pub fn from_path(path: &DiplomatStr) -> Result<Box<GmlReader>, Box<Error>> {
            let path = crate::error::utf8(path, "path")?;
            Ok(Box::new(GmlReader(Some(super::Reader::File(
                ecitygml::io::GmlReader::from_path(path)?,
            )))))
        }

        /// Whether envelopes of child objects are recomputed from their geometry (default: true).
        /// Has no effect after `finish`.
        pub fn with_rebuild_object_bounds(&mut self, rebuild_object_bounds: bool) {
            self.0 = self
                .0
                .take()
                .map(|reader| reader.with_rebuild_object_bounds(rebuild_object_bounds));
        }

        /// Reads the city model; fails with `InvalidArgument` if called a second time.
        pub fn finish(&mut self) -> Result<Box<CityModel>, Box<Error>> {
            let reader = self.0.take().ok_or_else(|| {
                crate::error::Error::new(
                    ErrorKind::InvalidArgument,
                    "the reader is already finished",
                )
            })?;
            Ok(Box::new(CityModel(reader.finish()?)))
        }
    }
}

pub use ffi::GmlReader;

/// The Rust readers behind the binding: ecitygml-io's `GmlReader` is generic over its source.
pub(crate) enum Reader {
    File(ecitygml::io::GmlReader<std::fs::File>),
    Bytes(ecitygml::io::GmlReader<std::io::Cursor<Vec<u8>>>),
}

impl Reader {
    fn with_rebuild_object_bounds(self, rebuild_object_bounds: bool) -> Self {
        match self {
            Reader::File(r) => Reader::File(r.with_rebuild_object_bounds(rebuild_object_bounds)),
            Reader::Bytes(r) => Reader::Bytes(r.with_rebuild_object_bounds(rebuild_object_bounds)),
        }
    }

    fn finish(self) -> Result<ecitygml::model::core::CityModel, ecitygml::io::Error> {
        match self {
            Reader::File(r) => r.finish(),
            Reader::Bytes(r) => r.finish(),
        }
    }
}
