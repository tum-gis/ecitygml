use crate::Error;
use crate::gml::codec::core::{
    deserialize_abstract_thematic_surface, serialize_abstract_thematic_surface,
    serialize_abstract_thematic_surface_attributes,
};
use crate::gml::util::{CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::core::AsAbstractThematicSurface;
use ecitygml_core::model::water_body::AbstractWaterBoundarySurface;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_water_boundary_surface(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractWaterBoundarySurface, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_water_boundary_surface received a truncated index — caller must scan to sufficient depth"
    );

    let abstract_thematic_surface =
        deserialize_abstract_thematic_surface(xml_document, index, config)?;
    let abstract_water_boundary_surface =
        AbstractWaterBoundarySurface::from_abstract_thematic_surface(abstract_thematic_surface);

    Ok(abstract_water_boundary_surface)
}

pub fn serialize_abstract_water_boundary_surface(
    abstract_water_boundary_surface: &AbstractWaterBoundarySurface,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_thematic_surface(
        abstract_water_boundary_surface.abstract_thematic_surface(),
        xml_fragment_writer,
    )
}

pub fn serialize_abstract_water_boundary_surface_attributes(
    abstract_water_boundary_surface: &AbstractWaterBoundarySurface,
) -> Vec<(String, String)> {
    serialize_abstract_thematic_surface_attributes(
        abstract_water_boundary_surface.abstract_thematic_surface(),
    )
}
