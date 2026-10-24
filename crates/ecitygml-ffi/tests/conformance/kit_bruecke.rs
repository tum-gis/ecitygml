//! The cases of `crates/ecitygml/tests/conformance/kit-bruecke.md`.

use crate::{assert_close, read};
use ecitygml_ffi::citygml::core::model::bridge::bridge::Bridge;
use ecitygml_ffi::citygml::core::model::common::feature_type::FeatureType;
use ecitygml_ffi::citygml::core::model::core::city_model::CityModel;
use ecitygml_ffi::citygml::core::model::core::refs::abstract_feature_kind_ref::AbstractFeatureKindRef;
use ecitygml_ffi::citygml::io::format::CitygmlFormat;
use ecitygml_ffi::citygml::io::gml::read::GmlReader;
use ecitygml_ffi::citygml::io::gml::write::GmlWriter;
use ecitygml_ffi::gml::core::model::geometry::direct_position::DirectPosition;
use ecitygml_ffi::gml::core::model::geometry::envelope::Envelope;

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
    read("kit-bruecke", "Modellbahnbruecke-LoD2-V03__v3.gml")
}

fn features(city_model: &CityModel) -> Vec<Box<AbstractFeatureKindRef<'_>>> {
    items!(city_model.iter_features())
}

fn bridge(city_model: &CityModel) -> &Bridge {
    features(city_model)
        .iter()
        .find_map(|feature| Bridge::try_from(feature))
        .expect("should have a bridge")
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
    assert_eq!(city_model.city_objects_len(), 1);
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
    assert_eq!(items!(city_model.iter_city_objects()).len(), 14);
}

#[test]
fn bridge_attributes() {
    let city_model = city_model();
    let bridge = bridge(&city_model);
    assert_eq!(
        bridge.feature_id().as_str(),
        "_Modellbahnbruecke-LoD2-V03_BD.rx3tFkxPQkL5qDXML1W7"
    );
    assert!(bridge.names().next().is_none());
    assert!(bridge.class().is_none());
    assert!(bridge.functions().next().is_none());
    assert!(bridge.usages().next().is_none());
    assert!(bridge.bridge_parts().next().is_none());
    assert!(bridge.boundaries().next().is_none());
    assert!(bridge.date_of_construction().is_none());
    assert!(bridge.creation_date().is_none());
    assert!(bridge.heights().next().is_none());
    assert!(bridge.occupancies().next().is_none());
    assert!(bridge.generic_attributes().next().is_none());
    assert!(bridge.external_references().next().is_none());
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
    assert_eq!(items!(multi_surface.surface_member()).len(), 18);
    assert_close(
        multi_surface.area_3d().expect("should compute"),
        795.4201811265907,
    );
    let triangulation = multi_surface.triangulate().expect("should triangulate");
    assert_eq!(items!(triangulation.surface().triangles()).len(), 60);
    assert!(!triangulation.has_skipped());
    assert!(bridge.lod1_solid().is_none());
    assert!(bridge.lod2_solid().is_none());
    assert!(bridge.lod3_multi_surface().is_none());
}

#[test]
fn bridge_round_trip() {
    let city_model = city_model();
    let mut writer = GmlWriter::new(CitygmlFormat::Gml);
    writer
        .finish(&city_model)
        .unwrap_or_else(|_| panic!("should write"));
    let written = GmlReader::new(writer.data(), CitygmlFormat::Gml)
        .finish()
        .unwrap_or_else(|_| panic!("should read"));
    assert_eq!(feature_types(&written), feature_types(&city_model));
    assert_eq!(
        bridge(&written).feature_id().as_str(),
        "_Modellbahnbruecke-LoD2-V03_BD.rx3tFkxPQkL5qDXML1W7"
    );
}
