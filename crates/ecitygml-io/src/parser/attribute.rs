use crate::Error;
use crate::Error::AttributeWithoutName;
use ecitygml_core::model;
use quick_xml::de;
use serde::{Deserialize, Serialize};

pub fn parse_generic_string_attribute(
    xml_document: &String,
) -> Result<model::core::StringAttribute, Error> {
    let parsed_attribute: StringAttribute = de::from_str(xml_document)?;
    let attribute = model::core::StringAttribute::try_from(parsed_attribute)?;

    Ok(attribute)
}

#[derive(Debug, Serialize, Deserialize, Clone, PartialEq, Eq, Hash)]
struct StringAttribute {
    pub name: String,
    pub value: String,
}

impl TryFrom<StringAttribute> for model::core::StringAttribute {
    type Error = Error;

    fn try_from(value: StringAttribute) -> Result<Self, Self::Error> {
        if value.name.is_empty() {
            return Err(AttributeWithoutName("string attribute".to_string()));
        }

        Ok(model::core::StringAttribute {
            name: value.name,
            value: value.value,
        })
    }
}

pub fn parse_generic_int_attribute(
    xml_document: &String,
) -> Result<model::core::IntAttribute, Error> {
    let parsed_attribute: IntAttribute = de::from_str(xml_document)?;
    let attribute = model::core::IntAttribute::try_from(parsed_attribute)?;

    Ok(attribute)
}

#[derive(Debug, Serialize, Deserialize, Clone, PartialEq, Eq, Hash)]
struct IntAttribute {
    pub name: String,
    pub value: i64,
}

impl TryFrom<IntAttribute> for model::core::IntAttribute {
    type Error = Error;

    fn try_from(value: IntAttribute) -> Result<Self, Self::Error> {
        if value.name.is_empty() {
            return Err(AttributeWithoutName("string attribute".to_string()));
        }

        Ok(model::core::IntAttribute {
            name: value.name,
            value: value.value,
        })
    }
}

pub fn parse_generic_double_attribute(
    xml_document: &String,
) -> Result<model::core::DoubleAttribute, Error> {
    let parsed_attribute: DoubleAttribute = de::from_str(xml_document)?;
    let attribute = model::core::DoubleAttribute::try_from(parsed_attribute)?;

    Ok(attribute)
}

#[derive(Debug, Serialize, Deserialize, Clone, PartialEq)]
struct DoubleAttribute {
    pub name: String,
    pub value: f64,
}

impl TryFrom<DoubleAttribute> for model::core::DoubleAttribute {
    type Error = Error;

    fn try_from(value: DoubleAttribute) -> Result<Self, Self::Error> {
        if value.name.is_empty() {
            return Err(AttributeWithoutName("string attribute".to_string()));
        }

        Ok(model::core::DoubleAttribute {
            name: value.name,
            value: value.value,
        })
    }
}

#[derive(Debug, Clone, PartialEq, Serialize, Deserialize)]
#[serde(rename_all = "PascalCase")]
pub enum GenericAttribute {
    #[serde(rename = "StringAttribute")]
    String(StringAttribute),
    #[serde(rename = "IntAttribute")]
    Int(IntAttribute),
    #[serde(rename = "DoubleAttribute")]
    Double(DoubleAttribute),
}

impl TryFrom<GenericAttribute> for model::core::GenericAttribute {
    type Error = Error;

    fn try_from(value: GenericAttribute) -> Result<Self, Self::Error> {
        match value {
            GenericAttribute::String(string_attr) => {
                let core_attr = model::core::StringAttribute::try_from(string_attr)?;
                Ok(model::core::GenericAttribute::String(core_attr))
            }
            GenericAttribute::Int(int_attr) => {
                let core_attr = model::core::IntAttribute::try_from(int_attr)?;
                Ok(model::core::GenericAttribute::Int(core_attr))
            }
            GenericAttribute::Double(double_attr) => {
                let core_attr = model::core::DoubleAttribute::try_from(double_attr)?;
                Ok(model::core::GenericAttribute::Double(core_attr))
            }
        }
    }
}

pub fn parse_generic_attribute(
    xml_document: &String,
) -> Result<model::core::GenericAttribute, Error> {
    let parsed_attribute: GenericAttribute = de::from_str(xml_document)?;
    let attribute = model::core::GenericAttribute::try_from(parsed_attribute)?;

    Ok(attribute)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_parse_generic_attribute_basic() {
        let xml_document = String::from(
            "<gen:StringAttribute>
    <gen:name>attribute_name</gen:name>
    <gen:value>1100</gen:value>
  </gen:StringAttribute>",
        );

        let generic_attribute = parse_generic_attribute(&xml_document).expect("should work");

        assert_eq!(generic_attribute.name(), "attribute_name");
        assert_eq!(
            generic_attribute.as_string().expect("must be string").value,
            "1100"
        );
    }

    #[test]
    fn test_parse_string_attribute_basic() {
        let xml_document = String::from(
            "<gen:StringAttribute>
          <gen:name>attribute_name</gen:name>
          <gen:value>1100</gen:value>
        </gen:StringAttribute>",
        );

        let string_attribute = parse_generic_string_attribute(&xml_document).expect("should work");

        assert_eq!(string_attribute.name, "attribute_name");
        assert_eq!(string_attribute.value, "1100");
    }

    #[test]
    fn test_parse_int_attribute_basic() {
        let xml_document = String::from(
            "<gen:IntAttribute>
          <gen:name>attribute_name</gen:name>
          <gen:value>1100</gen:value>
        </gen:IntAttribute>",
        );

        let int_attribute = parse_generic_int_attribute(&xml_document).expect("should work");

        assert_eq!(int_attribute.name, "attribute_name");
        assert_eq!(int_attribute.value, 1100);
    }

    #[test]
    fn test_parse_double_attribute_basic() {
        let xml_document = String::from(
            "<gen:IntAttribute>
          <gen:name>attribute_name</gen:name>
          <gen:value>42.2</gen:value>
        </gen:IntAttribute>",
        );

        let double_attribute = parse_generic_double_attribute(&xml_document).expect("should work");

        assert_eq!(double_attribute.name, "attribute_name");
        assert_eq!(double_attribute.value, 42.2);
    }
}
