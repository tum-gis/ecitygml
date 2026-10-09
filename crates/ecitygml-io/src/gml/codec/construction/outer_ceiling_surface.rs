use crate::Error;
use crate::gml::codec::construction::abstract_construction_surface::{
    deserialize_abstract_construction_surface, serialize_abstract_construction_surface,
    serialize_abstract_construction_surface_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::construction::{AsAbstractConstructionSurface, OuterCeilingSurface};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_outer_ceiling_surface(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<OuterCeilingSurface, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_construction_surface =
        deserialize_abstract_construction_surface(xml_document, index, config)?;
    Ok(OuterCeilingSurface::from_abstract_construction_surface(
        abstract_construction_surface,
    ))
}

pub fn serialize_outer_ceiling_surface(
    outer_ceiling_surface: &OuterCeilingSurface,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_outer_ceiling_surface_attributes(outer_ceiling_surface);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Construction,
        CityGmlElement::OuterCeilingSurface,
        attributes,
    )?;

    serialize_abstract_construction_surface(
        outer_ceiling_surface.abstract_construction_surface(),
        xml_fragment_writer,
    )?;

    xml_fragment_writer.write_end_event(
        CityGmlNamespace::Construction,
        CityGmlElement::OuterCeilingSurface,
    )?;

    Ok(())
}

pub fn serialize_outer_ceiling_surface_attributes(
    outer_ceiling_surface: &OuterCeilingSurface,
) -> Vec<(String, String)> {
    serialize_abstract_construction_surface_attributes(
        outer_ceiling_surface.abstract_construction_surface(),
    )
}
