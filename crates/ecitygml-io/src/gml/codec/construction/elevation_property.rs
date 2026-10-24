use crate::Error;
use crate::gml::codec::construction::elevation::{deserialize_elevation, serialize_elevation};
use crate::gml::codec::generics::generic_attribute_set::read_nested_element_index;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::construction::Elevation;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_elevation_property(xml_document: &[u8]) -> Result<Elevation, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    // Consume the property wrapper's own start tag (e.g. `<elevation>`).
    loop {
        match reader.read_event()? {
            Event::Start(_) => break,
            Event::Eof => {
                return Err(Error::ElementNotFound("elevation content".to_string()));
            }
            _ => {}
        }
    }

    let (pos_start, pos_end) = read_nested_element_index(&mut reader)?;
    deserialize_elevation(&xml_document[pos_start..pos_end])
}

pub fn serialize_elevation_property(
    elevation: &Elevation,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
    target_xml_namespace: CityGmlNamespace,
    target_xml_element: CityGmlElement,
) -> Result<(), Error> {
    xml_fragment_writer.write_start_event(target_xml_namespace, target_xml_element)?;
    serialize_elevation(elevation, xml_fragment_writer)?;
    xml_fragment_writer.write_end_event(target_xml_namespace, target_xml_element)?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    const PROPERTY: &[u8] = br#"<con:elevation>
<con:Elevation>
<con:elevationReference>generalGroundSurface</con:elevationReference>
<con:elevationValue srsDimension="1">105.3</con:elevationValue>
</con:Elevation>
</con:elevation>"#;

    #[test]
    fn test_round_trip_elevation_property() {
        let elevation = deserialize_elevation_property(PROPERTY).expect("should work");
        assert_eq!(elevation.elevation_value().coordinates(), &[105.3]);

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_elevation_property(
            &elevation,
            &mut xml_fragment_writer,
            CityGmlNamespace::Construction,
            CityGmlElement::ElevationProperty,
        )
        .expect("should serialize");
        let xml = {
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        };
        assert!(xml.starts_with(b"<con:elevation>"));

        assert_eq!(
            deserialize_elevation_property(&xml).expect("should round trip"),
            elevation
        );
    }
}
