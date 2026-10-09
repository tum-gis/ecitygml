use crate::Error;
use crate::gml::codec::core::{
    deserialize_abstract_thematic_surface, serialize_abstract_thematic_surface,
    serialize_abstract_thematic_surface_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::core::AsAbstractThematicSurface;
use ecitygml_core::model::generics::GenericThematicSurface;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::basic_types::Code;

pub fn deserialize_generic_thematic_surface(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<GenericThematicSurface, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_thematic_surface =
        deserialize_abstract_thematic_surface(xml_document, index, config)?;

    let mut generic_thematic_surface =
        GenericThematicSurface::from_abstract_thematic_surface(abstract_thematic_surface);

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    generic_thematic_surface.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    generic_thematic_surface.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    generic_thematic_surface.set_usages(usages.into_iter().map(Into::into).collect());

    Ok(generic_thematic_surface)
}

pub fn serialize_generic_thematic_surface(
    generic_thematic_surface: &GenericThematicSurface,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_generic_thematic_surface_attributes(generic_thematic_surface);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Generics,
        CityGmlElement::GenericThematicSurface,
        attributes,
    )?;

    serialize_abstract_thematic_surface(
        generic_thematic_surface.abstract_thematic_surface(),
        xml_fragment_writer,
    )?;

    if let Some(class) = generic_thematic_surface.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Generics,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in generic_thematic_surface.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::Generics,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in generic_thematic_surface.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::Generics,
            CityGmlElement::UsageProperty,
        )?;
    }

    xml_fragment_writer.write_end_event(
        CityGmlNamespace::Generics,
        CityGmlElement::GenericThematicSurface,
    )?;

    Ok(())
}

pub fn serialize_generic_thematic_surface_attributes(
    generic_thematic_surface: &GenericThematicSurface,
) -> Vec<(String, String)> {
    serialize_abstract_thematic_surface_attributes(
        generic_thematic_surface.abstract_thematic_surface(),
    )
}
