//! `WallSurface`, `RoofSurface`, `GroundSurface` and their filling surfaces (`DoorSurface`, `WindowSurface`).

use crate::*;

use ecitygml_ffi::citygml::core::model::building::building::Building;
use ecitygml_ffi::citygml::core::model::common::feature_type::FeatureType;
use ecitygml_ffi::citygml::core::model::construction::door_surface::DoorSurface;
use ecitygml_ffi::citygml::core::model::construction::ground_surface::GroundSurface;
use ecitygml_ffi::citygml::core::model::construction::roof_surface::RoofSurface;
use ecitygml_ffi::citygml::core::model::construction::wall_surface::WallSurface;
use ecitygml_ffi::citygml::core::model::construction::window_surface::WindowSurface;

const FZK_LOD2: &str = "FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml";
const FZK_LOD3: &str = "FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml";

/// Name and lod2 area of each surface that `try_from` accepts, in document order.
macro_rules! surfaces {
    ($city_model:expr, $ty:ty) => {{
        let mut features = $city_model.iter_features();
        std::iter::from_fn(|| features.next())
            .filter_map(|feature| <$ty>::try_from(&feature))
            .map(|surface| {
                assert!(surface.lod3_multi_surface().is_none());
                let multi_surface = surface.lod2_multi_surface().unwrap().object().unwrap();
                let name = surface.names().next().unwrap().value().to_owned();
                (name, multi_surface.area_3d().unwrap())
            })
            .collect::<Vec<_>>()
    }};
}

fn total(surfaces: &[(String, f64)]) -> f64 {
    surfaces.iter().map(|(_, area)| area).sum()
}

#[test]
fn wall_roof_and_ground_surfaces() {
    let city_model = read(format!("{FIXTURES}{FZK_LOD2}").as_bytes()).unwrap();

    let walls = surfaces!(city_model, WallSurface);
    let names: Vec<_> = walls.iter().map(|(name, _)| name.as_str()).collect();
    assert_eq!(
        names,
        [
            "Outer Wall 1 (West)",
            "Outer Wall 2 (South)",
            "Outer Wall 3 (East)",
            "Outer Wall 4 (North)"
        ]
    );
    assert!((total(&walls) - 188.62887820601463).abs() < 1e-6);

    let roofs = surfaces!(city_model, RoofSurface);
    assert_eq!(roofs.len(), 2);
    assert!((total(&roofs) - 138.56406460961398).abs() < 1e-6);

    let grounds = surfaces!(city_model, GroundSurface);
    assert_eq!(grounds.len(), 1);
    assert_eq!(grounds[0].0, "Base Surface");
    assert!((grounds[0].1 - 120.0).abs() < 1e-6);
}

#[test]
fn inherited_getters_and_try_from() {
    let city_model = read(format!("{FIXTURES}{FZK_LOD2}").as_bytes()).unwrap();
    let mut features = city_model.iter_features();
    let features: Vec<_> = std::iter::from_fn(|| features.next()).collect();

    let wall = features
        .iter()
        .find_map(|feature| WallSurface::try_from(feature))
        .unwrap();
    // AbstractThematicSurface, AbstractCityObject, AbstractFeature (ecitygml and egml)
    assert!(wall.lod0_multi_curve().is_none());
    assert!(wall.lod0_multi_surface().is_none());
    assert!(wall.lod1_multi_surface().is_none());
    assert!(wall.relative_to_terrain().is_none());
    assert_eq!(
        wall.feature_id().as_str(),
        "GML_5856d7ad-5e34-498a-817b-9544bfbb1475"
    );
    assert!(wall.creation_date().is_none());

    // Each type only accepts its own features.
    let roof = features
        .iter()
        .find(|f| RoofSurface::try_from(f).is_some())
        .unwrap();
    assert!(WallSurface::try_from(roof).is_none());
    assert!(GroundSurface::try_from(roof).is_none());
    let building = features
        .iter()
        .find(|f| Building::try_from(f).is_some())
        .unwrap();
    assert!(RoofSurface::try_from(building).is_none());
}

