use crate::Error;
use crate::gml::codec::building::abstract_building_subdivision_property::{
    deserialize_abstract_building_subdivision_property,
    serialize_abstract_building_subdivision_property,
};
use crate::gml::codec::building::building_constructive_element_property::{
    deserialize_building_constructive_element_property,
    serialize_building_constructive_element_property,
};
use crate::gml::codec::building::building_installation_property::{
    deserialize_building_installation_property, serialize_building_installation_property,
};
use crate::gml::codec::building::building_room_property::{
    deserialize_building_room_property, serialize_building_room_property,
};
use crate::gml::codec::construction::{
    deserialize_abstract_construction, serialize_abstract_construction,
    serialize_abstract_construction_attributes,
};
use crate::gml::codec::core::{deserialize_address_property, serialize_address_property};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::building::{AbstractBuilding, AsAbstractBuilding, AsAbstractBuildingMut};
use ecitygml_core::model::construction::AsAbstractConstruction;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::codec::xs::{deserialize_i64, serialize_i64};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter, collect_children};
use egml::model::basic_types::Code;

pub fn deserialize_abstract_building(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractBuilding, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_building received a truncated index — caller must scan to sufficient depth"
    );

    let mut abstract_construction_result = None;
    let mut building_rooms_result = None;
    let mut building_installations_result = None;
    let mut building_constructive_elements_result = None;
    let mut building_subdivisions_result = None;
    let mut addresses_result = None;

    rayon::scope(|s| {
        s.spawn(|_| {
            abstract_construction_result = Some(deserialize_abstract_construction(
                xml_document,
                index,
                config,
            ));
        });
        s.spawn(|_| {
            building_rooms_result = Some(collect_children(
                xml_document,
                index,
                CityGmlElement::BuildingRoomProperty.into(),
                config,
                deserialize_building_room_property,
            ));
        });
        s.spawn(|_| {
            building_installations_result = Some(collect_children(
                xml_document,
                index,
                CityGmlElement::BuildingInstallationProperty.into(),
                config,
                deserialize_building_installation_property,
            ));
        });
        s.spawn(|_| {
            building_constructive_elements_result = Some(collect_children(
                xml_document,
                index,
                CityGmlElement::BuildingConstructiveElementProperty.into(),
                config,
                deserialize_building_constructive_element_property,
            ));
        });
        s.spawn(|_| {
            building_subdivisions_result = Some(collect_children(
                xml_document,
                index,
                CityGmlElement::AbstractBuildingSubdivisionProperty.into(),
                config,
                deserialize_abstract_building_subdivision_property,
            ));
        });
        s.spawn(|_| {
            addresses_result = Some(collect_children(
                xml_document,
                index,
                CityGmlElement::AddressProperty.into(),
                config,
                deserialize_address_property,
            ));
        });
    });

    let mut abstract_building = AbstractBuilding::from_abstract_construction(
        abstract_construction_result.expect("rayon::scope guarantees all spawns complete")?,
    );

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    abstract_building.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    abstract_building.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    abstract_building.set_usages(usages.into_iter().map(Into::into).collect());

    let roof_type: Option<Code> = index
        .first(CityGmlElement::RoofTypeProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    abstract_building.set_roof_type_opt(roof_type.map(Into::into));

    let storeys_above_ground: Option<i64> = index
        .first(CityGmlElement::StoreysAboveGroundProperty.into())
        .map(|x| deserialize_i64(&xml_document[x.range()]))
        .transpose()?;
    abstract_building.set_storeys_above_ground_opt(storeys_above_ground);

    let storeys_below_ground: Option<i64> = index
        .first(CityGmlElement::StoreysBelowGroundProperty.into())
        .map(|x| deserialize_i64(&xml_document[x.range()]))
        .transpose()?;
    abstract_building.set_storeys_below_ground_opt(storeys_below_ground);

    abstract_building.set_building_constructive_elements(
        building_constructive_elements_result
            .expect("rayon::scope guarantees all spawns complete")?,
    );
    abstract_building.set_building_installations(
        building_installations_result.expect("rayon::scope guarantees all spawns complete")?,
    );
    abstract_building.set_building_rooms(
        building_rooms_result.expect("rayon::scope guarantees all spawns complete")?,
    );
    abstract_building.set_building_subdivisions(
        building_subdivisions_result.expect("rayon::scope guarantees all spawns complete")?,
    );
    abstract_building
        .set_addresses(addresses_result.expect("rayon::scope guarantees all spawns complete")?);

    Ok(abstract_building)
}

