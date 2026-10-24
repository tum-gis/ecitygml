use crate::Error;
use crate::Error::AttributeWithoutName;
use crate::gml::codec::common::deserialize_string;
use crate::gml::util::{CityGmlElement, CityGmlNamespace, DeserializationConfig};
use ecitygml_core::model::generics::DateAttribute;
use egml::io::codec::xs::{deserialize_date, serialize_date};
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use egml::model::xs::Date;
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_date_attribute(
    xml_document: &[u8],
    config: &DeserializationConfig,
) -> Result<DateAttribute, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    // Consume the root `<DateAttribute>` element's own start tag.
    loop {
        match reader.read_event()? {
            Event::Start(_) => break,
            Event::Eof => {
                return Err(Error::ElementNotFound("DateAttribute".to_string()));
            }
            _ => {}
        }
    }

    let mut name: Option<String> = None;
    let mut value: Option<Date> = None;

    loop {
        match reader.read_event()? {
            Event::Start(start) => {
                let pos_start = reader.buffer_position() as usize - start.len() - 2;
                reader.read_to_end(start.name())?;
                let pos_end = reader.buffer_position() as usize;
                let element = &xml_document[pos_start..pos_end];

                match start.local_name().as_ref() {
                    "name" => name = Some(deserialize_string(element)?.trim().to_string()),
                    "value" => value = Some(deserialize_date(element, config.gml_config())?),
                    _ => {}
                }
            }
            Event::Eof => break,
            _ => {}
        }
    }

    let name = name
        .filter(|x| !x.is_empty())
        .ok_or_else(|| AttributeWithoutName("date attribute".to_string()))?;
    let value = value.ok_or_else(|| Error::ElementNotFound("value".to_string()))?;

    Ok(DateAttribute { name, value })
}

pub fn serialize_date_attribute(
    date_attribute: &DateAttribute,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    xml_fragment_writer
        .write_start_event(CityGmlNamespace::Generics, CityGmlElement::DateAttribute)?;

    xml_fragment_writer.write_leaf_element(
        CityGmlNamespace::Generics,
        CityGmlElement::NameProperty,
        &date_attribute.name,
    )?;
    serialize_date(
        date_attribute.value,
        xml_fragment_writer,
        CityGmlNamespace::Generics,
        CityGmlElement::ValueProperty,
    )?;

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::Generics, CityGmlElement::DateAttribute)?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use chrono::FixedOffset;
    use egml::io::util::Formatting;

    fn deserialize(xml_document: &[u8]) -> Result<DateAttribute, Error> {
        deserialize_date_attribute(xml_document, &DeserializationConfig::default())
    }

    #[test]
    fn test_deserialize_date_attribute() {
        let date_attribute = deserialize(
            b"<gen:DateAttribute>
    <gen:name>renovatedOn</gen:name>
    <gen:value>2015-06-01+02:00</gen:value>
</gen:DateAttribute>",
        )
        .expect("should work");

        assert_eq!(date_attribute.name, "renovatedOn");
        assert_eq!(
            date_attribute.value,
            Date::from_parts(2015, 6, 1, 7_200).expect("valid date")
        );
    }

    #[test]
    fn test_deserialize_date_attribute_uses_configured_default_offset() {
        let mut config = DeserializationConfig::default();
        config.set_gml_config(
            egml::io::util::DeserializationConfig::default()
                .with_default_offset(FixedOffset::east_opt(3_600).expect("valid offset")),
        );

        let date_attribute = deserialize_date_attribute(
            b"<gen:DateAttribute>
    <gen:name>renovatedOn</gen:name>
    <gen:value>2015-06-01</gen:value>
</gen:DateAttribute>",
            &config,
        )
        .expect("should work");

        assert_eq!(date_attribute.value.offset_seconds(), 3_600);
    }

    #[test]
    fn test_deserialize_date_attribute_rejects_empty_name() {
        let result = deserialize(
            b"<gen:DateAttribute>
    <gen:name></gen:name>
    <gen:value>2015-06-01</gen:value>
</gen:DateAttribute>",
        );

        assert!(matches!(result, Err(AttributeWithoutName(_))));
    }

    #[test]
    fn test_deserialize_date_attribute_rejects_invalid_date() {
        let result = deserialize(
            b"<gen:DateAttribute>
    <gen:name>renovatedOn</gen:name>
    <gen:value>2015-02-30</gen:value>
</gen:DateAttribute>",
        );

        assert!(result.is_err());
    }

    #[test]
    fn test_round_trip_date_attribute() {
        let date_attribute = DateAttribute::new(
            "renovatedOn".to_string(),
            Date::from_parts(2015, 6, 1, 0).expect("valid date"),
        );

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_date_attribute(&date_attribute, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");
        assert!(xml.starts_with("<gen:DateAttribute><gen:name>renovatedOn</gen:name>"));

        assert_eq!(
            deserialize(xml.as_bytes()).expect("should round trip"),
            date_attribute
        );
    }
}
