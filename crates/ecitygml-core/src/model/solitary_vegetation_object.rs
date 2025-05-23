use crate::model::core::OccupiedSpace;
use crate::operations::{CityObjectVisitor, FeatureWithGeometry, Visitable};
use egml::model::geometry::Envelope;
use nalgebra::Isometry3;

#[derive(Debug, Clone, PartialEq)]
pub struct SolitaryVegetationObject {
    pub occupied_space: OccupiedSpace,
}

impl SolitaryVegetationObject {
    pub fn new(occupied_space: OccupiedSpace) -> Self {
        Self { occupied_space }
    }
}

impl Visitable for SolitaryVegetationObject {
    fn accept<V: CityObjectVisitor>(&self, visitor: &mut V) {
        visitor.visit_solitary_vegetation_object(self);
    }
}

impl FeatureWithGeometry for SolitaryVegetationObject {
    fn envelope(&self) -> Option<Envelope> {
        self.occupied_space.envelope()
    }

    fn apply_transform(&mut self, m: &Isometry3<f64>) {
        self.occupied_space.apply_transform(m);
    }
}
