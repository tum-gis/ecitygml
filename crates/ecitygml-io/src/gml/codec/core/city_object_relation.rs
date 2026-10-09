use crate::Error;
use crate::gml::codec::generics::generic_attribute_set::read_nested_element_index;
use crate::gml::codec::generics::{deserialize_generic_attribute, serialize_generic_attribute};
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::core::CityObjectRelation;
use ecitygml_core::model::core::values::RelationTypeValue;
use ecitygml_core::model::generics::GenericAttributeKind;
use egml::io::codec::base::{deserialize_reference, serialize_reference};
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use egml::model::base::Reference;
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_city_object_relation(xml_document: &[u8]) -> Result<CityObjectRelation, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    // Consume the root `<CityObjectRelation>` element's own start tag.
    loop {
        match reader.read_event()? {
            Event::Start(_) => break,
            Event::Eof => {
                return Err(Error::ElementNotFound("CityObjectRelation".to_string()));
            }
            _ => {}
        }
    }

    let mut relation_type: Option<RelationTypeValue> = None;
    let mut related_to: Option<Reference> = None;
    let mut generic_attributes: Vec<GenericAttributeKind> = Vec::new();

    loop {
        match reader.read_event()? {
            Event::Start(start) => match start.local_name().as_ref() {
                "relationType" => {
                    let pos_start = reader.buffer_position() as usize - start.len() - 2;
                    reader.read_to_end(start.name())?;
                    let pos_end = reader.buffer_position() as usize;
                    relation_type = Some(RelationTypeValue::from(deserialize_code(
                        &xml_document[pos_start..pos_end],
                    )?));
                }
                "relatedTo" => {
                    let pos_start = reader.buffer_position() as usize - start.len() - 2;
                    reader.read_to_end(start.name())?;
                    let pos_end = reader.buffer_position() as usize;
                    related_to = Some(deserialize_reference(&xml_document[pos_start..pos_end])?);
                }
                "genericAttribute" => {
                    let (pos_start, pos_end) = read_nested_element_index(&mut reader)?;
                    generic_attributes.push(deserialize_generic_attribute(
                        &xml_document[pos_start..pos_end],
                    )?);
                    reader.read_to_end(start.name())?;
                }
                _ => {
                    reader.read_to_end(start.name())?;
                }
            },
            Event::Empty(start) if start.local_name().as_ref() == "relatedTo" => {
                let pos_start = reader.buffer_position() as usize - start.len() - 3;
                let pos_end = reader.buffer_position() as usize;
                related_to = Some(deserialize_reference(&xml_document[pos_start..pos_end])?);
            }
            Event::Eof => break,
            _ => {}
        }
    }

    let relation_type =
        relation_type.ok_or_else(|| Error::ElementNotFound("relationType".to_string()))?;
    let related_to = related_to.ok_or_else(|| Error::ElementNotFound("relatedTo".to_string()))?;

    let mut relation = CityObjectRelation::new(relation_type, related_to);
    relation.set_generic_attributes(generic_attributes);

    Ok(relation)
}

