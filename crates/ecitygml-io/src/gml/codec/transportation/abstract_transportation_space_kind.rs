use crate::Error;
use crate::gml::codec::transportation::{
    deserialize_intersection, deserialize_railway, deserialize_road, deserialize_section,
    deserialize_square, deserialize_track, deserialize_waterway, serialize_intersection,
    serialize_railway, serialize_road, serialize_section, serialize_square, serialize_track,
    serialize_waterway,
};
use crate::gml::util::{CityGmlElement, CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::transportation::AbstractTransportationSpaceKind;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_transportation_space_kind(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Option<AbstractTransportationSpaceKind>, Error> {
    if let Some(index) = index.first(CityGmlElement::Section.into()) {
        let section = deserialize_section(&xml_document[index.range()], index, config)?;
        return Ok(Some(section.into()));
    }

    if let Some(index) = index.first(CityGmlElement::Intersection.into()) {
        let intersection = deserialize_intersection(&xml_document[index.range()], index, config)?;
        return Ok(Some(intersection.into()));
    }

    if let Some(index) = index.first(CityGmlElement::Road.into()) {
        let road = deserialize_road(&xml_document[index.range()], index, config)?;
        return Ok(Some(road.into()));
    }

    if let Some(index) = index.first(CityGmlElement::Track.into()) {
        let track = deserialize_track(&xml_document[index.range()], index, config)?;
        return Ok(Some(track.into()));
    }

    if let Some(index) = index.first(CityGmlElement::Railway.into()) {
        let railway = deserialize_railway(&xml_document[index.range()], index, config)?;
        return Ok(Some(railway.into()));
    }

    if let Some(index) = index.first(CityGmlElement::Waterway.into()) {
        let waterway = deserialize_waterway(&xml_document[index.range()], index, config)?;
        return Ok(Some(waterway.into()));
    }

    if let Some(index) = index.first(CityGmlElement::Square.into()) {
        let square = deserialize_square(&xml_document[index.range()], index, config)?;
        return Ok(Some(square.into()));
    }

    Ok(None)
}

pub fn serialize_abstract_transportation_space_kind(
    abstract_transportation_space_kind: &AbstractTransportationSpaceKind,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    match abstract_transportation_space_kind {
        AbstractTransportationSpaceKind::Section(x) => serialize_section(x, xml_fragment_writer),
        AbstractTransportationSpaceKind::Intersection(x) => {
            serialize_intersection(x, xml_fragment_writer)
        }
        AbstractTransportationSpaceKind::Road(x) => serialize_road(x, xml_fragment_writer),
        AbstractTransportationSpaceKind::Track(x) => serialize_track(x, xml_fragment_writer),
        AbstractTransportationSpaceKind::Railway(x) => serialize_railway(x, xml_fragment_writer),
        AbstractTransportationSpaceKind::Waterway(x) => serialize_waterway(x, xml_fragment_writer),
        AbstractTransportationSpaceKind::Square(x) => serialize_square(x, xml_fragment_writer),
    }
}
