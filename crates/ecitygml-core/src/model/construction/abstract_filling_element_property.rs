use crate::model::common::arena::ArenaProperty;
use crate::model::construction::AbstractFillingElementKind;

/// A filling element held inline or by `xlink:href`, corresponding to `con:AbstractFillingElementPropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `construction.xsd`).
pub type AbstractFillingElementProperty = ArenaProperty<AbstractFillingElementKind>;
