use crate::Error;
use crate::gml::codec::building::abstract_building_subdivision_kind::{
    deserialize_abstract_building_subdivision_kind, serialize_abstract_building_subdivision_kind,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::building::AbstractBuildingSubdivisionProperty;
use egml::io::codec::base::{
    deserialize_association_and_ownership_attributes,
    serialize_association_and_ownership_attributes,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::base::{HasAssociationAttributes, HasOwnershipAttributes};

pub fn deserialize_abstract_building_subdivision_property(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractBuildingSubdivisionProperty, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let (association, ownership) = deserialize_association_and_ownership_attributes(xml_document)?;
    let object = deserialize_abstract_building_subdivision_kind(xml_document, index, config)?;

    Ok(AbstractBuildingSubdivisionProperty::new(
        object,
        association,
        ownership,
    ))
}

pub fn serialize_abstract_building_subdivision_property(
    abstract_building_subdivision_property: &AbstractBuildingSubdivisionProperty,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_association_and_ownership_attributes(
        abstract_building_subdivision_property.association(),
        abstract_building_subdivision_property.ownership(),
    );

    match abstract_building_subdivision_property.object() {
        Some(object) => {
            xml_fragment_writer.write_start_event_with_attributes(
                CityGmlNamespace::Building,
                CityGmlElement::AbstractBuildingSubdivisionProperty,
                attributes,
            )?;
            serialize_abstract_building_subdivision_kind(object, xml_fragment_writer)?;
            xml_fragment_writer.write_end_event(
                CityGmlNamespace::Building,
                CityGmlElement::AbstractBuildingSubdivisionProperty,
            )?;
        }
        None => {
            xml_fragment_writer.write_empty_element_with_attributes(
                CityGmlNamespace::Building,
                CityGmlElement::AbstractBuildingSubdivisionProperty,
                attributes,
            )?;
        }
    }

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;

    use egml::model::base::AsAbstractGml;
    use egml::model::basic_types::Code;

    #[test]
    fn test_deserialize_basic_href_boundary() {
        let xml_document = b"<bldg:buildingSubdivision>
            <bldg:Storey>
              <gml:name>Second Floor</gml:name>
            </bldg:Storey>
          </bldg:buildingSubdivision>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_building_subdivision_property =
            deserialize_abstract_building_subdivision_property(
                xml_document,
                &index,
                &DeserializationConfig::default(),
            )
            .expect("should work");
        let abstract_building_subdivision_kind =
            abstract_building_subdivision_property.object().unwrap();

        assert_eq!(
            abstract_building_subdivision_kind.names().first().unwrap(),
            &Code::new("Second Floor")
        );
    }
}
