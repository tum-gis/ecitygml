use crate::Error;
use crate::gml::codec::building::{
    deserialize_building, deserialize_building_part, serialize_building, serialize_building_part,
};
use crate::gml::util::{CityGmlElement, CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::building::AbstractBuildingKind;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_building_kind(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Option<AbstractBuildingKind>, Error> {
    if let Some(index) = index.first(CityGmlElement::Building.into()) {
        let building = deserialize_building(&xml_document[index.range()], index, config)?;
        return Ok(Some(building.into()));
    }
    if let Some(index) = index.first(CityGmlElement::BuildingPart.into()) {
        let building_part = deserialize_building_part(&xml_document[index.range()], index, config)?;
        return Ok(Some(building_part.into()));
    }

    Ok(None)
}

pub fn serialize_abstract_building_kind(
    abstract_building_kind: &AbstractBuildingKind,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    match abstract_building_kind {
        AbstractBuildingKind::Building(x) => serialize_building(x, xml_fragment_writer),
        AbstractBuildingKind::BuildingPart(x) => serialize_building_part(x, xml_fragment_writer),
    }
}
