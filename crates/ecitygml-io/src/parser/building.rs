use crate::parser::attributes::extract_attributes;
use crate::parser::space::{parse_occupied_space, parse_space, parse_thematic_surface};
use crate::Error;
use ecitygml_core::model::building::Building;
use ecitygml_core::model::construction::{
    DoorSurface, GroundSurface, RoofSurface, WallSurface, WindowSurface,
};
use egml::model::base::Id;
use quick_xml::events::Event;
use quick_xml::Reader;
use std::collections::HashMap;

pub fn parse_building(id: &Id, xml_document: &String) -> Result<Building, Error> {
    let mut building = Building::new(id.clone());
    // todo: building.occupied_space = parse_occupied_space(&xml_document)?;

    let mut reader = Reader::from_str(xml_document.as_str());
    reader.config_mut().trim_text_start = true;
    reader.config_mut().trim_text_end = true;

    let mut txt = Vec::new();
    let mut buf = Vec::new();

    loop {
        match reader.read_event_into(&mut buf) {
            Ok(Event::Start(e)) => {
                let extracted_attributes: HashMap<String, String> = extract_attributes(&reader, &e);
                let id: Option<Id> = extracted_attributes
                    .get("id")
                    .map(|x| Id::try_from(x.as_str()).ok())
                    .flatten();

                match e.name().as_ref() {
                    b"con:WallSurface" => {
                        let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                        let id: Id = id.unwrap_or(Id::from_hashed_string(&xml_snippet));

                        let wall_surface = parse_wall_surface(&id, &xml_snippet)?;
                        building.wall_surface.push(wall_surface);
                    }
                    b"con:RoofSurface" => {
                        let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                        let id: Id = id.unwrap_or(Id::from_hashed_string(&xml_snippet));

                        let thematic_surface = parse_thematic_surface(&id, &xml_snippet)?;
                        let roof_surface = RoofSurface::new(thematic_surface);
                        building.roof_surface.push(roof_surface);
                    }
                    b"con:GroundSurface" => {
                        let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                        let id: Id = id.unwrap_or(Id::from_hashed_string(&xml_snippet));

                        let thematic_surface = parse_thematic_surface(&id, &xml_snippet)?;
                        let ground_surface = GroundSurface::new(thematic_surface);
                        building.ground_surface.push(ground_surface);
                    }
                    _ => {}
                }
            }
            Ok(Event::Eof) => break,
            Err(e) => panic!("Error at position {}: {:?}", reader.buffer_position(), e),
            Ok(Event::Text(e)) => txt.push(e.unescape().unwrap().into_owned()),
            _ => (),
        }
    }

    Ok(building)
}

pub fn parse_wall_surface(id: &Id, xml_document: &String) -> Result<WallSurface, Error> {
    let thematic_surface = parse_thematic_surface(&id, &xml_document)?;
    let mut wall_surface = WallSurface::new(thematic_surface);

    let mut reader = Reader::from_str(xml_document.as_str());
    reader.config_mut().trim_text_start = true;
    reader.config_mut().trim_text_end = true;

    let mut txt = Vec::new();
    let mut buf = Vec::new();

    loop {
        match reader.read_event_into(&mut buf) {
            Ok(Event::Start(e)) => {
                let extracted_attributes: HashMap<String, String> = extract_attributes(&reader, &e);
                let id: Option<Id> = extracted_attributes
                    .get("id")
                    .map(|x| Id::try_from(x.as_str()).ok())
                    .flatten();

                match e.name().as_ref() {
                    b"con:WindowSurface" => {
                        let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                        let id: Id = id.unwrap_or(Id::from_hashed_string(&xml_snippet));

                        let occupied_space = parse_occupied_space(&id, &xml_snippet)?;
                        let window_surface = WindowSurface::new(occupied_space);
                        wall_surface.window_surface.push(window_surface);
                    }
                    b"con:DoorSurface" => {
                        let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                        let id: Id = id.unwrap_or(Id::from_hashed_string(&xml_snippet));

                        let occupied_space = parse_occupied_space(&id, &xml_snippet)?;
                        let door_surface = DoorSurface::new(occupied_space);
                        wall_surface.door_surface.push(door_surface);
                    }
                    _ => {}
                }
            }
            Ok(Event::Eof) => break,
            Err(e) => panic!("Error at position {}: {:?}", reader.buffer_position(), e),
            Ok(Event::Text(e)) => txt.push(e.unescape().unwrap().into_owned()),
            _ => (),
        }
    }

    Ok(wall_surface)
}
