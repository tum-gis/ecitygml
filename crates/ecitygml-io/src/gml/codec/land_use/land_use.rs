use crate::Error;
use crate::gml::codec::core::{
    deserialize_abstract_thematic_surface, serialize_abstract_thematic_surface,
    serialize_abstract_thematic_surface_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::core::AsAbstractThematicSurface;
use ecitygml_core::model::land_use::LandUse;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::basic_types::Code;

pub fn deserialize_land_use(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<LandUse, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_thematic_surface =
        deserialize_abstract_thematic_surface(xml_document, index, config)?;

    let mut land_use = LandUse::from_abstract_thematic_surface(abstract_thematic_surface);

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    land_use.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    land_use.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    land_use.set_usages(usages.into_iter().map(Into::into).collect());

    Ok(land_use)
}

pub fn serialize_land_use(
    land_use: &LandUse,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_land_use_attributes(land_use);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::LandUse,
        CityGmlElement::LandUse,
        attributes,
    )?;

    serialize_abstract_thematic_surface(land_use.abstract_thematic_surface(), xml_fragment_writer)?;

    if let Some(class) = land_use.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::LandUse,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in land_use.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::LandUse,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in land_use.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::LandUse,
            CityGmlElement::UsageProperty,
        )?;
    }

    xml_fragment_writer.write_end_event(CityGmlNamespace::LandUse, CityGmlElement::LandUse)?;

    Ok(())
}

pub fn serialize_land_use_attributes(land_use: &LandUse) -> Vec<(String, String)> {
    serialize_abstract_thematic_surface_attributes(land_use.abstract_thematic_surface())
}
