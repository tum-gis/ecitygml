//! `CityObjectRelationProperty` (egml's `Property<CityObjectRelation>`) and its iterator.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::citygml::core::model::core::city_object_relation::ffi::CityObjectRelation;
    use crate::gml::core::model::xlink::href::ffi::HRef;
    use egml::model::base::HasAssociationAttributes;

    /// A city object relation property (inline relation and/or `xlink:href`), borrowed from a
    /// city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct CityObjectRelationProperty(ecitygml::model::core::CityObjectRelationProperty);

    impl CityObjectRelationProperty {
        /// The inline relation; none if the property only references one via `href`.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn object<'a>(&'a self) -> Option<&'a CityObjectRelation> {
            self.0.object().map(CityObjectRelation::transparent_convert)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn href<'a>(&'a self) -> Option<&'a HRef> {
            self.0.href().map(HRef::transparent_convert)
        }
    }

    type Properties<'a> = std::slice::Iter<'a, ecitygml::model::core::CityObjectRelationProperty>;

    /// Iterates over city object relation properties, borrowed from a city model.
    #[diplomat::opaque_mut]
    pub struct CityObjectRelationPropertyIterator<'a>(pub(crate) Properties<'a>);

    impl<'a> CityObjectRelationPropertyIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<&'a CityObjectRelationProperty> {
            self.0
                .next()
                .map(CityObjectRelationProperty::transparent_convert)
        }
    }
}

pub use ffi::{CityObjectRelationProperty, CityObjectRelationPropertyIterator};
