use std::path::Path;

use tracing::info;

pub fn run(file_path: impl AsRef<Path>) {
    let citygml_model = ecitygml::io::CitygmlReader::from_path(file_path)
        .unwrap()
        .finish()
        .unwrap();

    info!(
        "Number of city objects: {}\n",
        citygml_model.number_of_objects()
    );

    info!(
        "Total CityFurniture: {}",
        citygml_model.city_furniture().len()
    );
    info!(
        "\t- with lod1_solid: {}",
        citygml_model
            .city_furniture()
            .iter()
            .filter(|c| c.lod1_solid().is_some())
            .count()
    );
    info!(
        "\t- with lod2_solid: {}",
        citygml_model
            .city_furniture()
            .iter()
            .filter(|c| c.lod2_solid().is_some())
            .count()
    );
    info!(
        "\t- with lod2_multi_surface: {}",
        citygml_model
            .city_furniture()
            .iter()
            .filter(|c| c.lod2_multi_surface().is_some())
            .count()
    );
    info!(
        "\t- with reference_point: {}",
        citygml_model
            .city_furniture()
            .iter()
            .filter(|c| c.reference_point().is_some())
            .count()
    );

    info!("Total TrafficArea: {}", citygml_model.traffic_area().len());
    info!(
        "\t- with lod2_multi_surface: {}",
        citygml_model
            .traffic_area()
            .iter()
            .filter(|c| c.lod2_multi_surface().is_some())
            .count()
    );

    info!(
        "Total SolitaryVegetationObject: {}",
        citygml_model.solitary_vegetation_object().len()
    );
    info!(
        "\t- with lod1_solid: {}",
        citygml_model
            .solitary_vegetation_object()
            .iter()
            .filter(|c| c.lod1_solid().is_some())
            .count()
    );

    info!("Total WallSurface: {}", citygml_model.wall_surface().len());
    info!(
        "\t- with lod2_multi_surface: {}",
        citygml_model
            .wall_surface()
            .iter()
            .filter(|c| c.lod2_multi_surface().is_some())
            .count()
    );
    info!(
        "\t- with lod3_multi_surface: {}",
        citygml_model
            .wall_surface()
            .iter()
            .filter(|c| c.lod3_multi_surface().is_some())
            .count()
    );

    info!("Offset city model");
    let offset = nalgebra::Vector3::new(-678071.2478652871, -5403609.8367785765, -415.28);
    let transformed_citygml_model =
        ecitygml::transform::offset::offset_citygml_model(citygml_model, &offset).unwrap();
    info!(
        "Number of city objects: {}",
        transformed_citygml_model.number_of_objects()
    );
}
