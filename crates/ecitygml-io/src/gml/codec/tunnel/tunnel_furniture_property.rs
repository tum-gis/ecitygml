use crate::Error;
use crate::gml::codec::tunnel::{deserialize_tunnel_furniture, serialize_tunnel_furniture};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::tunnel::TunnelFurnitureProperty;
use egml::io::codec::base::{
    deserialize_association_and_ownership_attributes,
    serialize_association_and_ownership_attributes,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::base::{HasAssociationAttributes, HasOwnershipAttributes};

pub fn deserialize_tunnel_furniture_property(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<TunnelFurnitureProperty, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let (association, ownership) = deserialize_association_and_ownership_attributes(xml_document)?;
    let mut object = None;

    if let Some(index) = index.first(CityGmlElement::TunnelFurniture.into()) {
        object = Some(deserialize_tunnel_furniture(
            &xml_document[index.range()],
            index,
            config,
        )?);
    }

    Ok(TunnelFurnitureProperty::new(object, association, ownership))
}

pub fn serialize_tunnel_furniture_property(
    tunnel_furniture_property: &TunnelFurnitureProperty,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_association_and_ownership_attributes(
        tunnel_furniture_property.association(),
        tunnel_furniture_property.ownership(),
    );

    match tunnel_furniture_property.object() {
        Some(object) => {
            xml_fragment_writer.write_start_event_with_attributes(
                CityGmlNamespace::Tunnel,
                CityGmlElement::TunnelFurnitureProperty,
                attributes,
            )?;
            serialize_tunnel_furniture(object, xml_fragment_writer)?;
            xml_fragment_writer.write_end_event(
                CityGmlNamespace::Tunnel,
                CityGmlElement::TunnelFurnitureProperty,
            )?;
        }
        None => {
            xml_fragment_writer.write_empty_element_with_attributes(
                CityGmlNamespace::Tunnel,
                CityGmlElement::TunnelFurnitureProperty,
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
    fn test_deserialize_tunnel_furniture_property_with_inline_object() {
        let xml_document = b"<tun:tunnelFurniture>
    <tun:TunnelFurniture gml:id=\"BF_1\">
      <tun:class>7000</tun:class>
    </tun:TunnelFurniture>
  </tun:tunnelFurniture>";

        let tunnel_furniture_property = deserialize_tunnel_furniture_property(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let tunnel_furniture = tunnel_furniture_property
            .object()
            .expect("should be inline");
        assert_eq!(
            tunnel_furniture.feature_id(),
            &Id::try_from("BF_1").expect("should work")
        );
    }
}
