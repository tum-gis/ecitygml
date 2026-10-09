use crate::Error;
use crate::gml::codec::relief::{deserialize_tin_relief, serialize_tin_relief};
use crate::gml::util::{CityGmlElement, CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::relief::AbstractReliefComponentKind;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_relief_component_kind(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Option<AbstractReliefComponentKind>, Error> {
    if let Some(index) = index.first(CityGmlElement::TINRelief.into()) {
        let tin_surface = deserialize_tin_relief(&xml_document[index.range()], index, config)?;
        return Ok(Some(tin_surface.into()));
    }

    Ok(None)
}

pub fn serialize_abstract_relief_component_kind(
    abstract_relief_component_kind: &AbstractReliefComponentKind,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    match abstract_relief_component_kind {
        AbstractReliefComponentKind::TinRelief(x) => serialize_tin_relief(x, xml_fragment_writer),
    }
}
