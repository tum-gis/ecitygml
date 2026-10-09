use crate::Error;
use crate::gml::codec::core::{
    deserialize_abstract_feature_with_lifespan, serialize_abstract_feature_with_lifespan,
    serialize_abstract_feature_with_lifespan_attributes,
};
use crate::gml::util::{CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::core::{AbstractAppearance, AsAbstractFeatureWithLifespan};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_appearance(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractAppearance, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_appearance received a truncated index — caller must scan to sufficient depth"
    );

    let abstract_feature_with_lifespan =
        deserialize_abstract_feature_with_lifespan(xml_document, index, config)?;

    let abstract_appearance =
        AbstractAppearance::from_abstract_feature_with_lifespan(abstract_feature_with_lifespan);

    Ok(abstract_appearance)
}

pub fn serialize_abstract_appearance(
    abstract_appearance: &AbstractAppearance,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_feature_with_lifespan(
        abstract_appearance.abstract_feature_with_lifespan(),
        xml_fragment_writer,
    )
}

pub fn serialize_abstract_appearance_attributes(
    abstract_appearance: &AbstractAppearance,
) -> Vec<(String, String)> {
    serialize_abstract_feature_with_lifespan_attributes(
        abstract_appearance.abstract_feature_with_lifespan(),
    )
}
