use crate::model::core::{Space, ThematicSurface};
use crate::operations::{CityObjectVisitor, FeatureWithGeometry, Visitable};
use egml::model::geometry::Envelope;
use nalgebra::Isometry3;

#[derive(Debug, Clone, PartialEq)]
pub struct Road {
    pub space: Space,
    pub section: Vec<Section>,
    pub intersection: Vec<Intersection>,
}

impl Road {
    pub fn new(space: Space) -> Self {
        Self {
            space,
            section: Default::default(),
            intersection: Default::default(),
        }
    }
}

impl Visitable for Road {
    fn accept<V: CityObjectVisitor>(&self, visitor: &mut V) {
        visitor.visit_road(self);
        self.section.iter().for_each(|x| x.accept(visitor));
        self.intersection.iter().for_each(|x| x.accept(visitor));
    }
}

impl FeatureWithGeometry for Road {
    fn envelope(&self) -> Option<Envelope> {
        let mut envelopes: Vec<Option<Envelope>> = vec![];
        envelopes.extend(self.section.iter().map(|x| x.envelope()));
        envelopes.extend(self.intersection.iter().map(|x| x.envelope()));

        Envelope::from_optional_envelopes(&envelopes).expect("should work")
    }

    fn apply_transform(&mut self, m: &Isometry3<f64>) {
        self.section.iter_mut().for_each(|x| x.apply_transform(m));
        self.intersection
            .iter_mut()
            .for_each(|x| x.apply_transform(m));
    }
}

#[derive(Debug, Clone, PartialEq)]
pub struct Section {
    pub space: Space,
    pub traffic_space: Vec<TrafficSpace>,
    pub auxiliary_traffic_space: Vec<AuxiliaryTrafficSpace>,
}

impl Section {
    pub fn new(space: Space) -> Self {
        Self {
            space,
            traffic_space: Vec::new(),
            auxiliary_traffic_space: Vec::new(),
        }
    }
}

impl Visitable for Section {
    fn accept<V: CityObjectVisitor>(&self, visitor: &mut V) {
        visitor.visit_section(self);
        self.traffic_space.iter().for_each(|x| x.accept(visitor));
        self.auxiliary_traffic_space
            .iter()
            .for_each(|x| x.accept(visitor));
    }
}

impl FeatureWithGeometry for Section {
    fn envelope(&self) -> Option<Envelope> {
        let mut envelopes: Vec<Option<Envelope>> = vec![];
        envelopes.extend(self.traffic_space.iter().map(|x| x.envelope()));
        envelopes.extend(self.auxiliary_traffic_space.iter().map(|x| x.envelope()));

        Envelope::from_optional_envelopes(&envelopes).expect("should work")
    }

    fn apply_transform(&mut self, m: &Isometry3<f64>) {
        self.traffic_space
            .iter_mut()
            .for_each(|x| x.apply_transform(m));
        self.auxiliary_traffic_space
            .iter_mut()
            .for_each(|x| x.apply_transform(m));
    }
}

#[derive(Debug, Clone, PartialEq)]
pub struct Intersection {
    pub space: Space,
    pub traffic_space: Vec<TrafficSpace>,
    pub auxiliary_traffic_space: Vec<AuxiliaryTrafficSpace>,
}

impl Intersection {
    pub fn new(space: Space) -> Self {
        Self {
            space,
            traffic_space: Vec::new(),
            auxiliary_traffic_space: Vec::new(),
        }
    }
}

impl Visitable for Intersection {
    fn accept<V: CityObjectVisitor>(&self, visitor: &mut V) {
        visitor.visit_intersection(self);
        self.traffic_space.iter().for_each(|x| x.accept(visitor));
        self.auxiliary_traffic_space
            .iter()
            .for_each(|x| x.accept(visitor));
    }
}

impl FeatureWithGeometry for Intersection {
    fn envelope(&self) -> Option<Envelope> {
        let mut envelopes: Vec<Option<Envelope>> = vec![];
        envelopes.extend(self.traffic_space.iter().map(|x| x.envelope()));
        envelopes.extend(self.auxiliary_traffic_space.iter().map(|x| x.envelope()));

        Envelope::from_optional_envelopes(&envelopes).expect("should work")
    }

