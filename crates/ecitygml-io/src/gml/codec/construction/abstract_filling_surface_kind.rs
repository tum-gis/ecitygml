use crate::Error;
use crate::gml::codec::construction::{
    deserialize_door_surface, deserialize_window_surface, serialize_door_surface,
    serialize_window_surface,
};
use crate::gml::util::{CityGmlElement, CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::construction::AbstractFillingSurfaceKind;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_filling_surface_kind(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Option<AbstractFillingSurfaceKind>, Error> {
    if let Some(index) = index.first(CityGmlElement::DoorSurface.into()) {
        let door_surface = deserialize_door_surface(&xml_document[index.range()], index, config)?;
        return Ok(Some(door_surface.into()));
    }
    if let Some(index) = index.first(CityGmlElement::WindowSurface.into()) {
        let window_surface =
            deserialize_window_surface(&xml_document[index.range()], index, config)?;
        return Ok(Some(window_surface.into()));
    }

    Ok(None)
}

pub fn serialize_abstract_filling_surface_kind(
    abstract_filling_surface_kind: &AbstractFillingSurfaceKind,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    match abstract_filling_surface_kind {
        AbstractFillingSurfaceKind::DoorSurface(x) => {
            serialize_door_surface(x, xml_fragment_writer)
        }
        AbstractFillingSurfaceKind::WindowSurface(x) => {
            serialize_window_surface(x, xml_fragment_writer)
        }
    }
}
