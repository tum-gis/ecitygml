use crate::Error;
use crate::gml::codec::building::{
    deserialize_building_constructive_element, serialize_building_constructive_element,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::building::BuildingConstructiveElementProperty;
use egml::io::codec::base::{
    deserialize_association_and_ownership_attributes,
    serialize_association_and_ownership_attributes,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::base::{HasAssociationAttributes, HasOwnershipAttributes};

pub fn deserialize_building_constructive_element_property(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<BuildingConstructiveElementProperty, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let (association, ownership) = deserialize_association_and_ownership_attributes(xml_document)?;
    let mut object = None;

    if let Some(index) = index.first(CityGmlElement::BuildingConstructiveElement.into()) {
        object = Some(deserialize_building_constructive_element(
            &xml_document[index.range()],
            index,
            config,
        )?);
    }

    Ok(BuildingConstructiveElementProperty::new(
        object,
        association,
        ownership,
    ))
}

pub fn serialize_building_constructive_element_property(
    building_constructive_element_property: &BuildingConstructiveElementProperty,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_association_and_ownership_attributes(
        building_constructive_element_property.association(),
        building_constructive_element_property.ownership(),
    );

    match building_constructive_element_property.object() {
        Some(object) => {
            xml_fragment_writer.write_start_event_with_attributes(
                CityGmlNamespace::Building,
                CityGmlElement::BuildingConstructiveElementProperty,
                attributes,
            )?;
            serialize_building_constructive_element(object, xml_fragment_writer)?;
            xml_fragment_writer.write_end_event(
                CityGmlNamespace::Building,
                CityGmlElement::BuildingConstructiveElementProperty,
            )?;
        }
        None => {
            xml_fragment_writer.write_empty_element_with_attributes(
                CityGmlNamespace::Building,
                CityGmlElement::BuildingConstructiveElementProperty,
                attributes,
            )?;
        }
    }

    Ok(())
}
