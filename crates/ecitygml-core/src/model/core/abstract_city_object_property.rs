use crate::model::common::arena::ArenaProperty;
use crate::model::core::AbstractCityObjectKind;

/// A city object held inline or by `xlink:href`, corresponding to `core:AbstractCityObjectPropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `core.xsd`).
pub type AbstractCityObjectProperty = ArenaProperty<AbstractCityObjectKind>;
