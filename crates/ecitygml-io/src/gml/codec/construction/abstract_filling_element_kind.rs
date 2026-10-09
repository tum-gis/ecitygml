use crate::Error;
use crate::gml::codec::construction::door::{deserialize_door, serialize_door};
use crate::gml::codec::construction::window::{deserialize_window, serialize_window};
use crate::gml::util::{CityGmlElement, CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::construction::AbstractFillingElementKind;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_filling_element_kind(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Option<AbstractFillingElementKind>, Error> {
    if let Some(index) = index.first(CityGmlElement::Door.into()) {
        let door = deserialize_door(&xml_document[index.range()], index, config)?;
        return Ok(Some(door.into()));
    }
    if let Some(index) = index.first(CityGmlElement::Window.into()) {
        let window = deserialize_window(&xml_document[index.range()], index, config)?;
        return Ok(Some(window.into()));
    }

    Ok(None)
}

pub fn serialize_abstract_filling_element_kind(
    abstract_filling_element_kind: &AbstractFillingElementKind,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    match abstract_filling_element_kind {
        AbstractFillingElementKind::Door(x) => serialize_door(x, xml_fragment_writer),
        AbstractFillingElementKind::Window(x) => serialize_window(x, xml_fragment_writer),
    }
}
