use crate::model::common::arena::ArenaProperty;
use crate::model::construction::AbstractFillingSurfaceKind;

/// A filling surface held inline or by `xlink:href`, corresponding to `con:AbstractFillingSurfacePropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `construction.xsd`).
pub type AbstractFillingSurfaceProperty = ArenaProperty<AbstractFillingSurfaceKind>;
