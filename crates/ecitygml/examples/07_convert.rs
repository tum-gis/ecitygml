//! Converts a CityGML file: reads it and writes it again, e.g. compressed or indented.
//!
//! Shows writing with `GmlWriter`: `from_path` creates the output file and picks the format from its
//! extension (`.gml`, `.gml.gz` or `.gml.zst`), `with_formatting` sets the layout (here indented by
//! two spaces; `Formatting::Compact` writes no line breaks at all), and `finish` writes the city
//! model. Reading the written file back verifies the result.
//!
//! Usage: cargo run -p ecitygml --example 07_convert -- input.gml output.gml.gz
//!
//! Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml, converted to a .gml.gz file:
//!
//!     Read: 1 city object members, 8 city objects
//!     Wrote: gzip-compressed CityGML, indented by 2 spaces
//!     Read back: 1 city object members, 8 city objects

use std::process::ExitCode;

use ecitygml::io::{Error, GmlReader, GmlWriter};
use ecitygml::model::core::CityModel;
use egml::io::util::Formatting;

const INDENT_SIZE: usize = 2;

fn summary(city_model: &CityModel) -> String {
    let city_objects = city_model.iter_city_objects().count();
    format!(
        "{} city object members, {city_objects} city objects",
        city_model.city_object_members_len()
    )
}

/// What `GmlWriter::from_path` writes for this path (it fails for other extensions).
fn format_name(path: &str) -> &'static str {
    if path.ends_with(".gml.gz") {
        "gzip-compressed CityGML"
    } else if path.ends_with(".gml.zst") {
        "zstd-compressed CityGML"
    } else {
        "CityGML"
    }
}

fn convert(input_path: &str, output_path: &str) -> Result<(), Error> {
    let city_model = GmlReader::from_path(input_path)?.finish()?;
    println!("Read: {}", summary(&city_model));

    GmlWriter::from_path(output_path)?
        .with_formatting(Formatting::Indent {
            char: b' ',
            size: INDENT_SIZE,
        })
        .finish(&city_model)?;
    println!(
        "Wrote: {}, indented by {INDENT_SIZE} spaces",
        format_name(output_path)
    );

    let written = GmlReader::from_path(output_path)?.finish()?;
    println!("Read back: {}", summary(&written));
    Ok(())
}

fn main() -> ExitCode {
    let args: Vec<String> = std::env::args().collect();
    if args.len() != 3 {
        eprintln!("usage: 07_convert input.gml output.gml[.gz|.zst]");
        return ExitCode::from(2);
    }
    if let Err(error) = convert(&args[1], &args[2]) {
        eprintln!("error: {error}");
        return ExitCode::from(1);
    }
    ExitCode::SUCCESS
}
