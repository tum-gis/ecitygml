//! The cases of `crates/ecitygml/tests/conformance/asam-opendrive.md`.

use crate::{assert_close, read};
use ecitygml::model::common::{FeatureType, HasFeatureType, IterFeatures};
use ecitygml::model::core::enums::SpaceType;
use ecitygml::model::core::refs::AbstractFeatureKindRef;
use ecitygml::model::core::{
    AbstractSpaceBoundaryProperty, AsAbstractCityObject, AsAbstractFeature,
    AsAbstractFeatureWithLifespan, AsAbstractSpace, AsAbstractThematicSurface, CityModel,
};
use ecitygml::model::generics::GenericAttributeKind;
use ecitygml::model::transportation::enums::{GranularityValue, TrafficDirectionValue};
use ecitygml::model::transportation::{
    AsAbstractTransportationSpace, AuxiliaryTrafficArea, Marking, Road, Section, TrafficArea,
    TrafficSpace,
};
use egml::model::base::{AsAbstractGml, HasAssociationAttributes, Reference};
use egml::model::feature::AsAbstractFeature as _;
use egml::model::geometry::DirectPosition;
use egml::model::geometry::aggregates::MultiCurve;
use egml::model::geometry::primitives::AbstractCurveKind;

fn road(city_model: &CityModel) -> &Road {
    city_model
        .iter_features()
        .find_map(|feature| feature.try_into().ok())
        .expect("should have a road")
}

fn first_name(feature: &impl AsAbstractGml) -> &str {
    feature.names().first().expect("should have a name").value()
}

fn feature_types(city_model: &CityModel) -> Vec<FeatureType> {
    city_model
        .iter_features()
        .map(|feature| feature.feature_type())
        .collect()
}

fn assert_point_close(position: &DirectPosition, expected: (f64, f64, f64)) {
    assert_close(position.x(), expected.0);
    assert_close(position.y(), expected.1);
    assert_close(position.z(), expected.2);
}

fn assert_envelope(city_model: &CityModel, lower: (f64, f64, f64), upper: (f64, f64, f64)) {
    let envelope = city_model
        .bounded_by()
        .and_then(|shape| shape.envelope())
        .expect("should have an envelope");
    assert_point_close(envelope.lower_corner(), lower);
    assert_point_close(envelope.upper_corner(), upper);
}

/// The objects of inline properties; fails on a reference-only property.
fn objects<'a, P: HasAssociationAttributes + 'a, T: 'a>(
    properties: &'a [P],
    object: impl Fn(&'a P) -> Option<&'a T>,
) -> Vec<&'a T> {
    properties
        .iter()
        .map(|property| {
            assert!(property.href().is_none());
            object(property).expect("should be inline")
        })
        .collect()
}

/// The feature ids of features.
fn ids<'a>(features: impl IntoIterator<Item = &'a (impl AsAbstractFeature + 'a)>) -> Vec<&'a str> {
    features
        .into_iter()
        .map(|feature| feature.feature_id().as_str())
        .collect()
}

/// The single boundary of a space, inline, as a `T`.
fn only_boundary<'a, T>(boundaries: &'a [AbstractSpaceBoundaryProperty]) -> &'a T
where
    &'a T: TryFrom<AbstractFeatureKindRef<'a>>,
{
    let [boundary] = objects(boundaries, |property| property.object())[..] else {
        panic!("expected exactly one boundary");
    };
    AbstractFeatureKindRef::from(boundary)
        .try_into()
        .ok()
        .expect("unexpected boundary type")
}

/// The single curve member of an inline multi curve, as a line string: (point count, length).
fn line_string(multi_curve: &MultiCurve) -> (usize, f64) {
    let [member] = objects(multi_curve.curve_member(), |property| property.object())[..] else {
        panic!("expected exactly one curve member");
    };
    let AbstractCurveKind::LineString(line_string) = member else {
        panic!("expected a line string, got {member:?}");
    };
    (line_string.points().len(), line_string.length_3d())
}

fn local_ids(references: &[ecitygml::model::transportation::TrafficSpaceReference]) -> Vec<String> {
    references
        .iter()
        .map(|reference| {
            Reference::from(reference)
                .href()
                .and_then(|href| href.local_id())
                .expect("should reference a local id")
                .to_owned()
        })
        .collect()
}

mod road_shape {
    use super::*;

    fn city_model() -> CityModel {
        read("asam-opendrive", "ASAM-UC_RoadShape.gml")
    }

