use crate::model::appearance::AbstractSurfaceDataKind;
use crate::model::common::arena::ArenaProperty;

/// Surface data held inline or by `xlink:href`, corresponding to `app:AbstractSurfaceDataPropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `appearance.xsd`).
pub type AbstractSurfaceDataProperty = ArenaProperty<AbstractSurfaceDataKind>;
