use crate::Error;
use crate::gml::codec::common::deserialize_string;
use crate::gml::codec::generics::{deserialize_generic_attribute, serialize_generic_attribute};
use crate::gml::util::{CityGmlElement, CityGmlNamespace, DeserializationConfig};
use ecitygml_core::model::generics::{GenericAttributeKind, GenericAttributeSet};
use egml::io::codec::xs::{deserialize_any_uri, serialize_any_uri};
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use egml::model::xs::AnyUri;
use quick_xml::Reader;
use quick_xml::events::Event;
use tracing::warn;

pub fn deserialize_generic_attribute_set(
    xml_document: &[u8],
    config: &DeserializationConfig,
) -> Result<GenericAttributeSet, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    // Consume the root `<gen:GenericAttributeSet>` element's own start tag.
    loop {
        match reader.read_event()? {
            Event::Start(_) => break,
            Event::Eof => {
                return Err(Error::ElementNotFound("GenericAttributeSet".to_string()));
            }
            _ => {}
        }
    }

    let mut name: Option<String> = None;
    let mut code_space: Option<AnyUri> = None;
    let mut generic_attributes: Vec<GenericAttributeKind> = Vec::new();

    loop {
        let start = match reader.read_event()? {
            Event::Start(start) => start,
            Event::Eof => break,
            _ => continue,
        };

        match start.local_name().as_ref() {
            "name" => {
                let pos_start = reader.buffer_position() as usize - start.len() - 2;
                reader.read_to_end(start.name())?;
                let pos_end = reader.buffer_position() as usize;
                name = Some(
                    deserialize_string(&xml_document[pos_start..pos_end])?
                        .trim()
                        .to_string(),
                );
            }
            "codeSpace" => {
                let pos_start = reader.buffer_position() as usize - start.len() - 2;
                reader.read_to_end(start.name())?;
                let pos_end = reader.buffer_position() as usize;
                code_space = Some(deserialize_any_uri(&xml_document[pos_start..pos_end])?);
            }
            "genericAttribute" => {
                let (pos_start, pos_end) = read_nested_element_index(&mut reader)?;
                // An invalid member is dropped and logged instead of failing the whole set.
                match deserialize_generic_attribute(&xml_document[pos_start..pos_end], config) {
                    Ok(attribute) => generic_attributes.push(attribute),
                    Err(error) => warn!(?error, "dropping invalid generic attribute"),
                }
                reader.read_to_end(start.name())?;
            }
            _ => {
                reader.read_to_end(start.name())?;
            }
        }
    }

    Ok(GenericAttributeSet {
        name: name.unwrap_or_default(),
        code_space,
        generic_attributes,
    })
}

/// TODO: remove helper
pub(crate) fn read_nested_element_index(
    reader: &mut Reader<&[u8]>,
) -> Result<(usize, usize), Error> {
    loop {
        match reader.read_event()? {
            Event::Start(start) => {
                let pos_start = reader.buffer_position() as usize - start.len() - 2;
                reader.read_to_end(start.name())?;
                let pos_end = reader.buffer_position() as usize;
                return Ok((pos_start, pos_end));
            }
            Event::End(_) | Event::Eof => {
                return Err(Error::ElementNotFound("nested element content".to_string()));
            }
            _ => {}
        }
    }
}

