//! The error type returned by fallible functions.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use diplomat_runtime::DiplomatWrite;
    use std::fmt::Write;

    /// Category of an [`Error`].
    #[derive(Debug, PartialEq, Eq)]
    pub enum ErrorKind {
        /// An argument is invalid, e.g. an unsupported file extension or a non-UTF-8 string.
        InvalidArgument,
        /// Reading a file failed.
        Io,
        /// The file content is not valid CityGML.
        Parse,
        /// Geometry is only referenced by `xlink:href` and the reference is not resolved.
        UnresolvedReference,
    }

    /// An error with its kind and a human-readable message.
    #[diplomat::opaque]
    #[diplomat::attr(auto, error)]
    #[derive(Debug)]
    pub struct Error {
        pub(crate) kind: ErrorKind,
        pub(crate) message: String,
    }

    impl Error {
        pub fn kind(&self) -> ErrorKind {
            self.kind
        }

        // Python: `str(error)`, so raised exceptions show the message.
        #[diplomat::attr(nanobind, stringifier)]
        // JS builds thrown errors from `toString()`; its backend has no stringifier support.
        #[diplomat::attr(js, rename = "toString")]
        pub fn message(&self, write: &mut DiplomatWrite) {
            let _ = write.write_str(&self.message);
        }
    }
}

pub use ffi::{Error, ErrorKind};

impl Error {
    pub fn new(kind: ErrorKind, message: impl Into<String>) -> Box<Self> {
        Box::new(Self {
            kind,
            message: message.into(),
        })
    }
}

impl From<ecitygml::io::Error> for Box<Error> {
    fn from(error: ecitygml::io::Error) -> Self {
        use ecitygml::io::Error as E;
        let kind = match &error {
            E::InvalidFileExtension(_) | E::NoFileExtension() | E::NoFileName() => {
                ErrorKind::InvalidArgument
            }
            E::StdIo(_) => ErrorKind::Io,
            _ => ErrorKind::Parse,
        };
        Error::new(kind, error.to_string())
    }
}

/// Validates a string argument as UTF-8.
pub fn utf8<'a>(value: &'a [u8], argument: &str) -> Result<&'a str, Box<Error>> {
    std::str::from_utf8(value).map_err(|e| {
        Error::new(
            ErrorKind::InvalidArgument,
            format!("argument `{argument}` is not valid UTF-8: {e}"),
        )
    })
}

impl From<ecitygml::Error> for Box<Error> {
    fn from(error: ecitygml::Error) -> Self {
        match error {
            ecitygml::Error::GmlError(error) => error.into(),
            _ => Error::new(ErrorKind::InvalidArgument, error.to_string()),
        }
    }
}

impl From<egml::Error> for Box<Error> {
    fn from(error: egml::Error) -> Self {
        let kind = match error {
            egml::Error::UnresolvedSurfaceReference { .. }
            | egml::Error::UnresolvedCurveReference { .. } => ErrorKind::UnresolvedReference,
            _ => ErrorKind::InvalidArgument,
        };
        Error::new(kind, error.to_string())
    }
}
