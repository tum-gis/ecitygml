use crate::Error;
use crate::gml::codec::construction::{
    deserialize_abstract_filling_element_kind, serialize_abstract_filling_element_kind,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::construction::AbstractFillingElementProperty;
use egml::io::codec::base::{
    deserialize_association_and_ownership_attributes,
    serialize_association_and_ownership_attributes,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::base::{HasAssociationAttributes, HasOwnershipAttributes};

pub fn deserialize_abstract_filling_element_property(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractFillingElementProperty, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let (association, ownership) = deserialize_association_and_ownership_attributes(xml_document)?;
    let object = deserialize_abstract_filling_element_kind(xml_document, index, config)?;

    Ok(AbstractFillingElementProperty::new(
        object,
        association,
        ownership,
    ))
}

pub fn serialize_abstract_filling_element_property(
    abstract_filling_element_property: &AbstractFillingElementProperty,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_association_and_ownership_attributes(
        abstract_filling_element_property.association(),
        abstract_filling_element_property.ownership(),
    );

    match abstract_filling_element_property.object() {
        Some(object) => {
            xml_fragment_writer.write_start_event_with_attributes(
                CityGmlNamespace::Core,
                CityGmlElement::AbstractFillingElementProperty,
                attributes,
            )?;
            serialize_abstract_filling_element_kind(object, xml_fragment_writer)?;
            xml_fragment_writer.write_end_event(
                CityGmlNamespace::Core,
                CityGmlElement::AbstractFillingElementProperty,
            )?;
        }
        None => {
            xml_fragment_writer.write_empty_element_with_attributes(
                CityGmlNamespace::Core,
                CityGmlElement::AbstractFillingElementProperty,
                attributes,
            )?;
        }
    }

    Ok(())
}
