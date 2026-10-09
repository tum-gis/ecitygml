use crate::Error;
use crate::gml::codec::generics::generic_attribute_set::read_nested_element_index;
use crate::gml::codec::generics::{deserialize_generic_attribute, serialize_generic_attribute};
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::generics::GenericAttributeKind;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_generic_attribute_property(
    xml_document: &[u8],
) -> Result<GenericAttributeKind, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    // Consume the property wrapper's own start tag (e.g. `<genericAttribute>`).
    loop {
        match reader.read_event()? {
            Event::Start(_) => break,
            Event::Eof => {
                return Err(Error::ElementNotFound(
                    "generic attribute content".to_string(),
                ));
            }
            _ => {}
        }
    }

    let (pos_start, pos_end) = read_nested_element_index(&mut reader)?;
    deserialize_generic_attribute(&xml_document[pos_start..pos_end])
}

pub fn serialize_generic_attribute_property(
    generic_attribute: &GenericAttributeKind,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
    target_xml_namespace: CityGmlNamespace,
    target_xml_element: CityGmlElement,
) -> Result<(), Error> {
    xml_fragment_writer.write_start_event(target_xml_namespace, target_xml_element)?;
    serialize_generic_attribute(generic_attribute, xml_fragment_writer)?;
    xml_fragment_writer.write_end_event(target_xml_namespace, target_xml_element)?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::generics::StringAttribute;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_generic_attribute_property() {
        let xml_document = b"<genericAttribute>
    <gen:StringAttribute>
        <gen:name>attribute_name</gen:name>
        <gen:value>1100</gen:value>
    </gen:StringAttribute>
</genericAttribute>";

        let generic_attribute =
            deserialize_generic_attribute_property(xml_document).expect("should work");

        match generic_attribute {
            GenericAttributeKind::StringAttribute(x) => {
                assert_eq!(x.name, "attribute_name");
                assert_eq!(x.value, "1100");
            }
            other => panic!("expected StringAttribute, got {other:?}"),
        }
    }

    #[test]
    fn test_serialize_generic_attribute_property() {
        let generic_attribute = GenericAttributeKind::StringAttribute(StringAttribute {
            name: "attribute_name".to_string(),
            value: "1100".to_string(),
        });

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_generic_attribute_property(
            &generic_attribute,
            &mut xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::GenericAttributeProperty,
        )
        .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("StringAttribute"));
        assert!(xml.contains("attribute_name"));
        assert!(xml.contains("1100"));
    }

    #[test]
    fn test_round_trip_generic_attribute_property() {
        let xml_document = b"<genericAttribute>
    <gen:StringAttribute>
        <gen:name>attribute_name</gen:name>
        <gen:value>1100</gen:value>
    </gen:StringAttribute>
</genericAttribute>";

        let generic_attribute =
            deserialize_generic_attribute_property(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_generic_attribute_property(
            &generic_attribute,
            &mut xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::GenericAttributeProperty,
        )
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
            deserialize_generic_attribute_property(xml.as_bytes()).expect("should work");

        assert_eq!(generic_attribute, round_tripped);
    }
}
