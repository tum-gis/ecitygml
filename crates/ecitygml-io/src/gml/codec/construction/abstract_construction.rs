use crate::Error;
use crate::gml::codec::construction::height_property::{
    deserialize_height_property, serialize_height_property,
};
use crate::gml::codec::core::{
    deserialize_abstract_occupied_space, deserialize_occupancy_property,
    serialize_abstract_occupied_space, serialize_abstract_occupied_space_attributes,
    serialize_occupancy_property,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::construction::{
    AbstractConstruction, AsAbstractConstruction, AsAbstractConstructionMut, Height,
};
use ecitygml_core::model::core::{AsAbstractOccupiedSpace, Occupancy};
use egml::io::codec::xs::{deserialize_date, serialize_date};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_abstract_construction(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractConstruction, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_construction received a truncated index — caller must scan to sufficient depth"
    );

    let abstract_occupied_space = deserialize_abstract_occupied_space(xml_document, index, config)?;
    let mut abstract_construction =
        AbstractConstruction::from_abstract_occupied_space(abstract_occupied_space);

    let date_of_construction = index
        .first(CityGmlElement::DateOfConstructionProperty.into())
        .map(|x| deserialize_date(&xml_document[x.range()], config.gml_config()))
        .transpose()?;
    abstract_construction.set_date_of_construction(date_of_construction);

    let date_of_demolition = index
        .first(CityGmlElement::DateOfDemolitionProperty.into())
        .map(|x| deserialize_date(&xml_document[x.range()], config.gml_config()))
        .transpose()?;
    abstract_construction.set_date_of_demolition(date_of_demolition);

    let heights: Vec<Height> = index
        .get(CityGmlElement::HeightProperty.into())
        .iter()
        .map(|x| deserialize_height_property(&xml_document[x.range()]))
        .collect::<Result<_, _>>()?;
    abstract_construction.set_heights(heights);

    let occupancies: Vec<Occupancy> = index
        .get(CityGmlElement::OccupancyProperty.into())
        .iter()
        .map(|x| deserialize_occupancy_property(&xml_document[x.range()]))
        .collect::<Result<_, _>>()?;
    abstract_construction.set_occupancies(occupancies);

    Ok(abstract_construction)
}

pub fn serialize_abstract_construction(
    abstract_construction: &AbstractConstruction,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_occupied_space(
        abstract_construction.abstract_occupied_space(),
        xml_fragment_writer,
    )?;

    if let Some(date_of_construction) = abstract_construction.date_of_construction() {
        serialize_date(
            *date_of_construction,
            xml_fragment_writer,
            CityGmlNamespace::Construction,
            CityGmlElement::DateOfConstructionProperty,
        )?;
    }

    if let Some(date_of_demolition) = abstract_construction.date_of_demolition() {
        serialize_date(
            *date_of_demolition,
            xml_fragment_writer,
            CityGmlNamespace::Construction,
            CityGmlElement::DateOfDemolitionProperty,
        )?;
    }

    for height in abstract_construction.heights() {
        serialize_height_property(
            height,
            xml_fragment_writer,
            CityGmlNamespace::Construction,
            CityGmlElement::HeightProperty,
        )?;
    }

    for occupancy in abstract_construction.occupancies() {
        serialize_occupancy_property(
            occupancy,
            xml_fragment_writer,
            CityGmlNamespace::Construction,
            CityGmlElement::OccupancyProperty,
        )?;
    }

    Ok(())
}

pub fn serialize_abstract_construction_attributes(
    abstract_construction: &AbstractConstruction,
) -> Vec<(String, String)> {
    serialize_abstract_occupied_space_attributes(abstract_construction.abstract_occupied_space())
}

#[cfg(test)]
mod tests {
    use super::*;

