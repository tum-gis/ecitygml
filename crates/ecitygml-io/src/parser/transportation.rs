use crate::Error;
use crate::parser::space::{parse_space, parse_thematic_surface};
use crate::parser::util::extract_xml_element_attributes;
use ecitygml_core::model::transportation::{
    AuxiliaryTrafficArea, AuxiliaryTrafficSpace, Intersection, Road, Section, TrafficArea,
    TrafficSpace,
};
use egml::model::base::Id;
use quick_xml::Reader;
use quick_xml::events::Event;
use std::collections::HashMap;

pub fn parse_road(id: &Id, xml_document: &String) -> Result<Road, Error> {
    let space = parse_space(id, xml_document)?;
    let mut road = Road::new(space);

    let mut reader = Reader::from_str(xml_document.as_str());
    reader.config_mut().trim_text(true);

    let mut txt = Vec::new();
    let mut buf = Vec::new();

    loop {
        match reader.read_event_into(&mut buf) {
            Ok(Event::Start(e)) => {
                let extracted_attributes: HashMap<String, String> =
                    extract_xml_element_attributes(&reader, &e);
                let id: Option<Id> = extracted_attributes
                    .get("id")
                    .and_then(|x| Id::try_from(x.as_str()).ok());

                match e.name().as_ref() {
                    b"tran:Section" => {
                        let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                        let id: Id = id.unwrap_or(Id::from_hashed_string(&xml_snippet));

                        let section = parse_section(&id, &xml_snippet)?;
                        road.section.push(section);
                    }
                    b"tran:Intersection" => {
                        let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                        let id: Id = id.unwrap_or(Id::from_hashed_string(&xml_snippet));

                        let intersection = parse_intersection(&id, &xml_snippet)?;
                        road.intersection.push(intersection);
                    }
                    _ => {}
                }
            }
            Ok(Event::Eof) => break,
            Err(e) => panic!("Error at position {}: {:?}", reader.buffer_position(), e),
            Ok(Event::Text(e)) => txt.push(e.decode().unwrap().into_owned()),
            _ => (),
        }
    }

    Ok(road)
}

pub fn parse_section(id: &Id, xml_document: &String) -> Result<Section, Error> {
    let space = parse_space(id, xml_document)?;
    let mut section = Section::new(space);

    let mut reader = Reader::from_str(xml_document.as_str());
    reader.config_mut().trim_text(true);

    let mut txt = Vec::new();
    let mut buf = Vec::new();

    loop {
        match reader.read_event_into(&mut buf) {
            Ok(Event::Start(e)) => {
                let extracted_attributes: HashMap<String, String> =
                    extract_xml_element_attributes(&reader, &e);
                let id: Option<Id> = extracted_attributes
                    .get("id")
                    .and_then(|x| Id::try_from(x.as_str()).ok());

                match e.name().as_ref() {
                    b"tran:TrafficSpace" => {
                        let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                        let id: Id = id.unwrap_or(Id::from_hashed_string(&xml_snippet));

                        let traffic_space = parse_traffic_space(&id, &xml_snippet)?;
                        section.traffic_space.push(traffic_space);
                    }
                    b"tran:AuxiliaryTrafficSpace" => {
                        let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                        let id: Id = id.unwrap_or(Id::from_hashed_string(&xml_snippet));

                        let auxiliary_traffic_space =
                            parse_auxiliary_traffic_space(&id, &xml_snippet)?;
                        section
                            .auxiliary_traffic_space
                            .push(auxiliary_traffic_space);
                    }
                    _ => {}
                }
            }
            Ok(Event::Eof) => break,
            Err(e) => panic!("Error at position {}: {:?}", reader.buffer_position(), e),
            Ok(Event::Text(e)) => txt.push(e.decode().unwrap().into_owned()),
            _ => (),
        }
    }

    Ok(section)
}

