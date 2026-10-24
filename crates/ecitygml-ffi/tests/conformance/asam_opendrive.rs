//! The cases of `crates/ecitygml/tests/conformance/asam-opendrive.md`.

use crate::{assert_close, read};
use ecitygml_ffi::citygml::core::model::common::feature_type::FeatureType;
use ecitygml_ffi::citygml::core::model::core::abstract_space_boundary_property::AbstractSpaceBoundaryPropertyIterator;
use ecitygml_ffi::citygml::core::model::core::city_model::CityModel;
use ecitygml_ffi::citygml::core::model::core::enums::space_type::SpaceType;
use ecitygml_ffi::citygml::core::model::core::refs::abstract_feature_kind_ref::AbstractFeatureKindRef;
use ecitygml_ffi::citygml::core::model::transportation::auxiliary_traffic_area::AuxiliaryTrafficArea;
use ecitygml_ffi::citygml::core::model::transportation::enums::granularity_value::GranularityValue;
use ecitygml_ffi::citygml::core::model::transportation::enums::traffic_direction_value::TrafficDirectionValue;
use ecitygml_ffi::citygml::core::model::transportation::marking::Marking;
use ecitygml_ffi::citygml::core::model::transportation::road::Road;
use ecitygml_ffi::citygml::core::model::transportation::section::Section;
use ecitygml_ffi::citygml::core::model::transportation::traffic_area::TrafficArea;
use ecitygml_ffi::citygml::core::model::transportation::traffic_space::TrafficSpace;
use ecitygml_ffi::citygml::core::model::transportation::traffic_space_reference::TrafficSpaceReferenceIterator;
use ecitygml_ffi::gml::core::model::base::reference::Reference;
use ecitygml_ffi::gml::core::model::geometry::aggregates::multi_curve::MultiCurve;
use ecitygml_ffi::gml::core::model::geometry::direct_position::DirectPosition;
use ecitygml_ffi::gml::core::model::geometry::primitives::line_string::LineString;

/// All items of a Diplomat iterator.
macro_rules! items {
    // A match keeps the temporaries the iterator borrows from alive.
    ($iterator:expr) => {
        match $iterator {
            mut iterator => std::iter::from_fn(|| iterator.next()).collect::<Vec<_>>(),
        }
    };
}

/// The objects of inline properties; fails on a reference-only property.
macro_rules! objects {
    ($iterator:expr) => {
        items!($iterator)
            .into_iter()
            .map(|property| {
                assert!(property.href().is_none());
                property.object().expect("should be inline")
            })
            .collect::<Vec<_>>()
    };
}

/// The feature ids of features.
macro_rules! ids {
    ($features:expr) => {
        $features
            .iter()
            .map(|feature| feature.feature_id().as_str())
            .collect::<Vec<_>>()
    };
}

/// The code values of code list values.
macro_rules! values {
    ($iterator:expr) => {
        items!($iterator)
            .into_iter()
            .map(|value| value.value())
            .collect::<Vec<_>>()
    };
}

fn features(city_model: &CityModel) -> Vec<Box<AbstractFeatureKindRef<'_>>> {
    items!(city_model.iter_features())
}

fn road(city_model: &CityModel) -> &Road {
    features(city_model)
        .iter()
        .find_map(|feature| Road::try_from(feature))
        .expect("should have a road")
}

fn first_name<'a>(mut names: impl FnMut() -> Option<&'a str>) -> &'a str {
    names().expect("should have a name")
}

fn feature_types(city_model: &CityModel) -> Vec<FeatureType> {
    features(city_model)
        .iter()
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

/// The single boundary of a space, inline, as a feature.
fn only_boundary<'a>(
    boundaries: Box<AbstractSpaceBoundaryPropertyIterator<'a>>,
) -> Box<AbstractFeatureKindRef<'a>> {
    let boundaries = objects!(boundaries);
    let [boundary] = boundaries[..] else {
        panic!("expected exactly one boundary");
    };
    AbstractFeatureKindRef::from_space_boundary(boundary)
}

/// The single curve member of an inline multi curve, as a line string: (point count, length).
fn line_string(multi_curve: &MultiCurve) -> (usize, f64) {
    let members = objects!(multi_curve.curve_member());
    let [member] = members[..] else {
        panic!("expected exactly one curve member");
    };
    let line_string = LineString::try_from(member).expect("should be a line string");
    (items!(line_string.points()).len(), line_string.length_3d())
}

fn local_ids(references: Box<TrafficSpaceReferenceIterator<'_>>) -> Vec<String> {
    items!(references)
        .into_iter()
        .map(|reference| {
            Reference::from_traffic_space_reference(reference)
                .href()
                .and_then(|href| href.local_id())
                .expect("should reference a local id")
                .to_owned()
        })
        .collect()
}

mod road_shape {
    use super::*;

    fn city_model() -> Box<CityModel> {
        read("asam-opendrive", "ASAM-UC_RoadShape.gml")
    }

