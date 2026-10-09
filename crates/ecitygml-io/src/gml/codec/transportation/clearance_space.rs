use crate::Error;
use crate::gml::codec::core::{
    deserialize_abstract_unoccupied_space, serialize_abstract_unoccupied_space,
    serialize_abstract_unoccupied_space_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::core::AsAbstractUnoccupiedSpace;
use ecitygml_core::model::transportation::ClearanceSpace;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::basic_types::Code;

pub fn deserialize_clearance_space(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<ClearanceSpace, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_unoccupied_space =
        deserialize_abstract_unoccupied_space(xml_document, index, config)?;

    let mut clearance_space =
        ClearanceSpace::from_abstract_unoccupied_space(abstract_unoccupied_space);

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    clearance_space.set_class_opt(class.map(Into::into));

    Ok(clearance_space)
}

pub fn serialize_clearance_space(
    clearance_space: &ClearanceSpace,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_clearance_space_attributes(clearance_space);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Transportation,
        CityGmlElement::ClearanceSpace,
        attributes,
    )?;

    serialize_abstract_unoccupied_space(
        clearance_space.abstract_unoccupied_space(),
        xml_fragment_writer,
    )?;

    if let Some(class) = clearance_space.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::ClassProperty,
        )?;
    }

    xml_fragment_writer.write_end_event(
        CityGmlNamespace::Transportation,
        CityGmlElement::ClearanceSpace,
    )?;

    Ok(())
}

pub fn serialize_clearance_space_attributes(
    clearance_space: &ClearanceSpace,
) -> Vec<(String, String)> {
    serialize_abstract_unoccupied_space_attributes(clearance_space.abstract_unoccupied_space())
}
