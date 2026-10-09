use crate::Error;
use crate::gml::codec::construction::{
    deserialize_abstract_constructive_element, serialize_abstract_constructive_element,
    serialize_abstract_constructive_element_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::construction::AsAbstractConstructiveElement;
use ecitygml_core::model::tunnel::TunnelConstructiveElement;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::basic_types::Code;

pub fn deserialize_tunnel_constructive_element(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<TunnelConstructiveElement, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_constructive_element =
        deserialize_abstract_constructive_element(xml_document, index, config)?;
    let mut tunnel_constructive_element =
        TunnelConstructiveElement::from_abstract_constructive_element(
            abstract_constructive_element,
        );

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    tunnel_constructive_element.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    tunnel_constructive_element.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    tunnel_constructive_element.set_usages(usages.into_iter().map(Into::into).collect());

    Ok(tunnel_constructive_element)
}

pub fn serialize_tunnel_constructive_element(
    tunnel_constructive_element: &TunnelConstructiveElement,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_tunnel_constructive_element_attributes(tunnel_constructive_element);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Tunnel,
        CityGmlElement::TunnelConstructiveElement,
        attributes,
    )?;

    serialize_abstract_constructive_element(
        tunnel_constructive_element.abstract_constructive_element(),
        xml_fragment_writer,
    )?;

    if let Some(class) = tunnel_constructive_element.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Tunnel,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in tunnel_constructive_element.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::Tunnel,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in tunnel_constructive_element.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::Tunnel,
            CityGmlElement::UsageProperty,
        )?;
    }

    xml_fragment_writer.write_end_event(
        CityGmlNamespace::Tunnel,
        CityGmlElement::TunnelConstructiveElement,
    )?;

    Ok(())
}

pub fn serialize_tunnel_constructive_element_attributes(
    tunnel_constructive_element: &TunnelConstructiveElement,
) -> Vec<(String, String)> {
    serialize_abstract_constructive_element_attributes(
        tunnel_constructive_element.abstract_constructive_element(),
    )
}
