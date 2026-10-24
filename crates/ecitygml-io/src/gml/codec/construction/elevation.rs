use crate::Error;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::construction::values::ElevationReferenceValue;
use ecitygml_core::model::construction::{Elevation, ElevationValue};
use egml::io::codec::basic::{deserialize_code, serialize_code};
use egml::io::codec::xs::any_uri_from_lexical;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use egml::model::basic_types::Code;
use egml::model::xs::AnyUri;
use quick_xml::events::{BytesStart, Event};
use quick_xml::{Reader, XmlVersion};

pub fn deserialize_elevation(xml_document: &[u8]) -> Result<Elevation, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    // Consume the root `<Elevation>` element's own start tag.
    loop {
        match reader.read_event()? {
            Event::Start(_) => break,
            Event::Eof => {
                return Err(Error::ElementNotFound("Elevation".to_string()));
            }
            _ => {}
        }
    }

    let mut elevation_reference: Option<Code> = None;
    let mut elevation_value: Option<ElevationValue> = None;

    loop {
        match reader.read_event()? {
            Event::Start(start) => match start.local_name().as_ref() {
                "elevationReference" => {
                    let pos_start = reader.buffer_position() as usize - start.len() - 2;
                    reader.read_to_end(start.name())?;
                    let pos_end = reader.buffer_position() as usize;
                    elevation_reference =
                        Some(deserialize_code(&xml_document[pos_start..pos_end])?);
                }
                "elevationValue" => {
                    let text = reader.read_text(start.name())?;
                    elevation_value = Some(elevation_value_from(&start, text.trim())?);
                }
                _ => {
                    reader.read_to_end(start.name())?;
                }
            },
            Event::Empty(start) if start.local_name().as_ref() == "elevationValue" => {
                elevation_value = Some(elevation_value_from(&start, "")?);
            }
            Event::Eof => break,
            _ => {}
        }
    }

    let elevation_reference = elevation_reference
        .map(ElevationReferenceValue::from)
        .ok_or_else(|| Error::ElementNotFound("elevationReference".to_string()))?;
    let elevation_value =
        elevation_value.ok_or_else(|| Error::ElementNotFound("elevationValue".to_string()))?;

    Ok(Elevation::new(elevation_reference, elevation_value))
}

/// Reads a `gml:DirectPositionType` with any number of coordinates: the `srsDimension` and `srsName` attributes of
/// `start` and the whitespace-separated coordinates in `text`.
///
/// TODO: use egml's direct position codec once egml supports n-dimensional direct positions (its codec currently
/// rejects every `srsDimension` other than 3).
fn elevation_value_from(start: &BytesStart, text: &str) -> Result<ElevationValue, Error> {
    let mut srs_dimension: Option<u32> = None;
    let mut srs_name: Option<AnyUri> = None;
    for attr in start.attributes() {
        let attr = attr.map_err(quick_xml::Error::from)?;
        let value = attr.normalized_value(XmlVersion::Implicit1_0)?;
        match attr.key.local_name().as_ref() {
            "srsDimension" => {
                srs_dimension = Some(value.parse().map_err(|_| {
                    Error::UnknownElementNode(format!(
                        "expected srsDimension integer, got `{value}`"
                    ))
                })?)
            }
            "srsName" => srs_name = Some(any_uri_from_lexical(&value)),
            _ => {}
        }
    }

    let coordinates = text
        .split_whitespace()
        .map(|x| {
            x.parse::<f64>()
                .map_err(|_| Error::UnknownElementNode(format!("expected f64 value, got `{x}`")))
        })
        .collect::<Result<Vec<_>, _>>()?;
    if let Some(dimension) = srs_dimension
        && dimension as usize != coordinates.len()
    {
        return Err(Error::UnknownElementNode(format!(
            "srsDimension is {dimension}, but elevationValue has {} coordinates",
            coordinates.len()
        )));
    }

    let mut elevation_value = ElevationValue::new(coordinates)?;
    elevation_value.set_srs_dimension(srs_dimension);
    elevation_value.set_srs_name(srs_name);
    Ok(elevation_value)
}

