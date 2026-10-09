//! `Shell` (`gml:Shell`) and its iterator.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/gml/core/model/base/abstract_gml.rs")]
#[diplomat::include("src/gml/core/model/abstract_object.rs")]
#[diplomat::include("src/gml/core/model/common/triangulate.rs")]
pub mod ffi {
    use crate::error::ffi::Error;
    use crate::gml::core::model::geometry::direct_position::ffi::DirectPositionIterator;
    use crate::gml::core::model::geometry::envelope::ffi::Envelope;
    use crate::gml::core::model::geometry::primitives::abstract_surface_kind::ffi::AbstractSurfaceKind;
    use crate::gml::core::model::geometry::primitives::abstract_surface_property::ffi::AbstractSurfacePropertyIterator;

    /// A shell (closed surface), borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct Shell(egml::model::geometry::primitives::Shell);

    impl Shell {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}
        impl_triangulate_methods! {}

        /// The surface as a shell, or none if it is another type (Rust: `Shell::try_from`, which
        /// takes the surface by value).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn try_from<'a>(surface: &'a AbstractSurfaceKind) -> Option<&'a Shell> {
            match &surface.0 {
                egml::model::geometry::primitives::AbstractSurfaceKind::Shell(shell) => {
                    Some(Shell::transparent_convert(shell))
                }
                _ => None,
            }
        }

        /// The surface members (`gml:surfaceMember`).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn members<'a>(&'a self) -> Box<AbstractSurfacePropertyIterator<'a>> {
            Box::new(AbstractSurfacePropertyIterator(self.0.members().iter()))
        }

        /// All positions of the inline members.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn points<'a>(&'a self) -> Box<DirectPositionIterator<'a>> {
            Box::new(DirectPositionIterator(self.0.points().into_iter()))
        }

        pub fn area_3d(&self) -> Result<f64, Box<Error>> {
            Ok(self.0.area_3d()?)
        }

        /// Enclosed volume; fails with `UnresolvedReference` if a member is only an `xlink:href`.
        pub fn volume_3d(&self) -> Result<f64, Box<Error>> {
            Ok(self.0.volume_3d()?)
        }

        /// Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
        pub fn compute_envelope(&self) -> Option<Box<Envelope>> {
            egml::model::common::ComputeEnvelope::compute_envelope(&self.0)
                .map(|envelope| Box::new(Envelope(envelope)))
        }
    }

    /// Iterates over shells (e.g. a solid's interior shells), borrowed from a city model.
    #[diplomat::opaque_mut]
    pub struct ShellIterator<'a>(
        pub(crate) std::slice::Iter<'a, egml::model::geometry::primitives::Shell>,
    );

    impl<'a> ShellIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<&'a Shell> {
            self.0.next().map(Shell::transparent_convert)
        }
    }
}

pub use ffi::{Shell, ShellIterator};
