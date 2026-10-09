use crate::Error;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::appearance::enums::TextureType;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_texture_type(xml_document: &[u8]) -> Result<TextureType, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    loop {
        match reader.read_event()? {
            Event::Text(text) => {
                let value = text.as_ref();
                return texture_type_from_str(value.trim())
                    .ok_or_else(|| Error::UnknownElementNode(value.trim().to_string()));
            }
            Event::CData(cdata) => {
                let value = cdata.as_ref();
                return texture_type_from_str(value.trim())
                    .ok_or_else(|| Error::UnknownElementNode(value.trim().to_string()));
            }
            Event::Eof => {
                return Err(Error::ElementNotFound(
                    "textureType text content".to_string(),
                ));
            }
            _ => {}
        }
    }
}

pub fn serialize_texture_type(
    texture_type: TextureType,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
    target_xml_namespace: CityGmlNamespace,
    target_xml_element: CityGmlElement,
) -> Result<(), Error> {
    let value = texture_type_as_str(texture_type);

    xml_fragment_writer.write_leaf_element(target_xml_namespace, target_xml_element, value)?;

    Ok(())
}

fn texture_type_as_str(value: TextureType) -> &'static str {
    match value {
        TextureType::Specific => "specific",
        TextureType::Typical => "typical",
        TextureType::Unknown => "unknown",
    }
}

fn texture_type_from_str(value: &str) -> Option<TextureType> {
    match value {
        "specific" => Some(TextureType::Specific),
        "typical" => Some(TextureType::Typical),
        "unknown" => Some(TextureType::Unknown),
        _ => None,
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_texture_type() {
        let xml_document = b"<textureType>specific</textureType>";

        let texture_type = deserialize_texture_type(xml_document).expect("should work");

        assert_eq!(texture_type, TextureType::Specific);
    }

    #[test]
    fn test_deserialize_texture_type_rejects_unknown_value() {
        let xml_document = b"<textureType>notAValue</textureType>";

        let result = deserialize_texture_type(xml_document);

        assert!(result.is_err());
    }

    #[test]
    fn test_serialize_texture_type() {
        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);

        serialize_texture_type(
            TextureType::Typical,
            &mut xml_fragment_writer,
            CityGmlNamespace::Appearance,
            CityGmlElement::TextureTypeProperty,
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

        assert_eq!(xml, "<app:textureType>typical</app:textureType>");
    }

    #[test]
    fn test_round_trip_texture_type() {
        let xml_document = b"<textureType>unknown</textureType>";

        let texture_type = deserialize_texture_type(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_texture_type(
            texture_type,
            &mut xml_fragment_writer,
            CityGmlNamespace::Appearance,
            CityGmlElement::TextureTypeProperty,
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

        let round_tripped = deserialize_texture_type(xml.as_bytes()).expect("should work");

        assert_eq!(texture_type, round_tripped);
    }
}
