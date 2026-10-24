use crate::Error;
use crate::gml::codec::core::{
    deserialize_abstract_unoccupied_space, serialize_abstract_unoccupied_space,
    serialize_abstract_unoccupied_space_attributes,
};
use crate::gml::codec::tunnel::tunnel_furniture_property::{
    deserialize_tunnel_furniture_property, serialize_tunnel_furniture_property,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::core::AsAbstractUnoccupiedSpace;
use ecitygml_core::model::tunnel::HollowSpace;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter, collect_children};
use egml::model::basic_types::Code;

pub fn deserialize_hollow_space(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<HollowSpace, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_unoccupied_space =
        deserialize_abstract_unoccupied_space(xml_document, index, config)?;
    let mut hollow_space = HollowSpace::from_abstract_unoccupied_space(abstract_unoccupied_space);

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    hollow_space.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    hollow_space.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    hollow_space.set_usages(usages.into_iter().map(Into::into).collect());

    hollow_space.set_tunnel_furniture(collect_children(
        xml_document,
        index,
        CityGmlElement::TunnelFurnitureProperty.into(),
        config,
        deserialize_tunnel_furniture_property,
    )?);

    Ok(hollow_space)
}

pub fn serialize_hollow_space(
    hollow_space: &HollowSpace,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_hollow_space_attributes(hollow_space);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Tunnel,
        CityGmlElement::HollowSpace,
        attributes,
    )?;

    serialize_abstract_unoccupied_space(
        hollow_space.abstract_unoccupied_space(),
        xml_fragment_writer,
    )?;

    if let Some(class) = hollow_space.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Tunnel,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in hollow_space.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::Tunnel,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in hollow_space.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::Tunnel,
            CityGmlElement::UsageProperty,
        )?;
    }

    for prop in hollow_space.tunnel_furniture() {
        serialize_tunnel_furniture_property(prop, xml_fragment_writer)?;
    }

    xml_fragment_writer.write_end_event(CityGmlNamespace::Tunnel, CityGmlElement::HollowSpace)?;

    Ok(())
}

pub fn serialize_hollow_space_attributes(hollow_space: &HollowSpace) -> Vec<(String, String)> {
    serialize_abstract_unoccupied_space_attributes(hollow_space.abstract_unoccupied_space())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::core::AsAbstractFeature;
    use egml::io::util::Formatting;
    use egml::model::base::{AsAbstractGml, Id};

    fn deserialize(xml_document: &[u8]) -> HollowSpace {
        deserialize_hollow_space(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work")
    }

    #[test]
    fn test_deserialize_hollow_space() {
        let xml_document = b"<tun:HollowSpace gml:id=\"HS_1\">
      <gml:name>Service room</gml:name>
      <tun:class>5000</tun:class>
      <tun:function>5010</tun:function>
      <tun:function>5020</tun:function>
      <tun:usage>6000</tun:usage>
    </tun:HollowSpace>";

        let hollow_space = deserialize(xml_document);

        assert_eq!(
            hollow_space.feature_id(),
            &Id::try_from("HS_1").expect("should work")
        );
        assert_eq!(
            hollow_space.names().first().expect("should have a name"),
            &Code::new("Service room")
        );
        assert_eq!(hollow_space.class().map(|x| x.code().value()), Some("5000"));
        assert_eq!(
            hollow_space
                .functions()
                .iter()
                .map(|x| x.code().value())
                .collect::<Vec<_>>(),
            vec!["5010", "5020"]
        );
        assert_eq!(
            hollow_space
                .usages()
                .iter()
                .map(|x| x.code().value())
                .collect::<Vec<_>>(),
            vec!["6000"]
        );
    }

    #[test]
    fn test_deserialize_hollow_space_without_codes() {
        let hollow_space = deserialize(b"<tun:HollowSpace gml:id=\"HS_1\"/>");

        assert!(hollow_space.class().is_none());
        assert!(hollow_space.functions().is_empty());
        assert!(hollow_space.usages().is_empty());
    }

    #[test]
    fn test_round_trip_hollow_space() {
        let mut hollow_space = HollowSpace::new(Id::try_from("HS_1").expect("should work"));
        hollow_space.set_class(Code::new("5000").into());
        hollow_space.push_function(Code::new("5010").into());
        hollow_space.push_usage(Code::new("6000").into());

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_hollow_space(&hollow_space, &mut xml_fragment_writer).expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");
        assert!(xml.starts_with("<tun:HollowSpace"));

        assert_eq!(deserialize(xml.as_bytes()), hollow_space);
    }
}
