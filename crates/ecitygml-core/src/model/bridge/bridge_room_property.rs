use crate::model::bridge::BridgeRoom;
use crate::model::common::arena::ArenaProperty;

/// A bridge room held inline or by `xlink:href`, corresponding to `brid:BridgeRoomPropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `bridge.xsd`).
pub type BridgeRoomProperty = ArenaProperty<BridgeRoom>;
