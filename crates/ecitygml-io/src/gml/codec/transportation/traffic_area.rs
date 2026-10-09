use crate::Error;
use crate::gml::codec::core::{
    deserialize_abstract_thematic_surface, serialize_abstract_thematic_surface,
    serialize_abstract_thematic_surface_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::core::AsAbstractThematicSurface;
use ecitygml_core::model::transportation::TrafficArea;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::basic_types::Code;

pub fn deserialize_traffic_area(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<TrafficArea, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_thematic_surface =
        deserialize_abstract_thematic_surface(xml_document, index, config)?;
    let mut traffic_area = TrafficArea::from_abstract_thematic_surface(abstract_thematic_surface);

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    traffic_area.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    traffic_area.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    traffic_area.set_usages(usages.into_iter().map(Into::into).collect());

    let surface_material: Option<Code> = index
        .first(CityGmlElement::SurfaceMaterialProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    traffic_area.set_surface_material_opt(surface_material.map(Into::into));

    Ok(traffic_area)
}

pub fn serialize_traffic_area(
    traffic_area: &TrafficArea,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_traffic_area_attributes(traffic_area);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Transportation,
        CityGmlElement::TrafficArea,
        attributes,
    )?;

    serialize_abstract_thematic_surface(
        traffic_area.abstract_thematic_surface(),
        xml_fragment_writer,
    )?;

    if let Some(class) = traffic_area.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in traffic_area.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in traffic_area.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::UsageProperty,
        )?;
    }

    if let Some(surface_material) = traffic_area.surface_material() {
        serialize_code(
            surface_material.code(),
            xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::SurfaceMaterialProperty,
        )?;
    }

    xml_fragment_writer.write_end_event(
        CityGmlNamespace::Transportation,
        CityGmlElement::TrafficArea,
    )?;

    Ok(())
}

pub fn serialize_traffic_area_attributes(traffic_area: &TrafficArea) -> Vec<(String, String)> {
    serialize_abstract_thematic_surface_attributes(traffic_area.abstract_thematic_surface())
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
            b"<tran:TrafficArea gml:id=\"UUID_482ae9d8-0d5f-3a97-9d9e-e5362caa2a57\">
                  <gml:name>Lane</gml:name>
                  <genericAttribute>
                    <gen:StringAttribute>
                      <gen:name>opendrive_lane_type</gen:name>
                      <gen:value>SIDEWALK</gen:value>
                    </gen:StringAttribute>
                  </genericAttribute>
                  <tran:function>2</tran:function>
                  <tran:usage>1</tran:usage>
                  <tran:surfaceMaterial>1</tran:surfaceMaterial>
                </tran:TrafficArea>";

        let traffic_area = deserialize_traffic_area(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            traffic_area.feature_id(),
            &Id::try_from("UUID_482ae9d8-0d5f-3a97-9d9e-e5362caa2a57").expect("should work")
        );
        assert!(traffic_area.lod2_multi_surface().is_none());
        assert_eq!(traffic_area.generic_attributes().len(), 1);
        assert_eq!(
            traffic_area.functions().first().unwrap().code().value(),
            "2"
        );
        assert_eq!(traffic_area.usages().first().unwrap().code().value(), "1");
        assert_eq!(traffic_area.surface_material().unwrap().code().value(), "1");
    }
}
