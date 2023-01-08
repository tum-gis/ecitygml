use crate::error::CitygmlIoError;
use crate::error::CitygmlIoError::ElementNotFound;
use egml::geometry::{DirectPosition, MultiSurface};

use quick_xml::events::Event;
use quick_xml::Reader;

pub fn parse_point(xml_document: String) -> Result<DirectPosition, CitygmlIoError> {
    let mut reader = Reader::from_str(xml_document.as_str());
    reader.trim_text(true);

    let mut txt = Vec::new();
    let mut buf = Vec::new();
    loop {
        match reader.read_event_into(&mut buf) {
            Ok(Event::Start(e)) => match e.name().as_ref() {
                b"referencePoint" => {
                    let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                    let direct_position = egml::io::parse_point(&xml_snippet)?;
                    return Ok(direct_position);
                }
                _ => {}
            },
            Ok(Event::Eof) => break,
            Err(e) => panic!("Error at position {}: {:?}", reader.buffer_position(), e),
            Ok(Event::Text(e)) => txt.push(e.unescape().unwrap().into_owned()),
            _ => (),
        }
    }

    Err(ElementNotFound("point".to_string()))
}

pub fn parse_multi_surface(xml_document: String) -> Result<MultiSurface, CitygmlIoError> {
    let mut reader = Reader::from_str(xml_document.as_str());
    reader.trim_text(true);

    let mut txt = Vec::new();
    let mut buf = Vec::new();
    loop {
        match reader.read_event_into(&mut buf) {
            Ok(Event::Start(e)) => match e.name().as_ref() {
                b"lod2MultiSurface" => {
                    let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                    let multi_surface = egml::io::parse_multi_surface(&xml_snippet)?;
                    return Ok(multi_surface);
                }
                _ => {}
            },
            Ok(Event::Eof) => break,
            Err(e) => panic!("Error at position {}: {:?}", reader.buffer_position(), e),
            Ok(Event::Text(e)) => txt.push(e.unescape().unwrap().into_owned()),
            _ => (),
        }
    }

    Err(ElementNotFound("point".to_string()))
}
