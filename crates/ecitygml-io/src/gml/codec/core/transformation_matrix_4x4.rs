use crate::Error;
use crate::gml::util::{CityGmlElement, CityGmlNamespace};
use ecitygml_core::model::core::TransformationMatrix4x4;
use egml::io::util::{ChunkedSink, XmlFragmentWriter};
use quick_xml::Reader;
use quick_xml::events::Event;

pub fn deserialize_transformation_matrix_4x4(
    xml_document: &[u8],
) -> Result<TransformationMatrix4x4, Error> {
    let mut reader = Reader::from_reader(xml_document);
    reader.config_mut().trim_text(true);

    loop {
        match reader.read_event()? {
            Event::Text(text) => {
                let value = text.as_ref();
                return transformation_matrix_4x4_from_str(value);
            }
            Event::CData(cdata) => {
                let value = cdata.as_ref();
                return transformation_matrix_4x4_from_str(value);
            }
            Event::Eof => {
                return Err(Error::ElementNotFound(
                    "transformationMatrix text content".to_string(),
                ));
            }
            _ => {}
        }
    }
}

pub fn serialize_transformation_matrix_4x4(
    matrix: &TransformationMatrix4x4,
    xml_fragment_writer: &mut XmlFragmentWriter<ChunkedSink>,
    target_xml_namespace: CityGmlNamespace,
    target_xml_element: CityGmlElement,
) -> Result<(), Error> {
    let value = matrix
        .to_row_major()
        .iter()
        .map(|v| v.to_string())
        .collect::<Vec<_>>()
        .join(" ");

    xml_fragment_writer.write_leaf_element(target_xml_namespace, target_xml_element, &value)?;

    Ok(())
}

fn transformation_matrix_4x4_from_str(value: &str) -> Result<TransformationMatrix4x4, Error> {
    let values: Vec<f64> = value
        .split_whitespace()
        .filter_map(|v| v.parse().ok())
        .collect();

    Ok(TransformationMatrix4x4::try_from_row_major(values)?)
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::Formatting;

    #[test]
    fn test_deserialize_transformation_matrix_4x4() {
        let xml_document = b"<transformationMatrix>-0.5894514707536183 -0.8078037903020735 0.0 0.0 0.8078037903020735 -0.5894514707536183 0.0 0.0 0.0 0.0 1.0 0.0 0.0 0.0 0.0 1.0</transformationMatrix>";

        let matrix = deserialize_transformation_matrix_4x4(xml_document).expect("should work");

        assert_eq!(matrix.matrix()[(0, 1)], -0.8078037903020735);
    }

    #[test]
    fn test_deserialize_transformation_matrix_4x4_rejects_wrong_count() {
        let xml_document = b"<transformationMatrix>1.0 2.0 3.0</transformationMatrix>";

        let result = deserialize_transformation_matrix_4x4(xml_document);

        assert!(result.is_err());
    }

    #[test]
    fn test_serialize_transformation_matrix_4x4() {
        let matrix = TransformationMatrix4x4::try_from_row_major(vec![
            1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0,
        ])
        .expect("should build");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_transformation_matrix_4x4(
            &matrix,
            &mut xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::TransformationMatrixProperty,
        )
        .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        assert_eq!(
            xml,
            "<transformationMatrix>1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1</transformationMatrix>"
        );
    }

    #[test]
    fn test_round_trip_transformation_matrix_4x4() {
        let xml_document = b"<transformationMatrix>10.289999999999994 0.0 0.0 0.0 0.0 10.289999999999994 0.0 0.0 0.0 0.0 10.289999999999994 0.0 0.0 0.0 0.0 1.0</transformationMatrix>";

        let matrix = deserialize_transformation_matrix_4x4(xml_document).expect("should work");

        let mut xml_fragment_writer =
            XmlFragmentWriter::<ChunkedSink>::new_chunked(Formatting::Compact);
        serialize_transformation_matrix_4x4(
            &matrix,
            &mut xml_fragment_writer,
            CityGmlNamespace::Core,
            CityGmlElement::TransformationMatrixProperty,
        )
        .expect("should serialize");
        let xml = String::from_utf8({
            let mut buf = Vec::new();
            xml_fragment_writer
                .write_to(&mut buf)
                .expect("should flush fragments");
            buf
        })
        .expect("should convert to string");

        let round_tripped =
            deserialize_transformation_matrix_4x4(xml.as_bytes()).expect("should work");

        assert_eq!(matrix, round_tripped);
    }
}
