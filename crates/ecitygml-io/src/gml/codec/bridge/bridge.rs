use crate::Error;
use crate::gml::codec::bridge::bridge_part_property::{
    deserialize_bridge_part_property, serialize_bridge_part_property,
};
use crate::gml::codec::bridge::{
    deserialize_abstract_bridge, serialize_abstract_bridge, serialize_abstract_bridge_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::bridge::{AsAbstractBridge, Bridge};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter, collect_children};

pub fn deserialize_bridge(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Bridge, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let mut abstract_bridge_result = None;
    let mut bridge_parts_result = None;

    rayon::scope(|s| {
        s.spawn(|_| {
            abstract_bridge_result = Some(deserialize_abstract_bridge(xml_document, index, config))
        });
        s.spawn(|_| {
            bridge_parts_result = Some(collect_children(
                xml_document,
                index,
                CityGmlElement::BridgePartProperty.into(),
                config,
                deserialize_bridge_part_property,
            ));
        });
    });

    let mut bridge = Bridge::from_abstract_bridge(
        abstract_bridge_result.expect("rayon::scope guarantees all spawns complete")?,
    );
    bridge.set_bridge_parts(
        bridge_parts_result.expect("rayon::scope guarantees all spawns complete")?,
    );

    Ok(bridge)
}

pub fn serialize_bridge(
    bridge: &Bridge,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_bridge_attributes(bridge);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Bridge,
        CityGmlElement::Bridge,
        attributes,
    )?;

    serialize_abstract_bridge(bridge.abstract_bridge(), xml_fragment_writer)?;

    for prop in bridge.bridge_parts() {
        serialize_bridge_part_property(prop, xml_fragment_writer)?;
    }

    xml_fragment_writer.write_end_event(CityGmlNamespace::Bridge, CityGmlElement::Bridge)?;
    Ok(())
}

