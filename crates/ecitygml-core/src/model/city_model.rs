use crate::model::building::Building;
use crate::model::city_furniture::CityFurniture;
use crate::model::solitary_vegetation_object::SolitaryVegetationObject;
use crate::model::transportation::Road;
use crate::operations::{CityObjectVisitor, FeatureWithGeometry, Visitable};
use egml::model::geometry::Envelope;
use nalgebra::Isometry3;
use rayon::prelude::*;

#[derive(Debug, Clone, PartialEq, Default)]
pub struct CitygmlModel {
    pub building: Vec<Building>,
    pub city_furniture: Vec<CityFurniture>,
    pub road: Vec<Road>,
    pub solitary_vegetation_object: Vec<SolitaryVegetationObject>,
}

impl CitygmlModel {
    pub fn new(
        building: Vec<Building>,
        city_furniture: Vec<CityFurniture>,
        road: Vec<Road>,
        solitary_vegetation_object: Vec<SolitaryVegetationObject>,
    ) -> Self {
        Self {
            building,
            city_furniture,
            road,
            solitary_vegetation_object,
        }
    }

    pub fn from_citygml_models(citygml_models: &Vec<Self>) -> Self {
        let building: Vec<Building> = citygml_models
            .iter()
            .flat_map(|x| x.building.iter().cloned())
            .collect();
        let city_furniture: Vec<CityFurniture> = citygml_models
            .iter()
            .flat_map(|x| x.city_furniture.iter().cloned())
            .collect();
        let road: Vec<Road> = citygml_models
            .iter()
            .flat_map(|x| x.road.iter().cloned())
            .collect();
        let solitary_vegetation_object: Vec<SolitaryVegetationObject> = citygml_models
            .iter()
            .flat_map(|x| x.solitary_vegetation_object.iter().cloned())
            .collect();

        CitygmlModel::new(building, city_furniture, road, solitary_vegetation_object)
    }

    pub fn is_empty(&self) -> bool {
        self.building.is_empty()
            && self.city_furniture.is_empty()
            && self.road.is_empty()
            && self.solitary_vegetation_object.is_empty()
    }

    pub fn number_of_objects(&self) -> usize {
        self.building.len()
            + self.city_furniture.len()
            + self.road.len()
            + self.solitary_vegetation_object.len()
    }
}

impl Visitable for CitygmlModel {
    fn accept<V: CityObjectVisitor>(&self, visitor: &mut V) {
        visitor.visit_city_model(self);
        self.building.iter().for_each(|x| x.accept(visitor));
        self.city_furniture.iter().for_each(|x| x.accept(visitor));
        self.road.iter().for_each(|x| x.accept(visitor));
        self.solitary_vegetation_object
            .iter()
            .for_each(|x| x.accept(visitor));
    }
}

impl FeatureWithGeometry for CitygmlModel {
    fn envelope(&self) -> Option<Envelope> {
        let mut envelopes: Vec<Option<Envelope>> = vec![];
        envelopes.extend(self.building.iter().map(|x| x.envelope()));
        envelopes.extend(self.city_furniture.iter().map(|x| x.envelope()));
        envelopes.extend(self.road.iter().map(|x| x.envelope()));
        envelopes.extend(self.solitary_vegetation_object.iter().map(|x| x.envelope()));

        Envelope::from_optional_envelopes(&envelopes).expect("should work")
    }

    fn apply_transform(&mut self, m: &Isometry3<f64>) {
        self.building.iter_mut().for_each(|x| x.apply_transform(m));
        self.city_furniture
            .iter_mut()
            .for_each(|x| x.apply_transform(m));
        self.road.iter_mut().for_each(|x| x.apply_transform(m));
        self.solitary_vegetation_object
            .iter_mut()
            .for_each(|x| x.apply_transform(m));
    }
}