pub fn serialize_elevation(
    elevation: &Elevation,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
) -> Result<(), Error> {
    xml_fragment_writer
        .write_start_event(CityGmlNamespace::Construction, CityGmlElement::Elevation)?;

    serialize_code(
        elevation.elevation_reference().code(),
        xml_fragment_writer,
        CityGmlNamespace::Construction,
        CityGmlElement::ElevationReferenceProperty,
    )?;

    let elevation_value = elevation.elevation_value();
    let mut attributes: Vec<(&str, String)> = Vec::new();
    if let Some(srs_name) = elevation_value.srs_name() {
        attributes.push(("srsName", srs_name.to_string()));
    }
    if let Some(srs_dimension) = elevation_value.srs_dimension() {
        attributes.push(("srsDimension", srs_dimension.to_string()));
    }
    let content = elevation_value
        .coordinates()
        .iter()
        .map(|x| x.to_string())
        .collect::<Vec<_>>()
        .join(" ");
    xml_fragment_writer.write_leaf_element_with_attributes(
        CityGmlNamespace::Construction,
        CityGmlElement::ElevationValueProperty,
        attributes,
        &content,
    )?;

    xml_fragment_writer
        .write_end_event(CityGmlNamespace::Construction, CityGmlElement::Elevation)?;

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    const ELEVATION: &[u8] = br#"<con:Elevation>
<con:elevationReference>generalGroundSurface</con:elevationReference>
<con:elevationValue srsName="urn:ogc:def:crs:EPSG::7837" srsDimension="1">105.3</con:elevationValue>
</con:Elevation>"#;

    #[test]
    fn test_deserialize_one_dimensional_elevation() {
        let elevation = deserialize_elevation(ELEVATION).expect("should work");

        assert_eq!(
            elevation.elevation_reference().code().value(),
            "generalGroundSurface"
        );
        let value = elevation.elevation_value();
        assert_eq!(value.coordinates(), &[105.3]);
        assert_eq!(value.srs_dimension(), Some(1));
        assert_eq!(
            value.srs_name().map(AnyUri::as_str),
            Some("urn:ogc:def:crs:EPSG::7837")
        );
    }

    #[test]
    fn test_deserialize_elevation_without_attributes() {
        let elevation = deserialize_elevation(
            br#"<con:Elevation>
<con:elevationReference>entrancePoint</con:elevationReference>
<con:elevationValue>98.5</con:elevationValue>
</con:Elevation>"#,
        )
        .expect("should work");

        assert_eq!(elevation.elevation_value().coordinates(), &[98.5]);
        assert!(elevation.elevation_value().srs_dimension().is_none());
        assert!(elevation.elevation_value().srs_name().is_none());
    }

    #[test]
    fn test_deserialize_elevation_with_non_numeric_value_fails() {
        let result = deserialize_elevation(
            br#"<con:Elevation>
<con:elevationReference>entrancePoint</con:elevationReference>
<con:elevationValue>high</con:elevationValue>
</con:Elevation>"#,
        );

        assert!(matches!(result, Err(Error::UnknownElementNode(_))));
    }

    #[test]
    fn test_deserialize_elevation_with_dimension_mismatch_fails() {
        let result = deserialize_elevation(
            br#"<con:Elevation>
<con:elevationReference>entrancePoint</con:elevationReference>
<con:elevationValue srsDimension="1">1.0 2.0</con:elevationValue>
</con:Elevation>"#,
        );

        assert!(matches!(result, Err(Error::UnknownElementNode(_))));
    }

    #[test]
    fn test_deserialize_elevation_with_empty_value_fails() {
        let result = deserialize_elevation(
            br#"<con:Elevation>
<con:elevationReference>entrancePoint</con:elevationReference>
<con:elevationValue/>
</con:Elevation>"#,
        );

        assert!(matches!(
            result,
            Err(Error::EcitygmlError(ecitygml_core::Error::EmptyCoordinates))
        ));
    }

    #[test]
    fn test_round_trip_elevation() {
        let elevation = deserialize_elevation(ELEVATION).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_elevation(&elevation, &mut xml_fragment_writer).expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");
        assert!(xml.contains("srsDimension=\"1\""));
        assert!(xml.contains(">105.3</con:elevationValue>"));

        assert_eq!(
            deserialize_elevation(xml.as_bytes()).expect("should round trip"),
            elevation
        );
    }

    #[test]
    fn test_deserialize_elevation_srs_name_collapses_whitespace() {
        let elevation = deserialize_elevation(
            br#"<con:Elevation>
<con:elevationReference>entrancePoint</con:elevationReference>
<con:elevationValue srsName="  urn:ogc:def:crs:EPSG::7837 " srsDimension="1">98.5</con:elevationValue>
</con:Elevation>"#,
        )
        .expect("should work");

        assert_eq!(
            elevation.elevation_value().srs_name(),
            Some(&AnyUri::new("urn:ogc:def:crs:EPSG::7837"))
        );
    }
}
