use crate::model::common::arena::ArenaProperty;
use crate::model::relief::AbstractReliefComponentKind;

/// A relief component held inline or by `xlink:href`, corresponding to `dem:AbstractReliefComponentPropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `relief.xsd`).
pub type AbstractReliefComponentProperty = ArenaProperty<AbstractReliefComponentKind>;
