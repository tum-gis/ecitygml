use crate::Error;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::de;

pub fn deserialize_string(xml_document: &[u8]) -> Result<String, Error> {
    de::from_reader(xml_document).map_err(Error::from)
}

pub fn serialize_string(
    value: &str,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
    target_xml_namespace: CityGmlNamespace,
    target_xml_element: CityGmlElement,
) -> Result<(), Error> {
    xml_fragment_writer.write_leaf_element(target_xml_namespace, target_xml_element, value)?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_string() {
        let xml_document = b"<pcl:pointFile>abc.las</pcl:pointFile>";

        let value = deserialize_string(xml_document).expect("should work");

        assert_eq!(value, "abc.las");
    }

    #[test]
    fn test_serialize_string() {
        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_string(
            "abc.las",
            &mut xml_fragment_writer,
            CityGmlNamespace::PointCloud,
            CityGmlElement::PointFileProperty,
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

        assert_eq!(xml, "<pcl:pointFile>abc.las</pcl:pointFile>");
    }

    #[test]
    fn test_round_trip_string() {
        let xml_document = b"<pointFileSrsName>EPSG:25832</pointFileSrsName>";

        let value = deserialize_string(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_string(
            &value,
            &mut xml_fragment_writer,
            CityGmlNamespace::PointCloud,
            CityGmlElement::PointFileSrsNameProperty,
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

        let round_tripped = deserialize_string(xml.as_bytes()).expect("should work");

        assert_eq!(value, round_tripped);
    }
}
