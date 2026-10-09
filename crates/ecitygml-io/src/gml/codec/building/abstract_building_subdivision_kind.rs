use crate::Error;
use crate::gml::codec::building::{
    deserialize_building_unit, deserialize_storey, serialize_building_unit, serialize_storey,
};
use crate::gml::util::{CityGmlElement, CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::building::AbstractBuildingSubdivisionKind;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_building_subdivision_kind(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Option<AbstractBuildingSubdivisionKind>, Error> {
    if let Some(index) = index.first(CityGmlElement::Storey.into()) {
        let storey = deserialize_storey(&xml_document[index.range()], index, config)?;
        return Ok(Some(storey.into()));
    }

    if let Some(index) = index.first(CityGmlElement::BuildingUnit.into()) {
        let building_unit = deserialize_building_unit(&xml_document[index.range()], index, config)?;
        return Ok(Some(building_unit.into()));
    }

    Ok(None)
}

pub fn serialize_abstract_building_subdivision_kind(
    abstract_building_subdivision_kind: &AbstractBuildingSubdivisionKind,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    match abstract_building_subdivision_kind {
        AbstractBuildingSubdivisionKind::BuildingUnit(x) => {
            serialize_building_unit(x, xml_fragment_writer)
        }
        AbstractBuildingSubdivisionKind::Storey(x) => serialize_storey(x, xml_fragment_writer),
    }
}
