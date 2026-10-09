use crate::Error;
use crate::gml::codec::core::abstract_point_cloud_property::{
    deserialize_abstract_point_cloud_property, serialize_abstract_point_cloud_property,
};
use crate::gml::codec::core::{
    deserialize_abstract_space, serialize_abstract_space, serialize_abstract_space_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
    collect_gml_child_lenient,
};
use ecitygml_core::model::core::{
    AbstractPhysicalSpace, AsAbstractPhysicalSpace, AsAbstractPhysicalSpaceMut, AsAbstractSpace,
};
use egml::io::codec::geometry::aggregates::{
    deserialize_multi_curve_property, serialize_multi_curve_property,
};
use egml::io::util::{ChunkedSink, collect_child};
use egml::io::util::{XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_physical_space(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractPhysicalSpace, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_physical_space received a truncated index — caller must scan to sufficient depth"
    );

    let mut abstract_space_result = None;
    let mut lod1_terrain_intersection_curve_result = None;
    let mut lod2_terrain_intersection_curve_result = None;
    let mut lod3_terrain_intersection_curve_result = None;
    let mut point_cloud_result = None;

    rayon::scope(|s| {
        s.spawn(|_| {
            abstract_space_result = Some(deserialize_abstract_space(xml_document, index, config));
        });
        s.spawn(|_| {
            lod1_terrain_intersection_curve_result = Some(collect_gml_child_lenient(
                xml_document,
                index,
                CityGmlElement::Lod1TerrainIntersectionCurveProperty.into(),
                config.gml_config(),
                deserialize_multi_curve_property,
            ));
        });
        s.spawn(|_| {
            lod2_terrain_intersection_curve_result = Some(collect_gml_child_lenient(
                xml_document,
                index,
                CityGmlElement::Lod2TerrainIntersectionCurveProperty.into(),
                config.gml_config(),
                deserialize_multi_curve_property,
            ));
        });
        s.spawn(|_| {
            lod3_terrain_intersection_curve_result = Some(collect_gml_child_lenient(
                xml_document,
                index,
                CityGmlElement::Lod3TerrainIntersectionCurveProperty.into(),
                config.gml_config(),
                deserialize_multi_curve_property,
            ));
        });
        s.spawn(|_| {
            point_cloud_result = Some(collect_child(
                xml_document,
                index,
                CityGmlElement::AbstractPointCloudProperty.into(),
                config,
                deserialize_abstract_point_cloud_property,
            ));
        });
    });

    let mut abstract_physical_space = AbstractPhysicalSpace::from_abstract_space(
        abstract_space_result.expect("rayon::scope guarantees all spawns complete")?,
    );
    abstract_physical_space.set_lod1_terrain_intersection_curve(
        lod1_terrain_intersection_curve_result
            .expect("rayon::scope guarantees all spawns complete"),
    );
    abstract_physical_space.set_lod2_terrain_intersection_curve(
        lod2_terrain_intersection_curve_result
            .expect("rayon::scope guarantees all spawns complete"),
    );
    abstract_physical_space.set_lod3_terrain_intersection_curve(
        lod3_terrain_intersection_curve_result
            .expect("rayon::scope guarantees all spawns complete"),
    );
    abstract_physical_space
        .set_point_cloud(point_cloud_result.expect("rayon::scope guarantees all spawns complete")?);

    Ok(abstract_physical_space)
}

pub fn serialize_abstract_physical_space(
    abstract_physical_space: &AbstractPhysicalSpace,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_space(
        abstract_physical_space.abstract_space(),
        xml_fragment_writer,
    )?;

    if let Some(prop) = abstract_physical_space.lod1_terrain_intersection_curve() {
        serialize_multi_curve_property(
            prop,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::Lod1TerrainIntersectionCurveProperty,
        )?;
    }
    if let Some(prop) = abstract_physical_space.lod2_terrain_intersection_curve() {
        serialize_multi_curve_property(
            prop,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::Lod2TerrainIntersectionCurveProperty,
        )?;
    }
    if let Some(prop) = abstract_physical_space.lod3_terrain_intersection_curve() {
        serialize_multi_curve_property(
            prop,
            xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::Lod3TerrainIntersectionCurveProperty,
        )?;
    }

    if let Some(prop) = abstract_physical_space.point_cloud() {
        serialize_abstract_point_cloud_property(prop, xml_fragment_writer)?;
    }

    Ok(())
}

pub fn serialize_abstract_physical_space_attributes(
    abstract_physical_space: &AbstractPhysicalSpace,
) -> Vec<(String, String)> {
    serialize_abstract_space_attributes(abstract_physical_space.abstract_space())
}
