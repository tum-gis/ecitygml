use crate::Error;
use crate::gml::codec::bridge::{
    deserialize_bridge, deserialize_bridge_part, serialize_bridge, serialize_bridge_part,
};
use crate::gml::util::{CityGmlElement, CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::bridge::AbstractBridgeKind;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_bridge_kind(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Option<AbstractBridgeKind>, Error> {
    if let Some(index) = index.first(CityGmlElement::Bridge.into()) {
        let bridge = deserialize_bridge(&xml_document[index.range()], index, config)?;
        return Ok(Some(bridge.into()));
    }
    if let Some(index) = index.first(CityGmlElement::BridgePart.into()) {
        let bridge_part = deserialize_bridge_part(&xml_document[index.range()], index, config)?;
        return Ok(Some(bridge_part.into()));
    }

    Ok(None)
}

pub fn serialize_abstract_bridge_kind(
    abstract_bridge_kind: &AbstractBridgeKind,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    match abstract_bridge_kind {
        AbstractBridgeKind::Bridge(x) => serialize_bridge(x, xml_fragment_writer),
        AbstractBridgeKind::BridgePart(x) => serialize_bridge_part(x, xml_fragment_writer),
    }
}
