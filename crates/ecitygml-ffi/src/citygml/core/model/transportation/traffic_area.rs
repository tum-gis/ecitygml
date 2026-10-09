//! `TrafficArea`, mirroring `ecitygml::model::transportation::TrafficArea`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/core/abstract_thematic_surface.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_space_boundary.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_city_object.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_feature_with_lifespan.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_feature.rs")]
#[diplomat::include("src/gml/core/model/feature/abstract_feature.rs")]
#[diplomat::include("src/gml/core/model/base/abstract_gml.rs")]
#[diplomat::include("src/gml/core/model/abstract_object.rs")]
pub mod ffi {
    use crate::citygml::core::model::core::refs::abstract_feature_kind_ref::ffi::AbstractFeatureKindRef;
    use crate::citygml::core::model::transportation::values::surface_material_value::ffi::SurfaceMaterialValue;
    use crate::citygml::core::model::transportation::values::traffic_area_class_value::ffi::TrafficAreaClassValue;
    use crate::citygml::core::model::transportation::values::traffic_area_function_value::ffi::TrafficAreaFunctionValueIterator;
    use crate::citygml::core::model::transportation::values::traffic_area_usage_value::ffi::TrafficAreaUsageValueIterator;

    /// A traffic area, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct TrafficArea(ecitygml::model::transportation::TrafficArea);

    impl TrafficArea {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}
        impl_gml_abstract_feature_methods! {}
        impl_abstract_feature_methods! {}
        impl_abstract_feature_with_lifespan_methods! {}
        impl_abstract_city_object_methods! {}
        impl_abstract_space_boundary_methods! {}
        impl_abstract_thematic_surface_methods! {}

        /// The feature as a traffic area, or none if it is another type (Rust: `<&TrafficArea>::try_from`).
        pub fn try_from<'a>(feature: &AbstractFeatureKindRef<'a>) -> Option<&'a TrafficArea> {
            <&ecitygml::model::transportation::TrafficArea>::try_from(feature.0)
                .ok()
                .map(TrafficArea::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn class<'a>(&'a self) -> Option<&'a TrafficAreaClassValue> {
            self.0
                .class()
                .map(TrafficAreaClassValue::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn functions<'a>(&'a self) -> Box<TrafficAreaFunctionValueIterator<'a>> {
            Box::new(TrafficAreaFunctionValueIterator(self.0.functions().iter()))
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn usages<'a>(&'a self) -> Box<TrafficAreaUsageValueIterator<'a>> {
            Box::new(TrafficAreaUsageValueIterator(self.0.usages().iter()))
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn surface_material<'a>(&'a self) -> Option<&'a SurfaceMaterialValue> {
            self.0
                .surface_material()
                .map(SurfaceMaterialValue::transparent_convert)
        }
    }
}

pub use ffi::TrafficArea;
