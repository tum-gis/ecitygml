use crate::Error;
use crate::gml::codec::core::abstract_physical_space::{
    deserialize_abstract_physical_space, serialize_abstract_physical_space,
    serialize_abstract_physical_space_attributes,
};
use crate::gml::codec::core::implicit_geometry_property::{
    deserialize_implicit_geometry_property, serialize_implicit_geometry_property,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::core::{
    AbstractOccupiedSpace, AsAbstractOccupiedSpace, AsAbstractOccupiedSpaceMut,
    AsAbstractPhysicalSpace,
};
use egml::io::util::{ChunkedSink, collect_child};
use egml::io::util::{XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_occupied_space(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractOccupiedSpace, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_occupied_space received a truncated index — caller must scan to sufficient depth"
    );

    let mut abstract_physical_space_result = None;
    let mut lod1_implicit_geometry_result = None;
    let mut lod2_implicit_geometry_result = None;
    let mut lod3_implicit_geometry_result = None;

    rayon::scope(|s| {
        s.spawn(|_| {
            abstract_physical_space_result = Some(deserialize_abstract_physical_space(
                xml_document,
                index,
                config,
            ));
        });
        s.spawn(|_| {
            lod1_implicit_geometry_result = Some(collect_child(
                xml_document,
                index,
                CityGmlElement::Lod1ImplicitRepresentationProperty.into(),
                config,
                deserialize_implicit_geometry_property,
            ));
        });
        s.spawn(|_| {
            lod2_implicit_geometry_result = Some(collect_child(
                xml_document,
                index,
                CityGmlElement::Lod2ImplicitRepresentationProperty.into(),
                config,
                deserialize_implicit_geometry_property,
            ));
        });
        s.spawn(|_| {
            lod3_implicit_geometry_result = Some(collect_child(
                xml_document,
                index,
                CityGmlElement::Lod3ImplicitRepresentationProperty.into(),
                config,
                deserialize_implicit_geometry_property,
            ));
        });
    });

    let mut abstract_occupied_space = AbstractOccupiedSpace::from_abstract_physical_space(
        abstract_physical_space_result.expect("rayon::scope guarantees all spawns complete")?,
    );
    abstract_occupied_space.set_lod1_implicit_representation(
        lod1_implicit_geometry_result.expect("rayon::scope guarantees all spawns complete")?,
    );
    abstract_occupied_space.set_lod2_implicit_representation(
        lod2_implicit_geometry_result.expect("rayon::scope guarantees all spawns complete")?,
    );
    abstract_occupied_space.set_lod3_implicit_representation(
        lod3_implicit_geometry_result.expect("rayon::scope guarantees all spawns complete")?,
    );

    Ok(abstract_occupied_space)
}

pub fn serialize_abstract_occupied_space(
    abstract_occupied_space: &AbstractOccupiedSpace,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_physical_space(
        abstract_occupied_space.abstract_physical_space(),
        xml_fragment_writer,
    )?;

    if let Some(implicit_geometry_property) = abstract_occupied_space.lod1_implicit_representation()
    {
        serialize_implicit_geometry_property(
            implicit_geometry_property,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::Lod1ImplicitRepresentationProperty,
        )?;
    }

    if let Some(implicit_geometry_property) = abstract_occupied_space.lod2_implicit_representation()
    {
        serialize_implicit_geometry_property(
            implicit_geometry_property,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::Lod2ImplicitRepresentationProperty,
        )?;
    }

    if let Some(implicit_geometry_property) = abstract_occupied_space.lod3_implicit_representation()
    {
        serialize_implicit_geometry_property(
            implicit_geometry_property,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::Lod3ImplicitRepresentationProperty,
        )?;
    }

    Ok(())
}

pub fn serialize_abstract_occupied_space_attributes(
    abstract_occupied_space: &AbstractOccupiedSpace,
) -> Vec<(String, String)> {
    serialize_abstract_physical_space_attributes(abstract_occupied_space.abstract_physical_space())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::core::AsAbstractOccupiedSpace;

    #[test]
    fn test_deserialize_abstract_occupied_space() {
        let xml_document = b"<frn:CityFurniture gml:id=\"UUID_35904d1c-ecd3-30d8-b8a5-02710feebc2d\">
      <gml:name>Private_Parking</gml:name>
      <genericAttribute>
        <gen:StringAttribute>
          <gen:name>identifier_roadObjectName</gen:name>
          <gen:value>Private_Parking</gen:value>
        </gen:StringAttribute>
      </genericAttribute>
      <lod2MultiSurface>
        <gml:MultiSurface>
          <gml:surfaceMember>
            <gml:Polygon>
              <gml:exterior>
                <gml:LinearRing>
                  <gml:posList srsDimension=\"3\">678279.7493302015 5403792.6862397045 369.4773337509289 678279.7493302015 5403792.6862397045 369.2473337509289 678279.450359054 5403792.98122488 369.2473337509289 678279.450359054 5403792.98122488 369.4773337509289 678279.7493302015 5403792.6862397045 369.4773337509289</gml:posList>
                </gml:LinearRing>
              </gml:exterior>
            </gml:Polygon>
          </gml:surfaceMember>
        </gml:MultiSurface>
      </lod2MultiSurface>
      <lod1ImplicitRepresentation>
        <ImplicitGeometry>
          <transformationMatrix>-0.7023456529181015 0.7118360652755983 0.0 0.0 -0.7118360652755983 -0.7023456529181015 0.0 0.0 0.0 0.0 1.0 0.0 0.0 0.0 0.0 1.0</transformationMatrix>
          <referencePoint>
            <gml:Point>
              <gml:pos srsDimension=\"3\">678279.5998446278 5403792.833732292 369.2473337509289</gml:pos>
            </gml:Point>
          </referencePoint>
        </ImplicitGeometry>
      </lod1ImplicitRepresentation>
    </frn:CityFurniture>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_occupied_space = deserialize_abstract_occupied_space(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert!(
            abstract_occupied_space
                .lod1_implicit_representation()
                .is_some()
        );
        assert!(
            abstract_occupied_space
                .lod2_implicit_representation()
                .is_none()
        );
        assert!(
            abstract_occupied_space
                .lod3_implicit_representation()
                .is_none()
        );

        let lod1_implicit_representation = abstract_occupied_space
            .lod1_implicit_representation()
            .unwrap()
            .object()
            .unwrap();
        assert_eq!(
            lod1_implicit_representation
                .reference_point()
                .object()
                .expect("must exist")
                .pos()
                .x(),
            678279.5998446278
        );
        assert_eq!(
            lod1_implicit_representation
                .reference_point()
                .object()
                .expect("must exist")
                .pos()
                .y(),
            5403792.833732292
        );
        assert_eq!(
            lod1_implicit_representation
                .reference_point()
                .object()
                .expect("must exist")
                .pos()
                .z(),
            369.2473337509289
        );
    }
}
