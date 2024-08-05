use crate::model::construction::{GroundSurface, RoofSurface, WallSurface};
use crate::model::core::CityObject;
use crate::operations::{FeatureWithGeometry, Visitable, Visitor};
use egml::model::base;
use egml::model::base::Gml;
use egml::model::geometry::Envelope;
use nalgebra::Isometry3;

#[derive(Debug, Clone, PartialEq)]
pub struct Building {
    pub city_object: CityObject, // TODO: space
    pub wall_surface: Vec<WallSurface>,
    pub roof_surface: Vec<RoofSurface>,
    pub ground_surface: Vec<GroundSurface>,
}

impl Building {
    pub fn new(id: base::Id) -> Self {
        let gml = Gml::new(id);
        let city_object = CityObject::new(gml);

        Self {
            city_object,
            wall_surface: Vec::new(),
            roof_surface: Vec::new(),
            ground_surface: Vec::new(),
        }
    }
}

impl Visitable for Building {
    fn accept<V: Visitor>(&self, visitor: &mut V) {
        visitor.visit_building(self);
        self.wall_surface.iter().for_each(|x| x.accept(visitor));
        self.roof_surface.iter().for_each(|x| x.accept(visitor));
        self.ground_surface.iter().for_each(|x| x.accept(visitor));
    }
}

impl FeatureWithGeometry for Building {
    fn envelope(&self) -> Option<Envelope> {
        // todo: let mut envelopes: Vec<Option<Envelope>> = vec![self.occupied_space.envelope()];
        let mut envelopes: Vec<Option<Envelope>> = vec![];
        envelopes.extend(self.wall_surface.iter().map(|x| x.envelope()));
        envelopes.extend(self.roof_surface.iter().map(|x| x.envelope()));
        envelopes.extend(self.ground_surface.iter().map(|x| x.envelope()));

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
    }
}
