//! Measures the geometry of every building in a CityGML file: areas and triangle counts of its wall,
//! roof and ground surfaces, its doors and windows, and the volumes of its solids.
//!
//! Geometry calculations work on the geometry stored inline: `area_3d()` of a multi surface,
//! `volume_3d()` of a solid, `triangulate()` (a `Triangulation`, whose `surface()` holds the
//! triangles). They return an `egml::Error` when they can't compute a result. A common case: a solid
//! whose surfaces only reference the boundary polygons by `xlink:href` (the reader doesn't resolve
//! such references). Triangulation skips such surfaces, so this example checks for them before
//! computing a volume, shown as "not computable" with the reason.
//!
//! Usage: cargo run -p ecitygml --example 05_measure_geometry -- path/to/model.gml
//!
//! Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml (shortened):
//!
//!     Building UUID_d281adfc-4901-0f52-540b-4cc1a9325f82
//!       WallSurface: 4, area 188.629 m^2, 10 triangles
//!       RoofSurface: 2, area 138.564 m^2, 4 triangles
//!       GroundSurface: 1, area 120.000 m^2, 2 triangles
//!       Doors and windows: 0, area 0.000 m^2
//!       LoD2 solid: 7 surfaces, 7 of them xlink:href references
//!         Volume: not computable (surface member references '#PolyID7350_878_759628_120742' via ...)

use std::process::ExitCode;

use ecitygml::io::GmlReader;
use ecitygml::model::building::Building;
use ecitygml::model::common::IterFeatures;
use ecitygml::model::construction::{
    AsAbstractConstructionSurface, GroundSurface, RoofSurface, WallSurface,
};
use ecitygml::model::core::refs::AbstractFeatureKindRef;
use ecitygml::model::core::{AsAbstractFeature, AsAbstractSpace, AsAbstractThematicSurface};
use egml::model::base::HasAssociationAttributes;
use egml::model::common::Triangulate;
use egml::model::geometry::aggregates::MultiSurface;
use egml::model::geometry::primitives::Solid;

/// The multi surface of the highest level of detail a thematic surface has (LoD3 first).
fn highest_lod_multi_surface(surface: &impl AsAbstractThematicSurface) -> Option<&MultiSurface> {
    [
        surface.lod3_multi_surface(),
        surface.lod2_multi_surface(),
        surface.lod1_multi_surface(),
        surface.lod0_multi_surface(),
    ]
    .into_iter()
    .find_map(|property| property?.object())
}

#[derive(Default)]
struct Measurement {
    count: usize,
    area: f64,
    triangles: usize,
}

impl Measurement {
    /// Adds a surface with its highest LoD multi surface (if it has one).
    fn add(&mut self, surface: &impl AsAbstractThematicSurface) -> Result<(), egml::Error> {
        self.count += 1;
        if let Some(multi_surface) = highest_lod_multi_surface(surface) {
            self.area += multi_surface.area_3d()?;
            self.triangles += multi_surface.triangulate()?.surface().triangles().len();
        }
        Ok(())
    }
}

fn print_boundaries(building: &Building) -> Result<(), egml::Error> {
    let mut walls = Measurement::default();
    let mut roofs = Measurement::default();
    let mut grounds = Measurement::default();
    let mut fillings = Measurement::default();
    for boundary in building.boundaries().iter().filter_map(|p| p.object()) {
        let feature = AbstractFeatureKindRef::from(boundary);
        // Doors and windows are the filling surfaces of wall, roof and ground surfaces.
        let filling_surfaces = if let Ok(wall) = <&WallSurface>::try_from(feature) {
            walls.add(wall)?;
            wall.filling_surfaces()
        } else if let Ok(roof) = <&RoofSurface>::try_from(feature) {
            roofs.add(roof)?;
            roof.filling_surfaces()
        } else if let Ok(ground) = <&GroundSurface>::try_from(feature) {
            grounds.add(ground)?;
            ground.filling_surfaces()
        } else {
            continue;
        };
        for filling in filling_surfaces.iter().filter_map(|p| p.object()) {
            fillings.add(filling)?;
        }
    }
    for (label, m) in [
        ("WallSurface", &walls),
        ("RoofSurface", &roofs),
        ("GroundSurface", &grounds),
    ] {
        println!(
            "  {label}: {}, area {:.3} m^2, {} triangles",
            m.count, m.area, m.triangles
        );
    }
    println!(
        "  Doors and windows: {}, area {:.3} m^2",
        fillings.count, fillings.area
    );
    Ok(())
}

/// The volume of a solid, or why it can't be computed: surfaces referenced by `xlink:href` are not
/// resolved, so they are reported instead of computing the volume of an incomplete shell.
fn volume(solid: &Solid) -> Result<f64, String> {
    let members = solid
        .exterior()
        .map(|shell| shell.members())
        .unwrap_or_default();
    if let Some(href) = members
        .iter()
        .find(|m| m.object().is_none())
        .and_then(|m| m.href())
    {
        return Err(format!(
            "surface member references '{href}' via xlink:href, which is not resolved"
        ));
    }
    solid.volume_3d().map_err(|error| error.to_string())
}

fn print_solids(building: &Building) {
    let solids = [
        (1, building.lod1_solid()),
        (2, building.lod2_solid()),
        (3, building.lod3_solid()),
    ];
    for (lod, solid) in solids
        .into_iter()
        .filter_map(|(lod, p)| Some((lod, p?.object()?)))
    {
        let members = solid
            .exterior()
            .map(|shell| shell.members())
            .unwrap_or_default();
        let references = members.iter().filter(|m| m.object().is_none()).count();
        println!(
            "  LoD{lod} solid: {} surfaces, {references} of them xlink:href references",
            members.len()
        );
        match volume(solid) {
            Ok(volume) => println!("    Volume: {volume:.3} m^3"),
            Err(reason) => println!("    Volume: not computable ({reason})"),
        }
    }
}

fn main() -> ExitCode {
    let args: Vec<String> = std::env::args().collect();
    if args.len() != 2 {
        eprintln!("usage: 05_measure_geometry path/to/model.gml");
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
        println!("Building {}", building.feature_id());
        if let Err(error) = print_boundaries(building) {
            // e.g. a surface that can't be triangulated
            println!("  Boundaries: not computable ({error})");
        }
        print_solids(building);
    }
    ExitCode::SUCCESS
}
