use crate::Error;
use crate::gml::codec::relief::abstract_relief_component::{
    deserialize_abstract_relief_component, serialize_abstract_relief_component,
    serialize_abstract_relief_component_attributes,
};
use crate::gml::codec::relief::tin_property::{deserialize_tin_property, serialize_tin_property};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::relief::{AsAbstractReliefComponent, TinRelief};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter, collect_child};

pub fn deserialize_tin_relief(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<TinRelief, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let (abstract_relief_component_result, tin_result) = rayon::join(
        || deserialize_abstract_relief_component(xml_document, index, config),
        || {
            collect_child(
                xml_document,
                index,
                CityGmlElement::TinProperty.into(),
                config,
                deserialize_tin_property,
            )
        },
    );
    let abstract_relief_component = abstract_relief_component_result?;
    let tin = tin_result?;

    let mut tin_relief = TinRelief::from_abstract_relief_component(abstract_relief_component);
    tin_relief.set_tin_opt(tin);

    Ok(tin_relief)
}

pub fn serialize_tin_relief(
    tin_relief: &TinRelief,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_tin_relief_attributes(tin_relief);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Relief,
        CityGmlElement::TINRelief,
        attributes,
    )?;

    serialize_abstract_relief_component(
        tin_relief.abstract_relief_component(),
        xml_fragment_writer,
    )?;

    if let Some(prop) = tin_relief.tin() {
        serialize_tin_property(prop, xml_fragment_writer)?;
    }

    xml_fragment_writer.write_end_event(CityGmlNamespace::Relief, CityGmlElement::TINRelief)?;

    Ok(())
}

pub fn serialize_tin_relief_attributes(tin_relief: &TinRelief) -> Vec<(String, String)> {
    serialize_abstract_relief_component_attributes(tin_relief.abstract_relief_component())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::common::LevelOfDetail;
    use ecitygml_core::model::core::AsAbstractFeature;
    use ecitygml_core::model::relief::AsAbstractReliefComponent;
    use egml::model::base::Id;
    use egml::model::geometry::primitives::AsSurface;

    #[test]
    fn test_deserialize_tin_relief() {
        let xml_document = "
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
            </dem:TINRelief>";

        let tin_relief = deserialize_tin_relief(
            xml_document.as_bytes(),
            &XmlDocumentIndex::from_scan(xml_document.as_bytes(), None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(tin_relief.feature_id(), &Id::try_from("abc").unwrap());
        assert_eq!(tin_relief.lod(), LevelOfDetail::Three);
        assert_eq!(tin_relief.tin().unwrap().object().unwrap().patches_len(), 1);
    }

    #[test]
    pub fn test_deserialize_tin_relief_basic() {
        let xml_document = "<dem:TINRelief>
          <dem:lod>2</dem:lod>
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
                <gml:Triangle>
                  <gml:exterior>
                    <gml:LinearRing gml:id=\"Geo28109129\">
                      <gml:posList>513077.98546 5403284.940675 245.28 513073.615171 5403277.62549 244.056421 513080.474403 5403283.461339 245.28 513077.98546 5403284.940675 245.28</gml:posList>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Triangle>
              </gml:patches>
            </gml:TriangulatedSurface>
          </dem:tin>
        </dem:TINRelief>";

        let tin_relief = deserialize_tin_relief(
            xml_document.as_bytes(),
            &XmlDocumentIndex::from_scan(xml_document.as_bytes(), None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(tin_relief.lod(), LevelOfDetail::Two);
        assert_eq!(tin_relief.tin().unwrap().object().unwrap().patches_len(), 2);
    }
}
