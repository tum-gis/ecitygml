use ecitygml::io::GmlReader;
use ecitygml::model::common::IterFeatures;
use ecitygml::model::construction::WallSurface;
use ecitygml::model::core::AsAbstractThematicSurface;
use rayon::iter::IntoParallelRefIterator;
use rayon::iter::ParallelIterator;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let path = std::env::args()
        .nth(1)
        .unwrap_or_else(|| "model.gml".to_string());

    // Parse the CityGML document into the in-memory city model
    let city_model = GmlReader::from_path(path)?.finish()?;

    // Traverse all features and keep only those that are wall surfaces,
    // using a type-safe conversion that skips all other feature types
    let wall_surfaces: Vec<&WallSurface> = city_model
        .iter_features()
        .filter_map(|feature| <&WallSurface>::try_from(feature).ok())
        .collect();

    // Compute the areas of the LOD2 multi-surfaces in parallel across all
    // CPU cores and sum them up; walls without an LOD2 multi-surface, or
    // whose area cannot be computed, are skipped
    let total_area: f64 = wall_surfaces
        .par_iter()
        .filter_map(|wall| wall.lod2_multi_surface()?.object()?.area_3d().ok())
        .sum();
    println!("Total area of wall surfaces (LoD2): {total_area:.3} m^2");

    Ok(())
}
