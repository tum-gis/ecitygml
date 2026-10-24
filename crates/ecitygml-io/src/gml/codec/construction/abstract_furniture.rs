use crate::Error;
use crate::gml::codec::core::{
    deserialize_abstract_occupied_space, serialize_abstract_occupied_space,
    serialize_abstract_occupied_space_attributes,
};
use crate::gml::util::{CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::construction::AbstractFurniture;
use ecitygml_core::model::core::AsAbstractOccupiedSpace;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_furniture(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractFurniture, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_furniture received a truncated index — caller must scan to sufficient depth"
    );

    let abstract_occupied_space = deserialize_abstract_occupied_space(xml_document, index, config)?;
    let abstract_furniture =
        AbstractFurniture::from_abstract_occupied_space(abstract_occupied_space);

    Ok(abstract_furniture)
}

pub fn serialize_abstract_furniture(
    abstract_furniture: &AbstractFurniture,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_occupied_space(
        abstract_furniture.abstract_occupied_space(),
        xml_fragment_writer,
    )?;

    Ok(())
}

pub fn serialize_abstract_furniture_attributes(
    abstract_furniture: &AbstractFurniture,
) -> Vec<(String, String)> {
    serialize_abstract_occupied_space_attributes(abstract_furniture.abstract_occupied_space())
}
