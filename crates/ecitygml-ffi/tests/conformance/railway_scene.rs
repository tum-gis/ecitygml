//! The cases of `crates/ecitygml/tests/conformance/railway-scene.md`.

use crate::{assert_close, read, written};
use ecitygml_ffi::citygml::core::model::bridge::bridge::Bridge;
use ecitygml_ffi::citygml::core::model::building::building::Building;
use ecitygml_ffi::citygml::core::model::city_furniture::city_furniture::CityFurniture;
use ecitygml_ffi::citygml::core::model::common::feature_type::FeatureType;
use ecitygml_ffi::citygml::core::model::common::level_of_detail::LevelOfDetail;
use ecitygml_ffi::citygml::core::model::core::city_model::CityModel;
use ecitygml_ffi::citygml::core::model::core::enums::relative_to_terrain::RelativeToTerrain;
use ecitygml_ffi::citygml::core::model::core::implicit_geometry::ImplicitGeometry;
use ecitygml_ffi::citygml::core::model::core::refs::abstract_feature_kind_ref::AbstractFeatureKindRef;
use ecitygml_ffi::citygml::core::model::relief::relief_feature::ReliefFeature;
use ecitygml_ffi::citygml::core::model::relief::tin_relief::TinRelief;
use ecitygml_ffi::citygml::core::model::tunnel::tunnel::Tunnel;
use ecitygml_ffi::citygml::core::model::vegetation::solitary_vegetation_object::SolitaryVegetationObject;
use ecitygml_ffi::citygml::io::format::CitygmlFormat;
use ecitygml_ffi::citygml::io::gml::read::GmlReader;
use ecitygml_ffi::citygml::io::gml::write::GmlWriter;
use ecitygml_ffi::gml::core::model::basic_types::code::CodeIterator;
use ecitygml_ffi::gml::core::model::geometry::aggregates::multi_surface::MultiSurface;

const TEMPLATE_A: &str = "#Mult_SO043561_5693_194007";
const TEMPLATE_B: &str = "#Mult_SO045475_3243_790864";

/// A tree's `feature_id`, first name, `class`, `species` and `functions`.
type ExpectedTree = (
    &'static str,
    &'static str,
    Option<&'static str>,
    &'static str,
    &'static [&'static str],
);

/// All items of a Diplomat iterator.
macro_rules! items {
    // A match keeps the temporaries the iterator borrows from alive.
    ($iterator:expr) => {
        match $iterator {
            mut iterator => std::iter::from_fn(|| iterator.next()).collect::<Vec<_>>(),
        }
    };
}

fn city_model() -> Box<CityModel> {
    read("railway-scene", "Railway_Scene_LoD3__v3-thinned.gml")
}

fn features(city_model: &CityModel) -> Vec<Box<AbstractFeatureKindRef<'_>>> {
    items!(city_model.iter_features())
}

fn feature_types(city_model: &CityModel) -> Vec<FeatureType> {
    features(city_model)
        .iter()
        .map(|feature| feature.feature_type())
        .collect()
}

fn first_name(names: Box<CodeIterator<'_>>) -> &str {
    items!(names).first().expect("should have a name").value()
}

fn tunnels(city_model: &CityModel) -> Vec<&Tunnel> {
    features(city_model)
        .iter()
        .filter_map(|f| Tunnel::try_from(f))
        .collect()
}

fn trees(city_model: &CityModel) -> Vec<&SolitaryVegetationObject> {
    features(city_model)
        .iter()
        .filter_map(|f| SolitaryVegetationObject::try_from(f))
        .collect()
}

fn furniture(city_model: &CityModel) -> Vec<&CityFurniture> {
    features(city_model)
        .iter()
        .filter_map(|f| CityFurniture::try_from(f))
        .collect()
}

fn buildings(city_model: &CityModel) -> Vec<&Building> {
    features(city_model)
        .iter()
        .filter_map(|f| Building::try_from(f))
        .collect()
}

fn bridges(city_model: &CityModel) -> Vec<&Bridge> {
    features(city_model)
        .iter()
        .filter_map(|f| Bridge::try_from(f))
        .collect()
}

