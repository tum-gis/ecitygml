use crate::Error;
use crate::gml::codec::building::{deserialize_building_room, serialize_building_room};
use crate::gml::codec::transportation::{
    deserialize_abstract_transportation_space_kind, deserialize_auxiliary_traffic_space,
    deserialize_clearance_space, deserialize_hole, deserialize_traffic_space,
    serialize_abstract_transportation_space_kind, serialize_auxiliary_traffic_space,
    serialize_clearance_space, serialize_hole, serialize_traffic_space,
};
use crate::gml::util::{CityGmlElement, CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::core::AbstractUnoccupiedSpaceKind;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_unoccupied_space_kind(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Option<AbstractUnoccupiedSpaceKind>, Error> {
    if let Some(index) = index.first(CityGmlElement::AuxiliaryTrafficSpace.into()) {
        let auxiliary_traffic_space =
            deserialize_auxiliary_traffic_space(&xml_document[index.range()], index, config)?;
        return Ok(Some(auxiliary_traffic_space.into()));
    }
    if let Some(index) = index.first(CityGmlElement::BuildingRoom.into()) {
        let building_room = deserialize_building_room(&xml_document[index.range()], index, config)?;
        return Ok(Some(building_room.into()));
    }
    if let Some(index) = index.first(CityGmlElement::Hole.into()) {
        let hole = deserialize_hole(&xml_document[index.range()], index, config)?;
        return Ok(Some(hole.into()));
    }
    if let Some(index) = index.first(CityGmlElement::ClearanceSpace.into()) {
        let clearance_space =
            deserialize_clearance_space(&xml_document[index.range()], index, config)?;
        return Ok(Some(clearance_space.into()));
    }
    if let Some(index) = index.first(CityGmlElement::TrafficSpace.into()) {
        let traffic_space = deserialize_traffic_space(&xml_document[index.range()], index, config)?;
        return Ok(Some(traffic_space.into()));
    }
    if let Some(x) = deserialize_abstract_transportation_space_kind(xml_document, index, config)? {
        return Ok(Some(x.into()));
    }

    Ok(None)
}

pub fn serialize_abstract_unoccupied_space_kind(
    abstract_unoccupied_space_kind: &AbstractUnoccupiedSpaceKind,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    match abstract_unoccupied_space_kind {
        AbstractUnoccupiedSpaceKind::AuxiliaryTrafficSpace(x) => {
            serialize_auxiliary_traffic_space(x, xml_fragment_writer)
        }
        AbstractUnoccupiedSpaceKind::BuildingRoom(x) => {
            serialize_building_room(x, xml_fragment_writer)
        }
        AbstractUnoccupiedSpaceKind::ClearanceSpace(x) => {
            serialize_clearance_space(x, xml_fragment_writer)
        }
        AbstractUnoccupiedSpaceKind::Hole(x) => serialize_hole(x, xml_fragment_writer),
        AbstractUnoccupiedSpaceKind::TrafficSpace(x) => {
            serialize_traffic_space(x, xml_fragment_writer)
        }
        AbstractUnoccupiedSpaceKind::AbstractTransportationSpaceKind(x) => {
            serialize_abstract_transportation_space_kind(x, xml_fragment_writer)
        }
    }
}
