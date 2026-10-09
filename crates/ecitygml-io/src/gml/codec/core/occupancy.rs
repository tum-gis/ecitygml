use crate::Error;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::core::Occupancy;
use ecitygml_core::model::core::values::{IntervalValue, OccupantTypeValue};
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use egml::model::basic_types::Code;
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_occupancy(xml_document: &[u8]) -> Result<Occupancy, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    // Consume the root `<Occupancy>` element's own start tag.
    loop {
        match reader.read_event()? {
            Event::Start(_) => break,
            Event::Eof => {
                return Err(Error::ElementNotFound("Occupancy".to_string()));
            }
            _ => {}
        }
    }

    let mut number_of_occupants: Option<i64> = None;
    let mut interval: Option<Code> = None;
    let mut occupant_type: Option<Code> = None;

    loop {
        match reader.read_event()? {
            Event::Start(start) => match start.local_name().as_ref() {
                "numberOfOccupants" => {
                    let text = reader.read_text(start.name())?;
                    let decoded = text.as_ref();
                    let parsed: i64 = decoded.trim().parse().map_err(|_| {
                        Error::UnknownElementNode(format!(
                            "expected i64 numberOfOccupants, got `{decoded}`"
                        ))
                    })?;
                    number_of_occupants = Some(parsed);
                }
                "interval" => {
                    let pos_start = reader.buffer_position() as usize - start.len() - 2;
                    reader.read_to_end(start.name())?;
                    let pos_end = reader.buffer_position() as usize;
                    interval = Some(deserialize_code(&xml_document[pos_start..pos_end])?);
                }
                "occupantType" => {
                    let pos_start = reader.buffer_position() as usize - start.len() - 2;
                    reader.read_to_end(start.name())?;
                    let pos_end = reader.buffer_position() as usize;
                    occupant_type = Some(deserialize_code(&xml_document[pos_start..pos_end])?);
                }
                _ => {
                    reader.read_to_end(start.name())?;
                }
            },
            Event::Eof => break,
            _ => {}
        }
    }

    let number_of_occupants = number_of_occupants
        .ok_or_else(|| Error::ElementNotFound("numberOfOccupants".to_string()))?;

    let mut occupancy = Occupancy::new(number_of_occupants);
    occupancy.set_interval_opt(interval.map(IntervalValue::from));
    occupancy.set_occupant_type_opt(occupant_type.map(OccupantTypeValue::from));

    Ok(occupancy)
}

pub fn serialize_occupancy(
    occupancy: &Occupancy,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    xml_fragment_writer.write_start_event(CityGmlNamespace::Core, CityGmlElement::Occupancy)?;

    xml_fragment_writer.write_leaf_element(
        CityGmlNamespace::Core,
        CityGmlElement::NumberOfOccupantsProperty,
        &occupancy.number_of_occupants().to_string(),
    )?;

    if let Some(interval) = occupancy.interval() {
        serialize_code(
            interval.code(),
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::IntervalProperty,
        )?;
    }

    if let Some(occupant_type) = occupancy.occupant_type() {
        serialize_code(
            occupant_type.code(),
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::OccupantTypeProperty,
        )?;
    }

    xml_fragment_writer.write_end_event(CityGmlNamespace::Core, CityGmlElement::Occupancy)?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_occupancy() {
        let xml_document = b"<Occupancy>
    <numberOfOccupants>123</numberOfOccupants>
    <interval>myInterval</interval>
    <occupantType>myOccupantType</occupantType>
</Occupancy>";

        let occupancy = deserialize_occupancy(xml_document).expect("should work");

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
    fn test_deserialize_occupancy_without_optional_fields() {
        let xml_document = b"<Occupancy>
    <numberOfOccupants>123</numberOfOccupants>
</Occupancy>";

        let occupancy = deserialize_occupancy(xml_document).expect("should work");

        assert_eq!(occupancy.number_of_occupants(), 123);
        assert!(occupancy.interval().is_none());
        assert!(occupancy.occupant_type().is_none());
    }

    #[test]
    fn test_serialize_occupancy() {
        let mut occupancy = Occupancy::new(123);
        occupancy.set_interval(IntervalValue::from(Code::new("myInterval")));
        occupancy.set_occupant_type(OccupantTypeValue::from(Code::new("myOccupantType")));

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_occupancy(&occupancy, &mut xml_fragment_writer).expect("should serialize");
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
        assert!(xml.contains("interval"));
        assert!(xml.contains("myInterval"));
        assert!(xml.contains("occupantType"));
        assert!(xml.contains("myOccupantType"));
    }

    #[test]
    fn test_round_trip_occupancy() {
        let xml_document = b"<Occupancy>
    <numberOfOccupants>123</numberOfOccupants>
    <interval>myInterval</interval>
    <occupantType>myOccupantType</occupantType>
</Occupancy>";

        let occupancy = deserialize_occupancy(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_occupancy(&occupancy, &mut xml_fragment_writer).expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        let round_tripped = deserialize_occupancy(xml.as_bytes()).expect("should work");

        assert_eq!(occupancy, round_tripped);
    }
}
