use crate::Error;
use crate::gml::codec::core::{
    deserialize_abstract_unoccupied_space, deserialize_occupancy_property,
    serialize_abstract_unoccupied_space, serialize_abstract_unoccupied_space_attributes,
    serialize_occupancy_property,
};
use crate::gml::codec::transportation::auxiliary_traffic_space_property::{
    deserialize_auxiliary_traffic_space_property, serialize_auxiliary_traffic_space_property,
};
use crate::gml::codec::transportation::enums::{
    deserialize_traffic_direction_value, serialize_traffic_direction_value,
};
use crate::gml::codec::transportation::hole_property::{
    deserialize_hole_property, serialize_hole_property,
};
use crate::gml::codec::transportation::marking_property::{
    deserialize_marking_property, serialize_marking_property,
};
use crate::gml::codec::transportation::traffic_space_property::{
    deserialize_traffic_space_property, serialize_traffic_space_property,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::core::{AsAbstractUnoccupiedSpace, Occupancy};
use ecitygml_core::model::transportation::{
    AbstractTransportationSpace, AsAbstractTransportationSpace, AsAbstractTransportationSpaceMut,
};
use egml::io::util::XmlDocumentIndex;
use egml::io::util::{ChunkedSink, XmlFragmentWriter, collect_children};

pub fn deserialize_abstract_transportation_space(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractTransportationSpace, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_transportation_space received a truncated index — caller must scan to sufficient depth"
    );

    let mut abstract_unoccupied_space_result = None;
    let mut traffic_spaces_result = None;
    let mut auxiliary_traffic_spaces_result = None;
    let mut markings_result = None;
    let mut holes_result = None;

    rayon::scope(|s| {
        s.spawn(|_| {
            abstract_unoccupied_space_result = Some(deserialize_abstract_unoccupied_space(
                xml_document,
                index,
                config,
            ));
        });
        s.spawn(|_| {
            traffic_spaces_result = Some(collect_children(
                xml_document,
                index,
                CityGmlElement::TrafficSpaceProperty.into(),
                config,
                deserialize_traffic_space_property,
            ));
        });
        s.spawn(|_| {
            auxiliary_traffic_spaces_result = Some(collect_children(
                xml_document,
                index,
                CityGmlElement::AuxiliaryTrafficSpaceProperty.into(),
                config,
                deserialize_auxiliary_traffic_space_property,
            ));
        });
        s.spawn(|_| {
            markings_result = Some(collect_children(
                xml_document,
                index,
                CityGmlElement::MarkingProperty.into(),
                config,
                deserialize_marking_property,
            ));
        });
        s.spawn(|_| {
            holes_result = Some(collect_children(
                xml_document,
                index,
                CityGmlElement::HoleProperty.into(),
                config,
                deserialize_hole_property,
            ));
        });
    });

    let mut abstract_transportation_space =
        AbstractTransportationSpace::from_abstract_unoccupied_space(
            abstract_unoccupied_space_result
                .expect("rayon::scope guarantees all spawns complete")?,
        );

    let traffic_direction = index
        .first(CityGmlElement::TrafficDirectionProperty.into())
        .map(|x| deserialize_traffic_direction_value(&xml_document[x.range()]))
        .transpose()?;
    abstract_transportation_space.set_traffic_direction_opt(traffic_direction);

    let occupancies: Vec<Occupancy> = index
        .get(CityGmlElement::OccupancyProperty.into())
        .iter()
        .map(|x| deserialize_occupancy_property(&xml_document[x.range()]))
        .collect::<Result<_, _>>()?;
    abstract_transportation_space.set_occupancies(occupancies);

    abstract_transportation_space.set_traffic_spaces(
        traffic_spaces_result.expect("rayon::scope guarantees all spawns complete")?,
    );
    abstract_transportation_space.set_auxiliary_traffic_spaces(
        auxiliary_traffic_spaces_result.expect("rayon::scope guarantees all spawns complete")?,
    );
    abstract_transportation_space
        .set_markings(markings_result.expect("rayon::scope guarantees all spawns complete")?);
    abstract_transportation_space
        .set_holes(holes_result.expect("rayon::scope guarantees all spawns complete")?);

    Ok(abstract_transportation_space)
}

