use crate::Error;
use crate::gml::codec::transportation::abstract_transportation_space::{
    deserialize_abstract_transportation_space, serialize_abstract_transportation_space,
    serialize_abstract_transportation_space_attributes,
};
use crate::gml::codec::transportation::intersection_property::{
    deserialize_intersection_property, serialize_intersection_property,
};
use crate::gml::codec::transportation::section_property::{
    deserialize_section_property, serialize_section_property,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::transportation::{AsAbstractTransportationSpace, Road};
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use egml::io::util::{XmlDocumentIndex, collect_children};
use egml::model::basic_types::Code;
use rayon::iter::IntoParallelRefIterator;
use rayon::iter::ParallelIterator;

pub fn deserialize_road(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Road, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let mut abstract_transportation_space_result = None;
    let mut sections_result = None;
    let mut intersections_result = None;

    rayon::scope(|s| {
        s.spawn(|_| {
            abstract_transportation_space_result = Some(deserialize_abstract_transportation_space(
                xml_document,
                index,
                config,
            ))
        });
        s.spawn(|_| {
            sections_result = Some(collect_children(
                xml_document,
                index,
                CityGmlElement::SectionProperty.into(),
                config,
                deserialize_section_property,
            ));
        });
        s.spawn(|_| {
            intersections_result = Some(collect_children(
                xml_document,
                index,
                CityGmlElement::IntersectionProperty.into(),
                config,
                deserialize_intersection_property,
            ));
        });
    });
    let mut road = Road::from_abstract_transportation_space(
        abstract_transportation_space_result
            .expect("rayon::scope guarantees all spawns complete")?,
    );

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    road.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    road.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    road.set_usages(usages.into_iter().map(Into::into).collect());

    road.set_sections(sections_result.expect("rayon::scope guarantees all spawns complete")?);
    road.set_intersections(
        intersections_result.expect("rayon::scope guarantees all spawns complete")?,
    );

    Ok(road)
}

pub fn serialize_road(
    road: &Road,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_road_attributes(road);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Transportation,
        CityGmlElement::Road,
        attributes,
    )?;

    serialize_abstract_transportation_space(
        road.abstract_transportation_space(),
        xml_fragment_writer,
    )?;

    if let Some(class) = road.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in road.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in road.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::UsageProperty,
        )?;
    }

    let xml_fragments = road
        .sections()
        .par_iter()
        .map(|x| {
            let mut xml_fragment_writer = xml_fragment_writer.spawn_child();
            serialize_section_property(x, &mut xml_fragment_writer)?;
            Ok(xml_fragment_writer)
        })
        .collect::<Result<Vec<_>, Error>>()?;
    for fragment in xml_fragments {
        xml_fragment_writer.merge_chunked(fragment);
    }

    let xml_fragments = road
        .intersections()
        .par_iter()
        .map(|x| {
            let mut xml_fragment_writer = xml_fragment_writer.spawn_child();
            serialize_intersection_property(x, &mut xml_fragment_writer)?;
            Ok(xml_fragment_writer)
        })
        .collect::<Result<Vec<_>, Error>>()?;
    for fragment in xml_fragments {
        xml_fragment_writer.merge_chunked(fragment);
    }

    xml_fragment_writer.write_end_event(CityGmlNamespace::Transportation, CityGmlElement::Road)?;

    Ok(())
}

pub fn serialize_road_attributes(road: &Road) -> Vec<(String, String)> {
    serialize_abstract_transportation_space_attributes(road.abstract_transportation_space())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::core::{AsAbstractCityObject, AsAbstractFeature, AsAbstractSpace};
    use egml::model::base::Id;

    #[test]
    fn test_deserialize_basic_road() {
        let xml_document = b"
    <tran:Road gml:id=\"UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f\">
      <genericAttribute>
        <gen:StringAttribute>
          <gen:name>identifier_new_section</gen:name>
          <gen:value>abc</gen:value>
        </gen:StringAttribute>
      </genericAttribute>
      <tran:section>
        <tran:Section gml:id=\"UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29\">
        </tran:Section>
      </tran:section>
    </tran:Road>";

        let road = deserialize_road(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            road.feature_id(),
            &Id::try_from("UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f").expect("should work")
        );

        assert!(road.lod2_multi_surface().is_none());
        assert_eq!(road.generic_attributes().len(), 1);
        assert!(road.intersections().is_empty());
        assert_eq!(road.sections().len(), 1);
        let traffic_space = road.sections().first().unwrap().object().unwrap();
        assert_eq!(
            traffic_space.feature_id(),
            &Id::try_from("UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29").expect("should work")
        );
    }
}
