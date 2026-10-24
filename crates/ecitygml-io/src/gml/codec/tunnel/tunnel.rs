use crate::Error;
use crate::gml::codec::tunnel::tunnel_part_property::{
    deserialize_tunnel_part_property, serialize_tunnel_part_property,
};
use crate::gml::codec::tunnel::{
    deserialize_abstract_tunnel, serialize_abstract_tunnel, serialize_abstract_tunnel_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::tunnel::{AsAbstractTunnel, Tunnel};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter, collect_children};

pub fn deserialize_tunnel(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Tunnel, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let mut abstract_tunnel_result = None;
    let mut tunnel_parts_result = None;

    rayon::scope(|s| {
        s.spawn(|_| {
            abstract_tunnel_result = Some(deserialize_abstract_tunnel(xml_document, index, config))
        });
        s.spawn(|_| {
            tunnel_parts_result = Some(collect_children(
                xml_document,
                index,
                CityGmlElement::TunnelPartProperty.into(),
                config,
                deserialize_tunnel_part_property,
            ));
        });
    });

    let mut tunnel = Tunnel::from_abstract_tunnel(
        abstract_tunnel_result.expect("rayon::scope guarantees all spawns complete")?,
    );
    tunnel.set_tunnel_parts(
        tunnel_parts_result.expect("rayon::scope guarantees all spawns complete")?,
    );

    Ok(tunnel)
}

pub fn serialize_tunnel(
    tunnel: &Tunnel,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_tunnel_attributes(tunnel);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Tunnel,
        CityGmlElement::Tunnel,
        attributes,
    )?;

    serialize_abstract_tunnel(tunnel.abstract_tunnel(), xml_fragment_writer)?;

    for prop in tunnel.tunnel_parts() {
        serialize_tunnel_part_property(prop, xml_fragment_writer)?;
    }

    xml_fragment_writer.write_end_event(CityGmlNamespace::Tunnel, CityGmlElement::Tunnel)?;

    Ok(())
}

pub fn serialize_tunnel_attributes(tunnel: &Tunnel) -> Vec<(String, String)> {
    serialize_abstract_tunnel_attributes(tunnel.abstract_tunnel())
}

#[cfg(test)]
mod tests {
    use super::*;

    use ecitygml_core::model::core::AsAbstractFeature;
    use egml::io::util::Formatting;
    use egml::model::base::Id;

    #[test]
    fn test_deserialize_basic_tunnel() {
        let xml_document = b"
    <tun:Tunnel gml:id=\"UUID_tunnel-1\">
      <gml:name>Test Tunnel</gml:name>
      <tun:class>1000</tun:class>
      <tun:function>1010</tun:function>
      <tun:usage>2000</tun:usage>
      <tun:tunnelPart>
        <tun:TunnelPart gml:id=\"UUID_tunnel-part-1\">
          <gml:name>Test Tunnel Part</gml:name>
        </tun:TunnelPart>
      </tun:tunnelPart>
    </tun:Tunnel>";

        let tunnel = deserialize_tunnel(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            tunnel.feature_id(),
            &Id::try_from("UUID_tunnel-1").expect("should work")
        );
        assert_eq!(
            tunnel.class().expect("should be set").code().value(),
            "1000"
        );
        assert_eq!(
            tunnel
                .functions()
                .first()
                .expect("should be set")
                .code()
                .value(),
            "1010"
        );
        assert_eq!(
            tunnel
                .usages()
                .first()
                .expect("should be set")
                .code()
                .value(),
            "2000"
        );

        assert_eq!(tunnel.tunnel_parts().len(), 1);
        let tunnel_part = tunnel.tunnel_parts()[0].object().expect("should be parsed");
        assert_eq!(
            tunnel_part.feature_id(),
            &Id::try_from("UUID_tunnel-part-1").expect("should work")
        );
    }

