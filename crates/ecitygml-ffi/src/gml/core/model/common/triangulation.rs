//! `Triangulation`, the result of `triangulate()`, mirroring `egml::model::common::Triangulation`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::error::ffi::Error;
    use crate::gml::core::model::geometry::primitives::triangulated_surface::ffi::TriangulatedSurface;

    /// A triangulated surface and the members that couldn't be triangulated.
    #[diplomat::opaque]
    pub struct Triangulation(pub(crate) egml::model::common::Triangulation);

    impl Triangulation {
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn surface<'a>(&'a self) -> &'a TriangulatedSurface {
            TriangulatedSurface::transparent_convert(self.0.surface())
        }

        /// Whether some members couldn't be triangulated.
        pub fn has_skipped(&self) -> bool {
            self.0.has_skipped()
        }

        /// Why members couldn't be triangulated, one error each.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn skipped<'a>(&'a self) -> Box<TriangulationSkippedIterator<'a>> {
            Box::new(TriangulationSkippedIterator(self.0.skipped().iter()))
        }
    }

    /// Iterates over the errors of skipped members, borrowed from a triangulation.
    #[diplomat::opaque_mut]
    pub struct TriangulationSkippedIterator<'a>(pub(crate) std::slice::Iter<'a, egml::Error>);

    impl<'a> TriangulationSkippedIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<Box<Error>> {
            self.0.next().map(|error| error.clone().into())
        }
    }
}

pub use ffi::{Triangulation, TriangulationSkippedIterator};
