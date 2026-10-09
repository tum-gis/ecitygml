use crate::Error;
use crate::gml::codec::common::{deserialize_string, serialize_string};
use crate::gml::codec::core::{
    deserialize_abstract_point_cloud, serialize_abstract_point_cloud,
    serialize_abstract_point_cloud_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
    collect_gml_child_lenient,
};
use ecitygml_core::model::core::AsAbstractPointCloud;
use ecitygml_core::model::point_cloud::PointCloud;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::codec::geometry::aggregates::{
    deserialize_multi_point_property, serialize_multi_point_property,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::basic_types::Code;

pub fn deserialize_point_cloud(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<PointCloud, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let mut abstract_point_cloud_result = None;
    let mut points_result = None;

    rayon::scope(|s| {
        s.spawn(|_| {
            abstract_point_cloud_result = Some(deserialize_abstract_point_cloud(
                xml_document,
                index,
                config,
            ));
        });
        s.spawn(|_| {
            points_result = Some(collect_gml_child_lenient(
                xml_document,
                index,
                CityGmlElement::PointsProperty.into(),
                config.gml_config(),
                deserialize_multi_point_property,
            ));
        });
    });

    let mut point_cloud = PointCloud::from_abstract_point_cloud(
        abstract_point_cloud_result.expect("rayon::scope guarantees all spawns complete")?,
    );

    let mime_type: Option<Code> = index
        .first(CityGmlElement::MimeTypeProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    point_cloud.set_mime_type_opt(mime_type.map(Into::into));

    let point_file: Option<String> = index
        .first(CityGmlElement::PointFileProperty.into())
        .map(|x| deserialize_string(&xml_document[x.range()]))
        .transpose()?;
    point_cloud.set_point_file_opt(point_file);

    let point_file_srs_name: Option<String> = index
        .first(CityGmlElement::PointFileSrsNameProperty.into())
        .map(|x| deserialize_string(&xml_document[x.range()]))
        .transpose()?;
    point_cloud.set_point_file_srs_name_opt(point_file_srs_name);

    point_cloud.set_points_opt(points_result.expect("rayon::scope guarantees all spawns complete"));

    Ok(point_cloud)
}

pub fn serialize_point_cloud(
    point_cloud: &PointCloud,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_point_cloud_attributes(point_cloud);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::PointCloud,
        CityGmlElement::PointCloud,
        attributes,
    )?;

    serialize_abstract_point_cloud(point_cloud.abstract_point_cloud(), xml_fragment_writer)?;

    if let Some(mime_type) = point_cloud.mime_type() {
        serialize_code(
            mime_type.code(),
            xml_fragment_writer,
            CityGmlNamespace::PointCloud,
            CityGmlElement::MimeTypeProperty,
        )?;
    }

    if let Some(point_file) = point_cloud.point_file() {
        serialize_string(
            point_file,
            xml_fragment_writer,
            CityGmlNamespace::PointCloud,
            CityGmlElement::PointFileProperty,
        )?;
    }

    if let Some(point_file_srs_name) = point_cloud.point_file_srs_name() {
        serialize_string(
            point_file_srs_name,
            xml_fragment_writer,
            CityGmlNamespace::PointCloud,
            CityGmlElement::PointFileSrsNameProperty,
        )?;
    }

    if let Some(prop) = point_cloud.points() {
        serialize_multi_point_property(
            prop,
            xml_fragment_writer,
            CityGmlNamespace::PointCloud,
            CityGmlElement::PointsProperty,
        )?;
    }

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::PointCloud, CityGmlElement::PointCloud)?;

    Ok(())
}

