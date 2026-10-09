use crate::Error;
use crate::gml::codec::core::{
    deserialize_abstract_thematic_surface, serialize_abstract_thematic_surface,
    serialize_abstract_thematic_surface_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::core::AsAbstractThematicSurface;
use ecitygml_core::model::transportation::AuxiliaryTrafficArea;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::basic_types::Code;

pub fn deserialize_auxiliary_traffic_area(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AuxiliaryTrafficArea, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_thematic_surface =
        deserialize_abstract_thematic_surface(xml_document, index, config)?;
    let mut auxiliary_traffic_area =
        AuxiliaryTrafficArea::from_abstract_thematic_surface(abstract_thematic_surface);

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    auxiliary_traffic_area.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    auxiliary_traffic_area.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    auxiliary_traffic_area.set_usages(usages.into_iter().map(Into::into).collect());

    let surface_material: Option<Code> = index
        .first(CityGmlElement::SurfaceMaterialProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    auxiliary_traffic_area.set_surface_material_opt(surface_material.map(Into::into));

    Ok(auxiliary_traffic_area)
}

pub fn serialize_auxiliary_traffic_area(
    auxiliary_traffic_area: &AuxiliaryTrafficArea,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_auxiliary_traffic_area_attributes(auxiliary_traffic_area);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Transportation,
        CityGmlElement::AuxiliaryTrafficArea,
        attributes,
    )?;

    serialize_abstract_thematic_surface(
        auxiliary_traffic_area.abstract_thematic_surface(),
        xml_fragment_writer,
    )?;

    if let Some(class) = auxiliary_traffic_area.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in auxiliary_traffic_area.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in auxiliary_traffic_area.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::UsageProperty,
        )?;
    }

    if let Some(surface_material) = auxiliary_traffic_area.surface_material() {
        serialize_code(
            surface_material.code(),
            xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::SurfaceMaterialProperty,
        )?;
    }

    xml_fragment_writer.write_end_event(
        CityGmlNamespace::Transportation,
        CityGmlElement::AuxiliaryTrafficArea,
    )?;

    Ok(())
}

pub fn serialize_auxiliary_traffic_area_attributes(
    auxiliary_traffic_area: &AuxiliaryTrafficArea,
) -> Vec<(String, String)> {
    serialize_abstract_thematic_surface_attributes(
        auxiliary_traffic_area.abstract_thematic_surface(),
    )
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::core::{
        AsAbstractCityObject, AsAbstractFeature, AsAbstractThematicSurface,
    };
    use egml::model::base::Id;

    #[test]
    fn test_deserialize_basic_traffic_area() {
        let xml_document =
            b"<tran:AuxiliaryTrafficArea gml:id=\"UUID_312e01da-5c89-3f89-b8c0-3e0a8bafecbb\">
                  <genericAttribute>
                    <gen:StringAttribute>
                      <gen:name>opendrive_lane_type</gen:name>
                      <gen:value>BORDER</gen:value>
                    </gen:StringAttribute>
                  </genericAttribute>
                </tran:AuxiliaryTrafficArea>";

        let auxiliary_traffic_area = deserialize_auxiliary_traffic_area(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            auxiliary_traffic_area.feature_id(),
            &Id::try_from("UUID_312e01da-5c89-3f89-b8c0-3e0a8bafecbb").expect("should work")
        );
        assert!(auxiliary_traffic_area.lod2_multi_surface().is_none());
        assert_eq!(auxiliary_traffic_area.generic_attributes().len(), 1);
    }
}