pub fn serialize_abstract_transportation_space(
    abstract_transportation_space: &AbstractTransportationSpace,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_unoccupied_space(
        abstract_transportation_space.abstract_unoccupied_space(),
        xml_fragment_writer,
    )?;

    if let Some(traffic_direction) = abstract_transportation_space.traffic_direction() {
        serialize_traffic_direction_value(
            &traffic_direction,
            xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::TrafficDirectionProperty,
        )?;
    }

    for occupancy in abstract_transportation_space.occupancies() {
        serialize_occupancy_property(
            occupancy,
            xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::OccupancyProperty,
        )?;
    }

    for traffic_space_property in abstract_transportation_space.traffic_spaces() {
        serialize_traffic_space_property(traffic_space_property, xml_fragment_writer)?;
    }

    for auxiliary_traffic_space_property in abstract_transportation_space.auxiliary_traffic_spaces()
    {
        serialize_auxiliary_traffic_space_property(
            auxiliary_traffic_space_property,
            xml_fragment_writer,
        )?;
    }

    for marking_property in abstract_transportation_space.markings() {
        serialize_marking_property(marking_property, xml_fragment_writer)?;
    }

    for hole_property in abstract_transportation_space.holes() {
        serialize_hole_property(hole_property, xml_fragment_writer)?;
    }

    Ok(())
}

pub fn serialize_abstract_transportation_space_attributes(
    abstract_transportation_space: &AbstractTransportationSpace,
) -> Vec<(String, String)> {
    serialize_abstract_unoccupied_space_attributes(
        abstract_transportation_space.abstract_unoccupied_space(),
    )
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::transportation::AsAbstractTransportationSpace;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_abstract_transportation_space_with_occupancy() {
        let xml_document = b"\
<tran:Road gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <tran:occupancy>
        <Occupancy>
            <numberOfOccupants>123</numberOfOccupants>
            <interval>myInterval</interval>
            <occupantType>myOccupantType</occupantType>
        </Occupancy>
    </tran:occupancy>
</tran:Road>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_transportation_space = deserialize_abstract_transportation_space(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(abstract_transportation_space.occupancies().len(), 1);

        let occupancy = &abstract_transportation_space.occupancies()[0];
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
    fn test_serialize_abstract_transportation_space_with_occupancy() {
        let xml_document = b"\
<tran:Road gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <tran:occupancy>
        <Occupancy>
            <numberOfOccupants>123</numberOfOccupants>
            <interval>myInterval</interval>
            <occupantType>myOccupantType</occupantType>
        </Occupancy>
    </tran:occupancy>
</tran:Road>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_transportation_space = deserialize_abstract_transportation_space(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        xml_fragment_writer
            .write_start_event(CityGmlNamespace::Transportation, CityGmlElement::Road)
            .expect("should work");
        serialize_abstract_transportation_space(
            &abstract_transportation_space,
            &mut xml_fragment_writer,
        )
        .expect("should serialize");
        xml_fragment_writer
            .write_end_event(CityGmlNamespace::Transportation, CityGmlElement::Road)
            .expect("should work");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("tran:occupancy"));
        assert!(xml.contains("Occupancy"));
        assert!(xml.contains("numberOfOccupants"));
        assert!(xml.contains("123"));
        assert!(xml.contains("myInterval"));
        assert!(xml.contains("myOccupantType"));
    }

    #[test]
    fn test_round_trip_abstract_transportation_space_with_occupancy() {
        let xml_document = b"\
<tran:Road gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <tran:occupancy>
        <Occupancy>
            <numberOfOccupants>123</numberOfOccupants>
            <interval>myInterval</interval>
            <occupantType>myOccupantType</occupantType>
        </Occupancy>
    </tran:occupancy>
</tran:Road>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_transportation_space = deserialize_abstract_transportation_space(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        xml_fragment_writer
            .write_start_event(CityGmlNamespace::Transportation, CityGmlElement::Road)
            .expect("should work");
        serialize_abstract_transportation_space(
            &abstract_transportation_space,
            &mut xml_fragment_writer,
        )
        .expect("should serialize");
        xml_fragment_writer
            .write_end_event(CityGmlNamespace::Transportation, CityGmlElement::Road)
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
        let round_tripped = deserialize_abstract_transportation_space(
            xml.as_bytes(),
            &round_tripped_index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            abstract_transportation_space.occupancies(),
            round_tripped.occupancies()
        );
    }
}
