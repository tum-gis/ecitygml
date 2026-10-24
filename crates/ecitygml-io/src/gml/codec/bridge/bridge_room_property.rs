use crate::Error;
use crate::gml::codec::bridge::{deserialize_bridge_room, serialize_bridge_room};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::bridge::BridgeRoomProperty;
use egml::io::codec::base::{
    deserialize_association_and_ownership_attributes,
    serialize_association_and_ownership_attributes,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::base::{HasAssociationAttributes, HasOwnershipAttributes};

pub fn deserialize_bridge_room_property(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<BridgeRoomProperty, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let (association, ownership) = deserialize_association_and_ownership_attributes(xml_document)?;
    let mut object = None;

    if let Some(index) = index.first(CityGmlElement::BridgeRoom.into()) {
        object = Some(deserialize_bridge_room(
            &xml_document[index.range()],
            index,
            config,
        )?);
    }

    Ok(BridgeRoomProperty::new(object, association, ownership))
}

pub fn serialize_bridge_room_property(
    bridge_room_property: &BridgeRoomProperty,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_association_and_ownership_attributes(
        bridge_room_property.association(),
        bridge_room_property.ownership(),
    );

    match bridge_room_property.object() {
        Some(object) => {
            xml_fragment_writer.write_start_event_with_attributes(
                CityGmlNamespace::Bridge,
                CityGmlElement::BridgeRoomProperty,
                attributes,
            )?;
            serialize_bridge_room(object, xml_fragment_writer)?;
            xml_fragment_writer
                .write_end_event(CityGmlNamespace::Bridge, CityGmlElement::BridgeRoomProperty)?;
        }
        None => {
            xml_fragment_writer.write_empty_element_with_attributes(
                CityGmlNamespace::Bridge,
                CityGmlElement::BridgeRoomProperty,
                attributes,
            )?;
        }
    }

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::core::AsAbstractFeature;
    use egml::model::base::Id;

    #[test]
    fn test_deserialize_bridge_room_property_with_inline_object() {
        let xml_document = b"<brid:bridgeRoom>
    <brid:BridgeRoom gml:id=\"BR_1\">
      <brid:class>5000</brid:class>
    </brid:BridgeRoom>
  </brid:bridgeRoom>";

        let bridge_room_property = deserialize_bridge_room_property(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let bridge_room = bridge_room_property.object().expect("should be inline");
        assert_eq!(
            bridge_room.feature_id(),
            &Id::try_from("BR_1").expect("should work")
        );
    }
}
