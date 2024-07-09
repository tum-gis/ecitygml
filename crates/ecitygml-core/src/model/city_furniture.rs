use egml::base;
use egml::geometry;

#[derive(Debug, Clone, PartialEq)]
pub struct CityFurniture {
    id: base::Id,
    name: String,
    reference_point: Option<geometry::DirectPosition>,
    lod2_multi_surface: Option<geometry::MultiSurface>,
    lod2_solid: Option<geometry::Solid>,
    lod1_solid: Option<geometry::Solid>,
}

impl CityFurniture {
    pub fn new(id: base::Id, name: String) -> Self {
        Self {
            id,
            name,
            reference_point: None,
            lod2_multi_surface: None,
            lod2_solid: None,
            lod1_solid: None,
        }
    }

    pub fn reference_point(&self) -> &Option<geometry::DirectPosition> {
        &self.reference_point
    }

    pub fn set_reference_point(&mut self, reference_point: Option<geometry::DirectPosition>) {
        self.reference_point = reference_point;
    }

    pub fn lod2_multi_surface(&self) -> &Option<geometry::MultiSurface> {
        &self.lod2_multi_surface
    }

    pub fn set_lod2_multi_surface(&mut self, lod2_multi_surface: Option<geometry::MultiSurface>) {
        self.lod2_multi_surface = lod2_multi_surface;
    }

    pub fn lod1_solid(&self) -> &Option<geometry::Solid> {
        &self.lod1_solid
    }

    pub fn set_lod1_solid(&mut self, lod2_solid: Option<geometry::Solid>) {
        self.lod1_solid = lod2_solid;
    }
    pub fn lod2_solid(&self) -> &Option<geometry::Solid> {
        &self.lod2_solid
    }

    pub fn set_lod2_solid(&mut self, lod2_solid: Option<geometry::Solid>) {
        self.lod2_solid = lod2_solid;
    }
}
