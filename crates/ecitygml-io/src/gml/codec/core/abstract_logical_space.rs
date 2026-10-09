use crate::Error;
use crate::gml::codec::core::{
    deserialize_abstract_space, serialize_abstract_space, serialize_abstract_space_attributes,
};
use crate::gml::util::{CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::core::{AbstractLogicalSpace, AsAbstractSpace};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_logical_space(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractLogicalSpace, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_logical_space received a truncated index — caller must scan to sufficient depth"
    );

    let abstract_space = deserialize_abstract_space(xml_document, index, config)?;
    let abstract_logical_space = AbstractLogicalSpace::from_abstract_space(abstract_space);

    Ok(abstract_logical_space)
}

pub fn serialize_abstract_logical_space(
    abstract_logical_space: &AbstractLogicalSpace,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_space(abstract_logical_space.abstract_space(), xml_fragment_writer)
}

pub fn serialize_abstract_logical_space_attributes(
    abstract_logical_space: &AbstractLogicalSpace,
) -> Vec<(String, String)> {
    serialize_abstract_space_attributes(abstract_logical_space.abstract_space())
}
