use crate::Error;
use crate::gml::codec::core::{
    deserialize_abstract_thematic_surface, serialize_abstract_thematic_surface,
    serialize_abstract_thematic_surface_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::core::{AsAbstractThematicSurface, ClosureSurface};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_closure_surface(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<ClosureSurface, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_thematic_surface =
        deserialize_abstract_thematic_surface(xml_document, index, config)?;
    Ok(ClosureSurface::from_abstract_thematic_surface(
        abstract_thematic_surface,
    ))
}

pub fn serialize_closure_surface(
    closure_surface: &ClosureSurface,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_closure_surface_attributes(closure_surface);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Core,
        CityGmlElement::ClosureSurface,
        attributes,
    )?;

    serialize_abstract_thematic_surface(
        closure_surface.abstract_thematic_surface(),
        xml_fragment_writer,
    )?;

    xml_fragment_writer.write_end_event(CityGmlNamespace::Core, CityGmlElement::ClosureSurface)?;

    Ok(())
}

pub fn serialize_closure_surface_attributes(
    closure_surface: &ClosureSurface,
) -> Vec<(String, String)> {
    serialize_abstract_thematic_surface_attributes(closure_surface.abstract_thematic_surface())
}

#[cfg(test)]
mod tests {
    use super::*;

    use ecitygml_core::model::core::AsAbstractFeature;
    use egml::model::base::Id;

    #[test]
    fn test_deserialize_empty_closure_surface() {
        let xml_document =
            b"<ClosureSurface gml:id=\"fme-gen-f460209b-63b5-4ff8-92d5-cec932987265\"/>";

        let closure_surface = deserialize_closure_surface(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            closure_surface.feature_id(),
            &Id::try_from("fme-gen-f460209b-63b5-4ff8-92d5-cec932987265").expect("should work")
        );
    }
}
