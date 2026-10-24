use crate::Error;
use crate::gml::codec::city_object_group::role::{
    deserialize_role_property, serialize_role_property,
};
use crate::gml::codec::core::{
    deserialize_abstract_logical_space, serialize_abstract_logical_space,
    serialize_abstract_logical_space_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::city_object_group::{CityObjectGroup, Role};
use ecitygml_core::model::core::AsAbstractLogicalSpace;
use egml::io::codec::base::{deserialize_reference, serialize_reference};
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::collect_children;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::base::Reference;
use egml::model::basic_types::Code;
use rayon::iter::IntoParallelRefIterator;
use rayon::iter::ParallelIterator;

pub fn deserialize_city_object_group(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<CityObjectGroup, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_logical_space = deserialize_abstract_logical_space(xml_document, index, config)?;
    let mut city_object_group =
        CityObjectGroup::from_abstract_logical_space(abstract_logical_space);

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    city_object_group.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    city_object_group.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    city_object_group.set_usages(usages.into_iter().map(Into::into).collect());

    let parent = index
        .first(CityGmlElement::ParentProperty.into())
        .map(|x| deserialize_reference(&xml_document[x.range()]))
        .transpose()?;
    city_object_group.set_parent_opt(parent.map(Into::into));

    let group_members: Vec<Role> = collect_children(
        xml_document,
        index,
        CityGmlElement::GroupMemberProperty.into(),
        config,
        deserialize_role_property,
    )?;
    city_object_group.set_group_members(group_members);

    Ok(city_object_group)
}

pub fn serialize_city_object_group(
    city_object_group: &CityObjectGroup,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_city_object_group_attributes(city_object_group);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::CityObjectGroup,
        CityGmlElement::CityObjectGroup,
        attributes,
    )?;

    serialize_abstract_logical_space(
        city_object_group.abstract_logical_space(),
        xml_fragment_writer,
    )?;

    if let Some(class) = city_object_group.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::CityObjectGroup,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in city_object_group.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::CityObjectGroup,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in city_object_group.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::CityObjectGroup,
            CityGmlElement::UsageProperty,
        )?;
    }

    if let Some(parent) = city_object_group.parent() {
        serialize_reference(
            &Reference::from(parent),
            xml_fragment_writer,
            CityGmlNamespace::CityObjectGroup,
            CityGmlElement::ParentProperty,
        )?;
    }

    let child_writers = city_object_group
        .group_members()
        .par_iter()
        .map(|x| {
            let mut xml_fragment_writer = xml_fragment_writer.spawn_child();
            serialize_role_property(x, &mut xml_fragment_writer)?;
            Ok(xml_fragment_writer)
        })
        .collect::<Result<Vec<_>, Error>>()?;
    for current_child_writer in child_writers {
        xml_fragment_writer.merge_chunked(current_child_writer);
    }

    xml_fragment_writer.write_end_event(
        CityGmlNamespace::CityObjectGroup,
        CityGmlElement::CityObjectGroup,
    )?;

    Ok(())
}

