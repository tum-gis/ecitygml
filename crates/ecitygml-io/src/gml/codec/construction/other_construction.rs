use crate::Error;
use crate::gml::codec::construction::{
    deserialize_abstract_construction, serialize_abstract_construction,
    serialize_abstract_construction_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::construction::AsAbstractConstruction;
use ecitygml_core::model::construction::OtherConstruction;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::basic_types::Code;

pub fn deserialize_other_construction(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<OtherConstruction, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_construction = deserialize_abstract_construction(xml_document, index, config)?;

    let mut other_construction =
        OtherConstruction::from_abstract_construction(abstract_construction);

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    other_construction.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    other_construction.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    other_construction.set_usages(usages.into_iter().map(Into::into).collect());

    Ok(other_construction)
}

pub fn serialize_other_construction(
    other_construction: &OtherConstruction,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_other_construction_attributes(other_construction);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Construction,
        CityGmlElement::OtherConstruction,
        attributes,
    )?;

    serialize_abstract_construction(
        other_construction.abstract_construction(),
        xml_fragment_writer,
    )?;

    if let Some(class) = other_construction.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Construction,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in other_construction.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::Construction,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in other_construction.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::Construction,
            CityGmlElement::UsageProperty,
        )?;
    }

    xml_fragment_writer.write_end_event(
        CityGmlNamespace::Construction,
        CityGmlElement::OtherConstruction,
    )?;

    Ok(())
}

pub fn serialize_other_construction_attributes(
    other_construction: &OtherConstruction,
) -> Vec<(String, String)> {
    serialize_abstract_construction_attributes(other_construction.abstract_construction())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::core::AsAbstractFeature;
    use egml::io::util::Formatting;
    use egml::model::base::{AsAbstractGml, Id};

    fn deserialize(xml_document: &[u8]) -> OtherConstruction {
        deserialize_other_construction(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work")
    }

    #[test]
    fn test_deserialize_other_construction() {
        let xml_document = b"<con:OtherConstruction gml:id=\"OC_1\">
      <gml:name>Noise barrier</gml:name>
      <con:class codeSpace=\"https://example.com/class\">1000</con:class>
      <con:function>2000</con:function>
      <con:function>2010</con:function>
      <con:usage>3000</con:usage>
    </con:OtherConstruction>";

        let other_construction = deserialize(xml_document);

        assert_eq!(
            other_construction.feature_id(),
            &Id::try_from("OC_1").expect("should work")
        );
        assert_eq!(
            other_construction
                .names()
                .first()
                .expect("should have a name"),
            &Code::new("Noise barrier")
        );
        assert_eq!(
            other_construction.class().map(|x| x.code().value()),
            Some("1000")
        );
        assert_eq!(
            other_construction
                .functions()
                .iter()
                .map(|x| x.code().value())
                .collect::<Vec<_>>(),
            vec!["2000", "2010"]
        );
        assert_eq!(
            other_construction
                .usages()
                .iter()
                .map(|x| x.code().value())
                .collect::<Vec<_>>(),
            vec!["3000"]
        );
    }

    #[test]
    fn test_deserialize_other_construction_without_codes() {
        let xml_document = b"<con:OtherConstruction gml:id=\"OC_1\"/>";

        let other_construction = deserialize(xml_document);

        assert!(other_construction.class().is_none());
        assert!(other_construction.functions().is_empty());
        assert!(other_construction.usages().is_empty());
    }

    #[test]
    fn test_round_trip_other_construction() {
        let mut other_construction =
            OtherConstruction::new(Id::try_from("OC_1").expect("should work"));
        other_construction.set_class(Code::new("1000").into());
        other_construction.push_function(Code::new("2000").into());
        other_construction.push_usage(Code::new("3000").into());

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_other_construction(&other_construction, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");
        assert!(xml.contains("con:OtherConstruction"));

        assert_eq!(deserialize(xml.as_bytes()), other_construction);
    }
}
