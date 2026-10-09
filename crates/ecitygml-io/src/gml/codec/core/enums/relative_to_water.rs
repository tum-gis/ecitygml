use crate::Error;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::core::enums::RelativeToWater;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_relative_to_water(xml_document: &[u8]) -> Result<RelativeToWater, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    loop {
        match reader.read_event()? {
            Event::Text(text) => {
                let value = text.as_ref();
                return relative_to_water_from_str(value.trim())
                    .ok_or_else(|| Error::UnknownElementNode(value.trim().to_string()));
            }
            Event::CData(cdata) => {
                let value = cdata.as_ref();
                return relative_to_water_from_str(value.trim())
                    .ok_or_else(|| Error::UnknownElementNode(value.trim().to_string()));
            }
            Event::Eof => {
                return Err(Error::ElementNotFound(
                    "relativeToWater text content".to_string(),
                ));
            }
            _ => {}
        }
    }
}

pub fn serialize_relative_to_water(
    relative_to_water: RelativeToWater,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
    target_xml_namespace: CityGmlNamespace,
    target_xml_element: CityGmlElement,
) -> Result<(), Error> {
    let value = relative_to_water_as_str(relative_to_water);
    xml_fragment_writer.write_leaf_element(target_xml_namespace, target_xml_element, value)?;

    Ok(())
}

fn relative_to_water_as_str(value: RelativeToWater) -> &'static str {
    match value {
        RelativeToWater::EntirelyAboveWaterSurface => "entirelyAboveWaterSurface",
        RelativeToWater::SubstantiallyAboveWaterSurface => "substantiallyAboveWaterSurface",
        RelativeToWater::SubstantiallyAboveAndBelowWaterSurface => {
            "substantiallyAboveAndBelowWaterSurface"
        }
        RelativeToWater::SubstantiallyBelowWaterSurface => "substantiallyBelowWaterSurface",
        RelativeToWater::EntirelyBelowWaterSurface => "entirelyBelowWaterSurface",
        RelativeToWater::TemporarilyAboveAndBelowWaterSurface => {
            "temporarilyAboveAndBelowWaterSurface"
        }
    }
}

fn relative_to_water_from_str(value: &str) -> Option<RelativeToWater> {
    match value {
        "entirelyAboveWaterSurface" => Some(RelativeToWater::EntirelyAboveWaterSurface),
        "substantiallyAboveWaterSurface" => Some(RelativeToWater::SubstantiallyAboveWaterSurface),
        "substantiallyAboveAndBelowWaterSurface" => {
            Some(RelativeToWater::SubstantiallyAboveAndBelowWaterSurface)
        }
        "substantiallyBelowWaterSurface" => Some(RelativeToWater::SubstantiallyBelowWaterSurface),
        "entirelyBelowWaterSurface" => Some(RelativeToWater::EntirelyBelowWaterSurface),
        "temporarilyAboveAndBelowWaterSurface" => {
            Some(RelativeToWater::TemporarilyAboveAndBelowWaterSurface)
        }
        _ => None,
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_relative_to_water() {
        let xml_document = b"<relativeToWater>entirelyAboveWaterSurface</relativeToWater>";

        let value = deserialize_relative_to_water(xml_document).expect("should work");

        assert_eq!(value, RelativeToWater::EntirelyAboveWaterSurface);
    }

    #[test]
    fn test_deserialize_relative_to_water_rejects_unknown_value() {
        let xml_document = b"<relativeToWater>notAValue</relativeToWater>";

        let result = deserialize_relative_to_water(xml_document);

        assert!(result.is_err());
    }

    #[test]
    fn test_serialize_relative_to_water() {
        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);

        serialize_relative_to_water(
            RelativeToWater::SubstantiallyBelowWaterSurface,
            &mut xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::RelativeToWaterProperty,
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

        assert_eq!(
            xml,
            "<relativeToWater>substantiallyBelowWaterSurface</relativeToWater>"
        );
    }

    #[test]
    fn test_round_trip_relative_to_water() {
        let xml_document =
            b"<relativeToWater>temporarilyAboveAndBelowWaterSurface</relativeToWater>";

        let value = deserialize_relative_to_water(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_relative_to_water(
            value,
            &mut xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::RelativeToWaterProperty,
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

        let round_tripped = deserialize_relative_to_water(xml.as_bytes()).expect("should work");

        assert_eq!(value, round_tripped);
    }
}
