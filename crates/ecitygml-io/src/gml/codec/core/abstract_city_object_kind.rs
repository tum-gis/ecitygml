use crate::Error;
use crate::gml::codec::core::abstract_space_boundary_kind::{
    deserialize_abstract_space_boundary_kind, serialize_abstract_space_boundary_kind,
};
use crate::gml::codec::core::abstract_space_kind::{
    deserialize_abstract_space_kind, serialize_abstract_space_kind,
};
use crate::gml::util::{CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::core::AbstractCityObjectKind;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_city_object_kind(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Option<AbstractCityObjectKind>, Error> {
    if let Some(x) = deserialize_abstract_space_boundary_kind(xml_document, index, config)? {
        return Ok(Some(x.into()));
    }

    if let Some(x) = deserialize_abstract_space_kind(xml_document, index, config)? {
        return Ok(Some(x.into()));
    }

    Ok(None)
}

pub fn serialize_abstract_city_object_kind(
    abstract_city_object_kind: &AbstractCityObjectKind,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    match abstract_city_object_kind {
        AbstractCityObjectKind::AbstractSpaceBoundaryKind(x) => {
            serialize_abstract_space_boundary_kind(x, xml_fragment_writer)
        }
        AbstractCityObjectKind::AbstractSpaceKind(x) => {
            serialize_abstract_space_kind(x, xml_fragment_writer)
        }
    }
}
