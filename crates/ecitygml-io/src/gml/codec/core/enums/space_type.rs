use crate::Error;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::core::enums::SpaceType;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_space_type(xml_document: &[u8]) -> Result<SpaceType, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    loop {
        match reader.read_event()? {
            Event::Text(text) => {
                let value = text.as_ref();
                return space_type_from_str(value.trim())
                    .ok_or_else(|| Error::UnknownElementNode(value.trim().to_string()));
            }
            Event::CData(cdata) => {
                let value = cdata.as_ref();
                return space_type_from_str(value.trim())
                    .ok_or_else(|| Error::UnknownElementNode(value.trim().to_string()));
            }
            Event::Eof => {
                return Err(Error::ElementNotFound("spaceType text content".to_string()));
            }
            _ => {}
        }
    }
}

pub fn serialize_space_type(
    space_type: SpaceType,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
    target_xml_namespace: CityGmlNamespace,
    target_xml_element: CityGmlElement,
) -> Result<(), Error> {
    let value = space_type_as_str(space_type);
    xml_fragment_writer.write_leaf_element(target_xml_namespace, target_xml_element, value)?;

    Ok(())
}

fn space_type_as_str(value: SpaceType) -> &'static str {
    match value {
        SpaceType::Closed => "closed",
        SpaceType::Open => "open",
        SpaceType::SemiOpen => "semiOpen",
    }
}

fn space_type_from_str(value: &str) -> Option<SpaceType> {
    match value {
        "closed" => Some(SpaceType::Closed),
        "open" => Some(SpaceType::Open),
        "semiOpen" => Some(SpaceType::SemiOpen),
        _ => None,
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_space_type_value() {
        let xml_document = b"<spaceType>open</spaceType>";

        let space_type = deserialize_space_type(xml_document).expect("should work");

        assert_eq!(space_type, SpaceType::Open);
    }

    #[test]
    fn test_deserialize_space_type_rejects_unknown_value() {
        let xml_document = b"<spaceType>notAValue</spaceType>";

        let result = deserialize_space_type(xml_document);

        assert!(result.is_err());
    }

    #[test]
    fn test_serialize_space_type_value() {
        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);

        serialize_space_type(
            SpaceType::SemiOpen,
            &mut xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::SpaceTypeProperty,
        )
        .expect("should serialize");

        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert_eq!(xml, "<spaceType>semiOpen</spaceType>");
    }

    #[test]
    fn test_round_trip_space_type_value() {
        let xml_document = b"<spaceType>closed</spaceType>";

        let space_type = deserialize_space_type(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_space_type(
            space_type,
            &mut xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::SpaceTypeProperty,
        )
        .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        let round_tripped = deserialize_space_type(xml.as_bytes()).expect("should work");

        assert_eq!(space_type, round_tripped);
    }
}
