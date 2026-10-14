use ecitygml::io::GmlReader;
use ecitygml::model::building::Building;
use ecitygml::model::construction::AsAbstractConstruction;
use ecitygml::model::construction::enums::HeightStatusValue;
use ecitygml_core::model::core::refs::AbstractCityObjectKindRef;
use rayon::prelude::*;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let path = std::env::args()
        .nth(1)
        .unwrap_or_else(|| "model.gml".to_string());

    // Parse the CityGML document into the in-memory city model
    let city_model = GmlReader::from_path(path)?.finish()?;

    // Sum up the measured heights of the top-level buildings in parallel;
    // only heights from the lowest ground point to the top of construction
    // given in meters are taken into account
    let total_height: f64 = city_model
        .city_object_members()
        .par_iter()
        .filter_map(|member| member.object())
        .map(AbstractCityObjectKindRef::from)
        .filter_map(|object| <&Building>::try_from(object).ok())
        .flat_map_iter(|building| building.heights())
        .filter(|height| {
            height.low_reference().value() == "lowestGroundPoint"
                && height.high_reference().value() == "topOfConstruction"
                && height.status() == HeightStatusValue::Measured
                && height.length().uom() == "urn:adv:uom:m"
        })
        .map(|height| height.length().value())
        .sum();
    println!("Total measured height of buildings: {total_height:.3} m");

    Ok(())
}
