use crate::Error;
use crate::gml::codec::core::{
    deserialize_abstract_occupied_space, serialize_abstract_occupied_space,
    serialize_abstract_occupied_space_attributes,
};
use crate::gml::util::{CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::core::AsAbstractOccupiedSpace;
use ecitygml_core::model::vegetation::AbstractVegetationObject;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_vegetation_object(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractVegetationObject, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_vegetation_object received a truncated index — caller must scan to sufficient depth"
    );

    let occupied_space = deserialize_abstract_occupied_space(xml_document, index, config)?;
    let abstract_vegetation_object =
        AbstractVegetationObject::from_abstract_occupied_space(occupied_space);

    Ok(abstract_vegetation_object)
}

pub fn serialize_abstract_vegetation_object(
    abstract_vegetation_object: &AbstractVegetationObject,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_occupied_space(
        abstract_vegetation_object.abstract_occupied_space(),
        xml_fragment_writer,
    )
}

pub fn serialize_abstract_vegetation_object_attributes(
    abstract_vegetation_object: &AbstractVegetationObject,
) -> Vec<(String, String)> {
    serialize_abstract_occupied_space_attributes(
        abstract_vegetation_object.abstract_occupied_space(),
    )
}
