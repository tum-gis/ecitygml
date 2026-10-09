use crate::Error;
use crate::gml::codec::core::basic_types::{deserialize_lod, serialize_lod};
use crate::gml::codec::core::{
    deserialize_abstract_space_boundary, serialize_abstract_space_boundary,
    serialize_abstract_space_boundary_attributes,
};
use crate::gml::codec::relief::abstract_relief_component_property::{
    deserialize_abstract_relief_component_property, serialize_abstract_relief_component_property,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::core::AsAbstractSpaceBoundary;
use ecitygml_core::model::relief::ReliefFeature;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use egml::io::util::{XmlDocumentIndex, collect_children};

pub fn deserialize_relief_feature(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<ReliefFeature, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let mut abstract_space_boundary_result = None;
    let mut relief_components_result = None;

    rayon::scope(|s| {
        s.spawn(|_| {
            abstract_space_boundary_result = Some(deserialize_abstract_space_boundary(
                xml_document,
                index,
                config,
            ));
        });
        s.spawn(|_| {
            relief_components_result = Some(collect_children(
                xml_document,
                index,
                CityGmlElement::AbstractReliefComponentProperty.into(),
                config,
                deserialize_abstract_relief_component_property,
            ));
        });
    });

    let lod_index = index
        .first(CityGmlElement::LodProperty.into())
        .ok_or_else(|| Error::ElementNotFound("lod not found".into()))?;
    let lod = deserialize_lod(&xml_document[lod_index.range()])?;

    let mut relief_feature = ReliefFeature::from_abstract_space_boundary(
        abstract_space_boundary_result.expect("rayon::scope guarantees all spawns complete")?,
        lod,
    );
    relief_feature.set_relief_components(
        relief_components_result.expect("rayon::scope guarantees all spawns complete")?,
    );
    Ok(relief_feature)
}

pub fn serialize_relief_feature(
    relief_feature: &ReliefFeature,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_relief_feature_attributes(relief_feature);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Relief,
        CityGmlElement::ReliefFeature,
        attributes,
    )?;

    serialize_abstract_space_boundary(
        relief_feature.abstract_space_boundary(),
        xml_fragment_writer,
    )?;

    serialize_lod(
        relief_feature.lod(),
        xml_fragment_writer,
        CityGmlNamespace::Relief,
        CityGmlElement::LodProperty,
    )?;

    for component in relief_feature.relief_components() {
        serialize_abstract_relief_component_property(component, xml_fragment_writer)?;
    }

    xml_fragment_writer.write_end_event(CityGmlNamespace::Relief, CityGmlElement::ReliefFeature)?;

    Ok(())
}

pub fn serialize_relief_feature_attributes(
    relief_feature: &ReliefFeature,
) -> Vec<(String, String)> {
    serialize_abstract_space_boundary_attributes(relief_feature.abstract_space_boundary())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::common::LevelOfDetail;
    use ecitygml_core::model::core::AsAbstractFeature;
    use egml::io::util::{Formatting, XmlFragmentWriter};
    use egml::model::base::Id;

    #[test]
    fn test_deserialize_tin_relief() {
        let xml_document = "
            <dem:ReliefFeature gml:id=\"ID_7a8b707e-f87c-35f3-8e3c-254427e59493\">
              <dem:lod>2</dem:lod>
              <dem:reliefComponent>
                <dem:TINRelief gml:id=\"abc\">
                  <dem:lod>3</dem:lod>
                    <dem:tin>
                    <gml:TriangulatedSurface gml:id=\"ground\">
                      <gml:patches>
                        <gml:Triangle>
                          <gml:exterior>
                            <gml:LinearRing gml:id=\"Geo28109128\">
                              <gml:posList>513037.352708 5403284.890495 247.27 513034.424098 5403297.424959 247.19 513034.423981 5403287.429362 247.3 513037.352708 5403284.890495 247.27</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Triangle>
                      </gml:patches>
                    </gml:TriangulatedSurface>
                    </dem:tin>
                </dem:TINRelief>
              </dem:reliefComponent>
            </dem:ReliefFeature>";

        let relief_feature = deserialize_relief_feature(
            xml_document.as_bytes(),
            &XmlDocumentIndex::from_scan(xml_document.as_bytes(), None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            relief_feature.feature_id(),
            &Id::try_from("ID_7a8b707e-f87c-35f3-8e3c-254427e59493").unwrap()
        );
        assert_eq!(relief_feature.lod(), LevelOfDetail::Two);
        assert_eq!(relief_feature.num_relief_components(), 1);

        let abstract_relief_component_property = relief_feature
            .relief_components()
            .first()
            .to_owned()
            .unwrap();
        assert!(abstract_relief_component_property.object().is_some());
        let relief_component = abstract_relief_component_property.object().unwrap();
        assert_eq!(relief_component.feature_id(), &Id::try_from("abc").unwrap());
    }

    #[test]
    fn test_round_trip_relief_feature() {
        let xml_document = "
            <dem:ReliefFeature gml:id=\"ID_7a8b707e-f87c-35f3-8e3c-254427e59493\">
              <dem:lod>1</dem:lod>
            </dem:ReliefFeature>";

        let relief_feature = deserialize_relief_feature(
            xml_document.as_bytes(),
            &XmlDocumentIndex::from_scan(xml_document.as_bytes(), None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");
        assert_eq!(relief_feature.lod(), LevelOfDetail::One);

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_relief_feature(&relief_feature, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("dem:lod"));
        assert!(xml.contains('1'));

        let round_tripped = deserialize_relief_feature(
            xml.as_bytes(),
            &XmlDocumentIndex::from_scan(xml.as_bytes(), None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(relief_feature.lod(), round_tripped.lod());
    }
}
