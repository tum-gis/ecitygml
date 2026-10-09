//! `AbstractFeatureKindRef`, a reference to any feature of a city model, and its iterator.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use crate::citygml::core::model::common::feature_type::ffi::FeatureType;
    use crate::citygml::core::model::core::refs::abstract_city_object_kind_ref::ffi::AbstractCityObjectKindRef;

    /// A reference to a feature of any type; convert it with e.g. `TrafficSpace::try_from`.
    #[diplomat::opaque]
    pub struct AbstractFeatureKindRef<'a>(
        pub(crate) ecitygml::model::core::refs::AbstractFeatureKindRef<'a>,
    );

    impl<'a> AbstractFeatureKindRef<'a> {
        /// The feature a space boundary is (Rust: `From<&AbstractSpaceBoundaryKind>`), to convert it
        /// with e.g. `WallSurface::try_from`.
        pub fn from_space_boundary(
            boundary: &'a crate::citygml::core::model::core::abstract_space_boundary_kind::ffi::AbstractSpaceBoundaryKind,
        ) -> Box<AbstractFeatureKindRef<'a>> {
            Box::new(AbstractFeatureKindRef(
                ecitygml::model::core::refs::AbstractFeatureKindRef::from(&boundary.0),
            ))
        }

        /// The feature a city object is, to convert it with e.g. `Building::try_from` (Rust wraps it in
        /// the `AbstractFeatureWithLifespanKind(AbstractCityObjectKind(_))` variants; it has no `From`).
        pub fn from_city_object(
            city_object: &AbstractCityObjectKindRef<'a>,
        ) -> Box<AbstractFeatureKindRef<'a>> {
            Box::new(AbstractFeatureKindRef(
                ecitygml::model::core::refs::AbstractFeatureKindRef::AbstractFeatureWithLifespanKind(
                    ecitygml::model::core::refs::AbstractFeatureWithLifespanKindRef::AbstractCityObjectKind(
                        city_object.0,
                    ),
                ),
            ))
        }

        pub fn feature_type(&self) -> FeatureType {
            ecitygml::model::common::HasFeatureType::feature_type(&self.0).into()
        }
    }

    type FeatureRefs<'a> =
        Box<dyn Iterator<Item = ecitygml::model::core::refs::AbstractFeatureKindRef<'a>> + 'a>;

    /// Iterates over features of a city model, which it borrows.
    #[diplomat::opaque_mut]
    pub struct AbstractFeatureKindRefIterator<'a>(pub(crate) FeatureRefs<'a>);

    impl<'a> AbstractFeatureKindRefIterator<'a> {
        #[diplomat::attr(auto, iterator)]
        #[allow(clippy::should_implement_trait)] // Diplomat's iterator protocol, not `Iterator`
        pub fn next(&mut self) -> Option<Box<AbstractFeatureKindRef<'a>>> {
            self.0
                .next()
                .map(|feature| Box::new(AbstractFeatureKindRef(feature)))
        }
    }
}

pub use ffi::{AbstractFeatureKindRef, AbstractFeatureKindRefIterator};
