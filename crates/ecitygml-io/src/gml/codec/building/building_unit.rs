use crate::Error;
use crate::gml::codec::building::abstract_building_subdivision::{
    deserialize_abstract_building_subdivision, serialize_abstract_building_subdivision,
    serialize_abstract_building_subdivision_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

use ecitygml_core::model::building::{AsAbstractBuildingSubdivision, BuildingUnit};

pub fn deserialize_building_unit(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<BuildingUnit, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_building_subdivision =
        deserialize_abstract_building_subdivision(xml_document, index, config)?;
    let building_unit =
        BuildingUnit::from_abstract_building_subdivision(abstract_building_subdivision);

    Ok(building_unit)
}

pub fn serialize_building_unit(
    building_unit: &BuildingUnit,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_building_unit_attributes(building_unit);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Building,
        CityGmlElement::BuildingUnit,
        attributes,
    )?;

    serialize_abstract_building_subdivision(
        building_unit.abstract_building_subdivision(),
        xml_fragment_writer,
    )?;

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::Building, CityGmlElement::BuildingUnit)?;

    Ok(())
}

pub fn serialize_building_unit_attributes(building_unit: &BuildingUnit) -> Vec<(String, String)> {
    serialize_abstract_building_subdivision_attributes(
        building_unit.abstract_building_subdivision(),
    )
}
