use crate::Error;
use crate::gml::codec::bridge::{deserialize_bridge_room, serialize_bridge_room};
use crate::gml::codec::building::{deserialize_building_room, serialize_building_room};
use crate::gml::codec::generics::{
    deserialize_generic_unoccupied_space, serialize_generic_unoccupied_space,
};
use crate::gml::codec::transportation::{
    deserialize_abstract_transportation_space_kind, deserialize_auxiliary_traffic_space,
    deserialize_clearance_space, deserialize_hole, deserialize_traffic_space,
    serialize_abstract_transportation_space_kind, serialize_auxiliary_traffic_space,
    serialize_clearance_space, serialize_hole, serialize_traffic_space,
};
use crate::gml::codec::tunnel::{deserialize_hollow_space, serialize_hollow_space};
use crate::gml::util::{CityGmlElement, CombinedCityGmlElement, DeserializationConfig};
use ecitygml_core::model::core::AbstractUnoccupiedSpaceKind;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_unoccupied_space_kind(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Option<AbstractUnoccupiedSpaceKind>, Error> {
    if let Some(index) = index.first(CityGmlElement::AuxiliaryTrafficSpace.into()) {
        let auxiliary_traffic_space =
            deserialize_auxiliary_traffic_space(&xml_document[index.range()], index, config)?;
        return Ok(Some(auxiliary_traffic_space.into()));
    }
    if let Some(index) = index.first(CityGmlElement::BridgeRoom.into()) {
        let bridge_room = deserialize_bridge_room(&xml_document[index.range()], index, config)?;
        return Ok(Some(bridge_room.into()));
    }
    if let Some(index) = index.first(CityGmlElement::BuildingRoom.into()) {
        let building_room = deserialize_building_room(&xml_document[index.range()], index, config)?;
        return Ok(Some(building_room.into()));
    }
    if let Some(index) = index.first(CityGmlElement::GenericUnoccupiedSpace.into()) {
        let generic_unoccupied_space =
            deserialize_generic_unoccupied_space(&xml_document[index.range()], index, config)?;
        return Ok(Some(generic_unoccupied_space.into()));
    }
    if let Some(index) = index.first(CityGmlElement::Hole.into()) {
        let hole = deserialize_hole(&xml_document[index.range()], index, config)?;
        return Ok(Some(hole.into()));
    }
    if let Some(index) = index.first(CityGmlElement::HollowSpace.into()) {
        let hollow_space = deserialize_hollow_space(&xml_document[index.range()], index, config)?;
        return Ok(Some(hollow_space.into()));
    }
    if let Some(index) = index.first(CityGmlElement::ClearanceSpace.into()) {
        let clearance_space =
            deserialize_clearance_space(&xml_document[index.range()], index, config)?;
        return Ok(Some(clearance_space.into()));
    }
    if let Some(index) = index.first(CityGmlElement::TrafficSpace.into()) {
        let traffic_space = deserialize_traffic_space(&xml_document[index.range()], index, config)?;
        return Ok(Some(traffic_space.into()));
    }
    if let Some(x) = deserialize_abstract_transportation_space_kind(xml_document, index, config)? {
        return Ok(Some(x.into()));
    }

    Ok(None)
}

pub fn serialize_abstract_unoccupied_space_kind(
    abstract_unoccupied_space_kind: &AbstractUnoccupiedSpaceKind,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    match abstract_unoccupied_space_kind {
        AbstractUnoccupiedSpaceKind::AuxiliaryTrafficSpace(x) => {
            serialize_auxiliary_traffic_space(x, xml_fragment_writer)
        }
        AbstractUnoccupiedSpaceKind::BridgeRoom(x) => serialize_bridge_room(x, xml_fragment_writer),
        AbstractUnoccupiedSpaceKind::BuildingRoom(x) => {
            serialize_building_room(x, xml_fragment_writer)
        }
        AbstractUnoccupiedSpaceKind::ClearanceSpace(x) => {
            serialize_clearance_space(x, xml_fragment_writer)
        }
        AbstractUnoccupiedSpaceKind::GenericUnoccupiedSpace(x) => {
            serialize_generic_unoccupied_space(x, xml_fragment_writer)
        }
        AbstractUnoccupiedSpaceKind::Hole(x) => serialize_hole(x, xml_fragment_writer),
        AbstractUnoccupiedSpaceKind::HollowSpace(x) => {
            serialize_hollow_space(x, xml_fragment_writer)
        }
        AbstractUnoccupiedSpaceKind::TrafficSpace(x) => {
            serialize_traffic_space(x, xml_fragment_writer)
        }
        AbstractUnoccupiedSpaceKind::AbstractTransportationSpaceKind(x) => {
            serialize_abstract_transportation_space_kind(x, xml_fragment_writer)
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::bridge::BridgeRoom;
    use ecitygml_core::model::common::{FeatureType, HasFeatureType};
    use ecitygml_core::model::generics::GenericUnoccupiedSpace;
    use ecitygml_core::model::tunnel::HollowSpace;
    use egml::io::util::Formatting;
    use egml::model::base::Id;

    #[test]
    fn test_deserialize_generic_unoccupied_space_as_abstract_unoccupied_space_kind() {
        let xml_document = b"<cityObjectMember>
    <gen:GenericUnoccupiedSpace gml:id=\"GUS_1\">
      <gen:class>1000</gen:class>
    </gen:GenericUnoccupiedSpace>
  </cityObjectMember>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_unoccupied_space_kind = deserialize_abstract_unoccupied_space_kind(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work")
        .expect("should recognize a GenericUnoccupiedSpace");

        assert!(matches!(
            abstract_unoccupied_space_kind,
            AbstractUnoccupiedSpaceKind::GenericUnoccupiedSpace(_)
        ));
        assert_eq!(
            abstract_unoccupied_space_kind.feature_type(),
            FeatureType::GenericUnoccupiedSpace
        );
    }

    #[test]
    fn test_serialize_generic_unoccupied_space_as_abstract_unoccupied_space_kind() {
        let abstract_unoccupied_space_kind: AbstractUnoccupiedSpaceKind =
            GenericUnoccupiedSpace::new(Id::try_from("GUS_1").expect("should work")).into();

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_abstract_unoccupied_space_kind(
            &abstract_unoccupied_space_kind,
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
                .starts_with("<gen:GenericUnoccupiedSpace")
        );
    }

    #[test]
    fn test_deserialize_hollow_space_as_abstract_unoccupied_space_kind() {
        let xml_document = b"<tun:hollowSpace>
    <tun:HollowSpace gml:id=\"HS_1\">
      <tun:class>5000</tun:class>
    </tun:HollowSpace>
  </tun:hollowSpace>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_unoccupied_space_kind = deserialize_abstract_unoccupied_space_kind(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work")
        .expect("should recognize a HollowSpace");

        assert!(matches!(
            abstract_unoccupied_space_kind,
            AbstractUnoccupiedSpaceKind::HollowSpace(_)
        ));
        assert_eq!(
            abstract_unoccupied_space_kind.feature_type(),
            FeatureType::HollowSpace
        );
    }

    #[test]
    fn test_serialize_hollow_space_as_abstract_unoccupied_space_kind() {
        let abstract_unoccupied_space_kind: AbstractUnoccupiedSpaceKind =
            HollowSpace::new(Id::try_from("HS_1").expect("should work")).into();

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_abstract_unoccupied_space_kind(
            &abstract_unoccupied_space_kind,
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
                .starts_with("<tun:HollowSpace")
        );
    }

    #[test]
    fn test_deserialize_bridge_room_as_abstract_unoccupied_space_kind() {
        let xml_document = b"<brid:bridgeRoom>
    <brid:BridgeRoom gml:id=\"BR_1\">
      <brid:class>5000</brid:class>
    </brid:BridgeRoom>
  </brid:bridgeRoom>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_unoccupied_space_kind = deserialize_abstract_unoccupied_space_kind(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work")
        .expect("should recognize a BridgeRoom");

        assert!(matches!(
            abstract_unoccupied_space_kind,
            AbstractUnoccupiedSpaceKind::BridgeRoom(_)
        ));
        assert_eq!(
            abstract_unoccupied_space_kind.feature_type(),
            FeatureType::BridgeRoom
        );
    }

    #[test]
    fn test_serialize_bridge_room_as_abstract_unoccupied_space_kind() {
        let abstract_unoccupied_space_kind: AbstractUnoccupiedSpaceKind =
            BridgeRoom::new(Id::try_from("BR_1").expect("should work")).into();

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_abstract_unoccupied_space_kind(
            &abstract_unoccupied_space_kind,
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
                .starts_with("<brid:BridgeRoom")
        );
    }
}
