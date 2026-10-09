use crate::Error;
use crate::gml::codec::core::{
    deserialize_abstract_occupied_space, serialize_abstract_occupied_space,
    serialize_abstract_occupied_space_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::core::AsAbstractOccupiedSpace;
use ecitygml_core::model::water_body::WaterBody;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::basic_types::Code;

pub fn deserialize_water_body(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<WaterBody, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_occupied_space = deserialize_abstract_occupied_space(xml_document, index, config)?;
    let mut water_body = WaterBody::from_abstract_occupied_space(abstract_occupied_space);

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    water_body.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    water_body.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    water_body.set_usages(usages.into_iter().map(Into::into).collect());

    Ok(water_body)
}

pub fn serialize_water_body(
    water_body: &WaterBody,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_water_body_attributes(water_body);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::WaterBody,
        CityGmlElement::WaterBody,
        attributes,
    )?;

    serialize_abstract_occupied_space(water_body.abstract_occupied_space(), xml_fragment_writer)?;

    if let Some(class) = water_body.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::WaterBody,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in water_body.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::WaterBody,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in water_body.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::WaterBody,
            CityGmlElement::UsageProperty,
        )?;
    }

    xml_fragment_writer.write_end_event(CityGmlNamespace::WaterBody, CityGmlElement::WaterBody)?;

    Ok(())
}

pub fn serialize_water_body_attributes(water_body: &WaterBody) -> Vec<(String, String)> {
    serialize_abstract_occupied_space_attributes(water_body.abstract_occupied_space())
}