    fn apply_transform(&mut self, m: &Isometry3<f64>) {
        self.traffic_space
            .iter_mut()
            .for_each(|x| x.apply_transform(m));
        self.auxiliary_traffic_space
            .iter_mut()
            .for_each(|x| x.apply_transform(m));
    }
}

#[derive(Debug, Clone, PartialEq)]
pub struct TrafficSpace {
    pub space: Space,
    pub traffic_area: Vec<TrafficArea>, // this should be located in boundaries the space struct
}

impl TrafficSpace {
    pub fn new(space: Space) -> Self {
        Self {
            space,
            traffic_area: Vec::new(),
        }
    }
}

impl Visitable for TrafficSpace {
    fn accept<V: CityObjectVisitor>(&self, visitor: &mut V) {
        visitor.visit_traffic_space(self);
        self.traffic_area.iter().for_each(|x| x.accept(visitor));
    }
}

impl FeatureWithGeometry for TrafficSpace {
    fn envelope(&self) -> Option<Envelope> {
        let mut envelopes: Vec<Option<Envelope>> = vec![self.space.envelope()];
        envelopes.extend(self.traffic_area.iter().map(|x| x.envelope()));

        Envelope::from_optional_envelopes(&envelopes).expect("should work")
    }

    fn apply_transform(&mut self, m: &Isometry3<f64>) {
        self.space.apply_transform(m);
        self.traffic_area
            .iter_mut()
            .for_each(|x| x.apply_transform(m));
    }
}

#[derive(Debug, Clone, PartialEq)]
pub struct AuxiliaryTrafficSpace {
    pub space: Space,
    pub auxiliary_traffic_area: Vec<AuxiliaryTrafficArea>, // this should be located in boundaries the space struct
}

impl AuxiliaryTrafficSpace {
    pub fn new(space: Space) -> Self {
        Self {
            space,
            auxiliary_traffic_area: Vec::new(),
        }
    }
}

impl Visitable for AuxiliaryTrafficSpace {
    fn accept<V: CityObjectVisitor>(&self, visitor: &mut V) {
        visitor.visit_auxiliary_traffic_space(self);
        self.auxiliary_traffic_area
            .iter()
            .for_each(|x| x.accept(visitor));
    }
}

impl FeatureWithGeometry for AuxiliaryTrafficSpace {
    fn envelope(&self) -> Option<Envelope> {
        let mut envelopes: Vec<Option<Envelope>> = vec![self.space.envelope()];
        envelopes.extend(self.auxiliary_traffic_area.iter().map(|x| x.envelope()));

        Envelope::from_optional_envelopes(&envelopes).expect("should work")
    }

    fn apply_transform(&mut self, m: &Isometry3<f64>) {
        self.space.apply_transform(m);
        self.auxiliary_traffic_area
            .iter_mut()
            .for_each(|x| x.apply_transform(m));
    }
}

#[derive(Debug, Clone, PartialEq)]
pub struct TrafficArea {
    pub thematic_surface: ThematicSurface,
}

impl TrafficArea {
    pub fn new(thematic_surface: ThematicSurface) -> Self {
        Self { thematic_surface }
    }
}

impl Visitable for TrafficArea {
    fn accept<V: CityObjectVisitor>(&self, visitor: &mut V) {
        visitor.visit_traffic_area(self);
    }
}

impl FeatureWithGeometry for TrafficArea {
    fn envelope(&self) -> Option<Envelope> {
        self.thematic_surface.envelope()
    }

    fn apply_transform(&mut self, m: &Isometry3<f64>) {
        self.thematic_surface.apply_transform(m);
    }
}

#[derive(Debug, Clone, PartialEq)]
pub struct AuxiliaryTrafficArea {
    pub thematic_surface: ThematicSurface,
}

impl AuxiliaryTrafficArea {
    pub fn new(thematic_surface: ThematicSurface) -> Self {
        Self { thematic_surface }
    }
}

impl Visitable for AuxiliaryTrafficArea {
    fn accept<V: CityObjectVisitor>(&self, visitor: &mut V) {
        visitor.visit_auxiliary_traffic_area(self);
    }
}

impl FeatureWithGeometry for AuxiliaryTrafficArea {
    fn envelope(&self) -> Option<Envelope> {
        self.thematic_surface.envelope()
    }

    fn apply_transform(&mut self, m: &Isometry3<f64>) {
        self.thematic_surface.apply_transform(m);
    }
}
