use crate::error::Error;

use egml::geometry::{DirectPosition, MultiSurface, Solid};
use log::warn;

use quick_xml::events::Event;
use quick_xml::Reader;

#[derive(Debug, Clone, PartialEq, Default)]
pub struct ParsedGeometries {
    pub lod1_solid: Option<Solid>,
    pub lod2_solid: Option<Solid>,
    pub lod3_solid: Option<Solid>,
    pub lod0_multi_surface: Option<MultiSurface>,
    pub lod1_multi_surface: Option<MultiSurface>,
    pub lod2_multi_surface: Option<MultiSurface>,
    pub lod3_multi_surface: Option<MultiSurface>,
}

pub fn parse_geometries(xml_document: &String) -> Result<ParsedGeometries, Error> {
    let mut reader = Reader::from_str(xml_document.as_str());
    reader.config_mut().trim_text_start = true;
    reader.config_mut().trim_text_end = true;

    let mut txt = Vec::new();
    let mut buf = Vec::new();

    let mut parsed_geometries = ParsedGeometries::default();
    loop {
        match reader.read_event_into(&mut buf) {
            Ok(Event::Start(e)) => match e.name().as_ref() {
                b"lod1Solid" => {
                    let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                    parsed_geometries.lod1_solid = Some(egml::io::parse_solid(&xml_snippet)?);
                }
                b"lod2Solid" => {
                    let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                    parsed_geometries.lod2_solid = Some(egml::io::parse_solid(&xml_snippet)?);
                }
                b"lod0MultiSurface" => {
                    let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                    parsed_geometries.lod0_multi_surface =
                        Some(egml::io::parse_multi_surface(&xml_snippet)?);
                }
                b"lod1MultiSurface" => {
                    let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                    parsed_geometries.lod1_multi_surface =
                        Some(egml::io::parse_multi_surface(&xml_snippet)?);
                }
                b"lod2MultiSurface" => {
                    let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                    parsed_geometries.lod2_multi_surface =
                        Some(egml::io::parse_multi_surface(&xml_snippet)?);
                }
                b"lod3MultiSurface" => {
                    let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                    match egml::io::parse_multi_surface(&xml_snippet) {
                        Ok(lod3_multi_surface) => {
                            parsed_geometries.lod3_multi_surface = Some(lod3_multi_surface);
                        }
                        Err(e) => {
                            warn!(
                                "lod3MultiSurface contains invalid geometry: {}",
                                e.to_string()
                            )
                        }
                    }
                }
                _ => {}
            },
            Ok(Event::Eof) => break,
            Err(e) => panic!("Error at position {}: {:?}", reader.buffer_position(), e),
            Ok(Event::Text(e)) => txt.push(e.unescape().unwrap().into_owned()),
            _ => (),
        }
    }

    Ok(parsed_geometries)
}

// TODO: also move into parse geometries fn
pub fn parse_reference_point(xml_document: &String) -> Result<Option<DirectPosition>, Error> {
    let mut reader = Reader::from_str(xml_document.as_str());
    reader.config_mut().trim_text_start = true;
    reader.config_mut().trim_text_end = true;

    let mut txt = Vec::new();
    let mut buf = Vec::new();
    loop {
        match reader.read_event_into(&mut buf) {
            Ok(Event::Start(e)) => match e.name().as_ref() {
                b"referencePoint" => {
                    let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                    let direct_position = egml::io::parse_point(&xml_snippet)?;
                    return Ok(Some(direct_position));
                }
                _ => {}
            },
            Ok(Event::Eof) => break,
            Err(e) => panic!("Error at position {}: {:?}", reader.buffer_position(), e),
            Ok(Event::Text(e)) => txt.push(e.unescape().unwrap().into_owned()),
            _ => (),
        }
    }

    Ok(None)
}
