use crate::Error;
use crate::gml::codec::core::{
    deserialize_abstract_thematic_surface, serialize_abstract_thematic_surface,
    serialize_abstract_thematic_surface_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::core::AsAbstractThematicSurface;
use ecitygml_core::model::transportation::HoleSurface;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_hole_surface(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<HoleSurface, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_thematic_surface =
        deserialize_abstract_thematic_surface(xml_document, index, config)?;
    let hole_surface = HoleSurface::from_abstract_thematic_surface(abstract_thematic_surface);

    Ok(hole_surface)
}

pub fn serialize_hole_surface(
    hole_surface: &HoleSurface,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_hole_surface_attributes(hole_surface);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Transportation,
        CityGmlElement::HoleSurface,
        attributes,
    )?;

    serialize_abstract_thematic_surface(
        hole_surface.abstract_thematic_surface(),
        xml_fragment_writer,
    )?;

    xml_fragment_writer.write_end_event(
        CityGmlNamespace::Transportation,
        CityGmlElement::HoleSurface,
    )?;

    Ok(())
}

pub fn serialize_hole_surface_attributes(hole_surface: &HoleSurface) -> Vec<(String, String)> {
    serialize_abstract_thematic_surface_attributes(hole_surface.abstract_thematic_surface())
}
