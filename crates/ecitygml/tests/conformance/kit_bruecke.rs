//! The cases of `crates/ecitygml/tests/conformance/kit-bruecke.md`.

use crate::{assert_close, read};
use ecitygml::io::{CitygmlFormat, GmlReader, GmlWriter};
use ecitygml::model::bridge::{AsAbstractBridge, Bridge};
use ecitygml::model::common::{FeatureType, HasFeatureType, IterFeatures};
use ecitygml::model::construction::AsAbstractConstruction;
use ecitygml::model::core::{
    AsAbstractCityObject, AsAbstractFeature, AsAbstractFeatureWithLifespan, AsAbstractSpace,
    CityModel,
};
use egml::model::base::{AsAbstractGml, HasAssociationAttributes};
use egml::model::common::Triangulate;
use egml::model::feature::AsAbstractFeature as _;
use egml::model::geometry::{DirectPosition, Envelope};

fn city_model() -> CityModel {
    read("kit-bruecke", "Modellbahnbruecke-LoD2-V03__v3.gml")
}

fn bridge(city_model: &CityModel) -> &Bridge {
    city_model
        .iter_features()
        .find_map(|feature| feature.try_into().ok())
        .expect("should have a bridge")
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

fn assert_envelope(envelope: &Envelope, lower: (f64, f64, f64), upper: (f64, f64, f64)) {
    assert_point_close(envelope.lower_corner(), lower);
    assert_point_close(envelope.upper_corner(), upper);
}

#[test]
fn bridge_city_model() {
    use FeatureType::{
        Appearance, Bridge, BridgeConstructiveElement, BridgeInstallation, CityModel,
        ParameterizedTexture,
    };
    let city_model = city_model();
    assert_eq!(city_model.city_object_members_len(), 1);
    assert_envelope(
        city_model
            .bounded_by()
            .and_then(|shape| shape.envelope())
            .expect("should have an envelope"),
        (457644.585, 5439126.455, 109.0),
        (457708.084, 5439157.169, 124.3),
    );
    let expected = [
        vec![CityModel, Bridge, Appearance],
        vec![ParameterizedTexture; 3],
        vec![BridgeInstallation; 2],
        vec![BridgeConstructiveElement; 11],
    ]
    .concat();
    assert_eq!(feature_types(&city_model), expected);
    assert_eq!(city_model.iter_city_objects().count(), 14);
}

#[test]
fn bridge_attributes() {
    let city_model = city_model();
    let bridge = bridge(&city_model);
    assert_eq!(
        bridge.feature_id().to_string(),
        "_Modellbahnbruecke-LoD2-V03_BD.rx3tFkxPQkL5qDXML1W7"
    );
    assert!(bridge.names().is_empty());
    assert!(bridge.class().is_none());
    assert!(bridge.functions().is_empty());
    assert!(bridge.usages().is_empty());
    assert!(bridge.bridge_parts().is_empty());
    assert!(bridge.boundaries().is_empty());
    assert!(bridge.date_of_construction().is_none());
    assert!(bridge.creation_date().is_none());
    assert!(bridge.heights().is_empty());
    assert!(bridge.occupancies().is_empty());
    assert!(bridge.generic_attributes().is_empty());
    assert!(bridge.external_references().is_empty());
}

#[test]
fn bridge_geometry() {
    let city_model = city_model();
    let bridge = bridge(&city_model);
    assert_envelope(
        bridge
            .bounded_by()
            .and_then(|shape| shape.envelope())
            .expect("should have an envelope"),
        (457645.136, 5439126.692, 115.3),
        (457707.533, 5439156.931, 116.2),
    );
    let property = bridge
        .lod2_multi_surface()
        .expect("should have an LoD2 multi surface");
    assert!(property.href().is_none());
    let multi_surface = property.object().expect("should be inline");
    assert_eq!(multi_surface.surface_member().len(), 18);
    assert_close(
        multi_surface.area_3d().expect("should compute"),
        795.4201811265907,
    );
    let triangulation = multi_surface.triangulate().expect("should triangulate");
    assert_eq!(triangulation.surface().triangles().len(), 60);
    assert!(!triangulation.has_skipped());
    assert!(bridge.lod1_solid().is_none());
    assert!(bridge.lod2_solid().is_none());
    assert!(bridge.lod3_multi_surface().is_none());
}

fn assert_bridge_parts(bridge: &Bridge) {
    assert_eq!(bridge.bridge_constructive_elements().len(), 11);
    assert_eq!(bridge.bridge_installations().len(), 2);
    assert_eq!(bridge.appearances().len(), 1);
}

#[test]
fn bridge_parts() {
    let city_model = city_model();
    assert_bridge_parts(bridge(&city_model));
    let mut data = Vec::new();
    GmlWriter::new(&mut data, CitygmlFormat::Gml)
        .finish(&city_model)
        .expect("should write");
    let written = GmlReader::new(data.as_slice(), CitygmlFormat::Gml)
        .finish()
        .expect("should read");
    assert_bridge_parts(bridge(&written));
}

#[test]
fn bridge_round_trip() {
    let city_model = city_model();
    let mut data = Vec::new();
    GmlWriter::new(&mut data, CitygmlFormat::Gml)
        .finish(&city_model)
        .expect("should write");
    let written = GmlReader::new(data.as_slice(), CitygmlFormat::Gml)
        .finish()
        .expect("should read");
    assert_eq!(feature_types(&written), feature_types(&city_model));
    assert_eq!(
        bridge(&written).feature_id().to_string(),
        "_Modellbahnbruecke-LoD2-V03_BD.rx3tFkxPQkL5qDXML1W7"
    );
}