pub fn serialize_abstract_building(
    abstract_building: &AbstractBuilding,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_construction(
        abstract_building.abstract_construction(),
        xml_fragment_writer,
    )?;

    if let Some(class) = abstract_building.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in abstract_building.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in abstract_building.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::UsageProperty,
        )?;
    }

    if let Some(roof_type) = abstract_building.roof_type() {
        serialize_code(
            roof_type.code(),
            xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::RoofTypeProperty,
        )?;
    }

    if let Some(storeys_above_ground) = abstract_building.storeys_above_ground() {
        serialize_i64(
            storeys_above_ground,
            xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::StoreysAboveGroundProperty,
        )?;
    }

    if let Some(storeys_below_ground) = abstract_building.storeys_below_ground() {
        serialize_i64(
            storeys_below_ground,
            xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::StoreysBelowGroundProperty,
        )?;
    }

    for prop in abstract_building.building_rooms() {
        serialize_building_room_property(prop, xml_fragment_writer)?;
    }

    for prop in abstract_building.building_installations() {
        serialize_building_installation_property(prop, xml_fragment_writer)?;
    }

    for prop in abstract_building.building_constructive_elements() {
        serialize_building_constructive_element_property(prop, xml_fragment_writer)?;
    }

    for prop in abstract_building.building_subdivisions() {
        serialize_abstract_building_subdivision_property(prop, xml_fragment_writer)?;
    }

    for address in abstract_building.addresses() {
        serialize_address_property(
            address,
            xml_fragment_writer,
            CityGmlNamespace::Building,
            CityGmlElement::AddressProperty,
        )?;
    }

    Ok(())
}

