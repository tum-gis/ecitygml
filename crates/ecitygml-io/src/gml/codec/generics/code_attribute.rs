use crate::Error;
use crate::Error::AttributeWithoutName;
use crate::gml::codec::common::deserialize_string;
use crate::gml::util::{CityGmlElement, CityGmlNamespace, DeserializationConfig};
use ecitygml_core::model::generics::CodeAttribute;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use egml::model::basic_types::Code;
use quick_xml::Reader;
use quick_xml::events::Event;

/// The `config` is unused (a code needs no configuration) and only keeps the signature uniform with the other
/// generic attribute deserializers.
pub fn deserialize_code_attribute(
    xml_document: &[u8],
    _config: &DeserializationConfig,
) -> Result<CodeAttribute, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    // Consume the root `<CodeAttribute>` element's own start tag.
    loop {
        match reader.read_event()? {
            Event::Start(_) => break,
            Event::Eof => {
                return Err(Error::ElementNotFound("CodeAttribute".to_string()));
            }
            _ => {}
        }
    }

    let mut name: Option<String> = None;
    let mut value: Option<Code> = None;

    loop {
        match reader.read_event()? {
            Event::Start(start) => {
                let pos_start = reader.buffer_position() as usize - start.len() - 2;
                reader.read_to_end(start.name())?;
                let pos_end = reader.buffer_position() as usize;
                let element = &xml_document[pos_start..pos_end];

                match start.local_name().as_ref() {
                    "name" => name = Some(deserialize_string(element)?.trim().to_string()),
                    "value" => value = Some(deserialize_code(element)?),
                    _ => {}
                }
            }
            Event::Eof => break,
            _ => {}
        }
    }

    let name = name
        .filter(|x| !x.is_empty())
        .ok_or_else(|| AttributeWithoutName("code attribute".to_string()))?;
    let value = value.ok_or_else(|| Error::ElementNotFound("value".to_string()))?;

    Ok(CodeAttribute { name, value })
}

pub fn serialize_code_attribute(
    code_attribute: &CodeAttribute,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    xml_fragment_writer
        .write_start_event(CityGmlNamespace::Generics, CityGmlElement::CodeAttribute)?;

    xml_fragment_writer.write_leaf_element(
        CityGmlNamespace::Generics,
        CityGmlElement::NameProperty,
        &code_attribute.name,
    )?;
    serialize_code(
        &code_attribute.value,
        xml_fragment_writer,
        CityGmlNamespace::Generics,
        CityGmlElement::ValueProperty,
    )?;

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::Generics, CityGmlElement::CodeAttribute)?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;
    use egml::model::xs::AnyUri;

    fn deserialize(xml_document: &[u8]) -> Result<CodeAttribute, Error> {
        deserialize_code_attribute(xml_document, &DeserializationConfig::default())
    }

    #[test]
    fn test_deserialize_code_attribute_with_code_space() {
        let code_attribute = deserialize(
            b"<gen:CodeAttribute>
    <gen:name>roofType</gen:name>
    <gen:value codeSpace=\"https://example.org/roofTypes\">1000</gen:value>
</gen:CodeAttribute>",
        )
        .expect("should work");

        assert_eq!(code_attribute.name, "roofType");
        assert_eq!(code_attribute.value.value(), "1000");
        assert_eq!(
            code_attribute.value.code_space().map(AnyUri::as_str),
            Some("https://example.org/roofTypes")
        );
    }

    #[test]
    fn test_deserialize_code_attribute_without_code_space() {
        let code_attribute = deserialize(
            b"<gen:CodeAttribute>
    <gen:name>roofType</gen:name>
    <gen:value>1000</gen:value>
</gen:CodeAttribute>",
        )
        .expect("should work");

        assert_eq!(code_attribute.value, Code::new("1000"));
    }

    #[test]
    fn test_deserialize_code_attribute_rejects_empty_name() {
        let result = deserialize(
            b"<gen:CodeAttribute>
    <gen:name></gen:name>
    <gen:value>1000</gen:value>
</gen:CodeAttribute>",
        );

        assert!(matches!(result, Err(AttributeWithoutName(_))));
    }

    #[test]
    fn test_round_trip_code_attribute_keeps_code_space() {
        let code_attribute = CodeAttribute::new(
            "roofType".to_string(),
            Code::with_code_space("https://example.org/roofTypes", "1000"),
        );

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_code_attribute(&code_attribute, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");
        assert!(xml.contains("codeSpace=\"https://example.org/roofTypes\""));

        assert_eq!(
            deserialize(xml.as_bytes()).expect("should round trip"),
            code_attribute
        );
    }
}
