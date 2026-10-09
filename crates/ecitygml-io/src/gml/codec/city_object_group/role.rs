use crate::Error;
use crate::gml::codec::common::{deserialize_string, serialize_string};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::city_object_group::Role;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter, XmlNamespaceContext};

pub fn deserialize_role(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Role, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let mut role = Role::new();

    let value = index
        .first(CityGmlElement::RoleProperty.into())
        .map(|x| deserialize_string(&xml_document[x.range()]))
        .transpose()?;
    role.set_role_opt(value);

    Ok(role)
}

pub fn serialize_role(
    role: &Role,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    xml_fragment_writer
        .write_start_event(CityGmlNamespace::CityObjectGroup, CityGmlElement::Role)?;

    if let Some(value) = role.role() {
        serialize_string(
            value,
            xml_fragment_writer,
            CityGmlNamespace::CityObjectGroup,
            CityGmlElement::RoleProperty,
        )?;
    }

    xml_fragment_writer.write_end_event(CityGmlNamespace::CityObjectGroup, CityGmlElement::Role)?;

    Ok(())
}

pub fn deserialize_role_property(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Role, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let index = index.first(CityGmlElement::Role.into()).ok_or_else(|| {
        Error::ElementNotFound(
            XmlNamespaceContext::default()
                .qualify(CityGmlNamespace::CityObjectGroup, CityGmlElement::Role)
                .to_string(),
        )
    })?;

    deserialize_role(&xml_document[index.range()], index, config)
}

pub fn serialize_role_property(
    role: &Role,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    xml_fragment_writer.write_start_event(
        CityGmlNamespace::CityObjectGroup,
        CityGmlElement::GroupMemberProperty,
    )?;

    serialize_role(role, xml_fragment_writer)?;

    xml_fragment_writer.write_end_event(
        CityGmlNamespace::CityObjectGroup,
        CityGmlElement::GroupMemberProperty,
    )?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::{Formatting, XmlDocumentIndex};

    #[test]
    fn test_deserialize_role_with_role_value() {
        let xml_document = b"<grp:Role>
      <grp:role>Parent</grp:role>
      <grp:groupMember xlink:href=\"#GMLID_SO0286258_965_2893\"/>
    </grp:Role>";

        let role = deserialize_role(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(role.role(), Some("Parent"));
    }

    #[test]
    fn test_deserialize_role_without_role_value() {
        let xml_document = b"<grp:Role>
      <grp:groupMember xlink:href=\"#GMLID_SO0286258_965_2893\"/>
    </grp:Role>";

        let role = deserialize_role(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert!(role.role().is_none());
    }

    #[test]
    fn test_deserialize_role_property() {
        let xml_document = b"<grp:groupMember>
    <grp:Role>
      <grp:role>Parent</grp:role>
      <grp:groupMember xlink:href=\"#GMLID_SO0286258_965_2893\"/>
    </grp:Role>
  </grp:groupMember>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let role =
            deserialize_role_property(xml_document, &index, &DeserializationConfig::default())
                .expect("should work");

        assert_eq!(role.role(), Some("Parent"));
    }

    #[test]
    fn test_round_trip_role() {
        let mut role = Role::new();
        role.set_role("Parent".to_string());

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_role(&role, &mut xml_fragment_writer).expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        let round_tripped = deserialize_role(
            xml.as_bytes(),
            &XmlDocumentIndex::from_scan(xml.as_bytes(), None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should round trip");

        assert_eq!(role, round_tripped);
    }
}
