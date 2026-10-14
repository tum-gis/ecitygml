//! Prints a report of every building in a CityGML file: its attributes and its boundary surfaces.
//!
//! Shows how attributes are reached: getters return values directly (`storeys_above_ground()` is an
//! `Option<i64>`), code-list values (`functions()`, `class()`) and codes (`names()`) have a
//! `value()`, measures a value and a unit of measure, and generic attributes are a
//! `GenericAttributeKind` to match on. Boundaries are properties: `object()` is the boundary surface
//! held inline, `href()` the reference otherwise. A wall, roof or ground surface is reached from a
//! boundary with `try_from`, and its doors and windows are its filling surfaces.
//!
//! Usage: cargo run -p ecitygml --example 03_building_report -- path/to/model.gml
//!
//! Output for FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml (shortened):
//!
//!     Building UUID_d281adfc-4901-0f52-540b-4cc1a9325f82
//!       Name: AC14-FZK-Haus
//!       Class: 1000
//!       ...
//!       Boundaries:
//!         WallSurface GML_5856d7ad-5e34-498a-817b-9544bfbb1475
//!           WindowSurface GML_356b85c1-25a0-49f9-b39e-013fbbafcce4
//!           ...

use std::process::ExitCode;

use ecitygml::io::GmlReader;
use ecitygml::model::building::{AsAbstractBuilding, Building};
use ecitygml::model::common::{HasFeatureType, IterFeatures};
use ecitygml::model::construction::{
    AsAbstractConstruction, AsAbstractConstructionSurface, GroundSurface, RoofSurface, WallSurface,
};
use ecitygml::model::core::refs::AbstractFeatureKindRef;
use ecitygml::model::core::{AsAbstractCityObject, AsAbstractFeature, AsAbstractSpace};
use ecitygml::model::generics::GenericAttributeKind;
use egml::model::base::{AsAbstractGml, HasAssociationAttributes};

/// The values, comma-separated; "-" if there are none.
fn joined<'a>(values: impl IntoIterator<Item = &'a str>) -> String {
    let joined = values.into_iter().collect::<Vec<_>>().join(", ");
    if joined.is_empty() {
        "-".to_string()
    } else {
        joined
    }
}

fn optional(value: Option<i64>) -> String {
    value.map_or("-".to_string(), |value| value.to_string())
}

/// The value of a generic attribute: string, integer, double or measure (value and unit).
fn generic_attribute_value(attribute: &GenericAttributeKind) -> String {
    match attribute {
        GenericAttributeKind::StringAttribute(x) => x.value.clone(),
        GenericAttributeKind::IntAttribute(x) => x.value.to_string(),
        GenericAttributeKind::DoubleAttribute(x) => format!("{:.3}", x.value),
        GenericAttributeKind::MeasureAttribute(x) => {
            format!("{:.3} {}", x.value.value, x.value.uom)
        }
        // e.g. a generic attribute set, which holds further attributes
        GenericAttributeKind::GenericAttributeSet(_) => "(not shown)".to_string(),
    }
}

/// The doors and windows of a wall, roof or ground surface.
fn print_fillings(surface: &impl AsAbstractConstructionSurface) {
    for filling in surface.filling_surfaces().iter().filter_map(|p| p.object()) {
        println!("      {} {}", filling.feature_type(), filling.feature_id());
    }
}

fn print_building(building: &Building) {
    println!("Building {}", building.feature_id());
    println!(
        "  Name: {}",
        joined(building.names().iter().map(|name| name.value()))
    );
    println!(
        "  Class: {}",
        joined(building.class().map(|class| class.value()))
    );
    println!(
        "  Functions: {}",
        joined(building.functions().iter().map(|f| f.value()))
    );
    println!(
        "  Usages: {}",
        joined(building.usages().iter().map(|u| u.value()))
    );
    println!(
        "  Roof type: {}",
        joined(building.roof_type().map(|roof_type| roof_type.value()))
    );
    println!(
        "  Storeys above ground: {}",
        optional(building.storeys_above_ground())
    );
    println!(
        "  Storeys below ground: {}",
        optional(building.storeys_below_ground())
    );
    let date = building
        .date_of_construction()
        .map_or("-".to_string(), |date| {
            format!("{:04}-{:02}-{:02}", date.year(), date.month(), date.day())
        });
    println!("  Date of construction: {date}");

    println!("  Heights:");
    for height in building.heights() {
        let length = height.length();
        println!(
            "    {:.3} {} ({} to {})",
            length.value(),
            length.uom(),
            height.high_reference().value(),
            height.low_reference().value()
        );
    }

    println!("  Generic attributes:");
    for attribute in building.generic_attributes() {
        println!(
            "    {}: {}",
            attribute.name(),
            generic_attribute_value(attribute)
        );
    }

    // Each boundary property holds an `AbstractSpaceBoundaryKind` (or only an href). Wall, roof
    // and ground surfaces can have filling surfaces: doors and windows.
    println!("  Boundaries:");
    for boundary_property in building.boundaries() {
        let Some(boundary) = boundary_property.object() else {
            if let Some(href) = boundary_property.href() {
                println!("    (reference to {href})");
            }
            continue;
        };
        println!("    {} {}", boundary.feature_type(), boundary.feature_id());
        let feature = AbstractFeatureKindRef::from(boundary);
        if let Ok(wall) = <&WallSurface>::try_from(feature) {
            print_fillings(wall);
        } else if let Ok(roof) = <&RoofSurface>::try_from(feature) {
            print_fillings(roof);
        } else if let Ok(ground) = <&GroundSurface>::try_from(feature) {
            print_fillings(ground);
        }
    }
}

fn main() -> ExitCode {
    let args: Vec<String> = std::env::args().collect();
    if args.len() != 2 {
        eprintln!("usage: 03_building_report path/to/model.gml");
        return ExitCode::from(2);
    }
    let city_model = match GmlReader::from_path(&args[1]).and_then(|reader| reader.finish()) {
        Ok(city_model) => city_model,
        Err(error) => {
            eprintln!("error: {error}");
            return ExitCode::from(1);
        }
    };

    let buildings: Vec<&Building> = city_model
        .iter_features()
        .filter_map(|feature| feature.try_into().ok())
        .collect();
    if buildings.is_empty() {
        println!("No buildings.");
    }
    for (index, building) in buildings.into_iter().enumerate() {
        if index > 0 {
            println!();
        }
        print_building(building);
    }
    ExitCode::SUCCESS
}
