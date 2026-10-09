use crate::error::Error;
use crate::gml::read_impl::deserialize;
use crate::gml::util::DeserializationConfig;
use std::fs::File;
use std::io::{BufReader, Read};

use crate::error::Error::InvalidFileExtension;
use crate::format::CitygmlFormat;
use ecitygml_core::model::core::CityModel;
use std::path::Path;

/// `CitygmlReader` reads CityGML datasets.
///
#[derive(Debug, Clone)]
pub struct GmlReader<R: Read> {
    reader: R,
    format: CitygmlFormat,
    config: DeserializationConfig,
    rebuild_object_bounds: bool,
}

impl<R: Read> GmlReader<R> {
    /// Create a new [`GmlReader`] from an existing `Reader`.
    pub fn new(reader: R, format: CitygmlFormat) -> Self {
        Self {
            reader,
            format,
            config: DeserializationConfig::default(),
            rebuild_object_bounds: true,
        }
    }

    fn read(self) -> Result<Vec<u8>, Error> {
        let mut content = Vec::new();

        match self.format {
            CitygmlFormat::Gml => {
                BufReader::new(self.reader).read_to_end(&mut content)?;
            }
            #[cfg(not(target_arch = "wasm32"))]
            CitygmlFormat::GmlZst => {
                zstd::Decoder::new(BufReader::new(self.reader))?.read_to_end(&mut content)?;
            }
            // Pure-Rust decoder (zstd's C code isn't built for WebAssembly).
            #[cfg(target_arch = "wasm32")]
            CitygmlFormat::GmlZst => {
                ruzstd::decoding::StreamingDecoder::new(BufReader::new(self.reader))
                    .map_err(|e| std::io::Error::new(std::io::ErrorKind::InvalidData, e))?
                    .read_to_end(&mut content)?;
            }
            CitygmlFormat::GmlGz => {
                flate2::read::GzDecoder::new(BufReader::new(self.reader))
                    .read_to_end(&mut content)?;
            }
        }

        Ok(content)
    }

    pub fn with_rebuild_object_bounds(mut self, rebuild_object_bounds: bool) -> Self {
        self.rebuild_object_bounds = rebuild_object_bounds;
        self
    }

    pub fn finish(self) -> Result<CityModel, Error> {
        let rebuild_object_bounds = self.rebuild_object_bounds;
        let deserialization_config = self.config;
        let mut city_model = deserialize(self.read()?, &deserialization_config)?;

        if rebuild_object_bounds {
            city_model.recompute_child_bounding_shapes();
        }

        Ok(city_model)
    }
}

impl GmlReader<File> {
    pub fn from_path(path: impl AsRef<Path>) -> Result<Self, Error> {
        let format = CitygmlFormat::from_path(path.as_ref()).ok_or_else(|| {
            InvalidFileExtension(
                path.as_ref()
                    .extension()
                    .and_then(|ext| ext.to_str())
                    .unwrap_or_default()
                    .to_string(),
            )
        })?;

        let file = std::fs::File::open(path.as_ref())?;

        Ok(Self::new(file, format))
    }
}