/// A tree's inline LoD3 implicit geometry.
fn implicit_geometry(tree: &SolitaryVegetationObject) -> &ImplicitGeometry {
    let property = tree
        .lod3_implicit_representation()
        .expect("should have an LoD3 implicit representation");
    assert!(property.href().is_none());
    property.object().expect("should be inline")
}

/// The `href` of a tree's relative geometry, or none if it is inline.
fn template_href(tree: &SolitaryVegetationObject) -> Option<String> {
    implicit_geometry(tree)
        .relative_geometry()
        .and_then(|property| property.href())
        .map(|href| written(|w| href.to_string(w)))
}

fn matrix(geometry: &ImplicitGeometry, row: usize, column: usize) -> f64 {
    geometry
        .transformation_matrix()
        .get(row, column)
        .unwrap_or_else(|_| panic!("({row}, {column}) should be in range"))
}

#[test]
fn railway_city_model() {
    use FeatureType::*;
    let city_model = city_model();
    assert_eq!(city_model.city_objects_len(), 52);
    assert!(city_model.bounded_by().is_none());
    let types = feature_types(&city_model);
    assert_eq!(types.len(), 232);
    assert_eq!(types[0], CityModel);
    for (feature_type, count) in [
        (CityModel, 1),
        (SolitaryVegetationObject, 15),
        (Tunnel, 4),
        (TunnelInstallation, 8),
        (Railway, 10),
        (Bridge, 4),
        (BridgeConstructiveElement, 3),
        (BridgeInstallation, 2),
        (Building, 3),
        (BuildingInstallation, 56),
        (CityFurniture, 11),
        (CityObjectGroup, 1),
        (GenericOccupiedSpace, 2),
        (WaterBody, 1),
        (WaterSurface, 1),
        (WaterGroundSurface, 1),
        (ReliefFeature, 1),
        (TinRelief, 1),
        (WallSurface, 33),
        (RoofSurface, 12),
        (GroundSurface, 7),
        (ClosureSurface, 8),
        (DoorSurface, 9),
        (WindowSurface, 34),
        (OuterCeilingSurface, 3),
        (OuterFloorSurface, 1),
    ] {
        assert_eq!(
            types.iter().filter(|t| **t == feature_type).count(),
            count,
            "{feature_type:?}"
        );
    }
    assert_eq!(items!(city_model.iter_city_objects()).len(), 231);
}

#[test]
fn railway_tunnels() {
    use FeatureType::{
        ClosureSurface as Closure, GroundSurface as Ground, RoofSurface as Roof,
        WallSurface as Wall,
    };
    let city_model = city_model();
    let expected = [
        (
            "GMLID_BUI142242_863_347",
            "Tunnel KIT/KHH-3",
            [Ground, Wall, Roof, Wall, Closure, Closure],
        ),
        (
            "GMLID_BUI336993_213_9312",
            "Tunnel KIT/KHH-2",
            [Wall, Roof, Wall, Closure, Closure, Ground],
        ),
        (
            "GMLID_BUI289877_1911_4122",
            "Tunnel KIT/KHH-4",
            [Wall, Ground, Closure, Wall, Roof, Closure],
        ),
        (
            "GMLID_BUI180021_673_14143",
            "Tunnel KIT/KHH-1",
            [Ground, Wall, Roof, Closure, Closure, Wall],
        ),
    ];
    let tunnels = tunnels(&city_model);
    assert_eq!(tunnels.len(), expected.len());
    for (tunnel, (id, name, boundaries)) in tunnels.iter().zip(expected) {
        assert_eq!(tunnel.feature_id().as_str(), id);
        assert_eq!(first_name(tunnel.names()), name);
        let types: Vec<FeatureType> = items!(tunnel.boundaries())
            .into_iter()
            .map(|property| {
                assert!(property.href().is_none());
                property.object().expect("should be inline").feature_type()
            })
            .collect();
        assert_eq!(types, boundaries);
        assert!(tunnel.class().is_none());
        assert!(tunnel.functions().next().is_none());
        assert!(tunnel.usages().next().is_none());
        assert!(tunnel.tunnel_parts().next().is_none());
        let created = tunnel.creation_date().expect("should have a creation date");
        assert_eq!(
            (created.year(), created.month(), created.day()),
            (2015, 3, 6)
        );
        assert_eq!((created.hour(), created.minute()), (0, 0));
        assert_eq!(created.offset_seconds(), 3600);
        assert_eq!(
            tunnel.relative_to_terrain(),
            Some(RelativeToTerrain::EntirelyAboveTerrain)
        );
    }
}

