use crate::error::Error;
use crate::gml::codec::core::abstract_space_boundary_property::{
    deserialize_abstract_space_boundary_property, serialize_abstract_space_boundary_property,
};
use crate::gml::codec::core::enums::{deserialize_space_type, serialize_space_type};
use crate::gml::codec::core::{
    deserialize_abstract_city_object, deserialize_qualified_area_property,
    deserialize_qualified_volume_property, serialize_abstract_city_object,
    serialize_abstract_city_object_attributes, serialize_qualified_area_property,
    serialize_qualified_volume_property,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
    collect_gml_child_lenient,
};
use ecitygml_core::model::core::{
    AbstractSpace, AsAbstractCityObject, AsAbstractSpace, AsAbstractSpaceMut,
};
use egml::io::codec::geometry::aggregates::{
    deserialize_multi_curve_property, deserialize_multi_surface_property,
    serialize_multi_curve_property, serialize_multi_surface_property,
};
use egml::io::codec::geometry::primitives::{
    deserialize_point_property, deserialize_solid_property, serialize_point_property,
    serialize_solid_property,
};
use egml::io::util::{ChunkedSink, collect_children};
use egml::io::util::{XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_space(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractSpace, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_space received a truncated index — caller must scan to sufficient depth"
    );

    let mut abstract_city_object_result = None;
    let mut space_boundaries_result = None;
    let mut lod1_solid_result = None;
    let mut lod2_solid_result = None;
    let mut lod3_solid_result = None;
    let mut lod0_multi_surface_result = None;
    let mut lod2_multi_surface_result = None;
    let mut lod3_multi_surface_result = None;
    let mut lod0_multi_curve_result = None;
    let mut lod2_multi_curve_result = None;
    let mut lod3_multi_curve_result = None;
    let mut lod0_point_result = None;

    rayon::scope(|s| {
        s.spawn(|_| {
            abstract_city_object_result = Some(deserialize_abstract_city_object(
                xml_document,
                index,
                config,
            ));
        });
        s.spawn(|_| {
            space_boundaries_result = Some(collect_children(
                xml_document,
                index,
                CityGmlElement::BoundaryProperty.into(),
                config,
                deserialize_abstract_space_boundary_property,
            ));
        });
        s.spawn(|_| {
            lod1_solid_result = Some(collect_gml_child_lenient(
                xml_document,
                index,
                CityGmlElement::Lod1SolidProperty.into(),
                config.gml_config(),
                deserialize_solid_property,
            ));
        });
        s.spawn(|_| {
            lod2_solid_result = Some(collect_gml_child_lenient(
                xml_document,
                index,
                CityGmlElement::Lod2SolidProperty.into(),
                config.gml_config(),
                deserialize_solid_property,
            ));
        });
        s.spawn(|_| {
            lod3_solid_result = Some(collect_gml_child_lenient(
                xml_document,
                index,
                CityGmlElement::Lod3SolidProperty.into(),
                config.gml_config(),
                deserialize_solid_property,
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
            lod2_multi_curve_result = Some(collect_gml_child_lenient(
                xml_document,
                index,
                CityGmlElement::Lod2MultiCurveProperty.into(),
                config.gml_config(),
                deserialize_multi_curve_property,
            ));
        });
        s.spawn(|_| {
            lod3_multi_curve_result = Some(collect_gml_child_lenient(
                xml_document,
                index,
                CityGmlElement::Lod3MultiCurveProperty.into(),
                config.gml_config(),
                deserialize_multi_curve_property,
            ));
        });
        s.spawn(|_| {
            lod0_point_result = Some(collect_gml_child_lenient(
                xml_document,
                index,
                CityGmlElement::Lod0PointProperty.into(),
                config.gml_config(),
                deserialize_point_property,
            ));
        });
    });

    let mut abstract_space = AbstractSpace::from_abstract_city_object(
        abstract_city_object_result.expect("rayon::scope guarantees all spawns complete")?,
    );

    let space_type = index
        .first(CityGmlElement::SpaceTypeProperty.into())
        .map(|x| deserialize_space_type(&xml_document[x.range()]))
        .transpose()?;
    abstract_space.set_space_type_opt(space_type);

    let volumes = index
        .get(CityGmlElement::VolumeProperty.into())
        .iter()
        .map(|x| deserialize_qualified_volume_property(&xml_document[x.range()]))
        .collect::<Result<_, _>>()?;
    abstract_space.set_volumes(volumes);

    let areas = index
        .get(CityGmlElement::AreaProperty.into())
        .iter()
        .map(|x| deserialize_qualified_area_property(&xml_document[x.range()]))
        .collect::<Result<_, _>>()?;
    abstract_space.set_areas(areas);

    abstract_space
        .set_lod1_solid(lod1_solid_result.expect("rayon::scope guarantees all spawns complete"));
    abstract_space
        .set_lod2_solid(lod2_solid_result.expect("rayon::scope guarantees all spawns complete"));
    abstract_space
        .set_lod3_solid(lod3_solid_result.expect("rayon::scope guarantees all spawns complete"));
    abstract_space.set_lod0_multi_surface(
        lod0_multi_surface_result.expect("rayon::scope guarantees all spawns complete"),
    );
    abstract_space.set_lod2_multi_surface(
        lod2_multi_surface_result.expect("rayon::scope guarantees all spawns complete"),
    );
    abstract_space.set_lod3_multi_surface(
        lod3_multi_surface_result.expect("rayon::scope guarantees all spawns complete"),
    );
    abstract_space.set_lod0_multi_curve(
        lod0_multi_curve_result.expect("rayon::scope guarantees all spawns complete"),
    );
    abstract_space.set_lod2_multi_curve(
        lod2_multi_curve_result.expect("rayon::scope guarantees all spawns complete"),
    );
    abstract_space.set_lod3_multi_curve(
        lod3_multi_curve_result.expect("rayon::scope guarantees all spawns complete"),
    );
    abstract_space
        .set_lod0_point(lod0_point_result.expect("rayon::scope guarantees all spawns complete"));
    abstract_space.set_boundaries(
        space_boundaries_result.expect("rayon::scope guarantees all spawns complete")?,
    );

    Ok(abstract_space)
}

pub fn serialize_abstract_space(
    abstract_space: &AbstractSpace,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_city_object(abstract_space.abstract_city_object(), xml_fragment_writer)?;

    if let Some(space_type) = abstract_space.space_type() {
        serialize_space_type(
            space_type,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::SpaceTypeProperty,
        )?;
    }

    for volume in abstract_space.volumes() {
        serialize_qualified_volume_property(
            volume,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::VolumeProperty,
        )?;
    }

    for area in abstract_space.areas() {
        serialize_qualified_area_property(
            area,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::AreaProperty,
        )?;
    }

    if let Some(prop) = abstract_space.lod1_solid() {
        serialize_solid_property(
            prop,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::Lod1SolidProperty,
        )?;
    }
    if let Some(prop) = abstract_space.lod2_solid() {
        serialize_solid_property(
            prop,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::Lod2SolidProperty,
        )?;
    }
    if let Some(prop) = abstract_space.lod3_solid() {
        serialize_solid_property(
            prop,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::Lod3SolidProperty,
        )?;
    }
    if let Some(prop) = abstract_space.lod0_multi_surface() {
        serialize_multi_surface_property(
            prop,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::Lod0MultiSurfaceProperty,
        )?;
    }
    if let Some(prop) = abstract_space.lod2_multi_surface() {
        serialize_multi_surface_property(
            prop,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::Lod2MultiSurfaceProperty,
        )?;
    }
    if let Some(prop) = abstract_space.lod3_multi_surface() {
        serialize_multi_surface_property(
            prop,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::Lod3MultiSurfaceProperty,
        )?;
    }
    if let Some(prop) = abstract_space.lod0_multi_curve() {
        serialize_multi_curve_property(
            prop,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::Lod0MultiCurveProperty,
        )?;
    }
    if let Some(prop) = abstract_space.lod2_multi_curve() {
        serialize_multi_curve_property(
            prop,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::Lod2MultiCurveProperty,
        )?;
    }
    if let Some(prop) = abstract_space.lod3_multi_curve() {
        serialize_multi_curve_property(
            prop,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::Lod3MultiCurveProperty,
        )?;
    }
    if let Some(prop) = abstract_space.lod0_point() {
        serialize_point_property(
            prop,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::Lod0PointProperty,
        )?;
    }

    for prop in abstract_space.boundaries() {
        serialize_abstract_space_boundary_property(prop, xml_fragment_writer)?;
    }

    Ok(())
}

pub fn serialize_abstract_space_attributes(
    abstract_space: &AbstractSpace,
) -> Vec<(String, String)> {
    serialize_abstract_city_object_attributes(abstract_space.abstract_city_object())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::core::AsAbstractSpace;
    use ecitygml_core::model::core::enums::SpaceType;
    use egml::io::util::{Formatting, XmlFragmentWriter};

    #[test]
    fn test_deserialize_abstract_space_with_solid_with_links() {
        let xml_document = b"\
    <bldg:Building gml:id=\"UUID_d281adfc-4901-0f52-540b-4cc1a9325f82\">
      <lod2Solid>
        <gml:Solid>
          <gml:exterior>
            <gml:Shell>
              <gml:surfaceMember xlink:href=\"#PolyID7350_878_759628_120742\"/>
              <gml:surfaceMember xlink:href=\"#PolyID7351_1722_416019_316876\"/>
              <gml:surfaceMember xlink:href=\"#PolyID7352_230_209861_355851\"/>
              <gml:surfaceMember xlink:href=\"#PolyID7353_166_774155_320806\"/>
              <gml:surfaceMember xlink:href=\"#PolyID7354_1362_450904_410226\"/>
              <gml:surfaceMember xlink:href=\"#PolyID7355_537_416207_260034\"/>
              <gml:surfaceMember xlink:href=\"#PolyID7356_612_880782_415367\"/>
            </gml:Shell>
          </gml:exterior>
        </gml:Solid>
      </lod2Solid>
    </bldg:Building>
";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_space =
            deserialize_abstract_space(xml_document, &index, &DeserializationConfig::default())
                .expect("should work");

        assert!(abstract_space.lod1_solid().is_none());
        assert!(abstract_space.lod2_solid().is_some());
        assert!(abstract_space.lod3_solid().is_none());

        let lod2_solid = abstract_space.lod2_solid().expect("should work");
        let exterior_shell = lod2_solid.object().unwrap().exterior().unwrap();
        assert_eq!(exterior_shell.members().len(), 7);
    }

    #[test]
    fn test_deserialize_basic_abstract_space() {
        let xml_document = b"\
<tran:TrafficSpace gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
              <genericAttribute>
                <gen:IntAttribute>
                  <gen:name>identifier_laneId</gen:name>
                  <gen:value>1</gen:value>
                </gen:IntAttribute>
              </genericAttribute>
              <genericAttribute>
                <gen:IntAttribute>
                  <gen:name>identifier_laneSectionId</gen:name>
                  <gen:value>0</gen:value>
                </gen:IntAttribute>
              </genericAttribute>
              <spaceType>open</spaceType>
              <lod2Solid>
                <gml:Solid>
                  <gml:exterior>
                    <gml:Shell>
                      <gml:surfaceMember>
                        <gml:Polygon>
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension=\"3\">-49.60668801898414 3.9012103934480056 0.05 -17.879382466595356 28.260563471585364 0.05 -15.44344715878162 25.087832916346485 0.45 -47.1707527111704 0.7284798382091271 0.45 -49.60668801898414 3.9012103934480056 0.05</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon>
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension=\"3\">-47.1707527111704 0.7284798382091271 4.95 -15.44344715878162 25.087832916346485 4.95 -17.879382466595356 28.260563471585364 4.55 -49.60668801898414 3.9012103934480056 4.55 -47.1707527111704 0.7284798382091271 4.95</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon>
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension=\"3\">-49.60668801898414 3.9012103934480056 4.55 -17.879382466595356 28.260563471585364 4.55 -17.879382466595356 28.260563471585364 0.05 -49.60668801898414 3.9012103934480056 0.05 -49.60668801898414 3.9012103934480056 4.55</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon>
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension=\"3\">-47.1707527111704 0.7284798382091271 0.45 -15.44344715878162 25.087832916346485 0.45 -15.44344715878162 25.087832916346485 4.95 -47.1707527111704 0.7284798382091271 4.95 -47.1707527111704 0.7284798382091271 0.45</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon>
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension=\"3\">-49.60668801898414 3.9012103934480056 0.05 -47.1707527111704 0.7284798382091271 0.45 -47.1707527111704 0.7284798382091271 4.95 -49.60668801898414 3.9012103934480056 4.55 -49.60668801898414 3.9012103934480056 0.05</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                      <gml:surfaceMember>
                        <gml:Polygon>
                          <gml:exterior>
                            <gml:LinearRing>
                              <gml:posList srsDimension=\"3\">-17.879382466595356 28.260563471585364 0.05 -17.879382466595356 28.260563471585364 4.55 -15.44344715878162 25.087832916346485 4.95 -15.44344715878162 25.087832916346485 0.45 -17.879382466595356 28.260563471585364 0.05</gml:posList>
                            </gml:LinearRing>
                          </gml:exterior>
                        </gml:Polygon>
                      </gml:surfaceMember>
                    </gml:Shell>
                  </gml:exterior>
                </gml:Solid>
              </lod2Solid>
              <lod2MultiCurve>
                <gml:MultiCurve>
                  <gml:curveMember>
                    <gml:LineString>
                      <gml:posList srsDimension=\"3\">-48.38872036507727 2.3148451158285663 0.25 -16.661414812688488 26.674198193965925 0.25</gml:posList>
                    </gml:LineString>
                  </gml:curveMember>
                </gml:MultiCurve>
              </lod2MultiCurve>
              <tran:function>1</tran:function>
              <tran:usage>2</tran:usage>
              <tran:granularity>lane</tran:granularity>
              <tran:trafficDirection>backwards</tran:trafficDirection>
            </tran:TrafficSpace>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_space =
            deserialize_abstract_space(xml_document, &index, &DeserializationConfig::default())
                .expect("should work");

        assert!(abstract_space.lod1_solid().is_none());
        assert!(abstract_space.lod2_solid().is_some());
        assert!(abstract_space.lod2_multi_curve().is_some());
        assert_eq!(abstract_space.space_type(), Some(SpaceType::Open));
    }

    #[test]
    fn test_deserialize_abstract_space_with_volume() {
        let xml_document = b"\
<tran:TrafficSpace gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <spaceType>open</spaceType>
    <volume>
        <QualifiedVolume>
            <volume uom=\"m3\">5.0</volume>
            <typeOfVolume>RoadVolume</typeOfVolume>
        </QualifiedVolume>
    </volume>
</tran:TrafficSpace>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_space =
            deserialize_abstract_space(xml_document, &index, &DeserializationConfig::default())
                .expect("should work");

        assert_eq!(abstract_space.space_type(), Some(SpaceType::Open));
        assert_eq!(abstract_space.volumes().len(), 1);

        let volume = &abstract_space.volumes()[0];
        assert_eq!(volume.volume().value(), 5.0);
        assert_eq!(volume.volume().uom(), "m3");
        assert_eq!(volume.type_of_volume().code().value(), "RoadVolume");
    }

    #[test]
    fn test_serialize_abstract_space_with_volume() {
        let xml_document = b"\
<tran:TrafficSpace gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <spaceType>open</spaceType>
    <volume>
        <QualifiedVolume>
            <volume uom=\"m3\">5.0</volume>
            <typeOfVolume>RoadVolume</typeOfVolume>
        </QualifiedVolume>
    </volume>
</tran:TrafficSpace>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_space =
            deserialize_abstract_space(xml_document, &index, &DeserializationConfig::default())
                .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        xml_fragment_writer
            .write_start_event(
                CityGmlNamespace::Transportation,
                CityGmlElement::TrafficSpace,
            )
            .expect("should work");
        serialize_abstract_space(&abstract_space, &mut xml_fragment_writer)
            .expect("should serialize");
        xml_fragment_writer
            .write_end_event(
                CityGmlNamespace::Transportation,
                CityGmlElement::TrafficSpace,
            )
            .expect("should work");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("<volume>") || xml.contains("<volume "));
        assert!(xml.contains("QualifiedVolume"));
        assert!(xml.contains("uom=\"m3\""));
        assert!(xml.contains('5'));
        assert!(xml.contains("typeOfVolume"));
        assert!(xml.contains("RoadVolume"));
    }

    #[test]
    fn test_round_trip_abstract_space_with_volume() {
        let xml_document = b"\
<tran:TrafficSpace gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <spaceType>open</spaceType>
    <volume>
        <QualifiedVolume>
            <volume uom=\"m3\">5.0</volume>
            <typeOfVolume>RoadVolume</typeOfVolume>
        </QualifiedVolume>
    </volume>
</tran:TrafficSpace>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_space =
            deserialize_abstract_space(xml_document, &index, &DeserializationConfig::default())
                .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        xml_fragment_writer
            .write_start_event(
                CityGmlNamespace::Transportation,
                CityGmlElement::TrafficSpace,
            )
            .expect("should work");
        serialize_abstract_space(&abstract_space, &mut xml_fragment_writer)
            .expect("should serialize");
        xml_fragment_writer
            .write_end_event(
                CityGmlNamespace::Transportation,
                CityGmlElement::TrafficSpace,
            )
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
        let round_tripped = deserialize_abstract_space(
            xml.as_bytes(),
            &round_tripped_index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(abstract_space.volumes(), round_tripped.volumes());
    }

    #[test]
    fn test_deserialize_abstract_space_with_area() {
        let xml_document = b"\
<tran:TrafficSpace gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <spaceType>open</spaceType>
    <area>
        <QualifiedArea>
            <area uom=\"m2\">5.0</area>
            <typeOfArea>RoadArea</typeOfArea>
        </QualifiedArea>
    </area>
</tran:TrafficSpace>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_space =
            deserialize_abstract_space(xml_document, &index, &DeserializationConfig::default())
                .expect("should work");

        assert_eq!(abstract_space.space_type(), Some(SpaceType::Open));
        assert_eq!(abstract_space.areas().len(), 1);

        let area = &abstract_space.areas()[0];
        assert_eq!(area.area().value(), 5.0);
        assert_eq!(area.area().uom(), "m2");
        assert_eq!(area.type_of_area().code().value(), "RoadArea");
    }

    #[test]
    fn test_serialize_abstract_space_with_area() {
        let xml_document = b"\
<tran:TrafficSpace gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <spaceType>open</spaceType>
    <area>
        <QualifiedArea>
            <area uom=\"m2\">5.0</area>
            <typeOfArea>RoadArea</typeOfArea>
        </QualifiedArea>
    </area>
</tran:TrafficSpace>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_space =
            deserialize_abstract_space(xml_document, &index, &DeserializationConfig::default())
                .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        xml_fragment_writer
            .write_start_event(
                CityGmlNamespace::Transportation,
                CityGmlElement::TrafficSpace,
            )
            .expect("should work");
        serialize_abstract_space(&abstract_space, &mut xml_fragment_writer)
            .expect("should serialize");
        xml_fragment_writer
            .write_end_event(
                CityGmlNamespace::Transportation,
                CityGmlElement::TrafficSpace,
            )
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
        assert!(xml.contains("RoadArea"));
    }

    #[test]
    fn test_round_trip_abstract_space_with_area() {
        let xml_document = b"\
<tran:TrafficSpace gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <spaceType>open</spaceType>
    <area>
        <QualifiedArea>
            <area uom=\"m2\">5.0</area>
            <typeOfArea>RoadArea</typeOfArea>
        </QualifiedArea>
    </area>
</tran:TrafficSpace>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_space =
            deserialize_abstract_space(xml_document, &index, &DeserializationConfig::default())
                .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        xml_fragment_writer
            .write_start_event(
                CityGmlNamespace::Transportation,
                CityGmlElement::TrafficSpace,
            )
            .expect("should work");
        serialize_abstract_space(&abstract_space, &mut xml_fragment_writer)
            .expect("should serialize");
        xml_fragment_writer
            .write_end_event(
                CityGmlNamespace::Transportation,
                CityGmlElement::TrafficSpace,
            )
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
        let round_tripped = deserialize_abstract_space(
            xml.as_bytes(),
            &round_tripped_index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(abstract_space.areas(), round_tripped.areas());
    }

    fn serialize_traffic_space(abstract_space: &AbstractSpace) -> String {
        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        xml_fragment_writer
            .write_start_event(
                CityGmlNamespace::Transportation,
                CityGmlElement::TrafficSpace,
            )
            .expect("should work");
        serialize_abstract_space(abstract_space, &mut xml_fragment_writer)
            .expect("should serialize");
        xml_fragment_writer
            .write_end_event(
                CityGmlNamespace::Transportation,
                CityGmlElement::TrafficSpace,
            )
            .expect("should work");
        let mut buf = Vec::new();
        xml_fragment_writer
            .write_to(&mut buf)
            .expect("should flush fragments");
        String::from_utf8(buf).expect("should convert to string")
    }

    #[test]
    fn test_deserialize_abstract_space_with_lod0_point() {
        let xml_document = b"\
<tran:TrafficSpace gml:id=\"TS_1\">
    <lod0Point>
        <gml:Point gml:id=\"P_1\">
            <gml:pos>1.0 2.0 3.0</gml:pos>
        </gml:Point>
    </lod0Point>
</tran:TrafficSpace>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_space =
            deserialize_abstract_space(xml_document, &index, &DeserializationConfig::default())
                .expect("should work");

        let point = abstract_space
            .lod0_point()
            .and_then(|property| property.object())
            .expect("should have a lod0 point");
        assert_eq!(
            (point.pos().x(), point.pos().y(), point.pos().z()),
            (1.0, 2.0, 3.0)
        );
        assert!(abstract_space.lod0_multi_surface().is_none());
    }

    #[test]
    fn test_round_trip_abstract_space_with_lod0_point() {
        let xml_document = b"\
<tran:TrafficSpace gml:id=\"TS_1\">
    <lod0Point>
        <gml:Point gml:id=\"P_1\">
            <gml:pos>1.0 2.0 3.0</gml:pos>
        </gml:Point>
    </lod0Point>
    <lod1Solid xlink:href=\"#S_1\"/>
</tran:TrafficSpace>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_space =
            deserialize_abstract_space(xml_document, &index, &DeserializationConfig::default())
                .expect("should work");

        let xml = serialize_traffic_space(&abstract_space);
        assert!(xml.contains("<lod0Point>"), "{xml}");

        let round_tripped_index =
            XmlDocumentIndex::from_scan(xml.as_bytes(), None).expect("should work");
        let round_tripped = deserialize_abstract_space(
            xml.as_bytes(),
            &round_tripped_index,
            &DeserializationConfig::default(),
        )
        .expect("should work");
        assert_eq!(abstract_space.lod0_point(), round_tripped.lod0_point());
        assert_eq!(abstract_space.lod1_solid(), round_tripped.lod1_solid());
    }
}
