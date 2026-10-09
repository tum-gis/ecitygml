use crate::Error;
use crate::gml::codec::water_body::abstract_water_boundary_surface::{
    deserialize_abstract_water_boundary_surface, serialize_abstract_water_boundary_surface,
    serialize_abstract_water_boundary_surface_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::water_body::{AsAbstractWaterBoundarySurface, WaterSurface};
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::basic_types::Code;

pub fn deserialize_water_surface(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<WaterSurface, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_water_boundary_surface =
        deserialize_abstract_water_boundary_surface(xml_document, index, config)?;
    let mut water_surface =
        WaterSurface::from_abstract_water_boundary_surface(abstract_water_boundary_surface);

    let water_level: Option<Code> = index
        .first(CityGmlElement::WaterLevelProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    water_surface.set_water_level_opt(water_level.map(Into::into));

    Ok(water_surface)
}

pub fn serialize_water_surface(
    water_surface: &WaterSurface,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_water_surface_attributes(water_surface);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::WaterBody,
        CityGmlElement::WaterSurface,
        attributes,
    )?;

    serialize_abstract_water_boundary_surface(
        water_surface.abstract_water_boundary_surface(),
        xml_fragment_writer,
    )?;

    if let Some(water_level) = water_surface.water_level() {
        serialize_code(
            water_level.code(),
            xml_fragment_writer,
            CityGmlNamespace::WaterBody,
            CityGmlElement::WaterLevelProperty,
        )?;
    }

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::WaterBody, CityGmlElement::WaterSurface)?;

    Ok(())
}

pub fn serialize_water_surface_attributes(water_surface: &WaterSurface) -> Vec<(String, String)> {
    serialize_abstract_water_boundary_surface_attributes(
        water_surface.abstract_water_boundary_surface(),
    )
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::{Formatting, XmlFragmentWriter};

    #[test]
    fn test_deserialize_water_surface_with_water_level() {
        let xml_document =
            b"<wtr:WaterSurface gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <wtr:waterLevel>meanHighWater</wtr:waterLevel>
</wtr:WaterSurface>";

        let water_surface = deserialize_water_surface(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            water_surface
                .water_level()
                .expect("should be set")
                .code()
                .value(),
            "meanHighWater"
        );
    }

    #[test]
    fn test_round_trip_water_surface_with_water_level() {
        let xml_document =
            b"<wtr:WaterSurface gml:id=\"UUID_ae81947d-a661-3678-a5ee-eed58b68694f\">
    <wtr:waterLevel>meanHighWater</wtr:waterLevel>
</wtr:WaterSurface>";

        let water_surface = deserialize_water_surface(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_water_surface(&water_surface, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("wtr:waterLevel"));
        assert!(xml.contains("meanHighWater"));

        let round_tripped = deserialize_water_surface(
            xml.as_bytes(),
            &XmlDocumentIndex::from_scan(xml.as_bytes(), None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            water_surface
                .water_level()
                .map(|x| x.code().value().to_string()),
            round_tripped
                .water_level()
                .map(|x| x.code().value().to_string())
        );
    }
}
