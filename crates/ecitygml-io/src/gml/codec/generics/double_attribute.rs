use crate::Error;
use crate::Error::AttributeWithoutName;
use crate::gml::codec::common::deserialize_string;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::generics::DoubleAttribute;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_double_attribute(xml_document: &[u8]) -> Result<DoubleAttribute, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    // Consume the root `<DoubleAttribute>` element's own start tag.
    loop {
        match reader.read_event()? {
            Event::Start(_) => break,
            Event::Eof => {
                return Err(Error::ElementNotFound("DoubleAttribute".to_string()));
            }
            _ => {}
        }
    }

    let mut name: Option<String> = None;
    let mut value: Option<f64> = None;

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
                        let parsed: f64 = text.trim().parse().map_err(|_| {
                            Error::UnknownElementNode(format!("expected f64 value, got `{text}`"))
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

    let name = name.ok_or_else(|| AttributeWithoutName("double attribute".to_string()))?;
    if name.is_empty() {
        return Err(AttributeWithoutName("double attribute".to_string()));
    }
    let value = value.ok_or_else(|| Error::ElementNotFound("value".to_string()))?;

    Ok(DoubleAttribute { name, value })
}

pub fn serialize_double_attribute(
    double_attribute: &DoubleAttribute,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    xml_fragment_writer
        .write_start_event(CityGmlNamespace::Generics, CityGmlElement::DoubleAttribute)?;

    xml_fragment_writer.write_leaf_element(
        CityGmlNamespace::Generics,
        CityGmlElement::NameProperty,
        &double_attribute.name,
    )?;
    xml_fragment_writer.write_leaf_element(
        CityGmlNamespace::Generics,
        CityGmlElement::ValueProperty,
        &double_attribute.value.to_string(),
    )?;

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::Generics, CityGmlElement::DoubleAttribute)?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_double_attribute() {
        let xml_document = b"<gen:DoubleAttribute>
    <gen:name>height</gen:name>
    <gen:value>12.5</gen:value>
</gen:DoubleAttribute>";

        let double_attribute = deserialize_double_attribute(xml_document).expect("should work");

        assert_eq!(double_attribute.name, "height");
        assert_eq!(double_attribute.value, 12.5);
    }

    #[test]
    fn test_deserialize_double_attribute_rejects_empty_name() {
        let xml_document = b"<gen:DoubleAttribute>
    <gen:name></gen:name>
    <gen:value>12.5</gen:value>
</gen:DoubleAttribute>";

        let result = deserialize_double_attribute(xml_document);

        assert!(result.is_err());
    }

    #[test]
    fn test_serialize_double_attribute() {
        let double_attribute = DoubleAttribute {
            name: "height".to_string(),
            value: 12.5,
        };

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_double_attribute(&double_attribute, &mut xml_fragment_writer)
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
            "<gen:DoubleAttribute><gen:name>height</gen:name><gen:value>12.5</gen:value></gen:DoubleAttribute>"
        );
    }

    #[test]
    fn test_round_trip_double_attribute() {
        let xml_document = b"<gen:DoubleAttribute>
    <gen:name>area</gen:name>
    <gen:value>99.9</gen:value>
</gen:DoubleAttribute>";

        let double_attribute = deserialize_double_attribute(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_double_attribute(&double_attribute, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        let round_tripped = deserialize_double_attribute(xml.as_bytes()).expect("should work");

        assert_eq!(double_attribute, round_tripped);
    }

    #[test]
    fn test_deserialize_double_attribute_unescapes_name() {
        let double_attribute = deserialize_double_attribute(
            b"<gen:DoubleAttribute><gen:name>width &amp; depth</gen:name><gen:value>2.5</gen:value></gen:DoubleAttribute>",
        )
        .expect("should work");

        assert_eq!(double_attribute.name, "width & depth");
        assert_eq!(double_attribute.value, 2.5);
    }
}
