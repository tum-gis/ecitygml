use crate::Error;
use crate::gml::codec::core::{
    deserialize_abstract_feature, serialize_abstract_feature, serialize_abstract_feature_attributes,
};
use crate::gml::util::{CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::core::{AbstractPointCloud, AsAbstractFeature};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_point_cloud(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractPointCloud, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_point_cloud received a truncated index — caller must scan to sufficient depth"
    );

    let abstract_feature = deserialize_abstract_feature(xml_document, index, config)?;
    let abstract_point_cloud = AbstractPointCloud::from_abstract_feature(abstract_feature);

    Ok(abstract_point_cloud)
}

pub fn serialize_abstract_point_cloud(
    abstract_point_cloud: &AbstractPointCloud,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_feature(abstract_point_cloud.abstract_feature(), xml_fragment_writer)?;

    Ok(())
}

pub fn serialize_abstract_point_cloud_attributes(
    abstract_point_cloud: &AbstractPointCloud,
) -> Vec<(String, String)> {
    serialize_abstract_feature_attributes(abstract_point_cloud.abstract_feature())
}
