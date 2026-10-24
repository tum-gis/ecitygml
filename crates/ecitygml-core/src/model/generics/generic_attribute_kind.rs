use crate::model::generics::generic_attribute_set::GenericAttributeSet;
use crate::model::generics::string_attribute::StringAttribute;
use crate::model::generics::{
    CodeAttribute, DateAttribute, DoubleAttribute, IntAttribute, MeasureAttribute, UriAttribute,
};

#[derive(Debug, Clone, PartialEq)]
pub enum GenericAttributeKind {
    StringAttribute(StringAttribute),
    IntAttribute(IntAttribute),
    DoubleAttribute(DoubleAttribute),
    DateAttribute(DateAttribute),
    CodeAttribute(CodeAttribute),
    UriAttribute(UriAttribute),
    MeasureAttribute(MeasureAttribute),
    GenericAttributeSet(GenericAttributeSet),
}

impl GenericAttributeKind {
    pub fn name(&self) -> &str {
        match self {
            GenericAttributeKind::StringAttribute(x) => &x.name,
            GenericAttributeKind::IntAttribute(x) => &x.name,
            GenericAttributeKind::DoubleAttribute(x) => &x.name,
            GenericAttributeKind::DateAttribute(x) => &x.name,
            GenericAttributeKind::CodeAttribute(x) => &x.name,
            GenericAttributeKind::UriAttribute(x) => &x.name,
            GenericAttributeKind::MeasureAttribute(x) => &x.name,
            GenericAttributeKind::GenericAttributeSet(x) => &x.name,
        }
    }

    pub fn as_string(&self) -> Option<&StringAttribute> {
        if let GenericAttributeKind::StringAttribute(attr) = self {
            Some(attr)
        } else {
            None
        }
    }

    pub fn as_int(&self) -> Option<&IntAttribute> {
        if let GenericAttributeKind::IntAttribute(attr) = self {
            Some(attr)
        } else {
            None
        }
    }

    pub fn as_double(&self) -> Option<&DoubleAttribute> {
        if let GenericAttributeKind::DoubleAttribute(attr) = self {
            Some(attr)
        } else {
            None
        }
    }

    pub fn as_date(&self) -> Option<&DateAttribute> {
        if let GenericAttributeKind::DateAttribute(attr) = self {
            Some(attr)
        } else {
            None
        }
    }

    pub fn as_code(&self) -> Option<&CodeAttribute> {
        if let GenericAttributeKind::CodeAttribute(attr) = self {
            Some(attr)
        } else {
            None
        }
    }

    pub fn as_uri(&self) -> Option<&UriAttribute> {
        if let GenericAttributeKind::UriAttribute(attr) = self {
            Some(attr)
        } else {
            None
        }
    }
}

impl From<StringAttribute> for GenericAttributeKind {
    fn from(attr: StringAttribute) -> Self {
        GenericAttributeKind::StringAttribute(attr)
    }
}

impl From<IntAttribute> for GenericAttributeKind {
    fn from(attr: IntAttribute) -> Self {
        GenericAttributeKind::IntAttribute(attr)
    }
}

impl From<DoubleAttribute> for GenericAttributeKind {
    fn from(attr: DoubleAttribute) -> Self {
        GenericAttributeKind::DoubleAttribute(attr)
    }
}

impl From<DateAttribute> for GenericAttributeKind {
    fn from(attr: DateAttribute) -> Self {
        GenericAttributeKind::DateAttribute(attr)
    }
}

impl From<CodeAttribute> for GenericAttributeKind {
    fn from(attr: CodeAttribute) -> Self {
        GenericAttributeKind::CodeAttribute(attr)
    }
}

impl From<UriAttribute> for GenericAttributeKind {
    fn from(attr: UriAttribute) -> Self {
        GenericAttributeKind::UriAttribute(attr)
    }
}

impl From<MeasureAttribute> for GenericAttributeKind {
    fn from(attr: MeasureAttribute) -> Self {
        GenericAttributeKind::MeasureAttribute(attr)
    }
}

impl From<GenericAttributeSet> for GenericAttributeKind {
    fn from(attr: GenericAttributeSet) -> Self {
        GenericAttributeKind::GenericAttributeSet(attr)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::model::xs::Date;

    #[test]
    fn test_date_attribute_kind() {
        let date = Date::from_parts(2015, 6, 1, 0).expect("valid date");
        let kind: GenericAttributeKind = DateAttribute::new("renovatedOn".to_string(), date).into();

        assert_eq!(kind.name(), "renovatedOn");
        assert_eq!(kind.as_date().map(|x| x.value), Some(date));
        assert!(kind.as_int().is_none());
    }

    #[test]
    fn test_as_date_is_none_for_other_kinds() {
        let kind: GenericAttributeKind = IntAttribute::new("storeys".to_string(), 3).into();
        assert!(kind.as_date().is_none());
    }

    #[test]
    fn test_code_attribute_kind() {
        use egml::model::basic_types::Code;

        let code = Code::with_code_space("https://example.org/roofTypes", "1000");
        let kind: GenericAttributeKind =
            CodeAttribute::new("roofType".to_string(), code.clone()).into();

        assert_eq!(kind.name(), "roofType");
        assert_eq!(kind.as_code().map(|x| &x.value), Some(&code));
        assert!(kind.as_date().is_none());
    }

    #[test]
    fn test_as_code_is_none_for_other_kinds() {
        let kind: GenericAttributeKind = IntAttribute::new("storeys".to_string(), 3).into();
        assert!(kind.as_code().is_none());
    }

    #[test]
    fn test_uri_attribute_kind() {
        use egml::model::xs::AnyUri;

        let uri = AnyUri::new("https://example.org/cadastre/4711");
        let kind: GenericAttributeKind =
            UriAttribute::new("cadastreRecord".to_string(), uri.clone()).into();

        assert_eq!(kind.name(), "cadastreRecord");
        assert_eq!(kind.as_uri().map(|x| &x.value), Some(&uri));
        assert!(kind.as_code().is_none());
    }

    #[test]
    fn test_as_uri_is_none_for_other_kinds() {
        let kind: GenericAttributeKind = IntAttribute::new("storeys".to_string(), 3).into();
        assert!(kind.as_uri().is_none());
    }
}