    fn section(road: &Road) -> &Section {
        let [section] = objects(road.sections(), |property| property.object())[..] else {
            panic!("expected exactly one section");
        };
        section
    }

    fn traffic_spaces(road: &Road) -> Vec<&TrafficSpace> {
        objects(section(road).traffic_spaces(), |property| property.object())
    }

    #[test]
    fn road_shape_city_model() {
        let city_model = city_model();
        assert_eq!(city_model.city_object_members_len(), 1);
        let types = [
            FeatureType::CityModel,
            FeatureType::Road,
            FeatureType::Section,
            FeatureType::TrafficSpace,
            FeatureType::TrafficArea,
            FeatureType::TrafficSpace,
            FeatureType::TrafficArea,
            FeatureType::AuxiliaryTrafficSpace,
            FeatureType::AuxiliaryTrafficArea,
            FeatureType::AuxiliaryTrafficSpace,
            FeatureType::AuxiliaryTrafficArea,
        ];
        assert_eq!(feature_types(&city_model), types);
        assert_eq!(
            city_model
                .iter_city_objects()
                .map(|object| object.feature_type())
                .collect::<Vec<_>>(),
            types[1..]
        );
        assert_envelope(
            &city_model,
            (-50.21567184593757, -2.4442507170297514, 0.0),
            (-13.007511850967884, 29.053746110395082, 4.95),
        );
    }

    #[test]
    fn road_shape_road() {
        let city_model = city_model();
        let road = road(&city_model);
        assert_eq!(
            road.feature_id().as_str(),
            "UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f"
        );
        assert!(road.class().is_none());
        assert!(road.traffic_direction().is_none());
        assert!(road.functions().is_empty());
        assert!(road.usages().is_empty());
        assert!(road.intersections().is_empty());
        assert!(road.occupancies().is_empty());
        assert!(road.traffic_spaces().is_empty());
        assert!(road.auxiliary_traffic_spaces().is_empty());
        assert!(road.markings().is_empty());
        assert!(road.holes().is_empty());
        assert_eq!(
            section(road).feature_id().as_str(),
            "UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29"
        );
    }

    #[test]
    fn road_shape_section() {
        let city_model = city_model();
        let section = section(road(&city_model));
        assert!(section.class().is_none());
        assert!(section.traffic_direction().is_none());
        assert!(section.lod0_multi_curve().is_none());
        assert!(section.lod1_solid().is_none());
        assert!(section.markings().is_empty());
        assert!(section.holes().is_empty());
        assert_eq!(
            ids(objects(section.traffic_spaces(), |p| p.object())),
            [
                "UUID_ae81947d-a661-3678-a5ee-eed58b68694f",
                "UUID_6e4de408-1e54-3869-b7ce-1be3f2261421",
            ]
        );
        assert_eq!(
            ids(objects(section.auxiliary_traffic_spaces(), |p| p.object())),
            [
                "UUID_12298df9-4982-33a8-ab4a-9953410bbff7",
                "UUID_f8211bb5-0ce8-36e1-9b84-73d30114f578",
            ]
        );
    }

    #[test]
    fn road_shape_traffic_spaces() {
        let city_model = city_model();
        let spaces = traffic_spaces(road(&city_model));
        assert_eq!(
            spaces
                .iter()
                .map(|space| space.traffic_direction())
                .collect::<Vec<_>>(),
            [
                Some(TrafficDirectionValue::Backwards),
                Some(TrafficDirectionValue::Forwards)
            ]
        );
        for space in spaces {
            assert_eq!(space.granularity(), &GranularityValue::Lane);
            assert!(space.class().is_none());
            assert_eq!(
                space
                    .functions()
                    .iter()
                    .map(|f| f.value())
                    .collect::<Vec<_>>(),
                ["1"]
            );
            assert_eq!(
                space.usages().iter().map(|u| u.value()).collect::<Vec<_>>(),
                ["2"]
            );
            assert!(space.occupancies().is_empty());
            assert_eq!(space.space_type(), Some(SpaceType::Open));
            assert!(space.relative_to_terrain().is_none());
            assert!(space.creation_date().is_none());
            assert!(space.predecessors().is_empty());
            assert!(space.successors().is_empty());
            only_boundary::<TrafficArea>(space.boundaries());
        }
    }

