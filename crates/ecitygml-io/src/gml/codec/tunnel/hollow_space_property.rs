use crate::Error;
use crate::gml::codec::tunnel::{deserialize_hollow_space, serialize_hollow_space};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::tunnel::HollowSpaceProperty;
use egml::io::codec::base::{
    deserialize_association_and_ownership_attributes,
    serialize_association_and_ownership_attributes,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::base::{HasAssociationAttributes, HasOwnershipAttributes};

pub fn deserialize_hollow_space_property(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<HollowSpaceProperty, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let (association, ownership) = deserialize_association_and_ownership_attributes(xml_document)?;
    let mut object = None;

    if let Some(index) = index.first(CityGmlElement::HollowSpace.into()) {
        object = Some(deserialize_hollow_space(
            &xml_document[index.range()],
            index,
            config,
        )?);
    }

    Ok(HollowSpaceProperty::new(object, association, ownership))
}

pub fn serialize_hollow_space_property(
    hollow_space_property: &HollowSpaceProperty,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_association_and_ownership_attributes(
        hollow_space_property.association(),
        hollow_space_property.ownership(),
    );

    match hollow_space_property.object() {
        Some(object) => {
            xml_fragment_writer.write_start_event_with_attributes(
                CityGmlNamespace::Tunnel,
                CityGmlElement::HollowSpaceProperty,
                attributes,
            )?;
            serialize_hollow_space(object, xml_fragment_writer)?;
            xml_fragment_writer.write_end_event(
                CityGmlNamespace::Tunnel,
                CityGmlElement::HollowSpaceProperty,
            )?;
        }
        None => {
            xml_fragment_writer.write_empty_element_with_attributes(
                CityGmlNamespace::Tunnel,
                CityGmlElement::HollowSpaceProperty,
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
    fn test_deserialize_hollow_space_property_with_inline_object() {
        let xml_document = b"<tun:hollowSpace>
    <tun:HollowSpace gml:id=\"HS_1\">
      <tun:class>5000</tun:class>
    </tun:HollowSpace>
  </tun:hollowSpace>";

        let hollow_space_property = deserialize_hollow_space_property(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let hollow_space = hollow_space_property.object().expect("should be inline");
        assert_eq!(
            hollow_space.feature_id(),
            &Id::try_from("HS_1").expect("should work")
        );
    }
}
