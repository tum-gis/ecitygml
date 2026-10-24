use crate::Error;
use crate::Error::AttributeWithoutName;
use crate::gml::codec::common::deserialize_string;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::generics::StringAttribute;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_string_attribute(xml_document: &[u8]) -> Result<StringAttribute, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    // Consume the root `<StringAttribute>` element's own start tag.
    loop {
        match reader.read_event()? {
            Event::Start(_) => break,
            Event::Eof => {
                return Err(Error::ElementNotFound("StringAttribute".to_string()));
            }
            _ => {}
        }
    }

    let mut name: Option<String> = None;
    let mut value: Option<String> = None;

    // Each child is read as a whole element, so that entities such as `&amp;` are unescaped instead of splitting
    // the text into several events.
    loop {
        match reader.read_event()? {
            Event::Start(start) => {
                let pos_start = reader.buffer_position() as usize - start.len() - 2;
                reader.read_to_end(start.name())?;
                let pos_end = reader.buffer_position() as usize;
                let text = deserialize_string(&xml_document[pos_start..pos_end])?;

                match start.local_name().as_ref() {
                    "name" => name = Some(text.trim().to_string()),
                    "value" => {
                        value = Some(text.trim().to_string());
                    }
                    _ => {}
                }
            }
            Event::Eof => break,
            _ => {}
        }
    }

    let name = name.ok_or_else(|| AttributeWithoutName("string attribute".to_string()))?;
    if name.is_empty() {
        return Err(AttributeWithoutName("string attribute".to_string()));
    }
    let value = value.unwrap_or_default();

    Ok(StringAttribute { name, value })
}

pub fn serialize_string_attribute(
    string_attribute: &StringAttribute,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    xml_fragment_writer
        .write_start_event(CityGmlNamespace::Generics, CityGmlElement::StringAttribute)?;

    xml_fragment_writer.write_leaf_element(
        CityGmlNamespace::Generics,
        CityGmlElement::NameProperty,
        &string_attribute.name,
    )?;
    xml_fragment_writer.write_leaf_element(
        CityGmlNamespace::Generics,
        CityGmlElement::ValueProperty,
        &string_attribute.value.to_string(),
    )?;

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::Generics, CityGmlElement::StringAttribute)?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_string_attribute() {
        let xml_document = b"<gen:StringAttribute>
    <gen:name>material</gen:name>
    <gen:value>concrete</gen:value>
</gen:StringAttribute>";

        let string_attribute = deserialize_string_attribute(xml_document).expect("should work");

        assert_eq!(string_attribute.name, "material");
        assert_eq!(string_attribute.value, "concrete");
    }

    #[test]
    fn test_deserialize_string_attribute_rejects_empty_name() {
        let xml_document = b"<gen:StringAttribute>
    <gen:name></gen:name>
    <gen:value>concrete</gen:value>
</gen:StringAttribute>";

        let result = deserialize_string_attribute(xml_document);

        assert!(result.is_err());
    }

    #[test]
    fn test_serialize_string_attribute() {
        let string_attribute = StringAttribute {
            name: "material".to_string(),
            value: "concrete".to_string(),
        };

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_string_attribute(&string_attribute, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert_eq!(
            xml,
            "<gen:StringAttribute><gen:name>material</gen:name><gen:value>concrete</gen:value></gen:StringAttribute>"
        );
    }

    #[test]
    fn test_round_trip_string_attribute() {
        let xml_document = b"<gen:StringAttribute>
    <gen:name>construction_method</gen:name>
    <gen:value>prefab</gen:value>
</gen:StringAttribute>";

        let string_attribute = deserialize_string_attribute(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_string_attribute(&string_attribute, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        let round_tripped = deserialize_string_attribute(xml.as_bytes()).expect("should work");

        assert_eq!(string_attribute, round_tripped);
    }

    #[test]
    fn test_deserialize_string_attribute_unescapes_entities() {
        let string_attribute = deserialize_string_attribute(
            b"<gen:StringAttribute><gen:name>owner &amp; tenant</gen:name><gen:value>R&amp;D &lt;lab&gt;</gen:value></gen:StringAttribute>",
        )
        .expect("should work");

        assert_eq!(string_attribute.name, "owner & tenant");
        assert_eq!(string_attribute.value, "R&D <lab>");
    }

    #[test]
    fn test_round_trip_string_attribute_escapes_once() {
        let string_attribute = StringAttribute {
            name: "owner & tenant".to_string(),
            value: "R&D <lab>".to_string(),
        };

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_string_attribute(&string_attribute, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");
        assert!(xml.contains("R&amp;D &lt;lab&gt;"));
        assert!(!xml.contains("&amp;amp;"));

        assert_eq!(
            deserialize_string_attribute(xml.as_bytes()).expect("should round trip"),
            string_attribute
        );
    }
}
