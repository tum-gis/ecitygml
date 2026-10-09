use crate::Error;
use crate::gml::codec::construction::abstract_construction_surface::{
    deserialize_abstract_construction_surface, serialize_abstract_construction_surface,
    serialize_abstract_construction_surface_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::construction::{AsAbstractConstructionSurface, FloorSurface};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_floor_surface(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<FloorSurface, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_construction_surface =
        deserialize_abstract_construction_surface(xml_document, index, config)?;
    Ok(FloorSurface::from_abstract_construction_surface(
        abstract_construction_surface,
    ))
}

pub fn serialize_floor_surface(
    floor_surface: &FloorSurface,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_floor_surface_attributes(floor_surface);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Construction,
        CityGmlElement::FloorSurface,
        attributes,
    )?;

    serialize_abstract_construction_surface(
        floor_surface.abstract_construction_surface(),
        xml_fragment_writer,
    )?;

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::Construction, CityGmlElement::FloorSurface)?;

    Ok(())
}

pub fn serialize_floor_surface_attributes(floor_surface: &FloorSurface) -> Vec<(String, String)> {
    serialize_abstract_construction_surface_attributes(
        floor_surface.abstract_construction_surface(),
    )
}