    fn section(road: &Road) -> &Section {
        let sections = objects!(road.sections());
        let [section] = sections[..] else {
            panic!("expected exactly one section");
        };
        section
    }

    fn traffic_spaces(road: &Road) -> Vec<&TrafficSpace> {
        objects!(section(road).traffic_spaces())
    }

    #[test]
    fn road_shape_city_model() {
        let city_model = city_model();
        assert_eq!(city_model.city_objects_len(), 1);
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
            items!(city_model.iter_city_objects())
                .iter()
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
        assert!(road.functions().next().is_none());
        assert!(road.usages().next().is_none());
        assert!(road.intersections().next().is_none());
        assert!(road.occupancies().next().is_none());
        assert!(road.traffic_spaces().next().is_none());
        assert!(road.auxiliary_traffic_spaces().next().is_none());
        assert!(road.markings().next().is_none());
        assert!(road.holes().next().is_none());
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
        assert!(section.markings().next().is_none());
        assert!(section.holes().next().is_none());
        assert_eq!(
            ids!(objects!(section.traffic_spaces())),
            [
                "UUID_ae81947d-a661-3678-a5ee-eed58b68694f",
                "UUID_6e4de408-1e54-3869-b7ce-1be3f2261421",
            ]
        );
        assert_eq!(
            ids!(objects!(section.auxiliary_traffic_spaces())),
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
            assert_eq!(space.granularity(), GranularityValue::Lane);
            assert!(space.class().is_none());
            assert_eq!(values!(space.functions()), ["1"]);
            assert_eq!(values!(space.usages()), ["2"]);
            assert!(space.occupancies().next().is_none());
            assert_eq!(space.space_type(), Some(SpaceType::Open));
            assert!(space.relative_to_terrain().is_none());
            assert!(space.creation_date().is_none());
            assert!(space.predecessors().next().is_none());
            assert!(space.successors().next().is_none());
            assert!(TrafficArea::try_from(&only_boundary(space.boundaries())).is_some());
        }
    }

