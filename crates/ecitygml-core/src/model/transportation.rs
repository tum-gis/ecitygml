use egml::{base, geometry};

#[derive(Debug, Clone, PartialEq)]
pub struct TrafficArea {
    id: base::Id,
    name: String,
    lod2_multi_surface: Option<geometry::MultiSurface>,
}

impl TrafficArea {
    pub fn new(id: base::Id, name: String) -> Self {
        Self {
            id,
            name,
            lod2_multi_surface: None,
        }
    }

    pub fn lod2_multi_surface(&self) -> &Option<geometry::MultiSurface> {
        &self.lod2_multi_surface
    }

    pub fn set_lod2_multi_surface(&mut self, lod2_multi_surface: Option<geometry::MultiSurface>) {
        self.lod2_multi_surface = lod2_multi_surface;
    }
}
