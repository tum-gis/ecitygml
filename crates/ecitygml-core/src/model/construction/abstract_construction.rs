use crate::model::common::{ForEachFeatureMut, IterFeatures};
use crate::model::construction::construction_event::ConstructionEvent;
use crate::model::construction::elevation::Elevation;
use crate::model::construction::height::Height;
use crate::model::core::refs::AbstractFeatureKindRef;
use crate::model::core::refs::AbstractFeatureKindRefMut;
use crate::model::core::{
    AbstractOccupiedSpace, AsAbstractOccupiedSpace, AsAbstractOccupiedSpaceMut, Occupancy,
};
use egml::model::base::Id;
use egml::model::common::{ApplyTransform, ComputeEnvelope};
use egml::model::geometry::Envelope;
use egml::model::xs::Date;
use nalgebra::{Isometry3, Rotation3, Scale3, Transform3, Vector3};

#[derive(Debug, Clone, PartialEq)]
pub struct AbstractConstruction {
    pub(crate) abstract_occupied_space: AbstractOccupiedSpace,
    date_of_construction: Option<Date>,
    date_of_demolition: Option<Date>,
    construction_events: Vec<ConstructionEvent>,
    elevations: Vec<Elevation>,
    heights: Vec<Height>,
    occupancies: Vec<Occupancy>,
}

impl AbstractConstruction {
    pub fn new(id: Id) -> Self {
        Self::from_abstract_occupied_space(AbstractOccupiedSpace::new(id))
    }

    pub fn from_abstract_occupied_space(abstract_occupied_space: AbstractOccupiedSpace) -> Self {
        Self {
            abstract_occupied_space,
            date_of_construction: None,
            date_of_demolition: None,
            construction_events: Vec::new(),
            elevations: Vec::new(),
            heights: Vec::new(),
            occupancies: Vec::new(),
        }
    }
}

pub trait AsAbstractConstruction: AsAbstractOccupiedSpace {
    fn abstract_construction(&self) -> &AbstractConstruction;

    fn date_of_construction(&self) -> Option<&Date> {
        self.abstract_construction().date_of_construction.as_ref()
    }

    fn date_of_demolition(&self) -> Option<&Date> {
        self.abstract_construction().date_of_demolition.as_ref()
    }

    fn construction_events(&self) -> &[ConstructionEvent] {
        self.abstract_construction().construction_events.as_ref()
    }

    fn elevations(&self) -> &[Elevation] {
        self.abstract_construction().elevations.as_ref()
    }

    fn heights(&self) -> &[Height] {
        self.abstract_construction().heights.as_ref()
    }

    fn occupancies(&self) -> &[Occupancy] {
        self.abstract_construction().occupancies.as_ref()
    }
}

pub trait AsAbstractConstructionMut: AsAbstractOccupiedSpaceMut + AsAbstractConstruction {
    fn abstract_construction_mut(&mut self) -> &mut AbstractConstruction;

    fn set_date_of_construction(&mut self, date_of_construction: Option<Date>) {
        self.abstract_construction_mut().date_of_construction = date_of_construction;
    }

    fn set_date_of_demolition(&mut self, date_of_demolition: Option<Date>) {
        self.abstract_construction_mut().date_of_demolition = date_of_demolition;
    }

    fn construction_events_mut(&mut self) -> &mut Vec<ConstructionEvent> {
        &mut self.abstract_construction_mut().construction_events
    }

    fn set_construction_events(&mut self, values: Vec<ConstructionEvent>) {
        self.abstract_construction_mut().construction_events = values;
    }

    fn push_construction_event(&mut self, construction_event: ConstructionEvent) {
        self.abstract_construction_mut()
            .construction_events
            .push(construction_event);
    }

    fn extend_construction_events(
        &mut self,
        construction_events: impl IntoIterator<Item = ConstructionEvent>,
    ) {
        self.abstract_construction_mut()
            .construction_events
            .extend(construction_events);
    }

    fn elevations_mut(&mut self) -> &mut Vec<Elevation> {
        &mut self.abstract_construction_mut().elevations
    }

    fn set_elevations(&mut self, values: Vec<Elevation>) {
        self.abstract_construction_mut().elevations = values;
    }

    fn push_elevation(&mut self, elevation: Elevation) {
        self.abstract_construction_mut().elevations.push(elevation);
    }

    fn extend_elevations(&mut self, elevations: impl IntoIterator<Item = Elevation>) {
        self.abstract_construction_mut()
            .elevations
            .extend(elevations);
    }

    fn heights_mut(&mut self) -> &mut Vec<Height> {
        &mut self.abstract_construction_mut().heights
    }

    fn set_heights(&mut self, values: Vec<Height>) {
        self.abstract_construction_mut().heights = values;
    }

    fn push_height(&mut self, height: Height) {
        self.abstract_construction_mut().heights.push(height);
    }

    fn extend_heights(&mut self, heights: impl IntoIterator<Item = Height>) {
        self.abstract_construction_mut().heights.extend(heights);
    }

