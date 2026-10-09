use crate::Error;
use crate::gml::codec::relief::abstract_relief_component_kind::{
    deserialize_abstract_relief_component_kind, serialize_abstract_relief_component_kind,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::relief::AbstractReliefComponentProperty;
use egml::io::codec::base::{
    deserialize_association_and_ownership_attributes,
    serialize_association_and_ownership_attributes,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::base::{HasAssociationAttributes, HasOwnershipAttributes};

pub fn deserialize_abstract_relief_component_property(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractReliefComponentProperty, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let (association, ownership) = deserialize_association_and_ownership_attributes(xml_document)?;
    let object = deserialize_abstract_relief_component_kind(xml_document, index, config)?;

    Ok(AbstractReliefComponentProperty::new(
        object,
        association,
        ownership,
    ))
}

pub fn serialize_abstract_relief_component_property(
    abstract_relief_component_property: &AbstractReliefComponentProperty,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_association_and_ownership_attributes(
        abstract_relief_component_property.association(),
        abstract_relief_component_property.ownership(),
    );

    match abstract_relief_component_property.object() {
        Some(object) => {
            xml_fragment_writer.write_start_event_with_attributes(
                CityGmlNamespace::Relief,
                CityGmlElement::AbstractReliefComponentProperty,
                attributes,
            )?;
            serialize_abstract_relief_component_kind(object, xml_fragment_writer)?;
            xml_fragment_writer.write_end_event(
                CityGmlNamespace::Relief,
                CityGmlElement::AbstractReliefComponentProperty,
            )?;
        }
        None => {
            xml_fragment_writer.write_empty_element_with_attributes(
                CityGmlNamespace::Relief,
                CityGmlElement::AbstractReliefComponentProperty,
                attributes,
            )?;
        }
    }

    Ok(())
}
