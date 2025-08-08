use crate::error::Error;

use quick_xml::Reader;
use quick_xml::events::Event;
use std::collections::HashMap;

use crate::parser::building::parse_building;
use crate::parser::space::parse_occupied_space;
use crate::parser::transportation::parse_road;
use crate::parser::util::extract_xml_element_attributes;
use ecitygml_core::model::city_furniture::CityFurniture;
use ecitygml_core::model::city_model::CitygmlModel;
use ecitygml_core::model::solitary_vegetation_object::SolitaryVegetationObject;
use egml::model::base::Id;
use std::io::{BufReader, Read, Seek};

extern crate quick_xml;
extern crate serde;

pub fn read_from_file<R: Read + Seek>(reader: R) -> Result<CitygmlModel, Error> {
    let mut citygml_model = CitygmlModel::default();

    // TODO: improve
    let mut file_content: String = Default::default();
    BufReader::new(reader).read_to_string(&mut file_content)?;
    let mut reader = Reader::from_str(file_content.as_str());
    reader.config_mut().trim_text(true);

    let _count = 0;
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
                    b"bldg:Building" => {
                        let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                        let id: Id = id.unwrap_or(Id::from_hashed_string(&xml_snippet));

                        let building = parse_building(&id, &xml_snippet)?;

                        citygml_model.building.push(building);
                    }
                    b"frn:CityFurniture" => {
                        let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                        let id: Id = id.unwrap_or(Id::from_hashed_string(&xml_snippet));

                        let occupied_space = parse_occupied_space(&id, &xml_snippet)?;
                        let city_furniture = CityFurniture::new(occupied_space);
                        citygml_model.city_furniture.push(city_furniture);
                    }
                    b"tran:Road" => {
                        let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                        let id: Id = id.unwrap_or(Id::from_hashed_string(&xml_snippet));

                        let road = parse_road(&id, &xml_snippet)?;
                        citygml_model.road.push(road);
                    }
                    b"veg:SolitaryVegetationObject" => {
                        let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                        let id: Id = id.unwrap_or(Id::from_hashed_string(&xml_snippet));

                        let occupied_space = parse_occupied_space(&id, &xml_snippet)?;
                        let solitary_vegetation_object =
                            SolitaryVegetationObject::new(occupied_space);
                        citygml_model
                            .solitary_vegetation_object
                            .push(solitary_vegetation_object);
                    }

                    _ => (),
                }
            }
            Ok(Event::Eof) => break,
            Err(e) => panic!("Error at position {}: {:?}", reader.buffer_position(), e),
            Ok(Event::Text(e)) => txt.push(e.decode().unwrap().into_owned()),
            _ => (),
        }

        buf.clear();
    }

    Ok(citygml_model)
}
