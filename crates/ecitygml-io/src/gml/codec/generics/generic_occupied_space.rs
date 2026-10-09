use crate::Error;
use crate::gml::codec::core::{
    deserialize_abstract_occupied_space, serialize_abstract_occupied_space,
    serialize_abstract_occupied_space_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::core::AsAbstractOccupiedSpace;
use ecitygml_core::model::generics::GenericOccupiedSpace;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::basic_types::Code;

pub fn deserialize_generic_occupied_space(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<GenericOccupiedSpace, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_occupied_space = deserialize_abstract_occupied_space(xml_document, index, config)?;

    let mut generic_occupied_space =
        GenericOccupiedSpace::from_abstract_occupied_space(abstract_occupied_space);

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    generic_occupied_space.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    generic_occupied_space.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    generic_occupied_space.set_usages(usages.into_iter().map(Into::into).collect());

    Ok(generic_occupied_space)
}

pub fn serialize_generic_occupied_space(
    generic_occupied_space: &GenericOccupiedSpace,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_generic_occupied_space_attributes(generic_occupied_space);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Generics,
        CityGmlElement::GenericOccupiedSpace,
        attributes,
    )?;

    serialize_abstract_occupied_space(
        generic_occupied_space.abstract_occupied_space(),
        xml_fragment_writer,
    )?;

    if let Some(class) = generic_occupied_space.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Generics,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in generic_occupied_space.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::Generics,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in generic_occupied_space.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::Generics,
            CityGmlElement::UsageProperty,
        )?;
    }

    xml_fragment_writer.write_end_event(
        CityGmlNamespace::Generics,
        CityGmlElement::GenericOccupiedSpace,
    )?;

    Ok(())
}

pub fn serialize_generic_occupied_space_attributes(
    generic_occupied_space: &GenericOccupiedSpace,
) -> Vec<(String, String)> {
    serialize_abstract_occupied_space_attributes(generic_occupied_space.abstract_occupied_space())
}
