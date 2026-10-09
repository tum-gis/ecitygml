use crate::Error;
use crate::gml::codec::core::basic_types::{deserialize_lod, serialize_lod};
use crate::gml::codec::core::{
    deserialize_abstract_space_boundary, serialize_abstract_space_boundary,
    serialize_abstract_space_boundary_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::core::AsAbstractSpaceBoundary;
use ecitygml_core::model::relief::{AbstractReliefComponent, AsAbstractReliefComponent};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_relief_component(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractReliefComponent, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_relief_component received a truncated index — caller must scan to sufficient depth"
    );

    let abstract_space_boundary = deserialize_abstract_space_boundary(xml_document, index, config)?;

    let lod_index = index
        .first(CityGmlElement::LodProperty.into())
        .ok_or_else(|| Error::ElementNotFound("lod not found".into()))?;
    let lod = deserialize_lod(&xml_document[lod_index.range()])?;

    let abstract_relief_component =
        AbstractReliefComponent::from_abstract_space_boundary(abstract_space_boundary, lod);
    Ok(abstract_relief_component)
}

pub fn serialize_abstract_relief_component(
    abstract_relief_component: &AbstractReliefComponent,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_space_boundary(
        abstract_relief_component.abstract_space_boundary(),
        xml_fragment_writer,
    )?;

    serialize_lod(
        abstract_relief_component.lod(),
        xml_fragment_writer,
        CityGmlNamespace::Relief,
        CityGmlElement::LodProperty,
    )?;

    Ok(())
}

pub fn serialize_abstract_relief_component_attributes(
    abstract_relief_component: &AbstractReliefComponent,
) -> Vec<(String, String)> {
    serialize_abstract_space_boundary_attributes(
        abstract_relief_component.abstract_space_boundary(),
    )
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
                <dem:TINRelief gml:id=\"abc\">
                  <dem:lod>2</dem:lod>
                </dem:TINRelief>";

        let index = XmlDocumentIndex::from_scan(xml_document.as_ref(), None).expect("should work");
        let abstract_relief_component = deserialize_abstract_relief_component(
            xml_document.as_ref(),
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            abstract_relief_component.feature_id(),
            &Id::try_from("abc").unwrap()
        );
        assert_eq!(abstract_relief_component.lod(), LevelOfDetail::Two);
    }

    #[test]
    fn test_round_trip_abstract_relief_component() {
        let xml_document = "
                <dem:TINRelief gml:id=\"abc\">
                  <dem:lod>3</dem:lod>
                </dem:TINRelief>";

        let index = XmlDocumentIndex::from_scan(xml_document.as_ref(), None).expect("should work");
        let abstract_relief_component = deserialize_abstract_relief_component(
            xml_document.as_ref(),
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        xml_fragment_writer
            .write_start_event(CityGmlNamespace::Relief, CityGmlElement::TINRelief)
            .expect("should work");
        serialize_abstract_relief_component(&abstract_relief_component, &mut xml_fragment_writer)
            .expect("should serialize");
        xml_fragment_writer
            .write_end_event(CityGmlNamespace::Relief, CityGmlElement::TINRelief)
            .expect("should work");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("dem:lod"));
        assert!(xml.contains('3'));

        let round_tripped_index =
            XmlDocumentIndex::from_scan(xml.as_bytes(), None).expect("should work");
        let round_tripped = deserialize_abstract_relief_component(
            xml.as_bytes(),
            &round_tripped_index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(abstract_relief_component.lod(), round_tripped.lod());
    }
}
