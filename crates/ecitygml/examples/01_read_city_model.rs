//! Reads a CityGML file and prints an overview of the city model.
//!
//! This is the starting point for every program using ecitygml: `GmlReader` reads a file (plain,
//! `.gml.gz` or `.gml.zst`) into a `CityModel`, which owns all features. Errors, e.g. a missing file
//! or invalid XML, are returned as `ecitygml::io::Error`.
//!
//! Usage: cargo run -p ecitygml --example 01_read_city_model -- path/to/model.gml
//!
//! Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml:
//!
//!     City object members: 1
//!     City objects (at all depths): 8
//!     Envelope:
//!       lower corner: 457842.000, 5439083.000, 111.800
//!       upper corner: 457854.000, 5439093.000, 118.318
//!       size: 12.000 x 10.000 x 6.518

use std::process::ExitCode;

use ecitygml::io::GmlReader;
use egml::model::feature::AsAbstractFeature;

fn main() -> ExitCode {
    let args: Vec<String> = std::env::args().collect();
    if args.len() != 2 {
        eprintln!("usage: 01_read_city_model path/to/model.gml");
        return ExitCode::from(2);
    }

    // `from_path` opens the file and picks the format from its extension; `finish` parses it.
    let city_model = match GmlReader::from_path(&args[1]).and_then(|reader| reader.finish()) {
        Ok(city_model) => city_model,
        Err(error) => {
            eprintln!("error: {error}");
            return ExitCode::from(1);
        }
    };

    // `cityObjectMember`s are the top-level city objects (e.g. buildings); their boundary surfaces,
    // doors and windows are city objects too, which `iter_city_objects()` visits as well.
    println!(
        "City object members: {}",
        city_model.city_object_members_len()
    );
    println!(
        "City objects (at all depths): {}",
        city_model.iter_city_objects().count()
    );

    // `bounded_by()` is the `gml:boundedBy` property, a bounding shape holding an envelope; both
    // are optional, as in the file.
    let Some(envelope) = city_model.bounded_by().and_then(|shape| shape.envelope()) else {
        println!("Envelope: none");
        return ExitCode::SUCCESS;
    };
    let (lower, upper) = (envelope.lower_corner(), envelope.upper_corner());
    println!("Envelope:");
    println!(
        "  lower corner: {:.3}, {:.3}, {:.3}",
        lower.x(),
        lower.y(),
        lower.z()
    );
    println!(
        "  upper corner: {:.3}, {:.3}, {:.3}",
        upper.x(),
        upper.y(),
        upper.z()
    );
    println!(
        "  size: {:.3} x {:.3} x {:.3}",
        envelope.size_x(),
        envelope.size_y(),
        envelope.size_z()
    );
    ExitCode::SUCCESS
}
