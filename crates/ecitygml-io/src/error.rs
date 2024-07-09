use thiserror::Error;

#[derive(Error, Debug)]
pub enum Error {
    #[error(transparent)]
    Io(#[from] std::io::Error),
    #[error(transparent)]
    QuickXmlDeError(#[from] quick_xml::DeError),
    #[error(transparent)]
    GmlIoError(#[from] egml::io::Error),

    #[error("file extension is invalid")]
    NoFileExtension(),
    #[error("file extension `{0}` is invalid")]
    InvalidFileExtension(String),
    #[error("the data for key `{0}` is not available")]
    ElementNotFound(String),
}
