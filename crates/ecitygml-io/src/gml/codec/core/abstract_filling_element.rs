use crate::Error;
use crate::gml::codec::core::deserialize_abstract_occupied_space;
use crate::gml::util::{CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::construction::AbstractFillingElement;
use egml::io::util::XmlDocumentIndex;

#[expect(dead_code, reason = "not used yet")]
pub fn deserialize_abstract_filling_element(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractFillingElement, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_filling_element received a truncated index — caller must scan to sufficient depth"
    );

    let abstract_occupied_space = deserialize_abstract_occupied_space(xml_document, index, config)?;
    let abstract_filling_element =
        AbstractFillingElement::from_abstract_occupied_space(abstract_occupied_space);

    Ok(abstract_filling_element)
}