    #[test]
    fn road_shape_generic_attributes() {
        let city_model = city_model();
        let space = traffic_spaces(road(&city_model))[0];
        let attributes: Vec<(&str, String)> = items!(space.generic_attributes())
            .into_iter()
            .map(|attribute| {
                let value = if let Some(x) = attribute.as_int() {
                    format!("int {}", x.value())
                } else if let Some(x) = attribute.as_double() {
                    format!("double {:?}", x.value())
                } else if let Some(x) = attribute.as_string() {
                    format!("string {}", x.value())
                } else {
                    panic!("unexpected attribute {}", attribute.name())
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
                    .unwrap_or_else(|_| panic!("should compute"))
            })
            .collect();
        assert_close(volumes[0], 720.0);
        assert_close(volumes[1], 540.0);
        for space in spaces {
            let property = space.lod2_multi_curve().expect("should have an LoD2 curve");
            assert!(property.href().is_none());
            let multi_curve = property.object().expect("should be inline");
            assert_close(
                multi_curve
                    .length_3d()
                    .unwrap_or_else(|_| panic!("should compute")),
                40.0,
            );
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
        let boundaries: Vec<_> = traffic_spaces(road(&city_model))
            .iter()
            .map(|space| only_boundary(space.boundaries()))
            .collect();
        let areas: Vec<&TrafficArea> = boundaries
            .iter()
            .map(|boundary| TrafficArea::try_from(boundary).expect("a traffic area"))
            .collect();
        assert_eq!(
            ids!(areas),
            [
                "UUID_8625bf6f-57cb-3ddf-8fd1-6674b756a2e2",
                "UUID_dc110e80-dadc-3c87-b864-2854cc0cb39a",
            ]
        );
        let mut area_3d = Vec::new();
        for area in areas {
            let mut names = area.names();
            assert_eq!(first_name(|| names.next().map(|n| n.value())), "Lane");
            assert!(area.class().is_none());
            assert_eq!(values!(area.functions()), ["1"]);
            assert_eq!(values!(area.usages()), ["2"]);
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
            assert_eq!(items!(multi_surface.surface_member()).len(), 1);
            area_3d.push(
                multi_surface
                    .area_3d()
                    .unwrap_or_else(|_| panic!("should compute")),
            );
        }
        assert_close(area_3d[0], 160.79800993793438);
        assert_close(area_3d[1], 121.34249049694012);
    }

    #[test]
    fn road_shape_auxiliary_traffic() {
        let city_model = city_model();
        let section = section(road(&city_model));
        let mut boundaries = Vec::new();
        for space in objects!(section.auxiliary_traffic_spaces()) {
            assert_eq!(space.granularity(), GranularityValue::Lane);
            assert!(space.class().is_none());
            assert!(space.functions().next().is_none());
            assert!(space.usages().next().is_none());
            assert_eq!(space.space_type(), Some(SpaceType::Open));
            let solid = space
                .lod2_solid()
                .and_then(|property| property.object())
                .expect("should have an LoD2 solid");
            assert_close(
                solid
                    .volume_3d()
                    .unwrap_or_else(|_| panic!("should compute")),
                100.0,
            );
            let multi_curve = space
                .lod2_multi_curve()
                .and_then(|property| property.object())
                .expect("should have an LoD2 curve");
            assert_close(
                multi_curve
                    .length_3d()
                    .unwrap_or_else(|_| panic!("should compute")),
                40.0,
            );
            boundaries.push(only_boundary(space.boundaries()));
        }
        let areas: Vec<&AuxiliaryTrafficArea> = boundaries
            .iter()
            .map(|boundary| AuxiliaryTrafficArea::try_from(boundary).expect("an auxiliary area"))
            .collect();
        assert_eq!(
            ids!(areas),
            [
                "UUID_4890681a-e9fa-365e-a676-f89afb453f9b",
                "UUID_d3c71d48-5222-355e-8037-9677aee30d7e",
            ]
        );
        for area in areas {
            let mut names = area.names();
            assert_eq!(first_name(|| names.next().map(|n| n.value())), "Lane");
            assert!(area.class().is_none());
            assert!(area.functions().next().is_none());
            assert!(area.usages().next().is_none());
            assert!(area.surface_material().is_none());
            let multi_surface = area
                .lod2_multi_surface()
                .and_then(|property| property.object())
                .expect("should have an LoD2 multi surface");
            assert_close(
                multi_surface
                    .area_3d()
                    .unwrap_or_else(|_| panic!("should compute")),
                40.0,
            );
        }
    }
}

mod junction {
    use super::*;

    fn city_model() -> Box<CityModel> {
        read("asam-opendrive", "ASAM-Ex_Bidirectional_Junction.gml")
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
        assert_eq!(city_model.city_objects_len(), 1);
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
        assert_eq!(items!(city_model.iter_city_objects()).len(), 23);
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
        let sections = objects!(road.sections());
        assert_eq!(
            ids!(sections),
            [
                "UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29",
                "UUID_ef20f165-2564-373a-a5f8-98fd15f1ae69",
                "UUID_4799566b-daf4-3135-aa9d-ec1b34a9167d",
            ]
        );
        assert_eq!(
            sections
                .iter()
                .map(|s| items!(s.traffic_spaces()).len())
                .collect::<Vec<_>>(),
            [2, 1, 1]
        );
        assert_eq!(
            sections
                .iter()
                .map(|s| items!(s.markings()).len())
                .collect::<Vec<_>>(),
            [4, 0, 0]
        );
        assert!(
            sections
                .iter()
                .all(|s| s.auxiliary_traffic_spaces().next().is_none())
        );
        let intersections = objects!(road.intersections());
        let [intersection] = intersections[..] else {
            panic!("expected exactly one intersection");
        };
        assert_eq!(
            intersection.feature_id().as_str(),
            "UUID_47b7678d-e8b1-36ca-90b6-5b86cc859571"
        );
        assert!(intersection.class().is_none());
        assert_eq!(ids!(objects!(intersection.traffic_spaces())), SPACES[4..]);
    }

    #[test]
    fn junction_traffic_spaces() {
        let city_model = city_model();
        let features = features(&city_model);
        let spaces: Vec<&TrafficSpace> = features
            .iter()
            .filter_map(|feature| TrafficSpace::try_from(feature))
            .collect();
        assert_eq!(ids!(spaces), SPACES);
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
        let surfaces: Vec<(usize, f64)> = features(&city_model)
            .iter()
            .filter_map(|feature| TrafficArea::try_from(feature))
            .map(|area| {
                let multi_surface = area
                    .lod2_multi_surface()
                    .and_then(|property| property.object())
                    .expect("should have an LoD2 multi surface");
                (
                    items!(multi_surface.surface_member()).len(),
                    multi_surface
                        .area_3d()
                        .unwrap_or_else(|_| panic!("should compute")),
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
        let features = features(&city_model);
        let links: Vec<(Vec<String>, Vec<String>)> = features
            .iter()
            .filter_map(|feature| TrafficSpace::try_from(feature))
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
        let section = objects!(road(&city_model).sections())[0];
        let markings: Vec<&Marking> = objects!(section.markings());
        let mut areas = Vec::new();
        for marking in markings {
            let mut names = marking.names();
            assert_eq!(
                first_name(|| names.next().map(|n| n.value())),
                "RoadMarking"
            );
            assert!(marking.class().is_none());
            assert!(marking.lod0_multi_surface().is_none());
            assert!(marking.lod3_multi_surface().is_none());
            let multi_surface = marking
                .lod2_multi_surface()
                .and_then(|property| property.object())
                .expect("should have an LoD2 multi surface");
            assert_eq!(items!(multi_surface.surface_member()).len(), 1);
            areas.push(
                multi_surface
                    .area_3d()
                    .unwrap_or_else(|_| panic!("should compute")),
            );
        }
        assert_eq!(areas.len(), 4);
        for (actual, expected) in areas.iter().zip([0.48, 0.48, 0.48, 0.08962050155758661]) {
            assert_close(*actual, expected);
        }
    }
}
