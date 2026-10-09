use crate::Error;
use crate::gml::codec::transportation::abstract_transportation_space::{
    deserialize_abstract_transportation_space, serialize_abstract_transportation_space,
    serialize_abstract_transportation_space_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::transportation::{AsAbstractTransportationSpace, Intersection};
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::basic_types::Code;

pub fn deserialize_intersection(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Intersection, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_transportation_space =
        deserialize_abstract_transportation_space(xml_document, index, config)?;

    let mut intersection =
        Intersection::from_abstract_transportation_space(abstract_transportation_space);

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    intersection.set_class_opt(class.map(Into::into));

    Ok(intersection)
}

pub fn serialize_intersection(
    intersection: &Intersection,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_intersection_attributes(intersection);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Transportation,
        CityGmlElement::Intersection,
        attributes,
    )?;

    serialize_abstract_transportation_space(
        intersection.abstract_transportation_space(),
        xml_fragment_writer,
    )?;

    if let Some(class) = intersection.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::ClassProperty,
        )?;
    }

    xml_fragment_writer.write_end_event(
        CityGmlNamespace::Transportation,
        CityGmlElement::Intersection,
    )?;

    Ok(())
}

pub fn serialize_intersection_attributes(intersection: &Intersection) -> Vec<(String, String)> {
    serialize_abstract_transportation_space_attributes(intersection.abstract_transportation_space())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::core::{
        AbstractSpaceBoundaryKind, AbstractThematicSurfaceKind, AsAbstractCityObject,
        AsAbstractFeature, AsAbstractSpace,
    };
    use ecitygml_core::model::transportation::enums::GranularityValue;
    use ecitygml_core::model::transportation::{AsAbstractTransportationSpace, TrafficArea};
    use egml::model::base::Id;

    #[test]
    fn test_deserialize_basic_intersection() {
        let xml_document = b"
        <tran:Intersection gml:id=\"UUID_9a9fc5a0-b252-3d63-ac79-b3141175f152\">
          <genericAttribute>
            <gen:StringAttribute>
              <gen:name>identifier_new_section</gen:name>
              <gen:value>abc</gen:value>
            </gen:StringAttribute>
          </genericAttribute>
          <tran:trafficSpace>
            <tran:TrafficSpace gml:id=\"UUID_ff91145b-98e8-388b-b4d1-b94624f806db\">
              <genericAttribute>
                <gen:StringAttribute>
                  <gen:name>identifier_roadId</gen:name>
                  <gen:value>4516050</gen:value>
                </gen:StringAttribute>
              </genericAttribute>
              <tran:function>2</tran:function>
              <tran:usage>1</tran:usage>
              <tran:granularity>lane</tran:granularity>
              <tran:trafficDirection>forwards</tran:trafficDirection>
              <tran:predecessor xlink:href=\"#UUID_35e15191-e911-320b-bbe7-004b237a024a\"/>
              <tran:successor xlink:href=\"#UUID_efb6f11e-0d92-3d1f-8208-7ddbea02e829\"/>
            </tran:TrafficSpace>
          </tran:trafficSpace>
        </tran:Intersection>";

        let intersection = deserialize_intersection(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            intersection.feature_id(),
            &Id::try_from("UUID_9a9fc5a0-b252-3d63-ac79-b3141175f152").expect("should work")
        );

        assert!(intersection.lod2_multi_surface().is_none());
        assert_eq!(intersection.generic_attributes().len(), 1);
        assert!(intersection.auxiliary_traffic_spaces().is_empty());
        assert_eq!(intersection.traffic_spaces().len(), 1);
        let traffic_space = intersection
            .traffic_spaces()
            .first()
            .unwrap()
            .object()
            .unwrap();

        assert_eq!(
            traffic_space.feature_id(),
            &Id::try_from("UUID_ff91145b-98e8-388b-b4d1-b94624f806db").expect("should work")
        );
        assert_eq!(traffic_space.granularity(), &GranularityValue::Lane);

        let traffic_areas: Vec<&TrafficArea> = traffic_space
            .boundaries()
            .iter()
            .flat_map(|x| x.object())
            .filter_map(|x| match x {
                AbstractSpaceBoundaryKind::AbstractThematicSurfaceKind(
                    AbstractThematicSurfaceKind::TrafficArea(x),
                ) => Some(x),
                _ => None,
            })
            .collect();
        assert!(traffic_areas.is_empty());
    }
}
