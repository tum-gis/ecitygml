use crate::Error;
use crate::gml::codec::appearance::abstract_texture_kind::{
    deserialize_abstract_texture_kind, serialize_abstract_texture_kind,
};
use crate::gml::codec::appearance::x3d_material::{
    deserialize_x3d_material, serialize_x3d_material,
};
use crate::gml::util::{CityGmlElement, CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::appearance::AbstractSurfaceDataKind;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_surface_data_kind(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Option<AbstractSurfaceDataKind>, Error> {
    if let Some(x) = deserialize_abstract_texture_kind(xml_document, index, config)? {
        return Ok(Some(x.into()));
    }
    if let Some(index) = index.first(CityGmlElement::X3DMaterial.into()) {
        let x3d_material = deserialize_x3d_material(&xml_document[index.range()], index, config)?;
        return Ok(Some(x3d_material.into()));
    }

    Ok(None)
}

pub fn serialize_abstract_surface_data_kind(
    abstract_surface_data_kind: &AbstractSurfaceDataKind,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    match abstract_surface_data_kind {
        AbstractSurfaceDataKind::AbstractTextureKind(x) => {
            serialize_abstract_texture_kind(x, xml_fragment_writer)
        }
        AbstractSurfaceDataKind::X3DMaterial(x) => serialize_x3d_material(x, xml_fragment_writer),
    }
}
