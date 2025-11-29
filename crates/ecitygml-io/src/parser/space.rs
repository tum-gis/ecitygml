use crate::error::Error;
use egml::io::{parse_multi_surface, parse_solid};
use egml::model::base::Id;

use crate::parser::city_object::parse_city_object;
use ecitygml_core::model::core::{ImplicitGeometry, OccupiedSpace, Space, ThematicSurface};
use quick_xml::Reader;
use quick_xml::events::Event;
use tracing::warn;

pub fn parse_space(id: &Id, xml_document: &String) -> Result<Space, Error> {
    let city_object = parse_city_object(id, xml_document)?;
    let mut space = Space::new(city_object);

    let mut reader = Reader::from_str(xml_document.as_str());
    reader.config_mut().trim_text(true);

    let mut txt = Vec::new();
    let mut buf = Vec::new();

    loop {
        match reader.read_event_into(&mut buf) {
            Ok(Event::Start(e)) => match e.name().as_ref() {
                b"lod1Solid" => {
                    let xml_snippet: String = reader.read_text(e.name())?.into_owned();
                    space.lod1_solid = parse_solid(&xml_snippet)
                        .map_err(|e| {
                            warn!(
                                "lod1_solid of feature (id={}) contains invalid geometry: {}",
                                id,
                                e.to_string()
                            );
                        })
                        .ok();
                }
                b"lod2Solid" => {
                    let xml_snippet: String = reader.read_text(e.name())?.into_owned();
                    space.lod2_solid = parse_solid(&xml_snippet)
                        .map_err(|e| {
                            warn!(
                                "lod2_solid of feature (id={}) contains invalid geometry: {}",
                                id,
                                e.to_string()
                            );
                        })
                        .ok();
                }
                b"lod3Solid" => {
                    let xml_snippet: String = reader.read_text(e.name())?.into_owned();
                    space.lod3_solid = parse_solid(&xml_snippet)
                        .map_err(|e| {
                            warn!(
                                "lod3_solid of feature (id={}) contains invalid geometry: {}",
                                id,
                                e.to_string()
                            );
                        })
                        .ok();
                }
                b"lod0MultiSurface" => {
                    let xml_snippet: String = reader.read_text(e.name())?.into_owned();
                    space.lod0_multi_surface = parse_multi_surface(&xml_snippet)
                        .map_err(|e| {
                            warn!(
                                "lod0_multi_surface of feature (id={}) contains invalid geometry: {}",
                                id,
                                e.to_string()
                            );
                        })
                        .ok();
                }
                b"lod2MultiSurface" => {
                    let xml_snippet: String = reader.read_text(e.name())?.into_owned();
                    space.lod2_multi_surface = parse_multi_surface(&xml_snippet)
                        .map_err(|e| {
                            warn!(
                                "lod2_multi_surface of feature (id={}) contains invalid geometry: {}",
                                id,
                                e.to_string()
                            );
                        })
                        .ok();
                }
                b"lod3MultiSurface" => {
                    let xml_snippet: String = reader.read_text(e.name())?.into_owned();
                    space.lod3_multi_surface = parse_multi_surface(&xml_snippet)
                        .map_err(|e| {
                            warn!(
                                "lod3_multi_surface of feature (id={}) contains invalid geometry: {}",
                                id,
                                e.to_string()
                            );
                        })
                        .ok();
                }
                _ => {
                    reader.read_to_end(e.name())?;
                }
            },
            Ok(Event::Eof) => break,
            Err(e) => panic!("Error at position {}: {:?}", reader.buffer_position(), e),
            Ok(Event::Text(e)) => txt.push(e.decode().unwrap().into_owned()),
            _ => (),
        }
    }

    Ok(space)
}

pub fn parse_occupied_space(id: &Id, xml_document: &String) -> Result<OccupiedSpace, Error> {
    let space = parse_space(id, xml_document)?;
    let mut occupied_space = OccupiedSpace::new(space);

    let mut reader = Reader::from_str(xml_document.as_str());
    reader.config_mut().trim_text(true);

    let mut txt = Vec::new();
    let mut buf = Vec::new();

    loop {
        match reader.read_event_into(&mut buf) {
            Ok(Event::Start(e)) => match e.name().as_ref() {
                b"lod1ImplicitRepresentation" => {
                    let xml_snippet: String = reader.read_text(e.name())?.into_owned();
                    occupied_space.lod1_implicit_representation =
                        parse_implicit_geometry(&xml_snippet)
                            .map_err(|e| {
                                warn!(
                                    "lod1_implicit_representation of feature (id={}) contains invalid geometry: {}",
                                    id,
                                    e.to_string()
                                );
                            })
                            .ok();
                }
                b"lod2ImplicitRepresentation" => {
                    let xml_snippet: String = reader.read_text(e.name())?.into_owned();
                    occupied_space.lod2_implicit_representation =
                        parse_implicit_geometry(&xml_snippet)
                            .map_err(|e| {
                                warn!(
                                    "lod2_implicit_representation of feature (id={}) contains invalid geometry: {}",
                                    id,
                                    e.to_string()
                                );
                            })
                            .ok();
                }
                b"lod3ImplicitRepresentation" => {
                    let xml_snippet: String = reader.read_text(e.name())?.into_owned();
                    occupied_space.lod3_implicit_representation =
                        parse_implicit_geometry(&xml_snippet)
                            .map_err(|e| {
                                warn!(
                                    "lod3_implicit_representation of feature (id={}) contains invalid geometry: {}",
                                    id,
                                    e.to_string()
                                );
                            })
                            .ok();
                }
                _ => {
                    reader.read_to_end(e.name())?;
                }
            },
            Ok(Event::Eof) => break,
            Err(e) => panic!("Error at position {}: {:?}", reader.buffer_position(), e),
            Ok(Event::Text(e)) => txt.push(e.decode().unwrap().into_owned()),
            _ => (),
        }
    }

    Ok(occupied_space)
}

