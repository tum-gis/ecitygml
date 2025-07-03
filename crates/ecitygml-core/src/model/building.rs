use crate::model::construction::{GroundSurface, RoofSurface, WallSurface};
use crate::model::core::OccupiedSpace;
use crate::operations::{CityObjectVisitor, FeatureWithGeometry, Visitable};
use egml::model::geometry::Envelope;
use nalgebra::Isometry3;

#[derive(Debug, Clone, PartialEq)]
pub struct Building {
    pub occupied_space: OccupiedSpace,
    pub wall_surface: Vec<WallSurface>,
    pub roof_surface: Vec<RoofSurface>,
    pub ground_surface: Vec<GroundSurface>,
    pub building_constructive_element: Vec<BuildingConstructiveElement>,
}

impl Building {
    pub fn new(occupied_space: OccupiedSpace) -> Self {
        Self {
            occupied_space,
            wall_surface: Vec::new(),
            roof_surface: Vec::new(),
            ground_surface: Vec::new(),
            building_constructive_element: Vec::new(),
        }
    }
}

impl Visitable for Building {
    fn accept<V: CityObjectVisitor>(&self, visitor: &mut V) {
        visitor.visit_building(self);
        self.wall_surface.iter().for_each(|x| x.accept(visitor));
        self.roof_surface.iter().for_each(|x| x.accept(visitor));
        self.ground_surface.iter().for_each(|x| x.accept(visitor));
        self.building_constructive_element
            .iter()
            .for_each(|x| x.accept(visitor));
    }
}

impl FeatureWithGeometry for Building {
    fn envelope(&self) -> Option<Envelope> {
        // todo: let mut envelopes: Vec<Option<Envelope>> = vec![self.occupied_space.envelope()];
        let mut envelopes: Vec<Option<Envelope>> = vec![];
        envelopes.extend(self.wall_surface.iter().map(|x| x.envelope()));
        envelopes.extend(self.roof_surface.iter().map(|x| x.envelope()));
        envelopes.extend(self.ground_surface.iter().map(|x| x.envelope()));
        envelopes.extend(
            self.building_constructive_element
                .iter()
                .map(|x| x.envelope()),
        );

        Envelope::from_optional_envelopes(&envelopes).expect("should work")
    }

    fn apply_transform(&mut self, m: &Isometry3<f64>) {
        // todo: self.occupied_space.apply_transform(m);
        self.wall_surface
            .iter_mut()
            .for_each(|x| x.apply_transform(m));
        self.roof_surface
            .iter_mut()
            .for_each(|x| x.apply_transform(m));
        self.ground_surface
            .iter_mut()
            .for_each(|x| x.apply_transform(m));
        self.building_constructive_element
            .iter_mut()
            .for_each(|x| x.apply_transform(m));
    }
}

#[derive(Debug, Clone, PartialEq)]
pub struct BuildingConstructiveElement {
    pub occupied_space: OccupiedSpace,
}

impl BuildingConstructiveElement {
    pub fn new(occupied_space: OccupiedSpace) -> Self {
        Self { occupied_space }
    }
}

impl Visitable for BuildingConstructiveElement {
    fn accept<V: CityObjectVisitor>(&self, visitor: &mut V) {
        visitor.visit_building_constructive_element(self);
    }
}

impl FeatureWithGeometry for BuildingConstructiveElement {
    fn envelope(&self) -> Option<Envelope> {
        self.occupied_space.envelope()
    }

    fn apply_transform(&mut self, m: &Isometry3<f64>) {
        self.occupied_space.apply_transform(m);
    }
}
