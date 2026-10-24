use crate::Error;
use crate::gml::codec::building::room_height::{deserialize_room_height, serialize_room_height};
use crate::gml::codec::generics::generic_attribute_set::read_nested_element_index;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::building::RoomHeight;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_room_height_property(xml_document: &[u8]) -> Result<RoomHeight, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    // Consume the property wrapper's own start tag (e.g. `<roomHeight>`).
    loop {
        match reader.read_event()? {
            Event::Start(_) => break,
            Event::Eof => {
                return Err(Error::ElementNotFound("roomHeight content".to_string()));
            }
            _ => {}
        }
    }

    let (pos_start, pos_end) = read_nested_element_index(&mut reader)?;
    deserialize_room_height(&xml_document[pos_start..pos_end])
}

pub fn serialize_room_height_property(
    room_height: &RoomHeight,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
    target_xml_namespace: CityGmlNamespace,
    target_xml_element: CityGmlElement,
) -> Result<(), Error> {
    xml_fragment_writer.write_start_event(target_xml_namespace, target_xml_element)?;
    serialize_room_height(room_height, xml_fragment_writer)?;
    xml_fragment_writer.write_end_event(target_xml_namespace, target_xml_element)?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::building::{RoomHeight, values::RoomElevationReferenceValue};
    use ecitygml_core::model::construction::enums::HeightStatusValue;
    use egml::io::util::Formatting;
    use egml::model::basic_types::Code;
    use egml::model::measures::Length;

    fn sample_xml() -> &'static [u8] {
        br#"<bldg:roomHeight>
<bldg:RoomHeight>
<bldg:highReference>ceiling</bldg:highReference>
<bldg:lowReference>floor</bldg:lowReference>
<bldg:status>measured</bldg:status>
<bldg:value uom="urn:adv:uom:m">2.75</bldg:value>
</bldg:RoomHeight>
</bldg:roomHeight>"#
    }

    #[test]
    fn test_deserialize_room_height_property() {
        let room_height = deserialize_room_height_property(sample_xml()).expect("should work");

        assert_eq!(room_height.high_reference().value(), "ceiling");
        assert_eq!(room_height.low_reference().value(), "floor");
        assert_eq!(room_height.status(), HeightStatusValue::Measured);
        assert_eq!(room_height.length().uom(), "urn:adv:uom:m");
        assert_eq!(room_height.length().value(), 2.75);
    }

    #[test]
    fn test_round_trip_height_property() {
        let room_height = deserialize_room_height_property(sample_xml()).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_room_height_property(
            &room_height,
            &mut xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::RoomHeightProperty,
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

        let round_tripped = deserialize_room_height_property(xml.as_bytes()).expect("should work");

        assert_eq!(room_height, round_tripped);
    }

    #[test]
    fn test_serialize_room_height_property() {
        let room_height = RoomHeight::new(
            RoomElevationReferenceValue::from(Code::new("ceiling")),
            RoomElevationReferenceValue::from(Code::new("floor")),
            HeightStatusValue::Measured,
            Length::new(2.75, "urn:adv:uom:m"),
        );

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_room_height_property(
            &room_height,
            &mut xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::RoomHeightProperty,
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
            r#"<bldg:roomHeight><bldg:RoomHeight><bldg:highReference>ceiling</bldg:highReference><bldg:lowReference>floor</bldg:lowReference><bldg:status>measured</bldg:status><bldg:value uom="urn:adv:uom:m">2.75</bldg:value></bldg:RoomHeight></bldg:roomHeight>"#
        );
    }
}
