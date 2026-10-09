use crate::Error;
use crate::gml::codec::core::abstract_point_cloud_property::{
    deserialize_abstract_point_cloud_property, serialize_abstract_point_cloud_property,
};
use crate::gml::codec::core::{
    deserialize_abstract_space_boundary, deserialize_qualified_area_property,
    serialize_abstract_space_boundary, serialize_abstract_space_boundary_attributes,
    serialize_qualified_area_property,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
    collect_gml_child_lenient,
};
use ecitygml_core::model::core::{
    AbstractThematicSurface, AsAbstractSpaceBoundary, AsAbstractThematicSurface,
    AsAbstractThematicSurfaceMut,
};
use egml::io::codec::geometry::aggregates::{
    deserialize_multi_curve_property, deserialize_multi_surface_property,
    serialize_multi_curve_property, serialize_multi_surface_property,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter, collect_child};

pub fn deserialize_abstract_thematic_surface(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractThematicSurface, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_thematic_surface received a truncated index — caller must scan to sufficient depth"
    );

    let mut abstract_space_boundary_result = None;
    let mut lod0_multi_surface_result = None;
    let mut lod1_multi_surface_result = None;
    let mut lod2_multi_surface_result = None;
    let mut lod3_multi_surface_result = None;
    let mut lod0_multi_curve_result = None;
    let mut point_cloud_result = None;

    rayon::scope(|s| {
        s.spawn(|_| {
            abstract_space_boundary_result = Some(deserialize_abstract_space_boundary(
                xml_document,
                index,
                config,
            ));
        });
        s.spawn(|_| {
            lod0_multi_surface_result = Some(collect_gml_child_lenient(
                xml_document,
                index,
                CityGmlElement::Lod0MultiSurfaceProperty.into(),
                config.gml_config(),
                deserialize_multi_surface_property,
            ));
        });
        s.spawn(|_| {
            lod1_multi_surface_result = Some(collect_gml_child_lenient(
                xml_document,
                index,
                CityGmlElement::Lod1MultiSurfaceProperty.into(),
                config.gml_config(),
                deserialize_multi_surface_property,
            ));
        });
        s.spawn(|_| {
            lod2_multi_surface_result = Some(collect_gml_child_lenient(
                xml_document,
                index,
                CityGmlElement::Lod2MultiSurfaceProperty.into(),
                config.gml_config(),
                deserialize_multi_surface_property,
            ));
        });
        s.spawn(|_| {
            lod3_multi_surface_result = Some(collect_gml_child_lenient(
                xml_document,
                index,
                CityGmlElement::Lod3MultiSurfaceProperty.into(),
                config.gml_config(),
                deserialize_multi_surface_property,
            ));
        });
        s.spawn(|_| {
            lod0_multi_curve_result = Some(collect_gml_child_lenient(
                xml_document,
                index,
                CityGmlElement::Lod0MultiCurveProperty.into(),
                config.gml_config(),
                deserialize_multi_curve_property,
            ));
        });
        s.spawn(|_| {
            point_cloud_result = Some(collect_child(
                xml_document,
                index,
                CityGmlElement::AbstractPointCloudProperty.into(),
                config,
                deserialize_abstract_point_cloud_property,
            ));
        });
    });

    let mut abstract_thematic_surface = AbstractThematicSurface::from_abstract_space_boundary(
        abstract_space_boundary_result.expect("rayon::scope guarantees all spawns complete")?,
    );
    let areas = index
        .get(CityGmlElement::AreaProperty.into())
        .iter()
        .map(|x| deserialize_qualified_area_property(&xml_document[x.range()]))
        .collect::<Result<_, _>>()?;
    abstract_thematic_surface.set_areas(areas);
    abstract_thematic_surface.set_lod0_multi_surface(
        lod0_multi_surface_result.expect("rayon::scope guarantees all spawns complete"),
    );
    abstract_thematic_surface.set_lod1_multi_surface(
        lod1_multi_surface_result.expect("rayon::scope guarantees all spawns complete"),
    );
    abstract_thematic_surface.set_lod2_multi_surface(
        lod2_multi_surface_result.expect("rayon::scope guarantees all spawns complete"),
    );
    abstract_thematic_surface.set_lod3_multi_surface(
        lod3_multi_surface_result.expect("rayon::scope guarantees all spawns complete"),
    );
    abstract_thematic_surface.set_lod0_multi_curve(
        lod0_multi_curve_result.expect("rayon::scope guarantees all spawns complete"),
    );
    abstract_thematic_surface
        .set_point_cloud(point_cloud_result.expect("rayon::scope guarantees all spawns complete")?);

    Ok(abstract_thematic_surface)
}

pub fn serialize_abstract_thematic_surface(
    abstract_thematic_surface: &AbstractThematicSurface,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_space_boundary(
        abstract_thematic_surface.abstract_space_boundary(),
        xml_fragment_writer,
    )?;

    for area in abstract_thematic_surface.areas() {
        serialize_qualified_area_property(
            area,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::AreaProperty,
        )?;
    }

    if let Some(prop) = abstract_thematic_surface.lod0_multi_surface() {
        serialize_multi_surface_property(
            prop,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::Lod0MultiSurfaceProperty,
        )?;
    }
    if let Some(prop) = abstract_thematic_surface.lod1_multi_surface() {
        serialize_multi_surface_property(
            prop,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::Lod1MultiSurfaceProperty,
        )?;
    }
    if let Some(prop) = abstract_thematic_surface.lod2_multi_surface() {
        serialize_multi_surface_property(
            prop,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::Lod2MultiSurfaceProperty,
        )?;
    }
    if let Some(prop) = abstract_thematic_surface.lod3_multi_surface() {
        serialize_multi_surface_property(
            prop,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::Lod3MultiSurfaceProperty,
        )?;
    }
    if let Some(prop) = abstract_thematic_surface.lod0_multi_curve() {
        serialize_multi_curve_property(
            prop,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::Lod0MultiCurveProperty,
        )?;
    }

    if let Some(prop) = abstract_thematic_surface.point_cloud() {
        serialize_abstract_point_cloud_property(prop, xml_fragment_writer)?;
    }

    Ok(())
}

