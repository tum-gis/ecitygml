use crate::operations::{FeatureWithGeometry, Visitable, Visitor};
use egml::model::base::Gml;
use egml::model::geometry;
use egml::model::geometry::{DirectPosition, Envelope};
use egml::operations::geometry::Geometry;
use nalgebra::Isometry3;

#[derive(Debug, Clone, PartialEq)]
pub struct CityObject {
    pub gml: Gml,
    // TODO: generic_attributes: Vec<String>,
}

impl CityObject {
    pub fn new(gml: Gml) -> Self {
        Self { gml }
    }
}

#[derive(Debug, Clone, PartialEq, Default)]
pub struct ImplicitGeometry {
    pub reference_point: geometry::DirectPosition,
}

impl ImplicitGeometry {
    pub fn new(reference_point: geometry::DirectPosition) -> Self {
        Self { reference_point }
    }
}

impl Visitable for ImplicitGeometry {
    fn accept<V: Visitor>(&self, visitor: &mut V) {
        visitor.visit_implicit_geometry(self);
    }
}

impl Geometry for ImplicitGeometry {
    fn points(&self) -> Vec<&DirectPosition> {
        vec![&self.reference_point]
    }

    fn apply_transform(&mut self, m: &Isometry3<f64>) {
        self.reference_point.apply_transform(m);
    }
}

#[derive(Debug, Clone, PartialEq)]
pub struct Space {
    pub city_object: CityObject,

    pub lod1_solid: Option<geometry::Solid>,
    pub lod2_solid: Option<geometry::Solid>,
    pub lod3_solid: Option<geometry::Solid>,

    pub lod0_multi_surface: Option<geometry::MultiSurface>,
    pub lod2_multi_surface: Option<geometry::MultiSurface>,
    pub lod3_multi_surface: Option<geometry::MultiSurface>,
}

impl Space {
    pub fn new(city_object: CityObject) -> Self {
        Self {
            city_object,
            lod1_solid: None,
            lod2_solid: None,
            lod3_solid: None,
            lod0_multi_surface: None,
            lod2_multi_surface: None,
            lod3_multi_surface: None,
        }
    }
}

impl Visitable for Space {
    fn accept<V: Visitor>(&self, visitor: &mut V) {
        visitor.visit_space(self);

        if let Some(g) = &self.lod1_solid {
            g.accept(visitor);
        }
        if let Some(g) = &self.lod2_solid {
            g.accept(visitor);
        }
        if let Some(g) = &self.lod3_solid {
            g.accept(visitor);
        }
        if let Some(g) = &self.lod0_multi_surface {
            g.accept(visitor);
        }
        if let Some(g) = &self.lod2_multi_surface {
            g.accept(visitor);
        }
        if let Some(g) = &self.lod3_multi_surface {
            g.accept(visitor);
        }
    }
}

impl FeatureWithGeometry for Space {
    fn envelope(&self) -> Option<Envelope> {
        let envelopes: Vec<Option<Envelope>> = vec![
            self.lod1_solid.as_ref().map(|x| x.envelope()),
            self.lod2_solid.as_ref().map(|x| x.envelope()),
            self.lod3_solid.as_ref().map(|x| x.envelope()),
            self.lod0_multi_surface.as_ref().map(|x| x.envelope()),
            self.lod2_multi_surface.as_ref().map(|x| x.envelope()),
            self.lod3_multi_surface.as_ref().map(|x| x.envelope()),
        ];

        Envelope::from_optional_envelopes(&envelopes).expect("should work")
    }

    fn apply_transform(&mut self, m: &Isometry3<f64>) {
        if let Some(g) = &mut self.lod0_multi_surface {
            g.apply_transform(m);
        }
        if let Some(g) = &mut self.lod1_solid {
            g.apply_transform(m);
        }
        if let Some(g) = &mut self.lod2_solid {
            g.apply_transform(m);
        }
        if let Some(g) = &mut self.lod3_solid {
            g.apply_transform(m);
        }

        if let Some(g) = &mut self.lod0_multi_surface {
            g.apply_transform(m);
        }
        if let Some(g) = &mut self.lod2_multi_surface {
            g.apply_transform(m);
        }
        if let Some(g) = &mut self.lod3_multi_surface {
            g.apply_transform(m);
        }
    }
}

