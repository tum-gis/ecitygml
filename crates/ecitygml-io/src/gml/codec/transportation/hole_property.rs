use crate::Error;
use crate::gml::codec::transportation::{deserialize_hole, serialize_hole};
use crate::gml::util::{
    CityGmlElement, CityGmlNamespace, CombinedCityGmlElement, DeserializationConfig,
};
use ecitygml_core::model::transportation::HoleProperty;
use egml::io::codec::base::{
    deserialize_association_and_ownership_attributes,
    serialize_association_and_ownership_attributes,
};
use egml::io::util::{ChunkedSink, XmlDocumentIndex, XmlFragmentWriter};
use egml::model::base::{HasAssociationAttributes, HasOwnershipAttributes};

pub fn deserialize_hole_property(
    xml_document: &[u8],
    index: &XmlDocumentIndex<CombinedCityGmlElement>,
    config: &DeserializationConfig,
) -> Result<HoleProperty, Error> {
    let index = if index.is_truncated() {
        &XmlDocumentIndex::from_scan(xml_document, config.feature_rescan_depth())?
    } else {
        index
    };

    let (association, ownership) = deserialize_association_and_ownership_attributes(xml_document)?;
    let mut object = None;

    if let Some(index) = index.first(CityGmlElement::Hole.into()) {
        object = Some(deserialize_hole(
            &xml_document[index.range()],
            index,
            config,
        )?);
    }

    Ok(HoleProperty::new(object, association, ownership))
}

pub fn serialize_hole_property(
    hole_property: &HoleProperty,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    let attributes = serialize_association_and_ownership_attributes(
        hole_property.association(),
        hole_property.ownership(),
    );

    match hole_property.object() {
        Some(object) => {
            xml_fragment_writer.write_start_event_with_attributes(
                CityGmlNamespace::Transportation,
                CityGmlElement::HoleProperty,
                attributes,
            )?;
            serialize_hole(object, xml_fragment_writer)?;
            xml_fragment_writer.write_end_event(
                CityGmlNamespace::Transportation,
                CityGmlElement::HoleProperty,
            )?;
        }
        None => {
            xml_fragment_writer.write_empty_element_with_attributes(
                CityGmlNamespace::Transportation,
                CityGmlElement::HoleProperty,
                attributes,
            )?;
        }
    }

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::model::base::HasAssociationAttributes;
    use egml::model::xlink::HRef;

    #[test]
    fn test_deserialize_basic_href_marking_property() {
        let xml_document =
            b"<tran:hole xlink:href=\"#DEBY_LOD2_59772_4becb506-d53b-44ca-a483-e6a3d238b4c2\" />";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let hole_property =
            deserialize_hole_property(xml_document, &index, &DeserializationConfig::default())
                .expect("should work");

        assert_eq!(
            hole_property.href().expect("should exist"),
            &HRef::from("#DEBY_LOD2_59772_4becb506-d53b-44ca-a483-e6a3d238b4c2")
        );
    }

    #[test]
    fn test_deserialize_basic_hole_property() {
        let xml_document =
            b"<tran:hole>
            <tran:Hole gml:id=\"UUID_caee8e69-7e58-373d-8851-18733ef1bd09\">
              <gml:name>PotHole 1</gml:name>
              <lod0MultiCurve>
                <gml:MultiCurve>
                  <gml:curveMember>
                    <gml:LineString>
                      <gml:posList srsDimension=\"3\">678271.4067081005 5403811.079187075 366.9572377818742 678270.9302519264 5403811.592939825 366.95518582220353 678270.4543853031 5403812.10738513 366.9529930943392 678269.9803245188 5403812.623632342 366.9506572115437 678269.5092944839 5403813.142781629 366.9481757870797 678269.0425308547 5403813.665921351 366.94554643420963 678268.58116672 5403814.194021827 366.9427673574052 678268.1248923152 5403814.726687356 366.93984147941757 678267.6723232657 5403815.262555441 366.93677398203545 678267.2219856592 5403815.800280218 366.9335700612365 678266.7724620319 5403816.338595356 366.93023491299846 678266.3232302127 5403816.877044827 366.92677373329906 678265.8743892186 5403817.41572265 366.9231917181159 678265.4260511993 5403817.954732671 366.9194940634268 678264.9783292373 5403818.494177758 366.91568596520926 678264.5313373648 5403819.034159759 366.9117726194411 678264.1746481406 5403819.466234176 366.9085723886458</gml:posList>
                    </gml:LineString>
                  </gml:curveMember>
                </gml:MultiCurve>
              </lod0MultiCurve>
            </tran:Hole>
          </tran:hole>";

        let index = XmlDocumentIndex::from_scan(xml_document, None).expect("should work");
        let hole_property =
            deserialize_hole_property(xml_document, &index, &DeserializationConfig::default())
                .expect("should work");

        assert!(hole_property.object().is_some());
    }
}
