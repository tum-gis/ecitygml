use crate::Error;
use crate::gml::codec::appearance::abstract_surface_data_property::{
    deserialize_abstract_surface_data_property, serialize_abstract_surface_data_property,
};
use crate::gml::codec::common::{deserialize_string, serialize_string};
use crate::gml::codec::core::{
    deserialize_abstract_appearance, serialize_abstract_appearance,
    serialize_abstract_appearance_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::appearance::Appearance;
use ecitygml_core::model::core::AsAbstractAppearance;
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter, collect_children};

pub fn deserialize_appearance(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<Appearance, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let mut abstract_appearance_result = None;
    let mut surface_data_result = None;

    rayon::scope(|s| {
        s.spawn(|_| {
            abstract_appearance_result =
                Some(deserialize_abstract_appearance(xml_document, index, config));
        });
        s.spawn(|_| {
            surface_data_result = Some(collect_children(
                xml_document,
                index,
                CityGmlElement::AbstractSurfaceDataProperty.into(),
                config,
                deserialize_abstract_surface_data_property,
            ));
        });
    });

    let mut appearance = Appearance::from_abstract_appearance(
        abstract_appearance_result.expect("rayon::scope guarantees all spawns complete")?,
    );

    let theme: Option<String> = index
        .first(CityGmlElement::ThemeProperty.into())
        .map(|x| deserialize_string(&xml_document[x.range()]))
        .transpose()?;
    appearance.set_theme_opt(theme);

    appearance.set_surface_data(
        surface_data_result.expect("rayon::scope guarantees all spawns complete")?,
    );

    Ok(appearance)
}

pub fn serialize_appearance(
    appearance: &Appearance,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_appearance_attributes(appearance);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Appearance,
        CityGmlElement::Appearance,
        attributes,
    )?;

    serialize_abstract_appearance(appearance.abstract_appearance(), xml_fragment_writer)?;

    if let Some(theme) = appearance.theme() {
        serialize_string(
            theme,
            xml_fragment_writer,
            CityGmlNamespace::Appearance,
            CityGmlElement::ThemeProperty,
        )?;
    }

    for prop in appearance.surface_data() {
        serialize_abstract_surface_data_property(prop, xml_fragment_writer)?;
    }

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::Appearance, CityGmlElement::Appearance)?;

    Ok(())
}

pub fn serialize_appearance_attributes(appearance: &Appearance) -> Vec<(String, String)> {
    serialize_abstract_appearance_attributes(appearance.abstract_appearance())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_appearance_with_theme() {
        let xml_document = b"\
<app:Appearance gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <app:theme>visual</app:theme>
</app:Appearance>";

        let appearance = deserialize_appearance(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(appearance.theme(), Some("visual"));
    }

    #[test]
    fn test_round_trip_appearance_with_theme() {
        let xml_document = b"\
<app:Appearance gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <app:theme>visual</app:theme>
</app:Appearance>";

        let appearance = deserialize_appearance(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_appearance(&appearance, &mut xml_fragment_writer).expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("app:theme"));
        assert!(xml.contains("visual"));

        let round_tripped = deserialize_appearance(
            xml.as_bytes(),
            &XmlDocumentIndex::from_scan(xml.as_bytes(), None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(appearance.theme(), round_tripped.theme());
    }
}
