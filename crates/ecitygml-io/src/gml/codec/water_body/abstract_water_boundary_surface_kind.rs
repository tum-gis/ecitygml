use crate::Error;
use crate::gml::codec::water_body::{
    deserialize_water_ground_surface, deserialize_water_surface, serialize_water_ground_surface,
    serialize_water_surface,
};
use crate::gml::util::{CityGmlElement, CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::water_body::AbstractWaterBoundarySurfaceKind;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_water_boundary_surface_kind(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Option<AbstractWaterBoundarySurfaceKind>, Error> {
    if let Some(index) = index.first(CityGmlElement::WaterGroundSurface.into()) {
        let water_ground_surface =
            deserialize_water_ground_surface(&xml_document[index.range()], index, config)?;
        return Ok(Some(water_ground_surface.into()));
    }
    if let Some(index) = index.first(CityGmlElement::WaterSurface.into()) {
        let water_surface = deserialize_water_surface(&xml_document[index.range()], index, config)?;
        return Ok(Some(water_surface.into()));
    }

    Ok(None)
}

pub fn serialize_abstract_water_boundary_surface_kind(
    abstract_water_boundary_surface_kind: &AbstractWaterBoundarySurfaceKind,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    match abstract_water_boundary_surface_kind {
        AbstractWaterBoundarySurfaceKind::WaterGroundSurface(x) => {
            serialize_water_ground_surface(x, xml_fragment_writer)
        }
        AbstractWaterBoundarySurfaceKind::WaterSurface(x) => {
            serialize_water_surface(x, xml_fragment_writer)
        }
    }
}
