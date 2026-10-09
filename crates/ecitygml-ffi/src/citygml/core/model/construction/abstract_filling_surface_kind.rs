//! `AbstractFillingSurfaceKind`, mirroring `ecitygml::model::construction::AbstractFillingSurfaceKind`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/construction/abstract_filling_surface.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_thematic_surface.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_space_boundary.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_city_object.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_feature_with_lifespan.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_feature.rs")]
#[diplomat::include("src/gml/core/model/feature/abstract_feature.rs")]
#[diplomat::include("src/gml/core/model/base/abstract_gml.rs")]
#[diplomat::include("src/gml/core/model/abstract_object.rs")]
pub mod ffi {
    use crate::citygml::core::model::common::feature_type::ffi::FeatureType;

    /// A filling surface (door or window surface), borrowed from a city model. It has the getters of
    /// every ancestor, like the concrete types; `feature_type()` tells which one it is.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct AbstractFillingSurfaceKind(
        ecitygml::model::construction::AbstractFillingSurfaceKind,
    );

    impl AbstractFillingSurfaceKind {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}
        impl_gml_abstract_feature_methods! {}
        impl_abstract_feature_methods! {}
        impl_abstract_feature_with_lifespan_methods! {}
        impl_abstract_city_object_methods! {}
        impl_abstract_space_boundary_methods! {}
        impl_abstract_thematic_surface_methods! {}
        impl_abstract_filling_surface_methods! {}

        pub fn feature_type(&self) -> FeatureType {
            ecitygml::model::common::HasFeatureType::feature_type(&self.0).into()
        }
    }
}

pub use ffi::AbstractFillingSurfaceKind;
