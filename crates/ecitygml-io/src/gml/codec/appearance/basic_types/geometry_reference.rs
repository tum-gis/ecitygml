use crate::Error;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::appearance::GeometryReference;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_geometry_reference(xml_document: &[u8]) -> Result<GeometryReference, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    loop {
        match reader.read_event()? {
            Event::Text(text) => {
                let value = text.as_ref();
                return Ok(GeometryReference::new(value.trim().to_string()));
            }
            Event::CData(cdata) => {
                let value = cdata.as_ref();
                return Ok(GeometryReference::new(value.trim().to_string()));
            }
            Event::Eof => {
                return Err(Error::ElementNotFound(
                    "geometry reference text content".to_string(),
                ));
            }
            _ => {}
        }
    }
}

pub fn serialize_geometry_reference(
    geometry_reference: &GeometryReference,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
    target_xml_namespace: CityGmlNamespace,
    target_xml_element: CityGmlElement,
) -> Result<(), Error> {
    xml_fragment_writer.write_leaf_element(
        target_xml_namespace,
        target_xml_element,
        &geometry_reference.href,
    )?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_geometry_reference() {
        let xml_document = b"<app:target>#abc</app:target>";

        let geometry_reference = deserialize_geometry_reference(xml_document).expect("should work");

        assert_eq!(geometry_reference.href, "#abc");
    }

    #[test]
    fn test_serialize_geometry_reference() {
        let geometry_reference = GeometryReference::new("#abc".to_string());

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_geometry_reference(
            &geometry_reference,
            &mut xml_fragment_writer,
            CityGmlNamespace::Appearance,
            CityGmlElement::TargetProperty,
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

        assert_eq!(xml, "<app:target>#abc</app:target>");
    }

    #[test]
    fn test_round_trip_geometry_reference() {
        let xml_document = b"<target>#xyz</target>";

        let geometry_reference = deserialize_geometry_reference(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_geometry_reference(
            &geometry_reference,
            &mut xml_fragment_writer,
            CityGmlNamespace::Appearance,
            CityGmlElement::TargetProperty,
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

        let round_tripped = deserialize_geometry_reference(xml.as_bytes()).expect("should work");

        assert_eq!(geometry_reference, round_tripped);
    }
}
