use egml::geometry::LinearRing;

#[derive(Debug, Clone, PartialEq, Default)]
pub struct CityObject {
    pub name: String,
    pub geometries: Vec<LinearRing>,
}
