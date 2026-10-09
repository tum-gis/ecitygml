use crate::Error;
use crate::gml::codec::building::serialize_building_constructive_element_property;
use crate::gml::codec::core::{
    deserialize_abstract_logical_space, serialize_abstract_logical_space,
    serialize_abstract_logical_space_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::building::{
    AbstractBuildingSubdivision, AsAbstractBuildingSubdivision, AsAbstractBuildingSubdivisionMut,
};
use ecitygml_core::model::core::AsAbstractLogicalSpace;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::basic_types::Code;

pub fn deserialize_abstract_building_subdivision(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractBuildingSubdivision, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_building_subdivision received a truncated index — caller must scan to sufficient depth"
    );

    let abstract_logical_space = deserialize_abstract_logical_space(xml_document, index, config)?;
    let mut abstract_building_subdivision =
        AbstractBuildingSubdivision::from_abstract_logical_space(abstract_logical_space);

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    abstract_building_subdivision.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    abstract_building_subdivision.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    abstract_building_subdivision.set_usages(usages.into_iter().map(Into::into).collect());

    Ok(abstract_building_subdivision)
}

pub fn serialize_abstract_building_subdivision(
    abstract_building_subdivision: &AbstractBuildingSubdivision,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_logical_space(
        abstract_building_subdivision.abstract_logical_space(),
        xml_fragment_writer,
    )?;

    if let Some(class) = abstract_building_subdivision.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in abstract_building_subdivision.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in abstract_building_subdivision.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::UsageProperty,
        )?;
    }

    for prop in abstract_building_subdivision.building_constructive_elements() {
        serialize_building_constructive_element_property(prop, xml_fragment_writer)?;
    }

    Ok(())
}

pub fn serialize_abstract_building_subdivision_attributes(
    abstract_building_subdivision: &AbstractBuildingSubdivision,
) -> Vec<(String, String)> {
    serialize_abstract_logical_space_attributes(
        abstract_building_subdivision.abstract_logical_space(),
    )
}
