//! Exports the buildings of a CityGML file as a Wavefront OBJ file, one group per surface.
//!
//! Triangulates the highest-LoD geometry of every wall, roof and ground surface, and of their doors and
//! windows (`triangulate()` of a multi surface). A building without boundary surfaces is exported as
//! its solid instead. OBJ is written by hand here: vertices (`v x y z`) and triangles (`f i j k`,
//! 1-based indices over all vertices), grouped with `g name`.
//!
//! Usage: cargo run -p ecitygml --example 06_export_obj -- input.gml output.obj
//!
//! Output for FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml:
//!
//!     Wrote 48 vertices, 16 triangles, 7 groups

use std::fs::File;
use std::io::{BufWriter, Write};
use std::process::ExitCode;

use ecitygml::io::GmlReader;
use ecitygml::model::building::Building;
use ecitygml::model::common::{HasFeatureType, IterFeatures};
use ecitygml::model::construction::{
    AsAbstractConstructionSurface, GroundSurface, RoofSurface, WallSurface,
};
use ecitygml::model::core::refs::AbstractFeatureKindRef;
use ecitygml::model::core::{AsAbstractFeature, AsAbstractSpace, AsAbstractThematicSurface};
use egml::model::common::Triangulate;
use egml::model::geometry::aggregates::MultiSurface;

/// Writes OBJ groups as they come: `g` starts a group, `v` adds a vertex, `f` a triangle of the
/// last three vertices (OBJ indices are 1-based and count all vertices written so far).
struct ObjWriter<W: Write> {
    out: W,
    vertices: usize,
    triangles: usize,
    groups: usize,
}

impl<W: Write> ObjWriter<W> {
    /// Writes the triangles of anything that can be triangulated, e.g. a multi surface or solid.
    fn write_group(
        &mut self,
        name: &str,
        geometry: &impl Triangulate,
    ) -> Result<(), Box<dyn std::error::Error>> {
        writeln!(self.out, "g {name}")?;
        self.groups += 1;
        for triangle in geometry.triangulate()?.surface().triangles() {
            for corner in [triangle.a(), triangle.b(), triangle.c()] {
                writeln!(
                    self.out,
                    "v {:.6} {:.6} {:.6}",
                    corner.x(),
                    corner.y(),
                    corner.z()
                )?;
            }
            let first = self.vertices + 1;
            writeln!(self.out, "f {first} {} {}", first + 1, first + 2)?;
            self.vertices += 3;
            self.triangles += 1;
        }
        Ok(())
    }
}

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

fn write_surface<W: Write>(
    obj: &mut ObjWriter<W>,
    prefix: &str,
    surface: &(impl AsAbstractThematicSurface + AsAbstractFeature),
    type_name: &str,
) -> Result<(), Box<dyn std::error::Error>> {
    match highest_lod_multi_surface(surface) {
        Some(multi_surface) => {
            let name = format!("{prefix}_{type_name}_{}", surface.feature_id());
            obj.write_group(&name, multi_surface)
        }
        None => Ok(()),
    }
}

fn write_construction_surface<W: Write>(
    obj: &mut ObjWriter<W>,
    prefix: &str,
    surface: &(impl AsAbstractConstructionSurface + AsAbstractFeature),
    type_name: &str,
) -> Result<(), Box<dyn std::error::Error>> {
    write_surface(obj, prefix, surface, type_name)?;
    // Doors and windows: `feature_type()` names their type.
    for filling in surface.filling_surfaces().iter().filter_map(|p| p.object()) {
        write_surface(obj, prefix, filling, &filling.feature_type().to_string())?;
    }
    Ok(())
}

fn export_building<W: Write>(
    obj: &mut ObjWriter<W>,
    building: &Building,
) -> Result<(), Box<dyn std::error::Error>> {
    let prefix = building.feature_id().to_string();
    let mut has_surfaces = false;
    for boundary in building.boundaries().iter().filter_map(|p| p.object()) {
        let feature = AbstractFeatureKindRef::from(boundary);
        if let Ok(wall) = <&WallSurface>::try_from(feature) {
            write_construction_surface(obj, &prefix, wall, "WallSurface")?;
        } else if let Ok(roof) = <&RoofSurface>::try_from(feature) {
            write_construction_surface(obj, &prefix, roof, "RoofSurface")?;
        } else if let Ok(ground) = <&GroundSurface>::try_from(feature) {
            write_construction_surface(obj, &prefix, ground, "GroundSurface")?;
        } else {
            continue;
        }
        has_surfaces = true;
    }
    if has_surfaces {
        return Ok(());
    }
    let solids = [
        (3, building.lod3_solid()),
        (2, building.lod2_solid()),
        (1, building.lod1_solid()),
    ];
    if let Some((lod, solid)) = solids
        .into_iter()
        .find_map(|(lod, p)| Some((lod, p?.object()?)))
    {
        obj.write_group(&format!("{prefix}_LoD{lod}Solid"), solid)?;
    }
    Ok(())
}

fn export(
    input_path: &str,
    output_path: &str,
) -> Result<ObjWriter<BufWriter<File>>, Box<dyn std::error::Error>> {
    let city_model = GmlReader::from_path(input_path)?.finish()?;
    let mut obj = ObjWriter {
        out: BufWriter::new(File::create(output_path)?),
        vertices: 0,
        triangles: 0,
        groups: 0,
    };
    for feature in city_model.iter_features() {
        if let Ok(building) = <&Building>::try_from(feature) {
            export_building(&mut obj, building)?;
        }
    }
    obj.out.flush()?;
    Ok(obj)
}

fn main() -> ExitCode {
    let args: Vec<String> = std::env::args().collect();
    if args.len() != 3 {
        eprintln!("usage: 06_export_obj input.gml output.obj");
        return ExitCode::from(2);
    }
    match export(&args[1], &args[2]) {
        Ok(obj) => {
            println!(
                "Wrote {} vertices, {} triangles, {} groups",
                obj.vertices, obj.triangles, obj.groups
            );
            ExitCode::SUCCESS
        }
        Err(error) => {
            eprintln!("error: {error}");
            ExitCode::from(1)
        }
    }
}
