use crate::Error;
use crate::gml::codec::core::{
    deserialize_abstract_unoccupied_space, deserialize_occupancy_property,
    serialize_abstract_unoccupied_space, serialize_abstract_unoccupied_space_attributes,
    serialize_occupancy_property,
};
use crate::gml::codec::transportation::clearance_space_property::{
    deserialize_clearance_space_property, serialize_clearance_space_property,
};
use crate::gml::codec::transportation::enums::{
    deserialize_granularity_value, deserialize_traffic_direction_value,
    serialize_granularity_value, serialize_traffic_direction_value,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::core::{AsAbstractUnoccupiedSpace, Occupancy};
use ecitygml_core::model::transportation::{TrafficSpace, TrafficSpaceReference};
use egml::io::codec::base::{deserialize_reference, serialize_reference};
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use egml::io::util::{XmlDocumentIndex, collect_children};
use egml::model::base::Reference;
use egml::model::basic_types::Code;

pub fn deserialize_traffic_space(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<TrafficSpace, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let mut abstract_unoccupied_space_result = None;
    let mut clearance_spaces_result = None;
    let mut predecessors_result = None;
    let mut successors_result = None;

    rayon::scope(|s| {
        s.spawn(|_| {
            abstract_unoccupied_space_result = Some(deserialize_abstract_unoccupied_space(
                xml_document,
                index,
                config,
            ));
        });
        s.spawn(|_| {
            clearance_spaces_result = Some(collect_children(
                xml_document,
                index,
                CityGmlElement::ClearanceSpaceProperty.into(),
                config,
                deserialize_clearance_space_property,
            ));
        });
        s.spawn(|_| {
            predecessors_result = Some(
                index
                    .get(CityGmlElement::PredecessorProperty.into())
                    .iter()
                    .map(|index| deserialize_reference(&xml_document[index.range()]))
                    .collect::<Result<Vec<Reference>, _>>()
                    .map_err(Error::from),
            );
        });
        s.spawn(|_| {
            successors_result = Some(
                index
                    .get(CityGmlElement::SuccessorProperty.into())
                    .iter()
                    .map(|index| deserialize_reference(&xml_document[index.range()]))
                    .collect::<Result<Vec<Reference>, _>>()
                    .map_err(Error::from),
            );
        });
    });

    let granularity = index
        .first(CityGmlElement::GranularityProperty.into())
        .map(|x| deserialize_granularity_value(&xml_document[x.range()]))
        .transpose()?
        .ok_or_else(|| Error::ElementNotFound("granularity not found".into()))?;

    let mut traffic_space = TrafficSpace::from_abstract_unoccupied_space(
        abstract_unoccupied_space_result.expect("rayon::scope guarantees all spawns complete")?,
        granularity,
    );

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    traffic_space.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    traffic_space.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    traffic_space.set_usages(usages.into_iter().map(Into::into).collect());

    let traffic_direction = index
        .first(CityGmlElement::TrafficDirectionProperty.into())
        .map(|x| deserialize_traffic_direction_value(&xml_document[x.range()]))
        .transpose()?;
    traffic_space.set_traffic_direction_opt(traffic_direction);

    let occupancies: Vec<Occupancy> = index
        .get(CityGmlElement::OccupancyProperty.into())
        .iter()
        .map(|x| deserialize_occupancy_property(&xml_document[x.range()]))
        .collect::<Result<_, _>>()?;
    traffic_space.set_occupancies(occupancies);

    traffic_space.set_predecessors(
        predecessors_result
            .expect("rayon::scope guarantees all spawns complete")?
            .into_iter()
            .map(TrafficSpaceReference::from)
            .collect(),
    );
    traffic_space.set_successors(
        successors_result
            .expect("rayon::scope guarantees all spawns complete")?
            .into_iter()
            .map(TrafficSpaceReference::from)
            .collect(),
    );

    traffic_space.set_clearance_spaces(
        clearance_spaces_result.expect("rayon::scope guarantees all spawns complete")?,
    );

    Ok(traffic_space)
}

pub fn serialize_traffic_space(
    traffic_space: &TrafficSpace,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_traffic_space_attributes(traffic_space);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Transportation,
        CityGmlElement::TrafficSpace,
        attributes,
    )?;

    serialize_abstract_unoccupied_space(
        traffic_space.abstract_unoccupied_space(),
        xml_fragment_writer,
    )?;

    serialize_granularity_value(
        traffic_space.granularity(),
        xml_fragment_writer,
        CityGmlNamespace::Transportation,
        CityGmlElement::GranularityProperty,
    )?;

    if let Some(class) = traffic_space.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in traffic_space.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in traffic_space.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::UsageProperty,
        )?;
    }

    if let Some(traffic_direction) = traffic_space.traffic_direction() {
        serialize_traffic_direction_value(
            &traffic_direction,
            xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::TrafficDirectionProperty,
        )?;
    }

    for occupancy in traffic_space.occupancies() {
        serialize_occupancy_property(
            occupancy,
            xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::OccupancyProperty,
        )?;
    }

    for predecessor in traffic_space.predecessors() {
        serialize_reference(
            &Reference::from(predecessor),
            xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::PredecessorProperty,
        )?;
    }

    for successor in traffic_space.successors() {
        serialize_reference(
            &Reference::from(successor),
            xml_fragment_writer,
            CityGmlNamespace::Transportation,
            CityGmlElement::SuccessorProperty,
        )?;
    }

    for prop in traffic_space.clearance_spaces() {
        serialize_clearance_space_property(prop, xml_fragment_writer)?;
    }

    xml_fragment_writer.write_end_event(
        CityGmlNamespace::Transportation,
        CityGmlElement::TrafficSpace,
    )?;

    Ok(())
}

