use crate::Error;
use crate::gml::codec::core::abstract_space_boundary_kind::{
    deserialize_abstract_space_boundary_kind, serialize_abstract_space_boundary_kind,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::core::AbstractSpaceBoundaryProperty;
use egml::io::codec::base::{
    deserialize_association_and_ownership_attributes,
    serialize_association_and_ownership_attributes,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::base::{HasAssociationAttributes, HasOwnershipAttributes};

pub fn deserialize_abstract_space_boundary_property(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractSpaceBoundaryProperty, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let (association, ownership) = deserialize_association_and_ownership_attributes(xml_document)?;
    let object = deserialize_abstract_space_boundary_kind(xml_document, index, config)?;

    Ok(AbstractSpaceBoundaryProperty::new(
        object,
        association,
        ownership,
    ))
}

pub fn serialize_abstract_space_boundary_property(
    abstract_space_boundary_property: &AbstractSpaceBoundaryProperty,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_association_and_ownership_attributes(
        abstract_space_boundary_property.association(),
        abstract_space_boundary_property.ownership(),
    );

    match abstract_space_boundary_property.object() {
        Some(object) => {
            xml_fragment_writer.write_start_event_with_attributes(
                CityGmlNamespace::Core,
                CityGmlElement::BoundaryProperty,
                attributes,
            )?;
            serialize_abstract_space_boundary_kind(object, xml_fragment_writer)?;
            xml_fragment_writer
                .write_end_event(CityGmlNamespace::Core, CityGmlElement::BoundaryProperty)?;
        }
        None => {
            xml_fragment_writer.write_empty_element_with_attributes(
                CityGmlNamespace::Core,
                CityGmlElement::BoundaryProperty,
                attributes,
            )?;
        }
    }

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;

    use ecitygml_core::model::core::AsAbstractFeature;
    use egml::model::base::{HasAssociationAttributes, Id};
    use egml::model::xlink::HRef;

    #[test]
    fn test_deserialize_basic_href_boundary() {
        let xml_document =
            b"<boundary xlink:href=\"#DEBY_LOD2_59772_4becb506-d53b-44ca-a483-e6a3d238b4c2\" />";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_space_boundary_property = deserialize_abstract_space_boundary_property(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            abstract_space_boundary_property
                .href()
                .expect("should exist"),
            &HRef::from("#DEBY_LOD2_59772_4becb506-d53b-44ca-a483-e6a3d238b4c2")
        );
    }

    #[test]
    fn test_deserialize_empty_closure_surface() {
        let xml_document =
            b"<boundary><ClosureSurface gml:id=\"fme-gen-f460209b-63b5-4ff8-92d5-cec932987265\"/></boundary>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_space_boundary_property = deserialize_abstract_space_boundary_property(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            abstract_space_boundary_property
                .object()
                .unwrap()
                .feature_id(),
            &Id::try_from("fme-gen-f460209b-63b5-4ff8-92d5-cec932987265").expect("should work")
        );
    }
}
