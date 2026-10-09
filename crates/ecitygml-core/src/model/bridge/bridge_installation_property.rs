use crate::model::bridge::BridgeInstallation;
use crate::model::common::arena::ArenaProperty;

/// A bridge installation held inline or by `xlink:href`, corresponding to `brid:BridgeInstallationPropertyType`
/// ([OGC 21-006r2](https://docs.ogc.org/is/21-006r2/21-006r2.html), `bridge.xsd`).
pub type BridgeInstallationProperty = ArenaProperty<BridgeInstallation>;
