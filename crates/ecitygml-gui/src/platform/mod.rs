//! Platform-specific parts of the viewer: logging, the window, opening and saving files, and
//! background work. The desktop build uses native dialogs and threads; the web build
//! (`wasm32`) uses the browser's file picker, downloads, and defers work to the next frame.

#[cfg(not(target_arch = "wasm32"))]
mod native;
#[cfg(not(target_arch = "wasm32"))]
pub use native::*;

#[cfg(target_arch = "wasm32")]
mod web;
#[cfg(target_arch = "wasm32")]
pub use web::*;

/// File extensions offered in the open dialog.
pub const CITYGML_EXTENSIONS: &[&str] = &["gml", "xml", "zst", "gz"];

/// Window title (desktop) and page title (web).
pub const TITLE: &str = "ecitygml viewer";
