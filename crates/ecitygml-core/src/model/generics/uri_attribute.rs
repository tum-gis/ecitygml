use egml::model::xs::AnyUri;

/// A generic attribute holding a URI reference, corresponding to `gen:UriAttributeType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `generics.xsd`).
#[derive(Debug, Clone, PartialEq, Eq, Hash, Ord, PartialOrd)]
pub struct UriAttribute {
    pub name: String,
    pub value: AnyUri,
}

impl UriAttribute {
    pub fn new(name: String, value: AnyUri) -> Self {
        Self { name, value }
    }
}
