use crate::model::bridge::BridgeFurniture;
use crate::model::common::arena::ArenaProperty;

/// A bridge furniture held inline or by `xlink:href`, corresponding to `brid:BridgeFurniturePropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `bridge.xsd`).
pub type BridgeFurnitureProperty = ArenaProperty<BridgeFurniture>;