pub fn parse_thematic_surface(id: &Id, xml_document: &String) -> Result<ThematicSurface, Error> {
    let city_object = parse_city_object(id, xml_document)?;
    let mut thematic_surface = ThematicSurface::new(city_object);

    let mut reader = Reader::from_str(xml_document.as_str());
    reader.config_mut().trim_text(true);

    let mut txt = Vec::new();
    let mut buf = Vec::new();

    loop {
        match reader.read_event_into(&mut buf) {
            Ok(Event::Start(e)) => match e.name().as_ref() {
                b"lod0MultiSurface" => {
                    let xml_snippet: String = reader.read_text(e.name())?.into_owned();
                    thematic_surface.lod0_multi_surface = parse_multi_surface(&xml_snippet)
                        .map_err(|e| {
                            warn!(
                                "lod0_multi_surface of feature (id={}) contains invalid geometry: {}",
                                id,
                                e.to_string()
                            );
                        })
                        .ok();
                }
                b"lod1MultiSurface" => {
                    let xml_snippet: String = reader.read_text(e.name())?.into_owned();
                    thematic_surface.lod1_multi_surface = parse_multi_surface(&xml_snippet)
                        .map_err(|e| {
                            warn!(
                                "lod1_multi_surface of feature (id={}) contains invalid geometry: {}",
                                id,
                                e.to_string()
                            );
                        })
                        .ok();
                }
                b"lod2MultiSurface" => {
                    let xml_snippet: String = reader.read_text(e.name())?.into_owned();
                    thematic_surface.lod2_multi_surface = parse_multi_surface(&xml_snippet)
                        .map_err(|e| {
                            warn!(
                                "lod2_multi_surface of feature (id={}) contains invalid geometry: {}",
                                id,
                                e.to_string()
                            );
                        })
                        .ok();
                }
                b"lod3MultiSurface" => {
                    let xml_snippet: String = reader.read_text(e.name())?.into_owned();
                    thematic_surface.lod3_multi_surface = parse_multi_surface(&xml_snippet)
                        .map_err(|e| {
                            warn!(
                                "lod3_multi_surface of feature (id={}) contains invalid geometry: {}",id,
                                e.to_string()
                            );
                        })
                        .ok();
                }
                _ => {
                    reader.read_to_end(e.name())?;
                }
            },
            Ok(Event::Eof) => break,
            Err(e) => panic!("Error at position {}: {:?}", reader.buffer_position(), e),
            Ok(Event::Text(e)) => txt.push(e.decode().unwrap().into_owned()),
            _ => (),
        }
    }

    Ok(thematic_surface)
}

pub fn parse_implicit_geometry(xml_document: &String) -> Result<ImplicitGeometry, Error> {
    let mut implicit_geometry = ImplicitGeometry::default();

    let mut reader = Reader::from_str(xml_document.as_str());
    reader.config_mut().trim_text(true);

    let mut txt = Vec::new();
    let mut buf = Vec::new();
    loop {
        match reader.read_event_into(&mut buf) {
            Ok(Event::Start(e)) => {
                if e.name().as_ref() == b"referencePoint" {
                    let xml_snippet = reader.read_text(e.name())?.into_owned();
                    implicit_geometry.reference_point =
                        egml::io::parse_point(xml_snippet.as_bytes())?;
                }
            }
            Ok(Event::Eof) => break,
            Err(e) => panic!("Error at position {}: {:?}", reader.buffer_position(), e),
            Ok(Event::Text(e)) => txt.push(e.decode().unwrap().into_owned()),
            _ => (),
        }
    }

    Ok(implicit_geometry)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_parse_implicit_geometry_basic() {
        let xml_document = String::from(
            "<ImplicitGeometry>
    <transformationMatrix>-0.5894514707536183 -0.8078037903020735 0.0 0.0 0.8078037903020735 -0.5894514707536183 0.0 0.0 0.0 0.0 1.0 0.0 0.0 0.0 0.0 1.0</transformationMatrix>
    <referencePoint>
        <gml:Point>
            <gml:pos srsDimension=\"3\">678298.3706294019 5403791.857383491 366.9430094360463</gml:pos>
        </gml:Point>
    </referencePoint>
</ImplicitGeometry>");

        let generic_attribute = parse_implicit_geometry(&xml_document).expect("should work");

        assert_eq!(generic_attribute.reference_point.x(), 678298.3706294019);
        assert_eq!(generic_attribute.reference_point.y(), 5403791.857383491);
        assert_eq!(generic_attribute.reference_point.z(), 366.9430094360463);
    }
}
