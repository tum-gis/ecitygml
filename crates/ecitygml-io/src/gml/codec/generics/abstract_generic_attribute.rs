use crate::Error;
use crate::gml::codec::generics::double_attribute::{
    deserialize_double_attribute, serialize_double_attribute,
};
use crate::gml::codec::generics::generic_attribute_set::{
    deserialize_generic_attribute_set, serialize_generic_attribute_set,
};
use crate::gml::codec::generics::int_attribute::{
    deserialize_int_attribute, serialize_int_attribute,
};
use crate::gml::codec::generics::measure_attribute::{
    deserialize_measure_attribute, serialize_measure_attribute,
};
use crate::gml::codec::generics::{deserialize_string_attribute, serialize_string_attribute};
use ecitygml_core::model::generics::GenericAttributeKind;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_generic_attribute(xml_document: &[u8]) -> Result<GenericAttributeKind, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    loop {
        match reader.read_event()? {
            Event::Start(start) => {
                return match start.local_name().as_ref() {
                    "StringAttribute" => Ok(GenericAttributeKind::StringAttribute(
                        deserialize_string_attribute(xml_document)?,
                    )),
                    "IntAttribute" => Ok(GenericAttributeKind::IntAttribute(
                        deserialize_int_attribute(xml_document)?,
                    )),
                    "DoubleAttribute" => Ok(GenericAttributeKind::DoubleAttribute(
                        deserialize_double_attribute(xml_document)?,
                    )),
                    "MeasureAttribute" => Ok(GenericAttributeKind::MeasureAttribute(
                        deserialize_measure_attribute(xml_document)?,
                    )),
                    "GenericAttributeSet" => Ok(GenericAttributeKind::GenericAttributeSet(
                        deserialize_generic_attribute_set(xml_document)?,
                    )),
                    other => Err(Error::UnknownElementNode(other.to_string())),
                };
            }
            Event::Eof => {
                return Err(Error::ElementNotFound("generic attribute".to_string()));
            }
            _ => {}
        }
    }
}

