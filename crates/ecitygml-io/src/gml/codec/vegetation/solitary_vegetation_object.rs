use crate::Error;
use crate::gml::codec::vegetation::abstract_vegetation_object::{
    deserialize_abstract_vegetation_object, serialize_abstract_vegetation_object,
    serialize_abstract_vegetation_object_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::vegetation::{AsAbstractVegetationObject, SolitaryVegetationObject};
use egml::io::codec::basic::{
    deserialize_code, deserialize_measure, serialize_code, serialize_measure,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::basic_types::{Code, Measure};

pub fn deserialize_solitary_vegetation_object(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<SolitaryVegetationObject, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_vegetation_object =
        deserialize_abstract_vegetation_object(xml_document, index, config)?;
    let mut solitary_vegetation_object =
        SolitaryVegetationObject::from_abstract_vegetation_object(abstract_vegetation_object);

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    solitary_vegetation_object.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    solitary_vegetation_object.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    solitary_vegetation_object.set_usages(usages.into_iter().map(Into::into).collect());

    let species: Option<Code> = index
        .first(CityGmlElement::SpeciesProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    solitary_vegetation_object.set_species_opt(species.map(Into::into));

    let height: Option<Measure> = index
        .first(CityGmlElement::HeightProperty.into())
        .map(|x| deserialize_measure(xml_document[x.range()].as_ref()))
        .transpose()?;
    solitary_vegetation_object.set_height_opt(height);

    let trunk_diameter: Option<Measure> = index
        .first(CityGmlElement::TrunkDiameterProperty.into())
        .map(|x| deserialize_measure(xml_document[x.range()].as_ref()))
        .transpose()?;
    solitary_vegetation_object.set_trunk_diameter_opt(trunk_diameter);

    let crown_diameter: Option<Measure> = index
        .first(CityGmlElement::CrownDiameterProperty.into())
        .map(|x| deserialize_measure(xml_document[x.range()].as_ref()))
        .transpose()?;
    solitary_vegetation_object.set_crown_diameter_opt(crown_diameter);

    let root_ball_diameter: Option<Measure> = index
        .first(CityGmlElement::RootBallDiameterProperty.into())
        .map(|x| deserialize_measure(xml_document[x.range()].as_ref()))
        .transpose()?;
    solitary_vegetation_object.set_root_ball_diameter_opt(root_ball_diameter);

    let max_root_ball_depth: Option<Measure> = index
        .first(CityGmlElement::MaxRootBallDepthProperty.into())
        .map(|x| deserialize_measure(xml_document[x.range()].as_ref()))
        .transpose()?;
    solitary_vegetation_object.set_max_root_ball_depth_opt(max_root_ball_depth);

    Ok(solitary_vegetation_object)
}

pub fn serialize_solitary_vegetation_object(
    solitary_vegetation_object: &SolitaryVegetationObject,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_solitary_vegetation_object_attributes(solitary_vegetation_object);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::Vegetation,
        CityGmlElement::SolitaryVegetationObject,
        attributes,
    )?;

    serialize_abstract_vegetation_object(
        solitary_vegetation_object.abstract_vegetation_object(),
        xml_fragment_writer,
    )?;

    if let Some(class) = solitary_vegetation_object.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::Vegetation,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in solitary_vegetation_object.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::Vegetation,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in solitary_vegetation_object.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::Vegetation,
            CityGmlElement::UsageProperty,
        )?;
    }

    if let Some(species) = solitary_vegetation_object.species() {
        serialize_code(
            species.code(),
            xml_fragment_writer,
            CityGmlNamespace::Vegetation,
            CityGmlElement::SpeciesProperty,
        )?;
    }

    if let Some(height) = solitary_vegetation_object.height() {
        serialize_measure(
            height,
            xml_fragment_writer,
            CityGmlNamespace::Vegetation,
            CityGmlElement::HeightProperty,
        )?;
    }

    if let Some(trunk_diameter) = solitary_vegetation_object.trunk_diameter() {
        serialize_measure(
            trunk_diameter,
            xml_fragment_writer,
            CityGmlNamespace::Vegetation,
            CityGmlElement::TrunkDiameterProperty,
        )?;
    }

    if let Some(crown_diameter) = solitary_vegetation_object.crown_diameter() {
        serialize_measure(
            crown_diameter,
            xml_fragment_writer,
            CityGmlNamespace::Vegetation,
            CityGmlElement::CrownDiameterProperty,
        )?;
    }

    if let Some(root_ball_diameter) = solitary_vegetation_object.root_ball_diameter() {
        serialize_measure(
            root_ball_diameter,
            xml_fragment_writer,
            CityGmlNamespace::Vegetation,
            CityGmlElement::RootBallDiameterProperty,
        )?;
    }

    if let Some(max_root_ball_depth) = solitary_vegetation_object.max_root_ball_depth() {
        serialize_measure(
            max_root_ball_depth,
            xml_fragment_writer,
            CityGmlNamespace::Vegetation,
            CityGmlElement::MaxRootBallDepthProperty,
        )?;
    }

    xml_fragment_writer.write_end_event(
        CityGmlNamespace::Vegetation,
        CityGmlElement::SolitaryVegetationObject,
    )?;

    Ok(())
}