pub fn serialize_traffic_space_attributes(traffic_space: &TrafficSpace) -> Vec<(String, String)> {
    serialize_abstract_unoccupied_space_attributes(traffic_space.abstract_unoccupied_space())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::core::enums::SpaceType;
    use ecitygml_core::model::core::{
        AbstractSpaceBoundaryKind, AbstractThematicSurfaceKind, AsAbstractCityObject,
        AsAbstractFeature, AsAbstractSpace,
    };
    use ecitygml_core::model::transportation::TrafficArea;
    use ecitygml_core::model::transportation::enums::{GranularityValue, TrafficDirectionValue};
    use egml::io::util::Formatting;
    use egml::model::base::Id;

    #[test]
    fn test_deserialize_basic_section() {
        let xml_document =
            b"<tran:TrafficSpace gml:id=\"UUID_6e4de408-1e54-3869-b7ce-1be3f2261421\">
              <genericAttribute>
                <gen:StringAttribute>
                  <gen:name>opendrive_lane_type</gen:name>
                  <gen:value>DRIVING</gen:value>
                </gen:StringAttribute>
              </genericAttribute>
              <spaceType>open</spaceType>
              <boundary>
                <tran:TrafficArea gml:id=\"UUID_dc110e80-dadc-3c87-b864-2854cc0cb39a\">
                  <gml:name>Lane</gml:name>
                  <genericAttribute>
                    <gen:IntAttribute>
                      <gen:name>identifier_laneId</gen:name>
                      <gen:value>-1</gen:value>
                    </gen:IntAttribute>
                  </genericAttribute>
                  <tran:function>1</tran:function>
                  <tran:usage>2</tran:usage>
                </tran:TrafficArea>
              </boundary>
              <lod2MultiCurve>
                <gml:MultiCurve>
                  <gml:curveMember>
                    <gml:LineString>
                      <gml:posList srsDimension=\"3\">-52.6446227593087 1.5877425640718097 0.0 -47.64466181585868 1.6075052555478968 0.0 -42.64470087240866 1.627267947023984 0.0 -37.64473992895864 1.6470306385000706 0.0 -32.64477898550862 1.6667933299761577 0.0 -27.6448180420586 1.6865560214522448 0.0 -22.64485709860858 1.706318712928332 0.0 -17.644896155158555 1.7260814044044186 0.0 -15.898072287268029 1.7329858465699939 0.0</gml:posList>
                    </gml:LineString>
                  </gml:curveMember>
                </gml:MultiCurve>
              </lod2MultiCurve>
              <tran:function>1</tran:function>
              <tran:usage>2</tran:usage>
              <tran:granularity>lane</tran:granularity>
              <tran:trafficDirection>forwards</tran:trafficDirection>
              <tran:successor xlink:href=\"#UUID_144a6807-5844-32b2-bb34-8b2671b1afaa\"/>
            </tran:TrafficSpace>";

        let traffic_space = deserialize_traffic_space(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            traffic_space.feature_id(),
            &Id::try_from("UUID_6e4de408-1e54-3869-b7ce-1be3f2261421").expect("should work")
        );
        assert!(traffic_space.lod2_multi_surface().is_none());
        assert_eq!(traffic_space.generic_attributes().len(), 1);
        assert_eq!(traffic_space.space_type(), Some(SpaceType::Open));
        assert_eq!(
            traffic_space.functions().first().unwrap().code().value(),
            "1"
        );
        assert_eq!(traffic_space.usages().first().unwrap().code().value(), "2");
        assert_eq!(traffic_space.granularity(), &GranularityValue::Lane);
        assert_eq!(
            traffic_space.traffic_direction().unwrap(),
            TrafficDirectionValue::Forwards
        );
        let traffic_areas: Vec<&TrafficArea> = traffic_space
            .boundaries()
            .iter()
            .flat_map(|x| x.object())
            .filter_map(|x| match x {
                AbstractSpaceBoundaryKind::AbstractThematicSurfaceKind(
                    AbstractThematicSurfaceKind::TrafficArea(x),
                ) => Some(x),
                _ => None,
            })
            .collect();
        assert_eq!(traffic_areas.len(), 1);

        let traffic_area = traffic_areas.first().unwrap();
        assert_eq!(
            traffic_area.feature_id(),
            &Id::try_from("UUID_dc110e80-dadc-3c87-b864-2854cc0cb39a").expect("should work")
        );
        assert_eq!(traffic_area.generic_attributes().len(), 1);
        assert_eq!(
            traffic_area.functions().first().unwrap().code().value(),
            "1"
        );
        assert_eq!(traffic_area.usages().first().unwrap().code().value(), "2");
    }

    #[test]
    fn test_deserialize_traffic_space_with_occupancy() {
        let xml_document = b"\
<tran:TrafficSpace gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <tran:granularity>lane</tran:granularity>
    <tran:occupancy>
        <Occupancy>
            <numberOfOccupants>123</numberOfOccupants>
            <interval>myInterval</interval>
            <occupantType>myOccupantType</occupantType>
        </Occupancy>
    </tran:occupancy>
</tran:TrafficSpace>";

        let traffic_space = deserialize_traffic_space(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(traffic_space.occupancies().len(), 1);

        let occupancy = &traffic_space.occupancies()[0];
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
    fn test_serialize_traffic_space_with_occupancy() {
        let xml_document = b"\
<tran:TrafficSpace gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <tran:granularity>lane</tran:granularity>
    <tran:occupancy>
        <Occupancy>
            <numberOfOccupants>123</numberOfOccupants>
            <interval>myInterval</interval>
            <occupantType>myOccupantType</occupantType>
        </Occupancy>
    </tran:occupancy>
</tran:TrafficSpace>";

        let traffic_space = deserialize_traffic_space(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_traffic_space(&traffic_space, &mut xml_fragment_writer)
            .expect("should serialize");
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
    fn test_round_trip_traffic_space_with_occupancy() {
        let xml_document = b"\
<tran:TrafficSpace gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <tran:granularity>lane</tran:granularity>
    <tran:occupancy>
        <Occupancy>
            <numberOfOccupants>123</numberOfOccupants>
            <interval>myInterval</interval>
            <occupantType>myOccupantType</occupantType>
        </Occupancy>
    </tran:occupancy>
</tran:TrafficSpace>";

        let traffic_space = deserialize_traffic_space(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_traffic_space(&traffic_space, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        let round_tripped = deserialize_traffic_space(
            xml.as_bytes(),
            &XmlDocumentIndex::from_scan(xml.as_bytes(), None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(traffic_space.occupancies(), round_tripped.occupancies());
    }

    #[test]
    fn test_round_trip_traffic_space_with_predecessor() {
        let xml_document = b"\
<tran:TrafficSpace gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <tran:granularity>lane</tran:granularity>
    <tran:predecessor xlink:href=\"#UUID_ed2149e3-421a-3dcd-9727-54637db9d9e3\"/>
</tran:TrafficSpace>";

        let traffic_space = deserialize_traffic_space(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(traffic_space.predecessors().len(), 1);

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_traffic_space(&traffic_space, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("tran:predecessor"));
        assert!(xml.contains("UUID_ed2149e3-421a-3dcd-9727-54637db9d9e3"));

        let round_tripped = deserialize_traffic_space(
            xml.as_bytes(),
            &XmlDocumentIndex::from_scan(xml.as_bytes(), None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(traffic_space.predecessors(), round_tripped.predecessors());
    }

    #[test]
    fn test_round_trip_traffic_space_with_successor() {
        let xml_document = b"\
<tran:TrafficSpace gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <tran:granularity>lane</tran:granularity>
    <tran:successor xlink:href=\"#UUID_144a6807-5844-32b2-bb34-8b2671b1afaa\"/>
</tran:TrafficSpace>";

        let traffic_space = deserialize_traffic_space(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(traffic_space.successors().len(), 1);

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_traffic_space(&traffic_space, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("tran:successor"));
        assert!(xml.contains("UUID_144a6807-5844-32b2-bb34-8b2671b1afaa"));

        let round_tripped = deserialize_traffic_space(
            xml.as_bytes(),
            &XmlDocumentIndex::from_scan(xml.as_bytes(), None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(traffic_space.successors(), round_tripped.successors());
    }

    #[test]
    fn test_round_trip_traffic_space_with_granularity_and_traffic_direction() {
        let xml_document = b"\
<tran:TrafficSpace gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <tran:granularity>way</tran:granularity>
    <tran:trafficDirection>both</tran:trafficDirection>
</tran:TrafficSpace>";

        let traffic_space = deserialize_traffic_space(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");
        assert_eq!(traffic_space.granularity(), &GranularityValue::Way);
        assert_eq!(
            traffic_space.traffic_direction(),
            Some(TrafficDirectionValue::Both)
        );

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_traffic_space(&traffic_space, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("tran:granularity"));
        assert!(xml.contains("way"));
        assert!(xml.contains("tran:trafficDirection"));
        assert!(xml.contains("both"));

        let round_tripped = deserialize_traffic_space(
            xml.as_bytes(),
            &XmlDocumentIndex::from_scan(xml.as_bytes(), None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(traffic_space.granularity(), round_tripped.granularity());
        assert_eq!(
            traffic_space.traffic_direction(),
            round_tripped.traffic_direction()
        );
    }

    #[test]
    fn test_deserialize_traffic_space_without_granularity_returns_error() {
        let xml_document = b"\
<tran:TrafficSpace gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
</tran:TrafficSpace>";

        let result = deserialize_traffic_space(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        );

        assert!(result.is_err());
    }
}
