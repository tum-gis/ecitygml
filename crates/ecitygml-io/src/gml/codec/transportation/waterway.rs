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
use ecitygml_core::model::transportation::{AsAbstractTransportationSpace, Waterway};
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use egml::io::util::{XmlDocumentIndex, collect_children};
use egml::model::basic_types::Code;
use rayon::iter::IntoParallelRefIterator;
use rayon::iter::ParallelIterator;

pub fn deserialize_waterway(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Waterway, Error> {
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

    let mut waterway = Waterway::from_abstract_transportation_space(
        abstract_transportation_space_result
            .expect("rayon::scope guarantees all spawns complete")?,
    );

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    waterway.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    waterway.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    waterway.set_usages(usages.into_iter().map(Into::into).collect());

    waterway.set_sections(sections_result.expect("rayon::scope guarantees all spawns complete")?);
    waterway.set_intersections(
        intersections_result.expect("rayon::scope guarantees all spawns complete")?,
    );

    Ok(waterway)
}

pub fn serialize_waterway(
    waterway: &Waterway,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_waterway_attributes(waterway);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Transportation,
        CityGmlElement::Waterway,
        attributes,
    )?;

    serialize_abstract_transportation_space(
        waterway.abstract_transportation_space(),
        xml_fragment_writer,
    )?;

    if let Some(class) = waterway.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in waterway.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in waterway.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::UsageProperty,
        )?;
    }

    let xml_fragments = waterway
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

    let xml_fragments = waterway
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

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::Transportation, CityGmlElement::Waterway)?;

    Ok(())
}

pub fn serialize_waterway_attributes(waterway: &Waterway) -> Vec<(String, String)> {
    serialize_abstract_transportation_space_attributes(waterway.abstract_transportation_space())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::core::{AsAbstractCityObject, AsAbstractFeature, AsAbstractSpace};
    use egml::model::base::Id;

    #[test]
    fn test_deserialize_basic_waterway() {
        let xml_document = b"
    <tran:Waterway gml:id=\"UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f\">
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
    </tran:Waterway>";

        let waterway = deserialize_waterway(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            waterway.feature_id(),
            &Id::try_from("UUID_8a13804c-cbd7-3a2f-9d46-e4d528a4bb4f").expect("should work")
        );

        assert!(waterway.lod2_multi_surface().is_none());
        assert_eq!(waterway.generic_attributes().len(), 1);
        assert!(waterway.intersections().is_empty());
        assert_eq!(waterway.sections().len(), 1);
        let traffic_space = waterway.sections().first().unwrap().object().unwrap();
        assert_eq!(
            traffic_space.feature_id(),
            &Id::try_from("UUID_0950bfa5-204e-33e6-bdb7-c5c318d73a29").expect("should work")
        );
    }
}
