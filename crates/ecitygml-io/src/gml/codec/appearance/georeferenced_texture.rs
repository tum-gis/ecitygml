use crate::Error;
use crate::gml::codec::appearance::abstract_texture::{
    deserialize_abstract_texture, serialize_abstract_texture, serialize_abstract_texture_attributes,
};
use crate::gml::codec::common::{deserialize_bool, serialize_bool};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::appearance::{AsAbstractTexture, GeoreferencedTexture};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

pub fn deserialize_georeferenced_texture(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<GeoreferencedTexture, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_texture = deserialize_abstract_texture(xml_document, index, config)?;

    let mut georeferenced_texture = GeoreferencedTexture::from_abstract_texture(abstract_texture);

    let prefer_world_file: Option<bool> = index
        .first(CityGmlElement::PreferWorldFileProperty.into())
        .map(|x| deserialize_bool(&xml_document[x.range()]))
        .transpose()?;
    georeferenced_texture.set_prefer_world_file(prefer_world_file);

    Ok(georeferenced_texture)
}

pub fn serialize_georeferenced_texture(
    georeferenced_texture: &GeoreferencedTexture,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_georeferenced_texture_attributes(georeferenced_texture);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Appearance,
        CityGmlElement::GeoreferencedTexture,
        attributes,
    )?;

    serialize_abstract_texture(
        georeferenced_texture.abstract_texture(),
        xml_fragment_writer,
    )?;

    if let Some(prefer_world_file) = georeferenced_texture.prefer_world_file() {
        serialize_bool(
            prefer_world_file,
            xml_fragment_writer,
            CityGmlNamespace::Appearance,
            CityGmlElement::PreferWorldFileProperty,
        )?;
    }

    xml_fragment_writer.write_end_event(
        CityGmlNamespace::Appearance,
        CityGmlElement::GeoreferencedTexture,
    )?;

    Ok(())
}

pub fn serialize_georeferenced_texture_attributes(
    georeferenced_texture: &GeoreferencedTexture,
) -> Vec<(String, String)> {
    serialize_abstract_texture_attributes(georeferenced_texture.abstract_texture())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_georeferenced_texture_with_prefer_world_file() {
        let xml_document = b"\
<app:GeoreferencedTexture gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <app:preferWorldFile>true</app:preferWorldFile>
</app:GeoreferencedTexture>";

        let georeferenced_texture = deserialize_georeferenced_texture(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(georeferenced_texture.prefer_world_file(), Some(true));
    }

    #[test]
    fn test_round_trip_georeferenced_texture_with_prefer_world_file() {
        let xml_document = b"\
<app:GeoreferencedTexture gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <app:preferWorldFile>true</app:preferWorldFile>
</app:GeoreferencedTexture>";

        let georeferenced_texture = deserialize_georeferenced_texture(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_georeferenced_texture(&georeferenced_texture, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("app:preferWorldFile"));
        assert!(xml.contains("true"));

        let round_tripped = deserialize_georeferenced_texture(
            xml.as_bytes(),
            &XmlDocumentIndex::from_scan(xml.as_bytes(), None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            georeferenced_texture.prefer_world_file(),
            round_tripped.prefer_world_file()
        );
    }
}
