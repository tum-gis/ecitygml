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
use egml::model::geometry::{DirectPosition, LinearRing, MultiSurface, Polygon, Solid};
use egml::operations::geometry::Geometry;

pub trait Visitable {
    fn accept<V: Visitor>(&self, visitor: &mut V);
}

pub trait Visitor {
    type Result;

    fn visit_direct_position(&mut self, v: &DirectPosition) -> Self::Result;
    fn visit_linear_ring(&mut self, v: &LinearRing) -> Self::Result;
    fn visit_polygon(&mut self, v: &Polygon) -> Self::Result;
    fn visit_multi_surface(&mut self, v: &MultiSurface) -> Self::Result;
    fn visit_solid(&mut self, v: &Solid) -> Self::Result;

    fn visit_implicit_geometry(&mut self, v: &ImplicitGeometry) -> Self::Result;
    fn visit_thematic_surface(&mut self, v: &ThematicSurface) -> Self::Result;
    fn visit_space(&mut self, v: &Space) -> Self::Result;
    fn visit_occupied_space(&mut self, v: &OccupiedSpace) -> Self::Result;

    fn visit_city_model(&mut self, v: &CitygmlModel) -> Self::Result;

    fn visit_city_furniture(&mut self, v: &CityFurniture) -> Self::Result;

    fn visit_building(&mut self, v: &Building) -> Self::Result;
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
impl Visitor for Interpreter {
    type Result = ();

    fn visit_direct_position(&mut self, v: &DirectPosition) -> Self::Result {
        println!("hello direct_position");
    }

    fn visit_linear_ring(&mut self, v: &LinearRing) -> Self::Result {
        println!("hello linear_ring {}", v.gml.id);
    }

    fn visit_polygon(&mut self, v: &Polygon) -> Self::Result {
        println!("hello polygon {}", v.gml.id);
    }

    fn visit_multi_surface(&mut self, v: &MultiSurface) -> Self::Result {
        println!("hello multi_surface {}", v.gml.id);
    }

    fn visit_solid(&mut self, v: &Solid) -> Self::Result {
        println!("hello solid {}", v.gml.id);
    }

    fn visit_implicit_geometry(&mut self, v: &ImplicitGeometry) -> Self::Result {
        println!("hello implicit_geometry",);
    }

    fn visit_thematic_surface(&mut self, v: &ThematicSurface) -> Self::Result {
        println!("hello thematic_surface {}", v.city_object.gml.id);
    }

    fn visit_space(&mut self, v: &Space) -> Self::Result {
        println!("hello space {}", v.city_object.gml.id);
    }

    fn visit_occupied_space(&mut self, v: &OccupiedSpace) -> Self::Result {
        println!("hello occupied_space {}", v.space.city_object.gml.id);
    }

    fn visit_city_model(&mut self, v: &CitygmlModel) -> Self::Result {
        println!("hello city_model");
    }

    fn visit_city_furniture(&mut self, v: &CityFurniture) -> Self::Result {
        println!(
            "hello city_furniture {}",
            v.occupied_space.space.city_object.gml.id
        );
    }

    fn visit_building(&mut self, v: &Building) -> Self::Result {
        println!("hello building {}", v.city_object.gml.id);
    }

    fn visit_roof_surface(&mut self, v: &RoofSurface) -> Self::Result {
        println!(
            "hello roof_surface {}",
            v.thematic_surface.city_object.gml.id
        );
    }

    fn visit_ground_surface(&mut self, v: &GroundSurface) -> Self::Result {
        println!(
            "hello ground_surface {}",
            v.thematic_surface.city_object.gml.id
        );
    }

    fn visit_wall_surface(&mut self, v: &WallSurface) -> Self::Result {
        println!(
            "hello wall_surface {}",
            v.thematic_surface.city_object.gml.id
        );
    }

    fn visit_window_surface(&mut self, v: &WindowSurface) -> Self::Result {
        println!(
            "hello window_surface {}",
            v.occupied_space.space.city_object.gml.id
        );
    }

    fn visit_door_surface(&mut self, v: &DoorSurface) -> Self::Result {
        println!(
            "hello door_surface {}",
            v.occupied_space.space.city_object.gml.id
        );
    }

    fn visit_solitary_vegetation_object(&mut self, v: &SolitaryVegetationObject) -> Self::Result {
        println!(
            "hello solitary_vegetation_object {}",
            v.occupied_space.space.city_object.gml.id
        );
    }

    fn visit_road(&mut self, v: &Road) -> Self::Result {
        println!("hello road {}", v.city_object.gml.id);
    }

    fn visit_section(&mut self, v: &Section) -> Self::Result {
        println!("hello section {}", v.city_object.gml.id);
    }

    fn visit_intersection(&mut self, v: &Intersection) -> Self::Result {
        println!("hello intersection {}", v.city_object.gml.id);
    }

    fn visit_traffic_space(&mut self, v: &TrafficSpace) -> Self::Result {
        println!("hello traffic_space {}", v.space.city_object.gml.id);
    }

    fn visit_auxiliary_traffic_space(&mut self, v: &AuxiliaryTrafficSpace) -> Self::Result {
        println!(
            "hello auxiliary_traffic_space {}",
            v.space.city_object.gml.id
        );
    }

    fn visit_traffic_area(&mut self, v: &TrafficArea) -> Self::Result {
        println!(
            "hello traffic_area {}",
            v.thematic_surface.city_object.gml.id
        );
    }

    fn visit_auxiliary_traffic_area(&mut self, v: &AuxiliaryTrafficArea) -> Self::Result {
        println!(
            "hello auxiliary_traffic_area {}",
            v.thematic_surface.city_object.gml.id
        );
    }
}

impl Visitable for DirectPosition {
    fn accept<V: Visitor>(&self, visitor: &mut V) {
        visitor.visit_direct_position(self);
    }
}

impl Visitable for LinearRing {
    fn accept<V: Visitor>(&self, visitor: &mut V) {
        visitor.visit_linear_ring(self);
        self.points().iter().for_each(|x| x.accept(visitor));
    }
}

impl Visitable for Polygon {
    fn accept<V: Visitor>(&self, visitor: &mut V) {
        visitor.visit_polygon(self);
        visitor.visit_linear_ring(&self.exterior);
        self.interior.iter().for_each(|x| x.accept(visitor));
    }
}

impl Visitable for MultiSurface {
    fn accept<V: Visitor>(&self, visitor: &mut V) {
        visitor.visit_multi_surface(self);
        self.surface_member().iter().for_each(|x| x.accept(visitor));
    }
}

impl Visitable for Solid {
    fn accept<V: Visitor>(&self, visitor: &mut V) {
        visitor.visit_solid(self);
        self.members().iter().for_each(|x| x.accept(visitor));
    }
}
