use crate::model::generics::GenericAttributeKind;
use egml::model::xs::AnyUri;

/// A named group of generic attributes, corresponding to `gen:GenericAttributeSetType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `generics.xsd`).
#[derive(Debug, Clone, PartialEq)]
pub struct GenericAttributeSet {
    pub name: String,
    /// The authority (e.g. an organization or a code list) that defines the set.
    pub code_space: Option<AnyUri>,
    pub generic_attributes: Vec<GenericAttributeKind>,
}

impl GenericAttributeSet {
    pub fn new(name: String, generic_attributes: Vec<GenericAttributeKind>) -> Self {
        Self {
            name,
            code_space: None,
            generic_attributes,
        }
    }
}
