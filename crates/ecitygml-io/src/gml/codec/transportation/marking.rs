use crate::Error;
use crate::gml::codec::core::{
    deserialize_abstract_thematic_surface, serialize_abstract_thematic_surface,
    serialize_abstract_thematic_surface_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::core::AsAbstractThematicSurface;
use ecitygml_core::model::transportation::Marking;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::basic_types::Code;

pub fn deserialize_marking(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Marking, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_thematic_surface =
        deserialize_abstract_thematic_surface(xml_document, index, config)?;

    let mut marking = Marking::from_abstract_thematic_surface(abstract_thematic_surface);

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    marking.set_class_opt(class.map(Into::into));

    Ok(marking)
}

pub fn serialize_marking(
    marking: &Marking,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_marking_attributes(marking);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Transportation,
        CityGmlElement::Marking,
        attributes,
    )?;

    serialize_abstract_thematic_surface(marking.abstract_thematic_surface(), xml_fragment_writer)?;

    if let Some(class) = marking.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::ClassProperty,
        )?;
    }

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::Transportation, CityGmlElement::Marking)?;

    Ok(())
}

pub fn serialize_marking_attributes(marking: &Marking) -> Vec<(String, String)> {
    serialize_abstract_thematic_surface_attributes(marking.abstract_thematic_surface())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::core::{
        AsAbstractCityObject, AsAbstractFeature, AsAbstractThematicSurface,
    };
    use egml::model::base::Id;

    #[test]
    fn test_deserialize_basic_traffic_area() {
        let xml_document = b"<tran:Marking gml:id=\"UUID_312e01da-5c89-3f89-b8c0-3e0a8bafecbb\">
                  <genericAttribute>
                    <gen:StringAttribute>
                      <gen:name>opendrive_lane_type</gen:name>
                      <gen:value>BORDER</gen:value>
                    </gen:StringAttribute>
                  </genericAttribute>
                </tran:Marking>";

        let marking = deserialize_marking(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            marking.feature_id(),
            &Id::try_from("UUID_312e01da-5c89-3f89-b8c0-3e0a8bafecbb").expect("should work")
        );
        assert!(marking.lod2_multi_surface().is_none());
        assert_eq!(marking.generic_attributes().len(), 1);
    }
}
