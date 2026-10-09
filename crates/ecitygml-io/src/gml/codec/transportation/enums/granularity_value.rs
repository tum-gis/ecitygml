use crate::Error;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::transportation::enums::GranularityValue;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_granularity_value(xml_document: &[u8]) -> Result<GranularityValue, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    loop {
        match reader.read_event()? {
            Event::Text(text) => {
                let value = text.as_ref();
                return granularity_value_from_str(value.trim())
                    .ok_or_else(|| Error::UnknownElementNode(value.trim().to_string()));
            }
            Event::CData(cdata) => {
                let value = cdata.as_ref();
                return granularity_value_from_str(value.trim())
                    .ok_or_else(|| Error::UnknownElementNode(value.trim().to_string()));
            }
            Event::Eof => {
                return Err(Error::ElementNotFound(
                    "granularity text content".to_string(),
                ));
            }
            _ => {}
        }
    }
}

pub fn serialize_granularity_value(
    granularity: &GranularityValue,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
    target_xml_namespace: CityGmlNamespace,
    target_xml_element: CityGmlElement,
) -> Result<(), Error> {
    let value = granularity_value_as_str(granularity);

    xml_fragment_writer.write_leaf_element(target_xml_namespace, target_xml_element, value)?;

    Ok(())
}

fn granularity_value_as_str(value: &GranularityValue) -> &'static str {
    match value {
        GranularityValue::Lane => "lane",
        GranularityValue::Way => "way",
    }
}

fn granularity_value_from_str(value: &str) -> Option<GranularityValue> {
    match value {
        "lane" => Some(GranularityValue::Lane),
        "way" => Some(GranularityValue::Way),
        _ => None,
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_granularity_value() {
        let xml_document = b"<granularity>way</granularity>";

        let granularity = deserialize_granularity_value(xml_document).expect("should work");

        assert_eq!(granularity, GranularityValue::Way);
    }

    #[test]
    fn test_deserialize_granularity_value_rejects_unknown_value() {
        let xml_document = b"<granularity>notAValue</granularity>";

        let result = deserialize_granularity_value(xml_document);

        assert!(result.is_err());
    }

    #[test]
    fn test_serialize_granularity_value() {
        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);

        serialize_granularity_value(
            &GranularityValue::Lane,
            &mut xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::GranularityProperty,
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

        assert_eq!(xml, "<tran:granularity>lane</tran:granularity>");
    }

    #[test]
    fn test_round_trip_granularity_value() {
        let xml_document = b"<granularity>way</granularity>";

        let granularity = deserialize_granularity_value(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_granularity_value(
            &granularity,
            &mut xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::GranularityProperty,
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

        let round_tripped = deserialize_granularity_value(xml.as_bytes()).expect("should work");

        assert_eq!(granularity, round_tripped);
    }
}
