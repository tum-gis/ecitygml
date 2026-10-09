use crate::Error;
use crate::Error::AttributeWithoutName;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::generics::IntAttribute;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_int_attribute(xml_document: &[u8]) -> Result<IntAttribute, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    #[derive(PartialEq)]
    enum Current {
        None,
        Name,
        Value,
    }

    let mut current = Current::None;
    let mut name: Option<String> = None;
    let mut value: Option<i64> = None;

    loop {
        match reader.read_event()? {
            Event::Start(start) => {
                current = match start.local_name().as_ref() {
                    "name" => Current::Name,
                    "value" => Current::Value,
                    _ => Current::None,
                };
            }
            Event::Text(text) => {
                let text_value = text.as_ref();
                match current {
                    Current::Name => name = Some(text_value.trim().to_string()),
                    Current::Value => {
                        let parsed: i64 = text_value.trim().parse().map_err(|_| {
                            Error::UnknownElementNode(format!(
                                "expected i64 value, got `{text_value}`"
                            ))
                        })?;
                        value = Some(parsed);
                    }
                    Current::None => {}
                }
            }
            Event::End(_) => {
                current = Current::None;
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
}
