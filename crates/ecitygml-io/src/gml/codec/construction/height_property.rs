use crate::Error;
use crate::gml::codec::construction::height::{deserialize_height, serialize_height};
use crate::gml::codec::generics::generic_attribute_set::read_nested_element_index;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::construction::Height;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_height_property(xml_document: &[u8]) -> Result<Height, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    // Consume the property wrapper's own start tag (e.g. `<height>`).
    loop {
        match reader.read_event()? {
            Event::Start(_) => break,
            Event::Eof => {
                return Err(Error::ElementNotFound("height content".to_string()));
            }
            _ => {}
        }
    }

    let (pos_start, pos_end) = read_nested_element_index(&mut reader)?;
    deserialize_height(&xml_document[pos_start..pos_end])
}

pub fn serialize_height_property(
    height: &Height,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
    target_xml_namespace: CityGmlNamespace,
    target_xml_element: CityGmlElement,
) -> Result<(), Error> {
    xml_fragment_writer.write_start_event(target_xml_namespace, target_xml_element)?;
    serialize_height(height, xml_fragment_writer)?;
    xml_fragment_writer.write_end_event(target_xml_namespace, target_xml_element)?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::construction::enums::HeightStatusValue;
    use ecitygml_core::model::construction::{Height, values::ElevationReferenceValue};
    use egml::io::util::Formatting;
    use egml::model::basic_types::Code;
    use egml::model::measures::Length;

    fn sample_xml() -> &'static [u8] {
        br#"<con:height>
<con:Height>
<con:highReference>topOfConstruction</con:highReference>
<con:lowReference>lowestGroundPoint</con:lowReference>
<con:status>measured</con:status>
<con:value uom="urn:adv:uom:m">11.715</con:value>
</con:Height>
</con:height>"#
    }

    #[test]
    fn test_deserialize_height_property() {
        let height = deserialize_height_property(sample_xml()).expect("should work");

        assert_eq!(height.high_reference().value(), "topOfConstruction");
        assert_eq!(height.low_reference().value(), "lowestGroundPoint");
        assert_eq!(height.status(), HeightStatusValue::Measured);
        assert_eq!(height.length().uom(), "urn:adv:uom:m");
        assert_eq!(height.length().value(), 11.715);
    }

    #[test]
    fn test_round_trip_height_property() {
        let height = deserialize_height_property(sample_xml()).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_height_property(
            &height,
            &mut xml_fragment_writer,
            CityGmlNamespace::Construction,
            CityGmlElement::HeightProperty,
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

        let round_tripped = deserialize_height_property(xml.as_bytes()).expect("should work");

        assert_eq!(height, round_tripped);
    }

    #[test]
    fn test_serialize_height_property() {
        let height = Height::new(
            ElevationReferenceValue::from(Code::new("topOfConstruction")),
            ElevationReferenceValue::from(Code::new("lowestGroundPoint")),
            HeightStatusValue::Measured,
            Length::new(11.715, "urn:adv:uom:m"),
        );

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_height_property(
            &height,
            &mut xml_fragment_writer,
            CityGmlNamespace::Construction,
            CityGmlElement::HeightProperty,
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

        assert_eq!(
            xml,
            r#"<con:height><con:Height><con:highReference>topOfConstruction</con:highReference><con:lowReference>lowestGroundPoint</con:lowReference><con:status>measured</con:status><con:value uom="urn:adv:uom:m">11.715</con:value></con:Height></con:height>"#
        );
    }
}
