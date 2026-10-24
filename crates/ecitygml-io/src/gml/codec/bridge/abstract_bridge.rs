use crate::Error;
use crate::gml::codec::bridge::bridge_constructive_element_property::{
    deserialize_bridge_constructive_element_property,
    serialize_bridge_constructive_element_property,
};
use crate::gml::codec::bridge::bridge_furniture_property::{
    deserialize_bridge_furniture_property, serialize_bridge_furniture_property,
};
use crate::gml::codec::bridge::bridge_installation_property::{
    deserialize_bridge_installation_property, serialize_bridge_installation_property,
};
use crate::gml::codec::bridge::bridge_room_property::{
    deserialize_bridge_room_property, serialize_bridge_room_property,
};
use crate::gml::codec::common::{deserialize_bool, serialize_bool};
use crate::gml::codec::construction::{
    deserialize_abstract_construction, serialize_abstract_construction,
    serialize_abstract_construction_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::bridge::{AbstractBridge, AsAbstractBridge, AsAbstractBridgeMut};
use ecitygml_core::model::construction::AsAbstractConstruction;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter, collect_children};
use egml::model::basic_types::Code;

pub fn deserialize_abstract_bridge(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractBridge, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_bridge received a truncated index — caller must scan to sufficient depth"
    );

    let mut abstract_construction_result = None;
    let mut bridge_installations_result = None;
    let mut bridge_constructive_elements_result = None;
    let mut bridge_rooms_result = None;
    let mut bridge_furniture_result = None;

    rayon::scope(|s| {
        s.spawn(|_| {
            abstract_construction_result = Some(deserialize_abstract_construction(
                xml_document,
                index,
                config,
            ));
        });
        s.spawn(|_| {
            bridge_installations_result = Some(collect_children(
                xml_document,
                index,
                CityGmlElement::BridgeInstallationProperty.into(),
                config,
                deserialize_bridge_installation_property,
            ));
        });
        s.spawn(|_| {
            bridge_constructive_elements_result = Some(collect_children(
                xml_document,
                index,
                CityGmlElement::BridgeConstructiveElementProperty.into(),
                config,
                deserialize_bridge_constructive_element_property,
            ));
        });
        s.spawn(|_| {
            bridge_rooms_result = Some(collect_children(
                xml_document,
                index,
                CityGmlElement::BridgeRoomProperty.into(),
                config,
                deserialize_bridge_room_property,
            ));
        });
        s.spawn(|_| {
            bridge_furniture_result = Some(collect_children(
                xml_document,
                index,
                CityGmlElement::BridgeFurnitureProperty.into(),
                config,
                deserialize_bridge_furniture_property,
            ));
        });
    });

    let mut abstract_bridge = AbstractBridge::from_abstract_construction(
        abstract_construction_result.expect("rayon::scope guarantees all spawns complete")?,
    );

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    abstract_bridge.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    abstract_bridge.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    abstract_bridge.set_usages(usages.into_iter().map(Into::into).collect());

    let is_movable: Option<bool> = index
        .first(CityGmlElement::IsMovableProperty.into())
        .map(|x| deserialize_bool(&xml_document[x.range()]))
        .transpose()?;
    abstract_bridge.set_is_movable_opt(is_movable);

    abstract_bridge.set_bridge_installations(
        bridge_installations_result.expect("rayon::scope guarantees all spawns complete")?,
    );
    abstract_bridge.set_bridge_constructive_elements(
        bridge_constructive_elements_result
            .expect("rayon::scope guarantees all spawns complete")?,
    );
    abstract_bridge.set_bridge_rooms(
        bridge_rooms_result.expect("rayon::scope guarantees all spawns complete")?,
    );
    abstract_bridge.set_bridge_furniture(
        bridge_furniture_result.expect("rayon::scope guarantees all spawns complete")?,
    );

    Ok(abstract_bridge)
}

pub fn serialize_abstract_bridge(
    abstract_bridge: &AbstractBridge,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_construction(abstract_bridge.abstract_construction(), xml_fragment_writer)?;

    if let Some(is_movable) = abstract_bridge.is_movable() {
        serialize_bool(
            is_movable,
            xml_fragment_writer,
            CityGmlNamespace::Bridge,
            CityGmlElement::IsMovableProperty,
        )?;
    }

    if let Some(class) = abstract_bridge.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Bridge,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in abstract_bridge.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::Bridge,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in abstract_bridge.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::Bridge,
            CityGmlElement::UsageProperty,
        )?;
    }

    for prop in abstract_bridge.bridge_installations() {
        serialize_bridge_installation_property(prop, xml_fragment_writer)?;
    }
    for prop in abstract_bridge.bridge_constructive_elements() {
        serialize_bridge_constructive_element_property(prop, xml_fragment_writer)?;
    }
    for prop in abstract_bridge.bridge_rooms() {
        serialize_bridge_room_property(prop, xml_fragment_writer)?;
    }
    for prop in abstract_bridge.bridge_furniture() {
        serialize_bridge_furniture_property(prop, xml_fragment_writer)?;
    }

    Ok(())
}

pub fn serialize_abstract_bridge_attributes(
    abstract_bridge: &AbstractBridge,
) -> Vec<(String, String)> {
    serialize_abstract_construction_attributes(abstract_bridge.abstract_construction())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_abstract_bridge_with_is_movable() {
        let xml_document = b"\
<brid:Bridge gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <brid:isMovable>true</brid:isMovable>
</brid:Bridge>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_bridge =
            deserialize_abstract_bridge(xml_document, &index, &DeserializationConfig::default())
                .expect("should work");

        assert_eq!(abstract_bridge.is_movable(), Some(true));
    }

    #[test]
    fn test_round_trip_abstract_bridge_with_is_movable() {
        let xml_document = b"\
<brid:Bridge gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <brid:isMovable>true</brid:isMovable>
</brid:Bridge>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_bridge =
            deserialize_abstract_bridge(xml_document, &index, &DeserializationConfig::default())
                .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        xml_fragment_writer
            .write_start_event(CityGmlNamespace::Bridge, CityGmlElement::Bridge)
            .expect("should work");
        serialize_abstract_bridge(&abstract_bridge, &mut xml_fragment_writer).expect("should work");
        xml_fragment_writer
            .write_end_event(CityGmlNamespace::Bridge, CityGmlElement::Bridge)
            .expect("should work");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("brid:isMovable"));
        assert!(xml.contains("true"));

        let round_tripped_index =
            XmlDocumentIndex::from_scan(xml.as_bytes(), None).expect("should work");
        let round_tripped = deserialize_abstract_bridge(
            xml.as_bytes(),
            &round_tripped_index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(abstract_bridge.is_movable(), round_tripped.is_movable());
    }
}
