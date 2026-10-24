use crate::Error;
use crate::gml::codec::building::{
    deserialize_abstract_building_subdivision_kind, serialize_abstract_building_subdivision_kind,
};
use crate::gml::codec::city_object_group::{
    deserialize_city_object_group, serialize_city_object_group,
};
use crate::gml::codec::generics::{
    deserialize_generic_logical_space, serialize_generic_logical_space,
};
use crate::gml::util::{CityGmlElement, CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::core::AbstractLogicalSpaceKind;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_logical_space_kind(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Option<AbstractLogicalSpaceKind>, Error> {
    if let Some(x) = deserialize_abstract_building_subdivision_kind(xml_document, index, config)? {
        return Ok(Some(x.into()));
    }

    if let Some(index) = index.first(CityGmlElement::CityObjectGroup.into()) {
        let city_object_group =
            deserialize_city_object_group(&xml_document[index.range()], index, config)?;
        return Ok(Some(city_object_group.into()));
    }

    if let Some(index) = index.first(CityGmlElement::GenericLogicalSpace.into()) {
        let generic_logical_space =
            deserialize_generic_logical_space(&xml_document[index.range()], index, config)?;
        return Ok(Some(generic_logical_space.into()));
    }

    Ok(None)
}

pub fn serialize_abstract_logical_space_kind(
    abstract_logical_space_kind: &AbstractLogicalSpaceKind,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    match abstract_logical_space_kind {
        AbstractLogicalSpaceKind::AbstractBuildingSubdivisionKind(x) => {
            serialize_abstract_building_subdivision_kind(x, xml_fragment_writer)
        }
        AbstractLogicalSpaceKind::CityObjectGroup(x) => {
            serialize_city_object_group(x, xml_fragment_writer)
        }
        AbstractLogicalSpaceKind::GenericLogicalSpace(x) => {
            serialize_generic_logical_space(x, xml_fragment_writer)
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::common::{FeatureType, HasFeatureType};
    use ecitygml_core::model::generics::GenericLogicalSpace;
    use egml::io::util::Formatting;
    use egml::model::base::Id;

    #[test]
    fn test_deserialize_city_object_group_as_abstract_logical_space_kind() {
        let xml_document = b"<cityObjectMember>
    <grp:CityObjectGroup gml:id=\"UUID_f488e8ce-b953-4b35-a3fe-a394fb203868\">
      <gml:description>CityObjectGroup for grouping the trees to a forest</gml:description>
      <gml:name>Forest KIT</gml:name>
      <creationDate>2015-03-06T00:00:00+01:00</creationDate>
      <grp:groupMember>
        <grp:Role>
          <grp:groupMember xlink:href=\"#GMLID_SO0286258_965_2893\"/>
        </grp:Role>
      </grp:groupMember>
    </grp:CityObjectGroup>
  </cityObjectMember>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_logical_space_kind = deserialize_abstract_logical_space_kind(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work")
        .expect("should recognize a CityObjectGroup");

        assert!(matches!(
            abstract_logical_space_kind,
            AbstractLogicalSpaceKind::CityObjectGroup(_)
        ));
        assert_eq!(
            abstract_logical_space_kind.feature_type(),
            FeatureType::CityObjectGroup
        );
    }

    #[test]
    fn test_deserialize_generic_logical_space_as_abstract_logical_space_kind() {
        let xml_document = b"<cityObjectMember>
    <gen:GenericLogicalSpace gml:id=\"GLS_1\">
      <gen:class>1000</gen:class>
    </gen:GenericLogicalSpace>
  </cityObjectMember>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_logical_space_kind = deserialize_abstract_logical_space_kind(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work")
        .expect("should recognize a GenericLogicalSpace");

        assert!(matches!(
            abstract_logical_space_kind,
            AbstractLogicalSpaceKind::GenericLogicalSpace(_)
        ));
        assert_eq!(
            abstract_logical_space_kind.feature_type(),
            FeatureType::GenericLogicalSpace
        );
    }

    #[test]
    fn test_serialize_generic_logical_space_as_abstract_logical_space_kind() {
        let abstract_logical_space_kind: AbstractLogicalSpaceKind =
            GenericLogicalSpace::new(Id::try_from("GLS_1").expect("should work")).into();

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_abstract_logical_space_kind(
            &abstract_logical_space_kind,
            &mut xml_fragment_writer,
        )
        .expect("should serialize");
        let mut buf = Vec::new();
        xml_fragment_writer
            .write_to(&mut buf)
            .expect("should flush fragments");

        assert!(
            String::from_utf8(buf)
                .expect("should convert to string")
                .starts_with("<gen:GenericLogicalSpace")
        );
    }
}
