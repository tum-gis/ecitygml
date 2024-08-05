use crate::model::core::OccupiedSpace;
use crate::operations::{FeatureWithGeometry, Visitable, Visitor};
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
    fn accept<V: Visitor>(&self, visitor: &mut V) {
        visitor.visit_solitary_vegetation_object(self);
        self.occupied_space.accept(visitor);
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
