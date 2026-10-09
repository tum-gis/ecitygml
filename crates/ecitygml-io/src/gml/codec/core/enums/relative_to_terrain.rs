use crate::Error;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::core::enums::RelativeToTerrain;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_relative_to_terrain(xml_document: &[u8]) -> Result<RelativeToTerrain, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    loop {
        match reader.read_event()? {
            Event::Text(text) => {
                let value = text.as_ref();
                return relative_to_terrain_from_str(value.trim())
                    .ok_or_else(|| Error::UnknownElementNode(value.trim().to_string()));
            }
            Event::CData(cdata) => {
                let value = cdata.as_ref();
                return relative_to_terrain_from_str(value.trim())
                    .ok_or_else(|| Error::UnknownElementNode(value.trim().to_string()));
            }
            Event::Eof => {
                return Err(Error::ElementNotFound(
                    "relativeToTerrain text content".to_string(),
                ));
            }
            _ => {}
        }
    }
}

pub fn serialize_relative_to_terrain(
    relative_to_terrain: RelativeToTerrain,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
    target_xml_namespace: CityGmlNamespace,
    target_xml_element: CityGmlElement,
) -> Result<(), Error> {
    let value = relative_to_terrain_as_str(relative_to_terrain);
    xml_fragment_writer.write_leaf_element(target_xml_namespace, target_xml_element, value)?;

    Ok(())
}

fn relative_to_terrain_as_str(value: RelativeToTerrain) -> &'static str {
    match value {
        RelativeToTerrain::EntirelyAboveTerrain => "entirelyAboveTerrain",
        RelativeToTerrain::SubstantiallyAboveTerrain => "substantiallyAboveTerrain",
        RelativeToTerrain::SubstantiallyAboveAndBelowTerrain => "substantiallyAboveAndBelowTerrain",
        RelativeToTerrain::SubstantiallyBelowTerrain => "substantiallyBelowTerrain",
        RelativeToTerrain::EntirelyBelowTerrain => "entirelyBelowTerrain",
    }
}

fn relative_to_terrain_from_str(value: &str) -> Option<RelativeToTerrain> {
    match value {
        "entirelyAboveTerrain" => Some(RelativeToTerrain::EntirelyAboveTerrain),
        "substantiallyAboveTerrain" => Some(RelativeToTerrain::SubstantiallyAboveTerrain),
        "substantiallyAboveAndBelowTerrain" => {
            Some(RelativeToTerrain::SubstantiallyAboveAndBelowTerrain)
        }
        "substantiallyBelowTerrain" => Some(RelativeToTerrain::SubstantiallyBelowTerrain),
        "entirelyBelowTerrain" => Some(RelativeToTerrain::EntirelyBelowTerrain),
        _ => None,
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_relative_to_terrain() {
        let xml_document = b"<relativeToTerrain>entirelyAboveTerrain</relativeToTerrain>";

        let value = deserialize_relative_to_terrain(xml_document).expect("should work");

        assert_eq!(value, RelativeToTerrain::EntirelyAboveTerrain);
    }

    #[test]
    fn test_deserialize_relative_to_terrain_rejects_unknown_value() {
        let xml_document = b"<relativeToTerrain>notAValue</relativeToTerrain>";

        let result = deserialize_relative_to_terrain(xml_document);

        assert!(result.is_err());
    }

    #[test]
    fn test_serialize_relative_to_terrain() {
        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);

        serialize_relative_to_terrain(
            RelativeToTerrain::SubstantiallyBelowTerrain,
            &mut xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::RelativeToTerrainProperty,
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
            "<relativeToTerrain>substantiallyBelowTerrain</relativeToTerrain>"
        );
    }

    #[test]
    fn test_round_trip_relative_to_terrain() {
        let xml_document =
            b"<relativeToTerrain>substantiallyAboveAndBelowTerrain</relativeToTerrain>";

        let value = deserialize_relative_to_terrain(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_relative_to_terrain(
            value,
            &mut xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::RelativeToTerrainProperty,
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

        let round_tripped = deserialize_relative_to_terrain(xml.as_bytes()).expect("should work");

        assert_eq!(value, round_tripped);
    }
}
