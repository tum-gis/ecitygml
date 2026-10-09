use crate::Error;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::core::QualifiedArea;
use ecitygml_core::model::core::values::QualifiedAreaTypeValue;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::codec::measures::{deserialize_area, serialize_area};
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_qualified_area(xml_document: &[u8]) -> Result<QualifiedArea, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    // Consume the root `<QualifiedArea>` element's own start tag.
    loop {
        match reader.read_event()? {
            Event::Start(_) => break,
            Event::Eof => {
                return Err(Error::ElementNotFound("QualifiedArea".to_string()));
            }
            _ => {}
        }
    }

    let mut area = None;
    let mut type_of_area = None;

    loop {
        match reader.read_event()? {
            Event::Start(start) => {
                let pos_start = reader.buffer_position() as usize - start.len() - 2;
                match start.local_name().as_ref() {
                    "area" => {
                        reader.read_to_end(start.name())?;
                        let pos_end = reader.buffer_position() as usize;
                        let mut area_reader =
                            Reader::from_reader(&xml_document[pos_start..pos_end]);
                        area_reader.config_mut().trim_text(true);
                        area = Some(deserialize_area(&mut area_reader)?);
                    }
                    "typeOfArea" => {
                        reader.read_to_end(start.name())?;
                        let pos_end = reader.buffer_position() as usize;
                        type_of_area = Some(deserialize_code(&xml_document[pos_start..pos_end])?);
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

    let area = area.ok_or_else(|| Error::ElementNotFound("area".to_string()))?;
    let type_of_area =
        type_of_area.ok_or_else(|| Error::ElementNotFound("typeOfArea".to_string()))?;

    Ok(QualifiedArea::new(
        area,
        QualifiedAreaTypeValue::from(type_of_area),
    ))
}

pub fn serialize_qualified_area(
    qualified_area: &QualifiedArea,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    xml_fragment_writer.write_start_event(CityGmlNamespace::Core, CityGmlElement::QualifiedArea)?;

    serialize_area(
        qualified_area.area(),
        xml_fragment_writer,
        CityGmlNamespace::Core,
        CityGmlElement::AreaProperty,
    )?;

    serialize_code(
        qualified_area.type_of_area().code(),
        xml_fragment_writer,
        CityGmlNamespace::Core,
        CityGmlElement::TypeOfAreaProperty,
    )?;

    xml_fragment_writer.write_end_event(CityGmlNamespace::Core, CityGmlElement::QualifiedArea)?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;
    use egml::model::basic_types::Code;
    use egml::model::measures::Area;

    #[test]
    fn test_deserialize_qualified_area() {
        let xml_document = b"<QualifiedArea>
    <area uom=\"m2\">5.0</area>
    <typeOfArea>RoadArea</typeOfArea>
</QualifiedArea>";

        let qualified_area = deserialize_qualified_area(xml_document).expect("should work");

        assert_eq!(qualified_area.area().value(), 5.0);
        assert_eq!(qualified_area.area().uom(), "m2");
        assert_eq!(qualified_area.type_of_area().code().value(), "RoadArea");
    }

    #[test]
    fn test_deserialize_qualified_area_with_reversed_field_order() {
        let xml_document = b"<QualifiedArea>
    <typeOfArea>RoadArea</typeOfArea>
    <area uom=\"m2\">5.0</area>
</QualifiedArea>";

        let qualified_area = deserialize_qualified_area(xml_document).expect("should work");

        assert_eq!(qualified_area.area().value(), 5.0);
        assert_eq!(qualified_area.area().uom(), "m2");
        assert_eq!(qualified_area.type_of_area().code().value(), "RoadArea");
    }

    #[test]
    fn test_serialize_qualified_area() {
        let qualified_area = QualifiedArea::new(
            Area::new(5.0, "m2"),
            QualifiedAreaTypeValue::from(Code::new("RoadArea")),
        );

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_qualified_area(&qualified_area, &mut xml_fragment_writer)
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
        assert!(xml.contains("area"));
        assert!(xml.contains("uom=\"m2\""));
        assert!(xml.contains('5'));
        assert!(xml.contains("typeOfArea"));
        assert!(xml.contains("RoadArea"));
    }

    #[test]
    fn test_round_trip_qualified_area() {
        let xml_document = b"<QualifiedArea>
    <area uom=\"m2\">5.0</area>
    <typeOfArea>RoadArea</typeOfArea>
</QualifiedArea>";

        let qualified_area = deserialize_qualified_area(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_qualified_area(&qualified_area, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        let round_tripped = deserialize_qualified_area(xml.as_bytes()).expect("should work");

        assert_eq!(qualified_area, round_tripped);
    }
}
