use crate::Error;
use crate::gml::codec::building::{deserialize_building_furniture, serialize_building_furniture};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::building::BuildingFurnitureProperty;
use egml::io::codec::base::{
    deserialize_association_and_ownership_attributes,
    serialize_association_and_ownership_attributes,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::base::{HasAssociationAttributes, HasOwnershipAttributes};

pub fn deserialize_building_furniture_property(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<BuildingFurnitureProperty, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let (association, ownership) = deserialize_association_and_ownership_attributes(xml_document)?;
    let mut object = None;

    if let Some(index) = index.first(CityGmlElement::BuildingFurniture.into()) {
        object = Some(deserialize_building_furniture(
            &xml_document[index.range()],
            index,
            config,
        )?);
    }

    Ok(BuildingFurnitureProperty::new(
        object,
        association,
        ownership,
    ))
}

pub fn serialize_building_furniture_property(
    building_furniture_property: &BuildingFurnitureProperty,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_association_and_ownership_attributes(
        building_furniture_property.association(),
        building_furniture_property.ownership(),
    );

    match building_furniture_property.object() {
        Some(object) => {
            xml_fragment_writer.write_start_event_with_attributes(
                CityGmlNamespace::Building,
                CityGmlElement::BuildingFurnitureProperty,
                attributes,
            )?;
            serialize_building_furniture(object, xml_fragment_writer)?;
            xml_fragment_writer.write_end_event(
                CityGmlNamespace::Building,
                CityGmlElement::BuildingFurnitureProperty,
            )?;
        }
        None => {
            xml_fragment_writer.write_empty_element_with_attributes(
                CityGmlNamespace::Building,
                CityGmlElement::BuildingFurnitureProperty,
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
    use egml::model::base::Id;

    #[test]
    fn test_deserialize_building_furniture_property_with_inline_object() {
        let xml_document = b"<bldg:buildingFurniture>
    <bldg:BuildingFurniture gml:id=\"BF_1\">
      <bldg:class>7000</bldg:class>
    </bldg:BuildingFurniture>
  </bldg:buildingFurniture>";

        let building_furniture_property = deserialize_building_furniture_property(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let building_furniture = building_furniture_property
            .object()
            .expect("should be inline");
        assert_eq!(
            building_furniture.feature_id(),
            &Id::try_from("BF_1").expect("should work")
        );
    }
}
