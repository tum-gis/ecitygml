use crate::error::Error;
use ecitygml_core::{
    CityFurniture, CitygmlModel, SolitaryVegetationObject, TrafficArea, WallSurface,
};

use quick_xml::events::Event;
use quick_xml::Reader;
use std::collections::HashMap;

use std::io::{BufReader, Read, Seek};

use crate::parse::{parse_geometries, parse_reference_point};
use egml::base::Id;

extern crate quick_xml;
extern crate serde;

pub fn read_from_file<R: Read + Seek>(reader: R) -> Result<ecitygml_core::CitygmlModel, Error> {
    let mut citygml_model = CitygmlModel::default();

    // TODO: improve
    let mut file_content: String = Default::default();
    BufReader::new(reader).read_to_string(&mut file_content)?;
    let mut reader = Reader::from_str(file_content.as_str());
    reader.config_mut().trim_text_start = true;
    reader.config_mut().trim_text_end = true;

    let _count = 0;
    let mut txt = Vec::new();
    let mut buf = Vec::new();
    loop {
        match reader.read_event_into(&mut buf) {
            Ok(Event::Start(e)) => {
                let extracted_attributes: HashMap<String, String> = e
                    .attributes()
                    .map(|attr_res| match attr_res {
                        Ok(a) => {
                            let key = reader
                                .decoder()
                                .decode(a.key.local_name().as_ref())
                                .unwrap()
                                .to_string();
                            let value: String = a
                                .decode_and_unescape_value(reader.decoder())
                                .unwrap()
                                .to_string();
                            /*println!(
                                "key: {}, value: {}",
                                reader
                                    .decoder()
                                    .decode(a.key.local_name().as_ref())
                                    .unwrap(),
                                value
                            );*/
                            (key, value)
                        }
                        Err(err) => {
                            dbg!("unable to read key in DefaultSettings, err = {:?}", err);
                            (String::new(), String::new())
                        }
                    })
                    .collect();

                let id: Id = extracted_attributes
                    .get("id")
                    .unwrap_or(&String::new())
                    .to_string()
                    .into();

                match e.name().as_ref() {
                    b"frn:CityFurniture" => {
                        let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();

                        let name = String::new();
                        let mut city_furniture = CityFurniture::new(id, name);

                        let parsed_geometries = parse_geometries(&xml_snippet)?;

                        let point_geometry = parse_reference_point(&xml_snippet)?;
                        city_furniture.set_reference_point(point_geometry);
                        city_furniture.set_lod1_solid(parsed_geometries.lod1_solid);
                        city_furniture.set_lod2_solid(parsed_geometries.lod2_solid);
                        city_furniture.set_lod2_multi_surface(parsed_geometries.lod2_multi_surface);

                        citygml_model.push_city_furniture(city_furniture);
                    }
                    b"tran:TrafficArea" => {
                        let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();

                        let name = String::new();
                        let mut traffic_area = TrafficArea::new(id, name);

                        let parsed_geometries = parse_geometries(&xml_snippet)?;
                        traffic_area.set_lod2_multi_surface(parsed_geometries.lod2_multi_surface);

                        citygml_model.push_traffic_area(traffic_area);
                    }
                    b"veg:SolitaryVegetationObject" => {
                        let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();

                        let name = String::new();
                        let mut solitary_vegetation_object =
                            SolitaryVegetationObject::new(id, name);

                        let parsed_geometries = parse_geometries(&xml_snippet)?;
                        solitary_vegetation_object.set_lod1_solid(parsed_geometries.lod1_solid);

                        citygml_model.push_solitary_vegetation_object(solitary_vegetation_object);
                    }
                    b"con:WallSurface" => {
                        let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();

                        let name = String::new();
                        let mut wall_surface = WallSurface::new(id, name);

                        let parsed_geometries = parse_geometries(&xml_snippet)?;
                        wall_surface.set_lod2_multi_surface(parsed_geometries.lod2_multi_surface);
                        wall_surface.set_lod3_multi_surface(parsed_geometries.lod3_multi_surface);

                        citygml_model.push_wall_surface(wall_surface);
                    }
                    _ => (),
                }
            }
            Ok(Event::Eof) => break,
            Err(e) => panic!("Error at position {}: {:?}", reader.buffer_position(), e),
            Ok(Event::Text(e)) => txt.push(e.unescape().unwrap().into_owned()),
            _ => (),
        }

        buf.clear();
    }

    Ok(citygml_model)
}