#[test]
fn railway_trees() {
    let city_model = city_model();
    let expected: [ExpectedTree; 15] = [
        (
            "GMLID_SO0158953_776_12462",
            "Forest tree 3",
            Some("1070"),
            "1800",
            &[],
        ),
        ("GMLID_SO092422_3593_9527", "Tree1", None, "9999", &["LOD3"]),
        (
            "GMLID_SO0200811_525_4986",
            "Forest tree 1",
            Some("1060"),
            "1640",
            &[],
        ),
        (
            "GMLID_SO0321978_1466_7441",
            "Forest tree 4",
            Some("1070"),
            "1800",
            &[],
        ),
        (
            "GMLID_SO0260143_1214_1315",
            "Forest tree 11",
            Some("1060"),
            "1640",
            &[],
        ),
        (
            "GMLID_SO0400934_2926_3381",
            "Forest tree 12",
            Some("1060"),
            "1640",
            &[],
        ),
        (
            "GMLID_SO0124800_3522_13577",
            "Forest tree 13",
            Some("1060"),
            "1640",
            &[],
        ),
        (
            "GMLID_SO0443764_1492_9667",
            "Forest tree 14",
            Some("1060"),
            "1640",
            &[],
        ),
        (
            "GMLID_SO015374_872_14131",
            "Forest tree 2",
            Some("1060"),
            "1640",
            &[],
        ),
        (
            "GMLID_SO081792_2341_11961",
            "Forest tree 10",
            Some("1060"),
            "1640",
            &[],
        ),
        (
            "GMLID_SO0283142_1335_8999",
            "Forest tree 7",
            Some("1060"),
            "1640",
            &[],
        ),
        (
            "GMLID_SO0107241_3793_12555",
            "Forest tree 9",
            Some("1070"),
            "1800",
            &[],
        ),
        (
            "GMLID_SO0286258_965_2893",
            "Forest tree 5",
            Some("1070"),
            "1800",
            &[],
        ),
        (
            "GMLID_SO0410128_214_10515",
            "Forest tree 6",
            Some("1060"),
            "1640",
            &[],
        ),
        (
            "GMLID_SO086970_1053_8814",
            "Forest tree 8",
            Some("1060"),
            "1640",
            &[],
        ),
    ];
    let trees = trees(&city_model);
    assert_eq!(trees.len(), expected.len());
    for (tree, (id, name, class, species, functions)) in trees.iter().zip(expected) {
        assert_eq!(tree.feature_id().as_str(), id);
        assert_eq!(first_name(tree.names()), name);
        assert_eq!(tree.class().map(|c| c.value()), class);
        assert_eq!(tree.species().map(|s| s.value()), Some(species));
        assert_eq!(
            items!(tree.functions())
                .iter()
                .map(|f| f.value())
                .collect::<Vec<_>>(),
            functions
        );
        assert!(tree.usages().next().is_none());
        assert!(tree.lod1_implicit_representation().is_none());
        assert!(tree.lod2_implicit_representation().is_none());
    }
}

