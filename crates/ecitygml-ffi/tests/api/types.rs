//! The cases of `types.md`.

use crate::*;

use ecitygml_ffi::citygml::core::model::building::building::Building;
use ecitygml_ffi::citygml::core::model::common::level_of_detail::LevelOfDetail;
use ecitygml_ffi::citygml::core::model::construction::door_surface::DoorSurface;
use ecitygml_ffi::citygml::core::model::construction::ground_surface::GroundSurface;
use ecitygml_ffi::citygml::core::model::construction::roof_surface::RoofSurface;
use ecitygml_ffi::citygml::core::model::construction::wall_surface::WallSurface;
use ecitygml_ffi::citygml::core::model::construction::window_surface::WindowSurface;
use ecitygml_ffi::citygml::core::model::core::refs::abstract_feature_kind_ref::AbstractFeatureKindRef;
use ecitygml_ffi::citygml::core::model::transportation::auxiliary_traffic_area::AuxiliaryTrafficArea;
use ecitygml_ffi::citygml::core::model::transportation::auxiliary_traffic_space::AuxiliaryTrafficSpace;
use ecitygml_ffi::citygml::core::model::transportation::road::Road;
use ecitygml_ffi::citygml::core::model::transportation::section::Section;
use ecitygml_ffi::citygml::core::model::transportation::traffic_area::TrafficArea;
use ecitygml_ffi::citygml::core::model::transportation::traffic_space::TrafficSpace;
use ecitygml_ffi::citygml::core::model::vegetation::solitary_vegetation_object::SolitaryVegetationObject;
use ecitygml_ffi::gml::core::model::geometry::direct_position::DirectPosition;
use ecitygml_ffi::gml::core::model::xs::date::Date;
use ecitygml_ffi::gml::core::model::xs::date_time::DateTime;

const FZK_LOD1: &str = "fzk-haus/FZK-Haus-LoD1-KIT-IAI-KHH-B36-V1__v3.gml";
const FZK_LOD2: &str = "fzk-haus/FZK-Haus-LoD2-KIT-IAI-KHH-B36-V1__v3.gml";
const FZK_LOD3: &str = "fzk-haus/FZK-Haus-LoD3-KIT-IAI-KHH-B36-V1__v3.gml";
const TUM: &str = "tum-main-entrance/TUM-Main-Entrance.gml";
const ASAM_ROAD_SHAPE: &str = "asam-opendrive/ASAM-UC_RoadShape.gml";
const ASAM_JUNCTION: &str = "asam-opendrive/ASAM-Ex_Bidirectional_Junction.gml";
const RAILWAY: &str = "railway-scene/Railway_Scene_LoD3__v3-thinned.gml";
const SIG3D: &str = "http://www.sig3d.org/codelists/citygml/2.0/building/2.0/_AbstractBuilding_";

/// The first feature that `try_from` accepts.
fn first<'a, T: 'a>(
    city_model: &'a CityModel,
    try_from: impl Fn(&AbstractFeatureKindRef<'a>) -> Option<&'a T>,
) -> &'a T {
    let mut features = city_model.iter_features();
    std::iter::from_fn(|| features.next())
        .find_map(|feature| try_from(&feature))
        .expect("should have a feature of the type")
}

#[test]
fn direct_position_new() {
    let position = DirectPosition::new(1.0, 2.0, 3.0).unwrap();
    assert_eq!((position.x(), position.y(), position.z()), (1.0, 2.0, 3.0));
    let error = DirectPosition::new(f64::NAN, 0.0, 0.0).err().unwrap();
    assert_error(&error, ErrorKind::InvalidArgument, "non-finite");
}

#[test]
fn level_of_detail_index() {
    let all = [
        LevelOfDetail::Zero,
        LevelOfDetail::One,
        LevelOfDetail::Two,
        LevelOfDetail::Three,
    ];
    for (index, lod) in all.into_iter().enumerate() {
        assert_eq!(lod.as_index(), index);
        assert_eq!(LevelOfDetail::try_from(index as u8).unwrap(), lod);
    }
    let error = LevelOfDetail::try_from(4).unwrap_err();
    assert_error(&error, ErrorKind::InvalidArgument, "4");
}

#[test]
fn feature_type_name() {
    assert_eq!(written(|w| FeatureType::Building.to_string(w)), "Building");
    assert_eq!(
        written(|w| FeatureType::TinRelief.to_string(w)),
        "TinRelief"
    );
}

#[test]
fn date_from_parts() {
    let date = Date::from_parts(2020, 1, 2, 3600).unwrap();
    assert_eq!(
        (date.year(), date.month(), date.day(), date.offset_seconds()),
        (2020, 1, 2, 3600)
    );
    let start = date.start_of_day();
    assert_eq!((start.hour(), start.minute(), start.second()), (0, 0, 0));
    assert_eq!(
        written(|w| start.to_rfc3339(w)),
        "2020-01-02T00:00:00+01:00"
    );

    let error = Date::from_parts(2021, 2, 30, 0).err().unwrap();
    assert_error(
        &error,
        ErrorKind::InvalidArgument,
        "do not form a valid date",
    );
}

#[test]
fn date_time_from_parts() {
    let date_time = DateTime::from_parts(2017, 1, 23, 13, 14, 15, 500_000_000, -7200).unwrap();
    assert_eq!(
        (date_time.year(), date_time.month(), date_time.day()),
        (2017, 1, 23)
    );
    assert_eq!(
        (date_time.hour(), date_time.minute(), date_time.second()),
        (13, 14, 15)
    );
    assert_eq!(date_time.nanosecond(), 500_000_000);
    assert_eq!(date_time.offset_seconds(), -7200);
    assert_eq!(date_time.timestamp(), 1485184455);
    assert_eq!(date_time.timestamp_subsec_nanos(), 500_000_000);
    assert_eq!(
        written(|w| date_time.to_rfc3339(w)),
        "2017-01-23T13:14:15.500-02:00"
    );

    let error = DateTime::from_parts(2020, 1, 1, 0, 0, 0, 0, 30)
        .err()
        .unwrap();
    assert_error(
        &error,
        ErrorKind::InvalidArgument,
        "timezone offset of 30 s is invalid",
    );
}