    use chrono::{Datelike, NaiveDate, Timelike};
    use ecitygml_core::model::construction::AsAbstractConstruction;
    use ecitygml_core::model::construction::enums::HeightStatusValue;
    use ecitygml_core::model::core::AsAbstractFeatureWithLifespan;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_basic_abstract_construction() {
        let xml_document = b"
<bldg:Building gml:id=\"DEBY_LOD2_4959457\">
      <creationDate>2025-03-02T15:16:17+01:00</creationDate>
      <externalReference>
        <ExternalReference>
          <targetResource>DEBYvAAAAABTMIyA</targetResource>
          <informationSystem>http://repository.gdi-de.org/schemas/adv/citygml/fdv/art.htm#_9100</informationSystem>
        </ExternalReference>
      </externalReference>
      <genericAttribute>
        <gen:StringAttribute>
          <gen:name>DatenquelleBodenhoehe</gen:name>
          <gen:value>1100</gen:value>
        </gen:StringAttribute>
      </genericAttribute>
      <con:height>
        <con:Height>
          <con:highReference>topOfConstruction</con:highReference>
          <con:lowReference>lowestGroundPoint</con:lowReference>
          <con:status>measured</con:status>
          <con:value uom=\"urn:adv:uom:m\">19.408</con:value>
        </con:Height>
      </con:height>
    </bldg:Building>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_construction = deserialize_abstract_construction(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");
        let creation_date = abstract_construction
            .creation_date()
            .expect("should have creation date");
        assert_eq!(creation_date.local().year(), 2025);
        assert_eq!(creation_date.local().month(), 3);
        assert_eq!(creation_date.local().day(), 2);
        assert_eq!(creation_date.local().hour(), 15);
        assert_eq!(creation_date.local().minute(), 16);
        assert_eq!(creation_date.local().second(), 17);

        assert_eq!(abstract_construction.heights().len(), 1);
        let height = &abstract_construction.heights()[0];
        assert_eq!(height.high_reference().value(), "topOfConstruction");
        assert_eq!(height.low_reference().value(), "lowestGroundPoint");
        assert_eq!(height.status(), HeightStatusValue::Measured);
        assert_eq!(height.length().uom(), "urn:adv:uom:m");
        assert_eq!(height.length().value(), 19.408);
    }

    #[test]
    fn test_round_trip_abstract_construction_with_height() {
        let xml_document = b"\
<bldg:Building gml:id=\"DEBY_LOD2_4959457\">
    <con:height>
        <con:Height>
            <con:highReference>topOfConstruction</con:highReference>
            <con:lowReference>lowestGroundPoint</con:lowReference>
            <con:status>measured</con:status>
            <con:value uom=\"urn:adv:uom:m\">11.715</con:value>
        </con:Height>
    </con:height>
</bldg:Building>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_construction = deserialize_abstract_construction(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(abstract_construction.heights().len(), 1);

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        xml_fragment_writer
            .write_start_event(CityGmlNamespace::Building, CityGmlElement::Building)
            .expect("should work");
        serialize_abstract_construction(&abstract_construction, &mut xml_fragment_writer)
            .expect("should serialize");
        xml_fragment_writer
            .write_end_event(CityGmlNamespace::Building, CityGmlElement::Building)
            .expect("should work");
        let xml = {
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        };

        let index = XmlDocumentIndex::from_scan(&xml, None).expect("should work");
        let round_tripped =
            deserialize_abstract_construction(&xml, &index, &DeserializationConfig::default())
                .expect("should work");

        assert_eq!(abstract_construction.heights(), round_tripped.heights());
    }

    #[test]
    fn test_deserialize_abstract_construction_with_occupancy() {
        let xml_document = b"\
<bldg:Building gml:id=\"DEBY_LOD2_4959457\">
    <con:occupancy>
        <Occupancy>
            <numberOfOccupants>123</numberOfOccupants>
            <interval>myInterval</interval>
            <occupantType>myOccupantType</occupantType>
        </Occupancy>
    </con:occupancy>
</bldg:Building>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_construction = deserialize_abstract_construction(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(abstract_construction.occupancies().len(), 1);

        let occupancy = &abstract_construction.occupancies()[0];
        assert_eq!(occupancy.number_of_occupants(), 123);
        assert_eq!(
            occupancy.interval().expect("must exist").code().value(),
            "myInterval"
        );
        assert_eq!(
            occupancy
                .occupant_type()
                .expect("must exist")
                .code()
                .value(),
            "myOccupantType"
        );
    }

    #[test]
    fn test_serialize_abstract_construction_with_occupancy() {
        let xml_document = b"\
<bldg:Building gml:id=\"DEBY_LOD2_4959457\">
    <con:occupancy>
        <Occupancy>
            <numberOfOccupants>123</numberOfOccupants>
            <interval>myInterval</interval>
            <occupantType>myOccupantType</occupantType>
        </Occupancy>
    </con:occupancy>
</bldg:Building>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_construction = deserialize_abstract_construction(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_abstract_construction(&abstract_construction, &mut xml_fragment_writer)
            .expect("should work");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("con:occupancy"));
        assert!(xml.contains("Occupancy"));
        assert!(xml.contains("numberOfOccupants"));
        assert!(xml.contains("123"));
        assert!(xml.contains("myInterval"));
        assert!(xml.contains("myOccupantType"));
    }

    #[test]
    fn test_round_trip_abstract_construction_with_occupancy() {
        let xml_document = b"\
<bldg:Building gml:id=\"DEBY_LOD2_4959457\">
    <con:occupancy>
        <Occupancy>
            <numberOfOccupants>123</numberOfOccupants>
            <interval>myInterval</interval>
            <occupantType>myOccupantType</occupantType>
        </Occupancy>
    </con:occupancy>
</bldg:Building>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_construction = deserialize_abstract_construction(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        xml_fragment_writer
            .write_start_event(CityGmlNamespace::Building, CityGmlElement::Building)
            .expect("should work");
        serialize_abstract_construction(&abstract_construction, &mut xml_fragment_writer)
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

        let round_tripped_index =
            XmlDocumentIndex::from_scan(xml.as_bytes(), None).expect("should work");
        let round_tripped = deserialize_abstract_construction(
            xml.as_bytes(),
            &round_tripped_index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            abstract_construction.occupancies(),
            round_tripped.occupancies()
        );
    }

    #[test]
    fn test_round_trip_abstract_construction_with_date_of_construction_and_demolition() {
        let xml_document = b"\
<bldg:Building gml:id=\"DEBY_LOD2_4959457\">
    <con:dateOfConstruction>2010-05-20</con:dateOfConstruction>
    <con:dateOfDemolition>2020-11-03</con:dateOfDemolition>
</bldg:Building>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_construction = deserialize_abstract_construction(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            abstract_construction
                .date_of_construction()
                .map(|date| date.date()),
            NaiveDate::from_ymd_opt(2010, 5, 20)
        );
        assert_eq!(
            abstract_construction
                .date_of_demolition()
                .map(|date| date.date()),
            NaiveDate::from_ymd_opt(2020, 11, 3)
        );

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        xml_fragment_writer
            .write_start_event(CityGmlNamespace::Building, CityGmlElement::Building)
            .expect("should work");
        serialize_abstract_construction(&abstract_construction, &mut xml_fragment_writer)
            .expect("should serialize");
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

        assert!(xml.contains("con:dateOfConstruction"));
        assert!(xml.contains("2010-05-20"));
        assert!(xml.contains("con:dateOfDemolition"));
        assert!(xml.contains("2020-11-03"));

        let round_tripped_index =
            XmlDocumentIndex::from_scan(xml.as_bytes(), None).expect("should work");
        let round_tripped = deserialize_abstract_construction(
            xml.as_bytes(),
            &round_tripped_index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            abstract_construction.date_of_construction(),
            round_tripped.date_of_construction()
        );
        assert_eq!(
            abstract_construction.date_of_demolition(),
            round_tripped.date_of_demolition()
        );
    }
}
