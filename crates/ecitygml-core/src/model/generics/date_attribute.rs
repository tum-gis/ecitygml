use egml::model::xs::Date;

/// A generic attribute holding a date, corresponding to `gen:DateAttributeType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `generics.xsd`).
#[derive(Debug, Clone, PartialEq, Eq, Hash, Ord, PartialOrd)]
pub struct DateAttribute {
    pub name: String,
    pub value: Date,
}

impl DateAttribute {
    pub fn new(name: String, value: Date) -> Self {
        Self { name, value }
    }
}
