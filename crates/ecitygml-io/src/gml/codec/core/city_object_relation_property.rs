use crate::Error;
use crate::gml::codec::core::city_object_relation::{
    deserialize_city_object_relation, serialize_city_object_relation,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::core::CityObjectRelationProperty;
use egml::io::codec::base::{
    deserialize_association_and_ownership_attributes,
    serialize_association_and_ownership_attributes,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::base::{HasAssociationAttributes, HasOwnershipAttributes};

pub fn deserialize_city_object_relation_property(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<CityObjectRelationProperty, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let (association, ownership) = deserialize_association_and_ownership_attributes(xml_document)?;
    let mut object = None;

    if let Some(index) = index.first(CityGmlElement::CityObjectRelation.into()) {
        object = Some(deserialize_city_object_relation(
            &xml_document[index.range()],
            config,
        )?);
    }

    Ok(CityObjectRelationProperty::new(
        object,
        association,
        ownership,
    ))
}

pub fn serialize_city_object_relation_property(
    city_object_relation_property: &CityObjectRelationProperty,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_association_and_ownership_attributes(
        city_object_relation_property.association(),
        city_object_relation_property.ownership(),
    );

    match city_object_relation_property.object() {
        Some(object) => {
            xml_fragment_writer.write_start_event_with_attributes(
                CityGmlNamespace::Core,
                CityGmlElement::RelatedToProperty,
                attributes,
            )?;
            serialize_city_object_relation(object, xml_fragment_writer)?;
            xml_fragment_writer
                .write_end_event(CityGmlNamespace::Core, CityGmlElement::RelatedToProperty)?;
        }
        None => {
            xml_fragment_writer.write_empty_element_with_attributes(
                CityGmlNamespace::Core,
                CityGmlElement::RelatedToProperty,
                attributes,
            )?;
        }
    }

    Ok(())
}
