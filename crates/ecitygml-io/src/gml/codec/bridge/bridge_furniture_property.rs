use crate::Error;
use crate::gml::codec::bridge::{deserialize_bridge_furniture, serialize_bridge_furniture};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::bridge::BridgeFurnitureProperty;
use egml::io::codec::base::{
    deserialize_association_and_ownership_attributes,
    serialize_association_and_ownership_attributes,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::base::{HasAssociationAttributes, HasOwnershipAttributes};

pub fn deserialize_bridge_furniture_property(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<BridgeFurnitureProperty, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let (association, ownership) = deserialize_association_and_ownership_attributes(xml_document)?;
    let mut object = None;

    if let Some(index) = index.first(CityGmlElement::BridgeFurniture.into()) {
        object = Some(deserialize_bridge_furniture(
            &xml_document[index.range()],
            index,
            config,
        )?);
    }

    Ok(BridgeFurnitureProperty::new(object, association, ownership))
}

pub fn serialize_bridge_furniture_property(
    bridge_furniture_property: &BridgeFurnitureProperty,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_association_and_ownership_attributes(
        bridge_furniture_property.association(),
        bridge_furniture_property.ownership(),
    );

    match bridge_furniture_property.object() {
        Some(object) => {
            xml_fragment_writer.write_start_event_with_attributes(
                CityGmlNamespace::Bridge,
                CityGmlElement::BridgeFurnitureProperty,
                attributes,
            )?;
            serialize_bridge_furniture(object, xml_fragment_writer)?;
            xml_fragment_writer.write_end_event(
                CityGmlNamespace::Bridge,
                CityGmlElement::BridgeFurnitureProperty,
            )?;
        }
        None => {
            xml_fragment_writer.write_empty_element_with_attributes(
                CityGmlNamespace::Bridge,
                CityGmlElement::BridgeFurnitureProperty,
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
    fn test_deserialize_bridge_furniture_property_with_inline_object() {
        let xml_document = b"<brid:bridgeFurniture>
    <brid:BridgeFurniture gml:id=\"BF_1\">
      <brid:class>7000</brid:class>
    </brid:BridgeFurniture>
  </brid:bridgeFurniture>";

        let bridge_furniture_property = deserialize_bridge_furniture_property(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let bridge_furniture = bridge_furniture_property
            .object()
            .expect("should be inline");
        assert_eq!(
            bridge_furniture.feature_id(),
            &Id::try_from("BF_1").expect("should work")
        );
    }
}
