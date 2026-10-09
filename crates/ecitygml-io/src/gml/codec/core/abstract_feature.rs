use crate::Error;
use crate::gml::util::{CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::core::AbstractFeature;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::base::{AsAbstractGml, AsAbstractGmlMut, Id};
use std::sync::atomic::{AtomicU64, Ordering};

static NEXT_ID: AtomicU64 = AtomicU64::new(0);
fn generate_feature_id() -> Id {
    let n = NEXT_ID.fetch_add(1, Ordering::Relaxed);
    Id::try_from(format!("ecitygml-gen-feature-{n}"))
        .expect("ecitygml-gen-feature-{n} is always a valid xsd:ID")
}

pub fn deserialize_abstract_feature(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractFeature, Error> {
    let gml_index = index.convert(|e| match e {
        CombinedCityGmlElement::Gml(g) => Some(g),
        _ => None,
    });
    let mut gml_abstract_feature = egml::io::codec::feature::deserialize_abstract_feature(
        xml_document,
        &gml_index,
        config.gml_config(),
    )?;

    if gml_abstract_feature.abstract_gml().id().is_none() {
        gml_abstract_feature
            .abstract_gml_mut()
            .set_id(generate_feature_id());
        // gml_abstract_feature.abstract_gml.id = Some(Id::from_hashed_bytes(xml_document))
    }

    let abstract_feature = AbstractFeature::from_abstract_feature(gml_abstract_feature);

    Ok(abstract_feature)
}

pub fn serialize_abstract_feature(
    abstract_feature: &AbstractFeature,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    egml::io::codec::feature::serialize_abstract_feature(
        egml::model::feature::AsAbstractFeature::abstract_feature(abstract_feature),
        xml_fragment_writer,
    )?;

    Ok(())
}

pub fn serialize_abstract_feature_attributes(
    abstract_feature: &AbstractFeature,
) -> Vec<(String, String)> {
    egml::io::codec::feature::serialize_abstract_feature_attributes(
        egml::model::feature::AsAbstractFeature::abstract_feature(abstract_feature),
    )
}
