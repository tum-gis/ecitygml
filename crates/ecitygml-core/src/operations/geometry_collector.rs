use crate::model::building::{Building, BuildingConstructiveElement};
use crate::model::city_furniture::CityFurniture;
use crate::model::city_model::CitygmlModel;
use crate::model::common::{CityObjectClass, LevelOfDetail};
use crate::model::construction::{
    DoorSurface, GroundSurface, RoofSurface, WallSurface, WindowSurface,
};
use crate::model::core::{ImplicitGeometry, OccupiedSpace, Space, ThematicSurface};
use crate::model::solitary_vegetation_object::SolitaryVegetationObject;
use crate::model::transportation::{
    AuxiliaryTrafficArea, AuxiliaryTrafficSpace, Intersection, Road, Section, TrafficArea,
    TrafficSpace,
};
use crate::operations::CityObjectVisitor;
use egml::model::base::{Gml, Id};
use egml::model::geometry::{MultiSurface, Solid};
use std::collections::HashMap;

#[derive(Debug, Clone, PartialEq)]
pub struct CityObjectGeometryCollection {
    pub gml: Gml,
    pub class: CityObjectClass,
    pub implicit_geometries: HashMap<LevelOfDetail, ImplicitGeometry>,
    pub multi_surfaces: HashMap<LevelOfDetail, MultiSurface>,
    pub solids: HashMap<LevelOfDetail, Solid>,
}

impl CityObjectGeometryCollection {
    pub fn from_space(class: CityObjectClass, space: &Space) -> Self {
        let mut solids: HashMap<LevelOfDetail, Solid> = HashMap::new();
        if let Some(g) = &space.lod1_solid {
            solids.insert(LevelOfDetail::One, g.clone());
        }
        if let Some(g) = &space.lod2_solid {
            solids.insert(LevelOfDetail::Two, g.clone());
        }
        if let Some(g) = &space.lod3_solid {
            solids.insert(LevelOfDetail::Three, g.clone());
        }

        let mut multi_surfaces: HashMap<LevelOfDetail, MultiSurface> = HashMap::new();
        if let Some(g) = &space.lod0_multi_surface {
            multi_surfaces.insert(LevelOfDetail::Zero, g.clone());
        }
        if let Some(g) = &space.lod2_multi_surface {
            multi_surfaces.insert(LevelOfDetail::Two, g.clone());
        }
        if let Some(g) = &space.lod3_multi_surface {
            multi_surfaces.insert(LevelOfDetail::Three, g.clone());
        }

        Self {
            gml: space.city_object.gml.clone(),
            class,
            implicit_geometries: HashMap::new(),
            multi_surfaces,
            solids,
        }
    }
    pub fn from_occupied_space(class: CityObjectClass, occupied_space: &OccupiedSpace) -> Self {
        let mut city_object_geometry_collection =
            CityObjectGeometryCollection::from_space(class, &occupied_space.space);

        if let Some(g) = &occupied_space.lod1_implicit_representation {
            city_object_geometry_collection
                .implicit_geometries
                .insert(LevelOfDetail::One, g.clone());
        }
        if let Some(g) = &occupied_space.lod2_implicit_representation {
            city_object_geometry_collection
                .implicit_geometries
                .insert(LevelOfDetail::Two, g.clone());
        }
        if let Some(g) = &occupied_space.lod3_implicit_representation {
            city_object_geometry_collection
                .implicit_geometries
                .insert(LevelOfDetail::Three, g.clone());
        }

        city_object_geometry_collection
    }

    pub fn from_thematic_surface(
        class: CityObjectClass,
        thematic_surface: &ThematicSurface,
    ) -> Self {
        let mut multi_surfaces: HashMap<LevelOfDetail, MultiSurface> = HashMap::new();

        if let Some(g) = &thematic_surface.lod0_multi_surface {
            multi_surfaces.insert(LevelOfDetail::Zero, g.clone());
        }
        if let Some(g) = &thematic_surface.lod1_multi_surface {
            multi_surfaces.insert(LevelOfDetail::One, g.clone());
        }
        if let Some(g) = &thematic_surface.lod2_multi_surface {
            multi_surfaces.insert(LevelOfDetail::Two, g.clone());
        }
        if let Some(g) = &thematic_surface.lod3_multi_surface {
            multi_surfaces.insert(LevelOfDetail::Three, g.clone());
        }

        Self {
            gml: thematic_surface.city_object.gml.clone(),
            class,
            implicit_geometries: HashMap::new(),
            multi_surfaces,
            solids: HashMap::new(),
        }
    }
}

#[derive(Debug, Clone, PartialEq, Default)]
pub struct GeometryCollector {
    pub city_objects: HashMap<Id, CityObjectGeometryCollection>,
}

impl GeometryCollector {
    pub fn new() -> Self {
        Self {
            city_objects: HashMap::new(),
        }
    }
}

impl CityObjectVisitor for GeometryCollector {
    type Result = ();

    fn visit_city_model(&mut self, v: &CitygmlModel) -> Self::Result {}

