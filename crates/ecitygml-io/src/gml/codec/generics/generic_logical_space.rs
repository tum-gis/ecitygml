use crate::Error;
use crate::gml::codec::core::{
    deserialize_abstract_logical_space, serialize_abstract_logical_space,
    serialize_abstract_logical_space_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::core::AsAbstractLogicalSpace;
use ecitygml_core::model::generics::GenericLogicalSpace;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::basic_types::Code;

pub fn deserialize_generic_logical_space(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<GenericLogicalSpace, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_logical_space = deserialize_abstract_logical_space(xml_document, index, config)?;

    let mut generic_logical_space =
        GenericLogicalSpace::from_abstract_logical_space(abstract_logical_space);

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    generic_logical_space.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    generic_logical_space.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    generic_logical_space.set_usages(usages.into_iter().map(Into::into).collect());

    Ok(generic_logical_space)
}

pub fn serialize_generic_logical_space(
    generic_logical_space: &GenericLogicalSpace,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_generic_logical_space_attributes(generic_logical_space);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Generics,
        CityGmlElement::GenericLogicalSpace,
        attributes,
    )?;

    serialize_abstract_logical_space(
        generic_logical_space.abstract_logical_space(),
        xml_fragment_writer,
    )?;

    if let Some(class) = generic_logical_space.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Generics,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in generic_logical_space.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::Generics,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in generic_logical_space.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::Generics,
            CityGmlElement::UsageProperty,
        )?;
    }

    xml_fragment_writer.write_end_event(
        CityGmlNamespace::Generics,
        CityGmlElement::GenericLogicalSpace,
    )?;

    Ok(())
}

pub fn serialize_generic_logical_space_attributes(
    generic_logical_space: &GenericLogicalSpace,
) -> Vec<(String, String)> {
    serialize_abstract_logical_space_attributes(generic_logical_space.abstract_logical_space())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::core::AsAbstractFeature;
    use egml::io::util::Formatting;
    use egml::model::base::{AsAbstractGml, Id};

    fn deserialize(xml_document: &[u8]) -> GenericLogicalSpace {
        deserialize_generic_logical_space(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work")
    }

    #[test]
    fn test_deserialize_generic_logical_space() {
        let xml_document = b"<gen:GenericLogicalSpace gml:id=\"GLS_1\">
      <gml:name>Planning zone</gml:name>
      <gen:class codeSpace=\"https://example.com/class\">1000</gen:class>
      <gen:function>2000</gen:function>
      <gen:function>2010</gen:function>
      <gen:usage>3000</gen:usage>
    </gen:GenericLogicalSpace>";

        let generic_logical_space = deserialize(xml_document);

        assert_eq!(
            generic_logical_space.feature_id(),
            &Id::try_from("GLS_1").expect("should work")
        );
        assert_eq!(
            generic_logical_space
                .names()
                .first()
                .expect("should have a name"),
            &Code::new("Planning zone")
        );
        assert_eq!(
            generic_logical_space.class().map(|x| x.code().value()),
            Some("1000")
        );
        assert_eq!(
            generic_logical_space
                .functions()
                .iter()
                .map(|x| x.code().value())
                .collect::<Vec<_>>(),
            vec!["2000", "2010"]
        );
        assert_eq!(
            generic_logical_space
                .usages()
                .iter()
                .map(|x| x.code().value())
                .collect::<Vec<_>>(),
            vec!["3000"]
        );
    }

    #[test]
    fn test_deserialize_generic_logical_space_without_codes() {
        let xml_document = b"<gen:GenericLogicalSpace gml:id=\"GLS_1\"/>";

        let generic_logical_space = deserialize(xml_document);

        assert!(generic_logical_space.class().is_none());
        assert!(generic_logical_space.functions().is_empty());
        assert!(generic_logical_space.usages().is_empty());
    }

    #[test]
    fn test_round_trip_generic_logical_space() {
        let mut generic_logical_space =
            GenericLogicalSpace::new(Id::try_from("GLS_1").expect("should work"));
        generic_logical_space.set_class(Code::new("1000").into());
        generic_logical_space.push_function(Code::new("2000").into());
        generic_logical_space.push_usage(Code::new("3000").into());

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_generic_logical_space(&generic_logical_space, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");
        assert!(xml.contains("gen:GenericLogicalSpace"));

        assert_eq!(deserialize(xml.as_bytes()), generic_logical_space);
    }
}
