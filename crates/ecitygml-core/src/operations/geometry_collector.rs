use crate::model::building::Building;
use crate::model::city_furniture::CityFurniture;
use crate::model::city_model::CitygmlModel;
use crate::model::construction::{
    DoorSurface, GroundSurface, RoofSurface, WallSurface, WindowSurface,
};
use crate::model::core::{ImplicitGeometry, OccupiedSpace, Space, ThematicSurface};
use crate::model::solitary_vegetation_object::SolitaryVegetationObject;
use crate::model::transportation::{
    AuxiliaryTrafficArea, AuxiliaryTrafficSpace, Intersection, Road, Section, TrafficArea,
    TrafficSpace,
};
use crate::operations::Visitor;
use egml::model::geometry::{DirectPosition, LinearRing, MultiSurface, Polygon, Solid};

#[derive(Debug, Clone, PartialEq, Default)]
pub struct GeometryCollector {
    pub multi_surface: Vec<MultiSurface>,
    pub solid: Vec<Solid>,
}

impl GeometryCollector {
    pub fn new() -> Self {
        Self {
            multi_surface: Vec::new(),
            solid: Vec::new(),
        }
    }
}

impl Visitor for GeometryCollector {
    type Result = ();

    fn visit_direct_position(&mut self, v: &DirectPosition) -> Self::Result {}

    fn visit_linear_ring(&mut self, v: &LinearRing) -> Self::Result {}

    fn visit_polygon(&mut self, v: &Polygon) -> Self::Result {}

    fn visit_multi_surface(&mut self, v: &MultiSurface) -> Self::Result {
        self.multi_surface.push(v.clone());
    }

    fn visit_solid(&mut self, v: &Solid) -> Self::Result {
        self.solid.push(v.clone());
    }

    fn visit_implicit_geometry(&mut self, v: &ImplicitGeometry) -> Self::Result {}

    fn visit_thematic_surface(&mut self, v: &ThematicSurface) -> Self::Result {}

    fn visit_space(&mut self, v: &Space) -> Self::Result {}

    fn visit_occupied_space(&mut self, v: &OccupiedSpace) -> Self::Result {}

    fn visit_city_model(&mut self, v: &CitygmlModel) -> Self::Result {}

    fn visit_city_furniture(&mut self, v: &CityFurniture) -> Self::Result {}

    fn visit_building(&mut self, v: &Building) -> Self::Result {}

    fn visit_roof_surface(&mut self, v: &RoofSurface) -> Self::Result {}

    fn visit_ground_surface(&mut self, v: &GroundSurface) -> Self::Result {}

    fn visit_wall_surface(&mut self, v: &WallSurface) -> Self::Result {}

    fn visit_window_surface(&mut self, v: &WindowSurface) -> Self::Result {}

    fn visit_door_surface(&mut self, v: &DoorSurface) -> Self::Result {}

    fn visit_solitary_vegetation_object(&mut self, v: &SolitaryVegetationObject) -> Self::Result {}

    fn visit_road(&mut self, v: &Road) -> Self::Result {}

    fn visit_section(&mut self, v: &Section) -> Self::Result {}

    fn visit_intersection(&mut self, v: &Intersection) -> Self::Result {}

    fn visit_traffic_space(&mut self, v: &TrafficSpace) -> Self::Result {}

    fn visit_auxiliary_traffic_space(&mut self, v: &AuxiliaryTrafficSpace) -> Self::Result {}

    fn visit_traffic_area(&mut self, v: &TrafficArea) -> Self::Result {}

    fn visit_auxiliary_traffic_area(&mut self, v: &AuxiliaryTrafficArea) -> Self::Result {}
}