pub fn serialize_bridge_attributes(bridge: &Bridge) -> Vec<(String, String)> {
    serialize_abstract_bridge_attributes(bridge.abstract_bridge())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::bridge::AsAbstractBridge;

    use ecitygml_core::model::core::AsAbstractFeature;
    use egml::io::util::Formatting;
    use egml::model::base::Id;

    #[test]
    fn test_deserialize_basic_bridge() {
        let xml_document = b"
    <brid:Bridge gml:id=\"UUID_bridge-1\">
      <gml:name>Test Bridge</gml:name>
      <brid:class>1000</brid:class>
      <brid:function>1010</brid:function>
      <brid:usage>2000</brid:usage>
      <brid:isMovable>true</brid:isMovable>
      <brid:bridgePart>
        <brid:BridgePart gml:id=\"UUID_bridge-part-1\">
          <gml:name>Test Bridge Part</gml:name>
          <brid:isMovable>false</brid:isMovable>
        </brid:BridgePart>
      </brid:bridgePart>
    </brid:Bridge>";

        let bridge = deserialize_bridge(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            bridge.feature_id(),
            &Id::try_from("UUID_bridge-1").expect("should work")
        );
        assert_eq!(
            bridge.class().expect("should be set").code().value(),
            "1000"
        );
        assert_eq!(
            bridge
                .functions()
                .first()
                .expect("should be set")
                .code()
                .value(),
            "1010"
        );
        assert_eq!(
            bridge
                .usages()
                .first()
                .expect("should be set")
                .code()
                .value(),
            "2000"
        );
        assert_eq!(bridge.is_movable(), Some(true));

        assert_eq!(bridge.bridge_parts().len(), 1);
        let bridge_part = bridge.bridge_parts()[0].object().expect("should be parsed");
        assert_eq!(
            bridge_part.feature_id(),
            &Id::try_from("UUID_bridge-part-1").expect("should work")
        );
        assert_eq!(bridge_part.is_movable(), Some(false));
    }

    #[test]
    fn test_round_trip_bridge() {
        let xml_document = b"
    <brid:Bridge gml:id=\"UUID_bridge-1\">
      <gml:name>Test Bridge</gml:name>
      <brid:class>1000</brid:class>
      <brid:function>1010</brid:function>
      <brid:usage>2000</brid:usage>
      <brid:isMovable>true</brid:isMovable>
      <brid:bridgePart>
        <brid:BridgePart gml:id=\"UUID_bridge-part-1\">
          <gml:name>Test Bridge Part</gml:name>
          <brid:isMovable>false</brid:isMovable>
        </brid:BridgePart>
      </brid:bridgePart>
    </brid:Bridge>";

        let bridge = deserialize_bridge(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_bridge(&bridge, &mut xml_fragment_writer).expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        let round_tripped = deserialize_bridge(
            xml.as_bytes(),
            &XmlDocumentIndex::from_scan(xml.as_bytes(), None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should round trip");

        assert_eq!(bridge.feature_id(), round_tripped.feature_id());
        assert_eq!(bridge.class(), round_tripped.class());
        assert_eq!(bridge.functions(), round_tripped.functions());
        assert_eq!(bridge.usages(), round_tripped.usages());
        assert_eq!(bridge.is_movable(), round_tripped.is_movable());
        assert_eq!(
            bridge.bridge_parts().len(),
            round_tripped.bridge_parts().len()
        );

        let round_tripped_part = round_tripped.bridge_parts()[0]
            .object()
            .expect("should be parsed");
        assert_eq!(round_tripped_part.is_movable(), Some(false));
    }

    #[test]
    fn test_round_trip_bridge_installation() {
        let xml_document = b"
    <brid:Bridge gml:id=\"UUID_bridge-1\">
      <brid:bridgeInstallation>
        <brid:BridgeInstallation gml:id=\"UUID_bridge-installation-1\">
          <brid:class>3000</brid:class>
          <brid:function>3010</brid:function>
          <brid:usage>4000</brid:usage>
        </brid:BridgeInstallation>
      </brid:bridgeInstallation>
    </brid:Bridge>";

        let bridge = deserialize_bridge(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(bridge.bridge_installations().len(), 1);
        let installation = bridge.bridge_installations()[0]
            .object()
            .expect("should be parsed");
        assert_eq!(
            installation.feature_id(),
            &Id::try_from("UUID_bridge-installation-1").expect("should work")
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
        serialize_bridge(&bridge, &mut xml_fragment_writer).expect("should work");
        let xml = {
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        };

        let round_tripped = deserialize_bridge(
            &xml,
            &XmlDocumentIndex::from_scan(&xml, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should round trip");
        assert_eq!(
            bridge.bridge_installations().len(),
            round_tripped.bridge_installations().len()
        );
        let round_tripped_installation = round_tripped.bridge_installations()[0]
            .object()
            .expect("should be parsed");
        assert_eq!(round_tripped_installation.class(), installation.class());
    }

    #[test]
    fn test_round_trip_bridge_constructive_element() {
        let xml_document = b"
    <brid:Bridge gml:id=\"UUID_bridge-1\">
      <brid:bridgeConstructiveElement>
        <brid:BridgeConstructiveElement gml:id=\"UUID_bridge-constructive-element-1\">
          <brid:class>5000</brid:class>
          <brid:function>5010</brid:function>
          <brid:usage>6000</brid:usage>
        </brid:BridgeConstructiveElement>
      </brid:bridgeConstructiveElement>
    </brid:Bridge>";

        let bridge = deserialize_bridge(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(bridge.bridge_constructive_elements().len(), 1);
        let element = bridge.bridge_constructive_elements()[0]
            .object()
            .expect("should be parsed");
        assert_eq!(
            element.feature_id(),
            &Id::try_from("UUID_bridge-constructive-element-1").expect("should work")
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
        serialize_bridge(&bridge, &mut xml_fragment_writer).expect("should serialize");
        let xml = {
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        };

        let round_tripped = deserialize_bridge(
            &xml,
            &XmlDocumentIndex::from_scan(&xml, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should round trip");
        assert_eq!(
            bridge.bridge_constructive_elements().len(),
            round_tripped.bridge_constructive_elements().len()
        );
        let round_tripped_element = round_tripped.bridge_constructive_elements()[0]
            .object()
            .expect("should be parsed");
        assert_eq!(round_tripped_element.class(), element.class());
    }

    #[test]
    fn test_round_trip_bridge_room() {
        let xml_document = b"
    <brid:Bridge gml:id=\"UUID_bridge-1\">
      <brid:class>1000</brid:class>
      <brid:bridgeRoom>
        <brid:BridgeRoom gml:id=\"UUID_bridge-room-1\">
          <brid:class>5000</brid:class>
          <brid:function>5010</brid:function>
          <brid:usage>6000</brid:usage>
        </brid:BridgeRoom>
      </brid:bridgeRoom>
    </brid:Bridge>";

        let bridge = deserialize_bridge(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            bridge.class().expect("should be set").code().value(),
            "1000"
        );
        assert_eq!(bridge.bridge_rooms().len(), 1);
        let bridge_room = bridge.bridge_rooms()[0].object().expect("should be parsed");
        assert_eq!(
            bridge_room.feature_id(),
            &Id::try_from("UUID_bridge-room-1").expect("should work")
        );
        assert_eq!(
            bridge_room.class().expect("should be set").code().value(),
            "5000"
        );
        assert_eq!(bridge_room.functions().len(), 1);
        assert_eq!(bridge_room.usages().len(), 1);

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_bridge(&bridge, &mut xml_fragment_writer).expect("should serialize");
        let xml = {
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        };

        let round_tripped = deserialize_bridge(
            &xml,
            &XmlDocumentIndex::from_scan(&xml, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should round trip");

        assert_eq!(round_tripped.bridge_rooms(), bridge.bridge_rooms());
    }

    #[test]
    fn test_round_trip_bridge_furniture_on_bridge_and_in_room() {
        let xml_document = b"
    <brid:Bridge gml:id=\"UUID_bridge-1\">
      <brid:bridgeRoom>
        <brid:BridgeRoom gml:id=\"UUID_bridge-room-1\">
          <brid:class>5000</brid:class>
          <brid:bridgeFurniture>
            <brid:BridgeFurniture gml:id=\"UUID_room-furniture-1\">
              <brid:class>7000</brid:class>
            </brid:BridgeFurniture>
          </brid:bridgeFurniture>
        </brid:BridgeRoom>
      </brid:bridgeRoom>
      <brid:bridgeFurniture>
        <brid:BridgeFurniture gml:id=\"UUID_bridge-furniture-1\">
          <brid:class>7100</brid:class>
          <brid:function>7110</brid:function>
          <brid:usage>7200</brid:usage>
        </brid:BridgeFurniture>
      </brid:bridgeFurniture>
    </brid:Bridge>";

        let bridge = deserialize_bridge(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(bridge.bridge_furniture().len(), 1);
        let bridge_furniture = bridge.bridge_furniture()[0]
            .object()
            .expect("should be parsed");
        assert_eq!(
            bridge_furniture.feature_id(),
            &Id::try_from("UUID_bridge-furniture-1").expect("should work")
        );
        assert_eq!(
            bridge_furniture
                .class()
                .expect("should be set")
                .code()
                .value(),
            "7100"
        );
        assert_eq!(bridge_furniture.functions().len(), 1);
        assert_eq!(bridge_furniture.usages().len(), 1);

        let bridge_room = bridge.bridge_rooms()[0].object().expect("should be parsed");
        assert_eq!(
            bridge_room.class().expect("should be set").code().value(),
            "5000"
        );
        assert_eq!(bridge_room.bridge_furniture().len(), 1);
        let room_furniture = bridge_room.bridge_furniture()[0]
            .object()
            .expect("should be parsed");
        assert_eq!(
            room_furniture.feature_id(),
            &Id::try_from("UUID_room-furniture-1").expect("should work")
        );

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_bridge(&bridge, &mut xml_fragment_writer).expect("should serialize");
        let xml = {
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        };

        let round_tripped = deserialize_bridge(
            &xml,
            &XmlDocumentIndex::from_scan(&xml, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should round trip");

        assert_eq!(round_tripped.bridge_furniture(), bridge.bridge_furniture());
        assert_eq!(round_tripped.bridge_rooms(), bridge.bridge_rooms());
    }
}
