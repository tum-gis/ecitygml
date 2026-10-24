use crate::Error;
use crate::gml::codec::building::building_furniture_property::{
    deserialize_building_furniture_property, serialize_building_furniture_property,
};
use crate::gml::codec::building::room_height_property::{
    deserialize_room_height_property, serialize_room_height_property,
};
use crate::gml::codec::core::{
    deserialize_abstract_unoccupied_space, serialize_abstract_unoccupied_space,
    serialize_abstract_unoccupied_space_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::building::{BuildingRoom, RoomHeight};
use ecitygml_core::model::core::AsAbstractUnoccupiedSpace;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter, collect_children};
use egml::model::basic_types::Code;

pub fn deserialize_building_room(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<BuildingRoom, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_unoccupied_space =
        deserialize_abstract_unoccupied_space(xml_document, index, config)?;
    let mut building_room = BuildingRoom::from_abstract_unoccupied_space(abstract_unoccupied_space);

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    building_room.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    building_room.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    building_room.set_usages(usages.into_iter().map(Into::into).collect());

    let room_heights: Vec<RoomHeight> = index
        .get(CityGmlElement::RoomHeightProperty.into())
        .iter()
        .map(|x| deserialize_room_height_property(&xml_document[x.range()]))
        .collect::<Result<_, _>>()?;
    building_room.set_room_heights(room_heights);

    building_room.set_building_furniture(collect_children(
        xml_document,
        index,
        CityGmlElement::BuildingFurnitureProperty.into(),
        config,
        deserialize_building_furniture_property,
    )?);

    Ok(building_room)
}

pub fn serialize_building_room(
    building_room: &BuildingRoom,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_building_room_attributes(building_room);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Building,
        CityGmlElement::BuildingRoom,
        attributes,
    )?;

    serialize_abstract_unoccupied_space(
        building_room.abstract_unoccupied_space(),
        xml_fragment_writer,
    )?;

    if let Some(class) = building_room.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in building_room.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in building_room.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::UsageProperty,
        )?;
    }

    for room_height in building_room.room_heights() {
        serialize_room_height_property(
            room_height,
            xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::RoomHeightProperty,
        )?;
    }

    for prop in building_room.building_furniture() {
        serialize_building_furniture_property(prop, xml_fragment_writer)?;
    }

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::Building, CityGmlElement::BuildingRoom)?;

    Ok(())
}

pub fn serialize_building_room_attributes(building_room: &BuildingRoom) -> Vec<(String, String)> {
    serialize_abstract_unoccupied_space_attributes(building_room.abstract_unoccupied_space())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    const BUILDING_ROOM: &[u8] = b"<bldg:BuildingRoom gml:id=\"ROOM_1\">
      <bldg:class>5000</bldg:class>
      <bldg:roomHeight>
        <bldg:RoomHeight>
          <bldg:highReference>ceiling</bldg:highReference>
          <bldg:lowReference>floor</bldg:lowReference>
          <bldg:status>measured</bldg:status>
          <bldg:value uom=\"m\">2.75</bldg:value>
        </bldg:RoomHeight>
      </bldg:roomHeight>
      <bldg:roomHeight>
        <bldg:RoomHeight>
          <bldg:highReference>ceiling</bldg:highReference>
          <bldg:lowReference>floor</bldg:lowReference>
          <bldg:status>estimated</bldg:status>
          <bldg:value uom=\"m\">3.1</bldg:value>
        </bldg:RoomHeight>
      </bldg:roomHeight>
      <bldg:buildingFurniture>
        <bldg:BuildingFurniture gml:id=\"FURNITURE_1\"/>
      </bldg:buildingFurniture>
    </bldg:BuildingRoom>";

    fn deserialize(xml_document: &[u8]) -> BuildingRoom {
        deserialize_building_room(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work")
    }

    #[test]
    fn test_deserialize_building_room_with_room_heights() {
        let building_room = deserialize(BUILDING_ROOM);

        assert_eq!(building_room.room_heights().len(), 2);
        assert_eq!(building_room.room_heights()[0].length().value(), 2.75);
        assert_eq!(building_room.room_heights()[1].length().value(), 3.1);
        assert_eq!(building_room.building_furniture().len(), 1);
    }

    #[test]
    fn test_round_trip_building_room_with_room_heights() {
        let building_room = deserialize(BUILDING_ROOM);

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_building_room(&building_room, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        let room_height_position = xml
            .find("<bldg:roomHeight>")
            .expect("should write roomHeight");
        let furniture_position = xml
            .find("<bldg:buildingFurniture>")
            .expect("should write buildingFurniture");
        assert!(
            room_height_position < furniture_position,
            "roomHeight must precede buildingFurniture (XSD order)"
        );

        assert_eq!(deserialize(xml.as_bytes()), building_room);
    }
}