pub fn serialize_city_object_relation(
    relation: &CityObjectRelation,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    xml_fragment_writer
        .write_start_event(CityGmlNamespace::Core, CityGmlElement::CityObjectRelation)?;

    for generic_attribute in relation.generic_attributes() {
        xml_fragment_writer.write_start_event(
            CityGmlNamespace::Core,
            CityGmlElement::GenericAttributeProperty,
        )?;
        serialize_generic_attribute(generic_attribute, xml_fragment_writer)?;
        xml_fragment_writer.write_end_event(
            CityGmlNamespace::Core,
            CityGmlElement::GenericAttributeProperty,
        )?;
    }

    serialize_code(
        relation.relation_type().code(),
        xml_fragment_writer,
        CityGmlNamespace::Core,
        CityGmlElement::RelationTypeProperty,
    )?;

    serialize_reference(
        relation.relation_to(),
        xml_fragment_writer,
        CityGmlNamespace::Core,
        CityGmlElement::RelatedToProperty,
    )?;

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::Core, CityGmlElement::CityObjectRelation)?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;
    use egml::model::base::HasAssociationAttributes;
    use egml::model::xlink::HRef;

    fn full_xml() -> &'static str {
        "<CityObjectRelation>\
          <genericAttribute>\
            <StringAttribute>\
              <name>identifier_roadObjectId</name>\
              <value>4970002</value>\
            </StringAttribute>\
          </genericAttribute>\
          <genericAttribute>\
            <StringAttribute>\
              <name>identifier_roadObjectName</name>\
              <value>tree</value>\
            </StringAttribute>\
          </genericAttribute>\
          <genericAttribute>\
            <StringAttribute>\
              <name>identifier_roadId</name>\
              <value>1970000</value>\
            </StringAttribute>\
          </genericAttribute>\
          <relationType>relatedVegetation</relationType>\
          <relatedTo href=\"#UUID_e8b543d5-43f3-3b07-94ee-c8e76419b29f\"/>\
        </CityObjectRelation>"
    }

    #[test]
    fn test_convert_to_city_object_relation() {
        let relation =
            deserialize_city_object_relation(full_xml().as_bytes()).expect("should convert");

        assert_eq!(relation.relation_type().value(), "relatedVegetation");
        assert_eq!(
            relation.relation_to().href().expect("should have href"),
            &HRef::from("#UUID_e8b543d5-43f3-3b07-94ee-c8e76419b29f")
        );
        assert_eq!(relation.generic_attributes().len(), 3);
    }

    #[test]
    fn test_generic_attribute_names() {
        let relation =
            deserialize_city_object_relation(full_xml().as_bytes()).expect("should convert");

        let names: Vec<&str> = relation
            .generic_attributes()
            .iter()
            .map(|a| a.name())
            .collect();

        assert!(names.contains(&"identifier_roadObjectId"));
        assert!(names.contains(&"identifier_roadObjectName"));
        assert!(names.contains(&"identifier_roadId"));
    }

    #[test]
    fn test_deserialize_without_generic_attributes() {
        let xml = "<CityObjectRelation>\
          <relationType>adjecent</relationType>\
          <relatedTo href=\"#UUID_abc123\"/>\
        </CityObjectRelation>";

        let relation = deserialize_city_object_relation(xml.as_bytes()).expect("should convert");

        assert_eq!(relation.relation_type().value(), "adjecent");
        assert_eq!(
            relation.relation_to().href().expect("should have an href"),
            &HRef::from("#UUID_abc123")
        );
        assert!(relation.generic_attributes().is_empty());
    }

    #[test]
    fn test_missing_relation_type_returns_error() {
        let xml = "<CityObjectRelation>\
          <relatedTo href=\"#UUID_abc123\"/>\
        </CityObjectRelation>";

        let result = deserialize_city_object_relation(xml.as_bytes());
        assert!(result.is_err());
    }

    #[test]
    fn test_missing_related_to_returns_error() {
        let xml = "<CityObjectRelation>\
          <relationType>adjecent</relationType>\
        </CityObjectRelation>";

        let result = deserialize_city_object_relation(xml.as_bytes());
        assert!(result.is_err());
    }

    #[test]
    fn test_round_trip() {
        let relation =
            deserialize_city_object_relation(full_xml().as_bytes()).expect("should convert");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_city_object_relation(&relation, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        let round_tripped =
            deserialize_city_object_relation(xml.as_bytes()).expect("should round trip");

        assert_eq!(relation.relation_type(), round_tripped.relation_type());
        assert_eq!(relation.relation_to(), round_tripped.relation_to());
        assert_eq!(
            relation.generic_attributes().len(),
            round_tripped.generic_attributes().len()
        );
    }
}
