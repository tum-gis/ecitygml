use crate::Error;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::core::QualifiedVolume;
use ecitygml_core::model::core::values::QualifiedVolumeTypeValue;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::codec::measures::{deserialize_volume, serialize_volume};
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_qualified_volume(xml_document: &[u8]) -> Result<QualifiedVolume, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    // Consume the root `<QualifiedVolume>` element's own start tag.
    loop {
        match reader.read_event()? {
            Event::Start(_) => break,
            Event::Eof => {
                return Err(Error::ElementNotFound("QualifiedVolume".to_string()));
            }
            _ => {}
        }
    }

    let mut volume = None;
    let mut type_of_volume = None;

    loop {
        match reader.read_event()? {
            Event::Start(start) => {
                let pos_start = reader.buffer_position() as usize - start.len() - 2;
                match start.local_name().as_ref() {
                    "volume" => {
                        reader.read_to_end(start.name())?;
                        let pos_end = reader.buffer_position() as usize;
                        let mut volume_reader =
                            Reader::from_reader(&xml_document[pos_start..pos_end]);
                        volume_reader.config_mut().trim_text(true);
                        volume = Some(deserialize_volume(&mut volume_reader)?);
                    }
                    "typeOfVolume" => {
                        reader.read_to_end(start.name())?;
                        let pos_end = reader.buffer_position() as usize;
                        type_of_volume = Some(deserialize_code(&xml_document[pos_start..pos_end])?);
                    }
                    _ => {
                        reader.read_to_end(start.name())?;
                    }
                }
            }
            Event::Eof => break,
            _ => {}
        }
    }

    let volume = volume.ok_or_else(|| Error::ElementNotFound("volume".to_string()))?;
    let type_of_volume =
        type_of_volume.ok_or_else(|| Error::ElementNotFound("typeOfVolume".to_string()))?;

    Ok(QualifiedVolume::new(
        volume,
        QualifiedVolumeTypeValue::from(type_of_volume),
    ))
}

pub fn serialize_qualified_volume(
    qualified_volume: &QualifiedVolume,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    xml_fragment_writer
        .write_start_event(CityGmlNamespace::Core, CityGmlElement::QualifiedVolume)?;

    serialize_volume(
        qualified_volume.volume(),
        xml_fragment_writer,
        CityGmlNamespace::Core,
        CityGmlElement::VolumeProperty,
    )?;

    serialize_code(
        qualified_volume.type_of_volume().code(),
        xml_fragment_writer,
        CityGmlNamespace::Core,
        CityGmlElement::TypeOfVolumeProperty,
    )?;

    xml_fragment_writer.write_end_event(CityGmlNamespace::Core, CityGmlElement::QualifiedVolume)?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;
    use egml::model::basic_types::Code;
    use egml::model::measures::Volume;

    #[test]
    fn test_deserialize_qualified_volume() {
        let xml_document = b"<QualifiedVolume>
    <volume uom=\"m3\">5.0</volume>
    <typeOfVolume>RoadVolume</typeOfVolume>
</QualifiedVolume>";

        let qualified_volume = deserialize_qualified_volume(xml_document).expect("should work");

        assert_eq!(qualified_volume.volume().value(), 5.0);
        assert_eq!(qualified_volume.volume().uom(), "m3");
        assert_eq!(
            qualified_volume.type_of_volume().code().value(),
            "RoadVolume"
        );
    }

    #[test]
    fn test_deserialize_qualified_volume_with_reversed_field_order() {
        let xml_document = b"<QualifiedVolume>
    <typeOfVolume>RoadVolume</typeOfVolume>
    <volume uom=\"m3\">5.0</volume>
</QualifiedVolume>";

        let qualified_volume = deserialize_qualified_volume(xml_document).expect("should work");

        assert_eq!(qualified_volume.volume().value(), 5.0);
        assert_eq!(qualified_volume.volume().uom(), "m3");
        assert_eq!(
            qualified_volume.type_of_volume().code().value(),
            "RoadVolume"
        );
    }

    #[test]
    fn test_serialize_qualified_volume() {
        let qualified_volume = QualifiedVolume::new(
            Volume::new(5.0, "m3"),
            QualifiedVolumeTypeValue::from(Code::new("RoadVolume")),
        );

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_qualified_volume(&qualified_volume, &mut xml_fragment_writer)
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
        assert!(xml.contains("volume"));
        assert!(xml.contains("uom=\"m3\""));
        assert!(xml.contains('5'));
        assert!(xml.contains("typeOfVolume"));
        assert!(xml.contains("RoadVolume"));
    }

    #[test]
    fn test_round_trip_qualified_volume() {
        let xml_document = b"<QualifiedVolume>
    <volume uom=\"m3\">5.0</volume>
    <typeOfVolume>RoadVolume</typeOfVolume>
</QualifiedVolume>";

        let qualified_volume = deserialize_qualified_volume(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_qualified_volume(&qualified_volume, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        let round_tripped = deserialize_qualified_volume(xml.as_bytes()).expect("should work");

        assert_eq!(qualified_volume, round_tripped);
    }
}
