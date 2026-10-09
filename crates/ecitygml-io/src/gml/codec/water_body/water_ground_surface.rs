use crate::Error;
use crate::gml::codec::water_body::abstract_water_boundary_surface::{
    deserialize_abstract_water_boundary_surface, serialize_abstract_water_boundary_surface,
    serialize_abstract_water_boundary_surface_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::water_body::{AsAbstractWaterBoundarySurface, WaterGroundSurface};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_water_ground_surface(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<WaterGroundSurface, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_water_boundary_surface =
        deserialize_abstract_water_boundary_surface(xml_document, index, config)?;
    let water_ground_surface =
        WaterGroundSurface::from_abstract_water_boundary_surface(abstract_water_boundary_surface);

    Ok(water_ground_surface)
}

pub fn serialize_water_ground_surface(
    water_ground_surface: &WaterGroundSurface,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_water_ground_surface_attributes(water_ground_surface);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::WaterBody,
        CityGmlElement::WaterGroundSurface,
        attributes,
    )?;

    serialize_abstract_water_boundary_surface(
        water_ground_surface.abstract_water_boundary_surface(),
        xml_fragment_writer,
    )?;

    xml_fragment_writer.write_end_event(
        CityGmlNamespace::WaterBody,
        CityGmlElement::WaterGroundSurface,
    )?;

    Ok(())
}

pub fn serialize_water_ground_surface_attributes(
    water_ground_surface: &WaterGroundSurface,
) -> Vec<(String, String)> {
    serialize_abstract_water_boundary_surface_attributes(
        water_ground_surface.abstract_water_boundary_surface(),
    )
}
