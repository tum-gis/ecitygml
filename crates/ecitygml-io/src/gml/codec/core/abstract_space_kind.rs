use crate::Error;
use crate::gml::codec::core::abstract_logical_space_kind::{
    deserialize_abstract_logical_space_kind, serialize_abstract_logical_space_kind,
};
use crate::gml::codec::core::abstract_physical_space_kind::{
    deserialize_abstract_physical_space_kind, serialize_abstract_physical_space_kind,
};
use crate::gml::util::{CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::core::AbstractSpaceKind;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_space_kind(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Option<AbstractSpaceKind>, Error> {
    if let Some(x) = deserialize_abstract_logical_space_kind(xml_document, index, config)? {
        return Ok(Some(x.into()));
    }

    if let Some(x) = deserialize_abstract_physical_space_kind(xml_document, index, config)? {
        return Ok(Some(x.into()));
    }

    Ok(None)
}

pub fn serialize_abstract_space_kind(
    abstract_space_kind: &AbstractSpaceKind,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    match abstract_space_kind {
        AbstractSpaceKind::AbstractLogicalSpaceKind(x) => {
            serialize_abstract_logical_space_kind(x, xml_fragment_writer)
        }
        AbstractSpaceKind::AbstractPhysicalSpaceKind(x) => {
            serialize_abstract_physical_space_kind(x, xml_fragment_writer)
        }
    }
}
