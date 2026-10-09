use crate::Error;
use crate::gml::codec::core::{
    deserialize_abstract_filling_surface, serialize_abstract_filling_surface,
    serialize_abstract_filling_surface_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::construction::{AsAbstractFillingSurface, WindowSurface};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_window_surface(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<WindowSurface, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_filling_surface =
        deserialize_abstract_filling_surface(xml_document, index, config)?;
    let window_surface = WindowSurface::from_abstract_filling_surface(abstract_filling_surface);

    Ok(window_surface)
}

pub fn serialize_window_surface(
    window_surface: &WindowSurface,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_window_surface_attributes(window_surface);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Construction,
        CityGmlElement::WindowSurface,
        attributes,
    )?;

    serialize_abstract_filling_surface(
        window_surface.abstract_filling_surface(),
        xml_fragment_writer,
    )?;

    xml_fragment_writer.write_end_event(
        CityGmlNamespace::Construction,
        CityGmlElement::WindowSurface,
    )?;

    Ok(())
}

pub fn serialize_window_surface_attributes(
    window_surface: &WindowSurface,
) -> Vec<(String, String)> {
    serialize_abstract_filling_surface_attributes(window_surface.abstract_filling_surface())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::core::{AsAbstractFeature, AsAbstractThematicSurface};
    use egml::io::util::{Formatting, XmlFragmentWriter};
    use egml::model::base::{AsAbstractGml, Id};
    use egml::model::basic_types::Code;
    use itertools::Itertools;

    #[test]
    fn test_serialize_round_trip() {
        let xml_document = b"
            <con:WindowSurface gml:id=\"GML_d0f329f3-5b05-428d-87c3-945b3868337f\">
              <gml:name>Window West</gml:name>
              <lod3MultiSurface>
                <gml:MultiSurface>
                  <gml:surfaceMember>
                    <gml:Polygon gml:id=\"PolyID58821_1939_612838_272028\">
                      <gml:exterior>
                        <gml:LinearRing gml:id=\"PolyID58821_1939_612838_272028_0\">
                          <gml:pos>457843.79 5439083.12 112.8</gml:pos>
                          <gml:pos>457845.79 5439083.12 112.8</gml:pos>
                          <gml:pos>457845.79 5439083.12 114.0</gml:pos>
                          <gml:pos>457843.79 5439083.12 114.0</gml:pos>
                          <gml:pos>457843.79 5439083.12 112.8</gml:pos>
                        </gml:LinearRing>
                      </gml:exterior>
                    </gml:Polygon>
                  </gml:surfaceMember>
                </gml:MultiSurface>
              </lod3MultiSurface>
            </con:WindowSurface>";

        let window_surface = deserialize_window_surface(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .unwrap();
        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::default());
        serialize_window_surface(&window_surface, &mut xml_fragment_writer).unwrap();
        let xml_output = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .unwrap();

        assert!(xml_output.contains("con:WindowSurface"));
        assert!(xml_output.contains("gml:id=\"GML_d0f329f3-5b05-428d-87c3-945b3868337f\""));
        assert!(xml_output.contains("gml:name"));
        assert!(xml_output.contains("Window West"));
        assert!(xml_output.contains("lod3MultiSurface"));
        assert!(xml_output.contains("gml:MultiSurface"));
        assert!(xml_output.contains("gml:Polygon"));
    }

    #[test]
    fn test_serialize_with_generic_attributes() {
        let xml_document = b"
            <con:WindowSurface gml:id=\"test-window-id\">
              <genericAttribute>
                <gen:StringAttribute>
                  <gen:name>material</gen:name>
                  <gen:value>glass</gen:value>
                </gen:StringAttribute>
              </genericAttribute>
              <lod2MultiSurface>
                <gml:MultiSurface>
                  <gml:surfaceMember>
                    <gml:Polygon>
                      <gml:exterior>
                        <gml:LinearRing>
                          <gml:pos>0.0 0.0 0.0</gml:pos>
                          <gml:pos>1.0 0.0 0.0</gml:pos>
                          <gml:pos>1.0 1.0 0.0</gml:pos>
                          <gml:pos>0.0 0.0 0.0</gml:pos>
                        </gml:LinearRing>
                      </gml:exterior>
                    </gml:Polygon>
                  </gml:surfaceMember>
                </gml:MultiSurface>
              </lod2MultiSurface>
            </con:WindowSurface>";

        let window_surface = deserialize_window_surface(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .unwrap();
        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::default());
        serialize_window_surface(&window_surface, &mut xml_fragment_writer).unwrap();
        let xml_output = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .unwrap();

        assert!(xml_output.contains("genericAttribute"));
        assert!(xml_output.contains("material"));
        assert!(xml_output.contains("glass"));
        assert!(xml_output.contains("lod2MultiSurface"));
    }

    #[test]
    fn test_deserialize_with_lod3_multi_surface() {
        let xml_document = b"
            <con:WindowSurface gml:id=\"GML_d0f329f3-5b05-428d-87c3-945b3868337f\">
              <gml:name>Window West</gml:name>
              <lod3MultiSurface>
                <gml:MultiSurface>
                  <gml:surfaceMember>
                    <gml:Polygon gml:id=\"PolyID58821_1939_612838_272028\">
                      <gml:exterior>
                        <gml:LinearRing gml:id=\"PolyID58821_1939_612838_272028_0\">
                          <gml:pos>457843.79 5439083.12 112.8</gml:pos>
                          <gml:pos>457845.79 5439083.12 112.8</gml:pos>
                          <gml:pos>457845.79 5439083.12 114.0</gml:pos>
                          <gml:pos>457843.79 5439083.12 114.0</gml:pos>
                          <gml:pos>457843.79 5439083.12 112.8</gml:pos>
                        </gml:LinearRing>
                      </gml:exterior>
                    </gml:Polygon>
                  </gml:surfaceMember>
                </gml:MultiSurface>
              </lod3MultiSurface>
            </con:WindowSurface>";

        let window_surface = deserialize_window_surface(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .unwrap();

        assert_eq!(
            window_surface.feature_id(),
            &Id::try_from("GML_d0f329f3-5b05-428d-87c3-945b3868337f").expect("should work")
        );
        assert_eq!(
            window_surface.names().first().unwrap(),
            &Code::new("Window West")
        );
        assert!(window_surface.lod3_multi_surface().is_some());
    }
}
