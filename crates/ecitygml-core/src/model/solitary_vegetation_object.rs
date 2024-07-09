use egml::{base, geometry};

#[derive(Debug, Clone, PartialEq)]
pub struct SolitaryVegetationObject {
    id: base::Id,
    name: String,
    lod1_solid: Option<geometry::Solid>,
}

impl SolitaryVegetationObject {
    pub fn new(id: base::Id, name: String) -> Self {
        Self {
            id,
            name,
            lod1_solid: None,
        }
    }

    pub fn lod1_solid(&self) -> &Option<geometry::Solid> {
        &self.lod1_solid
    }

    pub fn set_lod1_solid(&mut self, lod1_solid: Option<geometry::Solid>) {
        self.lod1_solid = lod1_solid;
    }
}
