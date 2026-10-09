use egml::model::base::Property;
use egml::model::geometry::primitives::TriangulatedSurface;

/// A TIN held inline or by `xlink:href`, corresponding to `gml:TinPropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `relief.xsd`).
pub type TinProperty = Property<TriangulatedSurface>;
