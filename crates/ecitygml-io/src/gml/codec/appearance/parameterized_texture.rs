use crate::Error;
use crate::gml::codec::appearance::abstract_texture::{
    deserialize_abstract_texture, serialize_abstract_texture, serialize_abstract_texture_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::appearance::{AsAbstractTexture, ParameterizedTexture};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_parameterized_texture(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<ParameterizedTexture, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_texture = deserialize_abstract_texture(xml_document, index, config)?;
    let parameterized_texture = ParameterizedTexture::from_abstract_texture(abstract_texture);

    Ok(parameterized_texture)
}

pub fn serialize_parameterized_texture(
    parameterized_texture: &ParameterizedTexture,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_parameterized_texture_attributes(parameterized_texture);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Appearance,
        CityGmlElement::ParameterizedTexture,
        attributes,
    )?;

    serialize_abstract_texture(
        parameterized_texture.abstract_texture(),
        xml_fragment_writer,
    )?;

    xml_fragment_writer.write_end_event(
        CityGmlNamespace::Appearance,
        CityGmlElement::ParameterizedTexture,
    )?;

    Ok(())
}

pub fn serialize_parameterized_texture_attributes(
    parameterized_texture: &ParameterizedTexture,
) -> Vec<(String, String)> {
    serialize_abstract_texture_attributes(parameterized_texture.abstract_texture())
}
