use crate::Error;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

use crate::gml::codec::common::{deserialize_bool, serialize_bool};
use crate::gml::codec::core::{
    deserialize_abstract_feature, serialize_abstract_feature, serialize_abstract_feature_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::appearance::{
    AbstractSurfaceData, AsAbstractSurfaceData, AsAbstractSurfaceDataMut,
};
use ecitygml_core::model::core::AsAbstractFeature;

pub fn deserialize_abstract_surface_data(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractSurfaceData, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_surface_data received a truncated index — caller must scan to sufficient depth"
    );

    let abstract_feature = deserialize_abstract_feature(xml_document, index, config)?;
    let mut abstract_surface_data = AbstractSurfaceData::from_abstract_feature(abstract_feature);

    let is_front: Option<bool> = index
        .first(CityGmlElement::IsFrontProperty.into())
        .map(|x| deserialize_bool(&xml_document[x.range()]))
        .transpose()?;
    abstract_surface_data.set_is_front(is_front);

    Ok(abstract_surface_data)
}

pub fn serialize_abstract_surface_data(
    abstract_surface_data: &AbstractSurfaceData,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_feature(
        abstract_surface_data.abstract_feature(),
        xml_fragment_writer,
    )?;

    if let Some(is_front) = abstract_surface_data.is_front() {
        serialize_bool(
            *is_front,
            xml_fragment_writer,
            CityGmlNamespace::Appearance,
            CityGmlElement::IsFrontProperty,
        )?;
    }

    Ok(())
}

pub fn serialize_abstract_surface_data_attributes(
    abstract_surface_data: &AbstractSurfaceData,
) -> Vec<(String, String)> {
    serialize_abstract_feature_attributes(abstract_surface_data.abstract_feature())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_abstract_surface_data_with_is_front() {
        let xml_document = b"\
<app:X3DMaterial gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <app:isFront>true</app:isFront>
</app:X3DMaterial>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_surface_data = deserialize_abstract_surface_data(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(abstract_surface_data.is_front(), Some(&true));
    }

    #[test]
    fn test_round_trip_abstract_surface_data_with_is_front() {
        let xml_document = b"\
<app:X3DMaterial gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <app:isFront>true</app:isFront>
</app:X3DMaterial>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_surface_data = deserialize_abstract_surface_data(
            xml_document,
            &index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        xml_fragment_writer
            .write_start_event(CityGmlNamespace::Appearance, CityGmlElement::X3DMaterial)
            .expect("should work");
        serialize_abstract_surface_data(&abstract_surface_data, &mut xml_fragment_writer)
            .expect("should work");
        xml_fragment_writer
            .write_end_event(CityGmlNamespace::Appearance, CityGmlElement::X3DMaterial)
            .expect("should work");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("app:isFront"));
        assert!(xml.contains("true"));

        let round_tripped_index =
            XmlDocumentIndex::from_scan(xml.as_bytes(), None).expect("should work");
        let round_tripped = deserialize_abstract_surface_data(
            xml.as_bytes(),
            &round_tripped_index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(abstract_surface_data.is_front(), round_tripped.is_front());
    }
}
