use crate::{CityFurniture, TrafficArea, WallSurface};

use crate::model::solitary_vegetation_object::SolitaryVegetationObject;
use egml::geometry::{enlarge_envelopes, Envelope};

#[derive(Debug, Clone, PartialEq, Default)]
pub struct CitygmlModel {
    city_furniture: Vec<CityFurniture>,
    traffic_area: Vec<TrafficArea>,
    solitary_vegetation_object: Vec<SolitaryVegetationObject>,
    wall_surface: Vec<WallSurface>,
}

impl CitygmlModel {
    pub fn new(
        city_furniture: Vec<CityFurniture>,
        traffic_area: Vec<TrafficArea>,
        solitary_vegetation_object: Vec<SolitaryVegetationObject>,
        wall_surface: Vec<WallSurface>,
    ) -> Self {
        Self {
            city_furniture,
            traffic_area,
            solitary_vegetation_object,
            wall_surface,
        }
    }

    pub fn from_citygml_models(citygml_models: &Vec<Self>) -> Self {
        let city_furniture: Vec<CityFurniture> = citygml_models
            .iter()
            .flat_map(|x| x.city_furniture.iter().cloned())
            .collect();
        let traffic_area: Vec<TrafficArea> = citygml_models
            .iter()
            .flat_map(|x| x.traffic_area.iter().cloned())
            .collect();
        let solitary_vegetation_object: Vec<SolitaryVegetationObject> = citygml_models
            .iter()
            .flat_map(|x| x.solitary_vegetation_object.iter().cloned())
            .collect();
        let wall_surface: Vec<WallSurface> = citygml_models
            .iter()
            .flat_map(|x| x.wall_surface.iter().cloned())
            .collect();

        CitygmlModel::new(
            city_furniture,
            traffic_area,
            solitary_vegetation_object,
            wall_surface,
        )
    }

    pub fn city_furniture(&self) -> &Vec<CityFurniture> {
        &self.city_furniture
    }
    pub fn set_city_furniture(&mut self, val: Vec<CityFurniture>) {
        self.city_furniture = val;
    }

    pub fn traffic_area(&self) -> &Vec<TrafficArea> {
        &self.traffic_area
    }
    pub fn set_traffic_area(&mut self, val: Vec<TrafficArea>) {
        self.traffic_area = val;
    }

    pub fn solitary_vegetation_object(&self) -> &Vec<SolitaryVegetationObject> {
        &self.solitary_vegetation_object
    }
    pub fn set_solitary_vegetation_object(&mut self, val: Vec<SolitaryVegetationObject>) {
        self.solitary_vegetation_object = val;
    }

    pub fn wall_surface(&self) -> &Vec<WallSurface> {
        &self.wall_surface
    }
    pub fn set_wall_surface(&mut self, val: Vec<WallSurface>) {
        self.wall_surface = val;
    }

    pub fn is_empty(&self) -> bool {
        self.city_furniture.is_empty()
            && self.traffic_area.is_empty()
            && self.wall_surface.is_empty()
    }

    pub fn push_city_furniture(&mut self, city_furniture: CityFurniture) {
        self.city_furniture.push(city_furniture);
    }

    pub fn push_traffic_area(&mut self, traffic_area: TrafficArea) {
        self.traffic_area.push(traffic_area);
    }

    pub fn push_solitary_vegetation_object(
        &mut self,
        solitary_vegetation_object: SolitaryVegetationObject,
    ) {
        self.solitary_vegetation_object
            .push(solitary_vegetation_object);
    }

    pub fn push_wall_surface(&mut self, wall_surface: WallSurface) {
        self.wall_surface.push(wall_surface);
    }

    pub fn number_of_objects(&self) -> usize {
        self.city_furniture.len() + self.traffic_area.len() + self.wall_surface.len()
    }

    pub fn get_envelope(&self) -> Option<Envelope> {
        let mut envelopes: Vec<Envelope> = Vec::new();
        let mut feature_envelopes: Vec<Envelope> = self
            .city_furniture
            .iter()
            .flat_map(|f| f.lod2_multi_surface())
            .map(|f| f.get_envelope().unwrap())
            .collect();
        envelopes.append(&mut feature_envelopes);

        let mut feature_envelopes: Vec<Envelope> = self
            .city_furniture
            .iter()
            .flat_map(|f| f.lod2_solid())
            .map(|f| f.get_envelope().unwrap())
            .collect();
        envelopes.append(&mut feature_envelopes);

        let mut feature_envelopes: Vec<Envelope> = self
            .wall_surface
            .iter()
            .flat_map(|f| f.lod2_multi_surface())
            .map(|f| f.get_envelope().unwrap())
            .collect();
        envelopes.append(&mut feature_envelopes);

        let mut feature_envelopes: Vec<Envelope> = self
            .traffic_area
            .iter()
            .flat_map(|f| f.lod2_multi_surface())
            .map(|f| f.get_envelope().unwrap())
            .collect();
        envelopes.append(&mut feature_envelopes);

        if envelopes.is_empty() {
            return None;
        }
        let city_model_envelopes = enlarge_envelopes(&envelopes).unwrap();
        Some(city_model_envelopes)
    }

    /*pub(crate) fn all_vertices(&self) -> Vec<&Point3<f64>> {
        /*let all_vertices: Vec<&Point3<f64>> = self
        .city_objects
        .iter()
        .flat_map(|m| &m.geometries)
        .flat_map(|p| p.points())
        .collect();*/

        let all_vertices: Vec<&Point3<f64>> = Vec::new();
        all_vertices
    }

    pub fn get_min(&self) -> Point3<f64> {
        let vertices: Vec<&Point3<f64>> = self.all_vertices();

        let min_x = vertices
            .iter()
            .map(|p| p.x)
            .collect::<Vec<f64>>()
            .iter()
            .fold(f64::INFINITY, |a, &b| a.min(b));
        let min_y = vertices
            .iter()
            .map(|p| p.y)
            .collect::<Vec<f64>>()
            .iter()
            .fold(f64::INFINITY, |a, &b| a.min(b));
        let min_z = vertices
            .iter()
            .map(|p| p.z)
            .collect::<Vec<f64>>()
            .iter()
            .fold(f64::INFINITY, |a, &b| a.min(b));

        Point3::new(min_x, min_y, min_z)
    }*/
}