pub fn serialize_abstract_thematic_surface_attributes(
    abstract_thematic_surface: &AbstractThematicSurface,
) -> Vec<(String, String)> {
    serialize_abstract_space_boundary_attributes(
        abstract_thematic_surface.abstract_space_boundary(),
    )
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::core::{
        AsAbstractCityObject, AsAbstractFeature, AsAbstractThematicSurface,
    };
    use egml::io::util::{Formatting, XmlFragmentWriter};
    use egml::model::base::Id;

    #[test]
    fn test_deserialize_with_lod2_multi_surface() {
        let xml_document = b"\
<con:WallSurface gml:id=\"test-id-123\">
  <gml:name>Outer Wall 1 (West)</gml:name>
  <lod2MultiSurface>
    <gml:MultiSurface>
      <gml:surfaceMember>
        <gml:Polygon gml:id=\"PolyID7350_878_759628_120742\">
          <gml:exterior>
            <gml:LinearRing gml:id=\"PolyID7350_878_759628_120742_0\">
              <gml:pos>457842.0 5439088.0 118.317691453624</gml:pos>
              <gml:pos>457842.0 5439093.0 115.430940107676</gml:pos>
              <gml:pos>457842.0 5439093.0 111.8</gml:pos>
              <gml:pos>457842.0 5439083.0 111.8</gml:pos>
              <gml:pos>457842.0 5439083.0 115.430940107676</gml:pos>
              <gml:pos>457842.0 5439088.0 118.317691453624</gml:pos>
            </gml:LinearRing>
          </gml:exterior>
        </gml:Polygon>
      </gml:surfaceMember>
    </gml:MultiSurface>
  </lod2MultiSurface>
</con:WallSurface>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_thematic_surface = deserialize_abstract_thematic_surface(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            abstract_thematic_surface.feature_id(),
            &Id::try_from("test-id-123").expect("should work")
        );
        assert!(abstract_thematic_surface.lod2_multi_surface().is_some());
        assert_eq!(abstract_thematic_surface.generic_attributes().len(), 0);
    }

    #[test]
    fn test_deserialize_abstract_thematic_surface_with_area() {
        let xml_document = b"\
<con:WallSurface gml:id=\"test-id-123\">
  <area>
    <QualifiedArea>
      <area uom=\"m2\">5.0</area>
      <typeOfArea>RoadArea</typeOfArea>
    </QualifiedArea>
  </area>
</con:WallSurface>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_thematic_surface = deserialize_abstract_thematic_surface(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(abstract_thematic_surface.areas().len(), 1);

        let area = &abstract_thematic_surface.areas()[0];
        assert_eq!(area.area().value(), 5.0);
        assert_eq!(area.area().uom(), "m2");
        assert_eq!(area.type_of_area().code().value(), "RoadArea");
    }

    #[test]
    fn test_serialize_abstract_thematic_surface_with_area() {
        let xml_document = b"\
<con:WallSurface gml:id=\"test-id-123\">
  <area>
    <QualifiedArea>
      <area uom=\"m2\">5.0</area>
      <typeOfArea>WallAreaMeasured</typeOfArea>
    </QualifiedArea>
  </area>
</con:WallSurface>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_thematic_surface = deserialize_abstract_thematic_surface(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        xml_fragment_writer
            .write_start_event(CityGmlNamespace::Construction, CityGmlElement::WallSurface)
            .expect("should work");
        serialize_abstract_thematic_surface(&abstract_thematic_surface, &mut xml_fragment_writer)
            .expect("should serialize");
        xml_fragment_writer
            .write_end_event(CityGmlNamespace::Construction, CityGmlElement::WallSurface)
            .expect("should work");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("<area>") || xml.contains("<area "));
        assert!(xml.contains("QualifiedArea"));
        assert!(xml.contains("uom=\"m2\""));
        assert!(xml.contains('5'));
        assert!(xml.contains("typeOfArea"));
        assert!(xml.contains("WallAreaMeasured"));
    }

    #[test]
    fn test_round_trip_abstract_thematic_surface_with_area() {
        let xml_document = b"\
<con:WallSurface gml:id=\"test-id-123\">
  <area>
    <QualifiedArea>
      <area uom=\"m2\">5.0</area>
      <typeOfArea>WallAreaMeasured</typeOfArea>
    </QualifiedArea>
  </area>
</con:WallSurface>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_thematic_surface = deserialize_abstract_thematic_surface(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        xml_fragment_writer
            .write_start_event(CityGmlNamespace::Construction, CityGmlElement::WallSurface)
            .expect("should work");
        serialize_abstract_thematic_surface(&abstract_thematic_surface, &mut xml_fragment_writer)
            .expect("should serialize");
        xml_fragment_writer
            .write_end_event(CityGmlNamespace::Construction, CityGmlElement::WallSurface)
            .expect("should work");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        let round_tripped_index =
            XmlDocumentIndex::from_scan(xml.as_bytes(), None).expect("should work");
        let round_tripped = deserialize_abstract_thematic_surface(
            xml.as_bytes(),
            &round_tripped_index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(abstract_thematic_surface.areas(), round_tripped.areas());
    }
}