pub fn serialize_abstract_building_attributes(
    abstract_building: &AbstractBuilding,
) -> Vec<(String, String)> {
    serialize_abstract_construction_attributes(abstract_building.abstract_construction())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::building::AsAbstractBuilding;
    use ecitygml_core::model::construction::AsAbstractConstruction;
    use ecitygml_core::model::core::AsAbstractFeatureWithLifespan;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_basic_abstract_building() {
        let xml_document = b"
    <bldg:Building gml:id=\"DEBY_LOD2_4959457\">
      <creationDate>2025-01-02T00:00:00+01:00</creationDate>
      <externalReference>
        <ExternalReference>
          <targetResource>DEBYvAAAAABTMIyA</targetResource>
          <informationSystem>http://repository.gdi-de.org/schemas/adv/citygml/fdv/art.htm#_9100</informationSystem>
        </ExternalReference>
      </externalReference>
      <bldg:class>MyBuildingClass</bldg:class>
      <bldg:function>31001_3020</bldg:function>
      <bldg:roofType>1000</bldg:roofType>
      <bldg:storeysAboveGround>4</bldg:storeysAboveGround>
      <bldg:address>
        <Address>
          <xalAddress>
            <xAL:Address>
              <xAL:Country>
                <xAL:NameElement xAL:NameType=\"Name\">Germany</xAL:NameElement>
              </xAL:Country>
              <xAL:Locality xAL:Type=\"Town\">
                <xAL:NameElement xAL:NameType=\"Name\">Muenchen</xAL:NameElement>
              </xAL:Locality>
              <xAL:Thoroughfare xAL:Type=\"Street\">
                <xAL:NameElement>Arcisstrasse 21</xAL:NameElement>
              </xAL:Thoroughfare>
            </xAL:Address>
          </xalAddress>
        </Address>
      </bldg:address>
    </bldg:Building>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_building =
            deserialize_abstract_building(xml_document, &index, &DeserializationConfig::default())
                .expect("should work");
        assert!(abstract_building.date_of_construction().is_none());
        assert!(abstract_building.creation_date().is_some());
        assert_eq!(
            abstract_building.class().unwrap().code().value(),
            "MyBuildingClass"
        );
        assert_eq!(
            abstract_building
                .functions()
                .first()
                .unwrap()
                .code()
                .value(),
            "31001_3020"
        );
        assert!(abstract_building.usages().is_empty());
        assert_eq!(
            abstract_building
                .roof_type()
                .expect("should be set")
                .code()
                .value(),
            "1000"
        );
        assert_eq!(abstract_building.storeys_above_ground().unwrap(), 4);
        assert!(abstract_building.storeys_below_ground().is_none());

        assert_eq!(abstract_building.addresses().len(), 1);
        let country_names: Vec<&str> = abstract_building.addresses()[0]
            .object()
            .unwrap()
            .xal_address()
            .country()
            .unwrap()
            .name_elements()
            .iter()
            .map(|name| name.content())
            .collect();
        assert_eq!(country_names, ["Germany"]);
    }

    #[test]
    fn test_round_trip_abstract_building_with_address() {
        let xml_document = b"
    <bldg:Building gml:id=\"DEBY_LOD2_4959457\">
      <bldg:address>
        <Address>
          <xalAddress>
            <xAL:Address>
              <xAL:Country>
                <xAL:NameElement xAL:NameType=\"Name\">Germany</xAL:NameElement>
              </xAL:Country>
            </xAL:Address>
          </xalAddress>
        </Address>
      </bldg:address>
    </bldg:Building>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_building =
            deserialize_abstract_building(xml_document, &index, &DeserializationConfig::default())
                .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        xml_fragment_writer
            .write_start_event(CityGmlNamespace::Building, CityGmlElement::Building)
            .expect("should work");
        serialize_abstract_building(&abstract_building, &mut xml_fragment_writer)
            .expect("should work");
        xml_fragment_writer
            .write_end_event(CityGmlNamespace::Building, CityGmlElement::Building)
            .expect("should work");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("bldg:address"));
        assert!(xml.contains("xalAddress"));
        assert!(xml.contains("xAL:Address"));
        assert!(xml.contains("Germany"));

        let round_tripped_index =
            XmlDocumentIndex::from_scan(xml.as_bytes(), None).expect("should work");
        let round_tripped = deserialize_abstract_building(
            xml.as_bytes(),
            &round_tripped_index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(abstract_building.addresses(), round_tripped.addresses());
    }

    #[test]
    fn test_round_trip_abstract_building_with_roof_type_and_storeys() {
        let xml_document = b"
    <bldg:Building gml:id=\"DEBY_LOD2_4959457\">
      <bldg:roofType>1000</bldg:roofType>
      <bldg:storeysAboveGround>4</bldg:storeysAboveGround>
      <bldg:storeysBelowGround>2</bldg:storeysBelowGround>
    </bldg:Building>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_building =
            deserialize_abstract_building(xml_document, &index, &DeserializationConfig::default())
                .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        xml_fragment_writer
            .write_start_event(CityGmlNamespace::Building, CityGmlElement::Building)
            .expect("should work");
        serialize_abstract_building(&abstract_building, &mut xml_fragment_writer)
            .expect("should work");
        xml_fragment_writer
            .write_end_event(CityGmlNamespace::Building, CityGmlElement::Building)
            .expect("should work");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("bldg:roofType"));
        assert!(xml.contains("1000"));
        assert!(xml.contains("bldg:storeysAboveGround"));
        assert!(xml.contains("bldg:storeysBelowGround"));

        let round_tripped_index =
            XmlDocumentIndex::from_scan(xml.as_bytes(), None).expect("should work");
        let round_tripped = deserialize_abstract_building(
            xml.as_bytes(),
            &round_tripped_index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            abstract_building
                .roof_type()
                .map(|x| x.code().value().to_string()),
            round_tripped
                .roof_type()
                .map(|x| x.code().value().to_string())
        );
        assert_eq!(
            abstract_building.storeys_above_ground(),
            round_tripped.storeys_above_ground()
        );
        assert_eq!(
            abstract_building.storeys_below_ground(),
            round_tripped.storeys_below_ground()
        );
    }
}
