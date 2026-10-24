use crate::Error;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::de;

pub fn deserialize_f64(xml_document: &[u8]) -> Result<f64, Error> {
    de::from_reader(xml_document).map_err(Error::from)
}

pub fn serialize_f64(
    value: f64,
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

    fn serialized(value: f64) -> String {
        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_f64(
            value,
            &mut xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::SortKeyProperty,
        )
        .expect("should serialize");
        String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string")
    }

    #[test]
    fn test_deserialize_f64() {
        assert_eq!(
            deserialize_f64(b"<sortKey>1</sortKey>").expect("should work"),
            1.0
        );
        assert_eq!(
            deserialize_f64(b"<sortKey>-2.5e1</sortKey>").expect("should work"),
            -25.0
        );
    }

    #[test]
    fn test_deserialize_f64_rejects_non_numbers() {
        assert!(deserialize_f64(b"<sortKey>first</sortKey>").is_err());
    }

    #[test]
    fn test_serialize_f64() {
        assert_eq!(serialized(2.5), "<bldg:sortKey>2.5</bldg:sortKey>");
    }

    #[test]
    fn test_round_trip_f64() {
        let value = 0.1 + 0.2;
        let round_tripped = deserialize_f64(serialized(value).as_bytes()).expect("should work");

        assert_eq!(value, round_tripped);
    }
}
