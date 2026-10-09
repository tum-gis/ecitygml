use crate::model::building::AbstractBuildingSubdivisionKind;
use crate::model::common::arena::ArenaProperty;

/// A building subdivision held inline or by `xlink:href`, corresponding to `bldg:AbstractBuildingSubdivisionPropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `building.xsd`).
pub type AbstractBuildingSubdivisionProperty = ArenaProperty<AbstractBuildingSubdivisionKind>;
