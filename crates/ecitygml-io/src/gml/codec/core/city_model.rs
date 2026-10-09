use crate::Error;
use crate::gml::codec::core::abstract_appearance_property::{
    deserialize_abstract_appearance_property, serialize_abstract_appearance_member_property,
};
use crate::gml::codec::core::abstract_city_object_property::{
    deserialize_abstract_city_object_property, serialize_abstract_city_object_member_property,
};
use crate::gml::codec::core::{
    deserialize_abstract_feature_with_lifespan, serialize_abstract_feature_with_lifespan,
    serialize_abstract_feature_with_lifespan_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, DeserializationConfig, deserializer_pool, get_namespace_pairs,
};
use ecitygml_core::model::core::{AsAbstractFeatureWithLifespan, CityModel};
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use egml::io::util::{XmlDocumentIndex, collect_children};
use rayon::iter::{IntoParallelRefIterator, ParallelIterator};

pub fn deserialize_city_model(
    xml_document: &[u8],
    config: &DeserializationConfig,
) -> Result<CityModel, Error> {
    deserializer_pool().install(|| {
        let index = XmlDocumentIndex::from_scan(xml_document, config.initial_scan_depth())?;

        let mut abstract_feature_with_lifespan_result = None;
        let mut city_object_members_result = None;
        let mut appearance_members_result = None;

        rayon::scope(|s| {
            s.spawn(|_| {
                abstract_feature_with_lifespan_result = Some(
                    deserialize_abstract_feature_with_lifespan(xml_document, &index, config),
                );
            });
            s.spawn(|_| {
                city_object_members_result = Some(collect_children(
                    xml_document,
                    &index,
                    CityGmlElement::CityObjectMemberProperty.into(),
                    config,
                    deserialize_abstract_city_object_property,
                ));
            });
            s.spawn(|_| {
                appearance_members_result = Some(collect_children(
                    xml_document,
                    &index,
                    CityGmlElement::AppearanceMemberProperty.into(),
                    config,
                    deserialize_abstract_appearance_property,
                ));
            });
        });

        let mut city_model = CityModel::from_abstract_feature_with_lifespan(
            abstract_feature_with_lifespan_result
                .expect("rayon::scope guarantees all spawns complete")?,
        );
        city_model.set_city_object_members(
            city_object_members_result.expect("rayon::scope guarantees all spawns complete")?,
        );
        city_model.set_appearance_members(
            appearance_members_result.expect("rayon::scope guarantees all spawns complete")?,
        );

        Ok(city_model)
    })
}

pub fn serialize_city_model(
    city_model: &CityModel,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let mut attributes = get_namespace_pairs();
    attributes.extend(serialize_city_model_attributes(city_model));

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Core,
        CityGmlElement::CityModel,
        attributes,
    )?;

    serialize_abstract_feature_with_lifespan(
        city_model.abstract_feature_with_lifespan(),
        xml_fragment_writer,
    )?;

    let xml_fragments = city_model
        .city_object_members()
        .par_iter()
        .map(|x| {
            let mut xml_fragment_writer = xml_fragment_writer.spawn_child();
            serialize_abstract_city_object_member_property(x, &mut xml_fragment_writer)?;
            Ok(xml_fragment_writer)
        })
        .collect::<Result<Vec<_>, Error>>()?;
    for fragment in xml_fragments {
        xml_fragment_writer.merge_chunked(fragment);
    }

    let xml_fragments = city_model
        .appearance_members()
        .par_iter()
        .map(|x| {
            let mut xml_fragment_writer = xml_fragment_writer.spawn_child();
            serialize_abstract_appearance_member_property(x, &mut xml_fragment_writer)?;
            Ok(xml_fragment_writer)
        })
        .collect::<Result<Vec<_>, Error>>()?;
    for fragment in xml_fragments {
        xml_fragment_writer.merge_chunked(fragment);
    }

    xml_fragment_writer.write_end_event(CityGmlNamespace::Core, CityGmlElement::CityModel)?;

    Ok(())
}

pub fn serialize_city_model_attributes(city_model: &CityModel) -> Vec<(String, String)> {
    serialize_abstract_feature_with_lifespan_attributes(city_model.abstract_feature_with_lifespan())
}
