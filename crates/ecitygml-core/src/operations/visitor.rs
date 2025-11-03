use crate::model::building::{Building, BuildingConstructiveElement};
use crate::model::city_furniture::CityFurniture;
use crate::model::city_model::CitygmlModel;
use crate::model::construction::{
    DoorSurface, GroundSurface, RoofSurface, WallSurface, WindowSurface,
};
use crate::model::solitary_vegetation_object::SolitaryVegetationObject;
use crate::model::transportation::{
    AuxiliaryTrafficArea, AuxiliaryTrafficSpace, Intersection, Road, Section, TrafficArea,
    TrafficSpace,
};

pub trait Visitable {
    fn accept<V: CityObjectVisitor>(&self, visitor: &mut V);
}

pub trait CityObjectVisitor {
    type Result;

    fn visit_city_model(&mut self, v: &CitygmlModel) -> Self::Result;

    fn visit_city_furniture(&mut self, v: &CityFurniture) -> Self::Result;

    fn visit_building(&mut self, v: &Building) -> Self::Result;
    fn visit_building_constructive_element(
        &mut self,
        v: &BuildingConstructiveElement,
    ) -> Self::Result;
    fn visit_roof_surface(&mut self, v: &RoofSurface) -> Self::Result;
    fn visit_ground_surface(&mut self, v: &GroundSurface) -> Self::Result;
    fn visit_wall_surface(&mut self, v: &WallSurface) -> Self::Result;
    fn visit_window_surface(&mut self, v: &WindowSurface) -> Self::Result;
    fn visit_door_surface(&mut self, v: &DoorSurface) -> Self::Result;

    fn visit_solitary_vegetation_object(&mut self, v: &SolitaryVegetationObject) -> Self::Result;

    fn visit_road(&mut self, v: &Road) -> Self::Result;
    fn visit_section(&mut self, v: &Section) -> Self::Result;
    fn visit_intersection(&mut self, v: &Intersection) -> Self::Result;
    fn visit_traffic_space(&mut self, v: &TrafficSpace) -> Self::Result;
    fn visit_auxiliary_traffic_space(&mut self, v: &AuxiliaryTrafficSpace) -> Self::Result;
    fn visit_traffic_area(&mut self, v: &TrafficArea) -> Self::Result;
    fn visit_auxiliary_traffic_area(&mut self, v: &AuxiliaryTrafficArea) -> Self::Result;
}

pub struct Interpreter;

impl Default for Interpreter {
    fn default() -> Self {
        Self::new()
    }
}

impl Interpreter {
    pub fn new() -> Self {
        Self {}
    }
}
impl CityObjectVisitor for Interpreter {
    type Result = ();

    fn visit_city_model(&mut self, v: &CitygmlModel) -> Self::Result {
        println!("hello city_model");
    }

    fn visit_city_furniture(&mut self, v: &CityFurniture) -> Self::Result {
        println!(
            "hello city_furniture {}",
            v.occupied_space.space.city_object.abstract_gml.id
        );
    }

    fn visit_building(&mut self, v: &Building) -> Self::Result {
        println!(
            "hello building {}",
            v.occupied_space.space.city_object.abstract_gml.id
        );
    }

    fn visit_building_constructive_element(
        &mut self,
        v: &BuildingConstructiveElement,
    ) -> Self::Result {
        println!(
            "hello building_constructive_element {}",
            v.occupied_space.space.city_object.abstract_gml.id
        );
    }

    fn visit_roof_surface(&mut self, v: &RoofSurface) -> Self::Result {
        println!(
            "hello roof_surface {}",
            v.thematic_surface.city_object.abstract_gml.id
        );
    }

    fn visit_ground_surface(&mut self, v: &GroundSurface) -> Self::Result {
        println!(
            "hello ground_surface {}",
            v.thematic_surface.city_object.abstract_gml.id
        );
    }

    fn visit_wall_surface(&mut self, v: &WallSurface) -> Self::Result {
        println!(
            "hello wall_surface {}",
            v.thematic_surface.city_object.abstract_gml.id
        );
    }

    fn visit_window_surface(&mut self, v: &WindowSurface) -> Self::Result {
        println!(
            "hello window_surface {}",
            v.occupied_space.space.city_object.abstract_gml.id
        );
    }

    fn visit_door_surface(&mut self, v: &DoorSurface) -> Self::Result {
        println!(
            "hello door_surface {}",
            v.occupied_space.space.city_object.abstract_gml.id
        );
    }

    fn visit_solitary_vegetation_object(&mut self, v: &SolitaryVegetationObject) -> Self::Result {
        println!(
            "hello solitary_vegetation_object {}",
            v.occupied_space.space.city_object.abstract_gml.id
        );
    }

    fn visit_road(&mut self, v: &Road) -> Self::Result {
        println!("hello road {}", v.space.city_object.abstract_gml.id);
    }

    fn visit_section(&mut self, v: &Section) -> Self::Result {
        println!("hello section {}", v.space.city_object.abstract_gml.id);
    }

    fn visit_intersection(&mut self, v: &Intersection) -> Self::Result {
        println!("hello intersection {}", v.space.city_object.abstract_gml.id);
    }

    fn visit_traffic_space(&mut self, v: &TrafficSpace) -> Self::Result {
        println!(
            "hello traffic_space {}",
            v.space.city_object.abstract_gml.id
        );
    }

    fn visit_auxiliary_traffic_space(&mut self, v: &AuxiliaryTrafficSpace) -> Self::Result {
        println!(
            "hello auxiliary_traffic_space {}",
            v.space.city_object.abstract_gml.id
        );
    }

    fn visit_traffic_area(&mut self, v: &TrafficArea) -> Self::Result {
        println!(
            "hello traffic_area {}",
            v.thematic_surface.city_object.abstract_gml.id
        );
    }

    fn visit_auxiliary_traffic_area(&mut self, v: &AuxiliaryTrafficArea) -> Self::Result {
        println!(
            "hello auxiliary_traffic_area {}",
            v.thematic_surface.city_object.abstract_gml.id
        );
    }
}
