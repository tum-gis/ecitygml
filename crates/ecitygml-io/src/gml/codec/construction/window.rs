use crate::Error;
use crate::gml::codec::construction::abstract_filling_element::{
    deserialize_abstract_filling_element, serialize_abstract_filling_element,
    serialize_abstract_filling_element_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::construction::{AsAbstractFillingElement, Window};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_window(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Window, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_filling_element =
        deserialize_abstract_filling_element(xml_document, index, config)?;
    let window = Window::from_abstract_filling_element(abstract_filling_element);

    Ok(window)
}

pub fn serialize_window(
    window: &Window,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_window_attributes(window);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Construction,
        CityGmlElement::Window,
        attributes,
    )?;

    serialize_abstract_filling_element(window.abstract_filling_element(), xml_fragment_writer)?;

    xml_fragment_writer.write_end_event(CityGmlNamespace::Construction, CityGmlElement::Window)?;

    Ok(())
}

pub fn serialize_window_attributes(window: &Window) -> Vec<(String, String)> {
    serialize_abstract_filling_element_attributes(window.abstract_filling_element())
}

#[cfg(test)]
mod tests {
    use super::*;

    use ecitygml_core::model::core::{AsAbstractCityObject, AsAbstractFeature};
    use egml::model::base::Id;

    #[test]
    fn test_deserialize_basic_window() {
        let xml_document = b"<con:Window gml:id=\"GML_d38cf762-c29d-4491-88c9-bdc89e141978\">
              <gml:name>Window name</gml:name>
              <gen:genericAttribute>
                <gen:IntAttribute>
                  <gen:name>cleaning_number</gen:name>
                  <gen:value>10</gen:value>
                </gen:IntAttribute>
              </gen:genericAttribute>
              </con:Window>";

        let window = deserialize_window(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            window.feature_id(),
            &Id::try_from("GML_d38cf762-c29d-4491-88c9-bdc89e141978").expect("should work")
        );
        //assert!(window.lod3_multi_surface().is_some());
        assert_eq!(window.generic_attributes().len(), 1);
    }
}
