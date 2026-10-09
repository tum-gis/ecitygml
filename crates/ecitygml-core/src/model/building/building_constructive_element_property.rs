use crate::model::building::BuildingConstructiveElement;
use crate::model::common::arena::ArenaProperty;

/// A building constructive element held inline or by `xlink:href`, corresponding to `bldg:BuildingConstructiveElementPropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `building.xsd`).
pub type BuildingConstructiveElementProperty = ArenaProperty<BuildingConstructiveElement>;