#[test]
fn railway_tree_templates() {
    let city_model = city_model();
    for tree in trees(&city_model) {
        let geometry = implicit_geometry(tree);
        assert!(geometry.mime_type().is_none());
        for (row, column, value) in [(0, 0, 30.0), (1, 1, 30.0), (2, 2, 30.0), (3, 3, 1.0)] {
            assert_close(matrix(geometry, row, column), value);
        }
        let name = first_name(tree.names());
        let property = geometry
            .relative_geometry()
            .expect("should have a relative geometry");
        match name {
            "Forest tree 3" | "Tree1" | "Forest tree 1" => {
                assert!(property.href().is_none());
                let multi_surface =
                    MultiSurface::try_from(property.object().expect("should be inline"))
                        .unwrap_or_else(|| panic!("{name}: expected a multi surface"));
                assert_eq!(items!(multi_surface.surface_member()).len(), 1);
            }
            "Forest tree 4" | "Forest tree 9" | "Forest tree 5" => {
                assert!(property.object().is_none());
                assert_eq!(template_href(tree).as_deref(), Some(TEMPLATE_A), "{name}");
            }
            _ => {
                assert!(property.object().is_none());
                assert_eq!(template_href(tree).as_deref(), Some(TEMPLATE_B), "{name}");
            }
        }
    }
}

#[test]
fn railway_tree_placement() {
    let city_model = city_model();
    for tree in trees(&city_model) {
        let geometry = implicit_geometry(tree);
        let point = geometry
            .reference_point()
            .object()
            .expect("should have a reference point")
            .pos();
        let translation = (
            matrix(geometry, 0, 3),
            matrix(geometry, 1, 3),
            matrix(geometry, 2, 3),
        );
        let (reference, expected_translation) = match first_name(tree.names()) {
            "Forest tree 3" => (
                (-600.0, 400.0, -150.0),
                Some((39.4421005419207, 220.3838834926932, 268.5013679006178)),
            ),
            "Tree1" => (
                (-568.8000793496976, 457.60044759869743, 105.00139681350242),
                Some((0.0, 0.0, 0.0)),
            ),
            _ => ((-600.0, 400.0, -150.0), None),
        };
        assert_close(point.x(), reference.0);
        assert_close(point.y(), reference.1);
        assert_close(point.z(), reference.2);
        if let Some(expected) = expected_translation {
            assert_close(translation.0, expected.0);
            assert_close(translation.1, expected.1);
            assert_close(translation.2, expected.2);
        }
    }
}

#[test]
fn railway_furniture() {
    let city_model = city_model();
    let expected = [
        ("GMLID_7431654_78949_792", "1090"),
        ("GMLID_0528986_170479_94", "OTHERS"),
        ("GMLID_4323540_367099_910", "1090"),
        ("GMLID_1381455_184173_656", "OTHERS"),
        ("GMLID_1429491_351612_1485", "1090"),
        ("GMLID_5361967_192822_672", "1090"),
        ("GMLID_2108434_31807_876", "1090"),
        ("GMLID_0373494_301709_129", "1540"),
        ("GMLID_6162422_289094_1279", "1090"),
        ("GMLID_3313190_307178_612", "1090"),
        ("GMLID_855011_330784_753", "1540"),
    ];
    let furniture = furniture(&city_model);
    assert_eq!(furniture.len(), expected.len());
    for (item, (id, function)) in furniture.iter().zip(expected) {
        assert_eq!(item.feature_id().as_str(), id);
        assert_eq!(
            items!(item.functions())
                .iter()
                .map(|f| f.value())
                .collect::<Vec<_>>(),
            [function]
        );
        assert!(item.class().is_none());
        assert!(item.usages().next().is_none());
        assert!(item.lod3_implicit_representation().is_none());
        let property = item
            .lod3_multi_surface()
            .expect("should have an LoD3 multi surface");
        assert!(property.href().is_none());
        assert_eq!(
            items!(
                property
                    .object()
                    .expect("should be inline")
                    .surface_member()
            )
            .len(),
            1
        );
    }
}

