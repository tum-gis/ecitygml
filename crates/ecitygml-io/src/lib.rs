#![expect(
    clippy::module_inception,
    reason = "the modules mirror the CityGML packages and types, e.g. `model::building::building`"
)]

mod error;
mod format;
pub mod gml;

#[doc(inline)]
pub use crate::gml::read::GmlReader;

#[doc(inline)]
pub use crate::gml::write::GmlWriter;

#[doc(inline)]
pub use crate::error::Error;

#[doc(inline)]
pub use crate::format::CitygmlFormat;

#[doc(inline)]
pub use crate::gml::util::CitygmlVersion;

#[doc(inline)]
pub use crate::gml::FILE_EXTENSION_GML_FORMAT;

#[doc(inline)]
pub use crate::gml::FILE_EXTENSION_XML_FORMAT;

#[doc(inline)]
pub use crate::gml::FILE_EXTENSION_GML_ZST_FORMAT;

#[doc(inline)]
pub use crate::gml::FILE_EXTENSION_GML_GZ_FORMAT;
