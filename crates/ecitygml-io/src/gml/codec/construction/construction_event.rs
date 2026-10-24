use crate::Error;
use crate::gml::codec::common::{deserialize_string, serialize_string};
use crate::gml::util::{CityGmlElement, CityGmlNamespace, DeserializationConfig};
use ecitygml_core::model::construction::ConstructionEvent;
use ecitygml_core::model::construction::values::EventValue;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::codec::xs::{deserialize_date, serialize_date};
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use egml::model::basic_types::Code;
use egml::model::xs::Date;
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_construction_event(
    xml_document: &[u8],
    config: &DeserializationConfig,
) -> Result<ConstructionEvent, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    // Consume the root `<ConstructionEvent>` element's own start tag.
    loop {
        match reader.read_event()? {
            Event::Start(_) => break,
            Event::Eof => {
                return Err(Error::ElementNotFound("ConstructionEvent".to_string()));
            }
            _ => {}
        }
    }

    let mut event: Option<Code> = None;
    let mut date_of_event: Option<Date> = None;
    let mut description: Option<String> = None;

    loop {
        match reader.read_event()? {
            Event::Start(start) => {
                let pos_start = reader.buffer_position() as usize - start.len() - 2;
                reader.read_to_end(start.name())?;
                let pos_end = reader.buffer_position() as usize;
                let element = &xml_document[pos_start..pos_end];

                match start.local_name().as_ref() {
                    "event" => event = Some(deserialize_code(element)?),
                    "dateOfEvent" => {
                        date_of_event = Some(deserialize_date(element, config.gml_config())?)
                    }
                    "description" => description = Some(deserialize_string(element)?),
                    _ => {}
                }
            }
            Event::Eof => break,
            _ => {}
        }
    }

    let event = event
        .map(EventValue::from)
        .ok_or_else(|| Error::ElementNotFound("event".to_string()))?;
    let date_of_event =
        date_of_event.ok_or_else(|| Error::ElementNotFound("dateOfEvent".to_string()))?;

    let mut construction_event = ConstructionEvent::new(event, date_of_event);
    construction_event.set_description_opt(description);

    Ok(construction_event)
}

pub fn serialize_construction_event(
    construction_event: &ConstructionEvent,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    xml_fragment_writer.write_start_event(
        CityGmlNamespace::Construction,
        CityGmlElement::ConstructionEvent,
    )?;

    serialize_code(
        construction_event.event().code(),
        xml_fragment_writer,
        CityGmlNamespace::Construction,
        CityGmlElement::EventProperty,
    )?;
    serialize_date(
        *construction_event.date_of_event(),
        xml_fragment_writer,
        CityGmlNamespace::Construction,
        CityGmlElement::DateOfEventProperty,
    )?;
    if let Some(description) = construction_event.description() {
        serialize_string(
            description,
            xml_fragment_writer,
            CityGmlNamespace::Construction,
            CityGmlElement::DescriptionProperty,
        )?;
    }

    xml_fragment_writer.write_end_event(
        CityGmlNamespace::Construction,
        CityGmlElement::ConstructionEvent,
    )?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    const RENOVATION: &[u8] = br#"<con:ConstructionEvent>
<con:event>renovation</con:event>
<con:dateOfEvent>2015-06-01</con:dateOfEvent>
<con:description>Facade renovation</con:description>
</con:ConstructionEvent>"#;

    fn deserialize(xml_document: &[u8]) -> Result<ConstructionEvent, Error> {
        deserialize_construction_event(xml_document, &DeserializationConfig::default())
    }

    #[test]
    fn test_deserialize_construction_event() {
        let construction_event = deserialize(RENOVATION).expect("should work");

        assert_eq!(construction_event.event().code().value(), "renovation");
        assert_eq!(
            construction_event.date_of_event(),
            &Date::from_parts(2015, 6, 1, 0).expect("valid date")
        );
        assert_eq!(construction_event.description(), Some("Facade renovation"));
    }

    #[test]
    fn test_deserialize_construction_event_without_description() {
        let construction_event = deserialize(
            br#"<con:ConstructionEvent>
<con:event>construction</con:event>
<con:dateOfEvent>1998-03-15</con:dateOfEvent>
</con:ConstructionEvent>"#,
        )
        .expect("should work");

        assert_eq!(construction_event.event().code().value(), "construction");
        assert!(construction_event.description().is_none());
    }

    #[test]
    fn test_deserialize_construction_event_without_date_fails() {
        let result = deserialize(
            br#"<con:ConstructionEvent>
<con:event>renovation</con:event>
</con:ConstructionEvent>"#,
        );

        assert!(matches!(result, Err(Error::ElementNotFound(_))));
    }

    #[test]
    fn test_round_trip_construction_event() {
        let construction_event = deserialize(RENOVATION).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_construction_event(&construction_event, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");
        assert!(xml.contains("<con:description>Facade renovation</con:description>"));

        assert_eq!(
            deserialize(xml.as_bytes()).expect("should round trip"),
            construction_event
        );
    }
}
