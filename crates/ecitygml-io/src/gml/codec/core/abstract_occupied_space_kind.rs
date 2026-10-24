use crate::Error;
use crate::gml::codec::city_furniture::{deserialize_city_furniture, serialize_city_furniture};
use crate::gml::codec::construction::{
    deserialize_abstract_construction_kind, deserialize_abstract_constructive_element_kind,
    deserialize_abstract_filling_element_kind, deserialize_abstract_furniture_kind,
    deserialize_abstract_installation_kind, serialize_abstract_construction_kind,
    serialize_abstract_constructive_element_kind, serialize_abstract_filling_element_kind,
    serialize_abstract_furniture_kind, serialize_abstract_installation_kind,
};
use crate::gml::codec::generics::{
    deserialize_generic_occupied_space, serialize_generic_occupied_space,
};
use crate::gml::codec::vegetation::deserialize_abstract_vegetation_object_kind;
use crate::gml::codec::vegetation::serialize_abstract_vegetation_object_kind;
use crate::gml::codec::water_body::{deserialize_water_body, serialize_water_body};
use crate::gml::util::{CityGmlElement, CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::core::AbstractOccupiedSpaceKind;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_occupied_space_kind(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Option<AbstractOccupiedSpaceKind>, Error> {
    if let Some(index) = index.first(CityGmlElement::CityFurniture.into()) {
        let city_furniture =
            deserialize_city_furniture(&xml_document[index.range()], index, config)?;
        return Ok(Some(city_furniture.into()));
    }
    if let Some(x) = deserialize_abstract_construction_kind(xml_document, index, config)? {
        return Ok(Some(x.into()));
    }
    if let Some(x) = deserialize_abstract_constructive_element_kind(xml_document, index, config)? {
        return Ok(Some(x.into()));
    }
    if let Some(x) = deserialize_abstract_filling_element_kind(xml_document, index, config)? {
        return Ok(Some(x.into()));
    }
    if let Some(index) = index.first(CityGmlElement::GenericOccupiedSpace.into()) {
        let generic_occupied_space =
            deserialize_generic_occupied_space(&xml_document[index.range()], index, config)?;
        return Ok(Some(generic_occupied_space.into()));
    }
    if let Some(x) = deserialize_abstract_furniture_kind(xml_document, index, config)? {
        return Ok(Some(x.into()));
    }
    if let Some(x) = deserialize_abstract_installation_kind(xml_document, index, config)? {
        return Ok(Some(x.into()));
    }
    if let Some(x) = deserialize_abstract_vegetation_object_kind(xml_document, index, config)? {
        return Ok(Some(x.into()));
    }
    if let Some(index) = index.first(CityGmlElement::WaterBody.into()) {
        let water_body = deserialize_water_body(&xml_document[index.range()], index, config)?;
        return Ok(Some(water_body.into()));
    }

    Ok(None)
}

pub fn serialize_abstract_occupied_space_kind(
    abstract_occupied_space_kind: &AbstractOccupiedSpaceKind,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    match abstract_occupied_space_kind {
        AbstractOccupiedSpaceKind::CityFurniture(x) => {
            serialize_city_furniture(x, xml_fragment_writer)
        }
        AbstractOccupiedSpaceKind::AbstractConstructionKind(x) => {
            serialize_abstract_construction_kind(x, xml_fragment_writer)
        }
        AbstractOccupiedSpaceKind::AbstractConstructiveElementKind(x) => {
            serialize_abstract_constructive_element_kind(x, xml_fragment_writer)
        }
        AbstractOccupiedSpaceKind::AbstractFillingElementKind(x) => {
            serialize_abstract_filling_element_kind(x, xml_fragment_writer)
        }
        AbstractOccupiedSpaceKind::GenericOccupiedSpace(x) => {
            serialize_generic_occupied_space(x, xml_fragment_writer)
        }
        AbstractOccupiedSpaceKind::AbstractFurnitureKind(x) => {
            serialize_abstract_furniture_kind(x, xml_fragment_writer)
        }
        AbstractOccupiedSpaceKind::AbstractInstallationKind(x) => {
            serialize_abstract_installation_kind(x, xml_fragment_writer)
        }
        AbstractOccupiedSpaceKind::AbstractVegetationObjectKind(x) => {
            serialize_abstract_vegetation_object_kind(x, xml_fragment_writer)
        }
        AbstractOccupiedSpaceKind::WaterBody(x) => serialize_water_body(x, xml_fragment_writer),
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::bridge::BridgeFurniture;
    use ecitygml_core::model::building::BuildingFurniture;
    use ecitygml_core::model::common::{FeatureType, HasFeatureType};
    use ecitygml_core::model::construction::AbstractFurnitureKind;
    use ecitygml_core::model::tunnel::TunnelFurniture;
    use egml::io::util::Formatting;
    use egml::model::base::Id;

    #[test]
    fn test_deserialize_bridge_furniture_as_abstract_occupied_space_kind() {
        let xml_document = b"<brid:bridgeFurniture>
    <brid:BridgeFurniture gml:id=\"BF_1\">
      <brid:class>7000</brid:class>
    </brid:BridgeFurniture>
  </brid:bridgeFurniture>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_occupied_space_kind = deserialize_abstract_occupied_space_kind(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work")
        .expect("should recognize a BridgeFurniture");

        assert!(matches!(
            abstract_occupied_space_kind,
            AbstractOccupiedSpaceKind::AbstractFurnitureKind(
                AbstractFurnitureKind::BridgeFurniture(_)
            )
        ));
        assert_eq!(
            abstract_occupied_space_kind.feature_type(),
            FeatureType::BridgeFurniture
        );
    }

    #[test]
    fn test_serialize_bridge_furniture_as_abstract_occupied_space_kind() {
        let abstract_occupied_space_kind: AbstractOccupiedSpaceKind =
            BridgeFurniture::new(Id::try_from("BF_1").expect("should work")).into();

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_abstract_occupied_space_kind(
            &abstract_occupied_space_kind,
            &mut xml_fragment_writer,
        )
        .expect("should serialize");
        let mut buf = Vec::new();
        xml_fragment_writer
            .write_to(&mut buf)
            .expect("should flush fragments");

        assert!(
            String::from_utf8(buf)
                .expect("should convert to string")
                .starts_with("<brid:BridgeFurniture")
        );
    }

    #[test]
    fn test_deserialize_building_furniture_as_abstract_occupied_space_kind() {
        let xml_document = b"<bldg:buildingFurniture>
    <bldg:BuildingFurniture gml:id=\"BLF_1\">
      <bldg:class>7000</bldg:class>
    </bldg:BuildingFurniture>
  </bldg:buildingFurniture>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_occupied_space_kind = deserialize_abstract_occupied_space_kind(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work")
        .expect("should recognize a BuildingFurniture");

        assert!(matches!(
            abstract_occupied_space_kind,
            AbstractOccupiedSpaceKind::AbstractFurnitureKind(
                AbstractFurnitureKind::BuildingFurniture(_)
            )
        ));
        assert_eq!(
            abstract_occupied_space_kind.feature_type(),
            FeatureType::BuildingFurniture
        );
    }

    #[test]
    fn test_serialize_building_furniture_as_abstract_occupied_space_kind() {
        let abstract_occupied_space_kind: AbstractOccupiedSpaceKind =
            BuildingFurniture::new(Id::try_from("BLF_1").expect("should work")).into();

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_abstract_occupied_space_kind(
            &abstract_occupied_space_kind,
            &mut xml_fragment_writer,
        )
        .expect("should serialize");
        let mut buf = Vec::new();
        xml_fragment_writer
            .write_to(&mut buf)
            .expect("should flush fragments");

        assert!(
            String::from_utf8(buf)
                .expect("should convert to string")
                .starts_with("<bldg:BuildingFurniture")
        );
    }

    #[test]
    fn test_deserialize_tunnel_furniture_as_abstract_occupied_space_kind() {
        let xml_document = b"<tun:tunnelFurniture>
    <tun:TunnelFurniture gml:id=\"TF_1\">
      <tun:class>7000</tun:class>
    </tun:TunnelFurniture>
  </tun:tunnelFurniture>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_occupied_space_kind = deserialize_abstract_occupied_space_kind(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work")
        .expect("should recognize a TunnelFurniture");

        assert!(matches!(
            abstract_occupied_space_kind,
            AbstractOccupiedSpaceKind::AbstractFurnitureKind(
                AbstractFurnitureKind::TunnelFurniture(_)
            )
        ));
        assert_eq!(
            abstract_occupied_space_kind.feature_type(),
            FeatureType::TunnelFurniture
        );
    }

    #[test]
    fn test_serialize_tunnel_furniture_as_abstract_occupied_space_kind() {
        let abstract_occupied_space_kind: AbstractOccupiedSpaceKind =
            TunnelFurniture::new(Id::try_from("TF_1").expect("should work")).into();

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_abstract_occupied_space_kind(
            &abstract_occupied_space_kind,
            &mut xml_fragment_writer,
        )
        .expect("should serialize");
        let mut buf = Vec::new();
        xml_fragment_writer
            .write_to(&mut buf)
            .expect("should flush fragments");

        assert!(
            String::from_utf8(buf)
                .expect("should convert to string")
                .starts_with("<tun:TunnelFurniture")
        );
    }
}