#[derive(Debug, Clone, PartialEq)]
pub struct OccupiedSpace {
    pub space: Space,
    pub lod1_implicit_representation: Option<ImplicitGeometry>,
    pub lod2_implicit_representation: Option<ImplicitGeometry>,
    pub lod3_implicit_representation: Option<ImplicitGeometry>,
}

impl OccupiedSpace {
    pub fn new(space: Space) -> Self {
        Self {
            space,
            lod1_implicit_representation: None,
            lod2_implicit_representation: None,
            lod3_implicit_representation: None,
        }
    }
}

impl Visitable for OccupiedSpace {
    fn accept<V: Visitor>(&self, visitor: &mut V) {
        visitor.visit_occupied_space(self);
        self.space.accept(visitor);
        if let Some(g) = &self.lod1_implicit_representation {
            g.accept(visitor);
        }
        if let Some(g) = &self.lod2_implicit_representation {
            g.accept(visitor);
        }
        if let Some(g) = &self.lod3_implicit_representation {
            g.accept(visitor);
        }
    }
}

impl FeatureWithGeometry for OccupiedSpace {
    fn envelope(&self) -> Option<Envelope> {
        let envelopes: Vec<Option<Envelope>> = vec![
            self.space.envelope(),
            self.lod1_implicit_representation
                .as_ref()
                .map(|x| x.envelope()),
            self.lod2_implicit_representation
                .as_ref()
                .map(|x| x.envelope()),
            self.lod3_implicit_representation
                .as_ref()
                .map(|x| x.envelope()),
        ];

        Envelope::from_optional_envelopes(&envelopes).expect("should work")
    }

    fn apply_transform(&mut self, m: &Isometry3<f64>) {
        self.space.apply_transform(m);

        if let Some(g) = &mut self.lod1_implicit_representation {
            g.apply_transform(m);
        }
        if let Some(g) = &mut self.lod2_implicit_representation {
            g.apply_transform(m);
        }
        if let Some(g) = &mut self.lod3_implicit_representation {
            g.apply_transform(m);
        }
    }
}

#[derive(Debug, Clone, PartialEq)]
pub struct ThematicSurface {
    pub city_object: CityObject,
    pub lod0_multi_surface: Option<geometry::MultiSurface>,
    pub lod1_multi_surface: Option<geometry::MultiSurface>,
    pub lod2_multi_surface: Option<geometry::MultiSurface>,
    pub lod3_multi_surface: Option<geometry::MultiSurface>,
}

impl ThematicSurface {
    pub fn new(city_object: CityObject) -> Self {
        Self {
            city_object,
            lod0_multi_surface: None,
            lod1_multi_surface: None,
            lod2_multi_surface: None,
            lod3_multi_surface: None,
        }
    }
}

impl Visitable for ThematicSurface {
    fn accept<V: Visitor>(&self, visitor: &mut V) {
        visitor.visit_thematic_surface(self);
        if let Some(g) = &self.lod0_multi_surface {
            g.accept(visitor);
        }
        if let Some(g) = &self.lod1_multi_surface {
            g.accept(visitor);
        }
        if let Some(g) = &self.lod2_multi_surface {
            g.accept(visitor);
        }
        if let Some(g) = &self.lod3_multi_surface {
            g.accept(visitor);
        }
    }
}

impl FeatureWithGeometry for ThematicSurface {
    fn envelope(&self) -> Option<Envelope> {
        let envelopes: Vec<Option<Envelope>> = vec![
            self.lod0_multi_surface.as_ref().map(|x| x.envelope()),
            self.lod1_multi_surface.as_ref().map(|x| x.envelope()),
            self.lod2_multi_surface.as_ref().map(|x| x.envelope()),
            self.lod3_multi_surface.as_ref().map(|x| x.envelope()),
        ];

        Envelope::from_optional_envelopes(&envelopes).expect("should work")
    }

    fn apply_transform(&mut self, m: &Isometry3<f64>) {
        if let Some(g) = &mut self.lod0_multi_surface {
            g.apply_transform(m);
        }
        if let Some(g) = &mut self.lod1_multi_surface {
            g.apply_transform(m);
        }
        if let Some(g) = &mut self.lod2_multi_surface {
            g.apply_transform(m);
        }
        if let Some(g) = &mut self.lod3_multi_surface {
            g.apply_transform(m);
        }
    }
}
