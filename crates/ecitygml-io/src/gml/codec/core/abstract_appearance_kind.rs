use crate::Error;
use crate::gml::codec::appearance::{deserialize_appearance, serialize_appearance};
use crate::gml::util::{CityGmlElement, CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::core::AbstractAppearanceKind;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_appearance_kind(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Option<AbstractAppearanceKind>, Error> {
    if let Some(index) = index.first(CityGmlElement::Appearance.into()) {
        let appearance = deserialize_appearance(&xml_document[index.range()], index, config)?;
        return Ok(Some(appearance.into()));
    }

    Ok(None)
}

pub fn serialize_abstract_appearance_kind(
    abstract_appearance_kind: &AbstractAppearanceKind,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    match abstract_appearance_kind {
        AbstractAppearanceKind::Appearance(x) => serialize_appearance(x, xml_fragment_writer),
    }
}