    fn occupancies_mut(&mut self) -> &mut Vec<Occupancy> {
        &mut self.abstract_construction_mut().occupancies
    }

    fn set_occupancies(&mut self, values: Vec<Occupancy>) {
        self.abstract_construction_mut().occupancies = values;
    }

    fn push_occupancy(&mut self, occupancy: Occupancy) {
        self.abstract_construction_mut().occupancies.push(occupancy);
    }

    fn extend_occupancies(&mut self, occupancies: impl IntoIterator<Item = Occupancy>) {
        self.abstract_construction_mut()
            .occupancies
            .extend(occupancies);
    }
}

impl AsAbstractConstruction for AbstractConstruction {
    fn abstract_construction(&self) -> &AbstractConstruction {
        self
    }
}

impl AsAbstractConstructionMut for AbstractConstruction {
    fn abstract_construction_mut(&mut self) -> &mut AbstractConstruction {
        self
    }
}

#[macro_export]
macro_rules! impl_abstract_construction_traits {
    ($type:ty) => {
        $crate::impl_abstract_occupied_space_traits!($type);

        impl $crate::model::core::AsAbstractOccupiedSpace for $type {
            fn abstract_occupied_space(&self) -> &$crate::model::core::AbstractOccupiedSpace {
                &<$type as $crate::model::construction::AsAbstractConstruction>::abstract_construction(self).abstract_occupied_space
            }
        }
    };
}

#[macro_export]
macro_rules! impl_abstract_construction_mut_traits {
    ($type:ty) => {
        $crate::impl_abstract_occupied_space_mut_traits!($type);

        impl $crate::model::core::AsAbstractOccupiedSpaceMut for $type {
            fn abstract_occupied_space_mut(
                &mut self,
            ) -> &mut $crate::model::core::AbstractOccupiedSpace {
                &mut <$type as $crate::model::construction::AsAbstractConstructionMut>::abstract_construction_mut(self).abstract_occupied_space
            }
        }
    };
}

impl_abstract_construction_traits!(AbstractConstruction);
impl_abstract_construction_mut_traits!(AbstractConstruction);

impl IterFeatures for AbstractConstruction {
    fn iter_features(&self) -> Box<dyn Iterator<Item = AbstractFeatureKindRef<'_>> + '_> {
        self.abstract_occupied_space.iter_features()
    }
}

impl ForEachFeatureMut for AbstractConstruction {
    fn for_each_feature_mut<F: FnMut(AbstractFeatureKindRefMut<'_>)>(&mut self, f: &mut F) {
        self.abstract_occupied_space.for_each_feature_mut(f);
    }
}

impl ComputeEnvelope for AbstractConstruction {
    fn compute_envelope(&self) -> Option<Envelope> {
        self.abstract_occupied_space.compute_envelope()
    }
}

impl ApplyTransform for AbstractConstruction {
    fn apply_transform(&mut self, m: Transform3<f64>) {
        self.abstract_occupied_space.apply_transform(m);
    }

    fn apply_isometry(&mut self, isometry: Isometry3<f64>) {
        self.abstract_occupied_space.apply_isometry(isometry);
    }

    fn apply_translation(&mut self, vector: Vector3<f64>) {
        self.abstract_occupied_space.apply_translation(vector);
    }

    fn apply_rotation(&mut self, rotation: Rotation3<f64>) {
        self.abstract_occupied_space.apply_rotation(rotation);
    }

    fn apply_scale(&mut self, scale: Scale3<f64>) {
        self.abstract_occupied_space.apply_scale(scale);
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::model::basic_types::Code;

    fn event(name: &str) -> ConstructionEvent {
        ConstructionEvent::new(
            Code::new(name).into(),
            Date::from_parts(2015, 6, 1, 0).expect("valid date"),
        )
    }

    #[test]
    fn test_construction_events_accessors() {
        let mut abstract_construction =
            AbstractConstruction::new(Id::try_from("construction").expect("valid id"));
        assert!(abstract_construction.construction_events().is_empty());

        abstract_construction.push_construction_event(event("construction"));
        abstract_construction.extend_construction_events([event("renovation")]);
        assert_eq!(abstract_construction.construction_events().len(), 2);

        abstract_construction.set_construction_events(vec![event("demolition")]);
        assert_eq!(
            abstract_construction.construction_events(),
            &[event("demolition")]
        );
    }

    #[test]
    fn test_elevations_accessors() {
        use crate::model::construction::ElevationValue;

        let elevation = |value: f64| {
            Elevation::new(
                Code::new("generalGroundSurface").into(),
                ElevationValue::new(vec![value]).expect("should work"),
            )
        };
        let mut abstract_construction =
            AbstractConstruction::new(Id::try_from("construction").expect("valid id"));
        assert!(abstract_construction.elevations().is_empty());

        abstract_construction.push_elevation(elevation(105.3));
        abstract_construction.extend_elevations([elevation(106.0)]);
        assert_eq!(abstract_construction.elevations().len(), 2);

        abstract_construction.set_elevations(vec![elevation(107.0)]);
        assert_eq!(abstract_construction.elevations(), &[elevation(107.0)]);
    }
}
