use crate::Error;
use crate::gml::codec::bridge::{deserialize_abstract_bridge_kind, serialize_abstract_bridge_kind};
use crate::gml::codec::building::{
    deserialize_abstract_building_kind, serialize_abstract_building_kind,
};
use crate::gml::codec::tunnel::{deserialize_abstract_tunnel_kind, serialize_abstract_tunnel_kind};
use crate::gml::util::{CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::construction::AbstractConstructionKind;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_construction_kind(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Option<AbstractConstructionKind>, Error> {
    let abstract_building_kind = deserialize_abstract_building_kind(xml_document, index, config)?;
    if let Some(x) = abstract_building_kind {
        return Ok(Some(AbstractConstructionKind::AbstractBuildingKind(x)));
    }

    let abstract_bridge_kind = deserialize_abstract_bridge_kind(xml_document, index, config)?;
    if let Some(x) = abstract_bridge_kind {
        return Ok(Some(AbstractConstructionKind::AbstractBridgeKind(x)));
    }

    let abstract_tunnel_kind = deserialize_abstract_tunnel_kind(xml_document, index, config)?;
    if let Some(x) = abstract_tunnel_kind {
        return Ok(Some(AbstractConstructionKind::AbstractTunnelKind(x)));
    }

    Ok(None)
}

pub fn serialize_abstract_construction_kind(
    abstract_construction_kind: &AbstractConstructionKind,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    match abstract_construction_kind {
        AbstractConstructionKind::AbstractBuildingKind(x) => {
            serialize_abstract_building_kind(x, xml_fragment_writer)
        }
        AbstractConstructionKind::AbstractBridgeKind(x) => {
            serialize_abstract_bridge_kind(x, xml_fragment_writer)
        }
        AbstractConstructionKind::AbstractTunnelKind(x) => {
            serialize_abstract_tunnel_kind(x, xml_fragment_writer)
        }
    }
}
