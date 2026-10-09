use crate::Error;
use crate::gml::codec::appearance::abstract_surface_data::{
    deserialize_abstract_surface_data, serialize_abstract_surface_data,
    serialize_abstract_surface_data_attributes,
};
use crate::gml::codec::appearance::basic_types::{
    deserialize_color, deserialize_geometry_reference, serialize_color,
    serialize_geometry_reference,
};
use crate::gml::codec::common::{deserialize_bool, serialize_bool};
use crate::gml::codec::core::basic_types::{
    deserialize_double_between_0_and_1, serialize_double_between_0_and_1,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::appearance::{AsAbstractSurfaceData, GeometryReference, X3DMaterial};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_x3d_material(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<X3DMaterial, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_surface_data = deserialize_abstract_surface_data(xml_document, index, config)?;

    let mut x3d_material = X3DMaterial::from_abstract_surface_data(abstract_surface_data);

    let ambient_intensity = index
        .first(CityGmlElement::AmbientIntensityProperty.into())
        .map(|x| deserialize_double_between_0_and_1(&xml_document[x.range()]))
        .transpose()?;
    x3d_material.set_ambient_intensity_opt(ambient_intensity);

    let diffuse_color = index
        .first(CityGmlElement::DiffuseColorProperty.into())
        .map(|x| deserialize_color(&xml_document[x.range()]))
        .transpose()?;
    x3d_material.set_diffuse_color_opt(diffuse_color);

    let emissive_color = index
        .first(CityGmlElement::EmissiveColorProperty.into())
        .map(|x| deserialize_color(&xml_document[x.range()]))
        .transpose()?;
    x3d_material.set_emissive_color_opt(emissive_color);

    let specular_color = index
        .first(CityGmlElement::SpecularColorProperty.into())
        .map(|x| deserialize_color(&xml_document[x.range()]))
        .transpose()?;
    x3d_material.set_specular_color_opt(specular_color);

    let shininess = index
        .first(CityGmlElement::ShininessProperty.into())
        .map(|x| deserialize_double_between_0_and_1(&xml_document[x.range()]))
        .transpose()?;
    x3d_material.set_shininess_opt(shininess);

    let transparency = index
        .first(CityGmlElement::TransparencyProperty.into())
        .map(|x| deserialize_double_between_0_and_1(&xml_document[x.range()]))
        .transpose()?;
    x3d_material.set_transparency_opt(transparency);

    let is_smooth = index
        .first(CityGmlElement::IsSmoothProperty.into())
        .map(|x| deserialize_bool(&xml_document[x.range()]))
        .transpose()?;
    x3d_material.set_is_smooth(is_smooth);

    let targets: Vec<GeometryReference> = index
        .get(CityGmlElement::TargetProperty.into())
        .iter()
        .map(|x| deserialize_geometry_reference(&xml_document[x.range()]))
        .collect::<Result<_, _>>()?;
    x3d_material.set_targets(targets);

    Ok(x3d_material)
}

pub fn serialize_x3d_material(
    x3d_material: &X3DMaterial,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_x3d_material_attributes(x3d_material);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Appearance,
        CityGmlElement::X3DMaterial,
        attributes,
    )?;

    serialize_abstract_surface_data(x3d_material.abstract_surface_data(), xml_fragment_writer)?;

    if let Some(ambient_intensity) = x3d_material.ambient_intensity() {
        serialize_double_between_0_and_1(
            ambient_intensity,
            xml_fragment_writer,
            CityGmlNamespace::Appearance,
            CityGmlElement::AmbientIntensityProperty,
        )?;
    }

    if let Some(diffuse_color) = x3d_material.diffuse_color() {
        serialize_color(
            diffuse_color,
            xml_fragment_writer,
            CityGmlNamespace::Appearance,
            CityGmlElement::DiffuseColorProperty,
        )?;
    }

    if let Some(emissive_color) = x3d_material.emissive_color() {
        serialize_color(
            emissive_color,
            xml_fragment_writer,
            CityGmlNamespace::Appearance,
            CityGmlElement::EmissiveColorProperty,
        )?;
    }

    if let Some(specular_color) = x3d_material.specular_color() {
        serialize_color(
            specular_color,
            xml_fragment_writer,
            CityGmlNamespace::Appearance,
            CityGmlElement::SpecularColorProperty,
        )?;
    }

    if let Some(shininess) = x3d_material.shininess() {
        serialize_double_between_0_and_1(
            shininess,
            xml_fragment_writer,
            CityGmlNamespace::Appearance,
            CityGmlElement::ShininessProperty,
        )?;
    }

    if let Some(transparency) = x3d_material.transparency() {
        serialize_double_between_0_and_1(
            transparency,
            xml_fragment_writer,
            CityGmlNamespace::Appearance,
            CityGmlElement::TransparencyProperty,
        )?;
    }

    if let Some(is_smooth) = x3d_material.is_smooth() {
        serialize_bool(
            is_smooth,
            xml_fragment_writer,
            CityGmlNamespace::Appearance,
            CityGmlElement::IsSmoothProperty,
        )?;
    }

    for target in x3d_material.targets() {
        serialize_geometry_reference(
            target,
            xml_fragment_writer,
            CityGmlNamespace::Appearance,
            CityGmlElement::TargetProperty,
        )?;
    }

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::Appearance, CityGmlElement::X3DMaterial)?;

    Ok(())
}

