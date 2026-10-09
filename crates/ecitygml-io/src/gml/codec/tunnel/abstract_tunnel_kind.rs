use crate::Error;
use crate::gml::codec::tunnel::{
    deserialize_tunnel, deserialize_tunnel_part, serialize_tunnel, serialize_tunnel_part,
};
use crate::gml::util::{CityGmlElement, CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::tunnel::AbstractTunnelKind;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_tunnel_kind(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Option<AbstractTunnelKind>, Error> {
    if let Some(index) = index.first(CityGmlElement::Tunnel.into()) {
        let tunnel = deserialize_tunnel(&xml_document[index.range()], index, config)?;
        return Ok(Some(tunnel.into()));
    }
    if let Some(index) = index.first(CityGmlElement::TunnelPart.into()) {
        let tunnel_part = deserialize_tunnel_part(&xml_document[index.range()], index, config)?;
        return Ok(Some(tunnel_part.into()));
    }

    Ok(None)
}

pub fn serialize_abstract_tunnel_kind(
    abstract_tunnel_kind: &AbstractTunnelKind,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    match abstract_tunnel_kind {
        AbstractTunnelKind::Tunnel(x) => serialize_tunnel(x, xml_fragment_writer),
        AbstractTunnelKind::TunnelPart(x) => serialize_tunnel_part(x, xml_fragment_writer),
    }
}
