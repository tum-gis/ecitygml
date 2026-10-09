use crate::Error;
use crate::gml::codec::core::abstract_physical_space::{
    deserialize_abstract_physical_space, serialize_abstract_physical_space,
    serialize_abstract_physical_space_attributes,
};
use crate::gml::util::{CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::core::{AbstractUnoccupiedSpace, AsAbstractPhysicalSpace};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_unoccupied_space(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractUnoccupiedSpace, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_unoccupied_space received a truncated index — caller must scan to sufficient depth"
    );

    let abstract_physical_space = deserialize_abstract_physical_space(xml_document, index, config)?;
    let abstract_unoccupied_space =
        AbstractUnoccupiedSpace::from_abstract_physical_space(abstract_physical_space);

    Ok(abstract_unoccupied_space)
}

pub fn serialize_abstract_unoccupied_space(
    abstract_unoccupied_space: &AbstractUnoccupiedSpace,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_physical_space(
        abstract_unoccupied_space.abstract_physical_space(),
        xml_fragment_writer,
    )
}

pub fn serialize_abstract_unoccupied_space_attributes(
    abstract_unoccupied_space: &AbstractUnoccupiedSpace,
) -> Vec<(String, String)> {
    serialize_abstract_physical_space_attributes(
        abstract_unoccupied_space.abstract_physical_space(),
    )
}
