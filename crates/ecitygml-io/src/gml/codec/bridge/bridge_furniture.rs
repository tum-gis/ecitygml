use crate::Error;
use crate::gml::codec::construction::{
    deserialize_abstract_furniture, serialize_abstract_furniture,
    serialize_abstract_furniture_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::bridge::BridgeFurniture;
use ecitygml_core::model::construction::AsAbstractFurniture;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::basic_types::Code;

pub fn deserialize_bridge_furniture(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<BridgeFurniture, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_furniture = deserialize_abstract_furniture(xml_document, index, config)?;
    let mut bridge_furniture = BridgeFurniture::from_abstract_furniture(abstract_furniture);

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    bridge_furniture.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    bridge_furniture.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    bridge_furniture.set_usages(usages.into_iter().map(Into::into).collect());

    Ok(bridge_furniture)
}

pub fn serialize_bridge_furniture(
    bridge_furniture: &BridgeFurniture,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_bridge_furniture_attributes(bridge_furniture);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Bridge,
        CityGmlElement::BridgeFurniture,
        attributes,
    )?;

    serialize_abstract_furniture(bridge_furniture.abstract_furniture(), xml_fragment_writer)?;

    if let Some(class) = bridge_furniture.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Bridge,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in bridge_furniture.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::Bridge,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in bridge_furniture.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::Bridge,
            CityGmlElement::UsageProperty,
        )?;
    }

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::Bridge, CityGmlElement::BridgeFurniture)?;

    Ok(())
}

pub fn serialize_bridge_furniture_attributes(
    bridge_furniture: &BridgeFurniture,
) -> Vec<(String, String)> {
    serialize_abstract_furniture_attributes(bridge_furniture.abstract_furniture())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::core::AsAbstractFeature;
    use egml::io::util::Formatting;
    use egml::model::base::{AsAbstractGml, Id};

    fn deserialize(xml_document: &[u8]) -> BridgeFurniture {
        deserialize_bridge_furniture(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work")
    }

    #[test]
    fn test_deserialize_bridge_furniture() {
        let xml_document = b"<brid:BridgeFurniture gml:id=\"BF_1\">
      <gml:name>Bench</gml:name>
      <brid:class>7000</brid:class>
      <brid:function>7010</brid:function>
      <brid:function>7020</brid:function>
      <brid:usage>8000</brid:usage>
    </brid:BridgeFurniture>";

        let bridge_furniture = deserialize(xml_document);

        assert_eq!(
            bridge_furniture.feature_id(),
            &Id::try_from("BF_1").expect("should work")
        );
        assert_eq!(
            bridge_furniture
                .names()
                .first()
                .expect("should have a name"),
            &Code::new("Bench")
        );
        assert_eq!(
            bridge_furniture.class().map(|x| x.code().value()),
            Some("7000")
        );
        assert_eq!(
            bridge_furniture
                .functions()
                .iter()
                .map(|x| x.code().value())
                .collect::<Vec<_>>(),
            vec!["7010", "7020"]
        );
        assert_eq!(
            bridge_furniture
                .usages()
                .iter()
                .map(|x| x.code().value())
                .collect::<Vec<_>>(),
            vec!["8000"]
        );
    }

    #[test]
    fn test_deserialize_bridge_furniture_without_codes() {
        let bridge_furniture = deserialize(b"<brid:BridgeFurniture gml:id=\"BF_1\"/>");

        assert!(bridge_furniture.class().is_none());
        assert!(bridge_furniture.functions().is_empty());
        assert!(bridge_furniture.usages().is_empty());
    }

    #[test]
    fn test_round_trip_bridge_furniture() {
        let mut bridge_furniture = BridgeFurniture::new(Id::try_from("BF_1").expect("should work"));
        bridge_furniture.set_class(Code::new("7000").into());
        bridge_furniture.push_function(Code::new("7010").into());
        bridge_furniture.push_usage(Code::new("8000").into());

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_bridge_furniture(&bridge_furniture, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");
        assert!(xml.starts_with("<brid:BridgeFurniture"));

        assert_eq!(deserialize(xml.as_bytes()), bridge_furniture);
    }
}
