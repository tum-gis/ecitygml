use crate::Error;
use crate::gml::codec::construction::abstract_construction_surface::{
    deserialize_abstract_construction_surface, serialize_abstract_construction_surface,
    serialize_abstract_construction_surface_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::construction::{AsAbstractConstructionSurface, WallSurface};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_wall_surface(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<WallSurface, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_construction_surface =
        deserialize_abstract_construction_surface(xml_document, index, config)?;
    let wall_surface =
        WallSurface::from_abstract_construction_surface(abstract_construction_surface);

    Ok(wall_surface)
}

pub fn serialize_wall_surface(
    wall_surface: &WallSurface,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_wall_surface_attributes(wall_surface);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Construction,
        CityGmlElement::WallSurface,
        attributes,
    )?;

    serialize_abstract_construction_surface(
        wall_surface.abstract_construction_surface(),
        xml_fragment_writer,
    )?;

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::Construction, CityGmlElement::WallSurface)?;

    Ok(())
}

pub fn serialize_wall_surface_attributes(wall_surface: &WallSurface) -> Vec<(String, String)> {
    serialize_abstract_construction_surface_attributes(wall_surface.abstract_construction_surface())
}

#[cfg(test)]
mod tests {
    use super::*;

    use ecitygml_core::model::construction::{
        AbstractFillingSurfaceKind, AsAbstractConstructionSurface, DoorSurface, WindowSurface,
    };
    use ecitygml_core::model::core::{
        AsAbstractCityObject, AsAbstractFeature, AsAbstractThematicSurface,
    };
    use egml::model::base::Id;

