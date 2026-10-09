use crate::Error;
use crate::gml::codec::core::{
    deserialize_abstract_occupied_space, serialize_abstract_occupied_space,
    serialize_abstract_occupied_space_attributes,
};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::city_furniture::CityFurniture;
use ecitygml_core::model::core::AsAbstractOccupiedSpace;
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::basic_types::Code;

pub fn deserialize_city_furniture(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<CityFurniture, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let abstract_occupied_space = deserialize_abstract_occupied_space(xml_document, index, config)?;
    let mut city_furniture = CityFurniture::from_abstract_occupied_space(abstract_occupied_space);

    let class: Option<Code> = index
        .first(CityGmlElement::ClassProperty.into())
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .transpose()?;
    city_furniture.set_class_opt(class.map(Into::into));

    let functions: Vec<Code> = index
        .get(CityGmlElement::FunctionProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    city_furniture.set_functions(functions.into_iter().map(Into::into).collect());

    let usages: Vec<Code> = index
        .get(CityGmlElement::UsageProperty.into())
        .iter()
        .map(|x| deserialize_code(xml_document[x.range()].as_ref()))
        .collect::<Result<_, _>>()?;
    city_furniture.set_usages(usages.into_iter().map(Into::into).collect());

    Ok(city_furniture)
}

pub fn serialize_city_furniture(
    city_furniture: &CityFurniture,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_city_furniture_attributes(city_furniture);

    xml_fragment_writer.write_start_event_with_attributes(
        CityGmlNamespace::CityFurniture,
        CityGmlElement::CityFurniture,
        attributes,
    )?;

    serialize_abstract_occupied_space(
        city_furniture.abstract_occupied_space(),
        xml_fragment_writer,
    )?;

    if let Some(class) = city_furniture.class() {
        serialize_code(
            class.code(),
            xml_fragment_writer,
            CityGmlNamespace::CityFurniture,
            CityGmlElement::ClassProperty,
        )?;
    }

    for function in city_furniture.functions() {
        serialize_code(
            function.code(),
            xml_fragment_writer,
            CityGmlNamespace::CityFurniture,
            CityGmlElement::FunctionProperty,
        )?;
    }

    for usage in city_furniture.usages() {
        serialize_code(
            usage.code(),
            xml_fragment_writer,
            CityGmlNamespace::CityFurniture,
            CityGmlElement::UsageProperty,
        )?;
    }

    xml_fragment_writer.write_end_event(
        CityGmlNamespace::CityFurniture,
        CityGmlElement::CityFurniture,
    )?;

    Ok(())
}

pub fn serialize_city_furniture_attributes(
    city_furniture: &CityFurniture,
) -> Vec<(String, String)> {
    serialize_abstract_occupied_space_attributes(city_furniture.abstract_occupied_space())
}

#[cfg(test)]
mod tests {
    use super::*;
    use ecitygml_core::model::core::{
        AsAbstractCityObject, AsAbstractFeature, AsAbstractOccupiedSpace, AsAbstractSpace,
    };
    use egml::model::base::{AsAbstractGml, Id};
    use egml::model::basic_types::Code;

    #[test]
    fn test_deserialize_basic_city_furniture() {
        let xml_document = b"<frn:CityFurniture gml:id=\"UUID_379c7ee8-b010-33d2-8e55-786e6be6fa46\">
      <gml:name>Vorschriftzeichen</gml:name>
      <genericAttribute>
        <gen:StringAttribute>
          <gen:name>identifier_roadObjectName</gen:name>
          <gen:value>Vorschriftzeichen</gen:value>
        </gen:StringAttribute>
      </genericAttribute>
      <lod2MultiSurface>
        <gml:MultiSurface>
          <gml:surfaceMember>
            <gml:Polygon>
              <gml:exterior>
                <gml:LinearRing>
                  <gml:posList srsDimension=\"3\">678101.3310583181 5403639.968419715 370.3474251363769 678101.3310583181 5403639.968419715 369.92742513637694 678101.7298154243 5403640.100301367 369.92742513637694 678101.7298154243 5403640.100301367 370.3474251363769 678101.3310583181 5403639.968419715 370.3474251363769</gml:posList>
                </gml:LinearRing>
              </gml:exterior>
            </gml:Polygon>
          </gml:surfaceMember>
        </gml:MultiSurface>
      </lod2MultiSurface>
      <lod1ImplicitRepresentation>
        <ImplicitGeometry>
          <transformationMatrix>-0.3140039352235152 -0.9494216811639318 0.0 0.0 0.9494216811639318 -0.3140039352235152 0.0 0.0 0.0 0.0 1.0 0.0 0.0 0.0 0.0 1.0</transformationMatrix>
          <referencePoint>
            <gml:Point>
              <gml:pos srsDimension=\"3\">678101.5304368712 5403640.034360541 369.92742513637694</gml:pos>
            </gml:Point>
          </referencePoint>
        </ImplicitGeometry>
      </lod1ImplicitRepresentation>
    </frn:CityFurniture>";

        let city_furniture = deserialize_city_furniture(
            xml_document,
            &XmlDocumentIndex::from_scan(xml_document, None).expect("should work"),
            &DeserializationConfig::default(),
        )
        .expect("should work");

        assert_eq!(
            city_furniture.feature_id(),
            &Id::try_from("UUID_379c7ee8-b010-33d2-8e55-786e6be6fa46").expect("should work")
        );
        assert_eq!(
            city_furniture.names().first().expect("should work"),
            &Code::new("Vorschriftzeichen")
        );
        assert!(city_furniture.lod1_implicit_representation().is_some());
        assert!(city_furniture.lod2_multi_surface().is_some());
        assert_eq!(city_furniture.generic_attributes().len(), 1);
    }
}
