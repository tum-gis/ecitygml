//! Methods of ecitygml's `AbstractTransportationSpace`, generated into the bridge of every transportation space type.
//!
//! Like all abstract-type macros (see `src/gml/core/model/feature/abstract_feature.rs`): each type invokes the
//! macro of every abstract supertype itself and includes this file with `#[diplomat::include(...)]`.

#[diplomat::macro_rules]
macro_rules! impl_abstract_transportation_space_methods {
    () => {
        pub fn traffic_direction(
            &self,
        ) -> Option<crate::citygml::core::model::transportation::enums::traffic_direction_value::ffi::TrafficDirectionValue> {
            ecitygml::model::transportation::AsAbstractTransportationSpace::traffic_direction(&self.0)
                .map(Into::into)
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn occupancies<'a>(
            &'a self,
        ) -> Box<crate::citygml::core::model::core::occupancy::ffi::OccupancyIterator<'a>> {
            Box::new(crate::citygml::core::model::core::occupancy::ffi::OccupancyIterator(
                ecitygml::model::transportation::AsAbstractTransportationSpace::occupancies(&self.0).iter(),
            ))
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn traffic_spaces<'a>(
            &'a self,
        ) -> Box<crate::citygml::core::model::transportation::traffic_space_property::ffi::TrafficSpacePropertyIterator<'a>> {
            Box::new(crate::citygml::core::model::transportation::traffic_space_property::ffi::TrafficSpacePropertyIterator(
                ecitygml::model::transportation::AsAbstractTransportationSpace::traffic_spaces(&self.0).iter(),
            ))
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn auxiliary_traffic_spaces<'a>(
            &'a self,
        ) -> Box<crate::citygml::core::model::transportation::auxiliary_traffic_space_property::ffi::AuxiliaryTrafficSpacePropertyIterator<'a>> {
            Box::new(crate::citygml::core::model::transportation::auxiliary_traffic_space_property::ffi::AuxiliaryTrafficSpacePropertyIterator(
                ecitygml::model::transportation::AsAbstractTransportationSpace::auxiliary_traffic_spaces(&self.0).iter(),
            ))
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn markings<'a>(
            &'a self,
        ) -> Box<crate::citygml::core::model::transportation::marking_property::ffi::MarkingPropertyIterator<'a>> {
            Box::new(crate::citygml::core::model::transportation::marking_property::ffi::MarkingPropertyIterator(
                ecitygml::model::transportation::AsAbstractTransportationSpace::markings(&self.0).iter(),
            ))
        }

        #[allow(clippy::needless_lifetimes)] // Diplomat rejects elided lifetimes in return types
        pub fn holes<'a>(
            &'a self,
        ) -> Box<crate::citygml::core::model::transportation::hole_property::ffi::HolePropertyIterator<'a>> {
            Box::new(crate::citygml::core::model::transportation::hole_property::ffi::HolePropertyIterator(
                ecitygml::model::transportation::AsAbstractTransportationSpace::holes(&self.0).iter(),
            ))
        }
    };
}