#[test]
fn tum_wall_surfaces() {
    let city_model = read(format!("{FIXTURES}TUM-Main-Entrance.gml").as_bytes()).unwrap();
    let mut features = city_model.iter_features();
    let total_area: f64 = std::iter::from_fn(|| features.next())
        .filter_map(|feature| WallSurface::try_from(&feature))
        .map(|wall| {
            wall.lod2_multi_surface()
                .unwrap()
                .object()
                .unwrap()
                .area_3d()
                .unwrap()
        })
        .sum();
    assert!((total_area - 3783.390891).abs() < 1e-3, "{total_area}");
}

#[test]
fn door_and_window_surfaces() {
    let city_model = read(format!("{FIXTURES}{FZK_LOD3}").as_bytes()).unwrap();
    let mut features = city_model.iter_features();
    let features: Vec<_> = std::iter::from_fn(|| features.next()).collect();
    let lod3_area = |surface: Option<&ecitygml_ffi::gml::core::model::geometry::aggregates::multi_surface_property::MultiSurfaceProperty>| {
        surface.unwrap().object().unwrap().area_3d().unwrap()
    };

    let doors: Vec<_> = features
        .iter()
        .filter_map(|f| DoorSurface::try_from(f))
        .collect();
    let names: Vec<_> = doors
        .iter()
        .map(|d| d.names().next().unwrap().value())
        .collect();
    assert_eq!(names, ["Door West", "Door South"]);
    let door_area: f64 = doors
        .iter()
        .map(|d| lod3_area(d.lod3_multi_surface()))
        .sum();
    assert!((door_area - 6.803850099444389).abs() < 1e-6, "{door_area}");
    assert!(doors[0].lod2_multi_surface().is_none());

    let windows: Vec<_> = features
        .iter()
        .filter_map(|f| WindowSurface::try_from(f))
        .collect();
    assert_eq!(windows.len(), 11);
    let window_area: f64 = windows
        .iter()
        .map(|w| lod3_area(w.lod3_multi_surface()))
        .sum();
    assert!(
        (window_area - 23.168802611529827).abs() < 1e-6,
        "{window_area}"
    );

    // A door isn't a window or a wall.
    let door = features
        .iter()
        .find(|f| DoorSurface::try_from(f).is_some())
        .unwrap();
    assert!(WindowSurface::try_from(door).is_none());
    assert!(WallSurface::try_from(door).is_none());
}

#[test]
fn filling_surfaces_of_construction_surfaces() {
    let city_model = read(format!("{FIXTURES}{FZK_LOD3}").as_bytes()).unwrap();
    let mut features = city_model.iter_features();
    let features: Vec<_> = std::iter::from_fn(|| features.next()).collect();

    let west = features
        .iter()
        .find_map(|f| WallSurface::try_from(f))
        .unwrap();
    assert_eq!(west.names().next().unwrap().value(), "Outer Wall 1 (West)");
    let mut fillings = west.filling_surfaces();
    let mut seen = Vec::new();
    while let Some(property) = fillings.next() {
        assert!(property.href().is_none());
        let filling = property.object().unwrap();
        // AbstractFillingSurfaceKind carries the getters of every ancestor, like the concrete types.
        let area = filling
            .lod3_multi_surface()
            .unwrap()
            .object()
            .unwrap()
            .area_3d()
            .unwrap();
        assert!(area > 0.0);
        seen.push((
            filling.feature_type(),
            filling.names().next().unwrap().value(),
        ));
    }
    assert_eq!(
        seen,
        [
            (FeatureType::WindowSurface, "Window Round"),
            (FeatureType::WindowSurface, "Window North"),
            (FeatureType::DoorSurface, "Door West"),
            (FeatureType::WindowSurface, "Window South"),
        ]
    );

    let total: usize = features
        .iter()
        .filter_map(|f| WallSurface::try_from(f))
        .map(|wall| {
            let mut fillings = wall.filling_surfaces();
            std::iter::from_fn(|| fillings.next()).count()
        })
        .sum();
    assert_eq!(total, 13);
    let roof = features
        .iter()
        .find_map(|f| RoofSurface::try_from(f))
        .unwrap();
    assert!(roof.filling_surfaces().next().is_none());
}
