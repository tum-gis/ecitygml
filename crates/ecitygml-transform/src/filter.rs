use crate::error::Error;
use ecitygml_core::{
    CityFurniture, CitygmlModel, SolitaryVegetationObject, TrafficArea, WallSurface,
};
use egml::geometry::Envelope;

pub fn filter_by_bounding_box(
    mut city_model: CitygmlModel,
    filter_envelope: &Envelope,
) -> Result<CitygmlModel, Error> {
    // x.lod2_solid()
    let filtered_city_furniture: Vec<CityFurniture> = city_model
        .city_furniture()
        .clone()
        .into_iter()
        .filter(|f| {
            f.lod1_solid().as_ref().map_or(false, |g| {
                filter_envelope.contains_envelope_partially(&g.get_envelope().unwrap())
            }) || f.lod2_solid().as_ref().map_or(false, |g| {
                filter_envelope.contains_envelope_partially(&g.get_envelope().unwrap())
            }) || f.lod2_multi_surface().as_ref().map_or(false, |g| {
                filter_envelope.contains_envelope_partially(&g.get_envelope().unwrap())
            }) || f
                .reference_point()
                .as_ref()
                .map_or(false, |g| filter_envelope.contains(g))
        })
        .collect();
    city_model.set_city_furniture(filtered_city_furniture);

    let filtered_traffic_area: Vec<TrafficArea> = city_model
        .traffic_area()
        .clone()
        .into_iter()
        .filter(|f| {
            f.lod2_multi_surface().as_ref().map_or(false, |g| {
                filter_envelope.contains_envelope_partially(&g.get_envelope().unwrap())
            })
        })
        .collect();
    city_model.set_traffic_area(filtered_traffic_area);

    let filtered_solitary_vegetation_object: Vec<SolitaryVegetationObject> = city_model
        .solitary_vegetation_object()
        .clone()
        .into_iter()
        .filter(|f| {
            f.lod1_solid().as_ref().map_or(false, |g| {
                filter_envelope.contains_envelope_partially(&g.get_envelope().unwrap())
            })
        })
        .collect();
    city_model.set_solitary_vegetation_object(filtered_solitary_vegetation_object);

    let filtered_wall_surface: Vec<WallSurface> = city_model
        .wall_surface()
        .clone()
        .into_iter()
        .filter(|f| {
            f.lod2_multi_surface().as_ref().map_or(false, |g| {
                filter_envelope.contains_envelope_partially(&g.get_envelope().unwrap())
            }) || f.lod3_multi_surface().as_ref().map_or(false, |g| {
                filter_envelope.contains_envelope_partially(&g.get_envelope().unwrap())
            })
        })
        .collect();
    city_model.set_wall_surface(filtered_wall_surface);

    Ok(city_model)
}
