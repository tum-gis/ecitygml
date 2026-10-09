use crate::Error;
use crate::gml::codec::bridge::deserialize_bridge_constructive_element;
use crate::gml::codec::building::deserialize_building_constructive_element;
use crate::gml::codec::construction::{
    serialize_ceiling_surface, serialize_floor_surface, serialize_ground_surface,
    serialize_interior_wall_surface, serialize_outer_ceiling_surface,
    serialize_outer_floor_surface, serialize_roof_surface, serialize_wall_surface,
};
use crate::gml::codec::tunnel::deserialize_tunnel_constructive_element;
use crate::gml::util::{CityGmlElement, CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::construction::{
    AbstractConstructionSurfaceKind, AbstractConstructiveElementKind,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_constructive_element_kind(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Option<AbstractConstructiveElementKind>, Error> {
    if let Some(index) = index.first(CityGmlElement::BuildingConstructiveElement.into()) {
        let building_constructive_element =
            deserialize_building_constructive_element(&xml_document[index.range()], index, config)?;
        return Ok(Some(building_constructive_element.into()));
    }
    if let Some(index) = index.first(CityGmlElement::BridgeConstructiveElement.into()) {
        let bridge_constructive_element =
            deserialize_bridge_constructive_element(&xml_document[index.range()], index, config)?;
        return Ok(Some(bridge_constructive_element.into()));
    }
    if let Some(index) = index.first(CityGmlElement::TunnelConstructiveElement.into()) {
        let tunnel_constructive_element =
            deserialize_tunnel_constructive_element(&xml_document[index.range()], index, config)?;
        return Ok(Some(tunnel_constructive_element.into()));
    }

    Ok(None)
}

pub fn serialize_abstract_construction_surface_kind(
    abstract_construction_surface_kind: &AbstractConstructionSurfaceKind,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    match abstract_construction_surface_kind {
        AbstractConstructionSurfaceKind::CeilingSurface(x) => {
            serialize_ceiling_surface(x, xml_fragment_writer)
        }
        AbstractConstructionSurfaceKind::FloorSurface(x) => {
            serialize_floor_surface(x, xml_fragment_writer)
        }
        AbstractConstructionSurfaceKind::GroundSurface(x) => {
            serialize_ground_surface(x, xml_fragment_writer)
        }
        AbstractConstructionSurfaceKind::InteriorWallSurface(x) => {
            serialize_interior_wall_surface(x, xml_fragment_writer)
        }
        AbstractConstructionSurfaceKind::OuterCeilingSurface(x) => {
            serialize_outer_ceiling_surface(x, xml_fragment_writer)
        }
        AbstractConstructionSurfaceKind::OuterFloorSurface(x) => {
            serialize_outer_floor_surface(x, xml_fragment_writer)
        }
        AbstractConstructionSurfaceKind::RoofSurface(x) => {
            serialize_roof_surface(x, xml_fragment_writer)
        }
        AbstractConstructionSurfaceKind::WallSurface(x) => {
            serialize_wall_surface(x, xml_fragment_writer)
        }
    }
}
