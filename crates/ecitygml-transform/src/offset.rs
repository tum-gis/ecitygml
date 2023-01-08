use crate::error::EcitygmlIoError;
use ecitygml_core::{CityFurniture, CitygmlModel, TrafficArea, WallSurface};
use egml::transform::offset::{offset_multi_surface, offset_position};
use nalgebra::Vector3;

pub fn offset_citygml_model(
    mut city_model: CitygmlModel,
    offset: &Vector3<f64>,
) -> Result<CitygmlModel, EcitygmlIoError> {
    // TODO improve in-situ transformation without cloning

    let mut transformed_city_furniture: Vec<CityFurniture> = city_model.city_furniture().clone();
    transformed_city_furniture
        .iter_mut()
        .filter(|x| x.reference_point().is_some())
        .for_each(|x| {
            let reference_point = x.reference_point().unwrap();
            let offset_reference_point = offset_position(reference_point, offset).unwrap();
            x.set_reference_point(Some(offset_reference_point));
        });
    city_model.set_city_furniture(transformed_city_furniture);

    let mut transformed_traffic_area: Vec<TrafficArea> = city_model.traffic_area().clone();
    transformed_traffic_area
        .iter_mut()
        .filter(|x| x.lod2_multi_surface().is_some())
        .for_each(|x| {
            let geom = x.lod2_multi_surface().to_owned().unwrap();
            let offset_geom = offset_multi_surface(geom, offset).unwrap();
            x.set_lod2_multi_surface(Some(offset_geom));
        });
    city_model.set_traffic_area(transformed_traffic_area);

    let mut transformed_wall_surface: Vec<WallSurface> = city_model.wall_surface().clone();
    transformed_wall_surface
        .iter_mut()
        .filter(|x| x.lod2_multi_surface().is_some())
        .for_each(|x| {
            let geom = x.lod2_multi_surface().to_owned().unwrap();
            let offset_geom = offset_multi_surface(geom, offset).unwrap();
            x.set_lod2_multi_surface(Some(offset_geom));
        });
    city_model.set_wall_surface(transformed_wall_surface);

    Ok(city_model)
}
