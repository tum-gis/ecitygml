use crate::Error;
use crate::gml::codec::construction::{
    deserialize_abstract_installation, serialize_abstract_installation,
    serialize_abstract_installation_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::construction::AsAbstractInstallation;
use ecitygml_core::model::tunnel::TunnelInstallation;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::basic_types::Code;

pub fn deserialize_tunnel_installation(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<TunnelInstallation, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_installation = deserialize_abstract_installation(xml_document, index, config)?;
    let mut tunnel_installation =
        TunnelInstallation::from_abstract_installation(abstract_installation);

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    tunnel_installation.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    tunnel_installation.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    tunnel_installation.set_usages(usages.into_iter().map(Into::into).collect());

    Ok(tunnel_installation)
}

pub fn serialize_tunnel_installation(
    tunnel_installation: &TunnelInstallation,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_tunnel_installation_attributes(tunnel_installation);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Tunnel,
        CityGmlElement::TunnelInstallation,
        attributes,
    )?;

    serialize_abstract_installation(
        tunnel_installation.abstract_installation(),
        xml_fragment_writer,
    )?;

    if let Some(class) = tunnel_installation.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Tunnel,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in tunnel_installation.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::Tunnel,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in tunnel_installation.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::Tunnel,
            CityGmlElement::UsageProperty,
        )?;
    }

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::Tunnel, CityGmlElement::TunnelInstallation)?;

    Ok(())
}

pub fn serialize_tunnel_installation_attributes(
    tunnel_installation: &TunnelInstallation,
) -> Vec<(String, String)> {
    serialize_abstract_installation_attributes(tunnel_installation.abstract_installation())
}
