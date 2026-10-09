use crate::Error;
use crate::gml::codec::common::serialize_string;
use crate::gml::codec::core::abstract_appearance_property::{
    deserialize_abstract_appearance_property, serialize_abstract_appearance_property,
};
use crate::gml::codec::core::transformation_matrix_4x4::{
    deserialize_transformation_matrix_4x4, serialize_transformation_matrix_4x4,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
    collect_gml_child,
};
use ecitygml_core::model::core::values::MimeTypeValue;
use ecitygml_core::model::core::{ImplicitGeometry, TransformationMatrix4x4};
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::codec::geometry::primitives::{deserialize_point_property, serialize_point_property};
use egml::io::codec::geometry::{
    deserialize_abstract_geometry_property, serialize_abstract_geometry_property,
};
use egml::io::util::{
    ChunkedSink, GmlAttribute, XmlDocumentIndex, XmlElement, XmlFragmentWriter, collect_children,
    deserialize_gml_attributes,
};
use egml::model::base::Id;
use egml::model::basic_types::Code;
use quick_xml::Reader;
use quick_xml::events::Event;
use std::sync::atomic::{AtomicU64, Ordering};

static NEXT_ID: AtomicU64 = AtomicU64::new(0);
fn generate_object_id() -> Id {
    let n = NEXT_ID.fetch_add(1, Ordering::Relaxed);
    Id::try_from(format!("ecitygml-gen-object-{n}"))
        .expect("ecitygml-gen-object-{n} is always a valid xsd:ID")
}

pub fn deserialize_implicit_geometry(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<ImplicitGeometry, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    // Consume the root `<ImplicitGeometry>` element's own start tag.
    loop {
        match reader.read_event()? {
            Event::Start(_) => break,
            Event::Eof => {
                return Err(Error::ElementNotFound("ImplicitGeometry".to_string()));
            }
            _ => {}
        }
    }

    let mut transformation_matrix: Option<TransformationMatrix4x4> = None;
    let mut mime_type: Option<Code> = None;
    let mut library_object: Option<String> = None;

    loop {
        match reader.read_event()? {
            Event::Start(start) => match start.local_name().as_ref() {
                "transformationMatrix" => {
                    let pos_start = reader.buffer_position() as usize - start.len() - 2;
                    reader.read_to_end(start.name())?;
                    let pos_end = reader.buffer_position() as usize;
                    transformation_matrix = Some(deserialize_transformation_matrix_4x4(
                        &xml_document[pos_start..pos_end],
                    )?);
                }
                "mimeType" => {
                    let pos_start = reader.buffer_position() as usize - start.len() - 2;
                    reader.read_to_end(start.name())?;
                    let pos_end = reader.buffer_position() as usize;
                    mime_type = Some(deserialize_code(&xml_document[pos_start..pos_end])?);
                }
                "libraryObject" => {
                    let text = reader.read_text(start.name())?;
                    let decoded = text.as_ref();
                    library_object = Some(decoded.trim().to_string());
                }
                _ => {
                    reader.read_to_end(start.name())?;
                }
            },
            Event::Eof => break,
            _ => {}
        }
    }

    // `ImplicitGeometryType` extends `gml:AbstractGMLType`, so its identifier is `gml:id`.
    let object_id = deserialize_gml_attributes(xml_document)?
        .get(&GmlAttribute::Id)
        .map(|id| Id::try_from(id.as_str()))
        .transpose()?
        .unwrap_or_else(generate_object_id);
    let transformation_matrix = transformation_matrix
        .ok_or_else(|| Error::ElementNotFound("transformationMatrix".to_string()))?;

    let reference_point = collect_gml_child(
        xml_document,
        index,
        CityGmlElement::ReferencePointProperty.into(),
        config.gml_config(),
        deserialize_point_property,
    )?
    .ok_or(Error::ElementNotFound("reference point not found".into()))?;

    let mut implicit_geometry =
        ImplicitGeometry::new(object_id, transformation_matrix, reference_point);
    implicit_geometry.set_mime_type_opt(mime_type.map(MimeTypeValue::from));
    implicit_geometry.set_library_object_opt(library_object);
    implicit_geometry.set_relative_geometry_opt(collect_gml_child(
        xml_document,
        index,
        CityGmlElement::RelativeGeometryProperty.into(),
        config.gml_config(),
        deserialize_abstract_geometry_property,
    )?);
    implicit_geometry.set_appearances(collect_children(
        xml_document,
        index,
        CityGmlElement::AbstractAppearanceProperty.into(),
        config,
        deserialize_abstract_appearance_property,
    )?);

    Ok(implicit_geometry)
}

