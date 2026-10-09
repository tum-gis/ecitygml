use crate::model::building::BuildingRoom;
use crate::model::common::arena::ArenaProperty;

/// A building room held inline or by `xlink:href`, corresponding to `bldg:BuildingRoomPropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `building.xsd`).
pub type BuildingRoomProperty = ArenaProperty<BuildingRoom>;
