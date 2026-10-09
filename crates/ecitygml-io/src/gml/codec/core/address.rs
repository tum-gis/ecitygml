use crate::Error;
use crate::gml::codec::core::{deserialize_xal_address_property, serialize_xal_address_property};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
    collect_gml_child, collect_xal_child,
};
use ecitygml_core::model::core::Address;
use egml::io::codec::geometry::aggregates::{
    deserialize_multi_point_property, serialize_multi_point_property,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_address(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Address, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let xal_address = collect_xal_child(
        xml_document,
        index,
        CityGmlElement::XalAddressProperty.into(),
        config.gml_config(),
        deserialize_xal_address_property,
    )?
    .ok_or_else(|| Error::ElementNotFound("xalAddress".to_string()))?;

    let mut address = Address::new(xal_address);

    let multi_point = collect_gml_child(
        xml_document,
        index,
        CityGmlElement::MultiPointProperty.into(),
        config.gml_config(),
        deserialize_multi_point_property,
    )?;
    address.set_multi_point(multi_point);

    Ok(address)
}

pub fn serialize_address(
    address: &Address,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    xml_fragment_writer.write_start_event(CityGmlNamespace::Core, CityGmlElement::Address)?;

    serialize_xal_address_property(address.xal_address(), xml_fragment_writer)?;

    if let Some(multi_point) = address.multi_point() {
        serialize_multi_point_property(
            multi_point,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::MultiPointProperty,
        )?;
    }

    xml_fragment_writer.write_end_event(CityGmlNamespace::Core, CityGmlElement::Address)?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::{deserialize_address, serialize_address};
    use crate::gml::util::{CombinedCityGmlElement, DeserializationConfig};
    use egml::io::util::{ChunkedSink, Formatting, XmlDocumentIndex, XmlFragmentWriter};

    fn sample_xml() -> &'static [u8] {
        br#"<Address>
<xalAddress>
<xAL:Address>
<xAL:Country>
<xAL:NameElement xAL:NameType="Name">Germany</xAL:NameElement>
</xAL:Country>
</xAL:Address>
</xalAddress>
</Address>"#
    }

    #[test]
    fn test_deserialize_address() {
        let xml_document = sample_xml();
        let index = XmlDocumentIndex::<CombinedCityGmlElement>::from_scan(xml_document, None)
            .expect("should scan");

        let address = deserialize_address(xml_document, &index, &DeserializationConfig::default())
            .expect("should deserialize");

        let country_names: Vec<&str> = address
            .xal_address()
            .country()
            .unwrap()
            .name_elements()
            .iter()
            .map(|name| name.content())
            .collect();
        assert_eq!(country_names, ["Germany"]);
        assert!(address.multi_point().is_none());
    }

    #[test]
    fn test_serialize_address() {
        let xml_document = sample_xml();
        let index = XmlDocumentIndex::<CombinedCityGmlElement>::from_scan(xml_document, None)
            .expect("should scan");
        let address = deserialize_address(xml_document, &index, &DeserializationConfig::default())
            .expect("should deserialize");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_address(&address, &mut xml_fragment_writer).expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert_eq!(
            xml,
            r#"<Address><xalAddress><xAL:Address><xAL:Country><xAL:NameElement xAL:NameType="Name">Germany</xAL:NameElement></xAL:Country></xAL:Address></xalAddress></Address>"#
        );
    }

    #[test]
    fn test_round_trip_address() {
        let xml_document = sample_xml();
        let index = XmlDocumentIndex::<CombinedCityGmlElement>::from_scan(xml_document, None)
            .expect("should scan");
        let address = deserialize_address(xml_document, &index, &DeserializationConfig::default())
            .expect("should deserialize");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_address(&address, &mut xml_fragment_writer).expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        let index = XmlDocumentIndex::<CombinedCityGmlElement>::from_scan(xml.as_bytes(), None)
            .expect("should scan");
        let round_tripped =
            deserialize_address(xml.as_bytes(), &index, &DeserializationConfig::default())
                .expect("should deserialize");

        assert_eq!(address, round_tripped);
    }
}
