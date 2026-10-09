use crate::Error;
use crate::gml::codec::building::{
    deserialize_abstract_building, serialize_abstract_building,
    serialize_abstract_building_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::building::{AsAbstractBuilding, BuildingPart};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_building_part(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<BuildingPart, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_building = deserialize_abstract_building(xml_document, index, config)?;
    let building_part = BuildingPart::from_abstract_building(abstract_building);

    Ok(building_part)
}

pub fn serialize_building_part(
    building: &BuildingPart,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_building_part_attributes(building);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Building,
        CityGmlElement::BuildingPart,
        attributes,
    )?;

    serialize_abstract_building(building.abstract_building(), xml_fragment_writer)?;

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::Building, CityGmlElement::BuildingPart)?;

    Ok(())
}

pub fn serialize_building_part_attributes(building_part: &BuildingPart) -> Vec<(String, String)> {
    serialize_abstract_building_attributes(building_part.abstract_building())
}
