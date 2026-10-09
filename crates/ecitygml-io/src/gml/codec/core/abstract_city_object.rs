use crate::Error;
use crate::gml::codec::core::abstract_appearance_property::{
    deserialize_abstract_appearance_property, serialize_abstract_appearance_property,
};
use crate::gml::codec::core::abstract_feature_with_lifespan::deserialize_abstract_feature_with_lifespan;
use crate::gml::codec::core::city_object_relation_property::{
    deserialize_city_object_relation_property, serialize_city_object_relation_property,
};
use crate::gml::codec::core::enums::deserialize_relative_to_water;
use crate::gml::codec::core::enums::{
    deserialize_relative_to_terrain, serialize_relative_to_terrain, serialize_relative_to_water,
};
use crate::gml::codec::core::{
    deserialize_external_reference_property, serialize_external_reference_property,
};
use crate::gml::codec::core::{
    serialize_abstract_feature_with_lifespan, serialize_abstract_feature_with_lifespan_attributes,
};
use crate::gml::codec::generics::{
    deserialize_generic_attribute_property, serialize_generic_attribute_property,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::core::enums::{RelativeToTerrain, RelativeToWater};
use ecitygml_core::model::core::{
    AbstractCityObject, AsAbstractCityObject, AsAbstractCityObjectMut,
    AsAbstractFeatureWithLifespan,
};
use egml::io::util::collect_children;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_city_object(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractCityObject, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_city_object received a truncated index — caller must scan to sufficient depth"
    );

    let mut abstract_feature_with_lifespan_result = None;
    let mut appearances_result = None;
    let mut related_to_result = None;

    rayon::scope(|s| {
        s.spawn(|_| {
            abstract_feature_with_lifespan_result = Some(
                deserialize_abstract_feature_with_lifespan(xml_document, index, config),
            );
        });
        s.spawn(|_| {
            appearances_result = Some(collect_children(
                xml_document,
                index,
                CityGmlElement::AbstractAppearanceProperty.into(),
                config,
                deserialize_abstract_appearance_property,
            ));
        });
        s.spawn(|_| {
            related_to_result = Some(collect_children(
                xml_document,
                index,
                CityGmlElement::RelatedToProperty.into(),
                config,
                deserialize_city_object_relation_property,
            ));
        });
    });

    let mut abstract_city_object = AbstractCityObject::from_abstract_feature_with_lifespan(
        abstract_feature_with_lifespan_result
            .expect("rayon::scope guarantees all spawns complete")?,
    );

    let relative_to_terrain: Option<RelativeToTerrain> = index
        .first(CityGmlElement::RelativeToTerrainProperty.into())
        .map(|x| deserialize_relative_to_terrain(xml_document[x.range()].as_ref()))
        .transpose()?;
    abstract_city_object.set_relative_to_terrain(relative_to_terrain);

    let relative_to_water: Option<RelativeToWater> = index
        .first(CityGmlElement::RelativeToWaterProperty.into())
        .map(|x| deserialize_relative_to_water(xml_document[x.range()].as_ref()))
        .transpose()?;
    abstract_city_object.set_relative_to_water(relative_to_water);

    let external_references = index
        .get(CityGmlElement::ExternalReferenceProperty.into())
        .iter()
        .map(|x| deserialize_external_reference_property(&xml_document[x.range()]))
        .collect::<Result<_, _>>()?;
    abstract_city_object.set_external_references(external_references);

    let generic_attributes = index
        .get(CityGmlElement::GenericAttributeProperty.into())
        .iter()
        .map(|x| deserialize_generic_attribute_property(&xml_document[x.range()]))
        .collect::<Result<_, _>>()?;
    abstract_city_object.set_generic_attributes(generic_attributes);

    abstract_city_object
        .set_appearances(appearances_result.expect("rayon::scope guarantees all spawns complete")?);
    abstract_city_object
        .set_related_to(related_to_result.expect("rayon::scope guarantees all spawns complete")?);

    Ok(abstract_city_object)
}