    fn visit_city_furniture(&mut self, v: &CityFurniture) -> Self::Result {
        let city_object_geometry_collection = CityObjectGeometryCollection::from_occupied_space(
            CityObjectClass::CityFurniture,
            &v.occupied_space,
        );
        self.city_objects.insert(
            city_object_geometry_collection.gml.id.clone(),
            city_object_geometry_collection,
        );
    }

    fn visit_building(&mut self, v: &Building) -> Self::Result {}

    fn visit_building_constructive_element(
        &mut self,
        v: &BuildingConstructiveElement,
    ) -> Self::Result {
        let city_object_geometry_collection = CityObjectGeometryCollection::from_occupied_space(
            CityObjectClass::BuildingConstructiveElement,
            &v.occupied_space,
        );
        self.city_objects.insert(
            city_object_geometry_collection.gml.id.clone(),
            city_object_geometry_collection,
        );
    }

    fn visit_roof_surface(&mut self, v: &RoofSurface) -> Self::Result {
        let city_object_geometry_collection = CityObjectGeometryCollection::from_thematic_surface(
            CityObjectClass::RoofSurface,
            &v.thematic_surface,
        );
        self.city_objects.insert(
            city_object_geometry_collection.gml.id.clone(),
            city_object_geometry_collection,
        );
    }

    fn visit_ground_surface(&mut self, v: &GroundSurface) -> Self::Result {
        let city_object_geometry_collection = CityObjectGeometryCollection::from_thematic_surface(
            CityObjectClass::GroundSurface,
            &v.thematic_surface,
        );
        self.city_objects.insert(
            city_object_geometry_collection.gml.id.clone(),
            city_object_geometry_collection,
        );
    }

    fn visit_wall_surface(&mut self, v: &WallSurface) -> Self::Result {
        let city_object_geometry_collection = CityObjectGeometryCollection::from_thematic_surface(
            CityObjectClass::WallSurface,
            &v.thematic_surface,
        );
        self.city_objects.insert(
            city_object_geometry_collection.gml.id.clone(),
            city_object_geometry_collection,
        );
    }

    fn visit_window_surface(&mut self, v: &WindowSurface) -> Self::Result {
        let city_object_geometry_collection = CityObjectGeometryCollection::from_occupied_space(
            CityObjectClass::WindowSurface,
            &v.occupied_space,
        );
        self.city_objects.insert(
            city_object_geometry_collection.gml.id.clone(),
            city_object_geometry_collection,
        );
    }

    fn visit_door_surface(&mut self, v: &DoorSurface) -> Self::Result {
        let city_object_geometry_collection = CityObjectGeometryCollection::from_occupied_space(
            CityObjectClass::DoorSurface,
            &v.occupied_space,
        );
        self.city_objects.insert(
            city_object_geometry_collection.gml.id.clone(),
            city_object_geometry_collection,
        );
    }

    fn visit_solitary_vegetation_object(&mut self, v: &SolitaryVegetationObject) -> Self::Result {
        let city_object_geometry_collection = CityObjectGeometryCollection::from_occupied_space(
            CityObjectClass::SolitaryVegetationObject,
            &v.occupied_space,
        );
        self.city_objects.insert(
            city_object_geometry_collection.gml.id.clone(),
            city_object_geometry_collection,
        );
    }

    fn visit_road(&mut self, v: &Road) -> Self::Result {}

    fn visit_section(&mut self, v: &Section) -> Self::Result {}

    fn visit_intersection(&mut self, v: &Intersection) -> Self::Result {}

    fn visit_traffic_space(&mut self, v: &TrafficSpace) -> Self::Result {
        let city_object_geometry_collection =
            CityObjectGeometryCollection::from_space(CityObjectClass::TrafficSpace, &v.space);
        self.city_objects.insert(
            city_object_geometry_collection.gml.id.clone(),
            city_object_geometry_collection,
        );
    }

    fn visit_auxiliary_traffic_space(&mut self, v: &AuxiliaryTrafficSpace) -> Self::Result {
        let city_object_geometry_collection = CityObjectGeometryCollection::from_space(
            CityObjectClass::AuxiliaryTrafficSpace,
            &v.space,
        );
        self.city_objects.insert(
            city_object_geometry_collection.gml.id.clone(),
            city_object_geometry_collection,
        );
    }

    fn visit_traffic_area(&mut self, v: &TrafficArea) -> Self::Result {
        let city_object_geometry_collection = CityObjectGeometryCollection::from_thematic_surface(
            CityObjectClass::TrafficArea,
            &v.thematic_surface,
        );
        self.city_objects.insert(
            city_object_geometry_collection.gml.id.clone(),
            city_object_geometry_collection,
        );
    }

    fn visit_auxiliary_traffic_area(&mut self, v: &AuxiliaryTrafficArea) -> Self::Result {
        let city_object_geometry_collection = CityObjectGeometryCollection::from_thematic_surface(
            CityObjectClass::AuxiliaryTrafficArea,
            &v.thematic_surface,
        );
        self.city_objects.insert(
            city_object_geometry_collection.gml.id.clone(),
            city_object_geometry_collection,
        );
    }
}
