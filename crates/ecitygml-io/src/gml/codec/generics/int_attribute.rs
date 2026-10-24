use crate::Error;
use crate::Error::AttributeWithoutName;
use crate::gml::codec::common::deserialize_string;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::generics::IntAttribute;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_int_attribute(xml_document: &[u8]) -> Result<IntAttribute, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    // Consume the root `<IntAttribute>` element's own start tag.
    loop {
        match reader.read_event()? {
            Event::Start(_) => break,
            Event::Eof => {
                return Err(Error::ElementNotFound("IntAttribute".to_string()));
            }
            _ => {}
        }
    }

    let mut name: Option<String> = None;
    let mut value: Option<i64> = None;

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
                        let parsed: i64 = text.trim().parse().map_err(|_| {
                            Error::UnknownElementNode(format!("expected i64 value, got `{text}`"))
                        })?;
                        value = Some(parsed);
                    }
                    _ => {}
                }
            }
            Event::Eof => break,
            _ => {}
        }
    }

    let name = name.ok_or_else(|| AttributeWithoutName("int attribute".to_string()))?;
    if name.is_empty() {
        return Err(AttributeWithoutName("int attribute".to_string()));
    }
    let value = value.ok_or_else(|| Error::ElementNotFound("value".to_string()))?;

    Ok(IntAttribute { name, value })
}

pub fn serialize_int_attribute(
    int_attribute: &IntAttribute,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    xml_fragment_writer
        .write_start_event(CityGmlNamespace::Generics, CityGmlElement::IntAttribute)?;

    xml_fragment_writer.write_leaf_element(
        CityGmlNamespace::Generics,
        CityGmlElement::NameProperty,
        &int_attribute.name,
    )?;
    xml_fragment_writer.write_leaf_element(
        CityGmlNamespace::Generics,
        CityGmlElement::ValueProperty,
        &int_attribute.value.to_string(),
    )?;

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::Generics, CityGmlElement::IntAttribute)?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_int_attribute() {
        let xml_document = b"<gen:IntAttribute>
    <gen:name>storeys</gen:name>
    <gen:value>4</gen:value>
</gen:IntAttribute>";

        let int_attribute = deserialize_int_attribute(xml_document).expect("should work");

        assert_eq!(int_attribute.name, "storeys");
        assert_eq!(int_attribute.value, 4);
    }

    #[test]
    fn test_deserialize_int_attribute_rejects_empty_name() {
        let xml_document = b"<gen:IntAttribute>
    <gen:name></gen:name>
    <gen:value>4</gen:value>
</gen:IntAttribute>";

        let result = deserialize_int_attribute(xml_document);

        assert!(result.is_err());
    }

    #[test]
    fn test_serialize_int_attribute() {
        let int_attribute = IntAttribute {
            name: "storeys".to_string(),
            value: 4,
        };

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_int_attribute(&int_attribute, &mut xml_fragment_writer)
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
            "<gen:IntAttribute><gen:name>storeys</gen:name><gen:value>4</gen:value></gen:IntAttribute>"
        );
    }

    #[test]
    fn test_round_trip_int_attribute() {
        let xml_document = b"<gen:IntAttribute>
    <gen:name>floors</gen:name>
    <gen:value>-7</gen:value>
</gen:IntAttribute>";

        let int_attribute = deserialize_int_attribute(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_int_attribute(&int_attribute, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        let round_tripped = deserialize_int_attribute(xml.as_bytes()).expect("should work");

        assert_eq!(int_attribute, round_tripped);
    }

    #[test]
    fn test_deserialize_int_attribute_unescapes_name() {
        let int_attribute = deserialize_int_attribute(
            b"<gen:IntAttribute><gen:name>rooms &amp; halls</gen:name><gen:value>4</gen:value></gen:IntAttribute>",
        )
        .expect("should work");

        assert_eq!(int_attribute.name, "rooms & halls");
        assert_eq!(int_attribute.value, 4);
    }
}
