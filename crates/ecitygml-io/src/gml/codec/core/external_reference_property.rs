use crate::Error;
use crate::gml::codec::core::external_reference::{
    deserialize_external_reference, serialize_external_reference,
};
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::core::ExternalReference;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_external_reference_property(
    xml_document: &[u8],
) -> Result<ExternalReference, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    loop {
        match reader.read_event()? {
            Event::Start(start) if start.local_name().as_ref() == "ExternalReference" => {
                let pos_start = reader.buffer_position() as usize - start.len() - 2;
                reader.read_to_end(start.name())?;
                let pos_end = reader.buffer_position() as usize;
                return deserialize_external_reference(&xml_document[pos_start..pos_end]);
            }
            Event::Eof => {
                return Err(Error::ElementNotFound("ExternalReference".to_string()));
            }
            _ => {}
        }
    }
}

pub fn serialize_external_reference_property(
    external_reference: &ExternalReference,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
    target_xml_namespace: CityGmlNamespace,
    target_xml_element: CityGmlElement,
) -> Result<(), Error> {
    xml_fragment_writer.write_start_event(target_xml_namespace, target_xml_element)?;
    serialize_external_reference(external_reference, xml_fragment_writer)?;
    xml_fragment_writer.write_end_event(target_xml_namespace, target_xml_element)?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;
    use egml::model::xs::AnyUri;

    #[test]
    fn test_deserialize_external_reference_property() {
        let xml_document = b"<externalReference>
    <ExternalReference>
        <targetResource>DEHHALKA70002P5E</targetResource>
        <informationSystem>http://example.com</informationSystem>
    </ExternalReference>
</externalReference>";

        let external_reference =
            deserialize_external_reference_property(xml_document).expect("should work");

        assert_eq!(
            external_reference.target_resource.as_str(),
            "DEHHALKA70002P5E"
        );
        assert_eq!(
            external_reference
                .information_system
                .as_ref()
                .map(AnyUri::as_str),
            Some("http://example.com")
        );
    }

    #[test]
    fn test_serialize_external_reference_property() {
        let external_reference = ExternalReference {
            target_resource: AnyUri::new("DEHHALKA70002P5E"),
            information_system: Some(AnyUri::new("http://example.com")),
            relation_type: None,
        };

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_external_reference_property(
            &external_reference,
            &mut xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::ExternalReferenceProperty,
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

        assert!(xml.contains("ExternalReference"));
        assert!(xml.contains("DEHHALKA70002P5E"));
        assert!(xml.contains("http://example.com"));
    }

    #[test]
    fn test_round_trip_external_reference_property() {
        let xml_document = b"<externalReference>
    <ExternalReference>
        <targetResource>DEHHALKA70002P5E</targetResource>
        <informationSystem>http://example.com</informationSystem>
    </ExternalReference>
</externalReference>";

        let external_reference =
            deserialize_external_reference_property(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_external_reference_property(
            &external_reference,
            &mut xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::ExternalReferenceProperty,
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

        let round_tripped =
            deserialize_external_reference_property(xml.as_bytes()).expect("should work");

        assert_eq!(external_reference, round_tripped);
    }
}
