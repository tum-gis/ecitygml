use crate::Error;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::transportation::enums::TrafficDirectionValue;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_traffic_direction_value(
    xml_document: &[u8],
) -> Result<TrafficDirectionValue, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    loop {
        match reader.read_event()? {
            Event::Text(text) => {
                let value = text.as_ref();
                return traffic_direction_value_from_str(value.trim())
                    .ok_or_else(|| Error::UnknownElementNode(value.trim().to_string()));
            }
            Event::CData(cdata) => {
                let value = cdata.as_ref();
                return traffic_direction_value_from_str(value.trim())
                    .ok_or_else(|| Error::UnknownElementNode(value.trim().to_string()));
            }
            Event::Eof => {
                return Err(Error::ElementNotFound(
                    "trafficDirection text content".to_string(),
                ));
            }
            _ => {}
        }
    }
}

pub fn serialize_traffic_direction_value(
    traffic_direction: &TrafficDirectionValue,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
    target_xml_namespace: CityGmlNamespace,
    target_xml_element: CityGmlElement,
) -> Result<(), Error> {
    let value = traffic_direction_value_as_str(traffic_direction);

    xml_fragment_writer.write_leaf_element(target_xml_namespace, target_xml_element, value)?;

    Ok(())
}

fn traffic_direction_value_as_str(value: &TrafficDirectionValue) -> &'static str {
    match value {
        TrafficDirectionValue::Forwards => "forwards",
        TrafficDirectionValue::Backwards => "backwards",
        TrafficDirectionValue::Both => "both",
    }
}

fn traffic_direction_value_from_str(value: &str) -> Option<TrafficDirectionValue> {
    match value {
        "forwards" => Some(TrafficDirectionValue::Forwards),
        "backwards" => Some(TrafficDirectionValue::Backwards),
        "both" => Some(TrafficDirectionValue::Both),
        _ => None,
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_traffic_direction_value() {
        let xml_document = b"<trafficDirection>backwards</trafficDirection>";

        let traffic_direction =
            deserialize_traffic_direction_value(xml_document).expect("should work");

        assert_eq!(traffic_direction, TrafficDirectionValue::Backwards);
    }

    #[test]
    fn test_deserialize_traffic_direction_value_rejects_unknown_value() {
        let xml_document = b"<trafficDirection>sideways</trafficDirection>";

        let result = deserialize_traffic_direction_value(xml_document);

        assert!(result.is_err());
    }

    #[test]
    fn test_serialize_traffic_direction_value() {
        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);

        serialize_traffic_direction_value(
            &TrafficDirectionValue::Both,
            &mut xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::TrafficDirectionProperty,
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

        assert_eq!(xml, "<tran:trafficDirection>both</tran:trafficDirection>");
    }

    #[test]
    fn test_round_trip_traffic_direction_value() {
        let xml_document = b"<trafficDirection>forwards</trafficDirection>";

        let traffic_direction =
            deserialize_traffic_direction_value(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_traffic_direction_value(
            &traffic_direction,
            &mut xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::TrafficDirectionProperty,
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
            deserialize_traffic_direction_value(xml.as_bytes()).expect("should work");

        assert_eq!(traffic_direction, round_tripped);
    }
}