pub fn serialize_abstract_city_object(
    abstract_city_object: &AbstractCityObject,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_feature_with_lifespan(
        abstract_city_object.abstract_feature_with_lifespan(),
        xml_fragment_writer,
    )?;

    if let Some(relative_to_terrain) = abstract_city_object.relative_to_terrain() {
        serialize_relative_to_terrain(
            relative_to_terrain,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::RelativeToTerrainProperty,
        )?;
    }

    if let Some(relative_to_water) = abstract_city_object.relative_to_water() {
        serialize_relative_to_water(
            relative_to_water,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::RelativeToWaterProperty,
        )?;
    }

    for external_reference in abstract_city_object.external_references() {
        serialize_external_reference_property(
            external_reference,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::ExternalReferenceProperty,
        )?;
    }

    for generic_attribute in abstract_city_object.generic_attributes() {
        serialize_generic_attribute_property(
            generic_attribute,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::GenericAttributeProperty,
        )?;
    }

    for prop in abstract_city_object.appearances() {
        serialize_abstract_appearance_property(prop, xml_fragment_writer)?;
    }

    for prop in abstract_city_object.related_to() {
        serialize_city_object_relation_property(prop, xml_fragment_writer)?;
    }

    Ok(())
}

pub fn serialize_abstract_city_object_attributes(
    abstract_city_object: &AbstractCityObject,
) -> Vec<(String, String)> {
    serialize_abstract_feature_with_lifespan_attributes(
        abstract_city_object.abstract_feature_with_lifespan(),
    )
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::core::AsAbstractFeature;
    use egml::io::util::{Formatting, XmlFragmentWriter};
    use egml::model::base::{AsAbstractGml, HasAssociationAttributes, Id};
    use egml::model::basic_types::Code;

    #[test]
    fn test_deserialize_with_name_and_generic_attributes() {
        let xml_document = b"
    <con:WallSurface gml:id=\"test-id-123\">
      <gml:name>West wall</gml:name>
      <genericAttribute>
        <gen:StringAttribute>
          <gen:name>DatenquelleBodenhoehe</gen:name>
          <gen:value>1100</gen:value>
        </gen:StringAttribute>
      </genericAttribute>
      <genericAttribute>
        <gen:StringAttribute>
          <gen:name>DatenquelleDachhoehe</gen:name>
          <gen:value>1000</gen:value>
        </gen:StringAttribute>
      </genericAttribute>
    </con:WallSurface>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let city_object = deserialize_abstract_city_object(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            city_object.feature_id(),
            &Id::try_from("test-id-123").expect("should work")
        );
        assert_eq!(
            city_object.names().first().expect("name should be present"),
            &Code::new("West wall")
        );
        assert_eq!(city_object.generic_attributes().len(), 2);
    }

    #[test]
    fn test_deserialize_with_multiple_generic_attribute_types() {
        let xml_document = b"
    <bldg:Building gml:id=\"test-id\">
      <genericAttribute>
        <gen:StringAttribute>
          <gen:name>attribute_name_one</gen:name>
          <gen:value>1100</gen:value>
        </gen:StringAttribute>
      </genericAttribute>
      <genericAttribute>
        <gen:IntAttribute>
          <gen:name>attribute_name_two</gen:name>
          <gen:value>1100</gen:value>
        </gen:IntAttribute>
      </genericAttribute>
       <genericAttribute>
        <gen:DoubleAttribute>
          <gen:name>attribute_name_three</gen:name>
          <gen:value>1100</gen:value>
        </gen:DoubleAttribute>
      </genericAttribute>
    </bldg:Building>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let city_object = deserialize_abstract_city_object(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            city_object.feature_id(),
            &Id::try_from("test-id").expect("should work")
        );
        assert!(city_object.names().is_empty());
        assert_eq!(city_object.generic_attributes().len(), 3);
    }

    #[test]
    fn test_deserialize_with_related_to() {
        let xml_document = b"
    <tran:TrafficSpace gml:id=\"UUID_ed2149e3-421a-3dcd-9727-54637db9d9e3\">
      <relatedTo>
        <CityObjectRelation>
          <genericAttribute>
            <gen:StringAttribute>
              <gen:name>identifier_roadObjectId</gen:name>
              <gen:value>4970008</gen:value>
            </gen:StringAttribute>
          </genericAttribute>
          <relationType>relatedFurniture</relationType>
          <relatedTo xlink:href=\"#UUID_aca562a7-20d4-3159-b121-e50cc6eb0ade\"/>
        </CityObjectRelation>
      </relatedTo>
    </tran:TrafficSpace>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let city_object = deserialize_abstract_city_object(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(city_object.related_to().len(), 1);

        let relation = city_object.related_to()[0]
            .object()
            .expect("relation should be inline");

        assert_eq!(relation.relation_type().value(), "relatedFurniture");
        assert_eq!(
            relation.relation_to().href().expect("should have href"),
            &egml::model::xlink::HRef::from("#UUID_aca562a7-20d4-3159-b121-e50cc6eb0ade")
        );
        assert_eq!(relation.generic_attributes().len(), 1);
    }

    #[test]
    fn test_serialize_round_trip_related_to() {
        let xml_document = b"
    <tran:TrafficSpace gml:id=\"UUID_ed2149e3-421a-3dcd-9727-54637db9d9e3\">
      <relatedTo>
        <CityObjectRelation>
          <relationType>relatedFurniture</relationType>
          <relatedTo xlink:href=\"#UUID_aca562a7-20d4-3159-b121-e50cc6eb0ade\"/>
        </CityObjectRelation>
      </relatedTo>
    </tran:TrafficSpace>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let city_object = deserialize_abstract_city_object(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        xml_fragment_writer
            .write_start_event(
                CityGmlNamespace::Transportation,
                CityGmlElement::TrafficSpace,
            )
            .expect("should work");
        serialize_abstract_city_object(&city_object, &mut xml_fragment_writer)
            .expect("should work");
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

        assert!(xml.contains("relatedTo"));
    }

    #[test]
    fn test_deserialize_with_measure_generic_attribute() {
        let xml_document = b"
    <bldg:Building gml:id=\"test-id\">
      <genericAttribute>
        <gen:StringAttribute>
          <gen:name>attribute_name_one</gen:name>
          <gen:value>1100</gen:value>
        </gen:StringAttribute>
      </genericAttribute>
      <genericAttribute>
        <gen:MeasureAttribute>
          <gen:name>GrossPlannedArea</gen:name>
          <gen:value uom=\"m2\">120.0</gen:value>
        </gen:MeasureAttribute>
      </genericAttribute>
    </bldg:Building>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let city_object = deserialize_abstract_city_object(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            city_object.feature_id(),
            &Id::try_from("test-id").expect("should work")
        );
        assert!(city_object.names().is_empty());
        assert_eq!(city_object.generic_attributes().len(), 2);
    }

    #[test]
    fn test_deserialize_with_external_references() {
        let xml_document = b"
    <bldg:Building gml:id=\"test-id\">
      <externalReference>
        <ExternalReference>
          <targetResource>DEHHALKA70002P5E</targetResource>
          <informationSystem>http://example.com</informationSystem>
        </ExternalReference>
      </externalReference>
      <externalReference>
        <ExternalReference>
          <targetResource>DEHHALKA70002P5F</targetResource>
        </ExternalReference>
      </externalReference>
    </bldg:Building>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let city_object = deserialize_abstract_city_object(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(city_object.external_references().len(), 2);
        assert_eq!(
            city_object.external_references()[0].target_resource,
            "DEHHALKA70002P5E"
        );
        assert_eq!(
            city_object.external_references()[0]
                .information_system
                .as_deref(),
            Some("http://example.com")
        );
        assert_eq!(
            city_object.external_references()[1].target_resource,
            "DEHHALKA70002P5F"
        );
    }

    #[test]
    fn test_round_trip_with_external_references() {
        let xml_document = b"
    <bldg:Building gml:id=\"test-id\">
      <externalReference>
        <ExternalReference>
          <targetResource>DEHHALKA70002P5E</targetResource>
          <informationSystem>http://example.com</informationSystem>
        </ExternalReference>
      </externalReference>
    </bldg:Building>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let city_object = deserialize_abstract_city_object(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        xml_fragment_writer
            .write_start_event(CityGmlNamespace::Building, CityGmlElement::Building)
            .expect("should work");
        serialize_abstract_city_object(&city_object, &mut xml_fragment_writer)
            .expect("should work");
        xml_fragment_writer
            .write_end_event(CityGmlNamespace::Building, CityGmlElement::Building)
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
        let round_tripped = deserialize_abstract_city_object(
            xml.as_bytes(),
            &round_tripped_index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            city_object.external_references(),
            round_tripped.external_references()
        );
    }
}