    #[test]
    fn test_deserialize_basic_abstract_thematic_surface() {
        let xml_document = b"
<con:WallSurface gml:id=\"GML_d38cf762-c29d-4491-88c9-bdc89e141978\">
          <gml:name>Outer Wall 2 (South)</gml:name>
          <lod3MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:CompositeSurface gml:id=\"GML_4726d5c0-dfa2-4777-b1da-24798d72c27a\">
                  <gml:surfaceMember>
                    <gml:Polygon gml:id=\"PolyID58807_717_125437_84247\">
                      <gml:exterior>
                        <gml:LinearRing gml:id=\"PolyID58807_717_125437_84247_0\">
                          <gml:pos>457849.005 5439083.0 114.375</gml:pos>
                          <gml:pos>457849.005 5439083.2 114.375</gml:pos>
                          <gml:pos>457849.005 5439083.2 112.0</gml:pos>
                          <gml:pos>457849.005 5439083.0 112.0</gml:pos>
                          <gml:pos>457849.005 5439083.0 114.375</gml:pos>
                        </gml:LinearRing>
                      </gml:exterior>
                    </gml:Polygon>
                  </gml:surfaceMember>
                  <gml:surfaceMember>
                    <gml:Polygon gml:id=\"PolyID58808_349_692294_125678\">
                      <gml:exterior>
                        <gml:LinearRing gml:id=\"PolyID58808_349_692294_125678_0\">
                          <gml:pos>457852.21 5439083.0 114.0</gml:pos>
                          <gml:pos>457852.21 5439083.12 114.0</gml:pos>
                          <gml:pos>457852.21 5439083.12 112.8</gml:pos>
                          <gml:pos>457852.21 5439083.0 112.8</gml:pos>
                          <gml:pos>457852.21 5439083.0 114.0</gml:pos>
                        </gml:LinearRing>
                      </gml:exterior>
                    </gml:Polygon>
                  </gml:surfaceMember>
                  <gml:surfaceMember>
                    <gml:Polygon gml:id=\"PolyID58809_472_527501_416856\">
                      <gml:exterior>
                        <gml:LinearRing gml:id=\"PolyID58809_472_527501_416856_0\">
                          <gml:pos>457845.79 5439083.0 114.0</gml:pos>
                          <gml:pos>457845.79 5439083.12 114.0</gml:pos>
                          <gml:pos>457845.79 5439083.12 112.8</gml:pos>
                          <gml:pos>457845.79 5439083.0 112.8</gml:pos>
                          <gml:pos>457845.79 5439083.0 114.0</gml:pos>
                        </gml:LinearRing>
                      </gml:exterior>
                    </gml:Polygon>
                  </gml:surfaceMember>
                  <gml:surfaceMember>
                    <gml:Polygon gml:id=\"PolyID58810_1807_553097_148846\">
                      <gml:exterior>
                        <gml:LinearRing gml:id=\"PolyID58810_1807_553097_148846_0\">
                          <gml:pos>457845.79 5439083.0 112.8</gml:pos>
                          <gml:pos>457845.79 5439083.12 112.8</gml:pos>
                          <gml:pos>457843.79 5439083.12 112.8</gml:pos>
                          <gml:pos>457843.79 5439083.0 112.8</gml:pos>
                          <gml:pos>457845.79 5439083.0 112.8</gml:pos>
                        </gml:LinearRing>
                      </gml:exterior>
                    </gml:Polygon>
                  </gml:surfaceMember>
                  <gml:surfaceMember>
                    <gml:Polygon gml:id=\"PolyID58811_1622_73903_56220\">
                      <gml:exterior>
                        <gml:LinearRing gml:id=\"PolyID58811_1622_73903_56220_0\">
                          <gml:pos>457846.995 5439083.0 114.375</gml:pos>
                          <gml:pos>457846.995 5439083.2 114.375</gml:pos>
                          <gml:pos>457849.005 5439083.2 114.375</gml:pos>
                          <gml:pos>457849.005 5439083.0 114.375</gml:pos>
                          <gml:pos>457846.995 5439083.0 114.375</gml:pos>
                        </gml:LinearRing>
                      </gml:exterior>
                    </gml:Polygon>
                  </gml:surfaceMember>
                  <gml:surfaceMember>
                    <gml:Polygon gml:id=\"PolyID58812_795_350114_216214\">
                      <gml:exterior>
                        <gml:LinearRing gml:id=\"PolyID58812_795_350114_216214_0\">
                          <gml:pos>457843.79 5439083.0 112.8</gml:pos>
                          <gml:pos>457843.79 5439083.12 112.8</gml:pos>
                          <gml:pos>457843.79 5439083.12 114.0</gml:pos>
                          <gml:pos>457843.79 5439083.0 114.0</gml:pos>
                          <gml:pos>457843.79 5439083.0 112.8</gml:pos>
                        </gml:LinearRing>
                      </gml:exterior>
                    </gml:Polygon>
                  </gml:surfaceMember>
                  <gml:surfaceMember>
                    <gml:Polygon gml:id=\"PolyID58813_1099_461650_222485\">
                      <gml:exterior>
                        <gml:LinearRing gml:id=\"PolyID58813_1099_461650_222485_0\">
                          <gml:pos>457846.995 5439083.0 112.0</gml:pos>
                          <gml:pos>457846.995 5439083.2 112.0</gml:pos>
                          <gml:pos>457846.995 5439083.2 114.375</gml:pos>
                          <gml:pos>457846.995 5439083.0 114.375</gml:pos>
                          <gml:pos>457846.995 5439083.0 112.0</gml:pos>
                        </gml:LinearRing>
                      </gml:exterior>
                    </gml:Polygon>
                  </gml:surfaceMember>
                  <gml:surfaceMember>
                    <gml:Polygon gml:id=\"PolyID58814_1459_649731_52436\">
                      <gml:exterior>
                        <gml:LinearRing gml:id=\"PolyID58814_1459_649731_52436_0\">
                          <gml:pos>457850.21 5439083.0 114.0</gml:pos>
                          <gml:pos>457850.21 5439083.12 114.0</gml:pos>
                          <gml:pos>457852.21 5439083.12 114.0</gml:pos>
                          <gml:pos>457852.21 5439083.0 114.0</gml:pos>
                          <gml:pos>457850.21 5439083.0 114.0</gml:pos>
                        </gml:LinearRing>
                      </gml:exterior>
                    </gml:Polygon>
                  </gml:surfaceMember>
                  <gml:surfaceMember>
                    <gml:Polygon gml:id=\"PolyID58815_691_101880_418020\">
                      <gml:exterior>
                        <gml:LinearRing gml:id=\"PolyID58815_691_101880_418020_0\">
                          <gml:pos>457850.21 5439083.0 112.8</gml:pos>
                          <gml:pos>457850.21 5439083.12 112.8</gml:pos>
                          <gml:pos>457850.21 5439083.12 114.0</gml:pos>
                          <gml:pos>457850.21 5439083.0 114.0</gml:pos>
                          <gml:pos>457850.21 5439083.0 112.8</gml:pos>
                        </gml:LinearRing>
                      </gml:exterior>
                    </gml:Polygon>
                  </gml:surfaceMember>
                  <gml:surfaceMember>
                    <gml:Polygon gml:id=\"PolyID58816_858_312337_86583\">
                      <gml:exterior>
                        <gml:LinearRing gml:id=\"PolyID58816_858_312337_86583_0\">
                          <gml:pos>457846.995 5439083.0 112.0</gml:pos>
                          <gml:pos>457849.005 5439083.0 112.0</gml:pos>
                          <gml:pos>457849.005 5439083.2 112.0</gml:pos>
                          <gml:pos>457846.995 5439083.2 112.0</gml:pos>
                          <gml:pos>457846.995 5439083.0 112.0</gml:pos>
                        </gml:LinearRing>
                      </gml:exterior>
                    </gml:Polygon>
                  </gml:surfaceMember>
                  <gml:surfaceMember>
                    <gml:Polygon gml:id=\"PolyID58817_701_101369_361161\">
                      <gml:exterior>
                        <gml:LinearRing gml:id=\"PolyID58817_701_101369_361161_0\">
                          <gml:pos>457852.21 5439083.0 112.8</gml:pos>
                          <gml:pos>457852.21 5439083.12 112.8</gml:pos>
                          <gml:pos>457850.21 5439083.12 112.8</gml:pos>
                          <gml:pos>457850.21 5439083.0 112.8</gml:pos>
                          <gml:pos>457852.21 5439083.0 112.8</gml:pos>
                        </gml:LinearRing>
                      </gml:exterior>
                    </gml:Polygon>
                  </gml:surfaceMember>
                  <gml:surfaceMember>
                    <gml:Polygon gml:id=\"PolyID58818_1640_464682_59215\">
                      <gml:exterior>
                        <gml:LinearRing gml:id=\"PolyID58818_1640_464682_59215_0\">
                          <gml:pos>457843.79 5439083.0 114.0</gml:pos>
                          <gml:pos>457843.79 5439083.12 114.0</gml:pos>
                          <gml:pos>457845.79 5439083.12 114.0</gml:pos>
                          <gml:pos>457845.79 5439083.0 114.0</gml:pos>
                          <gml:pos>457843.79 5439083.0 114.0</gml:pos>
                        </gml:LinearRing>
                      </gml:exterior>
                    </gml:Polygon>
                  </gml:surfaceMember>
                  <gml:surfaceMember>
                    <gml:Polygon gml:id=\"PolyID58819_65_364244_211813\">
                      <gml:exterior>
                        <gml:LinearRing gml:id=\"PolyID58819_65_364244_211813_0\">
                          <gml:pos>457854.0 5439083.0 115.430940107676</gml:pos>
                          <gml:pos>457842.0 5439083.0 115.430940107676</gml:pos>
                          <gml:pos>457842.0 5439083.0 111.8</gml:pos>
                          <gml:pos>457854.0 5439083.0 111.8</gml:pos>
                          <gml:pos>457854.0 5439083.0 115.430940107676</gml:pos>
                        </gml:LinearRing>
                      </gml:exterior>
                      <gml:interior>
                        <gml:LinearRing gml:id=\"PolyID58819_65_364244_211813_1\">
                          <gml:pos>457849.005 5439083.0 114.375</gml:pos>
                          <gml:pos>457849.005 5439083.0 112.0</gml:pos>
                          <gml:pos>457846.995 5439083.0 112.0</gml:pos>
                          <gml:pos>457846.995 5439083.0 114.375</gml:pos>
                          <gml:pos>457849.005 5439083.0 114.375</gml:pos>
                        </gml:LinearRing>
                      </gml:interior>
                      <gml:interior>
                        <gml:LinearRing gml:id=\"PolyID58819_65_364244_211813_2\">
                          <gml:pos>457850.21 5439083.0 114.0</gml:pos>
                          <gml:pos>457852.21 5439083.0 114.0</gml:pos>
                          <gml:pos>457852.21 5439083.0 112.8</gml:pos>
                          <gml:pos>457850.21 5439083.0 112.8</gml:pos>
                          <gml:pos>457850.21 5439083.0 114.0</gml:pos>
                        </gml:LinearRing>
                      </gml:interior>
                      <gml:interior>
                        <gml:LinearRing gml:id=\"PolyID58819_65_364244_211813_3\">
                          <gml:pos>457845.79 5439083.0 112.8</gml:pos>
                          <gml:pos>457843.79 5439083.0 112.8</gml:pos>
                          <gml:pos>457843.79 5439083.0 114.0</gml:pos>
                          <gml:pos>457845.79 5439083.0 114.0</gml:pos>
                          <gml:pos>457845.79 5439083.0 112.8</gml:pos>
                        </gml:LinearRing>
                      </gml:interior>
                    </gml:Polygon>
                  </gml:surfaceMember>
                </gml:CompositeSurface>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </lod3MultiSurface>
          <con:fillingSurface>
            <con:WindowSurface gml:id=\"GML_98d9c4f5-9e47-4f0b-95f3-cf31e7520142\">
              <gml:name>Window East</gml:name>
              <lod3MultiSurface>
                <gml:MultiSurface>
                  <gml:surfaceMember>
                    <gml:Polygon gml:id=\"PolyID58820_1568_227087_210505\">
                      <gml:exterior>
                        <gml:LinearRing gml:id=\"PolyID58820_1568_227087_210505_0\">
                          <gml:pos>457852.21 5439083.12 112.8</gml:pos>
                          <gml:pos>457852.21 5439083.12 114.0</gml:pos>
                          <gml:pos>457850.21 5439083.12 114.0</gml:pos>
                          <gml:pos>457850.21 5439083.12 112.8</gml:pos>
                          <gml:pos>457852.21 5439083.12 112.8</gml:pos>
                        </gml:LinearRing>
                      </gml:exterior>
                    </gml:Polygon>
                  </gml:surfaceMember>
                </gml:MultiSurface>
              </lod3MultiSurface>
            </con:WindowSurface>
          </con:fillingSurface>
          <con:fillingSurface>
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
            </con:WindowSurface>
          </con:fillingSurface>
          <con:fillingSurface>
            <con:DoorSurface gml:id=\"GML_2d6ddf04-ee56-42a1-a9b1-b47e4181a629\">
              <gml:name>Door South</gml:name>
              <lod3MultiSurface>
                <gml:MultiSurface>
                  <gml:surfaceMember>
                    <gml:Polygon gml:id=\"PolyID58822_551_84845_215911\">
                      <gml:exterior>
                        <gml:LinearRing gml:id=\"PolyID58822_551_84845_215911_0\">
                          <gml:pos>457849.005 5439083.2 112.0</gml:pos>
                          <gml:pos>457849.005 5439083.2 114.375</gml:pos>
                          <gml:pos>457846.995 5439083.2 114.375</gml:pos>
                          <gml:pos>457846.995 5439083.2 112.0</gml:pos>
                          <gml:pos>457849.005 5439083.2 112.0</gml:pos>
                        </gml:LinearRing>
                      </gml:exterior>
                    </gml:Polygon>
                  </gml:surfaceMember>
                </gml:MultiSurface>
              </lod3MultiSurface>
            </con:DoorSurface>
          </con:fillingSurface>
        </con:WallSurface>";

        let wall_surface = deserialize_wall_surface(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            wall_surface.feature_id(),
            &Id::try_from("GML_d38cf762-c29d-4491-88c9-bdc89e141978").expect("should work")
        );
        assert!(wall_surface.lod3_multi_surface().is_some());
        assert_eq!(wall_surface.generic_attributes().len(), 0);
        let window_surfaces: Vec<&WindowSurface> = wall_surface
            .filling_surfaces()
            .iter()
            .flat_map(|x| x.object())
            .filter_map(|x| match x {
                AbstractFillingSurfaceKind::WindowSurface(x) => Some(x),
                _ => None,
            })
            .collect();
        assert_eq!(window_surfaces.len(), 2);

        let door_surfaces: Vec<&DoorSurface> = wall_surface
            .filling_surfaces()
            .iter()
            .flat_map(|x| x.object())
            .filter_map(|x| match x {
                AbstractFillingSurfaceKind::DoorSurface(x) => Some(x),
                _ => None,
            })
            .collect();
        assert_eq!(door_surfaces.len(), 1);
    }
}
