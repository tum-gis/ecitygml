use thiserror::Error;

#[derive(Error, Debug)]
pub enum EcitygmlIoError {
    #[error(transparent)]
    CitygmlError(#[from] ecitygml_core::EcitygmlError),
}