#[test]
fn railway_relief() {
    let city_model = city_model();
    let features = features(&city_model);
    let reliefs: Vec<&ReliefFeature> = features
        .iter()
        .filter_map(|f| ReliefFeature::try_from(f))
        .collect();
    let [relief] = reliefs[..] else {
        panic!("expected one relief feature");
    };
    assert_eq!(relief.feature_id().as_str(), "GMLID_TIN436865_187531_1154");
    assert!(relief.names().next().is_none());
    assert_eq!(relief.lod(), LevelOfDetail::Three);
    let components = items!(relief.relief_components());
    let [component] = components[..] else {
        panic!("expected one relief component");
    };
    assert!(component.href().is_none());
    assert_eq!(
        component.object().expect("should be inline").feature_type(),
        FeatureType::TinRelief
    );

    let tin_reliefs: Vec<&TinRelief> = features
        .iter()
        .filter_map(|f| TinRelief::try_from(f))
        .collect();
    let [tin_relief] = tin_reliefs[..] else {
        panic!("expected one TIN relief");
    };
    assert_eq!(
        tin_relief.feature_id().as_str(),
        "UUID_5aa70b07-6bbf-427b-8222-d72ed77dbfa9"
    );
    assert_eq!(tin_relief.lod(), LevelOfDetail::Three);
    let tin = tin_relief.tin().expect("should have a TIN");
    assert!(tin.href().is_none());
    let surface = tin.object().expect("should be inline");
    assert_eq!(items!(surface.triangles()).len(), 1);
    assert_close(
        surface.area_3d().expect("should compute"),
        3.2750424144626247,
    );
}

#[test]
fn railway_buildings_and_bridges() {
    let city_model = city_model();
    let buildings: Vec<(&str, &str, usize)> = buildings(&city_model)
        .iter()
        .map(|b| {
            (
                b.feature_id().as_str(),
                first_name(b.names()),
                items!(b.boundaries()).len(),
            )
        })
        .collect();
    assert_eq!(
        buildings,
        [
            ("GMLID_BUI184698_512_898", "Station KIT/KHH-1", 13),
            ("GMLID_BUI46739_1739_10911", "Chapel KIT/KHH-1", 19),
            ("GMLID_BUI130363_1235_6047", "Boatshouse KIT/KHH-1", 8),
        ]
    );
    let bridges: Vec<(&str, &str)> = bridges(&city_model)
        .iter()
        .map(|b| (b.feature_id().as_str(), first_name(b.names())))
        .collect();
    assert_eq!(
        bridges,
        [
            ("GMLID_BUI205585_1385_1373", "Bridge KIT 4"),
            ("GMLID_BUI51891_765_738", "Bridge KIT 3"),
            ("GMLID_BUI100628_817_8083", "Bridge KIT 2"),
            ("GMLID_BUI30683_572_6686", "Bridge KIT 1"),
        ]
    );
}

#[test]
fn railway_round_trip() {
    let city_model = city_model();
    let mut writer = GmlWriter::new(CitygmlFormat::Gml);
    writer
        .finish(&city_model)
        .unwrap_or_else(|_| panic!("should write"));
    let written = GmlReader::new(writer.data(), CitygmlFormat::Gml)
        .finish()
        .unwrap_or_else(|_| panic!("should read"));
    assert_eq!(feature_types(&written), feature_types(&city_model));
    let ids = |model: &CityModel| -> Vec<String> {
        let mut ids: Vec<String> = Vec::new();
        ids.extend(
            tunnels(model)
                .iter()
                .map(|x| x.feature_id().as_str().to_owned()),
        );
        ids.extend(
            trees(model)
                .iter()
                .map(|x| x.feature_id().as_str().to_owned()),
        );
        ids.extend(
            furniture(model)
                .iter()
                .map(|x| x.feature_id().as_str().to_owned()),
        );
        ids.extend(
            buildings(model)
                .iter()
                .map(|x| x.feature_id().as_str().to_owned()),
        );
        ids.extend(
            bridges(model)
                .iter()
                .map(|x| x.feature_id().as_str().to_owned()),
        );
        ids
    };
    assert_eq!(ids(&written), ids(&city_model));
    let hrefs = |model: &CityModel| -> Vec<Option<String>> {
        trees(model)
            .iter()
            .map(|tree| template_href(tree))
            .collect()
    };
    assert_eq!(hrefs(&written), hrefs(&city_model));
}
