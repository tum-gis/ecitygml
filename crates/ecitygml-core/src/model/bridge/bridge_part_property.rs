use crate::model::bridge::BridgePart;
use crate::model::common::arena::ArenaProperty;

/// A bridge part held inline or by `xlink:href`, corresponding to `brid:BridgePartPropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `bridge.xsd`).
pub type BridgePartProperty = ArenaProperty<BridgePart>;