pub fn serialize_generic_attribute(
    attr: &GenericAttributeKind,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    match attr {
        GenericAttributeKind::StringAttribute(x) => {
            serialize_string_attribute(x, xml_fragment_writer)
        }
        GenericAttributeKind::IntAttribute(x) => serialize_int_attribute(x, xml_fragment_writer),
        GenericAttributeKind::DoubleAttribute(x) => {
            serialize_double_attribute(x, xml_fragment_writer)
        }
        GenericAttributeKind::MeasureAttribute(x) => {
            serialize_measure_attribute(x, xml_fragment_writer)
        }
        GenericAttributeKind::GenericAttributeSet(x) => {
            serialize_generic_attribute_set(x, xml_fragment_writer)
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::generics::{
        DoubleAttribute, GenericAttributeSet, IntAttribute, MeasureAttribute, StringAttribute,
    };
    use egml::io::util::Formatting;
    use egml::model::basic_types::Measure;

    #[test]
    fn test_serialize_string_attribute() {
        let attr = GenericAttributeKind::StringAttribute(StringAttribute {
            name: "material".to_string(),
            value: "concrete".to_string(),
        });

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_generic_attribute(&attr, &mut xml_fragment_writer).unwrap();
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .unwrap();

        assert!(
            xml.contains("<gen:StringAttribute>"),
            "missing root element: {xml}"
        );
        assert!(
            xml.contains("<gen:name>material</gen:name>"),
            "missing name: {xml}"
        );
        assert!(
            xml.contains("<gen:value>concrete</gen:value>"),
            "missing value: {xml}"
        );
    }

    #[test]
    fn test_serialize_int_attribute() {
        let attr = GenericAttributeKind::IntAttribute(IntAttribute {
            name: "storeys".to_string(),
            value: 4,
        });

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_generic_attribute(&attr, &mut xml_fragment_writer).unwrap();
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .unwrap();

        assert!(
            xml.contains("<gen:IntAttribute>"),
            "missing root element: {xml}"
        );
        assert!(
            xml.contains("<gen:name>storeys</gen:name>"),
            "missing name: {xml}"
        );
        assert!(
            xml.contains("<gen:value>4</gen:value>"),
            "missing value: {xml}"
        );
    }

    #[test]
    fn test_serialize_double_attribute() {
        let attr = GenericAttributeKind::DoubleAttribute(DoubleAttribute {
            name: "height".to_string(),
            value: 12.5,
        });

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_generic_attribute(&attr, &mut xml_fragment_writer).unwrap();
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .unwrap();

        assert!(
            xml.contains("<gen:DoubleAttribute>"),
            "missing root element: {xml}"
        );
        assert!(
            xml.contains("<gen:name>height</gen:name>"),
            "missing name: {xml}"
        );
        assert!(
            xml.contains("<gen:value>12.5</gen:value>"),
            "missing value: {xml}"
        );
    }

    #[test]
    fn test_serialize_measure_attribute() {
        let attr = GenericAttributeKind::MeasureAttribute(MeasureAttribute {
            name: "GrossFloorArea".to_string(),
            value: Measure {
                uom: "m2".to_string(),
                value: 250.0,
            },
        });

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_generic_attribute(&attr, &mut xml_fragment_writer).unwrap();
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .unwrap();

        assert!(
            xml.contains("<gen:MeasureAttribute>"),
            "missing root element: {xml}"
        );
        assert!(
            xml.contains("<gen:name>GrossFloorArea</gen:name>"),
            "missing name: {xml}"
        );
        assert!(xml.contains("uom=\"m2\""), "missing uom attribute: {xml}");
        assert!(xml.contains("250"), "missing value: {xml}");
    }

    #[test]
    fn test_serialize_generic_attribute_set() {
        let string_attribute: GenericAttributeKind =
            StringAttribute::new("GrossFloorArea".to_string(), "250".to_string()).into();
        let int_attribute: GenericAttributeKind = IntAttribute::new("floors".to_string(), 7).into();
        let generic_attribute_set: GenericAttributeKind = GenericAttributeSet::new(
            "generic_attribute_name".to_string(),
            vec![string_attribute, int_attribute],
        )
        .into();

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_generic_attribute(&generic_attribute_set, &mut xml_fragment_writer).unwrap();
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .unwrap();

        assert!(
            xml.contains("<gen:GenericAttributeSet>"),
            "missing root element: {xml}"
        );
        assert!(
            xml.contains("<gen:name>generic_attribute_name</gen:name>"),
            "missing name: {xml}"
        );
        assert!(
            xml.contains("<gen:StringAttribute>"),
            "missing element: {xml}"
        );
        assert!(xml.contains("250"), "missing value: {xml}");
    }

    #[test]
    fn test_serialize_string_attribute_round_trip() {
        let original = GenericAttributeKind::StringAttribute(StringAttribute {
            name: "construction_method".to_string(),
            value: "prefab".to_string(),
        });

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_generic_attribute(&original, &mut xml_fragment_writer).unwrap();
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .unwrap();
        let recovered = deserialize_generic_attribute(xml.as_bytes()).unwrap();

        assert_eq!(original, recovered);
    }

    #[test]
    fn test_serialize_int_attribute_round_trip() {
        let original = GenericAttributeKind::IntAttribute(IntAttribute {
            name: "floors".to_string(),
            value: 7,
        });

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_generic_attribute(&original, &mut xml_fragment_writer).unwrap();
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .unwrap();
        let recovered = deserialize_generic_attribute(xml.as_bytes()).unwrap();

        assert_eq!(original, recovered);
    }

    #[test]
    fn test_serialize_double_attribute_round_trip() {
        let original = GenericAttributeKind::DoubleAttribute(DoubleAttribute {
            name: "area".to_string(),
            value: 99.9,
        });

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_generic_attribute(&original, &mut xml_fragment_writer).unwrap();
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .unwrap();
        let recovered = deserialize_generic_attribute(xml.as_bytes()).unwrap();

        assert_eq!(original, recovered);
    }

    #[test]
    fn test_serialize_measure_attribute_round_trip() {
        let original = GenericAttributeKind::MeasureAttribute(MeasureAttribute {
            name: "volume".to_string(),
            value: Measure {
                uom: "m3".to_string(),
                value: 1500.0,
            },
        });

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_generic_attribute(&original, &mut xml_fragment_writer).unwrap();
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .unwrap();
        let recovered = deserialize_generic_attribute(xml.as_bytes()).unwrap();

        assert_eq!(original, recovered);
    }

    // --- Deserialization tests ---

    #[test]
    fn test_deserialize_string_attribute_via_generic_kind() {
        let xml_document = b"<gen:StringAttribute>
    <gen:name>attribute_name</gen:name>
    <gen:value>1100</gen:value>
  </gen:StringAttribute>";

        let generic_attribute = deserialize_generic_attribute(xml_document).expect("should work");

        assert_eq!(generic_attribute.name(), "attribute_name");
        assert_eq!(
            generic_attribute.as_string().expect("must be string").value,
            "1100"
        );
    }

    #[test]
    fn test_deserialize_string_attribute() {
        let xml_document = b"<gen:StringAttribute>
          <gen:name>attribute_name</gen:name>
          <gen:value>1100</gen:value>
        </gen:StringAttribute>";

        let generic_attribute = deserialize_generic_attribute(xml_document).expect("should work");

        match generic_attribute {
            GenericAttributeKind::StringAttribute(x) => {
                assert_eq!(x.name, "attribute_name");
                assert_eq!(x.value, "1100");
            }
            other => panic!("Expected Double attribute, got {:?}", other),
        }
    }

    #[test]
    fn test_deserialize_int_attribute() {
        let xml_document = b"<gen:IntAttribute>
          <gen:name>attribute_name</gen:name>
          <gen:value>1100</gen:value>
        </gen:IntAttribute>";

        let generic_attribute = deserialize_generic_attribute(xml_document).expect("should work");

        match generic_attribute {
            GenericAttributeKind::IntAttribute(x) => {
                assert_eq!(x.name, "attribute_name");
                assert_eq!(x.value, 1100);
            }
            other => panic!("Expected Double attribute, got {:?}", other),
        }
    }

    #[test]
    fn test_deserialize_double_attribute() {
        let xml_document = b"<gen:DoubleAttribute>
          <gen:name>attribute_name</gen:name>
          <gen:value>42.2</gen:value>
        </gen:DoubleAttribute>";

        let generic_attribute = deserialize_generic_attribute(xml_document).expect("should work");

        match generic_attribute {
            GenericAttributeKind::DoubleAttribute(x) => {
                assert_eq!(x.name, "attribute_name");
                assert_eq!(x.value, 42.2);
            }
            other => panic!("Expected Double attribute, got {:?}", other),
        }
    }

    #[test]
    fn test_deserialize_generic_attribute_set() {
        let xml_document = "<gen:GenericAttributeSet>
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

        let generic_attribute_kind =
            deserialize_generic_attribute(xml_document.as_ref()).expect("should work");

        let GenericAttributeKind::GenericAttributeSet(generic_attribute_set) =
            generic_attribute_kind
        else {
            panic!("Expected GenericAttributeSet");
        };
        assert_eq!(generic_attribute_set.name, "generic_attribute_name");
        assert_eq!(generic_attribute_set.generic_attributes.len(), 2);

        let first_generic_attribute = &generic_attribute_set.generic_attributes[0];
        let GenericAttributeKind::StringAttribute(string_attribute) = first_generic_attribute
        else {
            panic!("Expected StringAttribute");
        };
        assert_eq!(string_attribute.name, "MyStringAttributeName");
        assert_eq!(string_attribute.value, "abc");

        let second_generic_attribute = &generic_attribute_set.generic_attributes[1];
        let GenericAttributeKind::IntAttribute(int_attribute) = second_generic_attribute else {
            panic!("Expected IntAttribute");
        };
        assert_eq!(int_attribute.name, "MyIntAttributeName");
        assert_eq!(int_attribute.value, -123);
    }
}
