use crate::Error;
use crate::gml::codec::construction::{
    deserialize_abstract_furniture, serialize_abstract_furniture,
    serialize_abstract_furniture_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::building::BuildingFurniture;
use ecitygml_core::model::construction::AsAbstractFurniture;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::basic_types::Code;

pub fn deserialize_building_furniture(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<BuildingFurniture, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_furniture = deserialize_abstract_furniture(xml_document, index, config)?;
    let mut building_furniture = BuildingFurniture::from_abstract_furniture(abstract_furniture);

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    building_furniture.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    building_furniture.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    building_furniture.set_usages(usages.into_iter().map(Into::into).collect());

    Ok(building_furniture)
}

pub fn serialize_building_furniture(
    building_furniture: &BuildingFurniture,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_building_furniture_attributes(building_furniture);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Building,
        CityGmlElement::BuildingFurniture,
        attributes,
    )?;

    serialize_abstract_furniture(building_furniture.abstract_furniture(), xml_fragment_writer)?;

    if let Some(class) = building_furniture.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in building_furniture.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in building_furniture.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::UsageProperty,
        )?;
    }

    xml_fragment_writer.write_end_event(
        CityGmlNamespace::Building,
        CityGmlElement::BuildingFurniture,
    )?;

    Ok(())
}

pub fn serialize_building_furniture_attributes(
    building_furniture: &BuildingFurniture,
) -> Vec<(String, String)> {
    serialize_abstract_furniture_attributes(building_furniture.abstract_furniture())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::core::AsAbstractFeature;
    use egml::io::util::Formatting;
    use egml::model::base::{AsAbstractGml, Id};

    fn deserialize(xml_document: &[u8]) -> BuildingFurniture {
        deserialize_building_furniture(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work")
    }

    #[test]
    fn test_deserialize_building_furniture() {
        let xml_document = b"<bldg:BuildingFurniture gml:id=\"BF_1\">
      <gml:name>Bench</gml:name>
      <bldg:class>7000</bldg:class>
      <bldg:function>7010</bldg:function>
      <bldg:function>7020</bldg:function>
      <bldg:usage>8000</bldg:usage>
    </bldg:BuildingFurniture>";

        let building_furniture = deserialize(xml_document);

        assert_eq!(
            building_furniture.feature_id(),
            &Id::try_from("BF_1").expect("should work")
        );
        assert_eq!(
            building_furniture
                .names()
                .first()
                .expect("should have a name"),
            &Code::new("Bench")
        );
        assert_eq!(
            building_furniture.class().map(|x| x.code().value()),
            Some("7000")
        );
        assert_eq!(
            building_furniture
                .functions()
                .iter()
                .map(|x| x.code().value())
                .collect::<Vec<_>>(),
            vec!["7010", "7020"]
        );
        assert_eq!(
            building_furniture
                .usages()
                .iter()
                .map(|x| x.code().value())
                .collect::<Vec<_>>(),
            vec!["8000"]
        );
    }

    #[test]
    fn test_deserialize_building_furniture_without_codes() {
        let building_furniture = deserialize(b"<bldg:BuildingFurniture gml:id=\"BF_1\"/>");

        assert!(building_furniture.class().is_none());
        assert!(building_furniture.functions().is_empty());
        assert!(building_furniture.usages().is_empty());
    }

    #[test]
    fn test_round_trip_building_furniture() {
        let mut building_furniture =
            BuildingFurniture::new(Id::try_from("BF_1").expect("should work"));
        building_furniture.set_class(Code::new("7000").into());
        building_furniture.push_function(Code::new("7010").into());
        building_furniture.push_usage(Code::new("8000").into());

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_building_furniture(&building_furniture, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");
        assert!(xml.starts_with("<bldg:BuildingFurniture"));

        assert_eq!(deserialize(xml.as_bytes()), building_furniture);
    }
}
