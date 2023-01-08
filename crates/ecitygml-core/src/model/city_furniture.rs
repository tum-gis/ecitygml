use egml::base;
use egml::geometry::DirectPosition;

#[derive(Debug, Clone, PartialEq)]
pub struct CityFurniture {
    id: base::Id,
    name: String,
    reference_point: Option<DirectPosition>,
}

impl CityFurniture {
    pub fn new(id: base::Id, name: String) -> Self {
        Self {
            id,
            name,
            reference_point: None,
        }
    }

    pub fn reference_point(&self) -> &Option<DirectPosition> {
        &self.reference_point
    }

    pub fn set_reference_point(&mut self, reference_point: Option<DirectPosition>) {
        self.reference_point = reference_point;
    }
}