pub fn serialize_solitary_vegetation_object_attributes(
    solitary_vegetation_object: &SolitaryVegetationObject,
) -> Vec<(String, String)> {
    serialize_abstract_vegetation_object_attributes(
        solitary_vegetation_object.abstract_vegetation_object(),
    )
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::core::{
        AsAbstractCityObject, AsAbstractFeature, AsAbstractOccupiedSpace,
    };
    use egml::io::util::Formatting;
    use egml::model::base::Id;

    #[test]
    fn test_deserialize_basic_solitary_vegetation_object() {
        let xml_document = b"<veg:SolitaryVegetationObject gml:id=\"UUID_cd516eff-0302-379f-a635-791ebe618098\">
      <genericAttribute>
        <gen:StringAttribute>
          <gen:name>opendrive_roadObject_type</gen:name>
          <gen:value>TREE</gen:value>
        </gen:StringAttribute>
      </genericAttribute>
      <lod1ImplicitRepresentation>
        <ImplicitGeometry>
          <transformationMatrix>-0.9092656859988072 -0.4162161845304895 0.0 0.0 0.4162161845304895 -0.9092656859988072 0.0 0.0 0.0 0.0 1.0 0.0 0.0 0.0 0.0 1.0</transformationMatrix>
          <referencePoint>
            <gml:Point>
              <gml:pos srsDimension=\"3\">678133.7625855505 5403776.088934055 367.0738274934606</gml:pos>
            </gml:Point>
          </referencePoint>
        </ImplicitGeometry>
      </lod1ImplicitRepresentation>
      <veg:height uom=\"#m\">12.1966</veg:height>
      <veg:trunkDiameter uom=\"#m\">0.4</veg:trunkDiameter>
    </veg:SolitaryVegetationObject>";

        let solitary_vegetation_object = deserialize_solitary_vegetation_object(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            solitary_vegetation_object.feature_id(),
            &Id::try_from("UUID_cd516eff-0302-379f-a635-791ebe618098").expect("should work")
        );
        assert!(
            solitary_vegetation_object
                .lod1_implicit_representation()
                .is_some()
        );
        assert_eq!(solitary_vegetation_object.generic_attributes().len(), 1);

        assert_eq!(
            solitary_vegetation_object
                .height()
                .expect("height should be read")
                .value,
            12.1966
        );
        assert_eq!(
            solitary_vegetation_object
                .height()
                .expect("height should be read")
                .uom,
            "#m"
        );
        assert_eq!(
            solitary_vegetation_object
                .trunk_diameter()
                .expect("trunk_diameter should be read")
                .value,
            0.4
        );
        assert_eq!(
            solitary_vegetation_object
                .trunk_diameter()
                .expect("trunk_diameter should be read")
                .uom,
            "#m"
        );
    }

    #[test]
    fn test_round_trip_solitary_vegetation_object_with_measures_and_species() {
        let xml_document =
            b"<veg:SolitaryVegetationObject gml:id=\"UUID_cd516eff-0302-379f-a635-791ebe618098\">
      <veg:species>Quercus robur</veg:species>
      <veg:height uom=\"#m\">12.1966</veg:height>
      <veg:trunkDiameter uom=\"#m\">0.4</veg:trunkDiameter>
      <veg:crownDiameter uom=\"#m\">5.5</veg:crownDiameter>
      <veg:rootBallDiameter uom=\"#m\">1.2</veg:rootBallDiameter>
      <veg:maxRootBallDepth uom=\"#m\">0.8</veg:maxRootBallDepth>
    </veg:SolitaryVegetationObject>";

        let solitary_vegetation_object = deserialize_solitary_vegetation_object(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            solitary_vegetation_object
                .species()
                .expect("species should be read")
                .code()
                .value(),
            "Quercus robur"
        );
        assert_eq!(
            solitary_vegetation_object
                .crown_diameter()
                .expect("crown_diameter should be read")
                .value,
            5.5
        );
        assert_eq!(
            solitary_vegetation_object
                .root_ball_diameter()
                .expect("root_ball_diameter should be read")
                .value,
            1.2
        );
        assert_eq!(
            solitary_vegetation_object
                .max_root_ball_depth()
                .expect("max_root_ball_depth should be read")
                .value,
            0.8
        );

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_solitary_vegetation_object(&solitary_vegetation_object, &mut xml_fragment_writer)
            .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert!(xml.contains("veg:species"));
        assert!(xml.contains("Quercus robur"));
        assert!(xml.contains("veg:crownDiameter"));
        assert!(xml.contains("veg:rootBallDiameter"));
        assert!(xml.contains("veg:maxRootBallDepth"));

        let round_tripped = deserialize_solitary_vegetation_object(
            xml.as_bytes(),
            &XmlDocumentIndex::from_scan(xml.as_bytes(), None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            solitary_vegetation_object.species(),
            round_tripped.species()
        );
        assert_eq!(solitary_vegetation_object.height(), round_tripped.height());
        assert_eq!(
            solitary_vegetation_object.trunk_diameter(),
            round_tripped.trunk_diameter()
        );
        assert_eq!(
            solitary_vegetation_object.crown_diameter(),
            round_tripped.crown_diameter()
        );
        assert_eq!(
            solitary_vegetation_object.root_ball_diameter(),
            round_tripped.root_ball_diameter()
        );
        assert_eq!(
            solitary_vegetation_object.max_root_ball_depth(),
            round_tripped.max_root_ball_depth()
        );
    }
}
