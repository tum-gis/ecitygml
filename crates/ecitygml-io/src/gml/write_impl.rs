use crate::Error;
use crate::gml::codec::core::serialize_city_model;
use ecitygml_core::model::core::CityModel;
use egml::io::util::{ChunkedSink, Formatting, XmlFragmentWriter};
use std::io::Write;

pub fn serialize<W: Write + Sync>(
    writer: &mut W,
    city_model: &CityModel,
    formatting: Formatting,
) -> Result<(), Error> {
    let mut xml_fragment_writer = XmlFragmentWriter::<ChunkedSink>::new_chunked(formatting);

    xml_fragment_writer
        .write_leaf_bytes(br#"<?xml version="1.0" encoding="UTF-8" standalone="yes"?>"#)?;

    serialize_city_model(city_model, &mut xml_fragment_writer)?;

    xml_fragment_writer.write_to(writer)?;

    Ok(())
}
