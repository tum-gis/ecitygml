use crate::Error;
use crate::gml::codec::core::abstract_appearance_kind::{
    deserialize_abstract_appearance_kind, serialize_abstract_appearance_kind,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::core::AbstractAppearanceProperty;
use egml::io::codec::base::{
    deserialize_association_and_ownership_attributes,
    serialize_association_and_ownership_attributes,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::base::{HasAssociationAttributes, HasOwnershipAttributes};

pub fn deserialize_abstract_appearance_property(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractAppearanceProperty, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let (association, ownership) = deserialize_association_and_ownership_attributes(xml_document)?;
    let object = deserialize_abstract_appearance_kind(xml_document, index, config)?;

    Ok(AbstractAppearanceProperty::new(
        object,
        association,
        ownership,
    ))
}

pub fn serialize_abstract_appearance_property(
    abstract_appearance_property: &AbstractAppearanceProperty,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_association_and_ownership_attributes(
        abstract_appearance_property.association(),
        abstract_appearance_property.ownership(),
    );

    match abstract_appearance_property.object() {
        Some(object) => {
            xml_fragment_writer.write_start_event_with_attributes(
                CityGmlNamespace::Appearance,
                CityGmlElement::AbstractAppearanceProperty,
                attributes,
            )?;
            serialize_abstract_appearance_kind(object, xml_fragment_writer)?;
            xml_fragment_writer.write_end_event(
                CityGmlNamespace::Appearance,
                CityGmlElement::AbstractAppearanceProperty,
            )?;
        }
        None => {
            xml_fragment_writer.write_empty_element_with_attributes(
                CityGmlNamespace::Appearance,
                CityGmlElement::AbstractAppearanceProperty,
                attributes,
            )?;
        }
    }

    Ok(())
}

pub fn serialize_abstract_appearance_member_property(
    abstract_appearance_property: &AbstractAppearanceProperty,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_association_and_ownership_attributes(
        abstract_appearance_property.association(),
        abstract_appearance_property.ownership(),
    );

    match abstract_appearance_property.object() {
        Some(object) => {
            xml_fragment_writer.write_start_event_with_attributes(
                CityGmlNamespace::Core,
                CityGmlElement::AppearanceMemberProperty,
                attributes,
            )?;
            serialize_abstract_appearance_kind(object, xml_fragment_writer)?;
            xml_fragment_writer.write_end_event(
                CityGmlNamespace::Core,
                CityGmlElement::AppearanceMemberProperty,
            )?;
        }
        None => {
            xml_fragment_writer.write_empty_element_with_attributes(
                CityGmlNamespace::Core,
                CityGmlElement::AppearanceMemberProperty,
                attributes,
            )?;
        }
    }

    Ok(())
}
