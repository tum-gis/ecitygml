use crate::Error;
use crate::gml::codec::building::{deserialize_building_part, serialize_building_part};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::building::BuildingPartProperty;
use egml::io::codec::base::{
    deserialize_association_and_ownership_attributes,
    serialize_association_and_ownership_attributes,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::base::{HasAssociationAttributes, HasOwnershipAttributes};

pub fn deserialize_building_part_property(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<BuildingPartProperty, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let (association, ownership) = deserialize_association_and_ownership_attributes(xml_document)?;
    let mut object = None;

    if let Some(index) = index.first(CityGmlElement::BuildingPart.into()) {
        object = Some(deserialize_building_part(
            &xml_document[index.range()],
            index,
            config,
        )?);
    }

    Ok(BuildingPartProperty::new(object, association, ownership))
}

pub fn serialize_building_part_property(
    building_part_property: &BuildingPartProperty,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_association_and_ownership_attributes(
        building_part_property.association(),
        building_part_property.ownership(),
    );

    match building_part_property.object() {
        Some(object) => {
            xml_fragment_writer.write_start_event_with_attributes(
                CityGmlNamespace::Building,
                CityGmlElement::BuildingPartProperty,
                attributes,
            )?;
            serialize_building_part(object, xml_fragment_writer)?;
            xml_fragment_writer.write_end_event(
                CityGmlNamespace::Building,
                CityGmlElement::BuildingPartProperty,
            )?;
        }
        None => {
            xml_fragment_writer.write_empty_element_with_attributes(
                CityGmlNamespace::Building,
                CityGmlElement::BuildingPartProperty,
                attributes,
            )?;
        }
    }

    Ok(())
}
