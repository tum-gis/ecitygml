use crate::Error;
use crate::gml::codec::bridge::{deserialize_bridge_furniture, serialize_bridge_furniture};
use crate::gml::codec::building::{deserialize_building_furniture, serialize_building_furniture};
use crate::gml::codec::tunnel::{deserialize_tunnel_furniture, serialize_tunnel_furniture};
use crate::gml::util::{CityGmlElement, CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::construction::AbstractFurnitureKind;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_furniture_kind(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Option<AbstractFurnitureKind>, Error> {
    if let Some(index) = index.first(CityGmlElement::BridgeFurniture.into()) {
        let bridge_furniture =
            deserialize_bridge_furniture(&xml_document[index.range()], index, config)?;
        return Ok(Some(bridge_furniture.into()));
    }
    if let Some(index) = index.first(CityGmlElement::BuildingFurniture.into()) {
        let building_furniture =
            deserialize_building_furniture(&xml_document[index.range()], index, config)?;
        return Ok(Some(building_furniture.into()));
    }
    if let Some(index) = index.first(CityGmlElement::TunnelFurniture.into()) {
        let tunnel_furniture =
            deserialize_tunnel_furniture(&xml_document[index.range()], index, config)?;
        return Ok(Some(tunnel_furniture.into()));
    }

    Ok(None)
}

pub fn serialize_abstract_furniture_kind(
    abstract_furniture_kind: &AbstractFurnitureKind,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    match abstract_furniture_kind {
        AbstractFurnitureKind::BridgeFurniture(x) => {
            serialize_bridge_furniture(x, xml_fragment_writer)
        }
        AbstractFurnitureKind::BuildingFurniture(x) => {
            serialize_building_furniture(x, xml_fragment_writer)
        }
        AbstractFurnitureKind::TunnelFurniture(x) => {
            serialize_tunnel_furniture(x, xml_fragment_writer)
        }
    }
}
