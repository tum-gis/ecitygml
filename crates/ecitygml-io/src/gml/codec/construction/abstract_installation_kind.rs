use crate::Error;
use crate::gml::codec::bridge::{deserialize_bridge_installation, serialize_bridge_installation};
use crate::gml::codec::building::{
    deserialize_building_installation, serialize_building_installation,
};
use crate::gml::codec::tunnel::{deserialize_tunnel_installation, serialize_tunnel_installation};
use crate::gml::util::{CityGmlElement, CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::construction::AbstractInstallationKind;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_installation_kind(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Option<AbstractInstallationKind>, Error> {
    if let Some(index) = index.first(CityGmlElement::BuildingInstallation.into()) {
        let building_installation =
            deserialize_building_installation(&xml_document[index.range()], index, config)?;
        return Ok(Some(building_installation.into()));
    }
    if let Some(index) = index.first(CityGmlElement::BridgeInstallation.into()) {
        let bridge_installation =
            deserialize_bridge_installation(&xml_document[index.range()], index, config)?;
        return Ok(Some(bridge_installation.into()));
    }
    if let Some(index) = index.first(CityGmlElement::TunnelInstallation.into()) {
        let tunnel_installation =
            deserialize_tunnel_installation(&xml_document[index.range()], index, config)?;
        return Ok(Some(tunnel_installation.into()));
    }

    Ok(None)
}

pub fn serialize_abstract_installation_kind(
    abstract_installation_kind: &AbstractInstallationKind,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    match abstract_installation_kind {
        AbstractInstallationKind::BuildingInstallation(x) => {
            serialize_building_installation(x, xml_fragment_writer)
        }
        AbstractInstallationKind::BridgeInstallation(x) => {
            serialize_bridge_installation(x, xml_fragment_writer)
        }
        AbstractInstallationKind::TunnelInstallation(x) => {
            serialize_tunnel_installation(x, xml_fragment_writer)
        }
    }
}
