use crate::Error;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::de;

pub fn deserialize_bool(xml_document: &[u8]) -> Result<bool, Error> {
    de::from_reader(xml_document).map_err(Error::from)
}

pub fn serialize_bool(
    value: bool,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
    target_xml_namespace: CityGmlNamespace,
    target_xml_element: CityGmlElement,
) -> Result<(), Error> {
    xml_fragment_writer.write_leaf_element(
        target_xml_namespace,
        target_xml_element,
        &value.to_string(),
    )?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_bool() {
        let xml_document = b"<isMovable>true</isMovable>";

        let value = deserialize_bool(xml_document).expect("should work");

        assert!(value);
    }

    #[test]
    fn test_serialize_bool() {
        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_bool(
            false,
            &mut xml_fragment_writer,
            CityGmlNamespace::Bridge,
            CityGmlElement::IsMovableProperty,
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

        assert_eq!(xml, "<brid:isMovable>false</brid:isMovable>");
    }

    #[test]
    fn test_round_trip_bool() {
        let xml_document = b"<isMovable>true</isMovable>";

        let value = deserialize_bool(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_bool(
            value,
            &mut xml_fragment_writer,
            CityGmlNamespace::Bridge,
            CityGmlElement::IsMovableProperty,
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

        let round_tripped = deserialize_bool(xml.as_bytes()).expect("should work");

        assert_eq!(value, round_tripped);
    }
}
