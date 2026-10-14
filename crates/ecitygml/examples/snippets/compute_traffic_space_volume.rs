use ecitygml::io::GmlReader;
use ecitygml::model::common::IterFeatures;
use ecitygml::model::core::AsAbstractSpace;
use ecitygml::model::transportation::TrafficSpace;
use rayon::prelude::*;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let path = std::env::args()
        .nth(1)
        .unwrap_or_else(|| "model.gml".to_string());

    // Parse the CityGML document into the in-memory city model
    let city_model = GmlReader::from_path(path)?.finish()?;

    // Traverse all features and keep only those that are traffic
    // spaces, using a type-safe conversion that skips all other
    // feature types
    let traffic_spaces: Vec<&TrafficSpace> = city_model
        .iter_features()
        .filter_map(|feature| feature.try_into().ok())
        .collect();

    // Compute the volumes of the LOD2 solids in parallel across all CPU
    // cores and sum them up; spaces without an LOD2 solid, or whose
    // volume cannot be computed, are skipped
    let total: f64 = traffic_spaces
        .par_iter()
        .filter_map(|space| space.lod2_solid()?.object()?.volume_3d().ok())
        .sum();
    println!("Total volume of traffic spaces (LoD2): {total:.3} m^3");

    Ok(())
}
