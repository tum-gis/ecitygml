use egml::model::geometry::Envelope;
use nalgebra::Isometry3;

pub trait FeatureWithGeometry {
    fn envelope(&self) -> Option<Envelope>;

    fn apply_transform(&mut self, m: &Isometry3<f64>);
}
/*
pub trait SpaceFeature {
    fn collect_multi_surfaces(&self) -> HashMap<LevelOfDetail, &MultiSurface>;
    fn collect_solids(&self) -> HashMap<LevelOfDetail, &Solid>;
}

#[derive(Debug, Clone, PartialEq, Eq, Hash)]
pub struct GeometryId {
    feature_id: Id,
    geometry_id: Id,
}

#[derive(Debug, Clone, PartialEq, Default)]
pub struct GeometryCollection<'a> {
    pub multi_surface: HashMap<GeometryId, &'a MultiSurface>,
    pub solid: HashMap<GeometryId, &'a Solid>,
}
impl GeometryCollection<'_> {}*/
