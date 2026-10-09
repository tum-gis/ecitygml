use crate::Error;
use crate::gml::codec::tunnel::{
    deserialize_abstract_tunnel, serialize_abstract_tunnel, serialize_abstract_tunnel_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::tunnel::{AsAbstractTunnel, TunnelPart};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_tunnel_part(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<TunnelPart, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_tunnel = deserialize_abstract_tunnel(xml_document, index, config)?;
    let tunnel_part = TunnelPart::from_abstract_tunnel(abstract_tunnel);

    Ok(tunnel_part)
}

pub fn serialize_tunnel_part(
    tunnel_part: &TunnelPart,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_tunnel_part_attributes(tunnel_part);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Tunnel,
        CityGmlElement::TunnelPart,
        attributes,
    )?;

    serialize_abstract_tunnel(tunnel_part.abstract_tunnel(), xml_fragment_writer)?;

    xml_fragment_writer.write_end_event(CityGmlNamespace::Tunnel, CityGmlElement::TunnelPart)?;

    Ok(())
}

pub fn serialize_tunnel_part_attributes(tunnel_part: &TunnelPart) -> Vec<(String, String)> {
    serialize_abstract_tunnel_attributes(tunnel_part.abstract_tunnel())
}
