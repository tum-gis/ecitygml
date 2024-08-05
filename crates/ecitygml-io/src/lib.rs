mod error;
mod parser;
mod read;
mod read_impl;
pub mod validate;
mod validate_impl;

#[doc(inline)]
pub use crate::read::CitygmlReader;

#[doc(inline)]
pub use crate::error::Error;

pub const FILE_EXTENSION_CITYGML_GML_FORMAT: &str = "gml";
pub const FILE_EXTENSION_CITYGML_XML_FORMAT: &str = "xml";
