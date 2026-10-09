use crate::Error;
use crate::gml::codec::transportation::{deserialize_traffic_space, serialize_traffic_space};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::transportation::TrafficSpaceProperty;
use egml::io::codec::base::{
    deserialize_association_and_ownership_attributes,
    serialize_association_and_ownership_attributes,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::base::{HasAssociationAttributes, HasOwnershipAttributes};

pub fn deserialize_traffic_space_property(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<TrafficSpaceProperty, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let (association, ownership) = deserialize_association_and_ownership_attributes(xml_document)?;
    let mut object = None;

    if let Some(index) = index.first(CityGmlElement::TrafficSpace.into()) {
        object = Some(deserialize_traffic_space(
            &xml_document[index.range()],
            index,
            config,
        )?);
    }

    Ok(TrafficSpaceProperty::new(object, association, ownership))
}

pub fn serialize_traffic_space_property(
    traffic_space_property: &TrafficSpaceProperty,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_association_and_ownership_attributes(
        traffic_space_property.association(),
        traffic_space_property.ownership(),
    );

    match traffic_space_property.object() {
        Some(object) => {
            xml_fragment_writer.write_start_event_with_attributes(
                CityGmlNamespace::Transportation,
                CityGmlElement::TrafficSpaceProperty,
                attributes,
            )?;
            serialize_traffic_space(object, xml_fragment_writer)?;
            xml_fragment_writer.write_end_event(
                CityGmlNamespace::Transportation,
                CityGmlElement::TrafficSpaceProperty,
            )?;
        }
        None => {
            xml_fragment_writer.write_empty_element_with_attributes(
                CityGmlNamespace::Transportation,
                CityGmlElement::TrafficSpaceProperty,
                attributes,
            )?;
        }
    }

    Ok(())
}
