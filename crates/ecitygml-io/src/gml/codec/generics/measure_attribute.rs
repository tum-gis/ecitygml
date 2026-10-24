use crate::Error;
use crate::Error::AttributeWithoutName;
use crate::gml::codec::common::deserialize_string;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::generics::MeasureAttribute;
use egml::io::codec::basic::{deserialize_measure, serialize_measure};
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use egml::model::basic_types::Measure;
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_measure_attribute(xml_document: &[u8]) -> Result<MeasureAttribute, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    let mut name: Option<String> = None;
    let mut value: Option<Measure> = None;

    loop {
        match reader.read_event()? {
            Event::Start(start) if start.local_name().as_ref() == "name" => {
                let pos_start = reader.buffer_position() as usize - start.len() - 2;
                reader.read_to_end(start.name())?;
                let pos_end = reader.buffer_position() as usize;
                name = Some(
                    deserialize_string(&xml_document[pos_start..pos_end])?
                        .trim()
                        .to_string(),
                );
            }
            Event::Start(start) if start.local_name().as_ref() == "value" => {
                let pos_start = reader.buffer_position() as usize - start.len() - 2;
                reader.read_to_end(start.name())?;
                let pos_end = reader.buffer_position() as usize;
                value = Some(deserialize_measure(&xml_document[pos_start..pos_end])?);
            }
            Event::Eof => break,
            _ => {}
        }
    }

    let name = name.ok_or_else(|| AttributeWithoutName("measure attribute".to_string()))?;
    if name.is_empty() {
        return Err(AttributeWithoutName("measure attribute".to_string()));
    }
    let value = value.ok_or_else(|| Error::ElementNotFound("value".to_string()))?;

    Ok(MeasureAttribute { name, value })
}

pub fn serialize_measure_attribute(
    measure_attribute: &MeasureAttribute,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    xml_fragment_writer
        .write_start_event(CityGmlNamespace::Generics, CityGmlElement::MeasureAttribute)?;

    xml_fragment_writer.write_leaf_element(
        CityGmlNamespace::Generics,
        CityGmlElement::NameProperty,
        &measure_attribute.name,
    )?;
    serialize_measure(
        &measure_attribute.value,
        xml_fragment_writer,
        CityGmlNamespace::Generics,
        CityGmlElement::ValueProperty,
    )?;

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::Generics, CityGmlElement::MeasureAttribute)?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_measure_attribute() {
        let xml_document = b"
        <gen:MeasureAttribute>
          <gen:name>GrossPlannedArea</gen:name>
          <gen:value uom=\"m2\">120.0</gen:value>
        </gen:MeasureAttribute>";

        let measure_attribute = deserialize_measure_attribute(xml_document).expect("should work");

        assert_eq!(measure_attribute.name, "GrossPlannedArea");
        assert_eq!(measure_attribute.value.uom, "m2");
        assert_eq!(measure_attribute.value.value, 120.0);
    }

    #[test]
    fn test_deserialize_measure_attribute_rejects_empty_name() {
        let xml_document = b"
        <gen:MeasureAttribute>
          <gen:name></gen:name>
          <gen:value uom=\"m2\">120.0</gen:value>
        </gen:MeasureAttribute>";

        let result = deserialize_measure_attribute(xml_document);

        assert!(result.is_err());
    }

    #[test]
    fn test_serialize_measure_attribute() {
        let measure_attribute = MeasureAttribute {
            name: "GrossPlannedArea".to_string(),
            value: Measure {
                uom: "m2".to_string(),
                value: 120.0,
            },
        };

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_measure_attribute(&measure_attribute, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("gen:MeasureAttribute"));
        assert!(xml.contains("gen:name"));
        assert!(xml.contains("GrossPlannedArea"));
        assert!(xml.contains("uom=\"m2\""));
        assert!(xml.contains("120"));
    }

    #[test]
    fn test_round_trip_measure_attribute() {
        let xml_document = b"
        <gen:MeasureAttribute>
          <gen:name>volume</gen:name>
          <gen:value uom=\"m3\">1500.0</gen:value>
        </gen:MeasureAttribute>";

        let measure_attribute = deserialize_measure_attribute(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_measure_attribute(&measure_attribute, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        let round_tripped = deserialize_measure_attribute(xml.as_bytes()).expect("should work");

        assert_eq!(measure_attribute, round_tripped);
    }

    #[test]
    fn test_deserialize_measure_attribute_unescapes_name() {
        let measure_attribute = deserialize_measure_attribute(
            b"<gen:MeasureAttribute><gen:name>height &amp; width</gen:name><gen:value uom=\"m\">2.5</gen:value></gen:MeasureAttribute>",
        )
        .expect("should work");

        assert_eq!(measure_attribute.name, "height & width");
    }
}
