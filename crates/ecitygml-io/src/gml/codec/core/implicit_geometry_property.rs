use crate::Error;
use crate::gml::codec::core::implicit_geometry::{
    deserialize_implicit_geometry, serialize_implicit_geometry,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::core::ImplicitGeometryProperty;
use egml::io::codec::base::{
    deserialize_association_and_ownership_attributes,
    serialize_association_and_ownership_attributes,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::base::{HasAssociationAttributes, HasOwnershipAttributes};

pub fn deserialize_implicit_geometry_property(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<ImplicitGeometryProperty, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let (association, ownership) = deserialize_association_and_ownership_attributes(xml_document)?;
    let mut object = None;

    if let Some(index) = index.first(CityGmlElement::ImplicitGeometry.into()) {
        object = Some(deserialize_implicit_geometry(
            &xml_document[index.range()],
            index,
            config,
        )?);
    }

    Ok(ImplicitGeometryProperty::new(
        object,
        association,
        ownership,
    ))
}

pub fn serialize_implicit_geometry_property(
    implicit_geometry_property: &ImplicitGeometryProperty,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
    target_xml_namespace: CityGmlNamespace,
    target_xml_element: CityGmlElement,
) -> Result<(), Error> {
    let attributes = serialize_association_and_ownership_attributes(
        implicit_geometry_property.association(),
        implicit_geometry_property.ownership(),
    );

    match implicit_geometry_property.object() {
        Some(object) => {
            xml_fragment_writer.write_start_event_with_attributes(
                target_xml_namespace,
                target_xml_element,
                attributes,
            )?;
            serialize_implicit_geometry(object, xml_fragment_writer)?;
            xml_fragment_writer.write_end_event(target_xml_namespace, target_xml_element)?;
        }
        None => {
            xml_fragment_writer.write_empty_element_with_attributes(
                target_xml_namespace,
                target_xml_element,
                attributes,
            )?;
        }
    }

    Ok(())
}
