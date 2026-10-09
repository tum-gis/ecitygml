use crate::Error;
use crate::gml::codec::construction::abstract_construction_surface::{
    deserialize_abstract_construction_surface, serialize_abstract_construction_surface,
    serialize_abstract_construction_surface_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::construction::{AsAbstractConstructionSurface, RoofSurface};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_roof_surface(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<RoofSurface, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_construction_surface =
        deserialize_abstract_construction_surface(xml_document, index, config)?;
    let roof_surface =
        RoofSurface::from_abstract_construction_surface(abstract_construction_surface);

    Ok(roof_surface)
}

pub fn serialize_roof_surface(
    roof_surface: &RoofSurface,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_roof_surface_attributes(roof_surface);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Construction,
        CityGmlElement::RoofSurface,
        attributes,
    )?;

    serialize_abstract_construction_surface(
        roof_surface.abstract_construction_surface(),
        xml_fragment_writer,
    )?;

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::Construction, CityGmlElement::RoofSurface)?;

    Ok(())
}

pub fn serialize_roof_surface_attributes(roof_surface: &RoofSurface) -> Vec<(String, String)> {
    serialize_abstract_construction_surface_attributes(roof_surface.abstract_construction_surface())
}