pub fn serialize_implicit_geometry(
    implicit_geometry: &ImplicitGeometry,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Core,
        CityGmlElement::ImplicitGeometry,
        [(
            GmlAttribute::Id.local_name(),
            implicit_geometry.object_id().as_str(),
        )],
    )?;

    serialize_transformation_matrix_4x4(
        implicit_geometry.transformation_matrix(),
        xml_fragment_writer,
        CityGmlNamespace::Core,
        CityGmlElement::TransformationMatrixProperty,
    )?;

    if let Some(mime_type) = implicit_geometry.mime_type() {
        serialize_code(
            mime_type.code(),
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::MimeTypeProperty,
        )?;
    }

    if let Some(library_object) = implicit_geometry.library_object() {
        serialize_string(
            library_object,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::LibraryObjectProperty,
        )?;
    }

    serialize_point_property(
        implicit_geometry.reference_point(),
        xml_fragment_writer,
        CityGmlNamespace::Core,
        CityGmlElement::ReferencePointProperty,
    )?;

    if let Some(prop) = implicit_geometry.relative_geometry() {
        serialize_abstract_geometry_property(
            prop,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::RelativeGeometryProperty,
        )?;
    }

    for prop in implicit_geometry.appearances() {
        serialize_abstract_appearance_property(prop, xml_fragment_writer)?;
    }

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::Core, CityGmlElement::ImplicitGeometry)?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use crate::gml::codec::core::implicit_geometry::{
        deserialize_implicit_geometry, serialize_implicit_geometry,
    };
    use crate::gml::util::DeserializationConfig;
    use ecitygml_core::model::core::ImplicitGeometry;
    use egml::io::util::{ChunkedSink, Formatting, XmlDocumentIndex, XmlFragmentWriter};

    #[test]
    fn test_deserialize_implicit_geometry_basic() {
        let xml_document = b"<ImplicitGeometry>
    <transformationMatrix>-0.5894514707536183 -0.8078037903020735 0.0 0.0 0.8078037903020735 -0.5894514707536183 0.0 0.0 0.0 0.0 1.0 0.0 0.0 0.0 0.0 1.0</transformationMatrix>
    <referencePoint>
        <gml:Point>
            <gml:pos srsDimension=\"3\">678298.3706294019 5403791.857383491 366.9430094360463</gml:pos>
        </gml:Point>
    </referencePoint>
</ImplicitGeometry>";

        let implicit_geometry = deserialize_implicit_geometry(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            implicit_geometry
                .reference_point()
                .object()
                .expect("must exist")
                .pos()
                .x(),
            678298.3706294019
        );
        assert_eq!(
            implicit_geometry
                .reference_point()
                .object()
                .expect("must exist")
                .pos()
                .y(),
            5403791.857383491
        );
        assert_eq!(
            implicit_geometry
                .reference_point()
                .object()
                .expect("must exist")
                .pos()
                .z(),
            366.9430094360463
        );
    }

    /// In CityGML 3.0, `ImplicitGeometryType` extends `gml:AbstractGMLType`; its identifier
    /// (UML `objectID`) is encoded as the `gml:id` attribute, not as a child element.
    const IMPLICIT_GEOMETRY_WITH_ID: &[u8] = b"<ImplicitGeometry gml:id=\"tree_prototype\">
    <transformationMatrix>1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1</transformationMatrix>
    <referencePoint>
        <gml:Point>
            <gml:pos>1.0 2.0 3.0</gml:pos>
        </gml:Point>
    </referencePoint>
