use crate::Error;
use crate::gml::codec::appearance::georeferenced_texture::{
    deserialize_georeferenced_texture, serialize_georeferenced_texture,
};
use crate::gml::codec::appearance::parameterized_texture::{
    deserialize_parameterized_texture, serialize_parameterized_texture,
};
use crate::gml::util::{CityGmlElement, CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::appearance::AbstractTextureKind;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_texture_kind(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Option<AbstractTextureKind>, Error> {
    if let Some(index) = index.first(CityGmlElement::GeoreferencedTexture.into()) {
        let georeferenced_texture =
            deserialize_georeferenced_texture(&xml_document[index.range()], index, config)?;
        return Ok(Some(georeferenced_texture.into()));
    }
    if let Some(index) = index.first(CityGmlElement::ParameterizedTexture.into()) {
        let parameterized_texture =
            deserialize_parameterized_texture(&xml_document[index.range()], index, config)?;
        return Ok(Some(parameterized_texture.into()));
    }

    Ok(None)
}

pub fn serialize_abstract_texture_kind(
    abstract_texture_kind: &AbstractTextureKind,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    match abstract_texture_kind {
        AbstractTextureKind::GeoreferencedTexture(x) => {
            serialize_georeferenced_texture(x, xml_fragment_writer)
        }
        AbstractTextureKind::ParameterizedTexture(x) => {
            serialize_parameterized_texture(x, xml_fragment_writer)
        }
    }
}
