use crate::Error;
use crate::gml::codec::core::{
    deserialize_abstract_city_object, serialize_abstract_city_object,
    serialize_abstract_city_object_attributes,
};
use crate::gml::util::{CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::core::{AbstractSpaceBoundary, AsAbstractCityObject};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_space_boundary(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractSpaceBoundary, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_space_boundary received a truncated index — caller must scan to sufficient depth"
    );

    let abstract_city_object = deserialize_abstract_city_object(xml_document, index, config)?;
    let abstract_space_boundary =
        AbstractSpaceBoundary::from_abstract_city_object(abstract_city_object);

    Ok(abstract_space_boundary)
}

pub fn serialize_abstract_space_boundary(
    abstract_space_boundary: &AbstractSpaceBoundary,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_city_object(
        abstract_space_boundary.abstract_city_object(),
        xml_fragment_writer,
    )
}

pub fn serialize_abstract_space_boundary_attributes(
    abstract_space_boundary: &AbstractSpaceBoundary,
) -> Vec<(String, String)> {
    serialize_abstract_city_object_attributes(abstract_space_boundary.abstract_city_object())
}
