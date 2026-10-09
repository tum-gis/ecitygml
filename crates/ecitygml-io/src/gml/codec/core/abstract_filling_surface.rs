use crate::Error;
use crate::gml::codec::core::{
    deserialize_abstract_thematic_surface, serialize_abstract_thematic_surface,
    serialize_abstract_thematic_surface_attributes,
};
use crate::gml::util::{CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::construction::AbstractFillingSurface;
use ecitygml_core::model::core::AsAbstractThematicSurface;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_filling_surface(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractFillingSurface, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_filling_surface received a truncated index — caller must scan to sufficient depth"
    );

    let abstract_thematic_surface =
        deserialize_abstract_thematic_surface(xml_document, index, config)?;
    let abstract_filling_surface =
        AbstractFillingSurface::from_abstract_thematic_surface(abstract_thematic_surface);

    Ok(abstract_filling_surface)
}

pub fn serialize_abstract_filling_surface(
    abstract_filling_surface: &AbstractFillingSurface,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_thematic_surface(
        abstract_filling_surface.abstract_thematic_surface(),
        xml_fragment_writer,
    )
}

pub fn serialize_abstract_filling_surface_attributes(
    abstract_filling_surface: &AbstractFillingSurface,
) -> Vec<(String, String)> {
    serialize_abstract_thematic_surface_attributes(
        abstract_filling_surface.abstract_thematic_surface(),
    )
}
