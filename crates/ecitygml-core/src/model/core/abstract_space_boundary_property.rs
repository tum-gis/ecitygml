use crate::model::common::arena::ArenaProperty;
use crate::model::core::abstract_space_boundary_kind::AbstractSpaceBoundaryKind;

/// A space boundary held inline or by `xlink:href`, corresponding to `core:AbstractSpaceBoundaryPropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `core.xsd`).
pub type AbstractSpaceBoundaryProperty = ArenaProperty<AbstractSpaceBoundaryKind>;