pub fn parse_intersection(id: &Id, xml_document: &String) -> Result<Intersection, Error> {
    let space = parse_space(id, xml_document)?;
    let mut intersection = Intersection::new(space);

    let mut reader = Reader::from_str(xml_document.as_str());
    reader.config_mut().trim_text(true);

    let mut txt = Vec::new();
    let mut buf = Vec::new();

    loop {
        match reader.read_event_into(&mut buf) {
            Ok(Event::Start(e)) => {
                let extracted_attributes: HashMap<String, String> =
                    extract_xml_element_attributes(&reader, &e);
                let id: Option<Id> = extracted_attributes
                    .get("id")
                    .and_then(|x| Id::try_from(x.as_str()).ok());

                match e.name().as_ref() {
                    b"tran:TrafficSpace" => {
                        let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                        let id: Id = id.unwrap_or(Id::from_hashed_string(&xml_snippet));

                        let traffic_space = parse_traffic_space(&id, &xml_snippet)?;
                        intersection.traffic_space.push(traffic_space);
                    }
                    b"tran:AuxiliaryTrafficSpace" => {
                        let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                        let id: Id = id.unwrap_or(Id::from_hashed_string(&xml_snippet));

                        let auxiliary_traffic_space =
                            parse_auxiliary_traffic_space(&id, &xml_snippet)?;
                        intersection
                            .auxiliary_traffic_space
                            .push(auxiliary_traffic_space);
                    }
                    _ => {}
                }
            }
            Ok(Event::Eof) => break,
            Err(e) => panic!("Error at position {}: {:?}", reader.buffer_position(), e),
            Ok(Event::Text(e)) => txt.push(e.decode().unwrap().into_owned()),
            _ => (),
        }
    }

    Ok(intersection)
}

pub fn parse_traffic_space(id: &Id, xml_document: &String) -> Result<TrafficSpace, Error> {
    let space = parse_space(id, xml_document)?;
    let mut traffic_space = TrafficSpace::new(space);

    let mut reader = Reader::from_str(xml_document.as_str());
    reader.config_mut().trim_text(true);

    let mut txt = Vec::new();
    let mut buf = Vec::new();

    loop {
        match reader.read_event_into(&mut buf) {
            Ok(Event::Start(e)) => {
                let extracted_attributes: HashMap<String, String> =
                    extract_xml_element_attributes(&reader, &e);
                let id: Option<Id> = extracted_attributes
                    .get("id")
                    .and_then(|x| Id::try_from(x.as_str()).ok());

                if e.name().as_ref() == b"tran:TrafficArea" {
                    let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                    let id: Id = id.unwrap_or(Id::from_hashed_string(&xml_snippet));

                    let thematic_surface = parse_thematic_surface(&id, &xml_snippet)?;
                    let traffic_area = TrafficArea::new(thematic_surface);
                    traffic_space.traffic_area.push(traffic_area);
                }
            }
            Ok(Event::Eof) => break,
            Err(e) => panic!("Error at position {}: {:?}", reader.buffer_position(), e),
            Ok(Event::Text(e)) => txt.push(e.decode().unwrap().into_owned()),
            _ => (),
        }
    }

    Ok(traffic_space)
}

pub fn parse_auxiliary_traffic_space(
    id: &Id,
    xml_document: &String,
) -> Result<AuxiliaryTrafficSpace, Error> {
    let space = parse_space(id, xml_document)?;
    let mut auxiliary_traffic_space = AuxiliaryTrafficSpace::new(space);

    let mut reader = Reader::from_str(xml_document.as_str());
    reader.config_mut().trim_text(true);

    let mut txt = Vec::new();
    let mut buf = Vec::new();

    loop {
        match reader.read_event_into(&mut buf) {
            Ok(Event::Start(e)) => {
                let extracted_attributes: HashMap<String, String> =
                    extract_xml_element_attributes(&reader, &e);
                let id: Option<Id> = extracted_attributes
                    .get("id")
                    .and_then(|x| Id::try_from(x.as_str()).ok());

                if e.name().as_ref() == b"tran:AuxiliaryTrafficArea" {
                    let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                    let id: Id = id.unwrap_or(Id::from_hashed_string(&xml_snippet));

                    let thematic_surface = parse_thematic_surface(&id, &xml_snippet)?;
                    let auxiliary_traffic_area = AuxiliaryTrafficArea::new(thematic_surface);

                    auxiliary_traffic_space
                        .auxiliary_traffic_area
                        .push(auxiliary_traffic_area);
                }
            }
            Ok(Event::Eof) => break,
            Err(e) => panic!("Error at position {}: {:?}", reader.buffer_position(), e),
            Ok(Event::Text(e)) => txt.push(e.decode().unwrap().into_owned()),
            _ => (),
        }
    }

    Ok(auxiliary_traffic_space)
}
