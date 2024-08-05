use crate::model::core::{OccupiedSpace, ThematicSurface};
use crate::operations::{FeatureWithGeometry, Visitable, Visitor};
use egml::model::geometry::Envelope;
use nalgebra::Isometry3;

#[derive(Debug, Clone, PartialEq)]
pub struct WallSurface {
    pub thematic_surface: ThematicSurface,
    pub door_surface: Vec<DoorSurface>,
    pub window_surface: Vec<WindowSurface>,
}

impl WallSurface {
    pub fn new(thematic_surface: ThematicSurface) -> Self {
        Self {
            thematic_surface,
            door_surface: Vec::new(),
            window_surface: Vec::new(),
        }
    }
}

impl Visitable for WallSurface {
    fn accept<V: Visitor>(&self, visitor: &mut V) {
        visitor.visit_wall_surface(self);
        self.thematic_surface.accept(visitor);
        self.door_surface.iter().for_each(|x| x.accept(visitor));
        self.window_surface.iter().for_each(|x| x.accept(visitor));
    }
}

impl FeatureWithGeometry for WallSurface {
    fn envelope(&self) -> Option<Envelope> {
        let mut envelopes: Vec<Option<Envelope>> = vec![self.thematic_surface.envelope()];
        envelopes.extend(self.door_surface.iter().map(|x| x.envelope()));
        envelopes.extend(self.window_surface.iter().map(|x| x.envelope()));

        Envelope::from_optional_envelopes(&envelopes).expect("should work")
    }

    fn apply_transform(&mut self, m: &Isometry3<f64>) {
        self.thematic_surface.apply_transform(m);
        self.door_surface
            .iter_mut()
            .for_each(|x| x.apply_transform(m));
        self.window_surface
            .iter_mut()
            .for_each(|x| x.apply_transform(m));
    }
}

#[derive(Debug, Clone, PartialEq)]
pub struct RoofSurface {
    pub thematic_surface: ThematicSurface,
}

impl RoofSurface {
    pub fn new(thematic_surface: ThematicSurface) -> Self {
        Self { thematic_surface }
    }
}

impl Visitable for RoofSurface {
    fn accept<V: Visitor>(&self, visitor: &mut V) {
        visitor.visit_roof_surface(self);
        self.thematic_surface.accept(visitor);
    }
}

impl FeatureWithGeometry for RoofSurface {
    fn envelope(&self) -> Option<Envelope> {
        self.thematic_surface.envelope()
    }

    fn apply_transform(&mut self, m: &Isometry3<f64>) {
        self.thematic_surface.apply_transform(m);
    }
}

#[derive(Debug, Clone, PartialEq)]
pub struct GroundSurface {
    pub thematic_surface: ThematicSurface,
}

impl GroundSurface {
    pub fn new(thematic_surface: ThematicSurface) -> Self {
        Self { thematic_surface }
    }
}

impl Visitable for GroundSurface {
    fn accept<V: Visitor>(&self, visitor: &mut V) {
        visitor.visit_ground_surface(self);
        self.thematic_surface.accept(visitor);
    }
}

impl FeatureWithGeometry for GroundSurface {
    fn envelope(&self) -> Option<Envelope> {
        self.thematic_surface.envelope()
    }

    fn apply_transform(&mut self, m: &Isometry3<f64>) {
        self.thematic_surface.apply_transform(m);
    }
}

#[derive(Debug, Clone, PartialEq)]
pub struct WindowSurface {
    pub occupied_space: OccupiedSpace,
}

impl WindowSurface {
    pub fn new(occupied_space: OccupiedSpace) -> Self {
        Self { occupied_space }
    }
}

impl Visitable for WindowSurface {
    fn accept<V: Visitor>(&self, visitor: &mut V) {
        visitor.visit_window_surface(self);
        self.occupied_space.accept(visitor);
    }
}

impl FeatureWithGeometry for WindowSurface {
    fn envelope(&self) -> Option<Envelope> {
        self.occupied_space.envelope()
    }

    fn apply_transform(&mut self, m: &Isometry3<f64>) {
        self.occupied_space.apply_transform(m);
    }
}

#[derive(Debug, Clone, PartialEq)]
pub struct DoorSurface {
    pub occupied_space: OccupiedSpace,
}

impl DoorSurface {
    pub fn new(occupied_space: OccupiedSpace) -> Self {
        Self { occupied_space }
    }
}

impl Visitable for DoorSurface {
    fn accept<V: Visitor>(&self, visitor: &mut V) {
        visitor.visit_door_surface(self);
        self.occupied_space.accept(visitor);
    }
}

impl FeatureWithGeometry for DoorSurface {
    fn envelope(&self) -> Option<Envelope> {
        self.occupied_space.envelope()
    }

    fn apply_transform(&mut self, m: &Isometry3<f64>) {
        self.occupied_space.apply_transform(m);
    }
}
