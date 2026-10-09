use crate::Error;
use crate::gml::codec::point_cloud::{deserialize_point_cloud, serialize_point_cloud};
use crate::gml::util::{CityGmlElement, CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::core::AbstractPointCloudKind;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_point_cloud_kind(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Option<AbstractPointCloudKind>, Error> {
    if let Some(index) = index.first(CityGmlElement::PointCloud.into()) {
        let point_cloud = deserialize_point_cloud(&xml_document[index.range()], index, config)?;
        return Ok(Some(point_cloud.into()));
    }

    Ok(None)
}

pub fn serialize_abstract_point_cloud_kind(
    abstract_point_cloud_kind: &AbstractPointCloudKind,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    match abstract_point_cloud_kind {
        AbstractPointCloudKind::PointCloud(x) => serialize_point_cloud(x, xml_fragment_writer),
    }
}
