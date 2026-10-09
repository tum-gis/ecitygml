//! `CitygmlFormat`, the encoding of CityGML content, mirroring `ecitygml::io::CitygmlFormat`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    /// Encoding of CityGML content.
    #[diplomat::enum_convert(ecitygml::io::CitygmlFormat)]
    #[derive(Debug, PartialEq, Eq)]
    pub enum CitygmlFormat {
        /// Plain GML (`.gml`, `.xml`).
        Gml,
        /// Zstandard-compressed GML (`.gml.zst`).
        GmlZst,
        /// Gzip-compressed GML (`.gml.gz`).
        GmlGz,
    }
}

pub use ffi::CitygmlFormat;
