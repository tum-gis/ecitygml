use crate::Error;
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::relief::TinProperty;
use egml::io::codec::base::{
    deserialize_association_and_ownership_attributes,
    serialize_association_and_ownership_attributes,
};
use egml::io::codec::geometry::primitives::{
    deserialize_triangulated_surface, serialize_triangulated_surface,
};
use egml::io::util::{ChunkedSink, GmlElement, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::base::{HasAssociationAttributes, HasOwnershipAttributes};

pub fn deserialize_tin_property(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<TinProperty, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let (association, ownership) = deserialize_association_and_ownership_attributes(xml_document)?;
    let mut object = None;

    if let Some(index) = index.first(GmlElement::TriangulatedSurface.into()) {
        let ts_slice = &xml_document[index.range()];
        let gml_index = index.convert(|e| match e {
            CombinedCityGmlElement::Gml(g) => Some(g),
            _ => None,
        });
        object = Some(deserialize_triangulated_surface(
            ts_slice,
            &gml_index,
            config.gml_config(),
        )?);
    };

    Ok(TinProperty::new(object, association, ownership))
}

pub fn serialize_tin_property(
    tin_property: &TinProperty,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_association_and_ownership_attributes(
        tin_property.association(),
        tin_property.ownership(),
    );

    match tin_property.object() {
        Some(object) => {
            xml_fragment_writer.write_start_event_with_attributes(
                CityGmlNamespace::Relief,
                CityGmlElement::TinProperty,
                attributes,
            )?;
            serialize_triangulated_surface(object, xml_fragment_writer)?;
            xml_fragment_writer
                .write_end_event(CityGmlNamespace::Relief, CityGmlElement::TinProperty)?;
        }
        None => {
            xml_fragment_writer.write_empty_element_with_attributes(
                CityGmlNamespace::Relief,
                CityGmlElement::TinProperty,
                attributes,
            )?;
        }
    }

    Ok(())
}