    #[test]
    fn test_round_trip_tunnel() {
        let xml_document = b"
    <tun:Tunnel gml:id=\"UUID_tunnel-1\">
      <gml:name>Test Tunnel</gml:name>
      <tun:class>1000</tun:class>
      <tun:function>1010</tun:function>
      <tun:usage>2000</tun:usage>
      <tun:tunnelPart>
        <tun:TunnelPart gml:id=\"UUID_tunnel-part-1\">
          <gml:name>Test Tunnel Part</gml:name>
        </tun:TunnelPart>
      </tun:tunnelPart>
    </tun:Tunnel>";

        let tunnel = deserialize_tunnel(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_tunnel(&tunnel, &mut xml_fragment_writer).expect("should serialize");
        let xml = {
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        };

        let round_tripped = deserialize_tunnel(
            &xml,
            &XmlDocumentIndex::from_scan(&xml, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should round trip");

        assert_eq!(tunnel.feature_id(), round_tripped.feature_id());
        assert_eq!(tunnel.class(), round_tripped.class());
        assert_eq!(tunnel.functions(), round_tripped.functions());
        assert_eq!(tunnel.usages(), round_tripped.usages());
        assert_eq!(
            tunnel.tunnel_parts().len(),
            round_tripped.tunnel_parts().len()
        );

        let round_tripped_part = round_tripped.tunnel_parts()[0]
            .object()
            .expect("should be parsed");
        assert_eq!(
            round_tripped_part.feature_id(),
            &Id::try_from("UUID_tunnel-part-1").expect("should work")
        );
    }

    #[test]
    fn test_round_trip_tunnel_installation() {
        let xml_document = b"
    <tun:Tunnel gml:id=\"UUID_tunnel-1\">
      <tun:tunnelInstallation>
        <tun:TunnelInstallation gml:id=\"UUID_tunnel-installation-1\">
          <tun:class>3000</tun:class>
          <tun:function>3010</tun:function>
          <tun:usage>4000</tun:usage>
        </tun:TunnelInstallation>
      </tun:tunnelInstallation>
    </tun:Tunnel>";

        let tunnel = deserialize_tunnel(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(tunnel.tunnel_installations().len(), 1);
        let installation = tunnel.tunnel_installations()[0]
            .object()
            .expect("should be parsed");
        assert_eq!(
            installation.feature_id(),
            &Id::try_from("UUID_tunnel-installation-1").expect("should work")
        );
        assert_eq!(
            installation.class().expect("should be set").code().value(),
            "3000"
        );
        assert_eq!(
            installation
                .functions()
                .first()
                .expect("should be set")
                .code()
                .value(),
            "3010"
        );
        assert_eq!(
            installation
                .usages()
                .first()
                .expect("should be set")
                .code()
                .value(),
            "4000"
        );

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_tunnel(&tunnel, &mut xml_fragment_writer).expect("should serialize");
        let xml = {
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        };

        let round_tripped = deserialize_tunnel(
            &xml,
            &XmlDocumentIndex::from_scan(&xml, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should round trip");
        assert_eq!(
            tunnel.tunnel_installations().len(),
            round_tripped.tunnel_installations().len()
        );
        let round_tripped_installation = round_tripped.tunnel_installations()[0]
            .object()
            .expect("should be parsed");
        assert_eq!(round_tripped_installation.class(), installation.class());
    }

    #[test]
    fn test_round_trip_tunnel_constructive_element() {
        let xml_document = b"
    <tun:Tunnel gml:id=\"UUID_tunnel-1\">
      <tun:tunnelConstructiveElement>
        <tun:TunnelConstructiveElement gml:id=\"UUID_tunnel-constructive-element-1\">
          <tun:class>5000</tun:class>
          <tun:function>5010</tun:function>
          <tun:usage>6000</tun:usage>
        </tun:TunnelConstructiveElement>
      </tun:tunnelConstructiveElement>
    </tun:Tunnel>";

        let tunnel = deserialize_tunnel(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(tunnel.tunnel_constructive_elements().len(), 1);
        let element = tunnel.tunnel_constructive_elements()[0]
            .object()
            .expect("should be parsed");
        assert_eq!(
            element.feature_id(),
            &Id::try_from("UUID_tunnel-constructive-element-1").expect("should work")
        );
        assert_eq!(
            element.class().expect("should be set").code().value(),
            "5000"
        );
        assert_eq!(
            element
                .functions()
                .first()
                .expect("should be set")
                .code()
                .value(),
            "5010"
        );
        assert_eq!(
            element
                .usages()
                .first()
                .expect("should be set")
                .code()
                .value(),
            "6000"
        );

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_tunnel(&tunnel, &mut xml_fragment_writer).expect("should serialize");
        let xml = {
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        };

        let round_tripped = deserialize_tunnel(
            &xml,
            &XmlDocumentIndex::from_scan(&xml, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should round trip");
        assert_eq!(
            tunnel.tunnel_constructive_elements().len(),
            round_tripped.tunnel_constructive_elements().len()
        );
        let round_tripped_element = round_tripped.tunnel_constructive_elements()[0]
            .object()
            .expect("should be parsed");
        assert_eq!(round_tripped_element.class(), element.class());
    }

    #[test]
    fn test_round_trip_tunnel_hollow_space() {
        let xml_document = b"
    <tun:Tunnel gml:id=\"UUID_tunnel-1\">
      <tun:class>1000</tun:class>
      <tun:hollowSpace>
        <tun:HollowSpace gml:id=\"UUID_hollow-space-1\">
          <tun:class>5000</tun:class>
          <tun:function>5010</tun:function>
          <tun:usage>6000</tun:usage>
        </tun:HollowSpace>
      </tun:hollowSpace>
    </tun:Tunnel>";

        let tunnel = deserialize_tunnel(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            tunnel.class().expect("should be set").code().value(),
            "1000"
        );
        assert_eq!(tunnel.hollow_spaces().len(), 1);
        let hollow_space = tunnel.hollow_spaces()[0]
            .object()
            .expect("should be parsed");
        assert_eq!(
            hollow_space.feature_id(),
            &Id::try_from("UUID_hollow-space-1").expect("should work")
        );
        assert_eq!(
            hollow_space.class().expect("should be set").code().value(),
            "5000"
        );
        assert_eq!(hollow_space.functions().len(), 1);
        assert_eq!(hollow_space.usages().len(), 1);

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_tunnel(&tunnel, &mut xml_fragment_writer).expect("should serialize");
        let xml = {
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        };

        let round_tripped = deserialize_tunnel(
            &xml,
            &XmlDocumentIndex::from_scan(&xml, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should round trip");

        assert_eq!(round_tripped.hollow_spaces(), tunnel.hollow_spaces());
    }

    #[test]
    fn test_round_trip_tunnel_furniture_on_tunnel_and_in_hollow_space() {
        let xml_document = b"
    <tun:Tunnel gml:id=\"UUID_tunnel-1\">
      <tun:hollowSpace>
        <tun:HollowSpace gml:id=\"UUID_hollow-space-1\">
          <tun:class>5000</tun:class>
          <tun:tunnelFurniture>
            <tun:TunnelFurniture gml:id=\"UUID_hollow-space-furniture-1\">
              <tun:class>7000</tun:class>
            </tun:TunnelFurniture>
          </tun:tunnelFurniture>
        </tun:HollowSpace>
      </tun:hollowSpace>
      <tun:tunnelFurniture>
        <tun:TunnelFurniture gml:id=\"UUID_tunnel-furniture-1\">
          <tun:class>7100</tun:class>
          <tun:function>7110</tun:function>
          <tun:usage>7200</tun:usage>
        </tun:TunnelFurniture>
      </tun:tunnelFurniture>
    </tun:Tunnel>";

        let tunnel = deserialize_tunnel(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(tunnel.tunnel_furniture().len(), 1);
        let tunnel_furniture = tunnel.tunnel_furniture()[0]
            .object()
            .expect("should be parsed");
        assert_eq!(
            tunnel_furniture.feature_id(),
            &Id::try_from("UUID_tunnel-furniture-1").expect("should work")
        );
        assert_eq!(
            tunnel_furniture
                .class()
                .expect("should be set")
                .code()
                .value(),
            "7100"
        );
        assert_eq!(tunnel_furniture.functions().len(), 1);
        assert_eq!(tunnel_furniture.usages().len(), 1);

        let hollow_space = tunnel.hollow_spaces()[0]
            .object()
            .expect("should be parsed");
        assert_eq!(hollow_space.tunnel_furniture().len(), 1);
        let hollow_space_furniture = hollow_space.tunnel_furniture()[0]
            .object()
            .expect("should be parsed");
        assert_eq!(
            hollow_space_furniture.feature_id(),
            &Id::try_from("UUID_hollow-space-furniture-1").expect("should work")
        );

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_tunnel(&tunnel, &mut xml_fragment_writer).expect("should serialize");
        let xml = {
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        };

        let round_tripped = deserialize_tunnel(
            &xml,
            &XmlDocumentIndex::from_scan(&xml, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should round trip");

        assert_eq!(round_tripped.tunnel_furniture(), tunnel.tunnel_furniture());
        assert_eq!(round_tripped.hollow_spaces(), tunnel.hollow_spaces());
    }
}
