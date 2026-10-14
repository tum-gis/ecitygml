use thiserror::Error;

#[derive(Error, Debug)]
pub enum Error {
    #[error(transparent)]
    Ecitygml(#[from] ecitygml::Error),
    #[error(transparent)]
    EcitygmlIo(#[from] ecitygml::io::Error),

    #[error(transparent)]
    StdIo(#[from] std::io::Error),
}
