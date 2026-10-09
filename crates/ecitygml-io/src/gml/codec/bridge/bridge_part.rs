use crate::Error;
use crate::gml::codec::bridge::{
    deserialize_abstract_bridge, serialize_abstract_bridge, serialize_abstract_bridge_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::bridge::{AsAbstractBridge, BridgePart};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_bridge_part(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<BridgePart, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_bridge = deserialize_abstract_bridge(xml_document, index, config)?;
    let bridge_part = BridgePart::from_abstract_bridge(abstract_bridge);

    Ok(bridge_part)
}

pub fn serialize_bridge_part(
    bridge_part: &BridgePart,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_bridge_part_attributes(bridge_part);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Bridge,
        CityGmlElement::BridgePart,
        attributes,
    )?;

    serialize_abstract_bridge(bridge_part.abstract_bridge(), xml_fragment_writer)?;

    xml_fragment_writer.write_end_event(CityGmlNamespace::Bridge, CityGmlElement::BridgePart)?;

    Ok(())
}

pub fn serialize_bridge_part_attributes(bridge_part: &BridgePart) -> Vec<(String, String)> {
    serialize_abstract_bridge_attributes(bridge_part.abstract_bridge())
}
