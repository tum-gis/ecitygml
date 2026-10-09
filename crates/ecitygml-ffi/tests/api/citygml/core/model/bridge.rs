//! `Bridge`, `BridgePart` and `Tunnel`, `TunnelPart` (AbstractBridge and AbstractTunnel getters).

use crate::*;

use ecitygml_ffi::citygml::core::model::bridge::bridge::Bridge;
use ecitygml_ffi::citygml::core::model::bridge::bridge_part::BridgePart;
use ecitygml_ffi::citygml::core::model::common::feature_type::FeatureType;
use ecitygml_ffi::citygml::core::model::tunnel::tunnel::Tunnel;
use ecitygml_ffi::citygml::core::model::tunnel::tunnel_part::TunnelPart;
use ecitygml_ffi::citygml::io::format::CitygmlFormat;
use ecitygml_ffi::citygml::io::gml::write::GmlWriter;

// No fixture contains a bridge or tunnel: the FZK LoD2 file header (namespaces, envelope) is
// reused with a single member, its properties in the order of the CityGML 3.0 schema.
const BRIDGE_MEMBER: &str = r#"<cityObjectMember>
    <brid:Bridge gml:id="bridge_1">
      <con:dateOfConstruction>1990-05-01</con:dateOfConstruction>
      <brid:class codeSpace="https://example.org/bridge_class">1000</brid:class>
      <brid:function>1010</brid:function>
      <brid:function>1020</brid:function>
      <brid:usage>1000</brid:usage>
      <brid:isMovable>true</brid:isMovable>
      <brid:bridgePart>
        <brid:BridgePart gml:id="bridge_part_1">
          <brid:isMovable>false</brid:isMovable>
        </brid:BridgePart>
      </brid:bridgePart>
    </brid:Bridge>
  </cityObjectMember>
</CityModel>
"#;

const TUNNEL_MEMBER: &str = r#"<cityObjectMember>
    <tun:Tunnel gml:id="tunnel_1">
      <con:dateOfConstruction>1990-05-01</con:dateOfConstruction>
      <tun:class codeSpace="https://example.org/tunnel_class">1000</tun:class>
      <tun:function>1010</tun:function>
      <tun:function>1020</tun:function>
      <tun:usage>1000</tun:usage>
      <tun:tunnelPart>
        <tun:TunnelPart gml:id="tunnel_part_1">
          <tun:function>1030</tun:function>
        </tun:TunnelPart>
      </tun:tunnelPart>
    </tun:Tunnel>
  </cityObjectMember>
</CityModel>
"#;

fn round_trip(model: &CityModel) -> Box<CityModel> {
    let mut writer = GmlWriter::new(CitygmlFormat::Gml);
    writer.finish(model).unwrap();
    GmlReader::new(writer.data(), CitygmlFormat::Gml)
        .finish()
        .unwrap()
}

fn feature_types(model: &CityModel) -> Vec<FeatureType> {
    let mut features = model.iter_features();
    std::iter::from_fn(|| features.next())
        .map(|f| f.feature_type())
        .collect()
}

fn first_bridge(model: &CityModel) -> &Bridge {
    let mut features = model.iter_features();
    std::iter::from_fn(|| features.next())
        .find_map(|f| Bridge::try_from(&f))
        .unwrap()
}

fn first_tunnel(model: &CityModel) -> &Tunnel {
    let mut features = model.iter_features();
    std::iter::from_fn(|| features.next())
        .find_map(|f| Tunnel::try_from(&f))
        .unwrap()
}

fn assert_bridge(bridge: &Bridge) {
    // AbstractBridge
    let class = bridge.class().unwrap().code();
    assert_eq!(class.value(), "1000");
    assert_eq!(class.code_space(), Some("https://example.org/bridge_class"));
    let mut functions = bridge.functions();
    let functions: Vec<_> = std::iter::from_fn(|| functions.next())
        .map(|f| (f.value(), f.code().code_space()))
        .collect();
    assert_eq!(functions, [("1010", None), ("1020", None)]);
    assert_eq!(bridge.usages().next().unwrap().value(), "1000");
    assert_eq!(bridge.is_movable(), Some(true));
    // AbstractConstruction, AbstractFeature
    let date = bridge.date_of_construction().unwrap();
    assert_eq!((date.year(), date.month(), date.day()), (1990, 5, 1));
    assert!(bridge.heights().next().is_none());
    assert_eq!(bridge.feature_id().as_str(), "bridge_1");
    // Bridge
    let mut parts = bridge.bridge_parts();
    let part = parts.next().unwrap().object().unwrap();
    assert!(parts.next().is_none());
    assert_eq!(part.feature_id().as_str(), "bridge_part_1");
    assert_eq!(part.is_movable(), Some(false));
    assert!(part.class().is_none());
    assert!(part.functions().next().is_none());
}

#[test]
fn bridge_and_part() {
    let model = read_member(BRIDGE_MEMBER);
    assert_eq!(
        feature_types(&model)[1..],
        [FeatureType::Bridge, FeatureType::BridgePart]
    );
    assert_eq!(model.city_objects_len(), 1);
    let mut features = model.iter_features();
    let features: Vec<_> = std::iter::from_fn(|| features.next()).collect();
    assert_eq!(
        features
            .iter()
            .filter(|f| Bridge::try_from(f).is_some())
            .count(),
        1
    );
    let part = features
        .iter()
        .find_map(|f| BridgePart::try_from(f))
        .unwrap();
    assert_eq!(part.feature_id().as_str(), "bridge_part_1");
    assert!(Bridge::try_from(&features[2]).is_none());

    assert_bridge(first_bridge(&model));
    assert_bridge(first_bridge(&round_trip(&model)));
}

fn assert_tunnel(tunnel: &Tunnel) {
    let class = tunnel.class().unwrap().code();
    assert_eq!(
        (class.value(), class.code_space()),
        ("1000", Some("https://example.org/tunnel_class"))
    );
    let mut functions = tunnel.functions();
    let functions: Vec<_> = std::iter::from_fn(|| functions.next())
        .map(|f| f.value())
        .collect();
    assert_eq!(functions, ["1010", "1020"]);
    assert_eq!(tunnel.usages().next().unwrap().value(), "1000");
    let date = tunnel.date_of_construction().unwrap();
    assert_eq!((date.year(), date.month(), date.day()), (1990, 5, 1));
    assert_eq!(tunnel.feature_id().as_str(), "tunnel_1");

    let mut parts = tunnel.tunnel_parts();
    let part = parts.next().unwrap().object().unwrap();
    assert!(parts.next().is_none());
    assert_eq!(part.feature_id().as_str(), "tunnel_part_1");
    assert_eq!(part.functions().next().unwrap().value(), "1030");
    assert!(part.class().is_none());
}

#[test]
fn tunnel_and_part() {
    let model = read_member(TUNNEL_MEMBER);
    assert_eq!(
        feature_types(&model)[1..],
        [FeatureType::Tunnel, FeatureType::TunnelPart]
    );
    let mut features = model.iter_features();
    let features: Vec<_> = std::iter::from_fn(|| features.next()).collect();
    assert_eq!(
        features
            .iter()
            .filter_map(|f| TunnelPart::try_from(f))
            .count(),
        1
    );
    assert!(Tunnel::try_from(&features[2]).is_none());

    assert_tunnel(first_tunnel(&model));
    assert_tunnel(first_tunnel(&round_trip(&model)));
}