pub fn serialize_point_cloud_attributes(point_cloud: &PointCloud) -> Vec<(String, String)> {
    serialize_abstract_point_cloud_attributes(point_cloud.abstract_point_cloud())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::core::AsAbstractFeature;
    use egml::io::util::Formatting;
    use egml::model::base::Id;

    #[test]
    fn test_deserialize_point_cloud_id_and_file_metadata() {
        let xml_document = b"<pcl:PointCloud gml:id=\"test-point-cloud-001\">
  <pcl:pointFile>abc.las</pcl:pointFile>
  <pcl:pointFileSrsName>EPSG:25832</pcl:pointFileSrsName>
</pcl:PointCloud>";

        let point_cloud = deserialize_point_cloud(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            point_cloud.feature_id(),
            &Id::try_from("test-point-cloud-001").expect("should work")
        );
        assert_eq!(point_cloud.point_file(), Some("abc.las"));
        assert_eq!(point_cloud.point_file_srs_name(), Some("EPSG:25832"));
        assert!(point_cloud.mime_type().is_none());
        assert!(point_cloud.points().is_none());
    }

    #[test]
    fn test_deserialize_point_cloud_point_member() {
        let xml_document = b"<pcl:PointCloud gml:id=\"test-point-cloud-002\">
  <pcl:points>
    <gml:MultiPoint>
      <gml:pointMember>
        <gml:Point>
          <gml:pos>678267.6213956032 5403783.626290152 366.96639999999996</gml:pos>
        </gml:Point>
      </gml:pointMember>
      <gml:pointMember>
        <gml:Point>
          <gml:pos>678289.06567932 5403807.373180328 366.99789425533834</gml:pos>
        </gml:Point>
      </gml:pointMember>
    </gml:MultiPoint>
  </pcl:points>
</pcl:PointCloud>";

        let point_cloud = deserialize_point_cloud(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let multi_point = point_cloud
            .points()
            .expect("points should be present")
            .object()
            .expect("MultiPoint object should be present");

        assert_eq!(multi_point.point_member().len(), 2);
        assert_eq!(
            multi_point.point_member()[0]
                .object()
                .expect("point should be present")
                .pos()
                .x(),
            678267.6213956032
        );
        assert_eq!(
            multi_point.point_member()[1]
                .object()
                .expect("point should be present")
                .pos()
                .x(),
            678289.06567932
        );
    }

    #[test]
    fn test_deserialize_point_cloud_point_members() {
        let xml_document = b"<pcl:PointCloud gml:id=\"test-point-cloud-003\">
  <pcl:points>
    <gml:MultiPoint>
      <gml:pointMembers>
        <gml:Point>
          <gml:pos>678267.6213956032 5403783.626290152 366.96639999999996</gml:pos>
        </gml:Point>
        <gml:Point>
          <gml:pos>678289.06567932 5403807.373180328 366.99789425533834</gml:pos>
        </gml:Point>
      </gml:pointMembers>
    </gml:MultiPoint>
  </pcl:points>
</pcl:PointCloud>";

        let point_cloud = deserialize_point_cloud(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let multi_point = point_cloud
            .points()
            .expect("points should be present")
            .object()
            .expect("MultiPoint object should be present");

        assert!(multi_point.point_member().is_empty());

        let point_members = multi_point
            .point_members()
            .expect("pointMembers should be present");
        assert_eq!(point_members.objects().len(), 2);
        assert_eq!(point_members.objects()[0].pos().x(), 678267.6213956032);
        assert_eq!(point_members.objects()[1].pos().x(), 678289.06567932);
    }

    #[test]
    fn test_round_trip_point_cloud_with_mime_type_and_file_metadata() {
        let xml_document = b"<pcl:PointCloud gml:id=\"test-point-cloud-004\">
  <pcl:mimeType>application/vnd.las</pcl:mimeType>
  <pcl:pointFile>abc.las</pcl:pointFile>
  <pcl:pointFileSrsName>EPSG:25832</pcl:pointFileSrsName>
</pcl:PointCloud>";

        let point_cloud = deserialize_point_cloud(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            point_cloud
                .mime_type()
                .expect("mime_type should be read")
                .code()
                .value(),
            "application/vnd.las"
        );

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_point_cloud(&point_cloud, &mut xml_fragment_writer).expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("pcl:mimeType"));
        assert!(xml.contains("application/vnd.las"));
        assert!(xml.contains("pcl:pointFile"));
        assert!(xml.contains("abc.las"));
        assert!(xml.contains("pcl:pointFileSrsName"));
        assert!(xml.contains("EPSG:25832"));

        let round_tripped = deserialize_point_cloud(
            xml.as_bytes(),
            &XmlDocumentIndex::from_scan(xml.as_bytes(), None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            point_cloud
                .mime_type()
                .map(|x| x.code().value().to_string()),
            round_tripped
                .mime_type()
                .map(|x| x.code().value().to_string())
        );
        assert_eq!(point_cloud.point_file(), round_tripped.point_file());
        assert_eq!(
            point_cloud.point_file_srs_name(),
            round_tripped.point_file_srs_name()
        );
    }
}
