use crate::Error;
use crate::gml::codec::construction::abstract_filling_surface_kind::{
    deserialize_abstract_filling_surface_kind, serialize_abstract_filling_surface_kind,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::construction::AbstractFillingSurfaceProperty;
use egml::io::codec::base::{
    deserialize_association_and_ownership_attributes,
    serialize_association_and_ownership_attributes,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::base::{HasAssociationAttributes, HasOwnershipAttributes};

pub fn deserialize_abstract_filling_surface_property(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractFillingSurfaceProperty, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let (association, ownership) = deserialize_association_and_ownership_attributes(xml_document)?;
    let object = deserialize_abstract_filling_surface_kind(xml_document, index, config)?;

    Ok(AbstractFillingSurfaceProperty::new(
        object,
        association,
        ownership,
    ))
}

pub fn serialize_abstract_filling_surface_property(
    abstract_filling_surface_property: &AbstractFillingSurfaceProperty,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_association_and_ownership_attributes(
        abstract_filling_surface_property.association(),
        abstract_filling_surface_property.ownership(),
    );

    match abstract_filling_surface_property.object() {
        Some(object) => {
            xml_fragment_writer.write_start_event_with_attributes(
                CityGmlNamespace::Core,
                CityGmlElement::AbstractFillingSurfaceProperty,
                attributes,
            )?;
            serialize_abstract_filling_surface_kind(object, xml_fragment_writer)?;
            xml_fragment_writer.write_end_event(
                CityGmlNamespace::Core,
                CityGmlElement::AbstractFillingSurfaceProperty,
            )?;
        }
        None => {
            xml_fragment_writer.write_empty_element_with_attributes(
                CityGmlNamespace::Core,
                CityGmlElement::AbstractFillingSurfaceProperty,
                attributes,
            )?;
        }
    }

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;

    use egml::model::base::HasAssociationAttributes;
    use egml::model::xlink::HRef;

    #[test]
    fn test_deserialize_basic_href_boundary() {
        let xml_document =
            b"<con:fillingSurface xlink:href=\"#DEBY_LOD2_59772_4becb506-d53b-44ca-a483-e6a3d238b4c2\" />";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_filling_surface_property = deserialize_abstract_filling_surface_property(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            abstract_filling_surface_property
                .href()
                .expect("should exist"),
            &HRef::from("#DEBY_LOD2_59772_4becb506-d53b-44ca-a483-e6a3d238b4c2")
        );
    }
}
