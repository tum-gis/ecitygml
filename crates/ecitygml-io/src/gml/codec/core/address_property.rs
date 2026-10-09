use crate::Error;
use crate::gml::codec::core::address::{deserialize_address, serialize_address};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::core::AddressProperty;
use egml::io::codec::base::{
    deserialize_association_and_ownership_attributes,
    serialize_association_and_ownership_attributes,
};
use egml::io::util::{ChunkedSink, XalElement, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::base::{HasAssociationAttributes, HasOwnershipAttributes};

pub fn deserialize_address_property(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AddressProperty, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let (association, ownership) = deserialize_association_and_ownership_attributes(xml_document)?;
    let mut object = None;

    if let Some(index) = index.first(XalElement::Address.into()) {
        object = Some(deserialize_address(
            &xml_document[index.range()],
            index,
            config,
        )?);
    }

    Ok(AddressProperty::new(object, association, ownership))
}

pub fn serialize_address_property(
    address_property: &AddressProperty,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
    target_xml_namespace: CityGmlNamespace,
    target_xml_element: CityGmlElement,
) -> Result<(), Error> {
    let attributes = serialize_association_and_ownership_attributes(
        address_property.association(),
        address_property.ownership(),
    );

    match address_property.object() {
        Some(object) => {
            xml_fragment_writer.write_start_event_with_attributes(
                target_xml_namespace,
                target_xml_element,
                attributes,
            )?;
            serialize_address(object, xml_fragment_writer)?;
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

#[cfg(test)]
mod tests {
    use super::{deserialize_address_property, serialize_address_property};
    use crate::gml::util::{
        CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
    };
    use egml::io::util::{ChunkedSink, Formatting, XmlDocumentIndex, XmlFragmentWriter};

    fn sample_xml() -> &'static [u8] {
        br#"<address>
<Address>
<xalAddress>
<xAL:Address>
<xAL:Country>
<xAL:NameElement xAL:NameType="Name">Germany</xAL:NameElement>
</xAL:Country>
</xAL:Address>
</xalAddress>
</Address>
</address>"#
    }

    #[test]
    fn test_deserialize_address_property() {
        let xml_document = sample_xml();
        let index = XmlDocumentIndex::<CombinedCityGmlElement>::from_scan(xml_document, None)
            .expect("should scan");

        let address =
            deserialize_address_property(xml_document, &index, &DeserializationConfig::default())
                .expect("should deserialize");

        let country_names: Vec<&str> = address
            .object()
            .unwrap()
            .xal_address()
            .country()
            .unwrap()
            .name_elements()
            .iter()
            .map(|name| name.content())
            .collect();
        assert_eq!(country_names, ["Germany"]);
    }

    #[test]
    fn test_round_trip_address_property() {
        let xml_document = sample_xml();
        let index = XmlDocumentIndex::<CombinedCityGmlElement>::from_scan(xml_document, None)
            .expect("should scan");
        let address =
            deserialize_address_property(xml_document, &index, &DeserializationConfig::default())
                .expect("should deserialize");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_address_property(
            &address,
            &mut xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::AddressProperty,
        )
        .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("bldg:address"));

        let round_tripped_index =
            XmlDocumentIndex::<CombinedCityGmlElement>::from_scan(xml.as_bytes(), None)
                .expect("should scan");
        let round_tripped = deserialize_address_property(
            xml.as_bytes(),
            &round_tripped_index,
            &DeserializationConfig::default(),
        )
        .expect("should deserialize");

        assert_eq!(address, round_tripped);
    }
}