pub fn serialize_city_object_group_attributes(
    city_object_group: &CityObjectGroup,
) -> Vec<(String, String)> {
    serialize_abstract_logical_space_attributes(city_object_group.abstract_logical_space())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::core::AsAbstractFeature;
    use egml::io::util::Formatting;
    use egml::model::base::{AsAbstractGml, HasAssociationAttributes, Id};
    use egml::model::xlink::HRef;

    #[test]
    fn test_deserialize_basic_city_object_group() {
        let xml_document =
            b"<grp:CityObjectGroup gml:id=\"UUID_f488e8ce-b953-4b35-a3fe-a394fb203868\">
      <gml:description>CityObjectGroup for grouping the trees to a forest</gml:description>
      <gml:name>Forest KIT</gml:name>
      <creationDate>2015-03-06T00:00:00+01:00</creationDate>
      <grp:groupMember>
        <grp:Role>
          <grp:groupMember xlink:href=\"#GMLID_SO0286258_965_2893\"/>
        </grp:Role>
      </grp:groupMember>
      <grp:groupMember>
        <grp:Role>
          <grp:groupMember xlink:href=\"#GMLID_SO0124800_3522_13577\"/>
        </grp:Role>
      </grp:groupMember>
      <grp:groupMember>
        <grp:Role>
          <grp:groupMember xlink:href=\"#GMLID_SO0443764_1492_9667\"/>
        </grp:Role>
      </grp:groupMember>
      <grp:groupMember>
        <grp:Role>
          <grp:groupMember xlink:href=\"#GMLID_SO0107241_3793_12555\"/>
        </grp:Role>
      </grp:groupMember>
      <grp:groupMember>
        <grp:Role>
          <grp:groupMember xlink:href=\"#GMLID_SO0158953_776_12462\"/>
        </grp:Role>
      </grp:groupMember>
      <grp:groupMember>
        <grp:Role>
          <grp:groupMember xlink:href=\"#GMLID_SO0410128_214_10515\"/>
        </grp:Role>
      </grp:groupMember>
      <grp:groupMember>
        <grp:Role>
          <grp:groupMember xlink:href=\"#GMLID_SO086970_1053_8814\"/>
        </grp:Role>
      </grp:groupMember>
      <grp:groupMember>
        <grp:Role>
          <grp:groupMember xlink:href=\"#GMLID_SO0200811_525_4986\"/>
        </grp:Role>
      </grp:groupMember>
      <grp:groupMember>
        <grp:Role>
          <grp:groupMember xlink:href=\"#GMLID_SO081792_2341_11961\"/>
        </grp:Role>
      </grp:groupMember>
      <grp:groupMember>
        <grp:Role>
          <grp:groupMember xlink:href=\"#GMLID_SO015374_872_14131\"/>
        </grp:Role>
      </grp:groupMember>
      <grp:groupMember>
        <grp:Role>
          <grp:groupMember xlink:href=\"#GMLID_SO0400934_2926_3381\"/>
        </grp:Role>
      </grp:groupMember>
      <grp:groupMember>
        <grp:Role>
          <grp:groupMember xlink:href=\"#GMLID_SO0260143_1214_1315\"/>
        </grp:Role>
      </grp:groupMember>
      <grp:groupMember>
        <grp:Role>
          <grp:role>Parent</grp:role>
          <grp:groupMember xlink:href=\"#GMLID_SO0321978_1466_7441\"/>
        </grp:Role>
      </grp:groupMember>
      <grp:groupMember>
        <grp:Role>
          <grp:groupMember xlink:href=\"#GMLID_SO0283142_1335_8999\"/>
        </grp:Role>
      </grp:groupMember>
    </grp:CityObjectGroup>";

        let city_object_group = deserialize_city_object_group(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            city_object_group.feature_id(),
            &Id::try_from("UUID_f488e8ce-b953-4b35-a3fe-a394fb203868").expect("should work")
        );
        assert_eq!(
            city_object_group.names().first().expect("should work"),
            &Code::new("Forest KIT")
        );
        assert!(city_object_group.class().is_none());
        assert!(city_object_group.functions().is_empty());
        assert!(city_object_group.usages().is_empty());

        assert_eq!(city_object_group.group_members().len(), 14);
        assert_eq!(
            city_object_group
                .group_members()
                .iter()
                .filter_map(|role| role.role())
                .collect::<Vec<_>>(),
            vec!["Parent"]
        );
        assert_eq!(
            Reference::from(city_object_group.group_members()[0].group_member()).href(),
            Some(&HRef::from("#GMLID_SO0286258_965_2893"))
        );
        assert!(city_object_group.parent().is_none());
    }

    #[test]
    fn test_deserialize_city_object_group_with_parent() {
        let xml_document =
            b"<grp:CityObjectGroup gml:id=\"UUID_f488e8ce-b953-4b35-a3fe-a394fb203868\">
      <grp:groupMember>
        <grp:Role>
          <grp:groupMember xlink:href=\"#GMLID_SO0286258_965_2893\"/>
        </grp:Role>
      </grp:groupMember>
      <grp:parent xlink:href=\"#GMLID_BUILDING_1\"/>
    </grp:CityObjectGroup>";

        let city_object_group = deserialize_city_object_group(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(city_object_group.group_members().len(), 1);
        assert_eq!(
            Reference::from(city_object_group.parent().expect("should have a parent")).href(),
            Some(&HRef::from("#GMLID_BUILDING_1"))
        );
    }

    #[test]
    fn test_round_trip_city_object_group_with_group_members() {
        use egml::model::base::Id;

        let mut city_object_group = CityObjectGroup::new(
            Id::try_from("UUID_f488e8ce-b953-4b35-a3fe-a394fb203868").expect("should work"),
        );

        let mut role_with_value =
            Role::new(Reference::new(HRef::from("#GMLID_SO0286258_965_2893")).into());
        role_with_value.set_role("Parent".to_string());
        city_object_group.push_group_member(role_with_value);
        city_object_group.push_group_member(Role::new(
            Reference::new(HRef::from("#GMLID_SO0124800_3522_13577")).into(),
        ));
        city_object_group.set_parent(Reference::new(HRef::from("#GMLID_BUILDING_1")).into());

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_city_object_group(&city_object_group, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should render");

        let round_tripped = deserialize_city_object_group(
            xml.as_bytes(),
            &XmlDocumentIndex::from_scan(xml.as_bytes(), None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should round trip");

        assert_eq!(round_tripped.group_members().len(), 2);
        assert_eq!(round_tripped.group_members()[0].role(), Some("Parent"));
        assert_eq!(round_tripped.group_members()[1].role(), None);
        assert_eq!(
            round_tripped.group_members(),
            city_object_group.group_members()
        );
        assert_eq!(round_tripped.parent(), city_object_group.parent());
    }
}
