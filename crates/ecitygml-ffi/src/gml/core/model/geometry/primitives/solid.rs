//! `Solid` (`gml:Solid`).

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
    use crate::gml::core::model::geometry::primitives::shell::ffi::{Shell, ShellIterator};

    /// A solid, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct Solid(egml::model::geometry::primitives::Solid);

    impl Solid {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}
        impl_triangulate_methods! {}

        /// The geometry as a `Solid`, or none if it is another type (Rust: nested
        /// `AbstractGeometryKind` variants).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn try_from<'a>(
            geometry: &'a crate::gml::core::model::geometry::abstract_geometry_kind::ffi::AbstractGeometryKind,
        ) -> Option<&'a Solid> {
            match &geometry.0 {
                egml::model::geometry::AbstractGeometryKind::AbstractGeometricPrimitiveKind(egml::model::geometry::primitives::AbstractGeometricPrimitiveKind::AbstractSolidKind(egml::model::geometry::primitives::AbstractSolidKind::Solid(x))) => Some(Solid::transparent_convert(x)),
                _ => None,
            }
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn exterior<'a>(&'a self) -> Option<&'a Shell> {
            self.0.exterior().map(Shell::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn interior<'a>(&'a self) -> Box<ShellIterator<'a>> {
            Box::new(ShellIterator(self.0.interior().iter()))
        }

        /// Volume of the exterior shell. Stricter than Rust, which skips shell members it can't
        /// triangulate (and panics on some): fails with `UnresolvedReference` if a member is only an
        /// `xlink:href`, and with `InvalidArgument` if a member can't be triangulated, so the volume is
        /// never computed from an incomplete shell.
        pub fn volume_3d(&self) -> Result<f64, Box<Error>> {
            if let Some(shell) = self.0.exterior() {
                super::ensure_complete_triangulation(shell)?;
            }
            Ok(self.0.volume_3d()?)
        }

        /// Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
        pub fn compute_envelope(&self) -> Option<Box<Envelope>> {
            egml::model::common::ComputeEnvelope::compute_envelope(&self.0)
                .map(|envelope| Box::new(Envelope(envelope)))
        }

        /// All positions of the exterior shell.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn points<'a>(&'a self) -> Box<DirectPositionIterator<'a>> {
            Box::new(DirectPositionIterator(self.0.points().into_iter()))
        }
    }
}

pub use ffi::Solid;

use crate::error::{Error, ErrorKind};
use egml::model::base::HasAssociationAttributes;
use egml::model::common::Triangulate;
use egml::model::geometry::primitives::{
    AbstractRingKind, AbstractSurfaceKind, AbstractSurfacePatchKind, AbstractSurfaceProperty, Shell,
};

/// Fails instead of letting egml's triangulation panic (`todo!()` for polygons without exterior
/// ring or with non-linear rings) or silently skip members (unresolved `xlink:href`s, members that
/// fail to triangulate).
fn ensure_complete_triangulation(shell: &Shell) -> Result<(), Box<Error>> {
    ensure_triangulatable(shell.members())?;
    let triangulation = shell.triangulate()?;
    if let Some(first) = triangulation.skipped().first() {
        return Err(Error::new(
            ErrorKind::InvalidArgument,
            format!(
                "{} surface member(s) of the shell could not be triangulated, e.g.: {first}",
                triangulation.skipped().len()
            ),
        ));
    }
    Ok(())
}

fn ensure_triangulatable(members: &[AbstractSurfaceProperty]) -> Result<(), Box<Error>> {
    for member in members {
        match member.object() {
            None => {
                return Err(match member.href() {
                    Some(href) => Error::new(
                        ErrorKind::UnresolvedReference,
                        format!(
                            "surface member references '{href}' via xlink:href, which is not resolved"
                        ),
                    ),
                    None => Error::new(ErrorKind::InvalidArgument, "empty surface member"),
                });
            }
            Some(AbstractSurfaceKind::Polygon(x)) => {
                ensure_linear_rings(x.exterior(), x.interior())?
            }
            Some(AbstractSurfaceKind::CompositeSurface(x)) => {
                ensure_triangulatable(x.surface_member())?
            }
            Some(AbstractSurfaceKind::Shell(x)) => ensure_triangulatable(x.members())?,
            Some(AbstractSurfaceKind::Surface(x)) => {
                for patch in x.patches() {
                    if let AbstractSurfacePatchKind::PolygonPatch(p) = patch {
                        ensure_linear_rings(p.exterior(), p.interior())?;
                    }
                }
            }
            Some(AbstractSurfaceKind::SurfaceKind(_)) => {}
        }
    }
    Ok(())
}

fn ensure_linear_rings(
    exterior: Option<&AbstractRingKind>,
    interior: &[AbstractRingKind],
) -> Result<(), Box<Error>> {
    let invalid = |message: &str| Error::new(ErrorKind::InvalidArgument, message);
    let exterior =
        exterior.ok_or_else(|| invalid("cannot triangulate a polygon without exterior ring"))?;
    if std::iter::once(exterior)
        .chain(interior)
        .any(|ring| !matches!(ring, AbstractRingKind::LinearRing(_)))
    {
        return Err(invalid(
            "cannot triangulate a polygon with a ring other than gml:LinearRing",
        ));
    }
    Ok(())
}
