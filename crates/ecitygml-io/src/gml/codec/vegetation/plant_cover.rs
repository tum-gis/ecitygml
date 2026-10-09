use crate::Error;
use crate::gml::codec::vegetation::abstract_vegetation_object::{
    deserialize_abstract_vegetation_object, serialize_abstract_vegetation_object,
    serialize_abstract_vegetation_object_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::vegetation::{AsAbstractVegetationObject, PlantCover};
use egml::io::codec::basic::{
    deserialize_code, deserialize_measure, serialize_code, serialize_measure,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::basic_types::{Code, Measure};

pub fn deserialize_plant_cover(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<PlantCover, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_vegetation_object =
        deserialize_abstract_vegetation_object(xml_document, index, config)?;
    let mut plant_cover = PlantCover::from_abstract_vegetation_object(abstract_vegetation_object);

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    plant_cover.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    plant_cover.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    plant_cover.set_usages(usages.into_iter().map(Into::into).collect());

    let average_height: Option<Measure> = index
        .first(CityGmlElement::AverageHeightProperty.into())
        .map(|x| deserialize_measure(xml_document[x.range()].as_ref()))
        .transpose()?;
    plant_cover.set_average_height_opt(average_height);

    let min_height: Option<Measure> = index
        .first(CityGmlElement::MinHeightProperty.into())
        .map(|x| deserialize_measure(xml_document[x.range()].as_ref()))
        .transpose()?;
    plant_cover.set_min_height_opt(min_height);

    let max_height: Option<Measure> = index
        .first(CityGmlElement::MaxHeightProperty.into())
        .map(|x| deserialize_measure(xml_document[x.range()].as_ref()))
        .transpose()?;
    plant_cover.set_max_height_opt(max_height);

    Ok(plant_cover)
}

pub fn serialize_plant_cover(
    plant_cover: &PlantCover,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_plant_cover_attributes(plant_cover);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Vegetation,
        CityGmlElement::PlantCover,
        attributes,
    )?;

    serialize_abstract_vegetation_object(
        plant_cover.abstract_vegetation_object(),
        xml_fragment_writer,
    )?;

    if let Some(class) = plant_cover.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Vegetation,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in plant_cover.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::Vegetation,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in plant_cover.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::Vegetation,
            CityGmlElement::UsageProperty,
        )?;
    }

    if let Some(average_height) = plant_cover.average_height() {
        serialize_measure(
            average_height,
            xml_fragment_writer,
            CityGmlNamespace::Vegetation,
            CityGmlElement::AverageHeightProperty,
        )?;
    }

    if let Some(min_height) = plant_cover.min_height() {
        serialize_measure(
            min_height,
            xml_fragment_writer,
            CityGmlNamespace::Vegetation,
            CityGmlElement::MinHeightProperty,
        )?;
    }

    if let Some(max_height) = plant_cover.max_height() {
        serialize_measure(
            max_height,
            xml_fragment_writer,
            CityGmlNamespace::Vegetation,
            CityGmlElement::MaxHeightProperty,
        )?;
    }

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::Vegetation, CityGmlElement::PlantCover)?;

    Ok(())
}

pub fn serialize_plant_cover_attributes(plant_cover: &PlantCover) -> Vec<(String, String)> {
    serialize_abstract_vegetation_object_attributes(plant_cover.abstract_vegetation_object())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_plant_cover_with_heights() {
        let xml_document = b"<veg:PlantCover gml:id=\"UUID_cd516eff-0302-379f-a635-791ebe618098\">
    <veg:averageHeight uom=\"#m\">2.5</veg:averageHeight>
    <veg:minHeight uom=\"#m\">1.0</veg:minHeight>
    <veg:maxHeight uom=\"#m\">4.0</veg:maxHeight>
</veg:PlantCover>";

        let plant_cover = deserialize_plant_cover(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            plant_cover
                .average_height()
                .expect("average_height should be read")
                .value,
            2.5
        );
        assert_eq!(
            plant_cover
                .min_height()
                .expect("min_height should be read")
                .value,
            1.0
        );
        assert_eq!(
            plant_cover
                .max_height()
                .expect("max_height should be read")
                .value,
            4.0
        );
    }

    #[test]
    fn test_round_trip_plant_cover_with_heights() {
        let xml_document = b"<veg:PlantCover gml:id=\"UUID_cd516eff-0302-379f-a635-791ebe618098\">
    <veg:averageHeight uom=\"#m\">2.5</veg:averageHeight>
    <veg:minHeight uom=\"#m\">1.0</veg:minHeight>
    <veg:maxHeight uom=\"#m\">4.0</veg:maxHeight>
</veg:PlantCover>";

        let plant_cover = deserialize_plant_cover(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_plant_cover(&plant_cover, &mut xml_fragment_writer).expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("veg:averageHeight"));
        assert!(xml.contains("veg:minHeight"));
        assert!(xml.contains("veg:maxHeight"));

        let round_tripped = deserialize_plant_cover(
            xml.as_bytes(),
            &XmlDocumentIndex::from_scan(xml.as_bytes(), None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(plant_cover.average_height(), round_tripped.average_height());
        assert_eq!(plant_cover.min_height(), round_tripped.min_height());
        assert_eq!(plant_cover.max_height(), round_tripped.max_height());
    }
}
