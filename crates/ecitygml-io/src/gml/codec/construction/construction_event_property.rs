use crate::Error;
use crate::gml::codec::construction::construction_event::{
    deserialize_construction_event, serialize_construction_event,
};
use crate::gml::codec::generics::generic_attribute_set::read_nested_element_index;
use crate::gml::util::{CityGmlElement, CityGmlNamespace, DeserializationConfig};
use ecitygml_core::model::construction::ConstructionEvent;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_construction_event_property(
    xml_document: &[u8],
    config: &DeserializationConfig,
) -> Result<ConstructionEvent, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    // Consume the property wrapper's own start tag (e.g. `<constructionEvent>`).
    loop {
        match reader.read_event()? {
            Event::Start(_) => break,
            Event::Eof => {
                return Err(Error::ElementNotFound(
                    "constructionEvent content".to_string(),
                ));
            }
            _ => {}
        }
    }

    let (pos_start, pos_end) = read_nested_element_index(&mut reader)?;
    deserialize_construction_event(&xml_document[pos_start..pos_end], config)
}

pub fn serialize_construction_event_property(
    construction_event: &ConstructionEvent,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
    target_xml_namespace: CityGmlNamespace,
    target_xml_element: CityGmlElement,
) -> Result<(), Error> {
    xml_fragment_writer.write_start_event(target_xml_namespace, target_xml_element)?;
    serialize_construction_event(construction_event, xml_fragment_writer)?;
    xml_fragment_writer.write_end_event(target_xml_namespace, target_xml_element)?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    const PROPERTY: &[u8] = br#"<con:constructionEvent>
<con:ConstructionEvent>
<con:event>renovation</con:event>
<con:dateOfEvent>2015-06-01</con:dateOfEvent>
</con:ConstructionEvent>
</con:constructionEvent>"#;

    #[test]
    fn test_round_trip_construction_event_property() {
        let construction_event =
            deserialize_construction_event_property(PROPERTY, &DeserializationConfig::default())
                .expect("should work");
        assert_eq!(construction_event.event().code().value(), "renovation");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_construction_event_property(
            &construction_event,
            &mut xml_fragment_writer,
            CityGmlNamespace::Construction,
            CityGmlElement::ConstructionEventProperty,
        )
        .expect("should serialize");
        let xml = {
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        };
        assert!(xml.starts_with(b"<con:constructionEvent>"));

        assert_eq!(
            deserialize_construction_event_property(&xml, &DeserializationConfig::default())
                .expect("should round trip"),
            construction_event
        );
    }
}