#[test]
fn date_time_read() {
    let city_model = read(&fixture(FZK_LOD2));
    let created = first(&city_model, |f| Building::try_from(f))
        .creation_date()
        .unwrap();
    assert_eq!(
        written(|w| created.to_rfc3339(w)),
        "2017-01-23T00:00:00+01:00"
    );
}

/// Asserts that `$ty::try_from` accepts exactly the features of `FeatureType::$ty`.
macro_rules! assert_try_from_matches {
    ($city_model:expr, $($ty:ident),+) => {{
        let mut features = $city_model.iter_features();
        while let Some(feature) = features.next() {
            let feature_type = feature.feature_type();
            $(
                assert_eq!(
                    $ty::try_from(&feature).is_some(),
                    feature_type == FeatureType::$ty,
                    "{} as {feature_type:?}",
                    stringify!($ty)
                );
            )+
        }
    }};
}

#[test]
fn try_from_matches_feature_type() {
    let city_model = read(&fixture(FZK_LOD3));
    assert_try_from_matches!(
        city_model,
        Building,
        WallSurface,
        RoofSurface,
        GroundSurface,
        DoorSurface,
        WindowSurface
    );
    let city_model = read(&fixture(ASAM_ROAD_SHAPE));
    assert_try_from_matches!(
        city_model,
        Road,
        Section,
        TrafficSpace,
        TrafficArea,
        AuxiliaryTrafficSpace,
        AuxiliaryTrafficArea
    );
}

#[test]
fn feature_from_city_object() {
    let city_model = read(&fixture(ASAM_JUNCTION));
    let city_object = city_model.iter_city_objects().next().unwrap();
    assert_eq!(city_object.feature_type(), FeatureType::Road);
    let feature = AbstractFeatureKindRef::from_city_object(&city_object);
    assert_eq!(feature.feature_type(), FeatureType::Road);
    let road = Road::try_from(&feature).unwrap();
    assert_eq!(
        road.feature_id().as_str(),
        "UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f"
    );
    assert!(Building::try_from(&feature).is_none());
}

#[test]
fn matrix_index_out_of_range() {
    let city_model = read(&fixture(RAILWAY));
    let mut features = city_model.iter_features();
    let tree = std::iter::from_fn(|| features.next())
        .filter_map(|f| SolitaryVegetationObject::try_from(&f))
        .find(|tree| tree.feature_id().as_str() == "GMLID_SO092422_3593_9527")
        .unwrap();
    let matrix = tree
        .lod3_implicit_representation()
        .unwrap()
        .object()
        .unwrap()
        .transformation_matrix();
    assert_eq!(matrix.get(3, 3).unwrap(), 1.0);
    for (row, column) in [(4, 0), (0, 4)] {
        let error = matrix.get(row, column).unwrap_err();
        assert_error(&error, ErrorKind::InvalidArgument, "out of range");
    }
}

#[test]
fn gml_id() {
    let city_model = read(&fixture(FZK_LOD1));
    let generated = city_model.feature_id().as_str();
    assert!(
        generated.starts_with("ecitygml-gen-feature-"),
        "{generated}"
    );
    assert_eq!(city_model.id().map(|id| id.as_str()), Some(generated));

    let city_model = read(&fixture(FZK_LOD2));
    let wall = first(&city_model, |f| WallSurface::try_from(f));
    let id = "GML_5856d7ad-5e34-498a-817b-9544bfbb1475";
    assert_eq!(wall.id().map(|id| id.as_str()), Some(id));
    assert_eq!(wall.feature_id().as_str(), id);

    let city_model = read(&fixture(TUM));
    assert_eq!(
        first(&city_model, |f| Building::try_from(f))
            .id()
            .map(|id| id.as_str()),
        Some("DEBY_LOD2_4959457")
    );
}

#[test]
fn code_space() {
    let city_model = read(&fixture(FZK_LOD2));
    let building = first(&city_model, |f| Building::try_from(f));
    let class = building.class().unwrap().code();
    assert_eq!(class.value(), "1000");
    assert_eq!(
        class.code_space(),
        Some(format!("{SIG3D}class.xml").as_str())
    );
    let mut functions = building.functions();
    let function = functions.next().unwrap();
    assert!(functions.next().is_none());
    assert_eq!(
        function.code().code_space(),
        Some(format!("{SIG3D}function.xml").as_str())
    );
    let mut usages = building.usages();
    let usage = usages.next().unwrap();
    assert!(usages.next().is_none());
    assert_eq!(
        usage.code().code_space(),
        Some(format!("{SIG3D}usage.xml").as_str())
    );

    let city_model = read(&fixture(TUM));
    let mut functions = first(&city_model, |f| Building::try_from(f)).functions();
    let function = functions.next().unwrap();
    assert!(functions.next().is_none());
    assert_eq!(function.value(), "31001_3020");
    assert!(function.code().code_space().is_none());

    let city_model = read(&fixture(FZK_LOD1));
    let mut names = city_model.names();
    let name = names.next().unwrap();
    assert!(names.next().is_none());
    assert_eq!(name.value(), "AC14-FZK-Haus");
    assert!(name.code_space().is_none());
}