pub fn serialize_generic_attribute_set(
    generic_attribute_set: &GenericAttributeSet,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    xml_fragment_writer.write_start_event(
        CityGmlNamespace::Generics,
        CityGmlElement::GenericAttributeSet,
    )?;

    xml_fragment_writer.write_leaf_element(
        CityGmlNamespace::Generics,
        CityGmlElement::NameProperty,
        &generic_attribute_set.name,
    )?;

    if let Some(code_space) = &generic_attribute_set.code_space {
        serialize_any_uri(
            code_space,
            xml_fragment_writer,
            CityGmlNamespace::Generics,
            CityGmlElement::CodeSpaceProperty,
        )?;
    }

    for generic_attribute in &generic_attribute_set.generic_attributes {
        xml_fragment_writer.write_start_event(
            CityGmlNamespace::Generics,
            CityGmlElement::GenericAttributeProperty,
        )?;
        serialize_generic_attribute(generic_attribute, xml_fragment_writer)?;
        xml_fragment_writer.write_end_event(
            CityGmlNamespace::Generics,
            CityGmlElement::GenericAttributeProperty,
        )?;
    }

    xml_fragment_writer.write_end_event(
        CityGmlNamespace::Generics,
        CityGmlElement::GenericAttributeSet,
    )?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::generics::{IntAttribute, StringAttribute};
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_generic_attribute_set_drops_invalid_member() {
        let xml_document = b"<gen:GenericAttributeSet>
    <gen:name>generic_attribute_name</gen:name>
    <gen:genericAttribute>
        <gen:IntAttribute>
            <gen:name>tip_prem_name</gen:name>
            <gen:value></gen:value>
        </gen:IntAttribute>
    </gen:genericAttribute>
    <gen:genericAttribute>
        <gen:IntAttribute>
            <gen:name>MyIntAttributeName</gen:name>
            <gen:value>-123</gen:value>
        </gen:IntAttribute>
    </gen:genericAttribute>
</gen:GenericAttributeSet>";

        let generic_attribute_set =
            deserialize_generic_attribute_set(xml_document, &DeserializationConfig::default())
                .expect("should work");

        assert_eq!(generic_attribute_set.generic_attributes.len(), 1);
        assert_eq!(
            generic_attribute_set.generic_attributes[0].name(),
            "MyIntAttributeName"
        );
    }

    #[test]
    fn test_deserialize_generic_attribute_set() {
        let xml_document = b"<gen:GenericAttributeSet>
    <gen:name>generic_attribute_name</gen:name>
    <gen:genericAttribute>
        <gen:StringAttribute>
            <gen:name>MyStringAttributeName</gen:name>
            <gen:value>abc</gen:value>
        </gen:StringAttribute>
    </gen:genericAttribute>
    <gen:genericAttribute>
        <gen:IntAttribute>
            <gen:name>MyIntAttributeName</gen:name>
            <gen:value>-123</gen:value>
        </gen:IntAttribute>
    </gen:genericAttribute>
</gen:GenericAttributeSet>";

        let generic_attribute_set =
            deserialize_generic_attribute_set(xml_document, &DeserializationConfig::default())
                .expect("should work");

        assert_eq!(generic_attribute_set.name, "generic_attribute_name");
        assert_eq!(generic_attribute_set.generic_attributes.len(), 2);

        let GenericAttributeKind::StringAttribute(string_attribute) =
            &generic_attribute_set.generic_attributes[0]
        else {
            panic!("expected StringAttribute");
        };
        assert_eq!(string_attribute.name, "MyStringAttributeName");
        assert_eq!(string_attribute.value, "abc");

        let GenericAttributeKind::IntAttribute(int_attribute) =
            &generic_attribute_set.generic_attributes[1]
        else {
            panic!("expected IntAttribute");
        };
        assert_eq!(int_attribute.name, "MyIntAttributeName");
        assert_eq!(int_attribute.value, -123);
    }

    #[test]
    fn test_serialize_generic_attribute_set() {
        let generic_attribute_set = GenericAttributeSet {
            name: "generic_attribute_name".to_string(),
            code_space: None,
            generic_attributes: vec![
                GenericAttributeKind::StringAttribute(StringAttribute {
                    name: "GrossFloorArea".to_string(),
                    value: "250".to_string(),
                }),
                GenericAttributeKind::IntAttribute(IntAttribute {
                    name: "floors".to_string(),
                    value: 7,
                }),
            ],
        };

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_generic_attribute_set(&generic_attribute_set, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("gen:GenericAttributeSet"));
        assert!(xml.contains("generic_attribute_name"));
        assert!(xml.contains("gen:StringAttribute"));
        assert!(xml.contains("250"));
        assert!(xml.contains("gen:IntAttribute"));
        assert!(xml.contains('7'));
    }

    #[test]
    fn test_round_trip_generic_attribute_set() {
        let xml_document = b"<gen:GenericAttributeSet>
    <gen:name>generic_attribute_name</gen:name>
    <gen:genericAttribute>
        <gen:StringAttribute>
            <gen:name>MyStringAttributeName</gen:name>
            <gen:value>abc</gen:value>
        </gen:StringAttribute>
    </gen:genericAttribute>
</gen:GenericAttributeSet>";

        let generic_attribute_set =
            deserialize_generic_attribute_set(xml_document, &DeserializationConfig::default())
                .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_generic_attribute_set(&generic_attribute_set, &mut xml_fragment_writer)
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
            deserialize_generic_attribute_set(xml.as_bytes(), &DeserializationConfig::default())
                .expect("should work");

        assert_eq!(generic_attribute_set, round_tripped);
    }

    const SET_WITH_CODE_SPACE: &[u8] = b"<gen:GenericAttributeSet>
    <gen:name>energy</gen:name>
    <gen:codeSpace>https://example.org/attributes?scheme=energy&amp;v=2</gen:codeSpace>
    <genericAttribute>
        <gen:IntAttribute>
            <gen:name>rating</gen:name>
            <gen:value>3</gen:value>
        </gen:IntAttribute>
    </genericAttribute>
</gen:GenericAttributeSet>";

    #[test]
    fn test_deserialize_generic_attribute_set_with_code_space() {
        let generic_attribute_set = deserialize_generic_attribute_set(
            SET_WITH_CODE_SPACE,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(generic_attribute_set.name, "energy");
        assert_eq!(
            generic_attribute_set
                .code_space
                .as_ref()
                .map(|x| x.as_str()),
            Some("https://example.org/attributes?scheme=energy&v=2")
        );
        assert_eq!(generic_attribute_set.generic_attributes.len(), 1);
    }

    fn serialize_to_string(generic_attribute_set: &GenericAttributeSet) -> String {
        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_generic_attribute_set(generic_attribute_set, &mut xml_fragment_writer)
            .expect("should serialize");
        String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string")
    }

    #[test]
    fn test_round_trip_generic_attribute_set_with_code_space() {
        let generic_attribute_set = deserialize_generic_attribute_set(
            SET_WITH_CODE_SPACE,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let xml = serialize_to_string(&generic_attribute_set);

        let name = xml.find("<gen:name>").expect("should write name");
        let code_space = xml.find("<gen:codeSpace>").expect("should write codeSpace");
        let member = xml
            .find("<gen:genericAttribute>")
            .expect("should write members");
        assert!(
            name < code_space && code_space < member,
            "codeSpace must follow name and precede genericAttribute (XSD order)"
        );
        assert!(xml.contains("?scheme=energy&amp;v=2"));

        assert_eq!(
            deserialize_generic_attribute_set(xml.as_bytes(), &DeserializationConfig::default())
                .expect("should round trip"),
            generic_attribute_set
        );
    }

    #[test]
    fn test_serialize_generic_attribute_set_without_code_space() {
        let generic_attribute_set = GenericAttributeSet::new(
            "energy".to_string(),
            vec![GenericAttributeKind::IntAttribute(IntAttribute {
                name: "rating".to_string(),
                value: 3,
            })],
        );

        let xml = serialize_to_string(&generic_attribute_set);

        assert!(!xml.contains("codeSpace"));
    }

    #[test]
    fn test_deserialize_generic_attribute_set_unescapes_name() {
        let generic_attribute_set = deserialize_generic_attribute_set(
            b"<gen:GenericAttributeSet><gen:name>energy &amp; heat</gen:name><genericAttribute><gen:IntAttribute><gen:name>rating</gen:name><gen:value>3</gen:value></gen:IntAttribute></genericAttribute></gen:GenericAttributeSet>",
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(generic_attribute_set.name, "energy & heat");
    }
}