    #[test]
    fn road_shape_generic_attributes() {
        let city_model = city_model();
        let space = traffic_spaces(road(&city_model))[0];
        let attributes: Vec<(&str, String)> = space
            .generic_attributes()
            .iter()
            .map(|attribute| {
                let value = match attribute {
                    GenericAttributeKind::IntAttribute(x) => format!("int {}", x.value),
                    GenericAttributeKind::DoubleAttribute(x) => format!("double {:?}", x.value),
                    GenericAttributeKind::StringAttribute(x) => format!("string {}", x.value),
                    other => panic!("unexpected attribute {other:?}"),
                };
                (attribute.name(), value)
            })
            .collect();
        let expected = [
            ("identifier_laneId", "int 1"),
            ("identifier_laneSectionId", "int 0"),
            ("identifier_roadId", "string 1"),
            ("opendrive_road_length", "double 40.0"),
            ("opendrive_road_rule", "string RIGHT_HAND_TRAFFIC"),
            ("opendrive_laneSection_curvePositionStart", "double 0.0"),
            ("opendrive_lane_type", "string DRIVING"),
            ("opendrive_lane_level", "string false"),
        ];
        assert_eq!(
            attributes,
            expected.map(|(name, value)| (name, value.to_owned()))
        );
    }

    #[test]
    fn road_shape_traffic_space_geometry() {
        let city_model = city_model();
        let spaces = traffic_spaces(road(&city_model));
        let volumes: Vec<f64> = spaces
            .iter()
            .map(|space| {
                space
                    .lod2_solid()
                    .and_then(|property| property.object())
                    .expect("should have an LoD2 solid")
                    .volume_3d()
                    .expect("should compute")
            })
            .collect();
        assert_close(volumes[0], 720.0);
        assert_close(volumes[1], 540.0);
        for space in spaces {
            let property = space.lod2_multi_curve().expect("should have an LoD2 curve");
            assert!(property.href().is_none());
            let multi_curve = property.object().expect("should be inline");
            assert_close(multi_curve.length_3d().expect("should compute"), 40.0);
            let (points, length) = line_string(multi_curve);
            assert_eq!(points, 2);
            assert_close(length, 40.0);
            assert!(space.lod0_multi_curve().is_none());
            assert!(space.lod3_multi_curve().is_none());
            assert!(space.lod1_solid().is_none());
            assert!(space.lod3_solid().is_none());
            assert!(space.lod2_multi_surface().is_none());
        }
    }

    #[test]
    fn road_shape_traffic_areas() {
        let city_model = city_model();
        let areas: Vec<&TrafficArea> = traffic_spaces(road(&city_model))
            .iter()
            .map(|space| only_boundary::<TrafficArea>(space.boundaries()))
            .collect();
        assert_eq!(
            ids(areas.iter().copied()),
            [
                "UUID_8625bf6f-57cb-3ddf-8fd1-6674b756a2e2",
                "UUID_dc110e80-dadc-3c87-b864-2854cc0cb39a",
            ]
        );
        let mut area_3d = Vec::new();
        for area in areas {
            assert_eq!(first_name(area), "Lane");
            assert!(area.class().is_none());
            assert_eq!(
                area.functions()
                    .iter()
                    .map(|f| f.value())
                    .collect::<Vec<_>>(),
                ["1"]
            );
            assert_eq!(
                area.usages().iter().map(|u| u.value()).collect::<Vec<_>>(),
                ["2"]
            );
            assert!(area.surface_material().is_none());
            assert!(area.lod0_multi_curve().is_none());
            assert!(area.lod0_multi_surface().is_none());
            assert!(area.lod1_multi_surface().is_none());
            assert!(area.lod3_multi_surface().is_none());
            assert!(area.relative_to_terrain().is_none());
            let multi_surface = area
                .lod2_multi_surface()
                .and_then(|property| property.object())
                .expect("should have an LoD2 multi surface");
            assert_eq!(multi_surface.surface_member().len(), 1);
            area_3d.push(multi_surface.area_3d().expect("should compute"));
        }
        assert_close(area_3d[0], 160.79800993793438);
        assert_close(area_3d[1], 121.34249049694012);
    }

