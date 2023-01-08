use ecitygml::{CityFurniture, TrafficArea, WallSurface};
use std::path::Path;
use tracing::info;

fn main() {
    tracing_subscriber::fmt::init();
    info!("Start ecitygml-cli");

    let input_file_path = Path::new("~/citygml_model.gml").canonicalize().unwrap();

    let citygml_model = ecitygml::io::CitygmlReader::new(input_file_path)
        .finish()
        .unwrap();

    info!(
        "Number of city objects: {}",
        citygml_model.number_of_objects()
    );

    let city_furniture_total_count: usize = citygml_model.city_furniture().len();
    let filtered_city_furniture: Vec<&CityFurniture> = citygml_model
        .city_furniture()
        .iter()
        .filter(|c| c.reference_point().is_some())
        .collect();
    let city_furniture_with_geometry_count = filtered_city_furniture.len();
    info!("number of city furniture with geometry {city_furniture_with_geometry_count} out of {city_furniture_total_count}");

    let traffic_areas_total_count: usize = citygml_model.traffic_area().len();
    let filtered_traffic_areas: Vec<&TrafficArea> = citygml_model
        .traffic_area()
        .iter()
        .filter(|c| c.lod2_multi_surface().is_some())
        .collect();
    let traffic_areas_with_geometry_count = filtered_traffic_areas.len();
    info!("number of traffic areas with geometry {traffic_areas_with_geometry_count} out of {traffic_areas_total_count}");

    let wall_surfaces_total_count: usize = citygml_model.wall_surface().len();
    let filtered_wall_surface: Vec<&WallSurface> = citygml_model
        .wall_surface()
        .iter()
        .filter(|c| c.lod2_multi_surface().is_some())
        .collect();
    let wall_surfaces_with_geometry_count = filtered_wall_surface.len();
    info!("number of wall surfaces with geometry {wall_surfaces_with_geometry_count} out of {wall_surfaces_total_count}");

    info!("Offset city model");
    let offset = nalgebra::Vector3::new(-678071.2478652871, -5403609.8367785765, -415.28);
    let transformed_citygml_model =
        ecitygml::transform::offset::offset_citygml_model(citygml_model, &offset).unwrap();
    info!(
        "Number of city objects: {}",
        transformed_citygml_model.number_of_objects()
    );
}
