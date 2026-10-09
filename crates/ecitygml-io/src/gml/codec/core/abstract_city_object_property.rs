use crate::Error;
use crate::gml::codec::core::abstract_city_object_kind::{
    deserialize_abstract_city_object_kind, serialize_abstract_city_object_kind,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::core::AbstractCityObjectProperty;
use egml::io::codec::base::{
    deserialize_association_and_ownership_attributes,
    serialize_association_and_ownership_attributes,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::base::{HasAssociationAttributes, HasOwnershipAttributes};

pub fn deserialize_abstract_city_object_property(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractCityObjectProperty, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let (association, ownership) = deserialize_association_and_ownership_attributes(xml_document)?;
    let object = deserialize_abstract_city_object_kind(xml_document, index, config)?;

    Ok(AbstractCityObjectProperty::new(
        object,
        association,
        ownership,
    ))
}

pub fn serialize_abstract_city_object_member_property(
    abstract_city_object_property: &AbstractCityObjectProperty,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_association_and_ownership_attributes(
        abstract_city_object_property.association(),
        abstract_city_object_property.ownership(),
    );

    match abstract_city_object_property.object() {
        Some(object) => {
            xml_fragment_writer.write_start_event_with_attributes(
                CityGmlNamespace::Core,
                CityGmlElement::CityObjectMemberProperty,
                attributes,
            )?;
            serialize_abstract_city_object_kind(object, xml_fragment_writer)?;
            xml_fragment_writer.write_end_event(
                CityGmlNamespace::Core,
                CityGmlElement::CityObjectMemberProperty,
            )?;
        }
        None => {
            xml_fragment_writer.write_empty_element_with_attributes(
                CityGmlNamespace::Core,
                CityGmlElement::CityObjectMemberProperty,
                attributes,
            )?;
        }
    }

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::model::xlink::HRef;
    #[test]
    fn test_deserialize_basic_href_boundary() {
        let xml_document =
            b"<core:cityObjectMember xlink:href=\"#DEBY_LOD2_59772_4becb506-d53b-44ca-a483-e6a3d238b4c2\" />";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_filling_surface_property = deserialize_abstract_city_object_property(
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
