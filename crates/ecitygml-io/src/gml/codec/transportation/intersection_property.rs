use crate::Error;
use crate::gml::codec::transportation::{deserialize_intersection, serialize_intersection};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::transportation::IntersectionProperty;
use egml::io::codec::base::{
    deserialize_association_and_ownership_attributes,
    serialize_association_and_ownership_attributes,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::base::{HasAssociationAttributes, HasOwnershipAttributes};

pub fn deserialize_intersection_property(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<IntersectionProperty, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let (association, ownership) = deserialize_association_and_ownership_attributes(xml_document)?;
    let mut object = None;

    if let Some(index) = index.first(CityGmlElement::Intersection.into()) {
        object = Some(deserialize_intersection(
            &xml_document[index.range()],
            index,
            config,
        )?);
    }

    Ok(IntersectionProperty::new(object, association, ownership))
}

pub fn serialize_intersection_property(
    intersection_property: &IntersectionProperty,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_association_and_ownership_attributes(
        intersection_property.association(),
        intersection_property.ownership(),
    );

    match intersection_property.object() {
        Some(object) => {
            xml_fragment_writer.write_start_event_with_attributes(
                CityGmlNamespace::Transportation,
                CityGmlElement::IntersectionProperty,
                attributes,
            )?;
            serialize_intersection(object, xml_fragment_writer)?;
            xml_fragment_writer.write_end_event(
                CityGmlNamespace::Transportation,
                CityGmlElement::IntersectionProperty,
            )?;
        }
        None => {
            xml_fragment_writer.write_empty_element_with_attributes(
                CityGmlNamespace::Transportation,
                CityGmlElement::IntersectionProperty,
                attributes,
            )?;
        }
    }

    Ok(())
}
