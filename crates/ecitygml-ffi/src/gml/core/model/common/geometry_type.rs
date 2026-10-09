//! `GeometryType`, mirroring `egml::model::common::GeometryType`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    /// Type of a GML geometry.
    #[diplomat::enum_convert(egml::model::common::GeometryType)]
    #[derive(Debug, PartialEq, Eq)]
    pub enum GeometryType {
        // 0-D / 1-D primitives (geometryBasic0d1d.xsd, geometryPrimitives.xsd)
        Point,
        LineString,
        Curve,
        OrientableCurve,
        // Rings (geometryBasic2d.xsd, geometryPrimitives.xsd)
        LinearRing,
        Ring,
        // Surfaces (geometryBasic2d.xsd, geometryPrimitives.xsd)
        Polygon,
        Surface,
        OrientableSurface,
        PolyhedralSurface,
        TriangulatedSurface,
        Tin,
        Shell,
        // Solids (geometryPrimitives.xsd)
        Solid,
        // Aggregates (geometryAggregates.xsd)
        MultiGeometry,
        MultiPoint,
        MultiCurve,
        MultiSurface,
        MultiSolid,
        // Complexes (geometryComplexes.xsd)
        GeometricComplex,
        CompositeCurve,
        CompositeSurface,
        CompositeSolid,
        // Implicit / grid geometries (grids.xsd)
        Grid,
        RectifiedGrid,
    }
}

pub use ffi::GeometryType;
