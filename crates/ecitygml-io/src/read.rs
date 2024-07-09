use crate::error::Error;
use crate::read_impl::read_from_file;
use std::fs::File;
use std::io::{Read, Seek};

use crate::error::Error::{InvalidFileExtension, NoFileExtension};
use crate::validate_impl::validate_from_reader;
use crate::{FILE_EXTENSION_CITYGML_GML_FORMAT, FILE_EXTENSION_CITYGML_XML_FORMAT};
use std::path::Path;

/// `CitygmlReader` reads CityGML datasets.
///
#[derive(Debug, Clone)]
pub struct CitygmlReader<R: Read + Seek> {
    reader: R,
}

impl<R: Read + Seek> CitygmlReader<R> {
    /// Create a new [`CitygmlReader`] from an existing `Reader`.
    pub fn new(reader: R) -> Self {
        Self { reader }
    }

    pub fn validate(self) -> Result<crate::validate::report::Report, Error> {
        validate_from_reader(self.reader)
    }

    pub fn finish(self) -> Result<ecitygml_core::CitygmlModel, Error> {
        read_from_file(self.reader)
    }
}

impl CitygmlReader<File> {
    pub fn from_path(path: impl AsRef<Path>) -> Result<Self, Error> {
        let extension = path.as_ref().extension().ok_or(NoFileExtension())?;
        if extension != FILE_EXTENSION_CITYGML_GML_FORMAT
            && extension != FILE_EXTENSION_CITYGML_XML_FORMAT
        {
            return Err(InvalidFileExtension(
                extension.to_str().unwrap_or_default().to_string(),
            ));
        }

        let file = std::fs::File::open(path)?;
        Ok(Self::new(file))
    }
}
