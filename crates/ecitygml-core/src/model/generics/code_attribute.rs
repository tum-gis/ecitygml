use egml::model::basic_types::Code;

/// A generic attribute holding a code with an optional code space, corresponding to `gen:CodeAttributeType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `generics.xsd`).
#[derive(Debug, Clone, PartialEq, PartialOrd, Eq, Hash)]
pub struct CodeAttribute {
    pub name: String,
    pub value: Code,
}

impl CodeAttribute {
    pub fn new(name: String, value: Code) -> Self {
        Self { name, value }
    }
}
