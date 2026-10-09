use crate::Error;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::appearance::enums::WrapMode;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_wrap_mode(xml_document: &[u8]) -> Result<WrapMode, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    loop {
        match reader.read_event()? {
            Event::Text(text) => {
                let value = text.as_ref();
                return wrap_mode_from_str(value.trim())
                    .ok_or_else(|| Error::UnknownElementNode(value.trim().to_string()));
            }
            Event::CData(cdata) => {
                let value = cdata.as_ref();
                return wrap_mode_from_str(value.trim())
                    .ok_or_else(|| Error::UnknownElementNode(value.trim().to_string()));
            }
            Event::Eof => {
                return Err(Error::ElementNotFound("wrapMode text content".to_string()));
            }
            _ => {}
        }
    }
}

pub fn serialize_wrap_mode(
    wrap_mode: WrapMode,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
    target_xml_namespace: CityGmlNamespace,
    target_xml_element: CityGmlElement,
) -> Result<(), Error> {
    let value = wrap_mode_as_str(wrap_mode);

    xml_fragment_writer.write_leaf_element(target_xml_namespace, target_xml_element, value)?;

    Ok(())
}

fn wrap_mode_as_str(value: WrapMode) -> &'static str {
    match value {
        WrapMode::None => "none",
        WrapMode::Wrap => "wrap",
        WrapMode::Mirror => "mirror",
        WrapMode::Clamp => "clamp",
        WrapMode::Border => "border",
    }
}

fn wrap_mode_from_str(value: &str) -> Option<WrapMode> {
    match value {
        "none" => Some(WrapMode::None),
        "wrap" => Some(WrapMode::Wrap),
        "mirror" => Some(WrapMode::Mirror),
        "clamp" => Some(WrapMode::Clamp),
        "border" => Some(WrapMode::Border),
        _ => None,
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_wrap_mode() {
        let xml_document = b"<wrapMode>mirror</wrapMode>";

        let wrap_mode = deserialize_wrap_mode(xml_document).expect("should work");

        assert_eq!(wrap_mode, WrapMode::Mirror);
    }

    #[test]
    fn test_deserialize_wrap_mode_rejects_unknown_value() {
        let xml_document = b"<wrapMode>notAValue</wrapMode>";

        let result = deserialize_wrap_mode(xml_document);

        assert!(result.is_err());
    }

    #[test]
    fn test_serialize_wrap_mode() {
        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);

        serialize_wrap_mode(
            WrapMode::Border,
            &mut xml_fragment_writer,
            CityGmlNamespace::Appearance,
            CityGmlElement::WrapModeProperty,
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

        assert_eq!(xml, "<app:wrapMode>border</app:wrapMode>");
    }

    #[test]
    fn test_round_trip_wrap_mode() {
        let xml_document = b"<wrapMode>clamp</wrapMode>";

        let wrap_mode = deserialize_wrap_mode(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_wrap_mode(
            wrap_mode,
            &mut xml_fragment_writer,
            CityGmlNamespace::Appearance,
            CityGmlElement::WrapModeProperty,
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

        let round_tripped = deserialize_wrap_mode(xml.as_bytes()).expect("should work");

        assert_eq!(wrap_mode, round_tripped);
    }
}
