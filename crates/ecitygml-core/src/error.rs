use thiserror::Error;

#[derive(Error, Debug)]
pub enum EcitygmlError {
    #[error("the data for key `{0}` is not available")]
    ElementNotFound(String),
}
