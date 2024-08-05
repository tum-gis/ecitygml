use ecitygml::io::{FILE_EXTENSION_CITYGML_GML_FORMAT, FILE_EXTENSION_CITYGML_XML_FORMAT};
use ecitygml::model::construction::{GroundSurface, RoofSurface, WallSurface};
use ecitygml::model::core::{OccupiedSpace, Space, ThematicSurface};
use ecitygml::operations::FeatureWithGeometry;
use std::path::Path;
use std::time::Instant;
use tracing::info;
use walkdir::WalkDir;

pub fn run(path: impl AsRef<Path>) {
    info!("Creating statistics for: {}", path.as_ref().display());

    if path.as_ref().is_file() {
        print_citygml_model_statistics(path);
    } else if path.as_ref().is_dir() {
        for entry in WalkDir::new(path)
            .sort_by(|a, b| a.file_name().cmp(b.file_name()))
            .into_iter()
            .filter_map(Result::ok)
            .filter(|e| e.file_type().is_file() && e.path().extension().is_some())
            .filter(|e| {
                e.path().extension().expect("must have an extension")
                    == FILE_EXTENSION_CITYGML_GML_FORMAT
                    || e.path().extension().expect("must have an extension")
                        == FILE_EXTENSION_CITYGML_XML_FORMAT
            })
        {
            info!("Start reading: {:?}", entry);
            let now = Instant::now();
            let citygml_model = ecitygml::io::CitygmlReader::from_path(entry.into_path())
                .unwrap()
                .finish()
                .unwrap();
            info!("Read model in {:.3?}", now.elapsed());
        }
    }
}

fn print_citygml_model_statistics(file_path: impl AsRef<Path>) {
    let now = Instant::now();
    let citygml_model = ecitygml::io::CitygmlReader::from_path(file_path)
        .unwrap()
        .finish()
        .unwrap();
    info!("Read model in {:.3?}", now.elapsed());

    info!(
        "Number of city objects: {}\n",
        citygml_model.number_of_objects()
    );

    let envelope = citygml_model.envelope().unwrap();
    info!(
        "Envelope: lower corner{}, upper corner {}\n",
        envelope.lower_corner(),
        envelope.upper_corner()
    );

    info!("Total Building: {}", citygml_model.building.len());
    let wall_surfaces: Vec<&WallSurface> = citygml_model
        .building
        .iter()
        .flat_map(|x| &x.wall_surface)
        .collect();
    info!("Total WallSurface: {}", wall_surfaces.len());
    if !wall_surfaces.is_empty() {
        print_statistics_thematic_surface(
            wall_surfaces.iter().map(|x| &x.thematic_surface).collect(),
        );
    }

    let roof_surfaces: Vec<&RoofSurface> = citygml_model
        .building
        .iter()
        .flat_map(|x| &x.roof_surface)
        .collect();
    info!("Total RoofSurface: {}", roof_surfaces.len());
    if !roof_surfaces.is_empty() {
        print_statistics_thematic_surface(
            roof_surfaces.iter().map(|x| &x.thematic_surface).collect(),
        );
    }

    let ground_surfaces: Vec<&GroundSurface> = citygml_model
        .building
        .iter()
        .flat_map(|x| &x.ground_surface)
        .collect();
    info!("Total GroundSurface: {}", ground_surfaces.len());
    if !ground_surfaces.is_empty() {
        print_statistics_thematic_surface(
            ground_surfaces
                .iter()
                .map(|x| &x.thematic_surface)
                .collect(),
        );
    }

    info!(
        "Total CityFurniture: {}",
        citygml_model.city_furniture.len()
    );
    if !citygml_model.city_furniture.is_empty() {
        print_statistics_occupied_space(
            citygml_model
                .city_furniture
                .iter()
                .map(|x| &x.occupied_space)
                .collect(),
        );
    }

    info!("Total Road: {}", citygml_model.road.len());

    info!(
        "Total SolitaryVegetationObject: {}",
        citygml_model.solitary_vegetation_object.len()
    );
    if !citygml_model.solitary_vegetation_object.is_empty() {
        print_statistics_occupied_space(
            citygml_model
                .solitary_vegetation_object
                .iter()
                .map(|x| &x.occupied_space)
                .collect(),
        );
    }

    /*info!("Offset city model");
    let translation = nalgebra::Vector3::new(-678071.2478652871, -5403609.8367785765, -415.28);
    let isometry = Isometry3::new(translation, Default::default());
    citygml_model.apply_transform(&isometry);
    info!(
        "Number of city objects: {}",
        citygml_model.number_of_objects()
    );*/
}

fn print_statistics_occupied_space(occupied_space: Vec<&OccupiedSpace>) {
    info!(
        "\t- with lod1_implicit_representation: {}",
        occupied_space
            .iter()
            .filter(|x| x.lod1_implicit_representation.is_some())
            .count()
    );
    info!(
        "\t- with lod2_implicit_representation: {}",
        occupied_space
            .iter()
            .filter(|x| x.lod2_implicit_representation.is_some())
            .count()
    );
    info!(
        "\t- with lod3_implicit_representation: {}",
        occupied_space
            .iter()
            .filter(|x| x.lod3_implicit_representation.is_some())
            .count()
    );

    print_statistics_space(occupied_space.iter().map(|x| &x.space).collect());
}

fn print_statistics_space(space: Vec<&Space>) {
    info!(
        "\t- with lod1_solid: {}",
        space.iter().filter(|x| x.lod1_solid.is_some()).count()
    );
    info!(
        "\t- with lod2_solid: {}",
        space.iter().filter(|x| x.lod2_solid.is_some()).count()
    );
    info!(
        "\t- with lod3_solid: {}",
        space.iter().filter(|x| x.lod3_solid.is_some()).count()
    );

    info!(
        "\t- with lod0_multi_surface: {}",
        space
            .iter()
            .filter(|x| x.lod0_multi_surface.is_some())
            .count()
    );
    info!(
        "\t- with lod2_multi_surface: {}",
        space
            .iter()
            .filter(|x| x.lod2_multi_surface.is_some())
            .count()
    );
    info!(
        "\t- with lod3_multi_surface: {}",
        space
            .iter()
            .filter(|x| x.lod3_multi_surface.is_some())
            .count()
    );
}

fn print_statistics_thematic_surface(thematic_surface: Vec<&ThematicSurface>) {
    info!(
        "\t- with lod0_multi_surface: {}",
        thematic_surface
            .iter()
            .filter(|x| x.lod0_multi_surface.is_some())
            .count()
    );
    info!(
        "\t- with lod1_multi_surface: {}",
        thematic_surface
            .iter()
            .filter(|x| x.lod1_multi_surface.is_some())
            .count()
    );
    info!(
        "\t- with lod2_multi_surface: {}",
        thematic_surface
            .iter()
            .filter(|x| x.lod2_multi_surface.is_some())
            .count()
    );
    info!(
        "\t- with lod3_multi_surface: {}",
        thematic_surface
            .iter()
            .filter(|x| x.lod3_multi_surface.is_some())
            .count()
    );
}
