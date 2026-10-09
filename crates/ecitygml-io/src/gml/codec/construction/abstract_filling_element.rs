use crate::Error;
use crate::gml::codec::core::{
    deserialize_abstract_occupied_space, serialize_abstract_occupied_space,
    serialize_abstract_occupied_space_attributes,
};
use crate::gml::util::{CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::construction::AbstractFillingElement;
use ecitygml_core::model::core::AsAbstractOccupiedSpace;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_filling_element(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractFillingElement, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_filling_element received a truncated index — caller must scan to sufficient depth"
    );

    let abstract_occupied_space = deserialize_abstract_occupied_space(xml_document, index, config)?;
    let window_surface =
        AbstractFillingElement::from_abstract_occupied_space(abstract_occupied_space);

    Ok(window_surface)
}

pub fn serialize_abstract_filling_element(
    abstract_filling_element: &AbstractFillingElement,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_occupied_space(
        abstract_filling_element.abstract_occupied_space(),
        xml_fragment_writer,
    )
}

pub fn serialize_abstract_filling_element_attributes(
    abstract_filling_element: &AbstractFillingElement,
) -> Vec<(String, String)> {
    serialize_abstract_occupied_space_attributes(abstract_filling_element.abstract_occupied_space())
}
