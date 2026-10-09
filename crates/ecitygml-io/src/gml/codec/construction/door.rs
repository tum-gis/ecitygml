use crate::Error;
use crate::gml::codec::construction::abstract_filling_element::{
    deserialize_abstract_filling_element, serialize_abstract_filling_element,
    serialize_abstract_filling_element_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::construction::{AsAbstractFillingElement, Door};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_door(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Door, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_filling_element =
        deserialize_abstract_filling_element(xml_document, index, config)?;
    let door = Door::from_abstract_filling_element(abstract_filling_element);

    Ok(door)
}

pub fn serialize_door(
    door: &Door,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_door_attributes(door);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Construction,
        CityGmlElement::Door,
        attributes,
    )?;

    serialize_abstract_filling_element(door.abstract_filling_element(), xml_fragment_writer)?;

    xml_fragment_writer.write_end_event(CityGmlNamespace::Construction, CityGmlElement::Door)?;

    Ok(())
}

pub fn serialize_door_attributes(door: &Door) -> Vec<(String, String)> {
    serialize_abstract_filling_element_attributes(door.abstract_filling_element())
}
