use crate::Error;
use crate::gml::codec::tunnel::{deserialize_tunnel_installation, serialize_tunnel_installation};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::tunnel::TunnelInstallationProperty;
use egml::io::codec::base::{
    deserialize_association_and_ownership_attributes,
    serialize_association_and_ownership_attributes,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::base::{HasAssociationAttributes, HasOwnershipAttributes};

pub fn deserialize_tunnel_installation_property(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<TunnelInstallationProperty, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let (association, ownership) = deserialize_association_and_ownership_attributes(xml_document)?;
    let mut object = None;

    if let Some(index) = index.first(CityGmlElement::TunnelInstallation.into()) {
        object = Some(deserialize_tunnel_installation(
            &xml_document[index.range()],
            index,
            config,
        )?);
    }

    Ok(TunnelInstallationProperty::new(
        object,
        association,
        ownership,
    ))
}

pub fn serialize_tunnel_installation_property(
    tunnel_installation_property: &TunnelInstallationProperty,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_association_and_ownership_attributes(
        tunnel_installation_property.association(),
        tunnel_installation_property.ownership(),
    );

    match tunnel_installation_property.object() {
        Some(object) => {
            xml_fragment_writer.write_start_event_with_attributes(
                CityGmlNamespace::Tunnel,
                CityGmlElement::TunnelInstallationProperty,
                attributes,
            )?;
            serialize_tunnel_installation(object, xml_fragment_writer)?;
            xml_fragment_writer.write_end_event(
                CityGmlNamespace::Tunnel,
                CityGmlElement::TunnelInstallationProperty,
            )?;
        }
        None => {
            xml_fragment_writer.write_empty_element_with_attributes(
                CityGmlNamespace::Tunnel,
                CityGmlElement::TunnelInstallationProperty,
                attributes,
            )?;
        }
    }

    Ok(())
}
