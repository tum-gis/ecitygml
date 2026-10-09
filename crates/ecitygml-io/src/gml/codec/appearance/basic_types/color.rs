use crate::Error;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::appearance::basic_types::Color;
use ecitygml_core::model::core::basic_types::DoubleBetween0And1;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_color(xml_document: &[u8]) -> Result<Color, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    loop {
        match reader.read_event()? {
            Event::Text(text) => {
                let value = text.as_ref();
                return color_from_str(value.trim());
            }
            Event::CData(cdata) => {
                let value = cdata.as_ref();
                return color_from_str(value.trim());
            }
            Event::Eof => {
                return Err(Error::ElementNotFound("color text content".to_string()));
            }
            _ => {}
        }
    }
}

pub fn serialize_color(
    color: Color,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
    target_xml_namespace: CityGmlNamespace,
    target_xml_element: CityGmlElement,
) -> Result<(), Error> {
    let value = format!(
        "{} {} {}",
        color.red().value(),
        color.green().value(),
        color.blue().value()
    );

    xml_fragment_writer.write_leaf_element(target_xml_namespace, target_xml_element, &value)?;

    Ok(())
}

fn color_from_str(value: &str) -> Result<Color, Error> {
    let values: Vec<f64> = value
        .split_whitespace()
        .filter_map(|v| v.parse().ok())
        .collect();
    let [r, g, b]: [f64; 3] = values.try_into().map_err(|_| {
        Error::UnknownElementNode(format!("expected exactly 3 f64 values, got `{value}`"))
    })?;

    Ok(Color::new(
        DoubleBetween0And1::try_from(r).map_err(ecitygml_core::Error::from)?,
        DoubleBetween0And1::try_from(g).map_err(ecitygml_core::Error::from)?,
        DoubleBetween0And1::try_from(b).map_err(ecitygml_core::Error::from)?,
    ))
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_color() {
        let xml_document = b"<app:diffuseColor>0.1 0.2 0.3</app:diffuseColor>";

        let color = deserialize_color(xml_document).expect("should work");

        assert_eq!(color.red().value(), 0.1);
        assert_eq!(color.green().value(), 0.2);
        assert_eq!(color.blue().value(), 0.3);
    }

    #[test]
    fn test_deserialize_color_rejects_wrong_number_of_values() {
        let xml_document = b"<diffuseColor>0.1 0.2</diffuseColor>";

        let result = deserialize_color(xml_document);

        assert!(result.is_err());
    }

    #[test]
    fn test_serialize_color() {
        let color = Color::new(
            DoubleBetween0And1::try_from(0.1).expect("should be valid"),
            DoubleBetween0And1::try_from(0.2).expect("should be valid"),
            DoubleBetween0And1::try_from(0.3).expect("should be valid"),
        );

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_color(
            color,
            &mut xml_fragment_writer,
            CityGmlNamespace::Appearance,
            CityGmlElement::DiffuseColorProperty,
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

        assert_eq!(xml, "<app:diffuseColor>0.1 0.2 0.3</app:diffuseColor>");
    }

    #[test]
    fn test_round_trip_color() {
        let xml_document = b"<emissiveColor>0.4 0.5 0.6</emissiveColor>";

        let color = deserialize_color(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_color(
            color,
            &mut xml_fragment_writer,
            CityGmlNamespace::Appearance,
            CityGmlElement::EmissiveColorProperty,
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

        let round_tripped = deserialize_color(xml.as_bytes()).expect("should work");

        assert_eq!(color, round_tripped);
    }
}
