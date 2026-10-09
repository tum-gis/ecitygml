use crate::Error;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::core::ExternalReference;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_external_reference(xml_document: &[u8]) -> Result<ExternalReference, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    #[derive(PartialEq)]
    enum Current {
        None,
        TargetResource,
        InformationSystem,
        RelationType,
    }

    let mut current = Current::None;
    let mut target_resource: Option<String> = None;
    let mut information_system: Option<String> = None;
    let mut relation_type: Option<String> = None;

    loop {
        match reader.read_event()? {
            Event::Start(start) => {
                current = match start.local_name().as_ref() {
                    "targetResource" => Current::TargetResource,
                    "informationSystem" => Current::InformationSystem,
                    "relationType" => Current::RelationType,
                    _ => Current::None,
                };
            }
            Event::Text(text) => {
                let value = text.as_ref();
                match current {
                    Current::TargetResource => target_resource = Some(value.trim().to_string()),
                    Current::InformationSystem => {
                        information_system = Some(value.trim().to_string());
                    }
                    Current::RelationType => relation_type = Some(value.trim().to_string()),
                    Current::None => {}
                }
            }
            Event::End(_) => {
                current = Current::None;
            }
            Event::Eof => break,
            _ => {}
        }
    }

    let target_resource =
        target_resource.ok_or_else(|| Error::ElementNotFound("targetResource".to_string()))?;

    Ok(ExternalReference {
        target_resource,
        information_system,
        relation_type,
    })
}

pub fn serialize_external_reference(
    external_reference: &ExternalReference,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    xml_fragment_writer
        .write_start_event(CityGmlNamespace::Core, CityGmlElement::ExternalReference)?;

    xml_fragment_writer.write_leaf_element(
        CityGmlNamespace::Core,
        CityGmlElement::TargetResourceProperty,
        &external_reference.target_resource,
    )?;

    if let Some(information_system) = &external_reference.information_system {
        xml_fragment_writer.write_leaf_element(
            CityGmlNamespace::Core,
            CityGmlElement::InformationSystemProperty,
            information_system,
        )?;
    }

    if let Some(relation_type) = &external_reference.relation_type {
        xml_fragment_writer.write_leaf_element(
            CityGmlNamespace::Core,
            CityGmlElement::RelationTypeProperty,
            relation_type,
        )?;
    }

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::Core, CityGmlElement::ExternalReference)?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_external_reference_basic() {
        let xml_document = b"<ExternalReference>
          <targetResource>DEHHALKA70002P5E</targetResource>
          <informationSystem>http://repository.gdi-de.org/schemas/adv/citygml/fdv/art.htm#_9100</informationSystem>
        </ExternalReference>";

        let external_reference = deserialize_external_reference(xml_document).expect("should work");

        assert_eq!(external_reference.target_resource, "DEHHALKA70002P5E");
        assert!(external_reference.information_system.is_some());
        assert_eq!(
            external_reference.information_system.unwrap(),
            "http://repository.gdi-de.org/schemas/adv/citygml/fdv/art.htm#_9100"
        );
        assert!(external_reference.relation_type.is_none());
    }

    #[test]
    fn test_serialize_external_reference() {
        let external_reference = ExternalReference {
            target_resource: "DEHHALKA70002P5E".to_string(),
            information_system: Some("http://example.com".to_string()),
            relation_type: None,
        };

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_external_reference(&external_reference, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("ExternalReference"));
        assert!(xml.contains("DEHHALKA70002P5E"));
        assert!(xml.contains("http://example.com"));
    }

    #[test]
    fn test_round_trip_external_reference() {
        let xml_document = b"<ExternalReference>
          <targetResource>DEHHALKA70002P5E</targetResource>
          <informationSystem>http://example.com</informationSystem>
          <relationType>self</relationType>
        </ExternalReference>";

        let external_reference = deserialize_external_reference(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_external_reference(&external_reference, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        let round_tripped = deserialize_external_reference(xml.as_bytes()).expect("should work");

        assert_eq!(external_reference, round_tripped);
    }
}
