use crate::Error;
use crate::gml::codec::construction::abstract_construction_surface::{
    deserialize_abstract_construction_surface, serialize_abstract_construction_surface,
    serialize_abstract_construction_surface_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::construction::{AsAbstractConstructionSurface, GroundSurface};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_ground_surface(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<GroundSurface, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_construction_surface =
        deserialize_abstract_construction_surface(xml_document, index, config)?;
    let ground_surface =
        GroundSurface::from_abstract_construction_surface(abstract_construction_surface);

    Ok(ground_surface)
}

pub fn serialize_ground_surface(
    ground_surface: &GroundSurface,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_ground_surface_attributes(ground_surface);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Construction,
        CityGmlElement::GroundSurface,
        attributes,
    )?;

    serialize_abstract_construction_surface(
        ground_surface.abstract_construction_surface(),
        xml_fragment_writer,
    )?;

    xml_fragment_writer.write_end_event(
        CityGmlNamespace::Construction,
        CityGmlElement::GroundSurface,
    )?;

    Ok(())
}

pub fn serialize_ground_surface_attributes(
    ground_surface: &GroundSurface,
) -> Vec<(String, String)> {
    serialize_abstract_construction_surface_attributes(
        ground_surface.abstract_construction_surface(),
    )
}
