use crate::Error;
use crate::gml::codec::building::building_furniture_property::{
    deserialize_building_furniture_property, serialize_building_furniture_property,
};
use crate::gml::codec::building::building_installation_property::{
    deserialize_building_installation_property, serialize_building_installation_property,
};
use crate::gml::codec::building::building_room_property::{
    deserialize_building_room_property, serialize_building_room_property,
};
use crate::gml::codec::building::{
    deserialize_building_constructive_element_property,
    serialize_building_constructive_element_property,
};
use crate::gml::codec::common::{deserialize_f64, serialize_f64};
use crate::gml::codec::construction::{
    deserialize_elevation_property, serialize_elevation_property,
};
use crate::gml::codec::core::{
    deserialize_abstract_logical_space, serialize_abstract_logical_space,
    serialize_abstract_logical_space_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::building::{
    AbstractBuildingSubdivision, AsAbstractBuildingSubdivision, AsAbstractBuildingSubdivisionMut,
};
use ecitygml_core::model::construction::Elevation;
use ecitygml_core::model::core::AsAbstractLogicalSpace;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter, collect_children};
use egml::model::basic_types::Code;

pub fn deserialize_abstract_building_subdivision(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractBuildingSubdivision, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_building_subdivision received a truncated index — caller must scan to sufficient depth"
    );

    let abstract_logical_space = deserialize_abstract_logical_space(xml_document, index, config)?;
    let mut abstract_building_subdivision =
        AbstractBuildingSubdivision::from_abstract_logical_space(abstract_logical_space);

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    abstract_building_subdivision.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    abstract_building_subdivision.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    abstract_building_subdivision.set_usages(usages.into_iter().map(Into::into).collect());

    let elevations: Vec<Elevation> = index
        .get(CityGmlElement::ElevationProperty.into())
        .iter()
        .map(|x| deserialize_elevation_property(&xml_document[x.range()]))
        .collect::<Result<_, _>>()?;
    abstract_building_subdivision.set_elevations(elevations);

    let sort_key: Option<f64> = index
        .first(CityGmlElement::SortKeyProperty.into())
        .map(|x| deserialize_f64(&xml_document[x.range()]))
        .transpose()?;
    abstract_building_subdivision.set_sort_key_opt(sort_key);

    abstract_building_subdivision.set_building_constructive_elements(collect_children(
        xml_document,
        index,
        CityGmlElement::BuildingConstructiveElementProperty.into(),
        config,
        deserialize_building_constructive_element_property,
    )?);
    abstract_building_subdivision.set_building_furniture(collect_children(
        xml_document,
        index,
        CityGmlElement::BuildingFurnitureProperty.into(),
        config,
        deserialize_building_furniture_property,
    )?);
    abstract_building_subdivision.set_building_installations(collect_children(
        xml_document,
        index,
        CityGmlElement::BuildingInstallationProperty.into(),
        config,
        deserialize_building_installation_property,
    )?);
    abstract_building_subdivision.set_building_rooms(collect_children(
        xml_document,
        index,
        CityGmlElement::BuildingRoomProperty.into(),
        config,
        deserialize_building_room_property,
    )?);

    Ok(abstract_building_subdivision)
}

pub fn serialize_abstract_building_subdivision(
    abstract_building_subdivision: &AbstractBuildingSubdivision,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_logical_space(
        abstract_building_subdivision.abstract_logical_space(),
        xml_fragment_writer,
    )?;

    if let Some(class) = abstract_building_subdivision.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in abstract_building_subdivision.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in abstract_building_subdivision.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::UsageProperty,
        )?;
    }

    for elevation in abstract_building_subdivision.elevations() {
        serialize_elevation_property(
            elevation,
            xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::ElevationProperty,
        )?;
    }

    if let Some(sort_key) = abstract_building_subdivision.sort_key() {
        serialize_f64(
            sort_key,
            xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::SortKeyProperty,
        )?;
    }

    for prop in abstract_building_subdivision.building_constructive_elements() {
        serialize_building_constructive_element_property(prop, xml_fragment_writer)?;
    }

    for prop in abstract_building_subdivision.building_furniture() {
        serialize_building_furniture_property(prop, xml_fragment_writer)?;
    }

    for prop in abstract_building_subdivision.building_installations() {
        serialize_building_installation_property(prop, xml_fragment_writer)?;
    }

    for prop in abstract_building_subdivision.building_rooms() {
        serialize_building_room_property(prop, xml_fragment_writer)?;
    }

    Ok(())
}

