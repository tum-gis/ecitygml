use crate::Error;
use crate::gml::codec::core::qualified_area::{
    deserialize_qualified_area, serialize_qualified_area,
};
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::core::QualifiedArea;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_qualified_area_property(xml_document: &[u8]) -> Result<QualifiedArea, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    // Consume the property wrapper's own start tag (e.g. `<area>`).
    loop {
        match reader.read_event()? {
            Event::Start(_) => break,
            Event::Eof => {
                return Err(Error::ElementNotFound("QualifiedArea content".to_string()));
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
                return deserialize_qualified_area(&xml_document[pos_start..pos_end]);
            }
            Event::Eof => {
                return Err(Error::ElementNotFound("QualifiedArea content".to_string()));
            }
            _ => {}
        }
    }
}

pub fn serialize_qualified_area_property(
    qualified_area: &QualifiedArea,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
    target_xml_namespace: CityGmlNamespace,
    target_xml_element: CityGmlElement,
) -> Result<(), Error> {
    xml_fragment_writer.write_start_event(target_xml_namespace, target_xml_element)?;
    serialize_qualified_area(qualified_area, xml_fragment_writer)?;
    xml_fragment_writer.write_end_event(target_xml_namespace, target_xml_element)?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::core::values::QualifiedAreaTypeValue;
    use egml::io::util::Formatting;
    use egml::model::basic_types::Code;
    use egml::model::measures::Area;

    #[test]
    fn test_deserialize_area_property() {
        let xml_document = b"<area>
    <QualifiedArea>
        <area uom=\"m2\">5.0</area>
        <typeOfArea>RoadArea</typeOfArea>
    </QualifiedArea>
</area>";

        let qualified_area =
            deserialize_qualified_area_property(xml_document).expect("should work");

        assert_eq!(qualified_area.area().value(), 5.0);
        assert_eq!(qualified_area.area().uom(), "m2");
        assert_eq!(qualified_area.type_of_area().code().value(), "RoadArea");
    }

    #[test]
    fn test_serialize_area_property() {
        let qualified_area = QualifiedArea::new(
            Area::new(5.0, "m2"),
            QualifiedAreaTypeValue::from(Code::new("RoadArea")),
        );

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_qualified_area_property(
            &qualified_area,
            &mut xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::AreaProperty,
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

        assert!(xml.contains("QualifiedArea"));
        assert!(xml.contains("uom=\"m2\""));
        assert!(xml.contains("typeOfArea"));
        assert!(xml.contains("RoadArea"));
    }

    #[test]
    fn test_round_trip_area_property() {
        let xml_document = b"<area>
    <QualifiedArea>
        <area uom=\"m2\">5.0</area>
        <typeOfArea>RoadArea</typeOfArea>
    </QualifiedArea>
</area>";

        let qualified_area =
            deserialize_qualified_area_property(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_qualified_area_property(
            &qualified_area,
            &mut xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::AreaProperty,
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
            deserialize_qualified_area_property(xml.as_bytes()).expect("should work");

        assert_eq!(qualified_area, round_tripped);
    }
}
