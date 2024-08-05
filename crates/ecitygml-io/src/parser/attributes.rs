use quick_xml::events::BytesStart;
use quick_xml::Reader;
use std::collections::HashMap;

pub fn extract_attributes(reader: &Reader<&[u8]>, e: &BytesStart) -> HashMap<String, String> {
    let extracted_attributes: HashMap<String, String> = e
        .attributes()
        .map(|attr_res| match attr_res {
            Ok(a) => {
                let key = reader
                    .decoder()
                    .decode(a.key.local_name().as_ref())
                    .unwrap()
                    .to_string();
                let value: String = a
                    .decode_and_unescape_value(reader.decoder())
                    .unwrap()
                    .to_string();
                /*println!(
                    "key: {}, value: {}",
                    reader
                        .decoder()
                        .decode(a.key.local_name().as_ref())
                        .unwrap(),
                    value
                );*/
                (key, value)
            }
            Err(err) => {
                dbg!("unable to read key in DefaultSettings, err = {:?}", err);
                (String::new(), String::new())
            }
        })
        .collect();

    extracted_attributes
}
