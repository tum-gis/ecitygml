use crate::Error;
use crate::gml::codec::core::{
    deserialize_abstract_occupied_space, serialize_abstract_occupied_space,
    serialize_abstract_occupied_space_attributes,
};
use crate::gml::util::{CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::construction::AbstractInstallation;
use ecitygml_core::model::core::AsAbstractOccupiedSpace;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_installation(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractInstallation, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_installation received a truncated index — caller must scan to sufficient depth"
    );

    let abstract_occupied_space = deserialize_abstract_occupied_space(xml_document, index, config)?;
    let abstract_installation =
        AbstractInstallation::from_abstract_occupied_space(abstract_occupied_space);

    Ok(abstract_installation)
}

pub fn serialize_abstract_installation(
    abstract_installation: &AbstractInstallation,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_occupied_space(
        abstract_installation.abstract_occupied_space(),
        xml_fragment_writer,
    )?;

    Ok(())
}

pub fn serialize_abstract_installation_attributes(
    abstract_installation: &AbstractInstallation,
) -> Vec<(String, String)> {
    serialize_abstract_occupied_space_attributes(abstract_installation.abstract_occupied_space())
}
