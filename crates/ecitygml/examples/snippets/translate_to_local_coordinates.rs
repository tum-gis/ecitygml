use ecitygml::io::{GmlReader, GmlWriter};
use egml::model::common::ApplyTransform;
use egml::model::feature::AsAbstractFeature;
use nalgebra::Vector3;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let args: Vec<String> = std::env::args().collect();
    let input_path = args.get(1).map_or("model.gml", String::as_str);
    let output_path = args.get(2).map_or("model_local.gml", String::as_str);

    // Parse the CityGML document, keeping the envelopes of the objects as
    // given in the file instead of recomputing them from their geometry
    let mut city_model = GmlReader::from_path(input_path)?
        .with_rebuild_object_bounds(false)
        .finish()?;

    // Move the center of the city model's envelope to the origin
    let center = city_model
        .bounded_by()
        .and_then(|shape| shape.envelope())
        .ok_or("the city model has no envelope")?
        .center();
    let offset = Vector3::new(-center.x(), -center.y(), -center.z());
    city_model.apply_translation(offset);

    // Write the translated city model as a CityGML document
    GmlWriter::from_path(output_path)?.finish(&city_model)?;

    println!(
        "Translated the city model by ({:.3}, {:.3}, {:.3}) \
         to local coordinates",
        offset.x, offset.y, offset.z
    );
    Ok(())
}
