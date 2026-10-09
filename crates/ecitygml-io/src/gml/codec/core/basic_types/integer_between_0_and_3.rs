use crate::Error;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::common::LevelOfDetail;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_lod(xml_document: &[u8]) -> Result<LevelOfDetail, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    loop {
        match reader.read_event()? {
            Event::Text(text) => {
                let value = text.as_ref();
                return lod_from_str(value.trim())
                    .ok_or_else(|| Error::UnknownElementNode(value.trim().to_string()));
            }
            Event::CData(cdata) => {
                let value = cdata.as_ref();
                return lod_from_str(value.trim())
                    .ok_or_else(|| Error::UnknownElementNode(value.trim().to_string()));
            }
            Event::Eof => {
                return Err(Error::ElementNotFound("lod text content".to_string()));
            }
            _ => {}
        }
    }
}

pub fn serialize_lod(
    lod: LevelOfDetail,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
    target_xml_namespace: CityGmlNamespace,
    target_xml_element: CityGmlElement,
) -> Result<(), Error> {
    let value = lod_as_str(lod);

    xml_fragment_writer.write_leaf_element(target_xml_namespace, target_xml_element, value)?;

    Ok(())
}

fn lod_as_str(value: LevelOfDetail) -> &'static str {
    match value {
        LevelOfDetail::Zero => "0",
        LevelOfDetail::One => "1",
        LevelOfDetail::Two => "2",
        LevelOfDetail::Three => "3",
    }
}

fn lod_from_str(value: &str) -> Option<LevelOfDetail> {
    match value {
        "0" => Some(LevelOfDetail::Zero),
        "1" => Some(LevelOfDetail::One),
        "2" => Some(LevelOfDetail::Two),
        "3" => Some(LevelOfDetail::Three),
        _ => None,
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_lod() {
        let xml_document = b"<dem:lod>2</dem:lod>";

        let lod = deserialize_lod(xml_document).expect("should work");

        assert_eq!(lod, LevelOfDetail::Two);
    }

    #[test]
    fn test_deserialize_lod_rejects_unknown_value() {
        let xml_document = b"<dem:lod>4</dem:lod>";

        let result = deserialize_lod(xml_document);

        assert!(result.is_err());
    }

    #[test]
    fn test_serialize_lod() {
        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);

        serialize_lod(
            LevelOfDetail::Three,
            &mut xml_fragment_writer,
            CityGmlNamespace::Relief,
            CityGmlElement::LodProperty,
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

        assert_eq!(xml, "<dem:lod>3</dem:lod>");
    }

    #[test]
    fn test_round_trip_lod() {
        let xml_document = b"<dem:lod>0</dem:lod>";

        let lod = deserialize_lod(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_lod(
            lod,
            &mut xml_fragment_writer,
            CityGmlNamespace::Relief,
            CityGmlElement::LodProperty,
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

        let round_tripped = deserialize_lod(xml.as_bytes()).expect("should work");

        assert_eq!(lod, round_tripped);
    }
}
