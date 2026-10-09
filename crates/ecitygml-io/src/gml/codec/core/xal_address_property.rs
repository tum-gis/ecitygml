use crate::Error;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use egml::io::codec::xal::{
    deserialize_address as deserialize_xal_address, serialize_address as serialize_xal_address,
};
use egml::io::util::{ChunkedSink, XalElement, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::xal;

/// The `xalAddress` property wraps `xAL:Address`, so descending one level (from the
/// property wrapper to the `xAL:Address` element itself) is needed before handing off to
/// egml's own [`deserialize_xal_address`], which expects to already be positioned on
/// `xAL:Address`.
pub fn deserialize_xal_address_property(
    xml_document: &[u8],
    index: &XmlDocumentIndex<XalElement>,
    config: &egml::io::util::DeserializationConfig,
) -> Result<xal::Address, egml::io::Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.rescan_depth())?
    } else {
        index
    };

    let address_node = index
        .first(XalElement::Address)
        .ok_or_else(|| egml::io::Error::ElementNotFound("xAL:Address".to_string()))?;

    deserialize_xal_address(&xml_document[address_node.range()], address_node, config)
}

/// Mirrors [`deserialize_xal_address_property`]: writes the property wrapper element (e.g.
/// `xalAddress`) around egml's own [`serialize_xal_address`] output for `xAL:Address`.
pub fn serialize_xal_address_property(
    xal_address: &xal::Address,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    xml_fragment_writer
        .write_start_event(CityGmlNamespace::Core, CityGmlElement::XalAddressProperty)?;

    serialize_xal_address(xal_address, xml_fragment_writer)?;

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::Core, CityGmlElement::XalAddressProperty)?;

    Ok(())
}
