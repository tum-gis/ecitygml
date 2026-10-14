//! `AbstractCityObjectKind`, mirroring `ecitygml::model::core::AbstractCityObjectKind`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/core/abstract_city_object.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_feature_with_lifespan.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_feature.rs")]
#[diplomat::include("src/gml/core/model/feature/abstract_feature.rs")]
#[diplomat::include("src/gml/core/model/base/abstract_gml.rs")]
#[diplomat::include("src/gml/core/model/abstract_object.rs")]
pub mod ffi {
    use crate::citygml::core::model::common::feature_type::ffi::FeatureType;

    /// A city object of any type (e.g. a building or road), borrowed from a city model. It has the
    /// getters of every ancestor; for the concrete type, convert it with
    /// `AbstractCityObjectKindRef::from_city_object`, `AbstractFeatureKindRef::from_city_object` and
    /// e.g. `Building::try_from`.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct AbstractCityObjectKind(pub(crate) ecitygml::model::core::AbstractCityObjectKind);

    impl AbstractCityObjectKind {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}
        impl_gml_abstract_feature_methods! {}
        impl_abstract_feature_methods! {}
        impl_abstract_feature_with_lifespan_methods! {}
        impl_abstract_city_object_methods! {}

        pub fn feature_type(&self) -> FeatureType {
            ecitygml::model::common::HasFeatureType::feature_type(&self.0).into()
        }
    }
}

pub use ffi::AbstractCityObjectKind;
