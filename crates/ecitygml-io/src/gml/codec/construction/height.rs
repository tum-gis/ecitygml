use crate::Error;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::construction::Height;
use ecitygml_core::model::construction::enums::HeightStatusValue;
use ecitygml_core::model::construction::values::ElevationReferenceValue;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use egml::model::basic_types::Code;
use egml::model::measures::Length;
use quick_xml::events::Event;
use quick_xml::{Reader, XmlVersion};

pub fn deserialize_height(xml_document: &[u8]) -> Result<Height, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    // Consume the root `<Height>` element's own start tag.
    loop {
        match reader.read_event()? {
            Event::Start(_) => break,
            Event::Eof => {
                return Err(Error::ElementNotFound("Height".to_string()));
            }
            _ => {}
        }
    }

    let mut high_reference: Option<Code> = None;
    let mut low_reference: Option<Code> = None;
    let mut status: Option<HeightStatusValue> = None;
    let mut length: Option<Length> = None;

    loop {
        match reader.read_event()? {
            Event::Start(start) => match start.local_name().as_ref() {
                "highReference" => {
                    let pos_start = reader.buffer_position() as usize - start.len() - 2;
                    reader.read_to_end(start.name())?;
                    let pos_end = reader.buffer_position() as usize;
                    high_reference = Some(deserialize_code(&xml_document[pos_start..pos_end])?);
                }
                "lowReference" => {
                    let pos_start = reader.buffer_position() as usize - start.len() - 2;
                    reader.read_to_end(start.name())?;
                    let pos_end = reader.buffer_position() as usize;
                    low_reference = Some(deserialize_code(&xml_document[pos_start..pos_end])?);
                }
                "status" => {
                    let text = reader.read_text(start.name())?;
                    let decoded = text.trim();
                    status = Some(
                        height_status_value_from_str(decoded)
                            .ok_or_else(|| Error::UnknownElementNode(decoded.to_string()))?,
                    );
                }
                "value" => {
                    let mut uom: Option<String> = None;
                    for attr in start.attributes() {
                        let attr = attr.map_err(quick_xml::Error::from)?;
                        if attr.key.local_name().as_ref() == "uom" {
                            uom =
                                Some(attr.normalized_value(XmlVersion::Implicit1_0)?.into_owned());
                        }
                    }
                    let uom =
                        uom.ok_or_else(|| Error::ElementNotFound("uom attribute".to_string()))?;

                    let text = reader.read_text(start.name())?;
                    let decoded = text.trim();
                    let value: f64 = decoded.parse().map_err(|_| {
                        Error::UnknownElementNode(format!("expected f64 value, got `{decoded}`"))
                    })?;
                    length = Some(Length::new(value, uom));
                }
                _ => {
                    reader.read_to_end(start.name())?;
                }
            },
            Event::Eof => break,
            _ => {}
        }
    }

    let high_reference = high_reference
        .map(ElevationReferenceValue::from)
        .ok_or_else(|| Error::ElementNotFound("highReference".to_string()))?;
    let low_reference = low_reference
        .map(ElevationReferenceValue::from)
        .ok_or_else(|| Error::ElementNotFound("lowReference".to_string()))?;
    let status = status.ok_or_else(|| Error::ElementNotFound("status".to_string()))?;
    let length = length.ok_or_else(|| Error::ElementNotFound("value".to_string()))?;

    Ok(Height::new(high_reference, low_reference, status, length))
}

pub fn serialize_height(
    height: &Height,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    xml_fragment_writer
        .write_start_event(CityGmlNamespace::Construction, CityGmlElement::Height)?;

    serialize_code(
        height.high_reference().code(),
        xml_fragment_writer,
        CityGmlNamespace::Construction,
        CityGmlElement::HighReferenceProperty,
    )?;

    serialize_code(
        height.low_reference().code(),
        xml_fragment_writer,
        CityGmlNamespace::Construction,
        CityGmlElement::LowReferenceProperty,
    )?;

    xml_fragment_writer.write_leaf_element(
        CityGmlNamespace::Construction,
        CityGmlElement::StatusProperty,
        height_status_value_as_str(height.status()),
    )?;

    xml_fragment_writer.write_leaf_element_with_attributes(
        CityGmlNamespace::Construction,
        CityGmlElement::ValueProperty,
        [("uom", height.length().uom())],
        &height.length().value().to_string(),
    )?;

    xml_fragment_writer.write_end_event(CityGmlNamespace::Construction, CityGmlElement::Height)?;

    Ok(())
}

fn height_status_value_as_str(value: HeightStatusValue) -> &'static str {
    match value {
        HeightStatusValue::Estimated => "estimated",
        HeightStatusValue::Measured => "measured",
    }
}

fn height_status_value_from_str(value: &str) -> Option<HeightStatusValue> {
    match value {
        "estimated" => Some(HeightStatusValue::Estimated),
        "measured" => Some(HeightStatusValue::Measured),
        _ => None,
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    fn sample_xml() -> &'static [u8] {
        br#"<con:Height>
<con:highReference>topOfConstruction</con:highReference>
<con:lowReference>lowestGroundPoint</con:lowReference>
<con:status>measured</con:status>
<con:value uom="urn:adv:uom:m">11.715</con:value>
</con:Height>"#
    }

    #[test]
    fn test_deserialize_height() {
        let height = deserialize_height(sample_xml()).expect("should work");

        assert_eq!(height.high_reference().value(), "topOfConstruction");
        assert_eq!(height.low_reference().value(), "lowestGroundPoint");
        assert_eq!(height.status(), HeightStatusValue::Measured);
        assert_eq!(height.length().uom(), "urn:adv:uom:m");
        assert_eq!(height.length().value(), 11.715);
    }

    #[test]
    fn test_serialize_height() {
        let height = Height::new(
            ElevationReferenceValue::from(Code::new("topOfConstruction")),
            ElevationReferenceValue::from(Code::new("lowestGroundPoint")),
            HeightStatusValue::Measured,
            Length::new(11.715, "urn:adv:uom:m"),
        );

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_height(&height, &mut xml_fragment_writer).expect("should serialize");
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
            r#"<con:Height><con:highReference>topOfConstruction</con:highReference><con:lowReference>lowestGroundPoint</con:lowReference><con:status>measured</con:status><con:value uom="urn:adv:uom:m">11.715</con:value></con:Height>"#
        );
    }

    #[test]
    fn test_round_trip_height() {
        let height = deserialize_height(sample_xml()).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_height(&height, &mut xml_fragment_writer).expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        let round_tripped = deserialize_height(xml.as_bytes()).expect("should work");

        assert_eq!(height, round_tripped);
    }
}
