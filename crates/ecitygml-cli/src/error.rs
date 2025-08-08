use thiserror::Error;

#[derive(Error, Debug)]
pub enum Error {
    #[error(transparent)]
    EcitygmlError(#[from] ecitygml::Error),
    #[error(transparent)]
    EcitygmlIoError(#[from] ecitygml::io::Error),

    #[error(transparent)]
    StdIoError(#[from] std::io::Error),
}
