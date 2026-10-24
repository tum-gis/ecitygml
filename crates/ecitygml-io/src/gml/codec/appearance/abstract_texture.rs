use crate::Error;
use egml::io::codec::xs::{deserialize_any_uri, serialize_any_uri};
use egml::model::xs::AnyUri;

use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};

use crate::gml::codec::appearance::abstract_surface_data::{
    deserialize_abstract_surface_data, serialize_abstract_surface_data,
    serialize_abstract_surface_data_attributes,
};
use crate::gml::codec::appearance::basic_types::{
    deserialize_color_plus_opacity, serialize_color_plus_opacity,
};
use crate::gml::codec::appearance::enums::{
    deserialize_texture_type, deserialize_wrap_mode, serialize_texture_type, serialize_wrap_mode,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::appearance::{
    AbstractTexture, AsAbstractSurfaceData, AsAbstractTexture, AsAbstractTextureMut,
};

pub fn deserialize_abstract_texture(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<AbstractTexture, Error> {
    debug_assert!(
        !index.is_truncated(),
        "deserialize_abstract_texture received a truncated index — caller must scan to sufficient depth"
    );

    let abstract_surface_data = deserialize_abstract_surface_data(xml_document, index, config)?;

    let mut abstract_texture = AbstractTexture::from_abstract_surface_data(abstract_surface_data);

    let image_uri: Option<AnyUri> = index
        .first(CityGmlElement::ImageUriProperty.into())
        .map(|x| deserialize_any_uri(&xml_document[x.range()]))
        .transpose()?;
    abstract_texture.set_image_uri(image_uri);

    let texture_type = index
        .first(CityGmlElement::TextureTypeProperty.into())
        .map(|x| deserialize_texture_type(&xml_document[x.range()]))
        .transpose()?;
    abstract_texture.set_texture_type(texture_type);

    let wrap_mode = index
        .first(CityGmlElement::WrapModeProperty.into())
        .map(|x| deserialize_wrap_mode(&xml_document[x.range()]))
        .transpose()?;
    abstract_texture.set_wrap_mode(wrap_mode);

    let border_color = index
        .first(CityGmlElement::BorderColorProperty.into())
        .map(|x| deserialize_color_plus_opacity(&xml_document[x.range()]))
        .transpose()?;
    abstract_texture.set_border_color(border_color);

    Ok(abstract_texture)
}

pub fn serialize_abstract_texture(
    abstract_texture: &AbstractTexture,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    serialize_abstract_surface_data(
        abstract_texture.abstract_surface_data(),
        xml_fragment_writer,
    )?;

    if let Some(image_uri) = abstract_texture.image_uri() {
        serialize_any_uri(
            image_uri,
            xml_fragment_writer,
            CityGmlNamespace::Appearance,
            CityGmlElement::ImageUriProperty,
        )?;
    }

    if let Some(texture_type) = abstract_texture.texture_type() {
        serialize_texture_type(
            texture_type,
            xml_fragment_writer,
            CityGmlNamespace::Appearance,
            CityGmlElement::TextureTypeProperty,
        )?;
    }

    if let Some(wrap_mode) = abstract_texture.wrap_mode() {
        serialize_wrap_mode(
            wrap_mode,
            xml_fragment_writer,
            CityGmlNamespace::Appearance,
            CityGmlElement::WrapModeProperty,
        )?;
    }

    if let Some(border_color) = abstract_texture.border_color() {
        serialize_color_plus_opacity(
            border_color,
            xml_fragment_writer,
            CityGmlNamespace::Appearance,
            CityGmlElement::BorderColorProperty,
        )?;
    }

    Ok(())
}

pub fn serialize_abstract_texture_attributes(
    abstract_texture: &AbstractTexture,
) -> Vec<(String, String)> {
    serialize_abstract_surface_data_attributes(abstract_texture.abstract_surface_data())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::appearance::enums::{TextureType, WrapMode};
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_abstract_texture() {
        let xml_document = b"\
<app:ParameterizedTexture gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <app:imageURI>textures/wall.png</app:imageURI>
    <app:textureType>specific</app:textureType>
    <app:wrapMode>wrap</app:wrapMode>
    <app:borderColor>0.1 0.2 0.3 0.4</app:borderColor>
</app:ParameterizedTexture>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_texture =
            deserialize_abstract_texture(xml_document, &index, &DeserializationConfig::default())
                .expect("should work");

        assert_eq!(
            abstract_texture.image_uri().map(AnyUri::as_str),
            Some("textures/wall.png")
        );
        assert_eq!(abstract_texture.texture_type(), Some(TextureType::Specific));
        assert_eq!(abstract_texture.wrap_mode(), Some(WrapMode::Wrap));
        assert_eq!(
            abstract_texture
                .border_color()
                .unwrap()
                .color()
                .red()
                .value(),
            0.1
        );
        assert_eq!(
            abstract_texture.border_color().unwrap().opacity().value(),
            0.4
        );
    }

    #[test]
    fn test_round_trip_abstract_texture() {
        let xml_document = b"\
<app:ParameterizedTexture gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <app:imageURI>textures/wall.png</app:imageURI>
    <app:textureType>specific</app:textureType>
    <app:wrapMode>wrap</app:wrapMode>
    <app:borderColor>0.1 0.2 0.3 0.4</app:borderColor>
</app:ParameterizedTexture>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_texture =
            deserialize_abstract_texture(xml_document, &index, &DeserializationConfig::default())
                .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        xml_fragment_writer
            .write_start_event(
                CityGmlNamespace::Appearance,
                CityGmlElement::ParameterizedTexture,
            )
            .expect("should work");
        serialize_abstract_texture(&abstract_texture, &mut xml_fragment_writer)
            .expect("should work");
        xml_fragment_writer
            .write_end_event(
                CityGmlNamespace::Appearance,
                CityGmlElement::ParameterizedTexture,
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

        assert!(xml.contains("app:imageURI"));
        assert!(xml.contains("textures/wall.png"));
        assert!(xml.contains("app:textureType"));
        assert!(xml.contains("app:wrapMode"));
        assert!(xml.contains("app:borderColor"));

        let round_tripped_index =
            XmlDocumentIndex::from_scan(xml.as_bytes(), None).expect("should work");
        let round_tripped = deserialize_abstract_texture(
            xml.as_bytes(),
            &round_tripped_index,
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(abstract_texture.image_uri(), round_tripped.image_uri());
        assert_eq!(
            abstract_texture.texture_type(),
            round_tripped.texture_type()
        );
        assert_eq!(abstract_texture.wrap_mode(), round_tripped.wrap_mode());
        assert_eq!(
            abstract_texture.border_color(),
            round_tripped.border_color()
        );
    }

    #[test]
    fn test_deserialize_abstract_texture_image_uri_as_any_uri() {
        let xml_document = b"\
<app:ParameterizedTexture gml:id=\"TEX_1\">
    <app:imageURI>
        https://example.org/textures?id=1&amp;size=2k
    </app:imageURI>
</app:ParameterizedTexture>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let abstract_texture =
            deserialize_abstract_texture(xml_document, &index, &DeserializationConfig::default())
                .expect("should work");

        assert_eq!(
            abstract_texture.image_uri().map(AnyUri::as_str),
            Some("https://example.org/textures?id=1&size=2k")
        );
    }
}
