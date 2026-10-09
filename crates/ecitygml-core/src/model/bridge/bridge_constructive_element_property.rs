use crate::model::bridge::BridgeConstructiveElement;
use crate::model::common::arena::ArenaProperty;

/// A bridge constructive element held inline or by `xlink:href`, corresponding to `brid:BridgeConstructiveElementPropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `bridge.xsd`).
pub type BridgeConstructiveElementProperty = ArenaProperty<BridgeConstructiveElement>;
