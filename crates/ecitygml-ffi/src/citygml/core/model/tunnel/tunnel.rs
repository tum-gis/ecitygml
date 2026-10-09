//! `Tunnel`, mirroring `ecitygml::model::tunnel::Tunnel`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
#[diplomat::include("src/citygml/core/model/tunnel/abstract_tunnel.rs")]
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
    use crate::citygml::core::model::core::refs::abstract_feature_kind_ref::ffi::AbstractFeatureKindRef;
    use crate::citygml::core::model::tunnel::tunnel_part_property::ffi::TunnelPartPropertyIterator;

    /// A tunnel, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct Tunnel(ecitygml::model::tunnel::Tunnel);

    impl Tunnel {
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
        impl_abstract_tunnel_methods! {}

        /// The feature as a tunnel, or none if it is another type (Rust: `<&Tunnel>::try_from`).
        pub fn try_from<'a>(feature: &AbstractFeatureKindRef<'a>) -> Option<&'a Tunnel> {
            <&ecitygml::model::tunnel::Tunnel>::try_from(feature.0)
                .ok()
                .map(Tunnel::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn tunnel_parts<'a>(&'a self) -> Box<TunnelPartPropertyIterator<'a>> {
            Box::new(TunnelPartPropertyIterator(self.0.tunnel_parts().iter()))
        }
    }
}

pub use ffi::Tunnel;
