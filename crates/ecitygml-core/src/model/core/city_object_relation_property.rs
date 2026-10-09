use crate::model::core::CityObjectRelation;
use egml::model::base::Property;

/// A city object relation held inline or by `xlink:href`, corresponding to `core:CityObjectRelationPropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `core.xsd`).
pub type CityObjectRelationProperty = Property<CityObjectRelation>;
