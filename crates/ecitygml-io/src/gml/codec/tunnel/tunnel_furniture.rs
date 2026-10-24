use crate::Error;
use crate::gml::codec::construction::{
    deserialize_abstract_furniture, serialize_abstract_furniture,
    serialize_abstract_furniture_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::construction::AsAbstractFurniture;
use ecitygml_core::model::tunnel::TunnelFurniture;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::basic_types::Code;

pub fn deserialize_tunnel_furniture(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<TunnelFurniture, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_furniture = deserialize_abstract_furniture(xml_document, index, config)?;
    let mut tunnel_furniture = TunnelFurniture::from_abstract_furniture(abstract_furniture);

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    tunnel_furniture.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    tunnel_furniture.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    tunnel_furniture.set_usages(usages.into_iter().map(Into::into).collect());

    Ok(tunnel_furniture)
}

pub fn serialize_tunnel_furniture(
    tunnel_furniture: &TunnelFurniture,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_tunnel_furniture_attributes(tunnel_furniture);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Tunnel,
        CityGmlElement::TunnelFurniture,
        attributes,
    )?;

    serialize_abstract_furniture(tunnel_furniture.abstract_furniture(), xml_fragment_writer)?;

    if let Some(class) = tunnel_furniture.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Tunnel,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in tunnel_furniture.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::Tunnel,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in tunnel_furniture.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::Tunnel,
            CityGmlElement::UsageProperty,
        )?;
    }

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::Tunnel, CityGmlElement::TunnelFurniture)?;

    Ok(())
}

pub fn serialize_tunnel_furniture_attributes(
    tunnel_furniture: &TunnelFurniture,
) -> Vec<(String, String)> {
    serialize_abstract_furniture_attributes(tunnel_furniture.abstract_furniture())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::core::AsAbstractFeature;
    use egml::io::util::Formatting;
    use egml::model::base::{AsAbstractGml, Id};

    fn deserialize(xml_document: &[u8]) -> TunnelFurniture {
        deserialize_tunnel_furniture(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work")
    }

    #[test]
    fn test_deserialize_tunnel_furniture() {
        let xml_document = b"<tun:TunnelFurniture gml:id=\"BF_1\">
      <gml:name>Bench</gml:name>
      <tun:class>7000</tun:class>
      <tun:function>7010</tun:function>
      <tun:function>7020</tun:function>
      <tun:usage>8000</tun:usage>
    </tun:TunnelFurniture>";

        let tunnel_furniture = deserialize(xml_document);

        assert_eq!(
            tunnel_furniture.feature_id(),
            &Id::try_from("BF_1").expect("should work")
        );
        assert_eq!(
            tunnel_furniture
                .names()
                .first()
                .expect("should have a name"),
            &Code::new("Bench")
        );
        assert_eq!(
            tunnel_furniture.class().map(|x| x.code().value()),
            Some("7000")
        );
        assert_eq!(
            tunnel_furniture
                .functions()
                .iter()
                .map(|x| x.code().value())
                .collect::<Vec<_>>(),
            vec!["7010", "7020"]
        );
        assert_eq!(
            tunnel_furniture
                .usages()
                .iter()
                .map(|x| x.code().value())
                .collect::<Vec<_>>(),
            vec!["8000"]
        );
    }

    #[test]
    fn test_deserialize_tunnel_furniture_without_codes() {
        let tunnel_furniture = deserialize(b"<tun:TunnelFurniture gml:id=\"BF_1\"/>");

        assert!(tunnel_furniture.class().is_none());
        assert!(tunnel_furniture.functions().is_empty());
        assert!(tunnel_furniture.usages().is_empty());
    }

    #[test]
    fn test_round_trip_tunnel_furniture() {
        let mut tunnel_furniture = TunnelFurniture::new(Id::try_from("BF_1").expect("should work"));
        tunnel_furniture.set_class(Code::new("7000").into());
        tunnel_furniture.push_function(Code::new("7010").into());
        tunnel_furniture.push_usage(Code::new("8000").into());

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_tunnel_furniture(&tunnel_furniture, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");
        assert!(xml.starts_with("<tun:TunnelFurniture"));

        assert_eq!(deserialize(xml.as_bytes()), tunnel_furniture);
    }
}
