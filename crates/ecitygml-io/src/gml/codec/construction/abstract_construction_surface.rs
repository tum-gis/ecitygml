use crate::Error;
use crate::gml::codec::construction::abstract_filling_surface_property::{
    deserialize_abstract_filling_surface_property, serialize_abstract_filling_surface_property,
};
use crate::gml::codec::core::{
    deserialize_abstract_thematic_surface, serialize_abstract_thematic_surface,
    serialize_abstract_thematic_surface_attributes,
};
use crate::gml::util::{CityGmlElement, CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::construction::{
    AbstractConstructionSurface, AsAbstractConstructionSurface, AsAbstractConstructionSurfaceMut,
};
use ecitygml_core::model::core::AsAbstractThematicSurface;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter, collect_children};

pub fn deserialize_abstract_construction_surface(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractConstructionSurface, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_construction_surface received a truncated index — caller must scan to sufficient depth"
    );

    let (abstract_thematic_surface_result, filling_surfaces_result) = rayon::join(
        || deserialize_abstract_thematic_surface(xml_document, index, config),
        || {
            collect_children(
                xml_document,
                index,
                CityGmlElement::AbstractFillingSurfaceProperty.into(),
                config,
                deserialize_abstract_filling_surface_property,
            )
        },
    );
    let abstract_thematic_surface = abstract_thematic_surface_result?;
    let filling_surfaces = filling_surfaces_result?;

    let mut abstract_construction_surface =
        AbstractConstructionSurface::from_abstract_thematic_surface(abstract_thematic_surface);
    abstract_construction_surface.set_filling_surfaces(filling_surfaces);

    Ok(abstract_construction_surface)
}

pub fn serialize_abstract_construction_surface(
    abstract_construction_surface: &AbstractConstructionSurface,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_thematic_surface(
        abstract_construction_surface.abstract_thematic_surface(),
        xml_fragment_writer,
    )?;

    for prop in abstract_construction_surface.filling_surfaces() {
        serialize_abstract_filling_surface_property(prop, xml_fragment_writer)?;
    }

    Ok(())
}

pub fn serialize_abstract_construction_surface_attributes(
    abstract_construction_surface: &AbstractConstructionSurface,
) -> Vec<(String, String)> {
    serialize_abstract_thematic_surface_attributes(
        abstract_construction_surface.abstract_thematic_surface(),
    )
}
