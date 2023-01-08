use crate::{CityFurniture, TrafficArea, WallSurface};

use nalgebra::Point3;

#[derive(Debug, Clone, PartialEq, Default)]
pub struct CitygmlModel {
    city_furniture: Vec<CityFurniture>,
    traffic_area: Vec<TrafficArea>,
    wall_surface: Vec<WallSurface>,
}

impl CitygmlModel {
    pub fn new(
        city_furniture: Vec<CityFurniture>,
        traffic_area: Vec<TrafficArea>,
        wall_surface: Vec<WallSurface>,
    ) -> Self {
        Self {
            city_furniture,
            traffic_area,
            wall_surface,
        }
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

    pub fn push_wall_surface(&mut self, wall_surface: WallSurface) {
        self.wall_surface.push(wall_surface);
    }

    pub fn number_of_objects(&self) -> usize {
        self.city_furniture.len() + self.traffic_area.len() + self.wall_surface.len()
    }

    pub(crate) fn all_vertices(&self) -> Vec<&Point3<f64>> {
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
    }
}
