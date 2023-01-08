use crate::error::CitygmlIoError;
use ecitygml_core::{CityFurniture, CitygmlModel, TrafficArea, WallSurface};
use nalgebra::Point3;
use quick_xml::events::Event;
use quick_xml::Reader;
use std::collections::HashMap;
use std::fs;

use crate::parse::{parse_multi_surface, parse_point};
use egml::base::Id;

use std::path::Path;

extern crate quick_xml;
extern crate serde;

pub fn read_from_file(
    path: impl AsRef<Path>,
    _corner_min: &Option<Point3<f64>>,
    _corner_max: &Option<Point3<f64>>,
) -> Result<ecitygml_core::CitygmlModel, CitygmlIoError> {
    let mut citygml_model = CitygmlModel::default();

    let file_content = fs::read_to_string(path)?;
    let mut reader = Reader::from_str(file_content.as_str());
    reader.trim_text(true);

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
                            let value: String =
                                a.decode_and_unescape_value(&reader).unwrap().to_string();
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
                        let point_geometry = parse_point(xml_snippet);
                        let name = String::new();
                        let mut city_furniture = CityFurniture::new(id, name);
                        city_furniture.set_reference_point(point_geometry.ok());
                        citygml_model.push_city_furniture(city_furniture);
                    }
                    b"tran:TrafficArea" => {
                        let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                        let multi_surface_geometry = parse_multi_surface(xml_snippet);

                        let name = String::new();
                        let mut traffic_area = TrafficArea::new(id, name);
                        traffic_area.set_lod2_multi_surface(multi_surface_geometry.ok());
                        citygml_model.push_traffic_area(traffic_area);
                    }
                    b"con:WallSurface" => {
                        let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                        let multi_surface_geometry = parse_multi_surface(xml_snippet);

                        let name = String::new();
                        let mut wall_surface = WallSurface::new(id, name);
                        wall_surface.set_lod2_multi_surface(multi_surface_geometry.ok());
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
