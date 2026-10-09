//! Methods of egml's `Triangulate` trait, generated into the bridge of every triangulatable type.
//!
//! Like the abstract-type macros (see `src/gml/core/model/feature/abstract_feature.rs`): each type
//! invokes the macro itself and includes this file with `#[diplomat::include(...)]`.

#[diplomat::macro_rules]
macro_rules! impl_triangulate_methods {
    () => {
        /// Triangulates the geometry (Rust: `Triangulate::triangulate`). Members that fail to
        /// triangulate are listed in `Triangulation::skipped`; as in egml, members that are only an
        /// `xlink:href` are left out without such an entry.
        pub fn triangulate(
            &self,
        ) -> Result<
            Box<crate::gml::core::model::common::triangulation::ffi::Triangulation>,
            Box<crate::error::ffi::Error>,
        > {
            Ok(Box::new(
                crate::gml::core::model::common::triangulation::ffi::Triangulation(
                    egml::model::common::Triangulate::triangulate(&self.0)?,
                ),
            ))
        }
    };
}