</ImplicitGeometry>";

    fn deserialize(xml_document: &[u8]) -> ImplicitGeometry {
        deserialize_implicit_geometry(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should deserialize")
    }

    fn serialize(implicit_geometry: &ImplicitGeometry) -> String {
        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_implicit_geometry(implicit_geometry, &mut xml_fragment_writer)
            .expect("should serialize");
        let mut buf = Vec::new();
        xml_fragment_writer
            .write_to(&mut buf)
            .expect("should flush fragments");
        String::from_utf8(buf).expect("should convert to string")
    }

    #[test]
    fn test_deserialize_implicit_geometry_reads_gml_id() {
        let implicit_geometry = deserialize(IMPLICIT_GEOMETRY_WITH_ID);
        assert_eq!(implicit_geometry.object_id().as_str(), "tree_prototype");
    }

    #[test]
    fn test_deserialize_implicit_geometry_without_gml_id_generates_one() {
        let implicit_geometry = deserialize(
            b"<ImplicitGeometry>
    <transformationMatrix>1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1</transformationMatrix>
    <referencePoint><gml:Point><gml:pos>1.0 2.0 3.0</gml:pos></gml:Point></referencePoint>
</ImplicitGeometry>",
        );
        assert!(
            implicit_geometry
                .object_id()
                .as_str()
                .starts_with("ecitygml-gen-object-")
        );
    }

    #[test]
    fn test_serialize_implicit_geometry_writes_gml_id_attribute() {
        let xml = serialize(&deserialize(IMPLICIT_GEOMETRY_WITH_ID));
        assert!(
            xml.contains("<ImplicitGeometry gml:id=\"tree_prototype\">"),
            "missing gml:id attribute: {xml}"
        );
        assert!(
            !xml.contains("objectId"),
            "unexpected objectId element: {xml}"
        );
    }

    #[test]
    fn test_implicit_geometry_id_round_trip() {
        let xml = serialize(&deserialize(IMPLICIT_GEOMETRY_WITH_ID));
        let implicit_geometry = deserialize(xml.as_bytes());
        assert_eq!(implicit_geometry.object_id().as_str(), "tree_prototype");
    }

    #[test]
    fn test_serialize_implicit_geometry_reference_point() {
        let xml_document = b"<ImplicitGeometry>
    <transformationMatrix>-0.5894514707536183 -0.8078037903020735 0.0 0.0 0.8078037903020735 -0.5894514707536183 0.0 0.0 0.0 0.0 1.0 0.0 0.0 0.0 0.0 1.0</transformationMatrix>
    <referencePoint>
        <gml:Point>
            <gml:pos srsDimension=\"3\">678298.3706294019 5403791.857383491 366.9430094360463</gml:pos>
        </gml:Point>
    </referencePoint>
</ImplicitGeometry>";

        let implicit_geometry = deserialize_implicit_geometry(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should deserialize");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_implicit_geometry(&implicit_geometry, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("referencePoint"), "missing <referencePoint>");
        assert!(
            xml.contains("678298.3706294019"),
            "missing reference point x coordinate"
        );
        assert!(
            xml.contains("5403791.857383491"),
            "missing reference point y coordinate"
        );
        assert!(
            xml.contains("366.9430094360463"),
            "missing reference point z coordinate"
        );
    }

    #[test]
    fn test_deserialize_implicit_geometry_with_relative_geometry() {
        let xml_document = b"<ImplicitGeometry>
  <transformationMatrix>10.289999999999994 0.0 0.0 0.0 0.0 10.289999999999994 0.0 0.0 0.0 0.0 10.289999999999994 0.0 0.0 0.0 0.0 1.0</transformationMatrix>
  <referencePoint>
    <gml:Point>
      <gml:pos>689949.3 5324001.1 586.3806</gml:pos>
    </gml:Point>
  </referencePoint>
  <relativeGeometry>
    <gml:MultiGeometry srsName=\"urn:ogc:def:crs:EPSG::25832\" srsDimension=\"3\" gml:id=\"fme-gen-1b18fb8f-dbee-460c-bd8e-4e3229066ea2\">
      <gml:geometryMember>
        <gml:MultiGeometry>
          <gml:geometryMember>
            <gml:Polygon>
              <gml:exterior>
                <gml:LinearRing>
                  <gml:posList>1.1102230246251565E-16 -0.08104761325536736 0.40000000000000024 5.551115123125783E-17 -0.25873011317535366 0.42868290603009473 -0.18294981752345554 -0.1829498175234554 0.42868290603009473 -0.057309316931854926 -0.057309316931854926 0.40000000000000024 1.1102230246251565E-16 -0.08104761325536736 0.40000000000000024</gml:posList>
                </gml:LinearRing>
              </gml:exterior>
            </gml:Polygon>
          </gml:geometryMember>
          <gml:geometryMember>
            <gml:Polygon>
              <gml:exterior>
                <gml:LinearRing>
                  <gml:posList>-0.057309316931854926 -0.057309316931854926 0.40000000000000024 -0.18294981752345554 -0.1829498175234554 0.42868290603009473 -0.25873011317535366 0.0 0.42868290603009473 -0.0810476132553673 0.0 0.40000000000000024 -0.057309316931854926 -0.057309316931854926 0.40000000000000024</gml:posList>
                </gml:LinearRing>
              </gml:exterior>
            </gml:Polygon>
          </gml:geometryMember>
          <gml:geometryMember>
            <gml:Polygon>
              <gml:exterior>
                <gml:LinearRing>
                  <gml:posList>-0.24026196252347953 0.24026196252347976 0.49950174129794134 -0.24748737341529176 0.2474873734152918 0.6403170178482882 5.551115123125783E-17 0.3500000000000002 0.6403170178482882 5.551115123125783E-17 0.3397817259230812 0.49950174129794134 -0.24026196252347953 0.24026196252347976 0.49950174129794134</gml:posList>
                </gml:LinearRing>
              </gml:exterior>
            </gml:Polygon>
          </gml:geometryMember>
        </gml:MultiGeometry>
      </gml:geometryMember>
    </gml:MultiGeometry>
  </relativeGeometry>
</ImplicitGeometry>";

        let implicit_geometry = deserialize_implicit_geometry(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should deserialize");

        let reference_point = implicit_geometry
            .reference_point()
            .object()
            .expect("reference point must exist");
        assert_eq!(reference_point.pos().x(), 689949.3);
        assert_eq!(reference_point.pos().y(), 5324001.1);
        assert_eq!(reference_point.pos().z(), 586.3806);

        assert_eq!(
            implicit_geometry.transformation_matrix().matrix()[(0, 0)],
            10.289999999999994
        );

        assert!(
            implicit_geometry.relative_geometry().is_some(),
            "relative geometry must be present"
        );
    }

    #[test]
    fn test_serialize_implicit_geometry_with_relative_geometry() {
        let xml_document = b"<ImplicitGeometry>
  <transformationMatrix>10.289999999999994 0.0 0.0 0.0 0.0 10.289999999999994 0.0 0.0 0.0 0.0 10.289999999999994 0.0 0.0 0.0 0.0 1.0</transformationMatrix>
  <referencePoint>
    <gml:Point>
      <gml:pos>689949.3 5324001.1 586.3806</gml:pos>
    </gml:Point>
  </referencePoint>
  <relativeGeometry>
    <gml:MultiGeometry srsName=\"urn:ogc:def:crs:EPSG::25832\" srsDimension=\"3\" gml:id=\"fme-gen-1b18fb8f-dbee-460c-bd8e-4e3229066ea2\">
      <gml:geometryMember>
        <gml:MultiGeometry>
          <gml:geometryMember>
            <gml:Polygon>
              <gml:exterior>
                <gml:LinearRing>
                  <gml:posList>1.1102230246251565E-16 -0.08104761325536736 0.40000000000000024 5.551115123125783E-17 -0.25873011317535366 0.42868290603009473 -0.18294981752345554 -0.1829498175234554 0.42868290603009473 -0.057309316931854926 -0.057309316931854926 0.40000000000000024 1.1102230246251565E-16 -0.08104761325536736 0.40000000000000024</gml:posList>
                </gml:LinearRing>
              </gml:exterior>
            </gml:Polygon>
          </gml:geometryMember>
          <gml:geometryMember>
            <gml:Polygon>
              <gml:exterior>
                <gml:LinearRing>
                  <gml:posList>-0.057309316931854926 -0.057309316931854926 0.40000000000000024 -0.18294981752345554 -0.1829498175234554 0.42868290603009473 -0.25873011317535366 0.0 0.42868290603009473 -0.0810476132553673 0.0 0.40000000000000024 -0.057309316931854926 -0.057309316931854926 0.40000000000000024</gml:posList>
                </gml:LinearRing>
              </gml:exterior>
            </gml:Polygon>
          </gml:geometryMember>
          <gml:geometryMember>
            <gml:Polygon>
              <gml:exterior>
                <gml:LinearRing>
                  <gml:posList>-0.24026196252347953 0.24026196252347976 0.49950174129794134 -0.24748737341529176 0.2474873734152918 0.6403170178482882 5.551115123125783E-17 0.3500000000000002 0.6403170178482882 5.551115123125783E-17 0.3397817259230812 0.49950174129794134 -0.24026196252347953 0.24026196252347976 0.49950174129794134</gml:posList>
                </gml:LinearRing>
              </gml:exterior>
            </gml:Polygon>
          </gml:geometryMember>
        </gml:MultiGeometry>
      </gml:geometryMember>
    </gml:MultiGeometry>
  </relativeGeometry>
</ImplicitGeometry>";

        let implicit_geometry = deserialize_implicit_geometry(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should deserialize");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_implicit_geometry(&implicit_geometry, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("referencePoint"), "missing <referencePoint>");
        assert!(xml.contains("689949.3"), "missing reference point x");
        assert!(xml.contains("5324001.1"), "missing reference point y");
        assert!(xml.contains("586.3806"), "missing reference point z");
        assert!(
            xml.contains("relativeGeometry"),
            "missing <relativeGeometry>"
        );
        assert!(xml.contains("MultiGeometry"), "missing <MultiGeometry>");
        assert!(xml.contains("Polygon"), "missing <Polygon>");
    }
}
