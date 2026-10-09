use crate::Error;
use crate::gml::codec::construction::{
    deserialize_abstract_construction, serialize_abstract_construction,
    serialize_abstract_construction_attributes,
};
use crate::gml::codec::tunnel::tunnel_constructive_element_property::{
    deserialize_tunnel_constructive_element_property,
    serialize_tunnel_constructive_element_property,
};
use crate::gml::codec::tunnel::tunnel_installation_property::{
    deserialize_tunnel_installation_property, serialize_tunnel_installation_property,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::construction::AsAbstractConstruction;
use ecitygml_core::model::tunnel::{AbstractTunnel, AsAbstractTunnel, AsAbstractTunnelMut};
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter, collect_children};
use egml::model::basic_types::Code;

pub fn deserialize_abstract_tunnel(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractTunnel, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_tunnel received a truncated index — caller must scan to sufficient depth"
    );

    let mut abstract_construction_result = None;
    let mut tunnel_installations_result = None;
    let mut tunnel_constructive_elements_result = None;

    rayon::scope(|s| {
        s.spawn(|_| {
            abstract_construction_result = Some(deserialize_abstract_construction(
                xml_document,
                index,
                config,
            ));
        });
        s.spawn(|_| {
            tunnel_installations_result = Some(collect_children(
                xml_document,
                index,
                CityGmlElement::TunnelInstallationProperty.into(),
                config,
                deserialize_tunnel_installation_property,
            ));
        });
        s.spawn(|_| {
            tunnel_constructive_elements_result = Some(collect_children(
                xml_document,
                index,
                CityGmlElement::TunnelConstructiveElementProperty.into(),
                config,
                deserialize_tunnel_constructive_element_property,
            ));
        });
    });

    let mut abstract_tunnel = AbstractTunnel::from_abstract_construction(
        abstract_construction_result.expect("rayon::scope guarantees all spawns complete")?,
    );

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    abstract_tunnel.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    abstract_tunnel.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    abstract_tunnel.set_usages(usages.into_iter().map(Into::into).collect());

    abstract_tunnel.set_tunnel_installations(
        tunnel_installations_result.expect("rayon::scope guarantees all spawns complete")?,
    );
    abstract_tunnel.set_tunnel_constructive_elements(
        tunnel_constructive_elements_result
            .expect("rayon::scope guarantees all spawns complete")?,
    );

    Ok(abstract_tunnel)
}

pub fn serialize_abstract_tunnel(
    abstract_tunnel: &AbstractTunnel,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_construction(abstract_tunnel.abstract_construction(), xml_fragment_writer)?;

    if let Some(class) = abstract_tunnel.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Tunnel,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in abstract_tunnel.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::Tunnel,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in abstract_tunnel.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::Tunnel,
            CityGmlElement::UsageProperty,
        )?;
    }

    for prop in abstract_tunnel.tunnel_installations() {
        serialize_tunnel_installation_property(prop, xml_fragment_writer)?;
    }
    for prop in abstract_tunnel.tunnel_constructive_elements() {
        serialize_tunnel_constructive_element_property(prop, xml_fragment_writer)?;
    }

    Ok(())
}

pub fn serialize_abstract_tunnel_attributes(
    abstract_tunnel: &AbstractTunnel,
) -> Vec<(String, String)> {
    serialize_abstract_construction_attributes(abstract_tunnel.abstract_construction())
}
