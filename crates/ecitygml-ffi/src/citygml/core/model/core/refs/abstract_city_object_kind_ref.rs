//! `AbstractCityObjectKindRef`, a reference to any city object of a city model, and its iterator.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::citygml::core::model::common::feature_type::ffi::FeatureType;

    /// A reference to a city object of any type; convert it with
    /// `AbstractFeatureKindRef::from_city_object` and then e.g. `Building::try_from`.
    #[diplomat::opaque]
    pub struct AbstractCityObjectKindRef<'a>(
        pub(crate) ecitygml::model::core::refs::AbstractCityObjectKindRef<'a>,
    );

    impl<'a> AbstractCityObjectKindRef<'a> {
        pub fn feature_type(&self) -> FeatureType {
            ecitygml::model::common::HasFeatureType::feature_type(&self.0).into()
        }
    }

    type CityObjectRefs<'a> =
        Box<dyn Iterator<Item = ecitygml::model::core::refs::AbstractCityObjectKindRef<'a>> + 'a>;

    /// Iterates over city objects of a city model, which it borrows.
    #[diplomat::opaque_mut]
    pub struct AbstractCityObjectKindRefIterator<'a>(pub(crate) CityObjectRefs<'a>);

    impl<'a> AbstractCityObjectKindRefIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<Box<AbstractCityObjectKindRef<'a>>> {
            self.0
                .next()
                .map(|city_object| Box::new(AbstractCityObjectKindRef(city_object)))
        }
    }
}

pub use ffi::{AbstractCityObjectKindRef, AbstractCityObjectKindRefIterator};
