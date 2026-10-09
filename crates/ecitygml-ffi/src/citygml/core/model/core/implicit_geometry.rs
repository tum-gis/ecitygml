//! `ImplicitGeometry`, mirroring `ecitygml::model::core::ImplicitGeometry`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::citygml::core::model::core::transformation_matrix_4x4::ffi::TransformationMatrix4x4;
    use crate::citygml::core::model::core::values::mime_type_value::ffi::MimeTypeValue;
    use crate::gml::core::model::base::id::ffi::Id;
    use crate::gml::core::model::geometry::abstract_geometry_property::ffi::AbstractGeometryProperty;
    use crate::gml::core::model::geometry::envelope::ffi::Envelope;
    use crate::gml::core::model::geometry::primitives::point_property::ffi::PointProperty;

    /// A prototype geometry placed by a transformation and a reference point, borrowed from a city
    /// model. Not bound yet: appearances.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct ImplicitGeometry(ecitygml::model::core::ImplicitGeometry);

    impl ImplicitGeometry {
        /// Identifies the implicit geometry (from its `gml:id`).
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn object_id<'a>(&'a self) -> &'a Id {
            Id::transparent_convert(self.0.object_id())
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn transformation_matrix<'a>(&'a self) -> &'a TransformationMatrix4x4 {
            TransformationMatrix4x4::transparent_convert(self.0.transformation_matrix())
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn mime_type<'a>(&'a self) -> Option<&'a MimeTypeValue> {
            self.0.mime_type().map(MimeTypeValue::transparent_convert)
        }

        /// Reference to the prototype in an external library.
        // Not in .NET: diplomat-tool 0.16 can't return an optional borrowed string there yet.
        #[diplomat::attr(dotnet, disable)]
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn library_object<'a>(&'a self) -> Option<&'a str> {
            self.0.library_object()
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn reference_point<'a>(&'a self) -> &'a PointProperty {
            PointProperty::transparent_convert(self.0.reference_point())
        }

        /// The prototype geometry, in its own coordinate system.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn relative_geometry<'a>(&'a self) -> Option<&'a AbstractGeometryProperty> {
            self.0
                .relative_geometry()
                .map(AbstractGeometryProperty::transparent_convert)
        }

        /// Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
        pub fn compute_envelope(&self) -> Option<Box<Envelope>> {
            egml::model::common::ComputeEnvelope::compute_envelope(&self.0)
                .map(|envelope| Box::new(Envelope(envelope)))
        }
    }
}

pub use ffi::ImplicitGeometry;
