//! `Building`, mirroring `ecitygml::model::building::Building`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/building/abstract_building.rs")]
#[diplomat::include("src/citygml/core/model/construction/abstract_construction.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_occupied_space.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_physical_space.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_space.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_city_object.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_feature_with_lifespan.rs")]
#[diplomat::include("src/citygml/core/model/core/abstract_feature.rs")]
#[diplomat::include("src/gml/core/model/feature/abstract_feature.rs")]
#[diplomat::include("src/gml/core/model/base/abstract_gml.rs")]
#[diplomat::include("src/gml/core/model/abstract_object.rs")]
pub mod ffi {
    use crate::citygml::core::model::building::building_part_property::ffi::BuildingPartPropertyIterator;
    use crate::citygml::core::model::core::refs::abstract_feature_kind_ref::ffi::AbstractFeatureKindRef;

    /// A building, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct Building(ecitygml::model::building::Building);

    impl Building {
        impl_gml_abstract_object_methods! {}
        impl_gml_abstract_gml_methods! {}
        impl_gml_abstract_feature_methods! {}
        impl_abstract_feature_methods! {}
        impl_abstract_feature_with_lifespan_methods! {}
        impl_abstract_city_object_methods! {}
        impl_abstract_space_methods! {}
        impl_abstract_physical_space_methods! {}
        impl_abstract_occupied_space_methods! {}
        impl_abstract_construction_methods! {}
        impl_abstract_building_methods! {}

        /// The feature as a building, or none if it is another type (Rust: `<&Building>::try_from`).
        pub fn try_from<'a>(feature: &AbstractFeatureKindRef<'a>) -> Option<&'a Building> {
            <&ecitygml::model::building::Building>::try_from(feature.0)
                .ok()
                .map(Building::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn building_parts<'a>(&'a self) -> Box<BuildingPartPropertyIterator<'a>> {
            Box::new(BuildingPartPropertyIterator(self.0.building_parts().iter()))
        }
    }
}

pub use ffi::Building;
