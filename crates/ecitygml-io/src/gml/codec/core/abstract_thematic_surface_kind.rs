use crate::Error;
use crate::gml::codec::construction::{
    deserialize_abstract_construction_surface_kind, deserialize_abstract_filling_surface_kind,
    serialize_abstract_construction_surface_kind, serialize_abstract_filling_surface_kind,
};
use crate::gml::codec::core::closure_surface::{
    deserialize_closure_surface, serialize_closure_surface,
};
use crate::gml::codec::generics::{
    deserialize_generic_thematic_surface, serialize_generic_thematic_surface,
};
use crate::gml::codec::land_use::{deserialize_land_use, serialize_land_use};
use crate::gml::codec::transportation::{
    deserialize_auxiliary_traffic_area, deserialize_hole_surface, deserialize_marking,
    deserialize_traffic_area, serialize_auxiliary_traffic_area, serialize_hole_surface,
    serialize_marking, serialize_traffic_area,
};
use crate::gml::codec::water_body::{
    deserialize_abstract_water_boundary_surface_kind,
    serialize_abstract_water_boundary_surface_kind,
};
use crate::gml::util::{CityGmlElement, CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::core::AbstractThematicSurfaceKind;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_thematic_surface_kind(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Option<AbstractThematicSurfaceKind>, Error> {
    if let Some(index) = index.first(CityGmlElement::AuxiliaryTrafficArea.into()) {
        let auxiliary_traffic_area =
            deserialize_auxiliary_traffic_area(&xml_document[index.range()], index, config)?;
        return Ok(Some(auxiliary_traffic_area.into()));
    }
    if let Some(index) = index.first(CityGmlElement::ClosureSurface.into()) {
        let closure_surface =
            deserialize_closure_surface(&xml_document[index.range()], index, config)?;
        return Ok(Some(closure_surface.into()));
    }
    if let Some(x) = deserialize_abstract_construction_surface_kind(xml_document, index, config)? {
        return Ok(Some(x.into()));
    }
    if let Some(x) = deserialize_abstract_filling_surface_kind(xml_document, index, config)? {
        return Ok(Some(x.into()));
    }
    if let Some(index) = index.first(CityGmlElement::GenericThematicSurface.into()) {
        let generic_thematic_surface =
            deserialize_generic_thematic_surface(&xml_document[index.range()], index, config)?;
        return Ok(Some(generic_thematic_surface.into()));
    }
    if let Some(index) = index.first(CityGmlElement::HoleSurface.into()) {
        let hole_surface = deserialize_hole_surface(&xml_document[index.range()], index, config)?;
        return Ok(Some(hole_surface.into()));
    }
    if let Some(index) = index.first(CityGmlElement::LandUse.into()) {
        let land_use = deserialize_land_use(&xml_document[index.range()], index, config)?;
        return Ok(Some(land_use.into()));
    }
    if let Some(index) = index.first(CityGmlElement::Marking.into()) {
        let marking = deserialize_marking(&xml_document[index.range()], index, config)?;
        return Ok(Some(marking.into()));
    }
    if let Some(index) = index.first(CityGmlElement::TrafficArea.into()) {
        let traffic_area = deserialize_traffic_area(&xml_document[index.range()], index, config)?;
        return Ok(Some(traffic_area.into()));
    }
    if let Some(x) = deserialize_abstract_water_boundary_surface_kind(xml_document, index, config)?
    {
        return Ok(Some(x.into()));
    }

    Ok(None)
}

pub fn serialize_abstract_thematic_surface_kind(
    abstract_thematic_surface_kind: &AbstractThematicSurfaceKind,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    match abstract_thematic_surface_kind {
        AbstractThematicSurfaceKind::AuxiliaryTrafficArea(x) => {
            serialize_auxiliary_traffic_area(x, xml_fragment_writer)
        }
        AbstractThematicSurfaceKind::ClosureSurface(x) => {
            serialize_closure_surface(x, xml_fragment_writer)
        }
        AbstractThematicSurfaceKind::AbstractConstructionSurfaceKind(x) => {
            serialize_abstract_construction_surface_kind(x, xml_fragment_writer)
        }
        AbstractThematicSurfaceKind::AbstractFillingSurfaceKind(x) => {
            serialize_abstract_filling_surface_kind(x, xml_fragment_writer)
        }
        AbstractThematicSurfaceKind::GenericThematicSurface(x) => {
            serialize_generic_thematic_surface(x, xml_fragment_writer)
        }
        AbstractThematicSurfaceKind::HoleSurface(x) => {
            serialize_hole_surface(x, xml_fragment_writer)
        }
        AbstractThematicSurfaceKind::LandUse(x) => serialize_land_use(x, xml_fragment_writer),
        AbstractThematicSurfaceKind::Marking(x) => serialize_marking(x, xml_fragment_writer),
        AbstractThematicSurfaceKind::TrafficArea(x) => {
            serialize_traffic_area(x, xml_fragment_writer)
        }
        AbstractThematicSurfaceKind::AbstractWaterBoundarySurfaceKind(x) => {
            serialize_abstract_water_boundary_surface_kind(x, xml_fragment_writer)
        }
    }
}