    #[test]
    fn road_shape_auxiliary_traffic() {
        let city_model = city_model();
        let section = section(road(&city_model));
        let mut areas = Vec::new();
        for space in objects(section.auxiliary_traffic_spaces(), |p| p.object()) {
            assert_eq!(space.granularity(), &GranularityValue::Lane);
            assert!(space.class().is_none());
            assert!(space.functions().is_empty());
            assert!(space.usages().is_empty());
            assert_eq!(space.space_type(), Some(SpaceType::Open));
            let solid = space
                .lod2_solid()
                .and_then(|property| property.object())
                .expect("should have an LoD2 solid");
            assert_close(solid.volume_3d().expect("should compute"), 100.0);
            let multi_curve = space
                .lod2_multi_curve()
                .and_then(|property| property.object())
                .expect("should have an LoD2 curve");
            assert_close(multi_curve.length_3d().expect("should compute"), 40.0);
            areas.push(only_boundary::<AuxiliaryTrafficArea>(space.boundaries()));
        }
        assert_eq!(
            ids(areas.iter().copied()),
            [
                "UUID_4890681a-e9fa-365e-a676-f89afb453f9b",
                "UUID_d3c71d48-5222-355e-8037-9677aee30d7e",
            ]
        );
        for area in areas {
            assert_eq!(first_name(area), "Lane");
            assert!(area.class().is_none());
            assert!(area.functions().is_empty());
            assert!(area.usages().is_empty());
            assert!(area.surface_material().is_none());
            let multi_surface = area
                .lod2_multi_surface()
                .and_then(|property| property.object())
                .expect("should have an LoD2 multi surface");
            assert_close(multi_surface.area_3d().expect("should compute"), 40.0);
        }
    }
}

mod junction {
    use super::*;

    fn city_model() -> CityModel {
        read("asam-opendrive", "ASAM-Ex_Bidirectional_Junction.gml")
    }

    fn traffic_spaces(city_model: &CityModel) -> Vec<&TrafficSpace> {
        city_model
            .iter_features()
            .filter_map(|feature| feature.try_into().ok())
            .collect()
    }

    const SPACES: [&str; 7] = [
        "UUID_ae81947d-a661-3678-a5ee-eed58b68694f",
        "UUID_6e4de408-1e54-3869-b7ce-1be3f2261421",
        "UUID_9582b02f-5cc7-38f8-b79c-a3a18b31856c",
        "UUID_c772e261-27f1-30b6-8a94-1ccf23e71a74",
        "UUID_656f23c9-92b6-3c98-a1bf-40b5f2625b13",
        "UUID_86f8df09-c972-332b-a279-636373ce4e0c",
        "UUID_144a6807-5844-32b2-bb34-8b2671b1afaa",
    ];

    #[test]
    fn junction_city_model() {
        let city_model = city_model();
        assert_eq!(city_model.city_object_members_len(), 1);
        use FeatureType::{
            CityModel, Intersection, Marking, Road, Section, TrafficArea, TrafficSpace,
        };
        assert_eq!(
            feature_types(&city_model),
            [
                CityModel,
                Road,
                Section,
                TrafficSpace,
                TrafficArea,
                TrafficSpace,
                TrafficArea,
                Marking,
                Marking,
                Marking,
                Marking,
                Section,
                TrafficSpace,
                TrafficArea,
                Section,
                TrafficSpace,
                TrafficArea,
                Intersection,
                TrafficSpace,
                TrafficArea,
                TrafficSpace,
                TrafficArea,
                TrafficSpace,
                TrafficArea,
            ]
        );
        assert_eq!(city_model.iter_city_objects().count(), 23);
        assert_envelope(
            &city_model,
            (-52.66282419815818, -37.4146115571896, 0.0),
            (34.10760429351533, 6.338805461729647, 0.0),
        );
    }

    #[test]
    fn junction_road() {
        let city_model = city_model();
        let road = road(&city_model);
        assert_eq!(
            road.feature_id().as_str(),
            "UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f"
        );
        let sections = objects(road.sections(), |property| property.object());
        assert_eq!(
            ids(sections.iter().copied()),
            [
                "UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29",
                "UUID_ef20f165-2564-373a-a5f8-98fd15f1ae69",
                "UUID_4799566b-daf4-3135-aa9d-ec1b34a9167d",
            ]
        );
        assert_eq!(
            sections
                .iter()
                .map(|s| s.traffic_spaces().len())
                .collect::<Vec<_>>(),
            [2, 1, 1]
        );
        assert_eq!(
            sections
                .iter()
                .map(|s| s.markings().len())
                .collect::<Vec<_>>(),
            [4, 0, 0]
        );
        assert!(
            sections
                .iter()
                .all(|s| s.auxiliary_traffic_spaces().is_empty())
        );
        let [intersection] = objects(road.intersections(), |property| property.object())[..] else {
            panic!("expected exactly one intersection");
        };
        assert_eq!(
            intersection.feature_id().as_str(),
            "UUID_47b7678d-e8b1-36ca-90b6-5b86cc859571"
        );
        assert!(intersection.class().is_none());
        assert_eq!(
            ids(objects(intersection.traffic_spaces(), |p| p.object())),
            SPACES[4..]
        );
    }

