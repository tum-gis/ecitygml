use crate::error::CitygmlIoError;
use crate::read_impl::read_from_file;
use nalgebra::Point3;
use std::path::{Path, PathBuf};

/// `CitygmlReader` reads CityGML datasets.
///
#[derive(Clone)]
pub struct CitygmlReader {
    path: PathBuf,
    corner_min: Option<Point3<f64>>,
    corner_max: Option<Point3<f64>>,
}

impl CitygmlReader {
    pub fn new(path: impl AsRef<Path>) -> Self {
        Self {
            path: path.as_ref().to_owned(),
            corner_min: None,
            corner_max: None,
        }
    }

    pub fn with_corner_min(mut self, corner_min: Option<Point3<f64>>) -> Self {
        self.corner_min = corner_min;
        self
    }

    pub fn with_corner_max(mut self, corner_max: Option<Point3<f64>>) -> Self {
        self.corner_max = corner_max;
        self
    }

    pub fn finish(self) -> Result<ecitygml_core::CitygmlModel, CitygmlIoError> {
        read_from_file(&self.path, &self.corner_min, &self.corner_max)
    }
}