pub fn serialize_abstract_building_subdivision_attributes(
    abstract_building_subdivision: &AbstractBuildingSubdivision,
) -> Vec<(String, String)> {
    serialize_abstract_logical_space_attributes(
        abstract_building_subdivision.abstract_logical_space(),
    )
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::core::AsAbstractFeature;
    use egml::io::util::Formatting;

    /// A subdivision with every property of `AbstractBuildingSubdivisionType`, in schema order.
    const SUBDIVISION: &[u8] = br#"<bldg:Storey gml:id="storey">
      <bldg:class>Entrance Floor</bldg:class>
      <bldg:elevation>
        <con:Elevation>
          <con:elevationReference>lowestGroundPoint</con:elevationReference>
          <con:elevationValue>2.7</con:elevationValue>
        </con:Elevation>
      </bldg:elevation>
      <bldg:sortKey>2</bldg:sortKey>
      <bldg:buildingConstructiveElement>
        <bldg:BuildingConstructiveElement gml:id="element"/>
      </bldg:buildingConstructiveElement>
      <bldg:buildingFurniture>
        <bldg:BuildingFurniture gml:id="furniture"/>
      </bldg:buildingFurniture>
      <bldg:buildingInstallation>
        <bldg:BuildingInstallation gml:id="installation"/>
      </bldg:buildingInstallation>
      <bldg:buildingRoom>
        <bldg:BuildingRoom gml:id="room"/>
      </bldg:buildingRoom>
    </bldg:Storey>"#;

    fn deserialized() -> AbstractBuildingSubdivision {
        deserialize_abstract_building_subdivision(
            SUBDIVISION,
            &XmlDocumentIndex::from_scan(SUBDIVISION, None).expect("should scan"),
            &DeserializationConfig::default(),
        )
        .expect("should deserialize")
    }

    #[test]
    fn test_deserialize_elevation_and_sort_key() {
        let subdivision = deserialized();

        assert_eq!(
            subdivision.class().map(|x| x.value()),
            Some("Entrance Floor")
        );
        let [elevation] = subdivision.elevations() else {
            panic!("expected one elevation, got {:?}", subdivision.elevations());
        };
        assert_eq!(elevation.elevation_reference().value(), "lowestGroundPoint");
        assert_eq!(elevation.elevation_value().coordinates(), [2.7]);
        assert_eq!(subdivision.sort_key(), Some(2.0));
    }

    #[test]
    fn test_deserialize_nested_features() {
        let subdivision = deserialized();
        let id =
            |object: Option<&dyn AsAbstractFeature>| object.map(|x| x.feature_id().to_string());

        assert_eq!(
            [
                id(subdivision.building_constructive_elements()[0]
                    .object()
                    .map(|x| x as _)),
                id(subdivision.building_furniture()[0].object().map(|x| x as _)),
                id(subdivision.building_installations()[0]
                    .object()
                    .map(|x| x as _)),
                id(subdivision.building_rooms()[0].object().map(|x| x as _)),
            ],
            ["element", "furniture", "installation", "room"].map(|x| Some(x.to_string()))
        );
    }

    #[test]
    fn test_serialize_in_schema_order() {
        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_abstract_building_subdivision(&deserialized(), &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        let positions: Vec<usize> = [
            "<bldg:class>",
            "<bldg:elevation>",
            "<bldg:sortKey>2</bldg:sortKey>",
            "<bldg:buildingConstructiveElement>",
            "<bldg:buildingFurniture>",
            "<bldg:buildingInstallation>",
            "<bldg:buildingRoom>",
        ]
        .iter()
        .map(|tag| {
            xml.find(tag)
                .unwrap_or_else(|| panic!("{tag} missing in {xml}"))
        })
        .collect();
        assert!(positions.is_sorted(), "not in schema order: {xml}");
    }
}
