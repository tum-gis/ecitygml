use crate::Error;
use crate::gml::codec::core::{
    deserialize_abstract_filling_surface, serialize_abstract_filling_surface,
    serialize_abstract_filling_surface_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::construction::{AsAbstractFillingSurface, DoorSurface};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_door_surface(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<DoorSurface, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_filling_surface =
        deserialize_abstract_filling_surface(xml_document, index, config)?;
    let door_surface = DoorSurface::from_abstract_filling_surface(abstract_filling_surface);

    Ok(door_surface)
}

pub fn serialize_door_surface(
    door_surface: &DoorSurface,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_door_surface_attributes(door_surface);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Construction,
        CityGmlElement::DoorSurface,
        attributes,
    )?;

    serialize_abstract_filling_surface(
        door_surface.abstract_filling_surface(),
        xml_fragment_writer,
    )?;

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::Construction, CityGmlElement::DoorSurface)?;

    Ok(())
}

pub fn serialize_door_surface_attributes(door_surface: &DoorSurface) -> Vec<(String, String)> {
    serialize_abstract_filling_surface_attributes(door_surface.abstract_filling_surface())
}
