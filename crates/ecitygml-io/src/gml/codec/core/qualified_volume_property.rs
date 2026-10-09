use crate::Error;
use crate::gml::codec::core::qualified_volume::{
    deserialize_qualified_volume, serialize_qualified_volume,
};
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::core::QualifiedVolume;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_qualified_volume_property(
    xml_document: &[u8],
) -> Result<QualifiedVolume, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    // Consume the property wrapper's own start tag (e.g. `<volume>`).
    loop {
        match reader.read_event()? {
            Event::Start(_) => break,
            Event::Eof => {
                return Err(Error::ElementNotFound(
                    "QualifiedVolume content".to_string(),
                ));
            }
            _ => {}
        }
    }

    loop {
        match reader.read_event()? {
            Event::Start(start) => {
                let pos_start = reader.buffer_position() as usize - start.len() - 2;
                reader.read_to_end(start.name())?;
                let pos_end = reader.buffer_position() as usize;
                return deserialize_qualified_volume(&xml_document[pos_start..pos_end]);
            }
            Event::Eof => {
                return Err(Error::ElementNotFound(
                    "QualifiedVolume content".to_string(),
                ));
            }
            _ => {}
        }
    }
}

pub fn serialize_qualified_volume_property(
    qualified_volume: &QualifiedVolume,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
    target_xml_namespace: CityGmlNamespace,
    target_xml_element: CityGmlElement,
) -> Result<(), Error> {
    xml_fragment_writer.write_start_event(target_xml_namespace, target_xml_element)?;
    serialize_qualified_volume(qualified_volume, xml_fragment_writer)?;
    xml_fragment_writer.write_end_event(target_xml_namespace, target_xml_element)?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::core::values::QualifiedVolumeTypeValue;
    use egml::io::util::Formatting;
    use egml::model::basic_types::Code;
    use egml::model::measures::Volume;

    #[test]
    fn test_deserialize_volume_property() {
        let xml_document = b"<volume>
    <QualifiedVolume>
        <volume uom=\"m3\">5.0</volume>
        <typeOfVolume>RoadVolume</typeOfVolume>
    </QualifiedVolume>
</volume>";

        let qualified_volume =
            deserialize_qualified_volume_property(xml_document).expect("should work");

        assert_eq!(qualified_volume.volume().value(), 5.0);
        assert_eq!(qualified_volume.volume().uom(), "m3");
        assert_eq!(
            qualified_volume.type_of_volume().code().value(),
            "RoadVolume"
        );
    }

    #[test]
    fn test_serialize_volume_property() {
        let qualified_volume = QualifiedVolume::new(
            Volume::new(5.0, "m3"),
            QualifiedVolumeTypeValue::from(Code::new("RoadVolume")),
        );

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_qualified_volume_property(
            &qualified_volume,
            &mut xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::VolumeProperty,
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

        assert!(xml.contains("QualifiedVolume"));
        assert!(xml.contains("uom=\"m3\""));
        assert!(xml.contains("typeOfVolume"));
        assert!(xml.contains("RoadVolume"));
    }

    #[test]
    fn test_round_trip_volume_property() {
        let xml_document = b"<volume>
    <QualifiedVolume>
        <volume uom=\"m3\">5.0</volume>
        <typeOfVolume>RoadVolume</typeOfVolume>
    </QualifiedVolume>
</volume>";

        let qualified_volume =
            deserialize_qualified_volume_property(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_qualified_volume_property(
            &qualified_volume,
            &mut xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::VolumeProperty,
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
            deserialize_qualified_volume_property(xml.as_bytes()).expect("should work");

        assert_eq!(qualified_volume, round_tripped);
    }
}
