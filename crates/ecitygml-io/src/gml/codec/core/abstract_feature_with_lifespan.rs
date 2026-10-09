use crate::Error;
use crate::gml::codec::core::abstract_feature::{
    deserialize_abstract_feature, serialize_abstract_feature,
};
use crate::gml::codec::core::serialize_abstract_feature_attributes;
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::core::{
    AbstractFeatureWithLifespan, AsAbstractFeature, AsAbstractFeatureWithLifespan,
    AsAbstractFeatureWithLifespanMut,
};
use egml::io::codec::xs::{deserialize_date_time, serialize_date_time};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::xs::DateTime;

pub fn deserialize_abstract_feature_with_lifespan(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractFeatureWithLifespan, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_feature_with_lifespan received a truncated index — caller must scan to sufficient depth"
    );

    let abstract_feature = deserialize_abstract_feature(xml_document, index, config)?;
    let mut abstract_feature_with_lifespan =
        AbstractFeatureWithLifespan::from_abstract_feature(abstract_feature);

    let creation_date: Option<DateTime> = index
        .first(CityGmlElement::CreationDateProperty.into())
        .map(|x| deserialize_date_time(xml_document[x.range()].as_ref(), config.gml_config()))
        .transpose()?;
    abstract_feature_with_lifespan.set_creation_date(creation_date);

    let termination_date: Option<DateTime> = index
        .first(CityGmlElement::TerminationDateProperty.into())
        .map(|x| deserialize_date_time(xml_document[x.range()].as_ref(), config.gml_config()))
        .transpose()?;
    abstract_feature_with_lifespan.set_termination_date(termination_date);

    let valid_from: Option<DateTime> = index
        .first(CityGmlElement::ValidFromProperty.into())
        .map(|x| deserialize_date_time(xml_document[x.range()].as_ref(), config.gml_config()))
        .transpose()?;
    abstract_feature_with_lifespan.set_valid_from(valid_from);

    let valid_to: Option<DateTime> = index
        .first(CityGmlElement::ValidToProperty.into())
        .map(|x| deserialize_date_time(xml_document[x.range()].as_ref(), config.gml_config()))
        .transpose()?;
    abstract_feature_with_lifespan.set_valid_to(valid_to);

    Ok(abstract_feature_with_lifespan)
}

pub fn serialize_abstract_feature_with_lifespan(
    abstract_feature_with_lifespan: &AbstractFeatureWithLifespan,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_feature(
        abstract_feature_with_lifespan.abstract_feature(),
        xml_fragment_writer,
    )?;

    if let Some(creation_date) = abstract_feature_with_lifespan.creation_date() {
        serialize_date_time(
            *creation_date,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::CreationDateProperty,
        )?;
    }

    if let Some(termination_date) = abstract_feature_with_lifespan.termination_date() {
        serialize_date_time(
            *termination_date,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::TerminationDateProperty,
        )?;
    }

    if let Some(valid_from) = abstract_feature_with_lifespan.valid_from() {
        serialize_date_time(
            *valid_from,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::ValidFromProperty,
        )?;
    }

    if let Some(valid_to) = abstract_feature_with_lifespan.valid_to() {
        serialize_date_time(
            *valid_to,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::ValidToProperty,
        )?;
    }

    Ok(())
}

pub fn serialize_abstract_feature_with_lifespan_attributes(
    abstract_feature_with_lifespan: &AbstractFeatureWithLifespan,
) -> Vec<(String, String)> {
    serialize_abstract_feature_attributes(abstract_feature_with_lifespan.abstract_feature())
}
