use crate::Error;
use crate::gml::codec::tunnel::{
    deserialize_tunnel_constructive_element, serialize_tunnel_constructive_element,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::tunnel::TunnelConstructiveElementProperty;
use egml::io::codec::base::{
    deserialize_association_and_ownership_attributes,
    serialize_association_and_ownership_attributes,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::base::{HasAssociationAttributes, HasOwnershipAttributes};

pub fn deserialize_tunnel_constructive_element_property(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<TunnelConstructiveElementProperty, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let (association, ownership) = deserialize_association_and_ownership_attributes(xml_document)?;
    let mut object = None;

    if let Some(index) = index.first(CityGmlElement::TunnelConstructiveElement.into()) {
        object = Some(deserialize_tunnel_constructive_element(
            &xml_document[index.range()],
            index,
            config,
        )?);
    }

    Ok(TunnelConstructiveElementProperty::new(
        object,
        association,
        ownership,
    ))
}

pub fn serialize_tunnel_constructive_element_property(
    tunnel_constructive_element_property: &TunnelConstructiveElementProperty,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_association_and_ownership_attributes(
        tunnel_constructive_element_property.association(),
        tunnel_constructive_element_property.ownership(),
    );

    match tunnel_constructive_element_property.object() {
        Some(object) => {
            xml_fragment_writer.write_start_event_with_attributes(
                CityGmlNamespace::Tunnel,
                CityGmlElement::TunnelConstructiveElementProperty,
                attributes,
            )?;
            serialize_tunnel_constructive_element(object, xml_fragment_writer)?;
            xml_fragment_writer.write_end_event(
                CityGmlNamespace::Tunnel,
                CityGmlElement::TunnelConstructiveElementProperty,
            )?;
        }
        None => {
            xml_fragment_writer.write_empty_element_with_attributes(
                CityGmlNamespace::Tunnel,
                CityGmlElement::TunnelConstructiveElementProperty,
                attributes,
            )?;
        }
    }

    Ok(())
}
