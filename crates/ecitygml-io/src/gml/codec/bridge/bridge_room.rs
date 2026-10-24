use crate::Error;
use crate::gml::codec::bridge::bridge_furniture_property::{
    deserialize_bridge_furniture_property, serialize_bridge_furniture_property,
};
use crate::gml::codec::core::{
    deserialize_abstract_unoccupied_space, serialize_abstract_unoccupied_space,
    serialize_abstract_unoccupied_space_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::bridge::BridgeRoom;
use ecitygml_core::model::core::AsAbstractUnoccupiedSpace;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter, collect_children};
use egml::model::basic_types::Code;

pub fn deserialize_bridge_room(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<BridgeRoom, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_unoccupied_space =
        deserialize_abstract_unoccupied_space(xml_document, index, config)?;
    let mut bridge_room = BridgeRoom::from_abstract_unoccupied_space(abstract_unoccupied_space);

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    bridge_room.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    bridge_room.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    bridge_room.set_usages(usages.into_iter().map(Into::into).collect());

    bridge_room.set_bridge_furniture(collect_children(
        xml_document,
        index,
        CityGmlElement::BridgeFurnitureProperty.into(),
        config,
        deserialize_bridge_furniture_property,
    )?);

    Ok(bridge_room)
}

pub fn serialize_bridge_room(
    bridge_room: &BridgeRoom,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_bridge_room_attributes(bridge_room);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Bridge,
        CityGmlElement::BridgeRoom,
        attributes,
    )?;

    serialize_abstract_unoccupied_space(
        bridge_room.abstract_unoccupied_space(),
        xml_fragment_writer,
    )?;

    if let Some(class) = bridge_room.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Bridge,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in bridge_room.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::Bridge,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in bridge_room.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::Bridge,
            CityGmlElement::UsageProperty,
        )?;
    }

    for prop in bridge_room.bridge_furniture() {
        serialize_bridge_furniture_property(prop, xml_fragment_writer)?;
    }

    xml_fragment_writer.write_end_event(CityGmlNamespace::Bridge, CityGmlElement::BridgeRoom)?;

    Ok(())
}

pub fn serialize_bridge_room_attributes(bridge_room: &BridgeRoom) -> Vec<(String, String)> {
    serialize_abstract_unoccupied_space_attributes(bridge_room.abstract_unoccupied_space())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::core::AsAbstractFeature;
    use egml::io::util::Formatting;
    use egml::model::base::{AsAbstractGml, Id};

    fn deserialize(xml_document: &[u8]) -> BridgeRoom {
        deserialize_bridge_room(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work")
    }

    #[test]
    fn test_deserialize_bridge_room() {
        let xml_document = b"<brid:BridgeRoom gml:id=\"BR_1\">
      <gml:name>Service room</gml:name>
      <brid:class>5000</brid:class>
      <brid:function>5010</brid:function>
      <brid:function>5020</brid:function>
      <brid:usage>6000</brid:usage>
    </brid:BridgeRoom>";

        let bridge_room = deserialize(xml_document);

        assert_eq!(
            bridge_room.feature_id(),
            &Id::try_from("BR_1").expect("should work")
        );
        assert_eq!(
            bridge_room.names().first().expect("should have a name"),
            &Code::new("Service room")
        );
        assert_eq!(bridge_room.class().map(|x| x.code().value()), Some("5000"));
        assert_eq!(
            bridge_room
                .functions()
                .iter()
                .map(|x| x.code().value())
                .collect::<Vec<_>>(),
            vec!["5010", "5020"]
        );
        assert_eq!(
            bridge_room
                .usages()
                .iter()
                .map(|x| x.code().value())
                .collect::<Vec<_>>(),
            vec!["6000"]
        );
    }

    #[test]
    fn test_deserialize_bridge_room_without_codes() {
        let bridge_room = deserialize(b"<brid:BridgeRoom gml:id=\"BR_1\"/>");

        assert!(bridge_room.class().is_none());
        assert!(bridge_room.functions().is_empty());
        assert!(bridge_room.usages().is_empty());
    }

    #[test]
    fn test_round_trip_bridge_room() {
        let mut bridge_room = BridgeRoom::new(Id::try_from("BR_1").expect("should work"));
        bridge_room.set_class(Code::new("5000").into());
        bridge_room.push_function(Code::new("5010").into());
        bridge_room.push_usage(Code::new("6000").into());

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_bridge_room(&bridge_room, &mut xml_fragment_writer).expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");
        assert!(xml.starts_with("<brid:BridgeRoom"));

        assert_eq!(deserialize(xml.as_bytes()), bridge_room);
    }
}
