use crate::model::building::BuildingPart;
use crate::model::common::arena::ArenaProperty;

/// A building part held inline or by `xlink:href`, corresponding to `bldg:BuildingPartPropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `building.xsd`).
pub type BuildingPartProperty = ArenaProperty<BuildingPart>;
