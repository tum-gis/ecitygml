//! Walks the road network of a CityGML file: roads, their sections and intersections, and the
//! traffic and auxiliary traffic spaces in them, with centre-line lengths, traffic-area areas and
//! the volumes of the traffic spaces.
//!
//! CityGML 3.0 models transportation as spaces: a road holds sections and intersections, each of
//! them holds traffic spaces (e.g. lanes) and auxiliary traffic spaces (e.g. sidewalks), and their
//! ground surfaces are traffic areas, reached through the space's boundaries with `try_from`.
//! Geometry calculations (`length_3d`, `area_3d`, `volume_3d`) can fail, e.g. for geometry only
//! referenced by `xlink:href`; such a value is shown as "not computable" and counted as 0.
//!
//! Usage: cargo run -p ecitygml --example 04_road_network -- path/to/model.gml
//!
//! Output for ASAM-UC_RoadShape.gml (shortened):
//!
//!     Road UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f
//!       Section UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29
//!         TrafficSpace UUID_ae81947d-a661-3678-a5ee-eed58b686946
//!           Centre line (LoD2): 40.000 m
//!           Volume (LoD2 solid): 720.000 m^3
//!           TrafficArea UUID_8625bf6f-57cb-3ddf-8fd1-6674b756a2e2: 160.798 m^2
//!     ...
//!     Total volume of traffic spaces (LoD2): 1260.000 m^3

use std::process::ExitCode;

use ecitygml::io::GmlReader;
use ecitygml::model::common::IterFeatures;
use ecitygml::model::core::refs::AbstractFeatureKindRef;
use ecitygml::model::core::{AsAbstractFeature, AsAbstractSpace, AsAbstractThematicSurface};
use ecitygml::model::transportation::{
    AsAbstractTransportationSpace, AuxiliaryTrafficArea, Road, TrafficArea,
};

/// Counts and sums over all spaces of one kind (traffic or auxiliary traffic spaces).
#[derive(Default)]
struct Totals {
    spaces: usize,
    length: f64,
    volume: f64,
    areas: usize,
    area: f64,
}

/// Traffic spaces have traffic areas, auxiliary traffic spaces auxiliary traffic areas.
#[derive(Clone, Copy)]
enum SpaceKind {
    Traffic,
    Auxiliary,
}

/// The measurement as text (e.g. "40.000 m") and value; "-" without geometry, and a note if the
/// calculation fails (counted as 0).
fn measured<G>(
    geometry: Option<&G>,
    measure: impl Fn(&G) -> Result<f64, egml::Error>,
    unit: &str,
) -> (String, f64) {
    match geometry.map(measure) {
        None => ("-".to_string(), 0.0),
        Some(Err(error)) => (format!("not computable ({error})"), 0.0),
        Some(Ok(value)) => (format!("{value:.3} {unit}"), value),
    }
}

fn print_space(
    space: &(impl AsAbstractSpace + AsAbstractFeature),
    kind: SpaceKind,
    totals: &mut Totals,
    indent: &str,
) {
    let (space_label, area_label) = match kind {
        SpaceKind::Traffic => ("TrafficSpace", "TrafficArea"),
        SpaceKind::Auxiliary => ("AuxiliaryTrafficSpace", "AuxiliaryTrafficArea"),
    };
    println!("{indent}{space_label} {}", space.feature_id());
    let curve = space.lod2_multi_curve().and_then(|p| p.object());
    let (length_text, length) = measured(curve, |c| c.length_3d(), "m");
    let solid = space.lod2_solid().and_then(|p| p.object());
    let (volume_text, volume) = measured(solid, |s| s.volume_3d(), "m^3");
    println!("{indent}  Centre line (LoD2): {length_text}");
    println!("{indent}  Volume (LoD2 solid): {volume_text}");
    totals.spaces += 1;
    totals.length += length;
    totals.volume += volume;

    // The areas are the space's boundaries of the matching type.
    for boundary in space.boundaries().iter().filter_map(|p| p.object()) {
        let feature = AbstractFeatureKindRef::from(boundary);
        let area = match kind {
            SpaceKind::Traffic => <&TrafficArea>::try_from(feature)
                .ok()
                .map(|a| (a.feature_id(), a.lod2_multi_surface())),
            SpaceKind::Auxiliary => <&AuxiliaryTrafficArea>::try_from(feature)
                .ok()
                .map(|a| (a.feature_id(), a.lod2_multi_surface())),
        };
        let Some((id, surface)) = area else {
            continue;
        };
        let (area_text, value) = measured(surface.and_then(|p| p.object()), |s| s.area_3d(), "m^2");
        println!("{indent}  {area_label} {id}: {area_text}");
        totals.areas += 1;
        totals.area += value;
    }
}

/// The traffic and auxiliary traffic spaces of a road, section or intersection.
fn print_spaces_of(
    transportation_space: &impl AsAbstractTransportationSpace,
    traffic: &mut Totals,
    auxiliary: &mut Totals,
    indent: &str,
) {
    for space in transportation_space
        .traffic_spaces()
        .iter()
        .filter_map(|p| p.object())
    {
        print_space(space, SpaceKind::Traffic, traffic, indent);
    }
    for space in transportation_space
        .auxiliary_traffic_spaces()
        .iter()
        .filter_map(|p| p.object())
    {
        print_space(space, SpaceKind::Auxiliary, auxiliary, indent);
    }
}

fn main() -> ExitCode {
    let args: Vec<String> = std::env::args().collect();
    if args.len() != 2 {
        eprintln!("usage: 04_road_network path/to/model.gml");
        return ExitCode::from(2);
    }
    let city_model = match GmlReader::from_path(&args[1]).and_then(|reader| reader.finish()) {
        Ok(city_model) => city_model,
        Err(error) => {
            eprintln!("error: {error}");
            return ExitCode::from(1);
        }
    };

    let (mut traffic, mut auxiliary) = (Totals::default(), Totals::default());
    let roads: Vec<&Road> = city_model
        .iter_features()
        .filter_map(|feature| feature.try_into().ok())
        .collect();
    for road in &roads {
        println!("Road {}", road.feature_id());
        print_spaces_of(*road, &mut traffic, &mut auxiliary, "  "); // a road can hold spaces directly, too
        for section in road.sections().iter().filter_map(|p| p.object()) {
            println!("  Section {}", section.feature_id());
            print_spaces_of(section, &mut traffic, &mut auxiliary, "    ");
        }
        for intersection in road.intersections().iter().filter_map(|p| p.object()) {
            println!("  Intersection {}", intersection.feature_id());
            print_spaces_of(intersection, &mut traffic, &mut auxiliary, "    ");
        }
    }

    println!();
    println!("Roads: {}", roads.len());
    for (label, totals) in [
        ("Traffic spaces", &traffic),
        ("Auxiliary traffic spaces", &auxiliary),
    ] {
        println!(
            "{label}: {}, centre lines {:.3} m, {} areas {:.3} m^2, volume {:.3} m^3",
            totals.spaces, totals.length, totals.areas, totals.area, totals.volume
        );
    }
    println!(
        "Total volume of traffic spaces (LoD2): {:.3} m^3",
        traffic.volume
    );
    ExitCode::SUCCESS
}
