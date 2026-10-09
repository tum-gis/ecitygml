use crate::Error;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::appearance::basic_types::{Color, ColorPlusOpacity};
use ecitygml_core::model::core::basic_types::DoubleBetween0And1;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_color_plus_opacity(xml_document: &[u8]) -> Result<ColorPlusOpacity, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    loop {
        match reader.read_event()? {
            Event::Text(text) => {
                let value = text.as_ref();
                return color_plus_opacity_from_str(value.trim());
            }
            Event::CData(cdata) => {
                let value = cdata.as_ref();
                return color_plus_opacity_from_str(value.trim());
            }
            Event::Eof => {
                return Err(Error::ElementNotFound(
                    "colorPlusOpacity text content".to_string(),
                ));
            }
            _ => {}
        }
    }
}

pub fn serialize_color_plus_opacity(
    color_plus_opacity: ColorPlusOpacity,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
    target_xml_namespace: CityGmlNamespace,
    target_xml_element: CityGmlElement,
) -> Result<(), Error> {
    let value = format!(
        "{} {} {} {}",
        color_plus_opacity.color().red().value(),
        color_plus_opacity.color().green().value(),
        color_plus_opacity.color().blue().value(),
        color_plus_opacity.opacity().value()
    );

    xml_fragment_writer.write_leaf_element(target_xml_namespace, target_xml_element, &value)?;

    Ok(())
}

fn color_plus_opacity_from_str(value: &str) -> Result<ColorPlusOpacity, Error> {
    let values: Vec<f64> = value
        .split_whitespace()
        .filter_map(|v| v.parse().ok())
        .collect();
    let [r, g, b, a]: [f64; 4] = values.try_into().map_err(|_| {
        Error::UnknownElementNode(format!("expected exactly 4 f64 values, got `{value}`"))
    })?;

    Ok(ColorPlusOpacity::new(
        Color::new(
            DoubleBetween0And1::try_from(r).map_err(ecitygml_core::Error::from)?,
            DoubleBetween0And1::try_from(g).map_err(ecitygml_core::Error::from)?,
            DoubleBetween0And1::try_from(b).map_err(ecitygml_core::Error::from)?,
        ),
        DoubleBetween0And1::try_from(a).map_err(ecitygml_core::Error::from)?,
    ))
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_color_plus_opacity() {
        let xml_document = b"<app:borderColor>0.1 0.2 0.3 0.4</app:borderColor>";

        let color_plus_opacity = deserialize_color_plus_opacity(xml_document).expect("should work");

        assert_eq!(color_plus_opacity.color().red().value(), 0.1);
        assert_eq!(color_plus_opacity.color().green().value(), 0.2);
        assert_eq!(color_plus_opacity.color().blue().value(), 0.3);
        assert_eq!(color_plus_opacity.opacity().value(), 0.4);
    }

    #[test]
    fn test_deserialize_color_plus_opacity_rejects_wrong_number_of_values() {
        let xml_document = b"<borderColor>0.1 0.2 0.3</borderColor>";

        let result = deserialize_color_plus_opacity(xml_document);

        assert!(result.is_err());
    }

    #[test]
    fn test_serialize_color_plus_opacity() {
        let color_plus_opacity = ColorPlusOpacity::new(
            Color::new(
                DoubleBetween0And1::try_from(0.1).expect("should be valid"),
                DoubleBetween0And1::try_from(0.2).expect("should be valid"),
                DoubleBetween0And1::try_from(0.3).expect("should be valid"),
            ),
            DoubleBetween0And1::try_from(0.4).expect("should be valid"),
        );

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_color_plus_opacity(
            color_plus_opacity,
            &mut xml_fragment_writer,
            CityGmlNamespace::Appearance,
            CityGmlElement::BorderColorProperty,
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

        assert_eq!(xml, "<app:borderColor>0.1 0.2 0.3 0.4</app:borderColor>");
    }

    #[test]
    fn test_round_trip_color_plus_opacity() {
        let xml_document = b"<borderColor>0.5 0.6 0.7 0.8</borderColor>";

        let color_plus_opacity = deserialize_color_plus_opacity(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_color_plus_opacity(
            color_plus_opacity,
            &mut xml_fragment_writer,
            CityGmlNamespace::Appearance,
            CityGmlElement::BorderColorProperty,
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

        let round_tripped = deserialize_color_plus_opacity(xml.as_bytes()).expect("should work");

        assert_eq!(color_plus_opacity, round_tripped);
    }
}
