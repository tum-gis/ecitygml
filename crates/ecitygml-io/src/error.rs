use egml::io::error::GmlIoError;
use thiserror::Error;

#[derive(Error, Debug)]
pub enum CitygmlIoError {
    #[error(transparent)]
    Io(#[from] std::io::Error),
    #[error(transparent)]
    GmlIoError(#[from] GmlIoError),

    #[error("the data for key `{0}` is not available")]
    ElementNotFound(String),
}
