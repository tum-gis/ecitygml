use crate::Error;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::core::basic_types::DoubleBetween0And1;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_double_between_0_and_1(
    xml_document: &[u8],
) -> Result<DoubleBetween0And1, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    loop {
        match reader.read_event()? {
            Event::Text(text) => {
                let value = text.as_ref();
                return double_between_0_and_1_from_str(value);
            }
            Event::CData(cdata) => {
                let value = cdata.as_ref();
                return double_between_0_and_1_from_str(value);
            }
            Event::Eof => {
                return Err(Error::ElementNotFound("double text content".to_string()));
            }
            _ => {}
        }
    }
}

pub fn serialize_double_between_0_and_1(
    value: DoubleBetween0And1,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
    target_xml_namespace: CityGmlNamespace,
    target_xml_element: CityGmlElement,
) -> Result<(), Error> {
    let text_value = value.value().to_string();

    xml_fragment_writer.write_leaf_element(
        target_xml_namespace,
        target_xml_element,
        &text_value,
    )?;

    Ok(())
}

fn double_between_0_and_1_from_str(value: &str) -> Result<DoubleBetween0And1, Error> {
    let parsed: f64 = value
        .trim()
        .parse()
        .map_err(|_| Error::UnknownElementNode(format!("expected f64 value, got `{value}`")))?;

    Ok(DoubleBetween0And1::try_from(parsed).map_err(ecitygml_core::Error::from)?)
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_double_between_0_and_1() {
        let xml_document = b"<shininess>0.5</shininess>";

        let value = deserialize_double_between_0_and_1(xml_document).expect("should work");

        assert_eq!(value.value(), 0.5);
    }

    #[test]
    fn test_deserialize_double_between_0_and_1_rejects_out_of_range() {
        let xml_document = b"<shininess>1.5</shininess>";

        let result = deserialize_double_between_0_and_1(xml_document);

        assert!(result.is_err());
    }

    #[test]
    fn test_serialize_double_between_0_and_1() {
        let value = DoubleBetween0And1::try_from(0.25).expect("should be valid");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_double_between_0_and_1(
            value,
            &mut xml_fragment_writer,
            CityGmlNamespace::Appearance,
            CityGmlElement::ShininessProperty,
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

        assert_eq!(xml, "<app:shininess>0.25</app:shininess>");
    }

    #[test]
    fn test_round_trip_double_between_0_and_1() {
        let xml_document = b"<transparency>0.75</transparency>";

        let value = deserialize_double_between_0_and_1(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_double_between_0_and_1(
            value,
            &mut xml_fragment_writer,
            CityGmlNamespace::Appearance,
            CityGmlElement::TransparencyProperty,
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
            deserialize_double_between_0_and_1(xml.as_bytes()).expect("should work");

        assert_eq!(value, round_tripped);
    }
}
