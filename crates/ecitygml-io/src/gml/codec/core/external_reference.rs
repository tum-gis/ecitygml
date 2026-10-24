use crate::Error;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::core::ExternalReference;
use egml::io::codec::xs::{deserialize_any_uri, serialize_any_uri};
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use egml::model::xs::AnyUri;
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_external_reference(xml_document: &[u8]) -> Result<ExternalReference, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    // Consume the root `<ExternalReference>` element's own start tag.
    loop {
        match reader.read_event()? {
            Event::Start(_) => break,
            Event::Eof => {
                return Err(Error::ElementNotFound("ExternalReference".to_string()));
            }
            _ => {}
        }
    }

    let mut target_resource: Option<AnyUri> = None;
    let mut information_system: Option<AnyUri> = None;
    let mut relation_type: Option<AnyUri> = None;

    // Each child is read as a whole element, so that entities such as `&amp;` in a URI are unescaped instead of
    // splitting the text into several events.
    loop {
        match reader.read_event()? {
            Event::Start(start) => {
                let pos_start = reader.buffer_position() as usize - start.len() - 2;
                reader.read_to_end(start.name())?;
                let pos_end = reader.buffer_position() as usize;
                let element = &xml_document[pos_start..pos_end];

                match start.local_name().as_ref() {
                    "targetResource" => target_resource = Some(deserialize_any_uri(element)?),
                    "informationSystem" => information_system = Some(deserialize_any_uri(element)?),
                    "relationType" => relation_type = Some(deserialize_any_uri(element)?),
                    _ => {}
                }
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

    serialize_any_uri(
        &external_reference.target_resource,
        xml_fragment_writer,
        CityGmlNamespace::Core,
        CityGmlElement::TargetResourceProperty,
    )?;

    if let Some(information_system) = &external_reference.information_system {
        serialize_any_uri(
            information_system,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::InformationSystemProperty,
        )?;
    }

    if let Some(relation_type) = &external_reference.relation_type {
        serialize_any_uri(
            relation_type,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::RelationTypeProperty,
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

        assert_eq!(
            external_reference.target_resource.as_str(),
            "DEHHALKA70002P5E"
        );
        assert!(external_reference.information_system.is_some());
        assert_eq!(
            external_reference.information_system.unwrap().as_str(),
            "http://repository.gdi-de.org/schemas/adv/citygml/fdv/art.htm#_9100"
        );
        assert!(external_reference.relation_type.is_none());
    }

    #[test]
    fn test_serialize_external_reference() {
        let external_reference = ExternalReference {
            target_resource: AnyUri::new("DEHHALKA70002P5E"),
            information_system: Some(AnyUri::new("http://example.com")),
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

    #[test]
    fn test_deserialize_external_reference_keeps_ampersand_in_uri() {
        let xml_document = b"<core:ExternalReference>
          <core:targetResource>https://example.org/?id=4711&amp;view=full</core:targetResource>
        </core:ExternalReference>";

        let external_reference = deserialize_external_reference(xml_document).expect("should work");

        assert_eq!(
            external_reference.target_resource.as_str(),
            "https://example.org/?id=4711&view=full"
        );
    }

    #[test]
    fn test_round_trip_external_reference_escapes_ampersand() {
        let external_reference = ExternalReference {
            target_resource: AnyUri::new("https://example.org/?id=4711&view=full"),
            information_system: None,
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
        assert!(xml.contains("?id=4711&amp;view=full"));

        assert_eq!(
            deserialize_external_reference(xml.as_bytes()).expect("should round trip"),
            external_reference
        );
    }

    #[test]
    fn test_deserialize_external_reference_collapses_whitespace() {
        let xml_document = b"<core:ExternalReference>
          <core:targetResource>
              https://example.org/a   b
          </core:targetResource>
        </core:ExternalReference>";

        let external_reference = deserialize_external_reference(xml_document).expect("should work");

        assert_eq!(
            external_reference.target_resource.as_str(),
            "https://example.org/a b"
        );
    }

    #[test]
    fn test_deserialize_external_reference_with_all_fields() {
        let xml_document = b"<core:ExternalReference>
          <core:targetResource>DEHHALKA70002P5E</core:targetResource>
          <core:informationSystem>https://example.org/alkis</core:informationSystem>
          <core:relationType>https://example.org/relation/sameAs</core:relationType>
        </core:ExternalReference>";

        let external_reference = deserialize_external_reference(xml_document).expect("should work");

        assert_eq!(
            external_reference.target_resource.as_str(),
            "DEHHALKA70002P5E"
        );
        assert_eq!(
            external_reference.information_system,
            Some(AnyUri::new("https://example.org/alkis"))
        );
        assert_eq!(
            external_reference.relation_type,
            Some(AnyUri::new("https://example.org/relation/sameAs"))
        );
    }

    #[test]
    fn test_deserialize_external_reference_without_target_resource_fails() {
        let xml_document = b"<core:ExternalReference>
          <core:informationSystem>https://example.org/alkis</core:informationSystem>
        </core:ExternalReference>";

        let result = deserialize_external_reference(xml_document);

        assert!(matches!(result, Err(Error::ElementNotFound(_))));
    }
}