    #[test]
    fn junction_traffic_spaces() {
        let city_model = city_model();
        let spaces = traffic_spaces(&city_model);
        assert_eq!(ids(spaces.iter().copied()), SPACES);
        assert_eq!(
            spaces
                .iter()
                .map(|space| space.traffic_direction())
                .collect::<Vec<_>>(),
            [Some(TrafficDirectionValue::Backwards)]
                .into_iter()
                .chain([Some(TrafficDirectionValue::Forwards); 6])
                .collect::<Vec<_>>()
        );
        assert!(spaces.iter().all(|space| space.lod2_solid().is_none()));
        let curves: Vec<(usize, f64)> = spaces
            .iter()
            .map(|space| {
                line_string(
                    space
                        .lod2_multi_curve()
                        .and_then(|property| property.object())
                        .expect("should have an LoD2 curve"),
                )
            })
            .collect();
        assert_eq!(
            curves.iter().map(|(points, _)| *points).collect::<Vec<_>>(),
            [9, 9, 5, 6, 7, 8, 7]
        );
        let lengths = [
            36.74683751297985,
            36.74683751297985,
            20.0,
            21.746217945006258,
            26.761532846607814,
            30.210435770102656,
            30.0,
        ];
        for ((_, actual), expected) in curves.iter().zip(lengths) {
            assert_close(*actual, expected);
        }
    }

    #[test]
    fn junction_traffic_areas() {
        let city_model = city_model();
        let surfaces: Vec<(usize, f64)> = city_model
            .iter_features()
            .filter_map(|feature| <&TrafficArea>::try_from(feature).ok())
            .map(|area| {
                let multi_surface = area
                    .lod2_multi_surface()
                    .and_then(|property| property.object())
                    .expect("should have an LoD2 multi surface");
                (
                    multi_surface.surface_member().len(),
                    multi_surface.area_3d().expect("should compute"),
                )
            })
            .collect();
        assert_eq!(
            surfaces
                .iter()
                .map(|(members, _)| *members)
                .collect::<Vec<_>>(),
            [8, 8, 4, 5, 6, 7, 6]
        );
        let areas = [
            112.81279116484816,
            112.81279116484816,
            61.4,
            66.76088909116919,
            81.22157625123039,
            92.69041581703632,
            92.1,
        ];
        for ((_, actual), expected) in surfaces.iter().zip(areas) {
            assert_close(*actual, expected);
        }
    }

    #[test]
    fn junction_traffic_space_links() {
        let city_model = city_model();
        let links: Vec<(Vec<String>, Vec<String>)> = traffic_spaces(&city_model)
            .iter()
            .map(|space| {
                (
                    local_ids(space.predecessors()),
                    local_ids(space.successors()),
                )
            })
            .collect();
        let [s0, s1, s2, s3, s4, s5, s6] = SPACES;
        let expected: [(&[&str], &[&str]); 7] = [
            (&[], &[]),
            (&[], &[s6]),
            (&[s4, s5], &[]),
            (&[], &[s4]),
            (&[s3], &[s2]),
            (&["UUID_d7d4aa5a-88c9-328d-9151-a6c043e57d7f"], &[s0]),
            (&[s1], &[s2]),
        ];
        assert_eq!(
            links,
            expected.map(|(predecessors, successors)| (
                predecessors.iter().map(|id| id.to_string()).collect(),
                successors.iter().map(|id| id.to_string()).collect()
            ))
        );
    }

    #[test]
    fn junction_markings() {
        let city_model = city_model();
        let road = road(&city_model);
        let section = objects(road.sections(), |property| property.object())[0];
        let markings: Vec<&Marking> = objects(section.markings(), |property| property.object());
        let mut areas = Vec::new();
        for marking in markings {
            assert_eq!(first_name(marking), "RoadMarking");
            assert!(marking.class().is_none());
            assert!(marking.lod0_multi_surface().is_none());
            assert!(marking.lod3_multi_surface().is_none());
            let multi_surface = marking
                .lod2_multi_surface()
                .and_then(|property| property.object())
                .expect("should have an LoD2 multi surface");
            assert_eq!(multi_surface.surface_member().len(), 1);
            areas.push(multi_surface.area_3d().expect("should compute"));
        }
        assert_eq!(areas.len(), 4);
        for (actual, expected) in areas.iter().zip([0.48, 0.48, 0.48, 0.08962050155758661]) {
            assert_close(*actual, expected);
        }
    }
}
