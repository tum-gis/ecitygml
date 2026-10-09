use crate::model::core::ImplicitGeometry;
use egml::model::base::Property;

/// An implicit geometry held inline or by `xlink:href`, corresponding to `core:ImplicitGeometryPropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `core.xsd`).
pub type ImplicitGeometryProperty = Property<ImplicitGeometry>;
