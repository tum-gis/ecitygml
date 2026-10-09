use crate::Error;
use crate::gml::codec::construction::{
    deserialize_abstract_constructive_element, serialize_abstract_constructive_element,
    serialize_abstract_constructive_element_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::bridge::BridgeConstructiveElement;
use ecitygml_core::model::construction::AsAbstractConstructiveElement;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::basic_types::Code;

pub fn deserialize_bridge_constructive_element(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<BridgeConstructiveElement, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_constructive_element =
        deserialize_abstract_constructive_element(xml_document, index, config)?;
    let mut bridge_constructive_element =
        BridgeConstructiveElement::from_abstract_constructive_element(
            abstract_constructive_element,
        );

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    bridge_constructive_element.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    bridge_constructive_element.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    bridge_constructive_element.set_usages(usages.into_iter().map(Into::into).collect());

    Ok(bridge_constructive_element)
}

pub fn serialize_bridge_constructive_element(
    bridge_constructive_element: &BridgeConstructiveElement,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_bridge_constructive_element_attributes(bridge_constructive_element);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Bridge,
        CityGmlElement::BridgeConstructiveElement,
        attributes,
    )?;

    serialize_abstract_constructive_element(
        bridge_constructive_element.abstract_constructive_element(),
        xml_fragment_writer,
    )?;

    if let Some(class) = bridge_constructive_element.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Bridge,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in bridge_constructive_element.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::Bridge,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in bridge_constructive_element.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::Bridge,
            CityGmlElement::UsageProperty,
        )?;
    }

    xml_fragment_writer.write_end_event(
        CityGmlNamespace::Bridge,
        CityGmlElement::BridgeConstructiveElement,
    )?;

    Ok(())
}

pub fn serialize_bridge_constructive_element_attributes(
    bridge_constructive_element: &BridgeConstructiveElement,
) -> Vec<(String, String)> {
    serialize_abstract_constructive_element_attributes(
        bridge_constructive_element.abstract_constructive_element(),
    )
}
