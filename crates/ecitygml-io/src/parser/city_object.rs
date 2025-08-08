use crate::Error;
use crate::parser::attribute::parse_generic_attribute;
use ecitygml_core::model::core::CityObject;
use egml::model::base::{Gml, Id};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn parse_city_object(id: &Id, xml_document: &String) -> Result<CityObject, Error> {
    let mut gml = Gml::new(id.clone());
    gml.name = vec!["name".to_string()]; // TODO
    let mut city_object = CityObject::new(gml, Vec::new());

    let mut reader = Reader::from_str(xml_document.as_str());
    reader.config_mut().trim_text(true);

    let mut txt = Vec::new();
    let mut buf = Vec::new();

    loop {
        match reader.read_event_into(&mut buf) {
            Ok(Event::Start(e)) => match e.name().as_ref() {
                b"genericAttribute" => {
                    let xml_snippet: String = reader.read_text(e.name()).unwrap().to_string();
                    let generic_attribute = parse_generic_attribute(&xml_snippet).ok();
                    if let Some(generic_attribute) = generic_attribute {
                        city_object.generic_attributes.push(generic_attribute);
                    }
                }
                _ => {
                    reader.read_to_end(e.name()).unwrap();
                }
            },
            Ok(Event::Eof) => break,
            Err(e) => panic!("Error at position {}: {:?}", reader.buffer_position(), e),
            Ok(Event::Text(e)) => txt.push(e.decode().unwrap().into_owned()),
            _ => (),
        }
    }

    Ok(city_object)
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::model::base::Id;

    #[test]
    fn test_parse_city_object_basic() {
        let id = Id::try_from("test-id-123").expect("should work");
        let xml_document = String::from(
            "<genericAttribute>
        <gen:StringAttribute>
          <gen:name>DatenquelleBodenhoehe</gen:name>
          <gen:value>1100</gen:value>
        </gen:StringAttribute>
      </genericAttribute>
      <genericAttribute>
        <gen:StringAttribute>
          <gen:name>DatenquelleDachhoehe</gen:name>
          <gen:value>1000</gen:value>
        </gen:StringAttribute>
      </genericAttribute>",
        );

        let city_object = parse_city_object(&id, &xml_document).expect("should work");

        assert_eq!(city_object.gml.id, id);
        assert_eq!(city_object.generic_attributes.len(), 2);
    }

    #[test]
    fn test_parse_city_object_with_mixed_attributes_xml() {
        let id = Id::try_from("empty-test").expect("should work");
        let xml_document = String::from(
            "
      <genericAttribute>
        <gen:StringAttribute>
          <gen:name>attribute_name_one</gen:name>
          <gen:value>1100</gen:value>
        </gen:StringAttribute>
      </genericAttribute>
      <genericAttribute>
        <gen:IntAttribute>
          <gen:name>attribute_name_two</gen:name>
          <gen:value>1100</gen:value>
        </gen:IntAttribute>
      </genericAttribute>
       <genericAttribute>
        <gen:DoubleAttribute>
          <gen:name>attribute_name_three</gen:name>
          <gen:value>1100</gen:value>
        </gen:DoubleAttribute>
      </genericAttribute>
      ",
        );

        let city_object = parse_city_object(&id, &xml_document).expect("should work");

        assert_eq!(city_object.gml.id, id);
        assert_eq!(city_object.gml.name, vec!["name".to_string()]);
        assert_eq!(city_object.generic_attributes.len(), 3);
    }
}
