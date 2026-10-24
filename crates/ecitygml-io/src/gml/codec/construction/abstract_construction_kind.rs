use crate::Error;
use crate::gml::codec::bridge::{deserialize_abstract_bridge_kind, serialize_abstract_bridge_kind};
use crate::gml::codec::building::{
    deserialize_abstract_building_kind, serialize_abstract_building_kind,
};
use crate::gml::codec::construction::{
    deserialize_other_construction, serialize_other_construction,
};
use crate::gml::codec::tunnel::{deserialize_abstract_tunnel_kind, serialize_abstract_tunnel_kind};
use crate::gml::util::{CityGmlElement, CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::construction::AbstractConstructionKind;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_construction_kind(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Option<AbstractConstructionKind>, Error> {
    let abstract_building_kind = deserialize_abstract_building_kind(xml_document, index, config)?;
    if let Some(x) = abstract_building_kind {
        return Ok(Some(AbstractConstructionKind::AbstractBuildingKind(x)));
    }

    let abstract_bridge_kind = deserialize_abstract_bridge_kind(xml_document, index, config)?;
    if let Some(x) = abstract_bridge_kind {
        return Ok(Some(AbstractConstructionKind::AbstractBridgeKind(x)));
    }

    let abstract_tunnel_kind = deserialize_abstract_tunnel_kind(xml_document, index, config)?;
    if let Some(x) = abstract_tunnel_kind {
        return Ok(Some(AbstractConstructionKind::AbstractTunnelKind(x)));
    }

    if let Some(index) = index.first(CityGmlElement::OtherConstruction.into()) {
        let other_construction =
            deserialize_other_construction(&xml_document[index.range()], index, config)?;
        return Ok(Some(AbstractConstructionKind::OtherConstruction(
            other_construction,
        )));
    }

    Ok(None)
}

pub fn serialize_abstract_construction_kind(
    abstract_construction_kind: &AbstractConstructionKind,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    match abstract_construction_kind {
        AbstractConstructionKind::AbstractBuildingKind(x) => {
            serialize_abstract_building_kind(x, xml_fragment_writer)
        }
        AbstractConstructionKind::AbstractBridgeKind(x) => {
            serialize_abstract_bridge_kind(x, xml_fragment_writer)
        }
        AbstractConstructionKind::AbstractTunnelKind(x) => {
            serialize_abstract_tunnel_kind(x, xml_fragment_writer)
        }
        AbstractConstructionKind::OtherConstruction(x) => {
            serialize_other_construction(x, xml_fragment_writer)
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::common::{FeatureType, HasFeatureType};
    use ecitygml_core::model::construction::OtherConstruction;
    use egml::io::util::Formatting;
    use egml::model::base::Id;

    #[test]
    fn test_deserialize_other_construction_as_abstract_construction_kind() {
        let xml_document = b"<cityObjectMember>
    <con:OtherConstruction gml:id=\"OC_1\">
      <con:class>1000</con:class>
    </con:OtherConstruction>
  </cityObjectMember>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_construction_kind = deserialize_abstract_construction_kind(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work")
        .expect("should recognize an OtherConstruction");

        assert!(matches!(
            abstract_construction_kind,
            AbstractConstructionKind::OtherConstruction(_)
        ));
        assert_eq!(
            abstract_construction_kind.feature_type(),
            FeatureType::OtherConstruction
        );
    }

    #[test]
    fn test_serialize_other_construction_as_abstract_construction_kind() {
        let abstract_construction_kind: AbstractConstructionKind =
            OtherConstruction::new(Id::try_from("OC_1").expect("should work")).into();

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_abstract_construction_kind(&abstract_construction_kind, &mut xml_fragment_writer)
            .expect("should serialize");
        let mut buf = Vec::new();
        xml_fragment_writer
            .write_to(&mut buf)
            .expect("should flush fragments");

        assert!(
            String::from_utf8(buf)
                .expect("should convert to string")
                .starts_with("<con:OtherConstruction")
        );
    }
}
