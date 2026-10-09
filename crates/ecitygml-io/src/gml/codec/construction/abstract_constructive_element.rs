use crate::Error;
use crate::gml::codec::common::{deserialize_bool, serialize_bool};
use crate::gml::codec::construction::abstract_filling_element_property::{
    deserialize_abstract_filling_element_property, serialize_abstract_filling_element_property,
};
use crate::gml::codec::core::{
    deserialize_abstract_occupied_space, serialize_abstract_occupied_space,
    serialize_abstract_occupied_space_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::construction::{
    AbstractConstructiveElement, AsAbstractConstructiveElement, AsAbstractConstructiveElementMut,
};
use ecitygml_core::model::core::AsAbstractOccupiedSpace;
use egml::io::util::XmlDocumentIndex;
use egml::io::util::{ChunkedSink, XmlFragmentWriter, collect_children};

pub fn deserialize_abstract_constructive_element(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractConstructiveElement, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_constructive_element received a truncated index — caller must scan to sufficient depth"
    );

    let mut abstract_occupied_space_result = None;
    let mut filling_elements_result = None;

    rayon::scope(|s| {
        s.spawn(|_| {
            abstract_occupied_space_result = Some(deserialize_abstract_occupied_space(
                xml_document,
                index,
                config,
            ));
        });
        s.spawn(|_| {
            filling_elements_result = Some(collect_children(
                xml_document,
                index,
                CityGmlElement::AbstractFillingElementProperty.into(),
                config,
                deserialize_abstract_filling_element_property,
            ));
        });
    });

    let mut abstract_constructive_element =
        AbstractConstructiveElement::from_abstract_occupied_space(
            abstract_occupied_space_result.expect("rayon::scope guarantees all spawns complete")?,
        );
    abstract_constructive_element.set_fillings(
        filling_elements_result.expect("rayon::scope guarantees all spawns complete")?,
    );

    let is_structural_element: Option<bool> = index
        .first(CityGmlElement::IsStructuralElementProperty.into())
        .map(|x| deserialize_bool(&xml_document[x.range()]))
        .transpose()?;
    abstract_constructive_element.set_is_structural_element(is_structural_element);

    Ok(abstract_constructive_element)
}

pub fn serialize_abstract_constructive_element(
    abstract_constructive_element: &AbstractConstructiveElement,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_occupied_space(
        abstract_constructive_element.abstract_occupied_space(),
        xml_fragment_writer,
    )?;

    if let Some(is_structural_element) = abstract_constructive_element.is_structural_element() {
        serialize_bool(
            is_structural_element,
            xml_fragment_writer,
            CityGmlNamespace::Construction,
            CityGmlElement::IsStructuralElementProperty,
        )?;
    }

    for prop in abstract_constructive_element.fillings() {
        serialize_abstract_filling_element_property(prop, xml_fragment_writer)?;
    }

    Ok(())
}

pub fn serialize_abstract_constructive_element_attributes(
    abstract_constructive_element: &AbstractConstructiveElement,
) -> Vec<(String, String)> {
    serialize_abstract_occupied_space_attributes(
        abstract_constructive_element.abstract_occupied_space(),
    )
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_abstract_constructive_element_with_is_structural_element() {
        let xml_document = b"\
<bldg:BuildingConstructiveElement gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <con:isStructuralElement>true</con:isStructuralElement>
</bldg:BuildingConstructiveElement>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_constructive_element = deserialize_abstract_constructive_element(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            abstract_constructive_element.is_structural_element(),
            Some(true)
        );
    }

    #[test]
    fn test_round_trip_abstract_constructive_element_with_is_structural_element() {
        let xml_document = b"\
<bldg:BuildingConstructiveElement gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <con:isStructuralElement>true</con:isStructuralElement>
</bldg:BuildingConstructiveElement>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_constructive_element = deserialize_abstract_constructive_element(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        xml_fragment_writer
            .write_start_event(
                CityGmlNamespace::Building,
                CityGmlElement::BuildingConstructiveElement,
            )
            .expect("should work");
        serialize_abstract_constructive_element(
            &abstract_constructive_element,
            &mut xml_fragment_writer,
        )
        .expect("should work");
        xml_fragment_writer
            .write_end_event(
                CityGmlNamespace::Building,
                CityGmlElement::BuildingConstructiveElement,
            )
            .expect("should work");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("con:isStructuralElement"));
        assert!(xml.contains("true"));

        let round_tripped_index =
            XmlDocumentIndex::from_scan(xml.as_bytes(), None).expect("should work");
        let round_tripped = deserialize_abstract_constructive_element(
            xml.as_bytes(),
            &round_tripped_index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            abstract_constructive_element.is_structural_element(),
            round_tripped.is_structural_element()
        );
    }
}
