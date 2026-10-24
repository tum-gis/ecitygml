use crate::Error;
use crate::Error::AttributeWithoutName;
use crate::gml::codec::common::deserialize_string;
use crate::gml::util::{CityGmlElement, CityGmlNamespace, DeserializationConfig};
use ecitygml_core::model::generics::UriAttribute;
use egml::io::codec::xs::{deserialize_any_uri, serialize_any_uri};
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use egml::model::xs::AnyUri;
use quick_xml::Reader;
use quick_xml::events::Event;

/// The `config` is unused (a URI needs no configuration) and only keeps the signature uniform with the other
/// generic attribute deserializers.
pub fn deserialize_uri_attribute(
    xml_document: &[u8],
    _config: &DeserializationConfig,
) -> Result<UriAttribute, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    // Consume the root `<UriAttribute>` element's own start tag.
    loop {
        match reader.read_event()? {
            Event::Start(_) => break,
            Event::Eof => {
                return Err(Error::ElementNotFound("UriAttribute".to_string()));
            }
            _ => {}
        }
    }

    let mut name: Option<String> = None;
    let mut value: Option<AnyUri> = None;

    loop {
        match reader.read_event()? {
            Event::Start(start) => {
                let pos_start = reader.buffer_position() as usize - start.len() - 2;
                reader.read_to_end(start.name())?;
                let pos_end = reader.buffer_position() as usize;
                let element = &xml_document[pos_start..pos_end];

                match start.local_name().as_ref() {
                    "name" => name = Some(deserialize_string(element)?.trim().to_string()),
                    "value" => value = Some(deserialize_any_uri(element)?),
                    _ => {}
                }
            }
            Event::Eof => break,
            _ => {}
        }
    }

    let name = name
        .filter(|x| !x.is_empty())
        .ok_or_else(|| AttributeWithoutName("uri attribute".to_string()))?;
    let value = value.ok_or_else(|| Error::ElementNotFound("value".to_string()))?;

    Ok(UriAttribute { name, value })
}

pub fn serialize_uri_attribute(
    uri_attribute: &UriAttribute,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    xml_fragment_writer
        .write_start_event(CityGmlNamespace::Generics, CityGmlElement::UriAttribute)?;

    xml_fragment_writer.write_leaf_element(
        CityGmlNamespace::Generics,
        CityGmlElement::NameProperty,
        &uri_attribute.name,
    )?;
    serialize_any_uri(
        &uri_attribute.value,
        xml_fragment_writer,
        CityGmlNamespace::Generics,
        CityGmlElement::ValueProperty,
    )?;

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::Generics, CityGmlElement::UriAttribute)?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    fn deserialize(xml_document: &[u8]) -> Result<UriAttribute, Error> {
        deserialize_uri_attribute(xml_document, &DeserializationConfig::default())
    }

    fn uri_attribute(value: &str) -> Result<UriAttribute, Error> {
        deserialize(
            format!(
                "<gen:UriAttribute><gen:name>cadastreRecord</gen:name><gen:value>{value}</gen:value></gen:UriAttribute>"
            )
            .as_bytes(),
        )
    }

    #[test]
    fn test_deserialize_uri_attribute() {
        let uri_attribute =
            uri_attribute("https://example.org/cadastre/4711").expect("should work");

        assert_eq!(uri_attribute.name, "cadastreRecord");
        assert_eq!(
            uri_attribute.value.as_str(),
            "https://example.org/cadastre/4711"
        );
    }

    #[test]
    fn test_deserialize_uri_attribute_unescapes_entities() {
        let uri_attribute =
            uri_attribute("https://example.org/?id=4711&amp;view=full").expect("should work");

        assert_eq!(
            uri_attribute.value.as_str(),
            "https://example.org/?id=4711&view=full"
        );
    }

    #[test]
    fn test_deserialize_uri_attribute_collapses_whitespace() {
        let uri_attribute =
            uri_attribute("\n   https://example.org/a   b \n").expect("should work");

        assert_eq!(uri_attribute.value.as_str(), "https://example.org/a b");
    }

    #[test]
    fn test_deserialize_uri_attribute_accepts_empty_value() {
        let uri_attribute = uri_attribute("").expect("an empty string is a valid xs:anyURI");

        assert_eq!(uri_attribute.value, AnyUri::default());
    }

    #[test]
    fn test_deserialize_uri_attribute_rejects_empty_name() {
        let result = deserialize(
            b"<gen:UriAttribute>
    <gen:name></gen:name>
    <gen:value>https://example.org/</gen:value>
</gen:UriAttribute>",
        );

        assert!(matches!(result, Err(AttributeWithoutName(_))));
    }

    #[test]
    fn test_deserialize_uri_attribute_without_value_fails() {
        let result = deserialize(
            b"<gen:UriAttribute>
    <gen:name>cadastreRecord</gen:name>
</gen:UriAttribute>",
        );

        assert!(matches!(result, Err(Error::ElementNotFound(_))));
    }

    #[test]
    fn test_round_trip_uri_attribute_escapes_ampersand() {
        let uri_attribute = UriAttribute::new(
            "cadastreRecord".to_string(),
            AnyUri::new("https://example.org/?id=4711&view=full"),
        );

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_uri_attribute(&uri_attribute, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");
        assert!(xml.contains("?id=4711&amp;view=full"));

        assert_eq!(
            deserialize(xml.as_bytes()).expect("should round trip"),
            uri_attribute
        );
    }
}
