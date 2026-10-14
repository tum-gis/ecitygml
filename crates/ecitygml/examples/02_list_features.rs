//! Lists the feature types of a CityGML file with their counts, and the ids of its buildings.
//!
//! A city model is a tree of features: the city model, buildings, their wall surfaces, the doors in
//! those walls, and so on. `iter_features()` visits all of them, depth first in document order, as
//! `AbstractFeatureKindRef`s. Each tells its `feature_type()`; to use the getters of its concrete
//! type, convert it with `try_from` (or `try_into`), which fails for other types.
//!
//! Usage: cargo run -p ecitygml --example 02_list_features -- path/to/model.gml
//!
//! Output for FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml (shortened):
//!
//!     Feature type              Count
//!     CityModel                     1
//!     Building                      1
//!     WallSurface                   4
//!     ...
//!     Total                        22
//!
//!     Buildings:
//!       UUID_d281adfc-4901-0f52-540b-4cc1a9325f82

use std::process::ExitCode;

use ecitygml::io::GmlReader;
use ecitygml::model::building::Building;
use ecitygml::model::common::{FeatureType, HasFeatureType, IterFeatures};
use ecitygml::model::core::AsAbstractFeature;

fn main() -> ExitCode {
    let args: Vec<String> = std::env::args().collect();
    if args.len() != 2 {
        eprintln!("usage: 02_list_features path/to/model.gml");
        return ExitCode::from(2);
    }
    let city_model = match GmlReader::from_path(&args[1]).and_then(|reader| reader.finish()) {
        Ok(city_model) => city_model,
        Err(error) => {
            eprintln!("error: {error}");
            return ExitCode::from(1);
        }
    };

    // Count the features per type, in the order the types first appear.
    let mut counts: Vec<(FeatureType, usize)> = Vec::new();
    for feature in city_model.iter_features() {
        let feature_type = feature.feature_type();
        match counts.iter_mut().find(|(t, _)| *t == feature_type) {
            Some((_, count)) => *count += 1,
            None => counts.push((feature_type, 1)),
        }
    }

    println!("{:<24} {:>6}", "Feature type", "Count");
    for (feature_type, count) in &counts {
        println!("{:<24} {:>6}", feature_type.to_string(), count);
    }
    let total: usize = counts.iter().map(|(_, count)| count).sum();
    println!("{:<24} {:>6}", "Total", total);

    // `<&Building>::try_from` turns a feature into a `&Building`; it borrows from the city model.
    println!();
    println!("Buildings:");
    for feature in city_model.iter_features() {
        if let Ok(building) = <&Building>::try_from(feature) {
            println!("  {}", building.feature_id());
        }
    }
    ExitCode::SUCCESS
}
