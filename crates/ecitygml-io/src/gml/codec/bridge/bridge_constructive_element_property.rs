use crate::Error;
use crate::gml::codec::bridge::{
    deserialize_bridge_constructive_element, serialize_bridge_constructive_element,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::bridge::BridgeConstructiveElementProperty;
use egml::io::codec::base::{
    deserialize_association_and_ownership_attributes,
    serialize_association_and_ownership_attributes,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::base::{HasAssociationAttributes, HasOwnershipAttributes};

pub fn deserialize_bridge_constructive_element_property(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<BridgeConstructiveElementProperty, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let (association, ownership) = deserialize_association_and_ownership_attributes(xml_document)?;
    let mut object = None;

    if let Some(index) = index.first(CityGmlElement::BridgeConstructiveElement.into()) {
        object = Some(deserialize_bridge_constructive_element(
            &xml_document[index.range()],
            index,
            config,
        )?);
    }

    Ok(BridgeConstructiveElementProperty::new(
        object,
        association,
        ownership,
    ))
}

pub fn serialize_bridge_constructive_element_property(
    bridge_constructive_element_property: &BridgeConstructiveElementProperty,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_association_and_ownership_attributes(
        bridge_constructive_element_property.association(),
        bridge_constructive_element_property.ownership(),
    );

    match bridge_constructive_element_property.object() {
        Some(object) => {
            xml_fragment_writer.write_start_event_with_attributes(
                CityGmlNamespace::Bridge,
                CityGmlElement::BridgeConstructiveElementProperty,
                attributes,
            )?;
            serialize_bridge_constructive_element(object, xml_fragment_writer)?;
            xml_fragment_writer.write_end_event(
                CityGmlNamespace::Bridge,
                CityGmlElement::BridgeConstructiveElementProperty,
            )?;
        }
        None => {
            xml_fragment_writer.write_empty_element_with_attributes(
                CityGmlNamespace::Bridge,
                CityGmlElement::BridgeConstructiveElementProperty,
                attributes,
            )?;
        }
    }

    Ok(())
}