pub fn serialize_x3d_material_attributes(x3d_material: &X3DMaterial) -> Vec<(String, String)> {
    serialize_abstract_surface_data_attributes(x3d_material.abstract_surface_data())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_x3d_material() {
        let xml_document = b"\
<app:X3DMaterial gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <app:ambientIntensity>0.5</app:ambientIntensity>
    <app:diffuseColor>0.1 0.2 0.3</app:diffuseColor>
    <app:emissiveColor>0.4 0.5 0.6</app:emissiveColor>
    <app:specularColor>0.7 0.8 0.9</app:specularColor>
    <app:shininess>0.2</app:shininess>
    <app:transparency>0.1</app:transparency>
    <app:isSmooth>true</app:isSmooth>
    <app:target>#poly1</app:target>
    <app:target>#poly2</app:target>
</app:X3DMaterial>";

        let x3d_material = deserialize_x3d_material(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(x3d_material.ambient_intensity().unwrap().value(), 0.5);
        assert_eq!(x3d_material.diffuse_color().unwrap().red().value(), 0.1);
        assert_eq!(x3d_material.emissive_color().unwrap().red().value(), 0.4);
        assert_eq!(x3d_material.specular_color().unwrap().red().value(), 0.7);
        assert_eq!(x3d_material.shininess().unwrap().value(), 0.2);
        assert_eq!(x3d_material.transparency().unwrap().value(), 0.1);
        assert_eq!(x3d_material.is_smooth(), Some(true));
        assert_eq!(x3d_material.targets().len(), 2);
        assert_eq!(x3d_material.targets()[0].href, "#poly1");
        assert_eq!(x3d_material.targets()[1].href, "#poly2");
    }

    #[test]
    fn test_round_trip_x3d_material() {
        let xml_document = b"\
<app:X3DMaterial gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <app:ambientIntensity>0.5</app:ambientIntensity>
    <app:diffuseColor>0.1 0.2 0.3</app:diffuseColor>
    <app:emissiveColor>0.4 0.5 0.6</app:emissiveColor>
    <app:specularColor>0.7 0.8 0.9</app:specularColor>
    <app:shininess>0.2</app:shininess>
    <app:transparency>0.1</app:transparency>
    <app:isSmooth>true</app:isSmooth>
    <app:target>#poly1</app:target>
    <app:target>#poly2</app:target>
</app:X3DMaterial>";

        let x3d_material = deserialize_x3d_material(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_x3d_material(&x3d_material, &mut xml_fragment_writer).expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("app:ambientIntensity"));
        assert!(xml.contains("app:diffuseColor"));
        assert!(xml.contains("app:emissiveColor"));
        assert!(xml.contains("app:specularColor"));
        assert!(xml.contains("app:shininess"));
        assert!(xml.contains("app:transparency"));
        assert!(xml.contains("app:isSmooth"));
        assert!(xml.contains("app:target"));
        assert!(xml.contains("#poly1"));
        assert!(xml.contains("#poly2"));

        let round_tripped = deserialize_x3d_material(
            xml.as_bytes(),
            &XmlDocumentIndex::from_scan(xml.as_bytes(), None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            x3d_material.ambient_intensity(),
            round_tripped.ambient_intensity()
        );
        assert_eq!(x3d_material.diffuse_color(), round_tripped.diffuse_color());
        assert_eq!(
            x3d_material.emissive_color(),
            round_tripped.emissive_color()
        );
        assert_eq!(
            x3d_material.specular_color(),
            round_tripped.specular_color()
        );
        assert_eq!(x3d_material.shininess(), round_tripped.shininess());
        assert_eq!(x3d_material.transparency(), round_tripped.transparency());
        assert_eq!(x3d_material.is_smooth(), round_tripped.is_smooth());
        assert_eq!(x3d_material.targets(), round_tripped.targets());
    }
}
