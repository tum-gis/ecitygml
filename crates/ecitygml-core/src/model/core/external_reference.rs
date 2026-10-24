use egml::model::xs::AnyUri;

/// A reference to an object in another information system, corresponding to `core:ExternalReferenceType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `core.xsd`).
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct ExternalReference {
    pub target_resource: AnyUri,
    pub information_system: Option<AnyUri>,
    pub relation_type: Option<AnyUri>,
}
