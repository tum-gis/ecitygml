use crate::Error;
use crate::gml::codec::construction::{
    deserialize_abstract_installation, serialize_abstract_installation,
    serialize_abstract_installation_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::building::BuildingInstallation;
use ecitygml_core::model::construction::AsAbstractInstallation;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::basic_types::Code;

pub fn deserialize_building_installation(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<BuildingInstallation, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_installation = deserialize_abstract_installation(xml_document, index, config)?;
    let mut building_installation =
        BuildingInstallation::from_abstract_installation(abstract_installation);

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    building_installation.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    building_installation.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    building_installation.set_usages(usages.into_iter().map(Into::into).collect());

    Ok(building_installation)
}

pub fn serialize_building_installation(
    building_installation: &BuildingInstallation,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_building_installation_attributes(building_installation);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Building,
        CityGmlElement::BuildingInstallation,
        attributes,
    )?;

    serialize_abstract_installation(
        building_installation.abstract_installation(),
        xml_fragment_writer,
    )?;

    if let Some(class) = building_installation.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in building_installation.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in building_installation.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::UsageProperty,
        )?;
    }

    xml_fragment_writer.write_end_event(
        CityGmlNamespace::Building,
        CityGmlElement::BuildingInstallation,
    )?;

    Ok(())
}

pub fn serialize_building_installation_attributes(
    building_installation: &BuildingInstallation,
) -> Vec<(String, String)> {
    serialize_abstract_installation_attributes(building_installation.abstract_installation())
}
