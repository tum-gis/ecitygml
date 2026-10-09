//! `CityObjectRelation`, mirroring `ecitygml::model::core::CityObjectRelation`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::citygml::core::model::core::values::relation_type_value::ffi::RelationTypeValue;
    use crate::citygml::core::model::generics::generic_attribute_kind::ffi::GenericAttributeKindIterator;
    use crate::gml::core::model::base::reference::ffi::Reference;

    /// A relation of a city object to another one, borrowed from a city model.
    #[diplomat::opaque]
    #[diplomat::transparent_convert]
    pub struct CityObjectRelation(ecitygml::model::core::CityObjectRelation);

    impl CityObjectRelation {
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn relation_type<'a>(&'a self) -> &'a RelationTypeValue {
            RelationTypeValue::transparent_convert(self.0.relation_type())
        }

        /// The related city object (`relatedTo`), by reference.
        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn relation_to<'a>(&'a self) -> &'a Reference {
            Reference::transparent_convert(self.0.relation_to())
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn generic_attributes<'a>(&'a self) -> Box<GenericAttributeKindIterator<'a>> {
            Box::new(GenericAttributeKindIterator(
                self.0.generic_attributes().iter(),
            ))
        }
    }
}

pub use ffi::CityObjectRelation;
