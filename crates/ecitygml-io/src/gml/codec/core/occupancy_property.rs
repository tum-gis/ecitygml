use crate::Error;
use crate::gml::codec::core::occupancy::{deserialize_occupancy, serialize_occupancy};
use crate::gml::codec::generics::generic_attribute_set::read_nested_element_index;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::core::Occupancy;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_occupancy_property(xml_document: &[u8]) -> Result<Occupancy, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    // Consume the property wrapper's own start tag (e.g. `<occupancy>`).
    loop {
        match reader.read_event()? {
            Event::Start(_) => break,
            Event::Eof => {
                return Err(Error::ElementNotFound("occupancy content".to_string()));
            }
            _ => {}
        }
    }

    let (pos_start, pos_end) = read_nested_element_index(&mut reader)?;
    deserialize_occupancy(&xml_document[pos_start..pos_end])
}

pub fn serialize_occupancy_property(
    occupancy: &Occupancy,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
    target_xml_namespace: CityGmlNamespace,
    target_xml_element: CityGmlElement,
) -> Result<(), Error> {
    xml_fragment_writer.write_start_event(target_xml_namespace, target_xml_element)?;
    serialize_occupancy(occupancy, xml_fragment_writer)?;
    xml_fragment_writer.write_end_event(target_xml_namespace, target_xml_element)?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::core::values::{IntervalValue, OccupantTypeValue};
    use egml::io::util::Formatting;
    use egml::model::basic_types::Code;

    #[test]
    fn test_deserialize_occupancy_property() {
        let xml_document = b"<occupancy>
    <Occupancy>
        <numberOfOccupants>123</numberOfOccupants>
        <interval>myInterval</interval>
        <occupantType>myOccupantType</occupantType>
    </Occupancy>
</occupancy>";

        let occupancy = deserialize_occupancy_property(xml_document).expect("should work");

        assert_eq!(occupancy.number_of_occupants(), 123);
        assert_eq!(
            occupancy.interval().expect("must exist").code().value(),
            "myInterval"
        );
        assert_eq!(
            occupancy
                .occupant_type()
                .expect("must exist")
                .code()
                .value(),
            "myOccupantType"
        );
    }

    #[test]
    fn test_serialize_occupancy_property() {
        let mut occupancy = Occupancy::new(123);
        occupancy.set_interval(IntervalValue::from(Code::new("myInterval")));
        occupancy.set_occupant_type(OccupantTypeValue::from(Code::new("myOccupantType")));

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_occupancy_property(
            &occupancy,
            &mut xml_fragment_writer,
            CityGmlNamespace::Construction,
            CityGmlElement::OccupancyProperty,
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

        assert!(xml.contains("Occupancy"));
        assert!(xml.contains("numberOfOccupants"));
        assert!(xml.contains("123"));
        assert!(xml.contains("myInterval"));
        assert!(xml.contains("myOccupantType"));
    }

    #[test]
    fn test_round_trip_occupancy_property() {
        let xml_document = b"<occupancy>
    <Occupancy>
        <numberOfOccupants>123</numberOfOccupants>
        <interval>myInterval</interval>
        <occupantType>myOccupantType</occupantType>
    </Occupancy>
</occupancy>";

        let occupancy = deserialize_occupancy_property(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_occupancy_property(
            &occupancy,
            &mut xml_fragment_writer,
            CityGmlNamespace::Construction,
            CityGmlElement::OccupancyProperty,
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

        let round_tripped = deserialize_occupancy_property(xml.as_bytes()).expect("should work");

        assert_eq!(occupancy, round_tripped);
    }
}
