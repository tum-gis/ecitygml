use crate::model::core::OccupiedSpace;
use crate::operations::{CityObjectVisitor, FeatureWithGeometry, Visitable};
use egml::model::geometry::Envelope;
use nalgebra::Isometry3;

#[derive(Debug, Clone, PartialEq)]
pub struct CityFurniture {
    pub occupied_space: OccupiedSpace,
}

impl CityFurniture {
    pub fn new(occupied_space: OccupiedSpace) -> Self {
        Self { occupied_space }
    }
}

impl Visitable for CityFurniture {
    fn accept<V: CityObjectVisitor>(&self, visitor: &mut V) {
        visitor.visit_city_furniture(self);
    }
}

impl FeatureWithGeometry for CityFurniture {
    fn envelope(&self) -> Option<Envelope> {
        self.occupied_space.envelope()
    }

    fn apply_transform(&mut self, m: &Isometry3<f64>) {
        self.occupied_space.apply_transform(m);
    }
}
